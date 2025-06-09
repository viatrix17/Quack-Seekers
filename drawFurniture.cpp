#include "config.h"
#include "drawRoom.h"
#include "boxLock.h"
#include "flower.h"
#include "lamp.h"
#include "hinge.h"
#include "key.h"
#include "handle.h"
#include "safe.h"
#include "duck.h"
#include "mattress.h"
#include "pillow.h"

extern bool open[10];
extern bool close[10];
extern float openAngle[10];
extern glm::vec3 drawerOffset;

extern ShaderProgram* spFur;
extern ShaderProgram* spMetal;

void drawWardrobe(glm::mat4 room, std::tuple<float, float, float> color) {

	glm::mat4 wardrobe = room;
	wardrobe = glm::translate(wardrobe, wardrobePos);
	
	glm::mat4 back = wardrobe;
	back = glm::translate(back, glm::vec3(0.0f, 0.0f, 25.0f));
	drawCubeWood(back, std::tuple<float, float, float> (68.0f, 100.0f, 1.0f));
	
	// top and 
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 board = wardrobe;
		board = glm::translate(board, glm::vec3(0.0f, 101.0f*i, 1.0f));
		board = glm::rotate(board, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCubeWood(board, std::tuple<float, float, float>(70.0f, 25.0f, 1.0f));
	}

	// sides
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 side = wardrobe;
		side = glm::translate(side, glm::vec3(69.0f*i, 0.0f, 1.0f));
		side = glm::rotate(side, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
		drawCubeWood(side, std::tuple<float, float, float>(25.0f, 100.0f, 1.0f));
	}
	
	// front aka door  maja sie obracac 
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 doorWing = wardrobe;
		doorWing = glm::translate(doorWing, glm::vec3(34.5f*i, 0.0f, -25.0f));
		// animation
		doorWing = glm::translate(doorWing, glm::vec3(34.5f*i, 0.0f, 0.0f));
		doorWing = glm::rotate(doorWing, openAngle[0]*i, glm::vec3(0.0f, -1.0f, 0.0f));
		doorWing = glm::translate(doorWing, glm::vec3(-34.5f*i, 0.0f, 0.0f));
		drawCubeWood(doorWing, std::tuple<float, float, float>(34.0f, 100.0f, 1.0f));
	}
	
	//shelves
	for (float i = 1; i < 5; i++) {
		glm::mat4 shelf = wardrobe;
		shelf = glm::translate(shelf, glm::vec3(0.0f, -101.0f+38.0f*i, 1.0f));
		shelf = glm::rotate(shelf, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCubeWood(shelf, std::tuple<float, float, float>(70.0f, 25.0f, 1.0f));
	}
}

void drawBoxes(glm::mat4 desk) {

	for (int i = 0; i < 2; i++) {
		glm::mat4 lowerPart = desk;
		lowerPart = glm::translate(lowerPart, glm::vec3(boxPos.x*(1+i)+i*25.0f, boxPos.y, boxPos.z));
		
		glm::mat4 upperPart = desk;
		upperPart = glm::translate(upperPart, glm::vec3(boxPos.x * (1 + i) + i * 25.0f, boxPos.y+7.05f, boxPos.z));
		//animation
		upperPart = glm::translate(upperPart, glm::vec3(0.0f, -1.0f, boxSize.z+0.5f));
		upperPart = glm::rotate(upperPart, openAngle[2+i], glm::vec3(1.0f, 0.0f, 0.0f));
		upperPart = glm::translate(upperPart, glm::vec3(0.0f, 1.0f, -(boxSize.z+0.5f)));
		
		for (int i = -1; i <= 1; i+=2) {
			glm::mat4 lowerVer = lowerPart;
			lowerVer = glm::translate(lowerVer, glm::vec3(0.0f, 0.0f, i * boxSize.z));
			drawCubeMarble(lowerVer, std::tuple<float, float, float>(boxSize.x, boxSize.y, 0.25f));
		
			glm::mat4 lowerSide = lowerPart;
			lowerSide = glm::translate(lowerSide, glm::vec3((boxSize.x-0.25f)*i, 0.0f, 0.0f));
			lowerSide = glm::rotate(lowerSide, 90*PI/180, glm::vec3(0.0f, 1.0f, 0.0f));
			drawCubeMarble(lowerSide, std::tuple<float, float, float>(boxSize.z-0.25f, boxSize.y, 0.25f));

			glm::mat4 upperVer = upperPart;
			upperVer = glm::translate(upperVer, glm::vec3(0.0f, 0.0f, i * boxSize.z));
			drawCubeMarble(upperVer, std::tuple<float, float, float>(boxSize.x, 2.0f, 0.25f));

			glm::mat4 upperSide = upperPart;
			upperSide = glm::translate(upperSide, glm::vec3((boxSize.x - 0.25f) * i, 0.0f, 0.0f));
			upperSide = glm::rotate(upperSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
			drawCubeMarble(upperSide, std::tuple<float, float, float>(boxSize.z - 0.25f, 2.0f, 0.25f));

		}

		glm::mat4 bottom = lowerPart;
		bottom = glm::translate(bottom, glm::vec3(0.0f, -5.0f, 0.0f));
		bottom = glm::rotate(bottom, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCubeMarble(bottom, std::tuple<float, float, float>(boxSize.x, boxSize.z+0.25, 0.25f));

		glm::mat4 top = upperPart;
		top = glm::translate(top, glm::vec3(0.0f, 2.0f, 0.0f));
		top = glm::rotate(top, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCubeMarble(top, std::tuple<float, float, float>(boxSize.x, boxSize.z+0.25, 0.25f));
	}
}

void drawDesk(glm::mat4 room, std::tuple<float, float, float> color) {

	glm::mat4 desk = room;
	desk = glm::translate(desk, deskPos);

	glm::mat4 board = desk;
	board = glm::rotate(desk, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCubeWood(board, std::tuple<float, float, float>(72.0f, 27.0f, 1.0f));

	//140cmx50cmx75cm

	//sides
	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 deskSide = desk;
		deskSide = glm::translate(deskSide, glm::vec3(69.0f * i, -38.5f, 0.0f));
		deskSide = glm::rotate(deskSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
		drawCubeWood(deskSide, std::tuple<float, float, float>(25.0f, 37.5f, 1.0f));
	}

	//the drawer
	glm::mat4 drawer = desk;
	drawer = glm::translate(drawer, drawerPos + drawerOffset);

	for (float i = -1; i <= 1; i += 2) {
		glm::mat4 drawerSide = drawer;
		drawerSide = glm::translate(drawerSide, glm::vec3(17.0f*i, 0.0f, -1.0f));
		drawerSide = glm::rotate(drawerSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
		drawCubeWood(drawerSide, std::tuple<float, float, float>(20.0f, 10.0f, 1.0f));
		
	}
	
	glm::mat4 drawerFront = drawer;
	drawerFront = glm::translate(drawerFront, glm::vec3(0.0f, 0.0f, -22.0f));
	drawCubeWood(drawerFront, std::tuple<float, float, float>(21.0f, 12.0f, 1.0f));

	glm::mat4 drawerBack = drawer;
	drawerBack = glm::translate(drawerBack, glm::vec3(0.0f, 0.0f, 20.0f));
	drawCubeWood(drawerBack, std::tuple<float, float, float>(18.0f, 10.0f, 1.0f));
	
	glm::mat4 drawerBottom = drawer;
	drawerBottom = glm::translate(drawerBottom, glm::vec3(0.0f, -11.0f, 0.0f));
	drawerBottom = glm::rotate(drawerBottom, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCubeWood(drawerBottom, std::tuple<float, float, float>(18.0f, 21.0f, 1.0f));

	//the cabinet
	glm::mat4 cabinet = desk;
	cabinet = glm::translate(cabinet, drawerPos + cabinetPos);

	glm::mat4 cabinetSide = cabinet;
	cabinetSide = glm::translate(cabinetSide, glm::vec3(20.0f, 12.0f, 0.0f));
	cabinetSide = glm::rotate(cabinetSide, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(cabinetSide, std::tuple<float, float, float>(21.0f, 35.0f, 1.0f));
	
	glm::mat4 cabinetFront = cabinet;
	cabinetFront = glm::translate(cabinetFront, glm::vec3(0.0f, -1.0f, -22.0f));
	//animation
	cabinetFront = glm::translate(cabinetFront, glm::vec3(-21.0f, 0.0f, 0.0f));
	cabinetFront = glm::rotate(cabinetFront, openAngle[1], glm::vec3(0.0f, 1.0f, 0.0f));
	cabinetFront = glm::translate(cabinetFront, glm::vec3(21.f, 0.0f, 0.0f));
	drawCubeWood(cabinetFront, std::tuple<float, float, float>(21.0f, 23.0f, 1.0f));

	glm::mat4 cabinetBack = cabinet;
	cabinetBack = glm::translate(cabinetBack, glm::vec3(-0.2f, 12.0f, 22.0f));
	drawCubeWood(cabinetBack, std::tuple<float, float, float>(21.1f, 36.0f, 1.0f));

	for (float i = 0; i <= 1; i++) {
		glm::mat4 cabinetBottom = cabinet;
		cabinetBottom = glm::translate(cabinetBottom, glm::vec3(0.0f-2.0f*(1-i), 0.0f - i * (23.0f), 0.0f));
		cabinetBottom = glm::rotate(cabinetBottom, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
		drawCubeWood(cabinetBottom, std::tuple<float, float, float>(21.0f, 21.0f, 1.0f));
	}

	drawBoxes(desk);
}

void drawBed(glm::mat4 room, std::tuple<float, float, float> color) {
	
	glm::mat4 bed = room;
	bed = glm::translate(bed, bedPos);
	//drawCube(bed, std::tuple<float, float, float>(100.0f, 5.0f, 40.0f), color);

	// frames
	glm::mat4 frame = bed;
	frame = glm::translate(frame, glm::vec3(0.0f, 0.0f, 38.0f));
	drawCubeWood(frame, std::tuple<float, float, float>(bedSize.x, 5.0f, 1.0f));

	for (float i = 0; i < 2; i++) {
		glm::mat4 backFrame = bed;
		backFrame = glm::translate(backFrame, glm::vec3(0.0f, i*20.0f, -38.0f));
		drawCubeWood(backFrame, std::tuple<float, float, float>(bedSize.x, 5.0f, 1.0f));
	}
	for (float i = -1; i <= 1; i+=2) {
		for (float j = 0; j < 2; j++) {
			glm::mat4 frame = bed;
			frame = glm::translate(frame, glm::vec3(102.0f * i, j*20.0f, 0.0f));
			frame = glm::rotate(frame, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
			drawCubeWood(frame, std::tuple<float, float, float>(33.0f, 5.0f, 1.0f));
		}
	}

	// legs
	for (float i = -1; i <= 1; i+=2) {
		for (float j = -1; j <= 1; j+=2) {
			glm::mat4 leg = bed;
			leg = glm::translate(leg, glm::vec3(105.0f*i, 0.0f, 38.0f*j));
			drawCubeWood(leg, std::tuple<float, float, float>(5.0f, 30.0f, 5.0f));
		}
	}
}

void drawFurniture(glm::mat4 room) {

	std::tuple<float, float, float> furnitureColor(0.3f, 0.17f, 0.12f); //brown color for the furniture

	for (int i = 0; i < 4; i++) {
		if (open[i]) {
			if (openAngle[i] >= 90 * PI / 180) {
				open[i] = false;
			}
		}
		else if (close[i]) {
			if (openAngle[i] <= 0 * PI / 180) {
				close[i] = false;
			}
		}
	}
	
	if (open[4]) {
		if (drawerOffset.z <= -40.0f) {
			drawerOffset.z = -40.0f;
			open[4] = false;
		}
	}
	else if (close[4]) {
		if (drawerOffset.z >= 0.0f) {
			drawerOffset.z = 0.0f;
			close[4] = false;
		}
	}

	
	drawDesk(room, furnitureColor);
	drawBed(room, furnitureColor);
	drawWardrobe(room, furnitureColor);
}