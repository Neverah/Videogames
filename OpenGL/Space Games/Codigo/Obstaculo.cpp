//Autor: Miguel Torres Estévez
#include "Obstaculo.h"

//Función que dibuja una pareja de torres dada la altura del hueco y su desplazamiento horizontal

void Obstaculo::dibujar(Sphere esfera) {

	//printf("Distancia: %lf\n", distanciaMaximaSS - Obstaculo::desplazamiento);

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	if(orientacion) transform = glm::translate(transform, glm::vec3(distanciaMaximaSS - Obstaculo::desplazamiento, -0.25 + ANCHO_SUELO_SS * 7.0 / 8.0, 0.0f));
	else transform = glm::translate(transform, glm::vec3(distanciaMaximaSS - Obstaculo::desplazamiento, 0.25 + ANCHO_SUELO_SS / 8.0, 0.0f));

	if (orientacion) transform = glm::rotate(transform, (float)(-Obstaculo::rotacion * ARADIANES), glm::vec3(0.0f, 0.0f, 1.0f));
	else transform = glm::rotate(transform, (float)(Obstaculo::rotacion * ARADIANES), glm::vec3(0.0f, 0.0f, 1.0f));

	transform = glm::rotate(transform, (float)(90.0 * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, Obstaculo::textura);

	esfera.draw();
}