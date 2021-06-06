//Autor: Miguel Torres Estévez

#ifndef COCHE_H
#define COCHE_H

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

#define ANCHO_COCHE 2.0					//Ancho
#define LARGO_COCHE 4.0					//Largo
#define VELOCIDAD_GIRO 2.0				//Velocidad del giro sobre sí mismo
#define VELOCIDAD_COCHE_ROJO 0.4		//Velocidad de movimiento del coche rojo
#define VELOCIDAD_REBOTE 0.15			//Velocidad inicial del rebote
#define VELOCIDAD_MAXIMA_COCHES 3.0		//Velocidad máxima alcanzable

class Coche
{

public:

	double px, pz;			//Coordenadas de la posición

	double velocidadBase;	//Velocidad base del coche
	double velocidad;		//Velocidad actual del coche

	double giro;			//Ángulo del giro sobre sí mismo

	int movimiento;			//Indica si el coche se está moviendo

	GLuint VAO;				//VAO
	GLuint textura;			//Índice de la textura

	Coche(double px, double pz, double velocidadBase, GLuint VAO, GLuint textura) {

		this->px = px;
		this->pz = pz;

		this->velocidadBase = velocidadBase;
		this->velocidad = velocidadBase;

		this->giro = rand() % 360;

		this->movimiento = 0;

		this->VAO = VAO;
		this->textura = textura;
	}

	void dibujar();
	void actualizarPosicion();
	int comprobarColision(Coche otroCoche);
};

#endif // !COCHE_H

