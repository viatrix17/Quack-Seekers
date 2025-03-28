#include "config.h"

void drawWall(glm::mat4 wall) {
	//wall = glm::scale(wall, glm::vec3());
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(wall));
	glUniform4f(spLambert->u("color"), 1, 0.5, 0, 1);
	Models::cube.drawSolid();

}
void drawRoom() {

	std::cout << "drawing a room!\n";

	// drawing the non-window walls
	glm::mat4 room = glm::mat4(1.0f);

	for (int i = 0; i < 1; i++) { // three non-window walls
		glm::mat4 wall = room;
		wall = glm::translate(wall, glm::vec3(0.0f,0.0f,20.0f)); 
		drawWall(wall);
	}

	// drawing the ceiling and the floor
}