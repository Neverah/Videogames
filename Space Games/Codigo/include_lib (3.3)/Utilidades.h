//Autor: Miguel Torres Estévez

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <windows.h>
#include <MMsystem.h>
#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>	
#include <vector>
#include <map>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Sphere.h"

#define PI 3.14159265359
#define ARADIANES PI/180.0
#define AGRADOS 180.0/PI

struct Character {
	unsigned int IDTextura;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

//Texto

FT_Library ft;
FT_Face face;
std::map<char, Character> Characters;

//Externos

extern GLuint shaderProgram;

//Funciones

void cargarCaracteres();

#endif // !UTILIDADES_H
