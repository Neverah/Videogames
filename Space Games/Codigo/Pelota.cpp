//Autor: Miguel Torres Estévez
#include "Pelota.h"

//Función que dibuja la pelota

void Pelota::dibujar(Sphere esfera) {

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	transform = glm::translate(transform, glm::vec3(Pelota::px, Pelota::py, Pelota::pz));
	transform = glm::rotate(transform, (float)(Pelota::anguloRotacion * ARADIANES), glm::vec3(1.0f, 1.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(Pelota::radio, Pelota::radio, Pelota::radio));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, Pelota::textura);

	esfera.draw();
}


//Función que actualiza la posición de la pelota según su velocidad y ángulo de giro

void Pelota::actualizarPosicion() {

	Pelota::px += Pelota::velocidad * cos(Pelota::anguloGiro * ARADIANES);
	Pelota::pz += Pelota::velocidad * sin(Pelota::anguloGiro * ARADIANES);

	Pelota::distanciaAlCentro = sqrt(Pelota::px * Pelota::px + Pelota::pz * Pelota::pz);

	Pelota::anguloRotacion += velocidad * 5.0;
	if (Pelota::anguloRotacion > 360) Pelota::anguloRotacion -= 360.0;
}


//Función que comprueba la colisión de la pelota con una pala

int Pelota::comprobarColision(Pala pala, Sphere esfera) {

	double distancia = sqrt((Pelota::px - pala.px) * (Pelota::px - pala.px) + (Pelota::pz - pala.pz) * (Pelota::pz - pala.pz));

	if (distancia < pala.sz) {	//Para no hacer la comprobación precisa con todas las palas, primero comprobamos si la pelota está dentro del área circular que engloba la pala

		double divisiones = 30;								//Divisiones
		double divisionesLaterales = divisiones * 0.3;		//Divisiones laterales (bordes de la pala)
		double factorSeguridad = 1.0;						//Un coeficiente de seguridad

		double incrementoX = (pala.sz * cos((pala.traslacion + 90.0) * ARADIANES) / ((double)divisiones * 2.0));
		double incrementoZ = (pala.sz * sin((pala.traslacion - 90.0) * ARADIANES) / ((double)divisiones * 2.0));

		//Comenzamos comprobando los bordes de la pala
		double circuloDerechoX = pala.px + (divisiones - divisionesLaterales) * incrementoX;
		double circuloDerechoZ = pala.pz + (divisiones - divisionesLaterales) * incrementoZ;

		double circuloIzquierdoX = pala.px - (divisiones - divisionesLaterales) * incrementoX;
		double circuloIzquierdoZ = pala.pz - (divisiones - divisionesLaterales) * incrementoZ;

		for (int i = 0; i < divisionesLaterales; i++) {	//Dividimos el área de la pala en tantos círculos hacia cada lateral como indique la variable de divisiones (es más fácil usar círculos, ya que la pala va a estar rotando)

			//Repartimos los círculos de forma uniforme a través de la pala

			circuloDerechoX += incrementoX;
			circuloDerechoZ += incrementoZ;

			distancia = sqrt((Pelota::px - circuloDerechoX) * (Pelota::px - circuloDerechoX) + (Pelota::pz - circuloDerechoZ) * (Pelota::pz - circuloDerechoZ));
			if (distancia < pala.sx * factorSeguridad + Pelota::radio) {
				Pelota::corregirColisionLateral(pala, sqrt(circuloDerechoX * circuloDerechoX + circuloDerechoZ * circuloDerechoZ));
				return true;
			}

			circuloIzquierdoX -= incrementoX;
			circuloIzquierdoZ -= incrementoZ;

			distancia = sqrt((Pelota::px - circuloIzquierdoX) * (Pelota::px - circuloIzquierdoX) + (Pelota::pz - circuloIzquierdoZ) * (Pelota::pz - circuloIzquierdoZ));
			if (distancia < pala.sx * factorSeguridad + Pelota::radio) {
				Pelota::corregirColisionLateral(pala, sqrt(circuloIzquierdoX * circuloIzquierdoX + circuloIzquierdoZ * circuloIzquierdoZ));
				return true;
			}
		}

		circuloDerechoX = pala.px;
		circuloDerechoZ = pala.pz;

		circuloIzquierdoX = pala.px;
		circuloIzquierdoZ = pala.pz;

		for (int i = 0; i < divisiones - divisionesLaterales; i++) {	//Dividimos el área de la pala en tantos círculos hacia cada lateral como indique la variable de divisiones (es más fácil usar círculos, ya que la pala va a estar rotando)

			//Repartimos los círculos de forma uniforme a través de la pala

			circuloDerechoX += incrementoX;
			circuloDerechoZ += incrementoZ;

			distancia = sqrt((Pelota::px - circuloDerechoX) * (Pelota::px - circuloDerechoX) + (Pelota::pz - circuloDerechoZ) * (Pelota::pz - circuloDerechoZ));
			if (distancia < pala.sx * factorSeguridad + Pelota::radio) {
				Pelota::corregirColisionLateral(pala, sqrt(circuloDerechoX * circuloDerechoX + circuloDerechoZ * circuloDerechoZ));
				//Pelota::corregirColisionFrontal(pala);
				return true;
			}

			circuloIzquierdoX -= incrementoX;
			circuloIzquierdoZ -= incrementoZ;

			distancia = sqrt((Pelota::px - circuloIzquierdoX) * (Pelota::px - circuloIzquierdoX) + (Pelota::pz - circuloIzquierdoZ) * (Pelota::pz - circuloIzquierdoZ));
			if (distancia < pala.sx * factorSeguridad + Pelota::radio) {
				
				Pelota::corregirColisionLateral(pala, sqrt(circuloIzquierdoX * circuloIzquierdoX + circuloIzquierdoZ * circuloIzquierdoZ));
				//Pelota::corregirColisionFrontal(pala);
				return true;
			}

			
		}
	}

	//printf("Pala: (%lf, %lf)\nCD:  (%lf, %lf)\nCI:  (%lf, %lf)\n-----------------------------------\n", pala.px, pala.pz, circuloDerechoX, circuloDerechoZ, circuloIzquierdoX, circuloIzquierdoZ);

	return false;
}


/*
//Función que corrige una colisión frontal de la pelota

void Pelota::corregirColisionFrontal(Pala pala) {

	Pelota::px -= Pelota::velocidad * cos(Pelota::anguloGiro * ARADIANES) * 1.5;
	Pelota::pz -= Pelota::velocidad * sin(Pelota::anguloGiro * ARADIANES) * 1.5;

	Pelota::anguloGiro += 180.0 - 20.0 + rand() % 40;

	if(Pelota::velocidad < 10.0) Pelota::velocidad += INCREMENTO_VELOCIDAD_PELOTAS;
	Pelota::contadorRebotes++;
}*/


//Función que corrige una colisión frontal de la pelota

void Pelota::corregirColisionFrontal(Pala pala) {

	Pelota::px -= Pelota::velocidad * cos(Pelota::anguloGiro * ARADIANES) * 1.5;
	Pelota::pz -= Pelota::velocidad * sin(Pelota::anguloGiro * ARADIANES) * 1.5;

	Pelota::anguloGiro += 180.0 - 30.0 + rand() % 60;

	if (Pelota::velocidad < 10.0) Pelota::velocidad += INCREMENTO_VELOCIDAD_PELOTAS;
	Pelota::contadorRebotes++;
}


//Función que corrige una colisión lateral de la pelota (más costosa, pero necesaria para evitar bugs)

void Pelota::corregirColisionLateral(Pala pala, double distanciaPuntoColision) {

	if (distanciaPuntoColision > Pelota::distanciaAlCentro) {

		Pelota::px -= Pelota::radio * cos(-pala.traslacion * ARADIANES);
		Pelota::pz -= Pelota::radio * sin(-pala.traslacion * ARADIANES);
	}
	else {

		Pelota::px += Pelota::radio * cos(-pala.traslacion * ARADIANES);
		Pelota::pz += Pelota::radio * sin(-pala.traslacion * ARADIANES);
	}

	Pelota::px -= Pelota::velocidad * cos(Pelota::anguloGiro * ARADIANES) * 1.5;
	Pelota::pz -= Pelota::velocidad * sin(Pelota::anguloGiro * ARADIANES) * 1.5;

	Pelota::anguloGiro += 180.0;

	if (Pelota::velocidad < 8) Pelota::velocidad += INCREMENTO_VELOCIDAD_PELOTAS;
	Pelota::contadorRebotes++;
}