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

void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			std::cout << "look to the left\n";
		}
		if (key == GLFW_KEY_RIGHT) {
			std::cout << "look to the right\n";

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
	glEnable(GL_DEPTH_TEST); 
	glfwSetKeyCallback(window, key_callback);
}


// freeing the resources
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
}



// drawing a scene
void drawScene(GLFWwindow* window) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// camera movement - to add

	//drawBackyard(); idk where to put this tbh xdd
	drawRoom();
	drawFurniture();

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

	window = glfwCreateWindow(1600, 800, "OpenGL", NULL, NULL);  

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

	// main game loop	
	while (!glfwWindowShouldClose(window)) 
	{		
		drawScene(window); 
		glfwPollEvents(); 
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate(); // free the resources taken by GLFW
	exit(EXIT_SUCCESS);
}
