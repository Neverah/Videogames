//Autor: Miguel Torres Estévez

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <windows.h>
#include <MMsystem.h>
#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>	
#include <string>
#include <vector>
#include <map>

#include "Sphere.h"

#ifndef FT2BUILD_H_
#include "ft2build.h"
#include FT_FREETYPE_H
#endif

#define PI 3.14159265359
#define ARADIANES PI/180.0
#define AGRADOS 180.0/PI

struct Character {
	unsigned int IDTextura;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

//Externos

extern GLuint shadersPrincipales;

#endif // !UTILIDADES_H
