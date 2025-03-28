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

bool turnRight = false, turnLeft = false; //turning around

float cameraSpeed = 0.1f;
//int stepsCount = 0;
bool stop = true;
bool forward = false, back = false, goRight = false, goLeft = false; //movement
glm::vec3 positionOffset;
glm::vec3 viewOffset;


void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			std::cout << "look to the left\n";
			turnLeft = true;
		}
		if (key == GLFW_KEY_RIGHT) {
			std::cout << "look to the right\n";
			turnRight = true;
		}
		if (key == GLFW_KEY_W) {
			forward = true;
			std::cout << "go forward\t" << forward <<" \n";
			std::cout << positionOffset.z << "\n";
			positionOffset.z += cameraSpeed * glfwGetTime();
			viewOffset.z += cameraSpeed * glfwGetTime();
		}
		if (key == GLFW_KEY_S) {
			back = true;
			std::cout << "go back\n";
			std::cout << positionOffset.z << "\n";
			positionOffset.z -= cameraSpeed * glfwGetTime();
			viewOffset.z -= cameraSpeed * glfwGetTime();
		
		}
		if (key == GLFW_KEY_D) {
			goRight = true;
			std::cout << "go right\n";
			positionOffset.x -= cameraSpeed * glfwGetTime();
			viewOffset.x -= cameraSpeed * glfwGetTime();
		}
		if (key == GLFW_KEY_A) {
			goLeft = true;
			std::cout << "go left\n";
			positionOffset.x += cameraSpeed * glfwGetTime();
			viewOffset.x += cameraSpeed * glfwGetTime();
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) {
			std::cout << "look to the left\n";
			turnLeft = false;
		}
		if (key == GLFW_KEY_RIGHT) {
			std::cout << "look to the right\n";
			turnRight = false;
		}
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
}


// freeing the resources
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
}



// drawing a scene
void drawScene(GLFWwindow* window, glm::vec3 positionOffset, glm::vec3 viewOffset) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// camera movement - to add

	/*glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);
	glm::mat4 V = V = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

	//drawBackyard(); idk where to put this tbh xdd
	/*if (!stop) {
		
	}*/
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

	window = glfwCreateWindow(1600, 800, "OpenGL", NULL, NULL);  //uwaga wszystkie wbudowane modele trzeba przeskalowac w wymiarze x /2 

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
		drawScene(window, positionOffset, viewOffset);
		glfwPollEvents(); 
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate(); // free the resources taken by GLFW
	exit(EXIT_SUCCESS);
}
