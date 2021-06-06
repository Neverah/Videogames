//Autor: Miguel Torres Est�vez
#include "Coche.h"

//Funci�n que dibuja el coche

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


//Funci�n que actualiza la posici�n del coche

void Coche::actualizarPosicion() {

	if (Coche::movimiento) {

		//El coche se desplaza seg�n su velocidad

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

		if (pxFrontalIzquierdo > 28 || pxFrontalIzquierdo < -28 || pxFrontalDerecho > 28 || pxFrontalDerecho < -28 ||		//Si las esquinas frontales salen del l�mite, se revierte el movimiento y se rebota si se estaba avanzando
			pzFrontalIzquierdo > 28 || pzFrontalIzquierdo < -28 || pzFrontalDerecho > 28 || pzFrontalDerecho < -28) {

				Coche::px -= Coche::velocidad * cos(-Coche::giro * ARADIANES);
				Coche::pz -= Coche::velocidad * sin(-Coche::giro * ARADIANES);

				if (velocidad >= 0) velocidad = -VELOCIDAD_REBOTE;
		}
		else if (pxTraseroIzquierdo > 28 || pxTraseroIzquierdo < -28 || pxTraseroDerecho > 28 || pxTraseroDerecho < -28 ||	//Si las esquinas traseras salen del l�mite, se revierte el movimiento seg�n el valor de la velocidad
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

		if (velocidad < 0) {	//Si se est� retrocediendo, se disminuye el retroceso hasta que la velocidad vuelve a ser positiva. En ese momento, se establece la velocidad a la base y se indica que el coche est� quieto

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

//Funci�n que comprueba si el coche ha chocado con otro

int Coche::comprobarColision(Coche otroCoche) {

	int colision = 0;		//Variable auxiliar para guardar el resultado en caso afirmativo, ya que para los coches frontales es necesario hacer una gesti�n antes del return
	double distancia;		//Variable para almacenar la distancia

	distancia = sqrt((Coche::px - otroCoche.px) * (Coche::px - otroCoche.px) + (Coche::pz - otroCoche.pz) * (Coche::pz - otroCoche.pz));

	if (distancia > 2.0 * LARGO_COCHE) return 0;		//Si los c�rculos que engloban a los coches en su totalidad no colisionan, no hay necesidad de hacer el c�lculo preciso
	if (Coche::velocidad < 0) return 0;					//Si los coches est�n dando marcha atr�s, las colisiones no cuentan (s�lo se est�n separando para deshacer un atasco)
	if (distancia < ANCHO_COCHE / 2.0) return 3;		//Hacemos una �ltima comprobaci�n para el caso en el que, al dar marcha atr�s, 2 coches hayan quedado superpuestos

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

	//C�lculo del �rea del otro coche mediante aproximaci�n por c�rculos

	double divisiones = 20;		//N�mero de divisiones a realizar

	moduloXLargo *= 0.5;
	moduloZLargo *= 0.5;

	double incrementoX = moduloXLargo / (divisiones * 2.0);
	double incrementoZ = moduloZLargo / (divisiones * 2.0);

	double circuloDerechoX = otroCoche.px;
	double circuloDerechoZ = otroCoche.pz;

	double circuloIzquierdoX = otroCoche.px;
	double circuloIzquierdoZ = otroCoche.pz;

	for (int i = 0; i < divisiones; i++) {	//Dividimos el �rea de la pala en tantos c�rculos hacia cada lateral como indique la variable de divisiones (es m�s f�cil usar c�rculos, ya que la pala va a estar rotando)

		//Repartimos los c�rculos de forma uniforme a trav�s de la pala y comprobamos si han colisionado con las esquinas del coche

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

		if (!Coche::movimiento) return 3;	//Si el coche colisiona y est� quieto, contar� como una colisi�n est�tica (se solucionar� retrocediendo)

		int diferenciaGiros = Coche::giro - otroCoche.giro;		//Si la colisi�n no es est�tica, obtenemos el valor verdadero de la diferencia de las rotaciones de los coches
		if (diferenciaGiros < 0) diferenciaGiros *= -1.0;

		if (diferenciaGiros > 130 && diferenciaGiros < 230) {	//Si los coches han chocado de frente dentro de un �ngulo de 100�, contar� como una colisi�n frontal (ambos coches rebotar�n)
			return 2;
		}

		return 1;	//En otro caso, contar� como una colisi�n normal (el coche sacar� al otro coche de la pista)
	}

	return 0;	//Si no se ha detectado ninguna colisi�n, se devuelve un falso
}