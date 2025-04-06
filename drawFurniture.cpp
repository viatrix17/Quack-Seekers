#include "config.h"
#include "drawRoom.h"

extern bool open;

void drawWardrobe(glm::mat4 room, std::tuple<float, float, float> color, float openAngle) {

	glm::mat4 wardrobe = room;
	wardrobe = glm::translate(wardrobe, glm::vec3(-130.0f + 20.0f, -23.0f, 200.0f - 20.0f - 25.0f));

	glm::mat4 back = wardrobe;
	back = glm::translate(back, glm::vec3(0.0f, 0.0f, 25.0f));
	drawCube(back, std::tuple<float, float, float> (68.0f, 100.0f, 1.0f), color);
	
	

	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 board = wardrobe;
		board = glm::translate(board, glm::vec3(0.0f, 101.0f*i, 1.0f));
		board = glm::rotate(board, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCube(board, std::tuple<float, float, float>(70.0f, 25.0f, 1.0f), color);
	}

	// sides
	glm::mat4 leftSide = wardrobe;
	leftSide = glm::translate(leftSide, glm::vec3(69.0f,0.0f,1.0f));
	leftSide = glm::rotate(leftSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(leftSide, std::tuple<float, float, float>(25.0f, 100.0f, 1.0f), color);

	glm::mat4 rightSide = wardrobe;
	rightSide = glm::translate(rightSide, glm::vec3(-69.0f, 0.0f, 1.0f));
	rightSide = glm::rotate(rightSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(rightSide, std::tuple<float, float, float>(25.0f, 100.0f, 1.0f), color);

	// front aka door  maja sie obracac 
	glm::mat4 leftWing = wardrobe;
	leftWing = glm::translate(leftWing, glm::vec3(34.5f, 0.0f, -25.0f));
	// animation
	leftWing = glm::translate(leftWing, glm::vec3(34.5f, 0.0f, 0.0f));
	leftWing = glm::rotate(leftWing, openAngle, glm::vec3(0.0f, -1.0f, 0.0f));
	leftWing = glm::translate(leftWing, glm::vec3(-34.5f, 0.0f, 0.0f));
	drawCube(leftWing, std::tuple<float, float, float>(34.0f, 100.0f, 1.0f), color);
	
	glm::mat4 rightWing = wardrobe;
	rightWing = glm::translate(rightWing, glm::vec3(-34.5f, 0.0f, -25.0f));
	rightWing = glm::translate(rightWing, glm::vec3(-34.5f, 0.0f, 0.0f));
	rightWing = glm::rotate(rightWing, -openAngle, glm::vec3(0.0f, -1.0f, 0.0f));
	rightWing = glm::translate(rightWing, glm::vec3(34.5f, 0.0f, 0.0f));
	drawCube(rightWing, std::tuple<float, float, float>(34.0f, 100.0f, 1.0f), color);

	//shelves
	for (float i = 1; i < 5; i++) {
		glm::mat4 shelf = wardrobe;
		shelf = glm::translate(shelf, glm::vec3(0.0f, -101.0f+38.0f*i, 1.0f));
		shelf = glm::rotate(shelf, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCube(shelf, std::tuple<float, float, float>(70.0f, 25.0f, 1.0f), color);
	}
}

void drawFurniture(glm::mat4 room, float openAngle) {

	std::tuple<float, float, float> furnitureColor(0.4f, 0.12f, 0.12f); //brown color for the furniture

	std::cout << "drawing furniture!\n";
	if (open) {
		if (openAngle >= 90 * PI / 180) {
			open = false;
		}
	}
	else {
		if (openAngle <= 0 * PI / 180) {
			open = true;
		}
	}
	drawWardrobe(room,furnitureColor, openAngle);
}