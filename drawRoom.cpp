#include "config.h"

void drawCube(glm::mat4 cube, std::tuple<float, float, float> scale, std::tuple<float, float, float> color) {
	cube = glm::scale(cube, glm::vec3(std::get<0>(scale),std::get<1>(scale),std::get<2>(scale)));
	//2cmx2cmx2xcm -> 4mx3mx0.25m -> 400cmx300cmx25cm  
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(cube));
	glUniform4f(spLambert->u("color"), std::get<0>(color), std::get<1>(color), std::get<2>(color), 1); 
	Models::cube.drawSolid();
}

void drawWallWithWindow(glm::mat4 wall, std::tuple<float, float, float> beige) {

	glm::mat4 leftPart = wall;
	leftPart = glm::translate(leftPart, glm::vec3(200.0f, 0.0f, -140.0f));
	leftPart = glm::rotate(leftPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(leftPart, std::tuple <float, float, float> (60.0f, 125.0f, 5.0f), beige);

	glm::mat4 rightPart = wall;
	rightPart = glm::translate(rightPart, glm::vec3(200.0f, 0.0f, 140.0f));
	rightPart = glm::rotate(rightPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(rightPart, std::tuple <float, float, float>(60.0f, 125.0f, 5.0f), beige);


	glm::mat4 downPart = wall;
	downPart = glm::translate(downPart, glm::vec3(200.0f, -90.0f, 0.0f));
	downPart = glm::rotate(downPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(downPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f), beige);

	glm::mat4 upPart = wall;
	upPart = glm::translate(upPart, glm::vec3(200.0f, 90.0f, 0.0f));
	upPart = glm::rotate(upPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(upPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f), beige);
}

void drawRoom(glm::vec3 cameraOffset, glm::vec3 viewOffset) {

	std::tuple<float, float, float> black(0.0f, 0.0f, 0.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	// drawing the non-window walls
	glm::mat4 room = glm::mat4(1.0f);

	//scaling values
	std::tuple<float, float, float> wallScale(200.0f, 125.0f, 5.0f);
	std::tuple<float, float, float> wallColor(0.9f, 0.84f, 0.78f); //beige color for the walls

	
	glm::mat4 frontWall = room;
	frontWall = glm::translate(frontWall, glm::vec3(0.0f,0.0f,200.0f));  
	drawCube(frontWall, wallScale, wallColor);
	
	glm::mat4 backWall = room; //with the door??
	backWall = glm::translate(backWall, glm::vec3(0.0f, 0.0f, -200.0f));
	drawCube(backWall, wallScale, wallColor);


	glm::mat4 rightWall = room;
	rightWall = glm::translate(rightWall, glm::vec3(-200.0f+10.0f, 0.0f, 0.0f));
	rightWall = glm::rotate(rightWall, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCube(rightWall, wallScale, wallColor);

	glm::mat4 leftWall = room;
	drawWallWithWindow(leftWall, wallColor);

	// drawing the ceiling and the floor

	std::tuple<float, float, float> floorAndCeilingScale(200.0f, 200.0f, 5.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	glm::mat4 floor = room;
	floor = glm::translate(floor, glm::vec3(0.0f, -150.0f+20.0f, 0.0f));
	floor = glm::rotate(floor, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCube(floor, floorAndCeilingScale, black);
	
	// dodac na koncu, jak sie zrobi oswietlenie w srodku
	/*glm::mat4 ceiling = room;
	ceiling = glm::translate(ceiling, glm::vec3(0.0f, -150.0f, 0.0f));
	ceiling = glm::rotate(ceiling, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCube(rightWall, wallScale, wallColor);

	ceiling = glm::scale(ceiling, glm::vec3(200.0f, 200.0f, 5.0f)); 
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(ceiling));
	glUniform4f(spLambert->u("color"), 0.0f, 0.0f, 0.0f, 1);
	Models::cube.drawSolid();*/
}