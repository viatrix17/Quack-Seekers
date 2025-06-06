/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA

should I delete it? xDD
*/

#include "config.h"

#include "drawRoom.h"
#include "drawFurniture.h"
#include "boxLock.h"


GLuint tex0;
GLuint tex1;
GLuint tex2;
GLuint tex3;
GLuint texBoxLock;

ShaderProgram* spWood; //woodish??
ShaderProgram* spMarble;
ShaderProgram* spMetal;

float cameraSpeed = 25.0f;
float rotateSpeed = 0.25f;
bool forward = false, back = false, goRight = false, goLeft = false; //movement

glm::vec3 positionOffset;
glm::vec3 viewOffset;
float cameraAngle = 0;

float lastFrameTime = 0.0f; // time of the last frame
float deltaTime = 0.0f; // time difference between frames

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float mouseSensitivity = 0.1f;

float yaw = -90.0f;  // initial yaw (direction)
float pitch = 0.0f;  // initial pitch (up/down)

bool open[5]; //0 - wardrobe,  1- cabinet, 2 - box1, 3 - box2, 4 - drawer,
bool close[5];
int openCount[5]; //0 - wardrobe, 1 - cabinet, 2 - box1, 3 - box3
float openAngle[5];
glm::vec3 drawerOffset;

float openSpeed = 1.0f;
float drawSpeed = 15.0f;

bool triggered[2]; // 0 - drawer and cabinet, 1 - boxes

bool isCameraLookingAtBox(glm::vec3 cameraPos, glm::vec3 viewDirection, glm::vec3 boxMin, glm::vec3 boxMax, float maxDistance, float minViewAngleDegress, float maxViewAngleDegrees) {
	// First, find the closest point on the box to the camera
	glm::vec3 closestPoint = glm::clamp(cameraPos, boxMin, boxMax);
	glm::vec3 toClosestPoint = closestPoint - cameraPos;
	float distance = glm::length(toClosestPoint);
	std::cout << distance << " distance\n";
	if (distance > maxDistance)
		return false;

	glm::vec3 toTargetNormalized = glm::normalize(toClosestPoint);
	float angle = glm::degrees(acos(glm::dot(glm::normalize(viewDirection), toTargetNormalized)));
	std::cout << angle << " angle\n";
	return (angle < maxViewAngleDegrees && angle > minViewAngleDegress);
}

// keys handling
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W) {
			forward = true;
		}
		if (key == GLFW_KEY_S) {
			back = true;
		}
		if (key == GLFW_KEY_D) {
			goRight = true;
		}
		if (key == GLFW_KEY_A) {
			goLeft = true;
		}
		if (key == GLFW_KEY_ESCAPE) {
			glfwDestroyWindow(window);
			glfwTerminate(); // free the resources taken by GLFW
			exit(EXIT_SUCCESS);
		}
		if (key == GLFW_KEY_SPACE) {
			/*if (!open[2]) {
				close[2] = false;
				open[2] = true;
			}
			else {
				open[2] = false;
				close[2] = true;
			}*/

			std::cout << positionOffset.x << " " << positionOffset.y << " " << positionOffset.z << "\n";

			//wardrobe animation trigger
			if (openCount[0] == 0) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, wardrobePos - wardrobeSize, wardrobePos + wardrobeSize, 120.0f, 0.0f, 70.0f)
					&& positionOffset.x < -30.0f) {
					close[0] = false;
					open[0] = true;
					openCount[0]++;

				}
			}
			else if (openCount[0] == 1) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, wardrobePos - wardrobeSize, wardrobePos + wardrobeSize, 180.0f, 0.0f, 90.0f)
					&& positionOffset.x < -30.0f) {
					open[0] = false;
					close[0] = true;
					openCount[0]--;
				}
			}
			std::cout << "drawer\n";
			//drawer animation trigger 
			if (openCount[4] == 0) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos) - drawerSize, (deskPos + drawerPos) + drawerSize, 100.0f, 0.0f, 20.0f)) {
					close[4] = false;
					open[4] = true;
					openCount[4]++;
					triggered[0] = true;
				}
			}
			else if (openCount[4] == 1) {
				if ((isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos) - drawerSize, (deskPos + drawerPos) + drawerSize, 140.0f, 0.0f, 22.0f)
					&& positionOffset.x > 30.0f && positionOffset.x < 90.0f)
					|| (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos) - drawerSize, (deskPos + drawerPos) + drawerSize, 160.0f, 0.0f, 40.0f)
						&& (positionOffset.x >= 90.0f && positionOffset.x < 140.0f || positionOffset.x > -10.0f && positionOffset.x <= 30.0f))) {
					open[4] = false;
					close[4] = true;
					openCount[4]--;
					triggered[0] = true;
				}
			}
			std::cout << "cabinet\n";
			//cabinet animation trigger
			if (openCount[1] == 0 && !triggered[0]) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos + cabinetPos) - cabinetSize, (deskPos + drawerPos + cabinetPos) + cabinetSize, 120.0f, 7.0f, 30.0f)) {
					close[1] = false;
					open[1] = true;
					openCount[1]++;
				}
			}
			else if (openCount[1] == 1 && !triggered[0]) {
				if ((isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos + cabinetPos) - cabinetSize, (deskPos + drawerPos + cabinetPos) + cabinetSize, 180.0f, 7.0f, 20.0f)
					|| isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos + cabinetPos) - cabinetSize, (deskPos + drawerPos + cabinetPos) + cabinetSize, 60.0f, 7.0f, 70.0f)
					&& positionOffset.x > 30.0f && positionOffset.x < 900.0f)
					|| (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos + cabinetPos) - cabinetSize, (deskPos + drawerPos + cabinetPos) + cabinetSize, 180.0f, 5.0f, 30.0f)
						&& (positionOffset.x >= 90.0f && positionOffset.x < 140.0f || positionOffset.x > -10.0f && positionOffset.x <= 30.0f))) {
					open[1] = false;
					close[1] = true;
					openCount[1]--;
				}
			}

			//box1 animation trigger
			if (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + boxPos) - boxSize, (deskPos + boxPos) + boxSize, 100.0f, 0.0f, 10.0f)) {
				if (openCount[2] == 0) {
					close[2] = false;
					open[2] = true;
					openCount[2]++;
					triggered[1] = true;
				}
				else if (openCount[2] == 1) {
					open[2] = false;
					close[2] = true;
					openCount[2]--;
					triggered[1] = true;
				}
			}

			//box2 animation trigger
			if (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + glm::vec3(boxPos.x * 2 + 1 * 25.0f, boxPos.y, boxPos.z)) - boxSize, 
				(deskPos + glm::vec3(boxPos.x * 2 + 1 * 25.0f, boxPos.y, boxPos.z)) + boxSize, 100.0f, 0.0f, 10.0f)) {
				if (openCount[3] == 0 && !triggered[1]) {
					close[3] = false;
					open[3] = true;
					openCount[3]++;
				}
				else if (openCount[3] == 1 && !triggered[1]) {
					open[3] = false;
					close[3] = true;
					openCount[3]--;
				}
			}
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) {
			forward = false;
		}
		if (key == GLFW_KEY_S) {
			back = false;
		}
		if (key == GLFW_KEY_D) {
			goRight = false;
		}
		if (key == GLFW_KEY_A) {
			goLeft = false;
		}
	}
	for (int i = 0; i < 2; i++) {
		triggered[i] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// calculate offset between current mouse position and last position
	float offsetX = xpos - lastX;
	float offsetY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	// Update the camera angles (yaw and pitch)
	yaw += offsetX * mouseSensitivity;
	pitch += offsetY * mouseSensitivity;

	/*if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;*/

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	viewOffset = glm::normalize(front);

}

// error handling
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
	unsigned width, height; //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return tex;
}

// initialization of the program
void initOpenGLProgram(GLFWwindow* window) {
    
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.58f, 0.88f, 0.92f, 0); //light blue/green for the sky/background
	positionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
	viewOffset = glm::vec3(0.0f, 0.0f, 100.0f);

	for (int i = 0; i < 5; i++) {
		open[i] = false;
		close[i] = false;
		openCount[i] = 0;
		openAngle[i] = 0.0f;
	}
	drawerOffset = glm::vec3(0.0f, 0.0f, 0.0f);

	tex0 = readTexture("textures/wood_small.png");
	
	tex1 = readTexture("textures/marble2.png");
	tex2 = readTexture("textures/marble2_specular.png");
	texBoxLock = readTexture("textures/metal.png");

	spWood = new ShaderProgram("v_wood.glsl", NULL, "f_wood.glsl");
	spMarble = new ShaderProgram("v_marble.glsl", NULL, "f_marble.glsl");
	spMetal = new ShaderProgram("v_metal.glsl", NULL, "f_metal.glsl");

	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
}


// freeing the resources
void freeOpenGLProgram(GLFWwindow* window) {
  

	glDeleteTextures(1, &tex0);
	glDeleteTextures(1, &tex1);
	glDeleteTextures(1, &tex2);
	glDeleteTextures(1, &texBoxLock);

	delete spWood, spMarble;
}

void cameraMovement() { //dać ograniczenia na movement, bo nam schodzi pod pokój XDDD
	if (forward) {
		positionOffset += cameraSpeed * deltaTime * viewOffset;
	}
	if (back) {
		positionOffset -= cameraSpeed * deltaTime * viewOffset;
	}

	// left/right movement
	if (goLeft) {
		positionOffset -= glm::normalize(glm::cross(viewOffset, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed * deltaTime;
	}
	if (goRight) {
		positionOffset += glm::normalize(glm::cross(viewOffset, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed * deltaTime;
	}
	
}

// drawing a scene
void drawScene(GLFWwindow* window, glm::vec3 positionOffset, glm::vec3 viewOffset) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 2.0f, 1.0f, 1000.0f);
	glm::mat4 V = glm::lookAt(positionOffset, positionOffset + viewOffset, glm::vec3(0.0f, 1.0f, 0.0f));

	//spMetal->use();
	spWood->use();
	glUniformMatrix4fv(spWood->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spWood->u("V"), 1, false, glm::value_ptr(V));
	glm::vec4 lightPosWorld = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // ustalona pozycja światła w świecie
	glm::vec4 lightPosEye = V * lightPosWorld; // przekształcenie do przestrzeni oka
	glUniform4fv(spWood->u("lp"), 1, glm::value_ptr(lightPosEye));


	//drawBackyard(); idk where to put this tbh xdd
	glm::mat4 room = glm::mat4(1.0f);

	drawRoom(room);
	drawFurniture(room);
	
	
	glfwSwapBuffers(window);
}

int main(void)
{
	GLFWwindow* window; 

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) { // GLFW initialization
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);  

	if (!window) 
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); 
	glfwSwapInterval(1); 

	if (glewInit() != GLEW_OK) { // GLEW initialization
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);
	
	glfwSetTime(0);

	float currentFrameTime;

	// main game loop	
	while (!glfwWindowShouldClose(window))
	{	
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		
		for (int i = 0; i < 4; i++) {
			if (open[i]) {
				openAngle[i] += openSpeed * deltaTime;
			}
			else if (close[i]) {
				openAngle[i] -= openSpeed * deltaTime;
			}
		}

		if (open[4]) {
			drawerOffset.z -= drawSpeed * deltaTime; 
		}
		else if (close[4]) {
			drawerOffset.z += drawSpeed * deltaTime;
		}
		
		cameraMovement();
		drawScene(window, positionOffset, viewOffset);
		glfwPollEvents(); 
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate(); // free the resources taken by GLFW
	exit(EXIT_SUCCESS);
}
