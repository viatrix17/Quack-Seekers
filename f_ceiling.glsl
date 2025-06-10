#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
uniform vec3 sunLightColor;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec3 lamp_l;
in vec3 sun_l;
in vec3 n;
in vec3 v;
in vec2 iTexCoord0;

void main(void) {

	float distance = length(lamp_l);  // Odleg³oœæ od œwiat³a ale tylko dla lampy
	float attenuation = 1.0 / (1.0 + 0.1 * distance + 0.1 * distance * distance);
	
	vec3 lamp_ml = normalize(lamp_l);
	vec3 sun_ml = normalize(sun_l);
	vec3 mn = normalize(n);
	vec3 mv = normalize(v);
	vec3 lamp_mr = reflect(-lamp_ml, mn);
	vec3 sun_mr = reflect(-sun_ml, mn);

	vec4 kd = texture(textureMap0, iTexCoord0);
	vec4 ks = texture(textureMap1, iTexCoord0);

	float shininess = 0.25;
	vec4 ambientColor = vec4(0.4, 0.4, 0.4, 1);

	float lamp_nl = clamp(dot(mn, lamp_ml), 0, 1);
	float sun_nl = clamp(dot(mn, sun_ml), 0, 1);
	float lamp_rv = pow(clamp(dot(lamp_mr, mv), 0.0, 1.0), 1);
	float sun_rv = pow(clamp(dot(sun_mr, mv), 0.0, 1.0), 5);
	//rv = max(rv - 0.1, 0.0); // cut off small highlights

	float lamp_specIntensity = lamp_rv * ks.r * 0.0005;
	float sun_specIntensity = sun_rv * ks.r * 0.005;

	vec3 lamp_specular = vec3(1.0) * lamp_specIntensity; // neutral white specular
	vec3 sun_specular = vec3(1.0) * sun_specIntensity; // neutral white specular

	pixelColor = vec4(sunLightColor * sun_nl * kd.rgb, kd.a) + vec4(sunLightColor * sun_specular * sun_rv, 0) + attenuation * vec4(lamp_nl * kd.rgb, kd.a) + attenuation * vec4(lamp_specular * lamp_rv, 0) + vec4(kd.rgb * ambientColor.rgb, kd.a);

}
