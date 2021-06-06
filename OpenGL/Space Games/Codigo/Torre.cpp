//Autor: Miguel Torres Estévez
#include "Torre.h"

//Función que dibuja una pareja de torres según la altura del hueco entre ellas y su desplazamiento horizontal

void Torre::dibujarParTorres() {

	double desplazamientoTorre = ALTURA_TORRES_FS / 2.0;

	glDisable(GL_CULL_FACE);

	//Torre 1

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader
	transform = glm::translate(transform, glm::vec3(POSICION_INICIO_TORRES - desplazamiento, 0.1f, alturaHueco + desplazamientoTorre + SEPARACION_HUECO_TORRES_FS));
	transform = glm::scale(transform, glm::vec3(ANCHO_TORRES_FS, 1.0, ALTURA_TORRES_FS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, Torre::textura);

	glBindVertexArray(Torre::VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Torre 2

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(POSICION_INICIO_TORRES - desplazamiento, 0.1f, alturaHueco - desplazamientoTorre - SEPARACION_HUECO_TORRES_FS));
	transform = glm::scale(transform, glm::vec3(ANCHO_TORRES_FS, 1.0, ALTURA_TORRES_FS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}