#include "config.h"
#include "myCube.h" // jak chcesz yztwac w wiekszej liczbie plikow tow rzuc dekalracje do myCube.cpp

extern ShaderProgram* spWood;
extern ShaderProgram* spMarble;
extern ShaderProgram* spFloor;

extern GLuint tex[4];

extern glm::vec3 positionOffset;

float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
int vertexCount = myCubeVertexCount;

void drawCubeWood(glm::mat4 cube, std::tuple<float, float, float> scale) {
	cube = glm::scale(cube, glm::vec3(std::get<0>(scale),std::get<1>(scale),std::get<2>(scale)));
	glUniformMatrix4fv(spWood->u("M"), 1, false, glm::value_ptr(cube));

	glUniform3fv(spWood->u("cameraWorldPos"), 1, glm::value_ptr(positionOffset));

	glEnableVertexAttribArray(spWood->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(spWood->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(spWood->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
	glVertexAttribPointer(spWood->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wska¿ tablicê z danymi dla atrybutu normal

	glEnableVertexAttribArray(spWood->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
	glVertexAttribPointer(spWood->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska¿ tablicê z danymi dla atrybutu texCoord

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	glUniform1i(spWood->u("textureMap0"), 0);


	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(spWood->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(spWood->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
	glDisableVertexAttribArray(spWood->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
}

void drawCubeMarble(glm::mat4 cube, std::tuple<float, float, float> scale) {
	cube = glm::scale(cube, glm::vec3(std::get<0>(scale), std::get<1>(scale), std::get<2>(scale)));
	glUniformMatrix4fv(spMarble->u("M"), 1, false, glm::value_ptr(cube));

	glUniform3fv(spMarble->u("cameraWorldPos"), 1, glm::value_ptr(positionOffset));


	glEnableVertexAttribArray(spMarble->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(spMarble->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(spMarble->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
	glVertexAttribPointer(spMarble->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wska¿ tablicê z danymi dla atrybutu normal


	glEnableVertexAttribArray(spMarble->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
	glVertexAttribPointer(spMarble->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska¿ tablicê z danymi dla atrybutu texCoord

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glUniform1i(spMarble->u("textureMap0"), 0);
	/*glUniform1i(spMarble->u("textureMap1"), 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, tex2);*/

	

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(spMarble->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(spMarble->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
	glDisableVertexAttribArray(spMarble->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal

}

void drawCubeFloor(glm::mat4 cube, std::tuple<float, float, float> scale) {
	cube = glm::scale(cube, glm::vec3(std::get<0>(scale), std::get<1>(scale), std::get<2>(scale)));
	glUniformMatrix4fv(spFloor->u("M"), 1, false, glm::value_ptr(cube));

	glUniform3fv(spFloor->u("cameraWorldPos"), 1, glm::value_ptr(positionOffset));

	glEnableVertexAttribArray(spFloor->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(spFloor->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(spFloor->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
	glVertexAttribPointer(spFloor->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wska¿ tablicê z danymi dla atrybutu normal

	glEnableVertexAttribArray(spFloor->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
	glVertexAttribPointer(spFloor->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska¿ tablicê z danymi dla atrybutu texCoord


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glUniform1i(spFloor->u("textureMap0"), 0);


	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(spFloor->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(spFloor->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
	glDisableVertexAttribArray(spFloor->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
}


void drawWallWithWindow(glm::mat4 wall, std::tuple<float, float, float> ) {

	glm::mat4 leftPart = wall;
	leftPart = glm::translate(leftPart, glm::vec3(200.0f, 0.0f, -140.0f));
	leftPart = glm::rotate(leftPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(leftPart, std::tuple <float, float, float> (60.0f, 125.0f, 5.0f));

	glm::mat4 rightPart = wall;
	rightPart = glm::translate(rightPart, glm::vec3(200.0f, 0.0f, 140.0f));
	rightPart = glm::rotate(rightPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(rightPart, std::tuple <float, float, float>(60.0f, 125.0f, 5.0f));


	glm::mat4 downPart = wall;
	downPart = glm::translate(downPart, glm::vec3(200.0f, -90.0f, 0.0f));
	downPart = glm::rotate(downPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(downPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f));

	glm::mat4 upPart = wall;
	upPart = glm::translate(upPart, glm::vec3(200.0f, 90.0f, 0.0f));
	upPart = glm::rotate(upPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(upPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f));
}

void drawRoom(glm::mat4 room, glm::mat4 P, glm::mat4 V) {

	std::tuple<float, float, float> black(0.0f, 0.0f, 0.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	// drawing the non-window walls

	//scaling values
	std::tuple<float, float, float> wallScale(200.0f, 125.0f, 5.0f);
	std::tuple<float, float, float> wallColor(0.9f, 0.84f, 0.78f); // color for the walls


	glm::mat4 frontWall = room;
	frontWall = glm::translate(frontWall, glm::vec3(0.0f,0.0f,200.0f));  
	drawCubeWood(frontWall, wallScale);
	
	glm::mat4 backWall = room; //with the door??
	backWall = glm::translate(backWall, glm::vec3(0.0f, 0.0f, -200.0f));
	drawCubeWood(backWall, wallScale);


	glm::mat4 rightWall = room;
	rightWall = glm::translate(rightWall, glm::vec3(-200.0f+10.0f, 0.0f, 0.0f));
	rightWall = glm::rotate(rightWall, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	drawCubeWood(rightWall, wallScale);

	glm::mat4 leftWall = room;
	drawWallWithWindow(leftWall, wallColor);

	// drawing the ceiling and the floor

	std::tuple<float, float, float> floorAndCeilingScale(200.0f, 200.0f, 5.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	glm::mat4 floor = room;
	floor = glm::translate(floor, glm::vec3(0.0f, -150.0f+20.0f, 0.0f));
	floor = glm::rotate(floor, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCubeWood(floor, floorAndCeilingScale);
	
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