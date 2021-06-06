//Autor: Miguel Torres Estévez
#include "Coche.h"

//Función que dibuja el coche

void Coche::dibujar() {

	glDisable(GL_CULL_FACE);

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	transform = glm::translate(transform, glm::vec3(Coche::px, 0.1f, Coche::pz));
	transform = glm::rotate(transform, (float)((Coche::giro + 90.0) * ARADIANES), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(ANCHO_COCHE, 1.0f, LARGO_COCHE));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, Coche::textura);

	glBindVertexArray(Coche::VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}


//Función que actualiza la posición del coche

void Coche::actualizarPosicion() {

	if (Coche::movimiento) {

		//El coche se desplaza según su velocidad

		Coche::px += Coche::velocidad * cos(-Coche::giro * ARADIANES);
		Coche::pz += Coche::velocidad * sin(-Coche::giro * ARADIANES);

		//Calculo de las posiciones de las esquinas del coche

		double moduloXAncho = ANCHO_COCHE / 2.0 * -cos((Coche::giro + 90.0) * ARADIANES);
		double moduloXLargo = LARGO_COCHE / 2.0 * cos(Coche::giro * ARADIANES);

		double moduloZAncho = ANCHO_COCHE / 2.0 * sin((Coche::giro + 90.0) * ARADIANES);
		double moduloZLargo = LARGO_COCHE / 2.0 * -sin(Coche::giro * ARADIANES);

		double pxFrontalIzquierdo = Coche::px - moduloXAncho + moduloXLargo;
		double pzFrontalIzquierdo = Coche::pz - moduloZAncho + moduloZLargo;

		double pxFrontalDerecho = Coche::px + moduloXAncho + moduloXLargo;
		double pzFrontalDerecho = Coche::pz + moduloZAncho + moduloZLargo;

		double pxTraseroIzquierdo = Coche::px - moduloXAncho - moduloXLargo;
		double pzTraseroIzquierdo = Coche::pz - moduloZAncho - moduloZLargo;

		double pxTraseroDerecho = Coche::px + moduloXAncho - moduloXLargo;
		double pzTraseroDerecho = Coche::pz + moduloZAncho - moduloZLargo;

		if (pxFrontalIzquierdo > 28 || pxFrontalIzquierdo < -28 || pxFrontalDerecho > 28 || pxFrontalDerecho < -28 ||		//Si las esquinas frontales salen del límite, se revierte el movimiento y se rebota si se estaba avanzando
			pzFrontalIzquierdo > 28 || pzFrontalIzquierdo < -28 || pzFrontalDerecho > 28 || pzFrontalDerecho < -28) {

				Coche::px -= Coche::velocidad * cos(-Coche::giro * ARADIANES);
				Coche::pz -= Coche::velocidad * sin(-Coche::giro * ARADIANES);

				if (velocidad >= 0) velocidad = -VELOCIDAD_REBOTE;
		}
		else if (pxTraseroIzquierdo > 28 || pxTraseroIzquierdo < -28 || pxTraseroDerecho > 28 || pxTraseroDerecho < -28 ||	//Si las esquinas traseras salen del límite, se revierte el movimiento según el valor de la velocidad
				 pzTraseroIzquierdo > 28 || pzTraseroIzquierdo < -28 || pzTraseroDerecho > 28 || pzTraseroDerecho < -28) {

			if (Coche::velocidad > 0) {
				Coche::px += Coche::velocidad * cos(-Coche::giro * ARADIANES);
				Coche::pz += Coche::velocidad * sin(-Coche::giro * ARADIANES);
			}
			else {
				Coche::px -= Coche::velocidad * cos(-Coche::giro * ARADIANES);
				Coche::pz -= Coche::velocidad * sin(-Coche::giro * ARADIANES);
			}
		}

		if (velocidad < 0) {	//Si se está retrocediendo, se disminuye el retroceso hasta que la velocidad vuelve a ser positiva. En ese momento, se establece la velocidad a la base y se indica que el coche está quieto

			velocidad += VELOCIDAD_REBOTE / 60.0;

			if (velocidad > 0) {
				movimiento = 0;
				velocidad = velocidadBase;
			}

		}
	}
	else {

		Coche::giro += VELOCIDAD_GIRO;
		if (Coche::giro > 360.0) Coche::giro -= 360.0;
		if (Coche::giro < -360.0) Coche::giro += 360.0;
	}
}

//NOTA:
//X -> Eje Y
//Z -> Eje X

//Función que comprueba si el coche ha chocado con otro

int Coche::comprobarColision(Coche otroCoche) {

	int colision = 0;		//Variable auxiliar para guardar el resultado en caso afirmativo, ya que para los coches frontales es necesario hacer una gestión antes del return
	double distancia;		//Variable para almacenar la distancia

	distancia = sqrt((Coche::px - otroCoche.px) * (Coche::px - otroCoche.px) + (Coche::pz - otroCoche.pz) * (Coche::pz - otroCoche.pz));

	if (distancia > 2.0 * LARGO_COCHE) return 0;		//Si los círculos que engloban a los coches en su totalidad no colisionan, no hay necesidad de hacer el cálculo preciso
	if (Coche::velocidad < 0) return 0;					//Si los coches están dando marcha atrás, las colisiones no cuentan (sólo se están separando para deshacer un atasco)
	if (distancia < ANCHO_COCHE / 2.0) return 3;		//Hacemos una última comprobación para el caso en el que, al dar marcha atrás, 2 coches hayan quedado superpuestos

	//Calculo de las esquinas frontales de este coche

	double moduloXAncho = ANCHO_COCHE / 2.0 * -cos((Coche::giro + 90.0) * ARADIANES);
	double moduloXLargo = LARGO_COCHE / 2.0 * cos(Coche::giro * ARADIANES);

	double moduloZAncho = ANCHO_COCHE / 2.0 * sin((Coche::giro + 90.0) * ARADIANES);
	double moduloZLargo = LARGO_COCHE / 2.0 * -sin(Coche::giro * ARADIANES);

	double pxFrontalIzquierdo = Coche::px - moduloXAncho + moduloXLargo;
	double pzFrontalIzquierdo = Coche::pz - moduloZAncho + moduloZLargo;

	double pxFrontalDerecho = Coche::px + moduloXAncho + moduloXLargo;
	double pzFrontalDerecho = Coche::pz + moduloZAncho + moduloZLargo;

	//printf("X: %lf, Z:%lf\nIX: %lf, IZ: %lf\nDX: %lf, DZ: %lf\n\n", Coche::px, Coche::pz, pxFrontalIzquierdo, pzFrontalIzquierdo, pxFrontalDerecho, pzFrontalDerecho);

	//Cálculo del área del otro coche mediante aproximación por círculos

	double divisiones = 20;		//Número de divisiones a realizar

	moduloXLargo *= 0.5;
	moduloZLargo *= 0.5;

	double incrementoX = moduloXLargo / (divisiones * 2.0);
	double incrementoZ = moduloZLargo / (divisiones * 2.0);

	double circuloDerechoX = otroCoche.px;
	double circuloDerechoZ = otroCoche.pz;

	double circuloIzquierdoX = otroCoche.px;
	double circuloIzquierdoZ = otroCoche.pz;

	for (int i = 0; i < divisiones; i++) {	//Dividimos el área de la pala en tantos círculos hacia cada lateral como indique la variable de divisiones (es más fácil usar círculos, ya que la pala va a estar rotando)

		//Repartimos los círculos de forma uniforme a través de la pala y comprobamos si han colisionado con las esquinas del coche

		circuloDerechoX += incrementoX;
		circuloDerechoZ += incrementoZ;

		distancia = sqrt((pxFrontalIzquierdo - circuloDerechoX) * (pxFrontalIzquierdo - circuloDerechoX) + (pzFrontalIzquierdo - circuloDerechoZ) * (pzFrontalIzquierdo - circuloDerechoZ));
		if (distancia < ANCHO_COCHE / 2.0) colision = 1;

		distancia = sqrt((pxFrontalDerecho - circuloDerechoX) * (pxFrontalDerecho - circuloDerechoX) + (pzFrontalDerecho - circuloDerechoZ) * (pzFrontalDerecho - circuloDerechoZ));
		if (distancia < ANCHO_COCHE / 2.0) colision = 1;


		circuloIzquierdoX -= incrementoX;
		circuloIzquierdoZ -= incrementoZ;

		distancia = sqrt((pxFrontalIzquierdo - circuloIzquierdoX) * (pxFrontalIzquierdo - circuloIzquierdoX) + (pzFrontalIzquierdo - circuloIzquierdoZ) * (pzFrontalIzquierdo - circuloIzquierdoZ));
		if (distancia < ANCHO_COCHE / 2.0) colision = 1;

		distancia = sqrt((pxFrontalDerecho - circuloIzquierdoX) * (pxFrontalDerecho - circuloIzquierdoX) + (pzFrontalDerecho - circuloIzquierdoZ) * (pzFrontalDerecho - circuloIzquierdoZ));
		if (distancia < ANCHO_COCHE / 2.0) colision = 1;
	}

	if (colision) {

		if (!Coche::movimiento) return 3;	//Si el coche colisiona y está quieto, contará como una colisión estática (se solucionará retrocediendo)

		int diferenciaGiros = Coche::giro - otroCoche.giro;		//Si la colisión no es estática, obtenemos el valor verdadero de la diferencia de las rotaciones de los coches
		if (diferenciaGiros < 0) diferenciaGiros *= -1.0;

		if (diferenciaGiros > 130 && diferenciaGiros < 230) {	//Si los coches han chocado de frente dentro de un ángulo de 100º, contará como una colisión frontal (ambos coches rebotarán)
			return 2;
		}

		return 1;	//En otro caso, contará como una colisión normal (el coche sacará al otro coche de la pista)
	}

	return 0;	//Si no se ha detectado ninguna colisión, se devuelve un falso
}