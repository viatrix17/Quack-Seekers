#include "config.h"

void pillow(glm::mat4 bed) {
	glm::mat4 pillow1 = bed;
	pillow1 = glm::translate(pillow1, glm::vec3(50.0f, 0.0f, -50.0f));
	pillow1 = glm::scale(pillow1, glm::vec3(20.0f, 20.0f, 20.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(pillow1));
	glUniform4f(spLambert->u("color"), 0, 0, 1, 0);
	drawPillow();
}

void drawFurniture(glm::mat4 P, glm::mat4 V, GLuint tex) {

	std::cout << "drawing furniture!\n";
	
	glm::mat4 bed = glm::mat4(1.0f);
	pillow(bed);
	

	
	
}