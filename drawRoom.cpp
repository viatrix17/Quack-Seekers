#include "config.h"
#include "myCube.h" // jak chcesz yztwac w wiekszej liczbie plikow tow rzuc dekalracje do myCube.cpp

extern ShaderProgram* spWood;
extern ShaderProgram* spMarble;

extern GLuint tex0;
extern GLuint tex1;



float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
int vertexCount = myCubeVertexCount;

void drawCubeWood(glm::mat4 cube, std::tuple<float, float, float> scale, std::tuple<float, float, float> color) {
	cube = glm::scale(cube, glm::vec3(std::get<0>(scale),std::get<1>(scale),std::get<2>(scale)));
	//2cmx2cmx2xcm -> 4mx3mx0.25m -> 400cmx300cmx25cm  
	glUniformMatrix4fv(spWood->u("M"), 1, false, glm::value_ptr(cube));
	glUniform4f(spWood->u("color"), std::get<0>(color), std::get<1>(color), std::get<2>(color), 1);

	glEnableVertexAttribArray(spWood->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(spWood->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(spWood->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
	glVertexAttribPointer(spWood->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska¿ tablicê z danymi dla atrybutu texCoord

	glUniform1i(spWood->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(spWood->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(spWood->a("color"));  //Wy³¹cz przesy³anie danych do atrybutu color
	glDisableVertexAttribArray(spWood->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0

	//glEnableVertexAttribArray(sp->a("color"));  //W³¹cz przesy³anie danych do atrybutu color
	//glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors); //Wska¿ tablicê z danymi dla atrybutu color
	//Models::cube.drawSolid();
}

//void drawCube(glm::mat4 cube, std::tuple<float, float, float> scale, std::tuple<float, float, float> color) {
//	cube = glm::scale(cube, glm::vec3(std::get<0>(scale), std::get<1>(scale), std::get<2>(scale)));
//	//2cmx2cmx2xcm -> 4mx3mx0.25m -> 400cmx300cmx25cm  
//	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(cube));
//	glUniform4f(spLambert->u("color"), std::get<0>(color), std::get<1>(color), std::get<2>(color), 1);
//	Models::cube.drawSolid();
//}

void drawWallWithWindow(glm::mat4 wall, std::tuple<float, float, float> beige) {

	glm::mat4 leftPart = wall;
	leftPart = glm::translate(leftPart, glm::vec3(200.0f, 0.0f, -140.0f));
	leftPart = glm::rotate(leftPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(leftPart, std::tuple <float, float, float> (60.0f, 125.0f, 5.0f), beige);

	glm::mat4 rightPart = wall;
	rightPart = glm::translate(rightPart, glm::vec3(200.0f, 0.0f, 140.0f));
	rightPart = glm::rotate(rightPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(rightPart, std::tuple <float, float, float>(60.0f, 125.0f, 5.0f), beige);


	glm::mat4 downPart = wall;
	downPart = glm::translate(downPart, glm::vec3(200.0f, -90.0f, 0.0f));
	downPart = glm::rotate(downPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(downPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f), beige);

	glm::mat4 upPart = wall;
	upPart = glm::translate(upPart, glm::vec3(200.0f, 90.0f, 0.0f));
	upPart = glm::rotate(upPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(upPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f), beige);
}

void drawRoom(glm::mat4 room) {

	std::tuple<float, float, float> black(0.0f, 0.0f, 0.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	// drawing the non-window walls

	//scaling values
	std::tuple<float, float, float> wallScale(200.0f, 125.0f, 5.0f);
	std::tuple<float, float, float> wallColor(0.9f, 0.84f, 0.78f); //beige color for the walls


	glm::mat4 frontWall = room;
	frontWall = glm::translate(frontWall, glm::vec3(0.0f,0.0f,200.0f));  
	drawCubeWood(frontWall, wallScale, wallColor);
	
	glm::mat4 backWall = room; //with the door??
	backWall = glm::translate(backWall, glm::vec3(0.0f, 0.0f, -200.0f));
	drawCubeWood(backWall, wallScale, wallColor);


	glm::mat4 rightWall = room;
	rightWall = glm::translate(rightWall, glm::vec3(-200.0f+10.0f, 0.0f, 0.0f));
	rightWall = glm::rotate(rightWall, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(rightWall, wallScale, wallColor);

	glm::mat4 leftWall = room;
	drawWallWithWindow(leftWall, wallColor);

	// drawing the ceiling and the floor

	std::tuple<float, float, float> floorAndCeilingScale(200.0f, 200.0f, 5.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	glm::mat4 floor = room;
	floor = glm::translate(floor, glm::vec3(0.0f, -150.0f+20.0f, 0.0f));
	floor = glm::rotate(floor, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCubeWood(floor, floorAndCeilingScale, black);
	
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