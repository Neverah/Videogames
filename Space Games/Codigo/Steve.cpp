//Autor: Miguel Torres Estévez
#include "Steve.h"

const double incrementoVelocidadPelotas = 0.01;

//Función que dibuja el avatar de Steve

void Steve::dibujar() {

	glDisable(GL_CULL_FACE);

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	transform = glm::translate(transform, glm::vec3(Steve::px, Steve::py, Steve::pz));
	transform = glm::scale(transform, glm::vec3(Steve::sx, Steve::sy, Steve::sz));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, Steve::textura);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}


//Función que gestiona el salto del avatar

void Steve::saltar() {
	Steve::velocidadCaida = Steve::velocidadSalto;
}


//Función que actualiza la posición del avatar según la gravedad

void Steve::caer() {
	Steve::velocidadCaida += GRAVEDAD;
	Steve::pz += Steve::velocidadCaida;
}


//Función que comprueba la colisión del avatar con las torres

int Steve::comprobarColision(Torre torre) {

	double pxTorre = POSICION_INICIO_TORRES - torre.desplazamiento;

	//printf("X: %lf, Z: %lf\n", Steve::px, Steve::pz);

	if (Steve::pz + Steve::sz / 2.0 > 12.0) {
		//printf("Colision por caida\n");
		return true;
	}

	if (Steve::px + Steve::sx / 2.0 > pxTorre - ANCHO_TORRES_FS / 2.0 && Steve::px - Steve::sx / 2.0 < pxTorre + ANCHO_TORRES_FS / 2.0) {
		//printf("Colision horizontal\n");
		if (Steve::pz - Steve::sz / 2.0 < torre.alturaHueco - SEPARACION_HUECO_TORRES_FS || Steve::pz + Steve::sz / 2.0 > torre.alturaHueco + SEPARACION_HUECO_TORRES_FS) {
			//printf("Colision vertical\n");
			return true;
		}
	}
	return false;
}