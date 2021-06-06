//Autor: Miguel Torres Estévez

#ifndef PELOTA_H
#define PELOTA_H

#ifndef PALA_H
#include "Pala.h"
#endif // !PALA_H

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

#define TAMANO_PELOTAS_PONG 1.0					//Tamaño de las pelotas
#define INCREMENTO_VELOCIDAD_PELOTAS 0.01		//Indica cuánto aumenta la velocidad de las pelotas con cada colisión

class Pelota
{

public:

	double px, py, pz;				//Coordenadas de la posición de la pelota
	double anguloGiro;				//Angulo de giro de la pelota
	double anguloRotacion;			//Angulo de la rotación de la pelota sobre si misma

	GLuint textura;					//Índice de la textura

	double radio;					//Radio de la pelota
	double velocidad;				//Velocidad actual de la pelota
	double distanciaAlCentro;		//Distancia de la pelota al centro (empleado en las colisiones)

	long int contadorRebotes;

	Pelota(double px, double py, double pz, double radio, double velocidad, GLuint textura) {

		this->px = px;
		this->py = py;
		this->pz = pz;

		this->radio = radio;
		this->distanciaAlCentro = 0;

		this->velocidad = velocidad;
		this->anguloGiro = rand() % 360;
		this->anguloRotacion = rand() % 360;

		this->textura = textura;

		this->contadorRebotes = 0;
	}

	void dibujar(Sphere esfera);
	void actualizarPosicion();
	int comprobarColision(Pala pala, Sphere esfera);
	void corregirColisionFrontal(Pala pala);
	void corregirColisionLateral(Pala pala, double distanciaPuntoColision);
};

#endif // !PELOTA_H

