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

bool open[10]; //0 - wardrobe
bool close[10];
int openCount[10];
float openAngle[10];
glm::vec3 drawerOffset;

float openSpeed = 1.0f;
float drawSpeed = 15.0f;

// mouse handling
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

bool isCameraLookingAtBox(glm::vec3 cameraPos, glm::vec3 viewDirection, glm::vec3 boxMin, glm::vec3 boxMax, float maxDistance, float maxViewAngleDegrees) {
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
	return angle < maxViewAngleDegrees;
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
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_SPACE) {
			std::cout << positionOffset.x << " " << positionOffset.y << " " << positionOffset.z << "\n";

			//wardrobe animation trigger
			if (openCount[0] == 0) {
				std::cout << (wardrobePos - wardrobeSize).x << "\n";
				if (isCameraLookingAtBox(positionOffset, viewOffset, wardrobePos-wardrobeSize, wardrobePos+wardrobeSize, 120.0f, 70.0f)
					&& positionOffset.x < -40.0f) {
					close[0] = false;
					open[0] = true;
					openCount[0]++;
				}
			}
			else if (openCount[0] == 1) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, wardrobePos - wardrobeSize, wardrobePos + wardrobeSize, 180.0f, 90.0f)
					&& positionOffset.x < -40.0f) {
					open[0] = false;
					close[0] = true;
					openCount[0]--;
				}
			}

			//drawer animation trigger 
			if (openCount[1] == 0) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos+drawerPos) - drawerSize, (deskPos+drawerPos) + drawerSize, 100.0f, 20.0f)) {
					close[1] = false;
					open[1] = true;
					openCount[1]++;
				}
			}
			else if (openCount[1] == 1) {
				if (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos+drawerPos) - drawerSize, (deskPos+drawerPos) + drawerSize, 140.0f, 20.0f)
					&& positionOffset.x > 30.0f && positionOffset.x < 90.0f
					|| (isCameraLookingAtBox(positionOffset, viewOffset, (deskPos + drawerPos) - drawerSize, (deskPos + drawerPos) + drawerSize, 140.0f, 40.0f) 
						&& (positionOffset.x >= 90.0f && positionOffset.x > 120.0f || positionOffset.x > -10.0f && positionOffset.x <= 30.0f))) {
					open[1] = false;
					close[1] = true;
					openCount[1]--;
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
}


// error handling
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


// initialization of the program
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.58f, 0.88f, 0.92f, 0); //light blue/green for the sky/background
	positionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
	viewOffset = glm::vec3(0.0f, 0.0f, 100.0f);

	for (int i = 0; i < 10; i++) {
		open[i] = false;
		close[i] = false;
		openCount[i] = 0;
		openAngle[i] = 0.0f;
	}
	drawerOffset = glm::vec3(0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
}


// freeing the resources
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
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

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

	//drawBackyard(); idk where to put this tbh xdd
	glm::mat4 room = glm::mat4(1.0f);
	drawRoom(room);
	drawFurniture(room);

	glfwSwapBuffers(window);
}

bool isCameraLookingAt(glm::vec3 cameraPos, glm::vec3 viewDir, glm::vec3 targetPos, float maxDistance, float maxViewAngleDegrees) {
	glm::vec3 toTarget = targetPos - cameraPos;
	float distance = glm::length(toTarget);

	if (distance > maxDistance)
		return false;

	glm::vec3 toTargetNormalized = glm::normalize(toTarget);
	float angle = glm::degrees(acos(glm::dot(glm::normalize(viewDir), toTargetNormalized)));

	return angle < maxViewAngleDegrees;
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
		
		if (open[0]) {
			openAngle[0] += openSpeed * deltaTime; // Zwiększanie kąta rotacji
		}
		else if (close[0]) {
			openAngle[0] -= openSpeed * deltaTime;
		}
		if (open[1]) {
			drawerOffset.z -= drawSpeed * deltaTime; // Zwiększanie kąta rotacji
		}
		else if (close[1]) {
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
