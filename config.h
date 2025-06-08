#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"

#include <iostream>
#include <cmath>
#include <tuple>

#define WIDTH (1600.0f)
#define HEIGHT (800.0f)

#define wardrobeSize (glm::vec3(140.0f/2.0f, 200.0f/2.0f, 50.0f/2.0f)) // divided by 2 for easier calculations and scaling
#define wardrobePos (glm::vec3(-110.0f, -23.0f, 155.0f))

#define deskSize (glm::vec3(140.0f/2.0f, 50.0f/2.0f, 50.0f/2.0f))
#define deskPos (glm::vec3(110.0f, -49.0f, 155.0f))
#define drawerSize (glm::vec3(42.0f/2, 20.0f/2, 50.0f/2))
#define drawerPos (glm::vec3(-46.8f, -14.0f, 0.0f)) // relative to the desk
#define cabinetSize (glm::vec3(42.0f/2, 50.0f/2, 50.0f/2.0f))
#define cabinetPos (glm::vec3(0.0f, -35.0f, 0.0f)) // relative to the drawer

#define boxSize (glm::vec3(30.0f/2.0f, 10.0f/2.0f, 20.0f/2.0f))
#define boxPos (glm::vec3(10.0f, 6.5f, 15.0f)) // relative to the desk

#define bedSize (glm::vec3(200.0f/2.0f, 0.0f, 80.0f/2.0f))
#define bedPos (glm::vec3(80.0f, -95.0f, -140.0f))