#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec3 l;
in vec3 n;
in vec3 v;
in vec2 iTexCoord0;

void main(void) {

	vec3 ml = normalize(l);
	vec3 mn = normalize(n);
	vec3 mv = normalize(v);
	vec3 mr = reflect(-ml, mn);

	vec4 kd = texture(textureMap0, iTexCoord0);
	vec4 ks = texture(textureMap1, iTexCoord0);

	float shininess = 0.25;
	vec4 ambientColor = vec4(0.3, 0.3, 0.3, 1);

	float nl = clamp(dot(mn, ml), 0, 1);
	float rv = pow(clamp(dot(mr, mv), 0.0, 1.0), shininess);
	rv = max(rv - 0.1, 0.0); // cut off small highlights

	float specIntensity = rv * ks.r * 0.05;

	vec3 specular = vec3(1.0) * specIntensity; // neutral white specular

	pixelColor = vec4(nl * kd.rgb, kd.a) + vec4(specular * rv * 0.03, 0) + vec4(kd.rgb * ambientColor.rgb, kd.a);

}
