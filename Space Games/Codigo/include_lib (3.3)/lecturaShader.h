/******************************************
  Lectura y creacion de Shaders
*******************************************/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS //Evitamos alguno errores de funciones no seguras
#endif
#pragma warning(disable:4996) //Evitamos alguno errores de funciones no seguras

//Librerias necesarias 
#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GLuint vertexShader, fragmentShader; // Definicion  vertex y fragment shader
GLuint  progShader;					// Definicion de el program Shader

									
// Para leer los ficheros de texto plano 


char *textFileRead(const char *fn) {
	
	FILE *fichero;
	char *contenido = NULL;

	int count = 0;
	
	if (fn != NULL) {
		fichero = fopen(fn, "rt");

		if (fichero != NULL) {

			fseek(fichero, 0, SEEK_END);
			count = ftell(fichero);
			rewind(fichero);

			if (count > 0) {
				contenido = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(contenido, sizeof(char), count, fichero);
				contenido[count] = '\0';
			}
			fclose(fichero);
		}
		else {

			printf("Error al abrir el fichero %s\n", fn);
			return NULL;
		}
	}
	 	
	return contenido;
}

// Nos indica e imprime por pantalla si hay algun error al crear el shader o el program

void printInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}



GLuint setShaders(const char *nVertx, const char *nFrag) {

	char *ficherovs = NULL;
	char *ficherofs = NULL;
	const char * codigovs = NULL;
	const char * codigofs = NULL;

	//Creo el vertexShader y el FragmentShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//Leo el codigo del ficheo y hay error devuelve un NULL
	ficherovs = textFileRead(nVertx);
		if (ficherovs == NULL) return NULL;
	ficherofs = textFileRead(nFrag);
		if (ficherofs == NULL) return NULL;

	//Lo igual al puntero para cargarlos
	codigovs = ficherovs;
	codigofs = ficherofs;
    //Los cargo
	glShaderSource(vertexShader, 1, &codigovs,NULL);
	glShaderSource(fragmentShader, 1, &codigofs,NULL);

	//Libero los ficheros
	free(ficherovs);free(ficherofs);

	// Copio vertex y Fragment
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//Miro si hay algun error
	printInfoLog(vertexShader);
	printInfoLog(fragmentShader);

	//Creo el programa asociado
	progShader = glCreateProgram();

	// Le attacheo shaders al programa
	glAttachShader(progShader,vertexShader);
	glAttachShader(progShader,fragmentShader);

	// Lo linko
	glLinkProgram(progShader);
	// A ver si hay errores
	printInfoLog(progShader);

	return (progShader);

}


