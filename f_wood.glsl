#version 330

uniform sampler2D textureMap0;


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 l;
in vec4 n;
in vec4 v;
in vec2 iTexCoord0;

void main(void) {

	vec4 ml = normalize(l);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	vec4 mr = reflect(-ml,mn); //Wektor odbity
	vec4 kd = texture(textureMap0,iTexCoord0);
	vec4 ks = kd*0.3;

	float distance = length(l);  // Odleg³oœæ od œwiat³a
	float attenuation = 1.0;// / (1.0 + 0.1 * distance + 0.0001 * distance * distance);

	vec4 ambientColor = vec4(0.3,0.3,0.3,1);
	float nl = clamp(dot(mn, ml), 0, 1); //Kosinus k¹ta pomiêdzy wektorami n i l.
	float rv = pow(clamp(dot(mr, mv), 0, 1), 25); // Kosinus k¹ta pomiêdzy wektorami r i v podniesiony do 25 potêgi

	pixelColor = attenuation * (vec4(nl * kd.rgb, kd.a) + vec4(ks.rgb*rv,0) + vec4(kd.rgb*ambientColor.rgb,kd.a));
	


}


