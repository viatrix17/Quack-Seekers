#include "config.h"

void drawFurniture(glm::mat4 P, glm::mat4 V, GLuint tex) {

	std::cout << "drawing furniture!\n";
	//pillow.draw();
	
	glm::mat4 bed = glm::mat4(1.0f);

	//spTextured->use();
	
	//glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	//glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));

	glm::mat4 pillow1 = bed;
	pillow1 = glm::scale(pillow1, glm::vec3(20.0f, 20.0f, 20.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(pillow1));
	glUniform4f(spLambert->u("color"), 0, 0, 1, 0);
	drawPillow();
	
}