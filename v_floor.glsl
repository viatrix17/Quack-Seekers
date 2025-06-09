#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lamp;
uniform vec4 sun;
uniform vec3 cameraWorldPos;

in vec4 vertex;
in vec4 normal;
in vec2 texCoord0;

out vec3 sun_l;
out vec3 lamp_l;
out vec3 n;
out vec3 v;

out vec2 iTexCoord0;

void main(void) {
    vec4 fragPos =  M * vertex;
    // Correct normal transformation
    mat3 normalMatrix = mat3(transpose(inverse(M))); // or mat3(V*M);
    vec3 fragNorm = normalMatrix * normal.xyz;

    // Vectors in eye space
    lamp_l = normalize(vec3(lamp) - fragPos.xyz); // lamp light direction
    sun_l = normalize(vec3(sun) - fragPos.xyz); // syn light direction
    n = normalize(fragNorm);                   // normal
    v = normalize(cameraWorldPos-fragPos.xyz);               // view direction

    iTexCoord0 = texCoord0;
    gl_Position = P * V* fragPos;
}
