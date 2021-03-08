//Autor: Miguel Torres Estévez

#ifndef OBSTACULO_H
#define OBSTACULO_H

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

#define LARGO_SUELO_SS 12.0
#define ANCHO_SUELO_SS 6.0
#define NUM_SECCIONES_PASILLO_SS 32

const double distanciaMaximaSS = NUM_SECCIONES_PASILLO_SS * LARGO_SUELO_SS;

class Obstaculo
{

public:

	int orientacion;			//Orientación del obstáculo (suelo o techo)

	double desplazamiento;		//Desplazamiento del obstáculo

	double rotacion;	//Rotación del obstáculo sobre sí mismo

	GLuint VAO;			//Índice del VAO
	GLuint textura;		//Índice de la textura

	Obstaculo(int orientacion, GLuint VAO, GLuint textura) {

		this->orientacion = orientacion;

		this->desplazamiento = 0;

		this->rotacion = 0;

		this->VAO = VAO;
		this->textura = textura;
	}

	void dibujar(Sphere esfera);
};

#endif // !OBSTACULO_H

