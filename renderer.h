#pragma once

#include "config.h"
#include "shaderprogram.h"


class Renderer {

private:
	ShaderProgram* sp;
	float* vertices;
	float* normals;
	float* texCoords;
	int vertexCount;
	float* c1; //= nullptr;
	float* c2; //= nullptr;
	float* c3; //= nullptr;
	 
	void parallax();

public:
	Renderer(ShaderProgram* sp, float* verts, float* norms, float* texs, int count)
		: sp(sp), vertices(verts), normals(norms), texCoords(texs), vertexCount(count), c1(nullptr), c2(nullptr), c3(nullptr){}

	Renderer(ShaderProgram* sp, float* verts, float* norms, float* texs, int count, float* c1, float* c2, float* c3)
		: sp(sp), vertices(verts), normals(norms), texCoords(texs), vertexCount(count), c1(c1), c2(c2), c3(c3) {}

	void draw(glm::mat4 modelMatrix, std::tuple<float, float, float> scale, glm::vec3 positionOffset, bool p);
};