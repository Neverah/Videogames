//Autor: Miguel Torres Estévez

#include "Pala.h"

//Función que dibuja la pala

void Pala::dibujar() {

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	transform = glm::rotate(transform, (float)(Pala::traslacion * ARADIANES), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::translate(transform, glm::vec3(Pala::distancia, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(Pala::sx, Pala::sy, Pala::sz));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, Pala::textura);

	glBindVertexArray(Pala::VAO);
	glDrawArrays(GL_TRIANGLES, 0, Pala::nVertices);
}


//Función que actualiza la posición de la pala según el ángulo de giro

void Pala::actualizarPosicion(double angulo) {

	Pala::traslacion += angulo;
	if (Pala::traslacion > 360.0) Pala::traslacion -= 360.0;
	if (Pala::traslacion < -360.0) Pala::traslacion += 360.0;

	Pala::px = distancia * cos(-Pala::traslacion * ARADIANES);
	Pala::pz = distancia * sin(-Pala::traslacion * ARADIANES);
}
