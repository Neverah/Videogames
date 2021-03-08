//Autor: Miguel Torres Est�vez

#ifndef STEVE_H
#define STEVE_H

#ifndef TORRE_H
#include "Torre.h"
#endif

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

#define GRAVEDAD 0.008;
#define VELOCIDAD_SALTO_BASE -0.22;

class Steve
{

public:

	double px, py, pz;				//Coordenadas de la posici�n
	double sx, sy, sz;				//Escalado

	double velocidadSalto;			//Velocidad vertical que se establece cuando se salta
	double velocidadCaida;			//Velocidad vertical de ca�da (si es negativa, caer� hacia arriba)

	GLuint VAO;						//�ndice del VAO
	GLuint textura;					//�ndice de la textura

	Steve(double px, double py, double pz, double sx, double sy, double sz, GLuint VAO, GLuint textura) {

		this->px = px;
		this->py = py;
		this->pz = pz;

		this->sx = sx;
		this->sy = sy;
		this->sz = sz;

		this->velocidadSalto = VELOCIDAD_SALTO_BASE;
		this->velocidadCaida = 0;

		this->VAO = VAO;
		this->textura = textura;
	}

	void dibujar();
	void saltar();
	void caer();
	int comprobarColision(Torre torre);
};

#endif // !STEVE_H

