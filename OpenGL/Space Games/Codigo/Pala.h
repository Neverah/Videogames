//Autor: Miguel Torres Estévez

#ifndef PALA_H
#define PALA_H

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

class Pala
{

public:

	double px, py, pz;				//Coordenadas de la posición
	double sx, sy, sz;				//Escalado
	double traslacion;				//Angulo de giro

	GLuint VAO;						//Índice del VAO
	GLuint textura;					//Índice de la textura

	int nVertices;					//Número de vértices

	double distancia;				//Distancia al centro

	Pala(double sx, double sy, double sz, double distancia, double traslacion, GLuint VAO, GLuint textura, int nVertices) {

		this->px = 0;
		this->py = 0;
		this->pz = 0;

		this->sx = sx;
		this->sy = sy;
		this->sz = sz;
		
		this->distancia = distancia;
		this->traslacion = traslacion;

		this->VAO = VAO;
		this->nVertices = nVertices;
		this->textura = textura;
	}

	void dibujar();
	void actualizarPosicion(double angulo);
};

#endif // !PALA_H

