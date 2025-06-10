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

	float distance = length(lamp_l);  // Odleg³oœæ od œwiat³a
	float attenuation = 1.0 / (1.0 + 0.1 * distance + 0.5 * distance * distance);

	vec3 lamp_ml = normalize(lamp_l);
	vec3 sun_ml = normalize(sun_l);
	vec3 mn = normalize(n);
	vec3 mv = normalize(v);
	vec3 lamp_mr = reflect(-lamp_ml,mn); //Wektor odbity
	vec3 sun_mr = reflect(-sun_ml,mn); //Wektor odbity
	vec4 kd = texture(textureMap0,iTexCoord0);
	vec4 ks = texture(textureMap1,iTexCoord0);
	

	vec4 ambientColor = vec4(0.3,0.3,0.3,1);
	float lamp_nl = clamp(dot(mn, lamp_ml), 0, 1); //Kosinus k¹ta pomiêdzy wektorami n i l.
	float sun_nl = clamp(dot(mn, sun_ml), 0, 1); //Kosinus k¹ta pomiêdzy wektorami n i l.
	float lamp_rv = pow(clamp(dot(lamp_mr, mv), 0, 1), 25); // Kosinus k¹ta pomiêdzy wektorami r i v podniesiony do 25 potêgi
	float sun_rv = pow(clamp(dot(sun_mr, mv), 0, 1), 25); // Kosinus k¹ta pomiêdzy wektorami r i v podniesiony do 25 potêgi

	pixelColor = vec4(sunLightColor * sun_nl * kd.rgb, kd.a) + attenuation * vec4(lamp_nl * kd.rgb, kd.a) + vec4(sunLightColor * ks.rgb * sun_rv, 0) + attenuation * vec4(ks.rgb * lamp_rv, 0) + vec4(kd.rgb*ambientColor.rgb,kd.a);;

}
