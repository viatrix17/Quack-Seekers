#include "config.h"
#include "renderer.h"
#include "shaderprogram.h"


extern ShaderProgram* spWood;
extern ShaderProgram* spMarble;
extern ShaderProgram* spFloor;
extern ShaderProgram* spCeiling;

extern GLuint tex[6];

extern glm::vec4 lampLightPos;

extern glm::vec3 positionOffset;

extern float* vertices;
extern float* normals;
extern float* texCoords;
extern float* colors;
extern int vertexCount;

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


	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(spWood->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(spWood->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
	glDisableVertexAttribArray(spWood->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
}



void drawWallWithWindow(glm::mat4 wall, std::tuple<float, float, float>, Renderer renderer) {

	glm::mat4 leftPart = wall;
	leftPart = glm::translate(leftPart, glm::vec3(200.0f, 0.0f, -140.0f));
	leftPart = glm::rotate(leftPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	renderer.draw(leftPart, std::tuple <float, float, float>(60.0f, 125.0f, 5.0f), positionOffset);

	glm::mat4 rightPart = wall;
	rightPart = glm::translate(rightPart, glm::vec3(200.0f, 0.0f, 140.0f));
	rightPart = glm::rotate(rightPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	renderer.draw(rightPart, std::tuple <float, float, float>(60.0f, 125.0f, 5.0f), positionOffset);

	glm::mat4 downPart = wall;
	downPart = glm::translate(downPart, glm::vec3(200.0f, -90.0f, 0.0f));
	downPart = glm::rotate(downPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	renderer.draw(downPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f), positionOffset);

	glm::mat4 upPart = wall;
	upPart = glm::translate(upPart, glm::vec3(200.0f, 90.0f, 0.0f));
	upPart = glm::rotate(upPart, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	renderer.draw(upPart, std::tuple <float, float, float>(200.0f, 35.0f, 5.0f), positionOffset);
}

void drawRoom(glm::mat4 room, glm::mat4 P, glm::mat4 V) {


	std::tuple<float, float, float> black(0.0f, 0.0f, 0.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	// drawing the non-window walls

	// scaling values
	std::tuple<float, float, float> wallScale(200.0f, 125.0f, 5.0f);
	std::tuple<float, float, float> wallColor(0.9f, 0.84f, 0.78f); // color for the walls
	std::tuple<float, float, float> floorAndCeilingScale(200.0f, 200.0f, 5.0f); //troche nie dosiega do konca jak sie zrobi z zewnatrz

	// drawing the ceiling and the floor
	glm::mat4 floor = room;
	floor = glm::translate(floor, glm::vec3(0.0f, -150.0f + 20.0f, 0.0f));
	floor = glm::rotate(floor, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));

	spFloor->use();
	spFloor->setUniforms(P, V, lampLightPos);
	spFloor->bindTexture(GL_TEXTURE0, tex[3], "textureMap0");
	spFloor->bindTexture(GL_TEXTURE1, tex[4], "textureMap1");
	Renderer floorRenderer(spFloor, vertices, normals, texCoords, vertexCount);
	floorRenderer.draw(floor, floorAndCeilingScale, positionOffset);

	// innym shaderem sufit
	glm::mat4 ceiling = room;
	ceiling = glm::translate(ceiling, glm::vec3(0.0f, 150.0f, 0.0f));
	ceiling = glm::rotate(ceiling, 90 * PI / 180, glm::vec3(1.0f, 0.0f, 0.0f));

	spCeiling->use();
	
	spCeiling->bindTexture(GL_TEXTURE0, tex[5], "textureMap0");


	//tu na sciany teksture dac
	spWood->use();
	spWood->setUniforms(P, V, lampLightPos);
	
	spWood->bindTexture(GL_TEXTURE0, tex[0], "textureMap0");

	Renderer woodRenderer(spWood, vertices, normals, texCoords, vertexCount);

	glm::mat4 frontWall = room;
	frontWall = glm::translate(frontWall, glm::vec3(0.0f, 0.0f, 200.0f));
	woodRenderer.draw(frontWall, wallScale, positionOffset);

	glm::mat4 backWall = room; //with the door??
	backWall = glm::translate(backWall, glm::vec3(0.0f, 0.0f, -200.0f));
	woodRenderer.draw(backWall, wallScale, positionOffset);

	glm::mat4 rightWall = room;
	rightWall = glm::translate(rightWall, glm::vec3(-200.0f + 10.0f, 0.0f, 0.0f));
	rightWall = glm::rotate(rightWall, 90 * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	woodRenderer.draw(rightWall, wallScale, positionOffset);

	glm::mat4 leftWall = room;
	drawWallWithWindow(leftWall, wallColor, woodRenderer);
}