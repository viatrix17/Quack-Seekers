#include "config.h"

extern bool right;
extern bool left;

//void drawWall(glm::mat4 wall) {
//	wall = glm::scale(wall, glm::vec3(4.0f,6.0f,1.0f)); //4x3x0.25m //initially cube is 2 which means 1.0f = 2 and 4.0f = 8
//	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(wall));
//	glUniform4f(spLambert->u("color"), 0.9f, 0.84f, 0.78f, 1); // beige color for the walls
//	Models::cube.drawSolid();
//
//}
void drawRoom(glm::vec3 cameraOffset, glm::vec3 viewOffset) {

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



	
	glm::mat4 frontWall = room;
	frontWall = glm::translate(frontWall, glm::vec3(0.0f,0.0f,200.0f));  
	frontWall = glm::scale(frontWall, glm::vec3(200.0f, 125.0f, 12.5f)); 
	//2cmx2cmx2xcm -> 4mx3mx0.25m -> 400cmx300cmx25cm  
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(frontWall));
	glUniform4f(spLambert->u("color"), 0.9f, 0.84f, 0.78f, 1); // beige color for the walls
	Models::cube.drawSolid();

	//drawWall(frontWall);
	
	glm::mat4 backWall = room; //with the door??
	backWall = glm::translate(backWall, glm::vec3(0.0f, 0.0f, -200.0f));
	backWall = glm::scale(backWall, glm::vec3(200.0f, 125.0f, 12.5f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(backWall));
	glUniform4f(spLambert->u("color"), 0.5f, 0.3f, 0.8f, 1); 
	Models::cube.drawSolid();
	//drawWall(backWall);

	glm::mat4 rightWall = room;
	rightWall = glm::translate(rightWall, glm::vec3(-200.0f+12.5f, 0.0f, 0.0f));
	rightWall = glm::rotate(rightWall, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	rightWall = glm::scale(rightWall, glm::vec3(200.0f, 125.0f, 12.5f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(rightWall));
	glUniform4f(spLambert->u("color"), 0.1f, 0.6f, 0.5f, 1); 
	Models::cube.drawSolid();
	//drawWall(rightWall);
	

	// drawing the ceiling and the floor
}