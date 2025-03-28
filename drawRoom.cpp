#include "config.h"

//void drawWall(glm::mat4 wall, float x, float y, float z) {
//	wall = glm::scale(wall, glm::vec3(x, y, z)); 
//	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(wall));
//	glUniform4f(spLambert->u("color"), 0.9f, 0.84f, 0.78f, 1); // beige color for the walls
//	Models::cube.drawSolid();
//
//}

void drawRoom(glm::vec3 cameraOffset, glm::vec3 viewOffset, float roomAngle) {

	//std::cout << "drawing a room!\n";

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 2.0f, 1.0f, 500.0f);
	glm::mat4 V;
	V = glm::lookAt(cameraOffset, viewOffset, glm::vec3(0.0f, 1.0f, 0.0f));
	/*if (right) {
		V = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (left) {
		V = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}*/
	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

	// drawing the non-window walls
	glm::mat4 room = glm::mat4(1.0f);
	room = glm::rotate(room, roomAngle, glm::vec3(0.0f,1.0f,0.0f));

	
	glm::mat4 frontWall = room;
	frontWall = glm::translate(frontWall, glm::vec3(0.0f,0.0f,200.0f));  
	frontWall = glm::scale(frontWall, glm::vec3(200.0f, 125.0f, 5.0f)); 
	//2cmx2cmx2xcm -> 4mx3mx0.25m -> 400cmx300cmx25cm  
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(frontWall));
	glUniform4f(spLambert->u("color"), 0.9f, 0.84f, 0.78f, 1); 
	Models::cube.drawSolid();

	//drawWall(frontWall);
	
	glm::mat4 backWall = room; //with the door??
	backWall = glm::translate(backWall, glm::vec3(0.0f, 0.0f, -200.0f));
	backWall = glm::scale(backWall, glm::vec3(200.0f, 125.0f, 5.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(backWall));
	glUniform4f(spLambert->u("color"), 0.5f, 0.3f, 0.8f, 1); 
	Models::cube.drawSolid();
	//drawWall(backWall);

	glm::mat4 rightWall = room;
	rightWall = glm::translate(rightWall, glm::vec3(-200.0f+10.0f, 0.0f, 0.0f));
	rightWall = glm::rotate(rightWall, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	rightWall = glm::scale(rightWall, glm::vec3(200.0f, 125.0f, 5.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(rightWall));
	glUniform4f(spLambert->u("color"), 0.1f, 0.6f, 0.5f, 1); 
	Models::cube.drawSolid();
	//drawWall(rightWall);

	// drawing the ceiling and the floor

	glm::mat4 floor = room;
	floor = glm::translate(floor, glm::vec3(0.0f, -150.0f+20.0f, 0.0f));
	floor = glm::rotate(floor, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	floor = glm::scale(floor, glm::vec3(200.0f, 200.0f, 5.0f)); //troche nie dosiega do konca jak sie zrobi z zewnatrz
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(floor));
	glUniform4f(spLambert->u("color"), 0.0f, 0.0f, 0.0f, 1);
	Models::cube.drawSolid();
	
	// dodac na koncu, jak sie zrobi oswietlenie w srodku
	/*glm::mat4 ceiling = room;
	ceiling = glm::translate(ceiling, glm::vec3(0.0f, -150.0f, 0.0f));
	ceiling = glm::rotate(ceiling, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	ceiling = glm::scale(ceiling, glm::vec3(200.0f, 200.0f, 5.0f)); 
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(ceiling));
	glUniform4f(spLambert->u("color"), 0.0f, 0.0f, 0.0f, 1);
	Models::cube.drawSolid();*/
}