#include "config.h"
#include "drawRoom.h"

extern bool open[10];
extern bool close[10];
extern float openAngle[10];
extern glm::vec3 drawerOffset;

void drawWardrobe(glm::mat4 room, std::tuple<float, float, float> color) {

	glm::mat4 wardrobe = room;
	wardrobe = glm::translate(wardrobe, wardrobePos);

	glm::mat4 back = wardrobe;
	back = glm::translate(back, glm::vec3(0.0f, 0.0f, 25.0f));
	drawCube(back, std::tuple<float, float, float> (68.0f, 100.0f, 1.0f), color);
	
	// top and 
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

	glm::mat4 desk = room;
	desk = glm::translate(desk, deskPos);

	glm::mat4 board = desk;
	board = glm::rotate(desk, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCube(board, std::tuple<float, float, float>(72.0f, 27.0f, 1.0f), color);

	//140cmx50cmx75cm

	//sides
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 deskSide = desk;
		deskSide = glm::translate(deskSide, glm::vec3(69.0f * i, -38.5f, 0.0f));
		deskSide = glm::rotate(deskSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
		drawCube(deskSide, std::tuple<float, float, float>(25.0f, 37.5f, 1.0f), color);
	}

	//the drawer
	glm::mat4 drawer = desk;
	drawer = glm::translate(drawer, drawerPos + drawerOffset);

	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 drawerSide = drawer;
		drawerSide = glm::translate(drawerSide, glm::vec3(17.0f*i, 0.0f, -1.0f));
		drawerSide = glm::rotate(drawerSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
		drawCube(drawerSide, std::tuple<float, float, float>(20.0f, 10.0f, 1.0f), color);
	}
	
	glm::mat4 drawerFront = drawer;
	drawerFront = glm::translate(drawerFront, glm::vec3(0.0f, 0.0f, -22.0f));
	drawCube(drawerFront, std::tuple<float, float, float>(21.0f, 12.0f, 1.0f), color);

	glm::mat4 drawerBack = drawer;
	drawerBack = glm::translate(drawerBack, glm::vec3(0.0f, 0.0f, 20.0f));
	drawCube(drawerBack, std::tuple<float, float, float>(18.0f, 10.0f, 1.0f), color);
	
	glm::mat4 drawerBottom = drawer;
	drawerBottom = glm::translate(drawerBottom, glm::vec3(0.0f, -11.0f, 0.0f));
	drawerBottom = glm::rotate(drawerBottom, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCube(drawerBottom, std::tuple<float, float, float>(18.0f, 21.0f, 1.0f), color);

	//the cabinet
	glm::mat4 cabinet = desk;
	cabinet = glm::translate(cabinet, drawerPos + cabinetPos);

	glm::mat4 cabinetSide = cabinet;
	cabinetSide = glm::translate(cabinetSide, glm::vec3(20.0f, 12.0f, 0.0f));
	cabinetSide = glm::rotate(cabinetSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(cabinetSide, std::tuple<float, float, float>(21.0f, 35.0f, 1.0f), color);
	
	glm::mat4 cabinetFront = cabinet;
	cabinetFront = glm::translate(cabinetFront, glm::vec3(0.0f, -1.0f, -22.0f));
	//animation
	cabinetFront = glm::translate(cabinetFront, glm::vec3(-21.0f, 0.0f, 0.0f));
	cabinetFront = glm::rotate(cabinetFront, openAngle[1], glm::vec3(0.0f, 1.0f, 0.0f));
	cabinetFront = glm::translate(cabinetFront, glm::vec3(21.f, 0.0f, 0.0f));
	drawCube(cabinetFront, std::tuple<float, float, float>(21.0f, 23.0f, 1.0f), color);

	glm::mat4 cabinetBack = cabinet;
	cabinetBack = glm::translate(cabinetBack, glm::vec3(-0.2f, 12.0f, 22.0f));
	drawCube(cabinetBack, std::tuple<float, float, float>(21.1f, 36.0f, 1.0f), color);

	for (float i = 0; i <= 1; i++) {
		glm::mat4 cabinetBottom = cabinet;
		cabinetBottom = glm::translate(cabinetBottom, glm::vec3(0.0f-2.0f*(1-i), 0.0f - i * (23.0f), 0.0f));
		cabinetBottom = glm::rotate(cabinetBottom, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCube(cabinetBottom, std::tuple<float, float, float>(21.0f, 21.0f, 1.0f), color);
	}

	//drawBoxes();

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
	if (open[1]) {
		if (drawerOffset.z <= -40.0f) {
			drawerOffset.z = -40.0f;
			open[1] = false;
		}
	}
	else if (close[1]) {
		if (drawerOffset.z >= 0.0f) {
			drawerOffset.z = 0.0f;
			close[1] = false;
		}
	}
	if (open[2]) {
		if (openAngle[1] >= 90 * PI / 180) {
			open[2] = false;
		}
	}
	else if (close[2]) {
		if (openAngle[1] <= 0 * PI / 180) {
			close[2] = false;
		}
	}

	drawWardrobe(room, furnitureColor);
	drawDesk(room, furnitureColor);
}