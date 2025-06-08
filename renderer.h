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

public:
	Renderer(ShaderProgram* sp, float* verts, float* norms, float* texs, int count)
		: sp(sp), vertices(verts), normals(norms), texCoords(texs), vertexCount(count) {}

	void draw(glm::mat4 modelMatrix, std::tuple<float, float, float> scale, glm::vec3 positionOffset);
};