//Autor: Miguel Torres Estévez

#ifndef TORRE_H
#define TORRE_H

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

#define SEPARACION_HUECO_TORRES_FS 3.4  //Será el doble en total
#define POSICION_INICIO_TORRES 35.0		//Desplazamiento hacia la derecha donde se crean las torres
#define ALTURA_TORRES_FS 24.0			//Altura
#define ANCHO_TORRES_FS 4.0				//Ancho

class Torre
{

public:

	double desplazamiento;			//Desplazamiento de la torre
	double alturaHueco;				//Altura a la que aparecerá centrado el hueco entre las torres

	GLuint VAO;						//Índice del VAO
	GLuint textura;					//Índice de la textura

	Torre(double desplazamiento, double alturaHueco, GLuint VAO, GLuint textura) {

		this->desplazamiento = desplazamiento;
		this->alturaHueco = alturaHueco;

		this->VAO = VAO;
		this->textura = textura;
	}

	void dibujarParTorres();
};

#endif // !TORRE_H

