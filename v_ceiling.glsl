
#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;
uniform vec3 cameraWorldPos;


//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
// in vec4 color; //kolor zwi¹zany z wierzcho³kiem
// in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord0;
in vec4 c1;
in vec4 c2;
in vec4 c3;

//Zmienne interpolowane
// out vec4 ic;
out vec4 l;
// out vec4 n;
out vec4 v;
out vec2 iTexCoord0;


void main(void) {
    mat4 invTBN = mat4(c1, c2, c3, vec4(0, 0, 0, 1)); //macierz odwrotna transponowana do macierzy TBN)
   // vec4 lp = vec4(0, 70, -6, 1); //przestrzeñ œwiata
    l = normalize(invTBN*(inverse(M) * lp - vertex)); //wektor do œwiat³a w przestrzeni oka
    v = normalize(invTBN*(inverse(V*M)*vec4(cameraWorldPos,1.0) - vertex)); //wektor do obserwatora w przestrzeni oka
    // n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
    iTexCoord0 = texCoord0;
    
    // ic = color;
    
    gl_Position=P*V*M*vertex;
}
