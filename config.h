#pragma once

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"

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
#define drawerPos (glm::vec3(-46.8f, 0.0f, 0.0f)) // relative to the desk