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
	vec3 mr = reflect(-ml,mn); //Wektor odbity
	vec4 kd = texture(textureMap0,iTexCoord0);
	vec4 ks = texture(textureMap1,iTexCoord0);

	vec4 ambientColor = vec4(0.3,0.3,0.3,1);
	float nl = clamp(dot(mn, ml), 0, 1); //Kosinus k¹ta pomiêdzy wektorami n i l.
	float rv = pow(clamp(dot(mr, mv), 0, 1), 5); // Kosinus k¹ta pomiêdzy wektorami r i v podniesiony do 25 potêgi

	pixelColor = vec4(nl * kd.rgb, kd.a) + vec4(ks.rgb*rv,0) + vec4(kd.rgb*ambientColor.rgb,kd.a);
	
}
