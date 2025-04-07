#include "config.h"
#include "drawRoom.h"

extern bool open[10];
extern bool close[10];
extern float openAngle[10];

void drawWardrobe(glm::mat4 room, std::tuple<float, float, float> color) {

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
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 side = wardrobe;
		side = glm::translate(side, glm::vec3(69.0f*i, 0.0f, 1.0f));
		side = glm::rotate(side, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
		drawCube(side, std::tuple<float, float, float>(25.0f, 100.0f, 1.0f), color);
	}

	/*glm::mat4 rightSide = wardrobe;
	rightSide = glm::translate(rightSide, glm::vec3(-69.0f, 0.0f, 1.0f));
	rightSide = glm::rotate(rightSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(rightSide, std::tuple<float, float, float>(25.0f, 100.0f, 1.0f), color);*/

	// front aka door  maja sie obracac 
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 doorWing = wardrobe;
		doorWing = glm::translate(doorWing, glm::vec3(34.5f*i, 0.0f, -25.0f));
		// animation
		doorWing = glm::translate(doorWing, glm::vec3(34.5f*i, 0.0f, 0.0f));
		doorWing = glm::rotate(doorWing, openAngle[0]*i, glm::vec3(0.0f, -1.0f, 0.0f));
		doorWing = glm::translate(doorWing, glm::vec3(-34.5f*i, 0.0f, 0.0f));
		drawCube(doorWing, std::tuple<float, float, float>(34.0f, 100.0f, 1.0f), color);
	}
	
	//shelves
	for (float i = 1; i < 5; i++) {
		glm::mat4 shelf = wardrobe;
		shelf = glm::translate(shelf, glm::vec3(0.0f, -101.0f+38.0f*i, 1.0f));
		shelf = glm::rotate(shelf, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCube(shelf, std::tuple<float, float, float>(70.0f, 25.0f, 1.0f), color);
	}
}

void drawDesk(glm::mat4 room, std::tuple<float, float, float> color) {

}

void drawFurniture(glm::mat4 room) {

	std::tuple<float, float, float> furnitureColor(0.4f, 0.12f, 0.12f); //brown color for the furniture

	if (open[0]) {
		if (openAngle[0] >= 90 * PI / 180) {
			open[0] = false;
		}
	}
	else if (close[0]) {
		if (openAngle[0] <= 0 * PI / 180) {
			close[0] = false;
		}

	}
	drawWardrobe(room, furnitureColor);
	//drawDesk(room, furnitureColor);
}