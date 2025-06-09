#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;
uniform vec3 cameraWorldPos;

in vec4 vertex;
in vec2 texCoord0;
in vec4 c1;
in vec4 c2;
in vec4 c3;

out vec4 l;         // wektor œwiat³a w przestrzeni tangentowej
out vec4 v;         // wektor widza w przestrzeni tangentowej
out vec2 iTexCoord0;

void main(void) {

    mat4 invTBN = mat4(c1, c2, c3, vec4(0,0,0,1));
    
    vec4 posModel = vertex;

    // œwiat³o w przestrzeni modelu
    vec4 lightVecModel = inverse(M) * lp - posModel;
    // konwersja do przestrzeni tangentowej
    l = normalize(invTBN * lightVecModel);

    // wektor widza w przestrzeni modelu
    vec4 viewVecModel = inverse(M) * vec4(cameraWorldPos, 1.0) - posModel;
    // konwersja do przestrzeni tangentowej
    v = normalize(invTBN * viewVecModel);

    iTexCoord0 = texCoord0;

    gl_Position = P * V * M * vertex;
}
