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

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	viewOffset = glm::normalize(front);

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
	glClearColor(0.58f, 0.88f, 0.92f, 0); //light blue/green for the sky/background
	positionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
	viewOffset = glm::vec3(0.0f, 0.0f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
}


// freeing the resources
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
}

void cameraMovement() { 

	float currentFrameTime = glfwGetTime();

	// calculate the time difference between this and the last frame
	deltaTime = currentFrameTime - lastFrameTime;

	// update the time for the next frame
	lastFrameTime = currentFrameTime;

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
	glm::mat4 V;
	V = glm::lookAt(positionOffset, positionOffset + viewOffset, glm::vec3(0.0f, 1.0f, 0.0f));

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));


	//drawBackyard(); idk where to put this tbh xdd
	
	drawRoom(positionOffset, viewOffset);
	//drawFurniture();

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

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);  //uwaga wszystkie wbudowane modele trzeba przeskalowac w wymiarze x /2 

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

	// main game loop	
	while (!glfwWindowShouldClose(window)) 
	{	
		cameraMovement();
		drawScene(window, positionOffset, viewOffset);
		glfwPollEvents(); 
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate(); // free the resources taken by GLFW
	exit(EXIT_SUCCESS);
}
