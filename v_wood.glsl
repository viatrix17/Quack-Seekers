#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wektor normalny wierzchołka w przestrzeni modelu
in vec2 texCoord0;

out vec4 iC;
out vec4 l;
out vec4 n;
out vec4 v;

out vec2 iTexCoord0;

void main(void) {

    vec4 normNormal = normalize(normal);
    l = normalize(lp - M * vertex);//znormalizowany wektor do światła w przestrzeni swiata
    n = normalize(M * normNormal);//znormalizowany wektor normalny w przestrzeni swiata
    v = normalize(vec4(0, 0, 0, 1) - M * vertex); //Wektor do obserwatora w przestrzeni swiata

    iTexCoord0=texCoord0;

    gl_Position=P*V*M*vertex;
}
