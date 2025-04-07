#include "pillowModel.h"
#include <config.h>
#include "objloader.hpp"

std::vector<float> verticesP;
std::vector<float> vertexNormalsP;
std::vector<float> texCoordsP;

static int lengthVectors;

void loadPillow(const char* filename) {
	bool res = loadOBJ(filename, verticesP, texCoordsP, vertexNormalsP);
	lengthVectors = verticesP.size() / 3;
	return;
}

void drawPillow() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, verticesP.data());
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, vertexNormalsP.data());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, texCoordsP.data());

	glDrawArrays(GL_TRIANGLES, 0, lengthVectors);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

