//Autor: Miguel Torres Estévez

////////////////////////////////////////////////////////////////////////////////////// Definiciones e includes //////////////////////////////////////////////////////////////////////////////////////

#ifndef PELOTA_H
#include "Pelota.h"
#endif // !PELOTA_H

#ifndef PALA_H
#include "Pala.h"
#endif // !PALA_H

#ifndef STEVE_H
#include "Steve.h"
#endif // !STEVE_H

#ifndef TORRE_H
#include "Torre.h"
#endif // !TORRE_H

#ifndef OBSTACULO_H
#include "Obstaculo.h"
#endif // !OBSTACULO_H

#ifndef COCHE_H
#include "Coche.h"
#endif // !COCHE_H

#ifndef UTILIDADES_H
#include "Utilidades.h"
#endif // !UTILIDADES_H

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif // !STB_IMAGE_IMPLEMENTATION

extern GLuint setShaders(const char* nVertx, const char* nFrag);
GLuint shadersPrincipales;
GLuint shadersTexto;

////////////////////////////////////////////////////////////////////////////////// Variables globales y constantes //////////////////////////////////////////////////////////////////////////////////

//Constantes

//Generales
#define FPS_PROGRAMA 60.0	//Número de FPS que va a tener el programa

//VAO
#define VERTICES_PRECISION_CIRCULO 300.0		//Número de vértices de precisión que tendrá el VAO del círculo

//Menú
#define TAMANO_FONDO_MENU 23.2	//Tamaño del fondo del menú
#define OPCIONES_MENU 5			//Número de opciones que tiene el menú					

//Pong Radial
#define V_PALAS_BASE 1.4						//Velocidad base del primer nivel de palas
#define DECREMENTO_VELOCIDAD_NIVEL_PALAS 0.85	//Indica cuánto se reduce la velocidad de giro en cada nivel de palas (los niveles mayores van más lentos)

#define DISTANCIA_ENTRE_PALAS 20.0				//Distancia entre los distintos niveles de palas
#define NUM_NIVELES_PALAS_INICIAL 3				//Número de niveles de palas al iniciar la partida
#define NUM_NIVELES_PALAS_MAX 6					//Número máximo de niveles de palas
#define TAMANO_PALAS_BASE 12					//Tamaño base de las palas del primer nivel
#define FACTOR_ESCALADO_TAMANO_PALAS 2.3		//Ajusta el incremento de tamaño de las palas por nivel

#define INCREMENTO_DISTANCIA_CAMARA_PONG 44.0	//Desplazamiento vertical de la cámara del Pong Radial al añadir o eliminar un nivel de palas

//Flappy Steve
#define TAMANO_FONDO_FS	35.0	//Tamaño del fondo del FS

//Crashing Cars
#define TAMANO_FONDO_CC 60.0	//Tamaño del fondo del CC


//Variables de la ventana

double anchoVentana = 1000;		//Ancho
double alturaVentana = 1000;	//Alto


//Variables de entorno

//Pong Radial
int nNivelesPalas = 0;					//Indica el número de niveles de palas que hay actualmente
int contadorMensajeInfo = 1;			//Indica cuántos rebotes quedan para que desaparezca el mensaje de información
long int contadorTotalPong = 0;			//Indica el número total de rebotes que se han obtenido en la partida del Pong Radial
long int contadorNuevoNivel = 10;		//Indica cuántos rebotes quedan para conseguir un nuevo nivel de palas
long int contadorPelotaNormal = 8;		//Indica cuántos rebotes quedan para que aparezca una nueva pelota normal
long int contadorPelotaEspecial = 20;	//Indica cuántos rebotes quedan para que aparezca una nueva pelota especial (bonus o trampa)

int siguientePelotaEspecial = 0;		//Indicador binario que indica si la siguiente pelota especial va a ser de tipo bonus o tipo trampa
double velocidadNuevasPelotas = 0.3;	//Velocidad que tendrán las nuevas pelotas al crearse (aumenta a medida que el juego avanza)

std::string mensajeInfo = "Start";							//Valor actual del mensaje de información del Pong Radial
glm::vec3 colorMensajeInfo = glm::vec3(1.0f, 1.0f, 1.0f);	//Color actual del mensaje de información del Pong Radial	

//Flappy Steve
long int contadorTotalFS = 0;			//Indica el número total de tuberías que has superado en el Flappy Steve

double desplazamientoFS1 = 0;						//Desplazamiento lateral de los fondos del Flappy Steve
double desplazamientoFS2 = -TAMANO_FONDO_FS;
double desplazamientoFSLuz = 0;						//Desplazamiento actual de la luz del Flappy Steve
double incrementoDesplazamientoFS = 0.1;			//Marca la velocidad de desplazamiento de los elementos del Flappy Steve

double cronometroFS = 0;				//Variable para cronometrar los eventos del Flappy Steve
double avanceCronometroFS = 0;			//Variable para almacenar cuánto ha avanzado el cronómetro dentro del intervalo al pausar

//Shadow Step
long int contadorTotalSS = 0;		//Indica el número total de tuberías que has superado en el Flappy Steve 	

double alturaVisionSS = 3.0;		//Altura a la que está posicionada la cámara respecto del suelo
double distanciaVisionSS = 7.0;		//Distancia a la que mira la cámara respecto de su posición actual
int orientacion = 0;				//Orientación actual de la cámara (suelo o techo)

double intervaloObstaculosSS = 3.0;				//Intervalo de tiempo (en segundos) que hay entre los obstáculos
double velocidadObstaculosSS = 0.5;				//Velocidad de acercamiento de los obstáculos hacia la cámara
double velocidadDesplazamientoSS = 0.2;			//Velocidad de desplazamiento de la cámara
std::vector<double> desplazamientoSeccionesSS;	//Vector de doubles que almacena el desplazamiento actual de cada sección del pasillo

double cronometroSS;				//Variable para cronometrar los eventos del Shadow Step
double avanceCronometroSS = 0;			//Variable para almacenar cuánto ha avanzado el cronómetro dentro del intervalo al pausar

//Crashing Cars
long int contadorTotalCC = 0;		//Indica el número total de coches a los que has chocado en el Crashing Cars

int posicionSiguenteCoche = 0;						//Indica en cual de las 8 posiciones posibles va a salir el próximo coche
double factorEscaladoVelocidadOtrosCoches = 0.75;	//Escalado de la velocidad del resto de coches respecto de la del coche rojo


//Iluminación
float tonalidadFoco[3] = { 1.0f, 1.0f, 0.0f };	//Tonalidad de la luz del foco
float intensidadAmbiente = 1.0;					//Intensidad de la luz ambiente


//Variables de control

//Generales
int juegoSeleccionado = 0;			//Indica qué juego está seleccionado actualmente
int mostrarControles = 0;			//Indicador binario que indica si se deben mostrar los controles
int pausa = 0;						//Indicador binario que indica si el juego está actualmente en pausa	

//Menú
int volverAlMenu = 0;				//Indicador binario que indica si se ha solicitado volver al menú
int opcionMenuSeleccionada = 1;		//Opción seleccionada actualmente del menú (por defecto, el Pong Radial)

//Pong Radial
double sentido = 1.0;				//Indica en qué sentido se mueven actualmente las palas del Pong Radial


//Variables de la cámara

float limiteCerca = 0.1;		//No puedo llamarlos near y far porque esas variables ya están definidas, pero son justo eso
float limiteLejos = 1000.0;
float fovy = 60.0;				//Ángulo del campo de visión

float distanciaCamara = 25;		//Distancia actual de la cámara


//VAOS

GLuint VAOPlano;
GLuint VAOCubo;
GLuint VAOCirculo;
GLuint VAOTexto;
GLuint VBOTexto;


//Texturas

GLuint texturaPalas;
GLuint texturaSuelo;
GLuint texturaLimite;
GLuint texturaLadrillos;
GLuint texturaPelotasTrampa;
GLuint texturaPelotasBonus;
GLuint texturaMenu;
GLuint texturaSteve;
GLuint texturaFondoFS;
GLuint texturaTorresFS;
GLuint texturaMadera;
GLuint texturaSueloSS;
GLuint texturaSueloCC;

GLuint texturaImagenPong;
GLuint texturaImagenFS;
GLuint texturaImagenSS;
GLuint texturaImagenCC;

std::vector<GLuint> texturasCuadros;
std::vector<GLuint> texturasCoches;


//Sistema de guardado

std::vector<long int> records;


//Texto

FT_Library ft;								//Librería
FT_Face face;								//Cara
std::map<char, Character> Characters;		//Mapa de caracteres


//Objetos

//General
Sphere esfera(1.0f, 18, 9);		//Esfera

//Pong Radial
std::vector<Pala> palas;				//Vector que almacena las palas
std::vector<Pelota> pelotasNormales;	//Vector que almacena las pelotas normales
std::vector<Pelota> pelotasBonus;		//Vector que almacena las pelotas bonus
std::vector<Pelota> pelotasTrampa;		//Vector que almacena las pelotas trampa

//Flappy Steve
std::vector<Torre> torres;								//Vector que almacena los pares de torres
Steve steve(0, 0.1f, 0, 2.5, 1.0, 2.5, NULL, NULL);		//Objeto que representa a Steve

//Shadow step
std::vector<Obstaculo> obstaculos;		//Vector que almacena los obstáculos
std::vector<GLuint> cuadros;			//Vector que almacena los índices de los cuadros del pasillo

//Crashing Cars
std::vector<Coche> coches;		//Vector que almacena los coches


//El programa se divide en tres modulos principales: Actualización, dibujo y carga inicial (en ese orden), he separado las funciones correspondientes a cada módulo para hacer más claro el código

//////////////////////////////////////////////////////////////////////////////////////  Declaraciones de funciones //////////////////////////////////////////////////////////////////////////////////////

//Estas funciones son necesarias antes de su declaración, por lo que las declaro antes aquí

void cargaInicialMenu();

void cargaInicialCC();

void cargaInicialSS();

void cargaInicialFS();

void cargaInicialPong();

void sumarContadorPong();

void dibujarTexto(std::string text, float x, float y, float scale, glm::vec3 color);

void gestionTeclado(GLFWwindow* window, int key, int scancode, int action, int mods);

////////////////////////////////////////////////////////////////////////////////////// Funciones de actualización //////////////////////////////////////////////////////////////////////////////////////

//Función que añade un nivel de palas

void anadirNivelPalas() {

	//Se comprueba que el nivel de palas actual no exceda el máximo
	if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) {

		//Se indica que hay un nuevo nivel de palas
		nNivelesPalas++;

		//Se crean e introducen tantas palas en el vector como sean necesarias
		for (int i = 0; i < nNivelesPalas + 2; i++) {
			palas.emplace_back(Pala(0.6, 0.1, TAMANO_PALAS_BASE * (1.0 + nNivelesPalas / FACTOR_ESCALADO_TAMANO_PALAS), nNivelesPalas * DISTANCIA_ENTRE_PALAS, i * (360.0 / (nNivelesPalas + 2.0)), VAOCubo, texturaPalas, 36));
		}

		//Se aleja la cámara para enfocar el nuevo nivel
		distanciaCamara += INCREMENTO_DISTANCIA_CAMARA_PONG;
	}
}


//Función que elimina un nivel de palas

void eliminarNivelPalas() {

	//Se comprueba que el nivel de palas actual no llegue a 0
	if (nNivelesPalas > 1) {

		//Se eliminan las palas del último nivel del vector
		for (int i = 0; i < nNivelesPalas + 2; i++) {
			palas.pop_back();
		}

		//Se indica que hay un nivel de palas menos
		nNivelesPalas--;

		//Se acerca la cámara para que no enfocar espacio vacío
		distanciaCamara -= INCREMENTO_DISTANCIA_CAMARA_PONG;
	}
}


//Función que rota las palas

void rotarPalas() {

	double velocidadNivel = V_PALAS_BASE;	//Se parte de la velocidad base del nivel 0
	int aux = 0;							//Se parte de la posición 0 del vector de palas

	for (int i = 0; i < nNivelesPalas; i++) {	//Recorremos todas las palas
		for (int j = 0; j < i + 3; j++) {

			if (i % 2 == 0) {	//Las palas de niveles alternos girarán en sentido opuesto

				palas[j + aux].actualizarPosicion(sentido * velocidadNivel);
			}
			else {

				palas[j + aux].actualizarPosicion(-sentido * velocidadNivel);
			}

		}
		aux += 3 + i;											//Se avanza al siguiente nivel de palas en el vector
		velocidadNivel *= DECREMENTO_VELOCIDAD_NIVEL_PALAS;		//Se reduce la velocidad de los niveles más lejanos
	}
}


//Función que añade una pelota dado su tipo a su respectivo vector

void anadirPelota(int tipo) {

	switch (tipo) {
	case 0:
		pelotasNormales.emplace_back(Pelota(0, 0, 0, TAMANO_PELOTAS_PONG, velocidadNuevasPelotas, texturaPalas));
		break;

	case 1:
		pelotasBonus.emplace_back(Pelota(0, 0, 0, TAMANO_PELOTAS_PONG, velocidadNuevasPelotas, texturaPelotasBonus));
		break;

	case 2:
		pelotasTrampa.emplace_back(Pelota(0, 0, 0, TAMANO_PELOTAS_PONG, velocidadNuevasPelotas, texturaPelotasTrampa));
		break;
	}

}


//Función que elimina una pelota del array indicado

void eliminarPelota(std::vector<Pelota>& vectorPelotas, int posicion) {
	if (posicion == -1) vectorPelotas.pop_back();							//Si se indica la posición -1, se elimina la última
	else vectorPelotas.erase(vectorPelotas.begin() + posicion);
}


//Función que mueve las pelotas

void moverPelotas() {

	for (int i = 0; i < pelotasNormales.size(); i++) {
		pelotasNormales[i].actualizarPosicion();
	}

	for (int i = 0; i < pelotasBonus.size(); i++) {
		pelotasBonus[i].actualizarPosicion();
	}

	for (int i = 0; i < pelotasTrampa.size(); i++) {
		pelotasTrampa[i].actualizarPosicion();
	}
}


//Función que comprueba si una pelota se ha salido del límite

int comprobarSalidaLimite(Pelota pelota) {
	return pelota.distanciaAlCentro >= (nNivelesPalas + 1.0) * DISTANCIA_ENTRE_PALAS;
}


//Función que elimina el par de torres más antiguo en el FS

void eliminarTorresFS() {
	if (torres.size() > 0) torres.erase(torres.begin());
}


//Función que añade un par de torres en el FS

void anadirTorresFS(double alturaHueco) {
	torres.emplace_back(15.0, alturaHueco, VAOPlano, texturaTorresFS);
}


//Función que mueve las torres en el FS

void moverTorresFS() {
	for (int i = 0; i < torres.size(); i++) {
		torres[i].desplazamiento += incrementoDesplazamientoFS;
	}
}


//Función que gestiona la derrota del Pong Radial

void derrotaPong(int opcion) {	//La opción es para diferenciar si ha sido llamada desde el menú (no sonará el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaPong.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[0] < contadorTotalPong) records[0] = contadorTotalPong;		//Si la puntuación obtenida supera el récord, se actualiza el récord

	//Vaciamos los vectores

	while (palas.size() > 0) {
		palas.pop_back();
		//printf("Pala eliminada\n");
	}

	while (pelotasNormales.size() > 0) {
		pelotasNormales.pop_back();
		//printf("Pelota normal eliminada\n");
	}

	while (pelotasBonus.size() > 0) {
		pelotasBonus.pop_back();
		//printf("Pelota bonus eliminada\n");
	}

	while (pelotasTrampa.size() > 0) {
		pelotasTrampa.pop_back();
		//printf("Pelota trampa eliminada\n");
	}

	cargaInicialMenu();		//Se vuelve al menú
}


//Función que gestiona la derrota del Flappy Steve

void derrotaFS(int opcion) {	//La opción es para diferenciar si ha sido llamada desde el menú (no sonará el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaFS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[1] < contadorTotalFS) records[1] = contadorTotalFS;		//Si la puntuación obtenida supera el récord, se actualiza el récord

	//Vaciamos los vectores

	while (torres.size() > 0) torres.pop_back();

	cargaInicialMenu();		//Se vuelve al menú
}


//Función que gestiona la derrota del Shadow Step

void derrotaSS(int opcion) {	//La opción es para diferenciar si ha sido llamada desde el menú (no sonará el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaSS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[2] < contadorTotalSS) records[2] = contadorTotalSS;		//Si la puntuación obtenida supera el récord, se actualiza el récord

	//Vaciamos los vectores

	while (obstaculos.size() > 0) obstaculos.pop_back();
	while (cuadros.size() > 0) cuadros.pop_back();

	cargaInicialMenu();		//Se vuelve al menú
}


//Función que gestiona la derrota del Crashing Cars

void derrotaCC(int opcion) {	//La opción es para diferenciar si ha sido llamada desde el menú (no sonará el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaCC.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[3] < contadorTotalCC) records[3] = contadorTotalCC;		//Si la puntuación obtenida supera el récord, se actualiza el récord

	//Vaciamos los vectores

	while (coches.size() > 0) coches.pop_back();

	cargaInicialMenu();		//Se vuelve al menú
}


//Función que gestiona la salida de una pelota normal fuera del límite

void gestionarSalidaPelotaNormalLimite() {

	if (palas.size() < 4) derrotaPong(1);	//Si solo quedaba el último nivel de palas, se pierde la partida
	else {									//Si había mas niveles, se devuelven todas las pelotas al centro, se reduce tanto su velocidad como la de las nuevas pelotas y se elimina el último nivel de palas

		for (int i = 0; i < pelotasNormales.size(); i++) {

			pelotasNormales[i].px = 0.0;
			pelotasNormales[i].pz = 0.0;
			pelotasNormales[i].velocidad *= 0.8;
		}

		for (int i = 0; i < pelotasBonus.size(); i++) {

			pelotasBonus[i].px = 0.0;
			pelotasBonus[i].pz = 0.0;
			pelotasBonus[i].velocidad *= 0.8;
		}

		for (int i = 0; i < pelotasTrampa.size(); i++) {

			pelotasTrampa[i].px = 0.0;
			pelotasTrampa[i].pz = 0.0;
			pelotasTrampa[i].velocidad *= 0.8;
		}

		velocidadNuevasPelotas *= 0.85;
		eliminarNivelPalas();
	}
}


//Función que comprueba las colisiones de una pelota con las palas

int comprobarColisionPelota(Pelota* pelota, std::vector<Pala>& palas) {

	for (Pala pala : palas) {
		if (pelota->comprobarColision(pala, esfera)) {
			return true;
		}
	}
	return false;
}


//Función que aplica la bonificación de las pelotas bonus

void accionPelotaBonus() {

	char mensaje[50];

	switch (rand() % 3) {

	case 0:			//Reducción de velocidad de las pelotas

		for (int i = 0; i < pelotasNormales.size(); i++) pelotasNormales[i].velocidad *= 0.8;

		for (int i = 0; i < pelotasBonus.size(); i++) pelotasBonus[i].velocidad *= 0.8;

		for (int i = 0; i < pelotasTrampa.size(); i++) pelotasTrampa[i].velocidad *= 0.8;

		velocidadNuevasPelotas *= 0.8;
		mensajeInfo = "Reduccion de velocidad de las pelotas";
		break;

	case 1:			//Nivel de palas extra > Se elimina una pelota > Reducción de velocidad de las pelotas

		if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) {	//Si algún bonus no es posible porque ya se ha alcanzado el máximo o el mínimo de entidades posible, se asigna alguno de los otros

			anadirNivelPalas();
			mensajeInfo = "Nivel de palas extra";
		}
		else if (pelotasNormales.size() > 1) {

			pelotasNormales.pop_back();
			mensajeInfo = "Se elimina una pelota";
		}
		else {

			for (int i = 0; i < pelotasNormales.size(); i++) pelotasNormales[i].velocidad *= 0.75;

			for (int i = 0; i < pelotasBonus.size(); i++) pelotasBonus[i].velocidad *= 0.75;

			for (int i = 0; i < pelotasTrampa.size(); i++) pelotasTrampa[i].velocidad *= 0.75;

			velocidadNuevasPelotas *= 0.75;
			mensajeInfo = "Reduccion de velocidad de las pelotas";
		}
		break;

	case 2:			//Se elimina una pelota > Nivel de palas extra > Reducción de velocidad de las pelotas

		if (pelotasNormales.size() > 1) {	//Lo mismo que antes, pero cambiando la prioridad

			pelotasNormales.pop_back();
			mensajeInfo = "Se elimina una pelota";
		}
		else if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) {

			anadirNivelPalas();
			mensajeInfo = "Nivel de palas extra";
		}
		else {

			for (int i = 0; i < pelotasNormales.size(); i++) pelotasNormales[i].velocidad *= 0.8;

			for (int i = 0; i < pelotasBonus.size(); i++) pelotasBonus[i].velocidad *= 0.8;

			for (int i = 0; i < pelotasTrampa.size(); i++) pelotasTrampa[i].velocidad *= 0.8;

			velocidadNuevasPelotas *= 0.8;
			mensajeInfo = "Reduccion de velocidad de las pelotas";
		}
		break;

	default:
		printf("Error con la pelota bonus\n");
		break;
	}
	contadorMensajeInfo = 3.0 * pelotasNormales.size();		//Aumentamos el contador del mensaje de información para que se imprima
	colorMensajeInfo = glm::vec3(0.0f, 1.0f, 0.0f);			//Asignamos el color verde al mensaje de información
}


//Función que realiza la penalización de las pelotas trampa (mismo funcionamiento que las de bonus, pero con penalizaciones)

void accionPelotaTrampa() {

	switch (rand() % 3) {

	case 0:

		for (int i = 0; i < pelotasNormales.size(); i++) pelotasNormales[i].velocidad *= 1.1;

		for (int i = 0; i < pelotasBonus.size(); i++) pelotasBonus[i].velocidad *= 1.1;

		for (int i = 0; i < pelotasTrampa.size(); i++) pelotasTrampa[i].velocidad *= 1.1;

		velocidadNuevasPelotas *= 1.1;
		mensajeInfo = "Incremento de velocidad de las pelotas";
		break;

	case 1:

		if (palas.size() < 4) derrotaPong(1);	//Si pierdes un nivel de palas y sólo te quedaba el último, pierdes automáticamente la partida
		else eliminarNivelPalas();
		mensajeInfo = "Se suprime un nivel de palas";
		break;

	case 2:

		anadirPelota(0);
		mensajeInfo = "Se suma una pelota";
		break;

	default:
		printf("Error con la pelota trampa\n");
		break;
	}
	contadorMensajeInfo = 3.0 * pelotasNormales.size();
	colorMensajeInfo = glm::vec3(1.0f, 0.0f, 0.0f);			//En el caso de las penalizaciones, el mensaje de información aparecerá en rojo
}


//Función que comprueba las colisiones de todas las pelotas

void comprobarColisionPelotas() {


	//Pelotas normales
	for (int i = 0; i < pelotasNormales.size(); i++) {

		//Cuando una pelota normal rebota, se aumenta el contador de rebotes y se incrementa ligeramente la velocidad de las nuevas pelotas
		if (comprobarColisionPelota(&pelotasNormales[i], palas)) {

			velocidadNuevasPelotas += INCREMENTO_VELOCIDAD_PELOTAS / (pelotasNormales.size() * 2.0);
			sumarContadorPong();
		}

		//Cuando una pelota normal sale del límite, se elimina y se llama a la función que gestiona las acciones correspondientes
		if (comprobarSalidaLimite(pelotasNormales[i])) {

			if (pelotasNormales.size() > 1) eliminarPelota(pelotasNormales, -1);
			gestionarSalidaPelotaNormalLimite();
		}
	}

	//Pelotas bonus
	for (int i = 0; i < pelotasBonus.size(); i++) {

		//Cuando una pelota bonus rebota 8 veces, se aplica el bonus y se elimina la pelota
		if (comprobarColisionPelota(&pelotasBonus[i], palas)) {

			if (pelotasBonus[i].contadorRebotes >= 8) {
				accionPelotaBonus();
				eliminarPelota(pelotasBonus, i);
			}
		}
		else {	//El else es necesario, ya que podría haberse eliminado la pelota antes de comprobar su salida

			//Si una pelota bonus sale del límite, simplemente desaparece
			if (comprobarSalidaLimite(pelotasBonus[i])) {
				eliminarPelota(pelotasBonus, i);
			}
		}
	}

	//Pelotas trampa
	for (int i = 0; i < pelotasTrampa.size(); i++) {

		//Cuando una pelota bonus rebota 5 veces, se aplica la penalización y se elimina la pelota
		if (comprobarColisionPelota(&pelotasTrampa[i], palas)) {

			if (pelotasTrampa[i].contadorRebotes >= 5) {
				accionPelotaTrampa();
				eliminarPelota(pelotasTrampa, i);
			}
		}
		else {	//El else es necesario, ya que podría haberse eliminado la pelota antes de comprobar su salida

			//Si una pelota trampa sale del límite, simplemente desaparece
			if (comprobarSalidaLimite(pelotasTrampa[i])) {
				eliminarPelota(pelotasTrampa, i);
			}
		}
	}
}


//Función que suma un rebote al contador y realiza las acciones correspondientes

void sumarContadorPong() {

	int auxColor = 0;	//Variable auxiliar para asegurarnos de que haya luz

	contadorTotalPong++;			//Se incrementa el contador total de rebotes
	contadorPelotaNormal--;			//Se reducen los contadores de los nuevos elementos
	contadorPelotaEspecial--;
	if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) contadorNuevoNivel--;	//El contador para el próximo nivel de palas no se modifica si ya se ha alcanzado el número máximo de niveles de palas
	if (contadorMensajeInfo > 0) contadorMensajeInfo--;					//Se reducen los rebotes restantes del mensaje de información
	intensidadAmbiente *= 0.995;										//Se reduce la intensidad de la luz ambiente, de forma que cada vez el exterior círculo de palas está más oscuro

	//Cuando los contadores de los nuevos elementos llegan a 0, se añade el elemento a la partida y se asigna un nuevo valor al contador, dependiente del número actual de pelotas
	if (!contadorNuevoNivel) {

		anadirNivelPalas();
		contadorNuevoNivel = 12 * pelotasNormales.size();
	}

	if (!contadorPelotaNormal) {

		anadirPelota(0);
		contadorPelotaNormal = 8 * pelotasNormales.size();
	}

	if (!contadorPelotaEspecial) {

		if (siguientePelotaEspecial) {	//El tipo de las pelotas especiales se alterna

			anadirPelota(1);
			siguientePelotaEspecial = !siguientePelotaEspecial;
		}
		else {

			anadirPelota(2);
			siguientePelotaEspecial = !siguientePelotaEspecial;
		}

		contadorPelotaEspecial = 24 * pelotasNormales.size();
	}

	while (!auxColor) {						//Por cada rebote, el color de la luz del foco cambia (se asegura que haya algún color)
		for (int i = 0; i < 3; i++) {

			float intensidadColor = (rand() % 4) / 2.0;
			tonalidadFoco[i] = intensidadColor;
			if (intensidadColor > 0) auxColor = 1;
		}
	}
}


//Función que mueve y alterna los planos del fondo del FS

void actualizarPosicionFondo() {

	//Los desplazamientos van aumentando y, en cuanto salen del límite, vuelven a su posición inicial, de forma que se mueven en bucle

	desplazamientoFS1 += incrementoDesplazamientoFS;
	if (desplazamientoFS1 > TAMANO_FONDO_FS) desplazamientoFS1 -= TAMANO_FONDO_FS;
	desplazamientoFS2 += incrementoDesplazamientoFS;
	if (desplazamientoFS2 > 0) desplazamientoFS2 -= TAMANO_FONDO_FS;
	desplazamientoFSLuz += incrementoDesplazamientoFS / 10.0;
	if (desplazamientoFSLuz > 40.0) desplazamientoFSLuz -= TAMANO_FONDO_FS + 12.0;
}


//Función que elige una textura de cuadro aleatoria y devuelve el índice

GLuint texturaCuadroAleatoria() {

	return texturasCuadros[rand() % 16];
}


//Función que actualiza la posición de las secciones del pasillo y las alterna

void actualizarPosicionPasillo() {

	double limiteSecciones = LARGO_SUELO_SS / 2.0;

	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS; i++) {		//Aumentamos el desplazamieto de las secciones del pasillo y, cuando dejan de ser visibles, las devolvemos a la posición más lejana y cambiamos sus cuadros

		desplazamientoSeccionesSS[i] += velocidadDesplazamientoSS;
		if (desplazamientoSeccionesSS[i] > limiteSecciones) {
			desplazamientoSeccionesSS[i] -= distanciaMaximaSS;
			cuadros[2 * i] = texturaCuadroAleatoria();
			cuadros[2 * i + 1] = texturaCuadroAleatoria();
		}
	}

	for (int i = 0; i < obstaculos.size(); i++) {			//Desplazamos los obstáculos y los rotamos

		obstaculos[i].desplazamiento += velocidadObstaculosSS;
		obstaculos[i].rotacion += 8.0;

		if (obstaculos[i].desplazamiento >= distanciaMaximaSS) {	//Cuando los obstáculos llegan a la posición de la cámara, se eliminan si están en el otro nivel o se termina la partida si están ene l mismo

			if (obstaculos[i].orientacion == orientacion) derrotaSS(1);
			else {

				obstaculos.erase(obstaculos.begin());

				if (velocidadObstaculosSS <= 7.0) velocidadObstaculosSS += 0.05;	//Cuando se elimina un obstáculo, se aumenta la velocidad y se reduce el intervalo para los nuevos obstáculos
				if (intervaloObstaculosSS >= 0.5) intervaloObstaculosSS -= 0.05;

				contadorTotalSS++;
			}
		}
	}
}


//Función que añade un nuevo coche al mapa

void nuevoCoche() {

	switch (posicionSiguenteCoche) {

	case 0:

		coches.emplace_back(20.0, 20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 1:

		coches.emplace_back(0, 20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 2:

		coches.emplace_back(0, -20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 3:

		coches.emplace_back(20.0, -20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 4:

		coches.emplace_back(-20.0, -20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 5:

		coches.emplace_back(-20.0, 0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 6:

		coches.emplace_back(20.0, 0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;

	case 7:

		coches.emplace_back(-20.0, 20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
		break;
	}

	posicionSiguenteCoche++;
	if (posicionSiguenteCoche >= 8) posicionSiguenteCoche -= 8;
	if (factorEscaladoVelocidadOtrosCoches < VELOCIDAD_MAXIMA_COCHES) factorEscaladoVelocidadOtrosCoches += 0.025;
}


//Función que comprueba las colisiones de un coche con el resto en el Crashing Cars

void comprobarColisionesCoches(Coche coche, int pos) {

	for (int i = 0; i < coches.size(); i++) {
		if (i != pos) {

			switch (coche.comprobarColision(coches[i])) {

			case 1:		//Colisión lateral

				if (!i) derrotaCC(1);	//Si le chocan al coche rojo, se pierde la partida
				else {

					coches.erase(coches.begin() + i);
					contadorTotalCC++;
					nuevoCoche();
				}
				break;

			case 2:		//Colisión frontal

				coches[i].movimiento = 1;
				coches[i].velocidad = -VELOCIDAD_REBOTE;
				coches[pos].movimiento = 1;
				coches[pos].velocidad = -VELOCIDAD_REBOTE;
				break;

			case 3:		//Colisión estática

				coches[pos].movimiento = 1;
				coches[pos].velocidad = -VELOCIDAD_REBOTE;
				break;

			default:
				break;
			}
		}
	}
}


//Función de actualización del Pong Radial

void actualizacionPong() {

	if (volverAlMenu) {
		derrotaPong(0);
	}
	else {

		if (!pausa) {

			rotarPalas();		//Se rotan las palas

			moverPelotas();		//Se mueven las pelotas

			comprobarColisionPelotas();		//Se comprueban las colisiones
		}
	}
}


//Función de actualización del Flappy Steve

void actualizacionFS() {

	if (volverAlMenu) {
		derrotaFS(0);
	}
	else {

		if (!pausa) {

			if (glfwGetTime() - 3 >= cronometroFS) {	//Cada 3 segundos, se añade un nuevo par de torres de altura aleatoria, se elimina el par de torres que ha salido del límite de visión y se aumenta el contador
				cronometroFS = glfwGetTime();

				contadorTotalFS++;

				anadirTorresFS(8.0 - rand() % 16);

				if (torres.size() > 3) {
					eliminarTorresFS();
				}
			}

			for (Torre torre : torres) {								//Se comprueban las colisiones
				if (steve.comprobarColision(torre)) derrotaFS(1);
			}

			moverTorresFS();					//Se mueven las torres
			actualizarPosicionFondo();			//Se mueve el fondo
			steve.caer();						//Se gestiona la caída
		}
	}
}


//Función de actualización del Shadow Step

void actualizacionSS() {

	if (volverAlMenu) {
		derrotaSS(0);
	}
	else {

		if (!pausa) {

			if (glfwGetTime() - intervaloObstaculosSS >= cronometroSS) {		//Cada vez que se cumple el intervalo, se añade un nuevo obstáculo

				cronometroSS = glfwGetTime();
				obstaculos.emplace_back(rand() % 2, VAOCubo, texturaMadera);	//La orientación del obstáculo será aleatoria
			}

			actualizarPosicionPasillo();	//Se actualiza el desplazamiento de las secciones del pasillo
		}
	}
}


//Función de actualización del Crushing Cars

void actualizacionCC() {

	if (volverAlMenu) {
		derrotaCC(0);
	}
	else {

		if (!pausa) {

			for (int i = 0; i < coches.size(); i++) coches[i].actualizarPosicion();
			for (int i = 0; i < coches.size(); i++) comprobarColisionesCoches(coches[i], i);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////// Funciones de dibujo //////////////////////////////////////////////////////////////////////////////////////

//Función que dibuja la hitbbox de las palas (solo para comprobaciones)

void dibujarHitboxPala(Pala pala) {

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	double divisiones = 30;	//Divisiones
	double divisionesLaterales = divisiones * 0.2;

	double incrementoX = (pala.sz * cos((pala.traslacion + 90.0) * ARADIANES) / ((double)divisiones * 2.0));
	double incrementoZ = (pala.sz * sin((pala.traslacion - 90.0) * ARADIANES) / ((double)divisiones * 2.0));

	double circuloDerechoX = pala.px;
	double circuloDerechoZ = pala.pz;

	double circuloIzquierdoX = pala.px;
	double circuloIzquierdoZ = pala.pz;

	//Dividimos el área de la pala en tantos círculos hacia cada lateral como indique la variable de divisiones (es más fácil usar círculos, ya que la pala va a estar rotando)

	for (int i = 0; i < divisiones - divisionesLaterales; i++) {

		//Repartimos los círculos de forma uniforme a través de la pala

		circuloDerechoX += incrementoX;
		circuloDerechoZ += incrementoZ;

		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(circuloDerechoX, 0.0, circuloDerechoZ));
		transform = glm::scale(transform, glm::vec3(0.6, 0.6, 0.6));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, texturaPalas);
		esfera.draw();

		circuloIzquierdoX -= incrementoX;
		circuloIzquierdoZ -= incrementoZ;

		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(circuloIzquierdoX, 0.0, circuloIzquierdoZ));
		transform = glm::scale(transform, glm::vec3(0.6, 0.6, 0.6));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, texturaPalas);
		esfera.draw();
	}

	for (int i = 0; i < divisionesLaterales; i++) {

		circuloDerechoX += incrementoX;
		circuloDerechoZ += incrementoZ;

		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(circuloDerechoX, 0.0, circuloDerechoZ));
		transform = glm::scale(transform, glm::vec3(0.6, 0.6, 0.6));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, texturaLimite);
		esfera.draw();

		circuloIzquierdoX -= incrementoX;
		circuloIzquierdoZ -= incrementoZ;

		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(circuloIzquierdoX, 0.0, circuloIzquierdoZ));
		transform = glm::scale(transform, glm::vec3(0.6, 0.6, 0.6));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, texturaLimite);
		esfera.draw();
	}
}


//Función que dibuja la hitbbox de los coches (solo para comprobaciones)

void dibujarHitboxCoche(Coche coche) {

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	double moduloXAncho = ANCHO_COCHE / 2.0 * -cos((coche.giro + 90.0) * ARADIANES);
	double moduloXLargo = LARGO_COCHE / 2.0 * cos(coche.giro * ARADIANES);

	double moduloZAncho = ANCHO_COCHE / 2.0 * sin((coche.giro + 90.0) * ARADIANES);
	double moduloZLargo = LARGO_COCHE / 2.0 * -sin(coche.giro * ARADIANES);

	double pxFrontalIzquierdo = coche.px - moduloXAncho + moduloXLargo;
	double pzFrontalIzquierdo = coche.pz - moduloZAncho + moduloZLargo;

	double pxFrontalDerecho = coche.px + moduloXAncho + moduloXLargo;
	double pzFrontalDerecho = coche.pz + moduloZAncho + moduloZLargo;

	double pxTraseroIzquierdo = coche.px - moduloXAncho - moduloXLargo;
	double pzTraseroIzquierdo = coche.pz - moduloZAncho - moduloZLargo;

	double pxTraseroDerecho = coche.px + moduloXAncho - moduloXLargo;
	double pzTraseroDerecho = coche.pz + moduloZAncho - moduloZLargo;

	//Dibujamos esferas en las esquinas de la hitbox

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(pxFrontalIzquierdo, 0.0, pzFrontalIzquierdo));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaLimite);
	esfera.draw();

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(pxFrontalDerecho, 0.0, pzFrontalDerecho));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaLimite);
	esfera.draw();

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(pxTraseroDerecho, 0.0, pzTraseroDerecho));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaLimite);
	esfera.draw();

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(pxTraseroIzquierdo, 0.0, pzTraseroIzquierdo));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaLimite);
	esfera.draw();

	//Dibujamos el resto de la hitbox

	// /*

	double divisiones = 10;		//Número de divisiones a realizar
	double distancia;			//Variable para almacenar la distancia

	double incrementoX = moduloXLargo / (divisiones * 2.0);
	double incrementoZ = moduloZLargo / (divisiones * 2.0);

	double circuloDerechoX = coche.px;
	double circuloDerechoZ = coche.pz;

	double circuloIzquierdoX = coche.px;
	double circuloIzquierdoZ = coche.pz;

	for (int i = 0; i < divisiones; i++) {	//Dividimos el área de la pala en tantos círculos hacia cada lateral como indique la variable de divisiones (es más fácil usar círculos, ya que la pala va a estar rotando)

		//Repartimos los círculos de forma uniforme a través de la pala y comprobamos si han colisionado con las esquinas del coche

		circuloDerechoX += incrementoX;
		circuloDerechoZ += incrementoZ;

		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(circuloDerechoX, 0.0, circuloDerechoZ));
		transform = glm::scale(transform, glm::vec3(ANCHO_COCHE / 2.0, ANCHO_COCHE / 2.0, ANCHO_COCHE / 2.0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, texturaPalas);
		esfera.draw();

		circuloIzquierdoX -= incrementoX;
		circuloIzquierdoZ -= incrementoZ;

		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(circuloIzquierdoX, 0.0, circuloIzquierdoZ));
		transform = glm::scale(transform, glm::vec3(ANCHO_COCHE / 2.0, ANCHO_COCHE / 2.0, ANCHO_COCHE / 2.0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, texturaPalas);
		esfera.draw();
	}

	// */
}


//Función que dibuja el fondo exterior del Pong Radial

void dibujarFondoPong() {

	glDisable(GL_CULL_FACE);

	double tamano = (nNivelesPalas + 1.0) * DISTANCIA_ENTRE_PALAS * 2.5;

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader
	transform = glm::translate(transform, glm::vec3(0.0f, -0.5f, 0.0f));
	transform = glm::scale(transform, glm::vec3(tamano, 1.0, tamano));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, texturaLadrillos);

	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}


//Función que dibuja el suelo circular y la marca del límite del Pong Radial

void dibujarSueloPong() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	double tamano = (nNivelesPalas + 1.0) * DISTANCIA_ENTRE_PALAS;

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader

	//Circulo interior
	transform = glm::translate(transform, glm::vec3(0, -0.2f, 0.0));
	transform = glm::rotate(transform, (float)(90.0 * ARADIANES), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(tamano, tamano, tamano));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, texturaSuelo);

	glBindVertexArray(VAOCirculo);
	glDrawArrays(GL_TRIANGLE_FAN, 0, VERTICES_PRECISION_CIRCULO);

	tamano *= 1.02;

	//Circulo exterior
	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(0, -0.3f, 0.0));
	transform = glm::rotate(transform, (float)(90.0 * ARADIANES), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(tamano, tamano, tamano));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, texturaLimite);

	glBindVertexArray(VAOCirculo);
	glDrawArrays(GL_TRIANGLE_FAN, 0, VERTICES_PRECISION_CIRCULO);
}


//Función que dibuja el fondo del Flappy Steve

void dibujarFondoFS() {

	glDisable(GL_CULL_FACE);

	//Plano 1

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader
	transform = glm::translate(transform, glm::vec3(-desplazamientoFS1, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(TAMANO_FONDO_FS, 1.0, TAMANO_FONDO_FS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, texturaFondoFS);

	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Plano 2

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(-desplazamientoFS2, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(TAMANO_FONDO_FS, 1.0, TAMANO_FONDO_FS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, texturaFondoFS);

	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}


//Función que dibuja una sección del pasillo dada la distancia

void dibujarSeccionPasillo(int posicion) {

	double distancia = desplazamientoSeccionesSS[posicion];
	double mitadAncho = ANCHO_SUELO_SS / 2.0;	//Lo calculamos ahora para calcularlo solo una vez
	glm::mat4 transformAux = glm::mat4();

	//Suelo

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader
	transform = glm::translate(transform, glm::vec3(-distancia, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(LARGO_SUELO_SS, 1.0, ANCHO_SUELO_SS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaSueloSS);
	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Techo

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(-distancia, ANCHO_SUELO_SS, 0.0f));
	transform = glm::rotate(transform, (float)(180.0 * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(LARGO_SUELO_SS, 1.0, ANCHO_SUELO_SS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaLadrillos);
	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Pared derecha

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(-distancia, mitadAncho, mitadAncho));
	if (orientacion) transform = glm::rotate(transform, (float)(270.0 * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	else transform = glm::rotate(transform, (float)(-90.0 * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	transformAux = transform;
	transform = glm::scale(transform, glm::vec3(LARGO_SUELO_SS, 1.0, ANCHO_SUELO_SS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaMadera);
	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	transformAux = glm::translate(transformAux, glm::vec3(0.0, 0.1, 0.8));
	transformAux = glm::rotate(transformAux, (float)(180.0 * ARADIANES), glm::vec3(0.0f, 1.0f, 0.0f));
	transformAux = glm::scale(transformAux, glm::vec3(8.0, 1.0, 2.0));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
	glBindTexture(GL_TEXTURE_2D, cuadros[2 * posicion]);
	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Pared izquierda

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(-distancia, mitadAncho, -mitadAncho));
	if (orientacion) transform = glm::rotate(transform, (float)(90.0 * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	else transform = glm::rotate(transform, (float)(90.0 * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	transformAux = transform;
	transform = glm::scale(transform, glm::vec3(LARGO_SUELO_SS, 1.0, ANCHO_SUELO_SS));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaMadera);
	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	transformAux = glm::translate(transformAux, glm::vec3(0.0, 0.1, -0.8));
	transformAux = glm::scale(transformAux, glm::vec3(8.0, 1.0, 2.0));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
	glBindTexture(GL_TEXTURE_2D, cuadros[2 * posicion + 1]);
	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


//Función que dibuja todas las secciones del pasillo

void dibujarPasilloSS() {

	glDisable(GL_CULL_FACE);

	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS; i++) dibujarSeccionPasillo(i);

	glEnable(GL_CULL_FACE);
}


//Función que dibuja el fondo del Crashing Cars

void dibujarFondoCC() {

	glDisable(GL_CULL_FACE);

	//Plano 1

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(TAMANO_FONDO_CC - 4.0, 1.0f, TAMANO_FONDO_CC - 4.0));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaSueloCC);

	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(0.0f, -0.1f, 0.0f));
	transform = glm::scale(transform, glm::vec3(TAMANO_FONDO_CC, 1.0f, TAMANO_FONDO_CC));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, texturaLimite);

	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}


//Función que dibuja una imagen en un plano con una textura, tamaño y coordenadas dadas

void dibujarImagen(GLuint textura, double ancho, double alto, double px, double py, double pz) {

	glDisable(GL_CULL_FACE);

	glm::mat4 transform = glm::mat4();
	unsigned int transformLoc = glGetUniformLocation(shadersPrincipales, "model");	//Se busca en el shader
	transform = glm::translate(transform, glm::vec3(px, py, pz));
	transform = glm::scale(transform, glm::vec3(ancho, 1.0, alto));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindTexture(GL_TEXTURE_2D, textura);

	glBindVertexArray(VAOPlano);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_CULL_FACE);
}


//Función que dibuja una cadena de texto en pantalla

void dibujarTexto(std::string text, float x, float y, float scale, glm::vec3 color) {

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Configuramos los shaders del texto
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(anchoVentana), 0.0f, static_cast<float>(alturaVentana));
	glUseProgram(shadersTexto);
	glUniformMatrix4fv(glGetUniformLocation(shadersTexto, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(glGetUniformLocation(shadersTexto, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAOTexto);

	//Iteramos todos los caracteres de la cadena dada
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		//Leemos los datos del caracter actual del mapa de caracteres
		Character ch = Characters[*c];

		//Calculamos las coordenadas y tamaño del caracter
		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		//Reasignamos el valor de VBOTexto para cada caracter
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		//Asignamos la textura del caracter
		glBindTexture(GL_TEXTURE_2D, ch.IDTextura);

		//Asignamos los nuevos vértices a VBOTexto
		glBindBuffer(GL_ARRAY_BUFFER, VBOTexto);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Dibujamos el plano con el caracter
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Nos desplazamos en el eje X para escribir el siguiente caracter
		x += (ch.Advance >> 6) * scale;
	}

	//Desvinculamos los VAOs y las texturas y volvemos a usar los shaders principales
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(shadersPrincipales);
}


//Función de iluminación del Pong Radial

void iluminacionPong() {

	//Color de la luz del foco
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, tonalidadFoco[0], tonalidadFoco[1], tonalidadFoco[2]); //La tonalidad será la indicada por el vector de tonalidadFoco, que se habrá generado aleatoriamente con cada rebote

	//Color de la luz ambiental
	unsigned int ambientColorLoc = glGetUniformLocation(shadersPrincipales, "ambientColor");
	glUniform3f(ambientColorLoc, 1.0f, 1.0f, 1.0f);

	//Intensidad de la luz ambiental
	unsigned int ambientIntensityLoc = glGetUniformLocation(shadersPrincipales, "ambientIntensity");
	glUniform1f(ambientIntensityLoc, intensidadAmbiente); //La intensidad será la indicada por intensidadAmbiente, que disminuirá con cada rebote

	//Posición de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 0.0, distanciaCamara, 0.0);

	//Posición a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, 0.0, 0.0, 0.0);

	//Posición de la cámara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0, distanciaCamara, 0.0);

	//Ángulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 21.5 + 0.3 * nNivelesPalas); //El ángulo de apertura del foco varía con el número de niveles de palas
}


//Función de iluminación del Flappy Steve

void iluminacionFS() {

	//Color de la luz del foco
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, 25.0f, 1.0f, 0.0f);

	//Color de la luz ambiental
	unsigned int ambientColorLoc = glGetUniformLocation(shadersPrincipales, "ambientColor");
	glUniform3f(ambientColorLoc, 0.8f, 0.8f, 0.8f);

	//Intensidad de la luz ambiental
	unsigned int ambientIntensityLoc = glGetUniformLocation(shadersPrincipales, "ambientIntensity");
	glUniform1f(ambientIntensityLoc, intensidadAmbiente);

	//Posición de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 14.0 - desplazamientoFSLuz, distanciaCamara, -14.0); //La luz se desplazará progresivamente hacia la izquierda según la variable de desplazamientoFSLuz

	//Posición a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, 14.0 - desplazamientoFSLuz, 0.0, -14.0);

	//Posición de la cámara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0, distanciaCamara, 0.0);

	//Ángulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 4.0);
}


//Función de iluminación del Shadow Step

void iluminacionSS() {

	//Según la orientación, asignamos la altura de la cámara y la altura a la que mira la luz
	float alturaCamara = alturaVisionSS;
	float alturaLuz = 0.0f;

	if (orientacion != 0) {

		alturaCamara = ANCHO_SUELO_SS - alturaVisionSS;
		alturaLuz = ANCHO_SUELO_SS;
	}

	//Color de la luz del foco
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	//Color de la luz ambiental
	unsigned int ambientColorLoc = glGetUniformLocation(shadersPrincipales, "ambientColor");
	glUniform3f(ambientColorLoc, 1.0f, 1.0f, 1.0f);

	//Intensidad de la luz ambiental
	unsigned int ambientIntensityLoc = glGetUniformLocation(shadersPrincipales, "ambientIntensity");
	glUniform1f(ambientIntensityLoc, intensidadAmbiente);

	//Posición de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 0.0f, alturaVisionSS, 0.0f);

	//Posición a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, distanciaVisionSS * 3.0, alturaLuz, 0.0f); //La luz mira 3 veces más lejos de lo que mira la cámara y a la altura indicada

	//Posición de la cámara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0f, distanciaCamara, 0.0f);

	//Ángulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 8.0f);
}


//Función de iluminación del Crashing Cars

void iluminacionCC() {

	//Color de la luz del foco
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	//Color de la luz ambiental
	unsigned int ambientColorLoc = glGetUniformLocation(shadersPrincipales, "ambientColor");
	glUniform3f(ambientColorLoc, 1.0f, 1.0f, 1.0f);

	//Intensidad de la luz ambiental
	unsigned int ambientIntensityLoc = glGetUniformLocation(shadersPrincipales, "ambientIntensity");
	glUniform1f(ambientIntensityLoc, intensidadAmbiente);

	//Posición de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, coches[0].px + LARGO_COCHE / 2.0 * cos(coches[0].giro * ARADIANES), 1.5f, coches[0].pz + LARGO_COCHE / 2.0 * -sin(coches[0].giro * ARADIANES));

	//Posición a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, coches[0].px + 3.0 * cos(coches[0].giro * ARADIANES), 0.0f, coches[0].pz + 3.0 * -sin(coches[0].giro * ARADIANES)); //La luz mira al frente del coche

	//Posición de la cámara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0f, distanciaCamara, 0.0f);

	//Ángulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 45.0f);
}


//Función de iluminación del menú

void iluminacionMenu() {

	//Color de la luz del foco
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	//Color de la luz ambiental
	unsigned int ambientColorLoc = glGetUniformLocation(shadersPrincipales, "ambientColor");
	glUniform3f(ambientColorLoc, 1.0f, 1.0f, 1.0f);

	//Intensidad de la luz ambiental
	unsigned int ambientIntensityLoc = glGetUniformLocation(shadersPrincipales, "ambientIntensity");
	glUniform1f(ambientIntensityLoc, 0.5);

	//Posición de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 0.0, distanciaCamara, 0.0);

	//Objetivo de la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");

	switch (opcionMenuSeleccionada) {	//El lugar que iluminca el foco dependerá de la opción seleccionada en el menú
	case 0:

		glUniform3f(lookAtLoc, 8.8, 0.0, 8.8);
		glUniform3f(lightColorLoc, 1.0f, 0.0f, 0.0f);
		break;

	case 1:

		glUniform3f(lookAtLoc, -4.0, 0.0, -3.0);
		break;

	case 2:

		glUniform3f(lookAtLoc, 4.0, 0.0, -3.0);
		break;

	case 3:

		glUniform3f(lookAtLoc, -4.0, 0.0, 4.0);
		break;

	case 4:
		glUniform3f(lookAtLoc, 4.0, 0.0, 4.0);
		break;
	}


	//Posición de la cámara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0, distanciaCamara, 0.0);

	//Ángulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 8);
}


//Función de posicionamiento de la cámara del Pong Radial

void posicionarCamaraPong() {

	//Matriz de vista

	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0f, distanciaCamara, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
	unsigned int viewLoc = glGetUniformLocation(shadersPrincipales, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Matriz de proyección

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}


//Función de posicionamiento de la cámara del Flappy Steve

void posicionarCamaraFS() {

	//Matriz de vista

	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0f, distanciaCamara, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f));
	unsigned int viewLoc = glGetUniformLocation(shadersPrincipales, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Matriz de proyección

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


//Función de posicionamiento de la cámara del Shadow Step

void posicionarCamaraSS() {

	//Según la orientación seleccionada, se cambiará la orientación de la cámara, su altura y la altura a la que mirará (alturaLuz, ya que es la misma que la de la luz)
	float orientacionCamara = 1.0f;
	float alturaCamara = alturaVisionSS;
	float alturaLuz = 0.0f;

	if (orientacion != 0) {

		orientacionCamara = -1.0f;
		alturaCamara = ANCHO_SUELO_SS - alturaVisionSS;
		alturaLuz = ANCHO_SUELO_SS;
	}

	//Matriz de vista

	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0f, alturaCamara, 0.0f),
		glm::vec3(distanciaVisionSS, alturaLuz, 0.0f),
		glm::vec3(0.0f, orientacionCamara, 0.0f));
	unsigned int viewLoc = glGetUniformLocation(shadersPrincipales, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Matriz de proyección

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}


//Función de posicionamiento de la cámara del Crashing Cars

void posicionarCamaraCC() {

	//Matriz de vista

	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0f, distanciaCamara, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f));
	unsigned int viewLoc = glGetUniformLocation(shadersPrincipales, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Matriz de proyección

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


//Función de posicionamiento de la cámara del menú

void posicionarCamaraMenu() {

	glViewport(0, 0, anchoVentana, alturaVentana);	//Vista de tamaño de la ventana

	//Matriz de vista

	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0f, distanciaCamara, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f));
	unsigned int viewLoc = glGetUniformLocation(shadersPrincipales, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Matriz de proyección

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}


//Función que dibuja el texto del pong

void dibujarTextoPong() {

	//El brillo de las letras se reducirá al reducirse la intensidad ambiente
	glm::vec3 color = glm::vec3(intensidadAmbiente + 0.5, intensidadAmbiente + 0.5, intensidadAmbiente + 0.5);

	//Se dibujan todos los contadores
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalPong);
	dibujarTexto(cadena, 10.0, alturaVentana - 125.0, 1.0f, color);
	cadena = "Siguiente pelota: " + std::to_string(contadorPelotaNormal);
	dibujarTexto(cadena, 10.0, alturaVentana - 25.0, 1.0f, color);
	cadena = "Siguiente nivel de palas: " + std::to_string(contadorNuevoNivel);
	dibujarTexto(cadena, 10.0, alturaVentana - 50.0, 1.0f, color);
	cadena = "Siguiente pelota especial: " + std::to_string(contadorPelotaEspecial);
	dibujarTexto(cadena, 10.0, alturaVentana - 75.0, 1.0f, color);

	//Se dibuja la información sobre los controles
	if (mostrarControles) {

		dibujarTexto("Espacio: Cambiar sentido", 725.0, alturaVentana - 25.0, 1.0f, color);
		dibujarTexto("ESC: Volver al menu", 770.0, alturaVentana - 50.0, 1.0f, color);
		dibujarTexto("P: Pausar", 886.0, alturaVentana - 75.0, 1.0f, color);
	}
	else {

		dibujarTexto("C: Mostrar controles", 751.0, alturaVentana - 25.0, 1.0f, color);
	}

	//El mensaje de información sólo se dibujará si su contador es mayor que 0
	if (contadorMensajeInfo > 0) {
		dibujarTexto(mensajeInfo, (anchoVentana / 2.0) - 12.0 * mensajeInfo.size() / 2.0, alturaVentana / 2.0, 1.0f, colorMensajeInfo);
	}
}


//Función que dibuja el texto del Flappy Steve

void dibujarTextoFS() {

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	//Se dibuja el contador
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalFS);
	dibujarTexto(cadena, 25.0, 25.0, 1.0f, color);

	//Se dibuja la información sobre los controles
	if (mostrarControles) {

		dibujarTexto("ESC: Volver al menu", 750.0, 25.0, 1.0f, color);
		dibujarTexto("Espacio: Saltar", 798.0, 50.0, 1.0f, color);
		dibujarTexto("P: Pausar", 866.0, 75.0, 1.0f, color);
	}
	else {

		dibujarTexto("C: Mostrar controles", 732.0, 25.0, 1.0f, color);
	}
}


//Función que dibuja el texto del Shadow Step

void dibujarTextoSS() {

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	//Se dibuja el contador
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalSS);
	dibujarTexto(cadena, 25.0, 25.0, 1.0f, color);

	//Se dibuja la información sobre los controles
	if (mostrarControles) {

	dibujarTexto("Espacio: Invertir altura", 703.0, 25.0, 1.0f, color);
	dibujarTexto("ESC: Volver al menu", 750.0, 50.0, 1.0f, color);
	dibujarTexto("P: Pausar", 866.0, 75.0, 1.0f, color);
	}
	else {

		dibujarTexto("C: Mostrar controles", 732.0, 25.0, 1.0f, color);
	}
}


//Función que dibuja el texto del Crashing Cars

void dibujarTextoCC() {

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	//Se dibuja el contador
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalCC);
	dibujarTexto(cadena, 25.0, 25.0, 1.0f, color);

	//Se dibuja la información sobre los controles
	if (mostrarControles) {

	dibujarTexto("Espacio: Mover coches", 730.0, 25.0, 1.0f, color);
	dibujarTexto("ESC: Volver al menu", 750.0, 50.0, 1.0f, color);
	dibujarTexto("P: Pausar", 866.0, 75.0, 1.0f, color);
	}
	else {

	dibujarTexto("C: Mostrar controles", 732.0, 25.0, 1.0f, color);
	}
}


//Función que dibuja el texto de pausa centrado en pantalla (si se ha seleccionado la opción)

void dibujarMensajePausa() {
	if (pausa) dibujarTexto("Pausa", (anchoVentana / 2.0) - 12.0 * 5 / 2.0, alturaVentana / 2.0, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}


//Función de dibujo del Pong Radial

void dibujoPong() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	posicionarCamaraPong();		//Se posiciona la cámara

	dibujarSueloPong();			//Se dibuja el suelo (circular)

	dibujarFondoPong();			//Se dibuja el fondo

	//Se dibujan todas las palas y pelotas
	for (Pala pala : palas) {
		pala.dibujar();
		//dibujarHitboxPala(pala);
	}

	for (Pelota pelota : pelotasNormales) {
		pelota.dibujar(esfera);
	}

	for (Pelota pelota : pelotasBonus) {
		pelota.dibujar(esfera);
	}

	for (Pelota pelota : pelotasTrampa) {
		pelota.dibujar(esfera);
	}

	iluminacionPong();			//Se aplica la iluminación
	dibujarTextoPong();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Función que dibuja el Flappy Steve

void dibujoFS() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	iluminacionFS();		//Se aplica la iluminación

	posicionarCamaraFS();	//Se posiciona la cámara

	dibujarFondoFS();		//Se dibuja el fondo

	//Una vez dibujado el fondo, quitamos el color a la luz (para que no ilumine los elementos del frente, ya que la luz debe simular un Sol en el fondo)
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, 0.0f, 0.0f, 0.0f);

	//Se dibujan todos los pares de torres
	for (Torre torre : torres) {
		torre.dibujarParTorres();
	}

	steve.dibujar();			//Se dibuja a Steve

	dibujarTextoFS();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Función que dibuja el Shadow Step

void dibujoSS() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	iluminacionSS();		//Se aplica la iluminación

	posicionarCamaraSS();	//Se posiciona la cámara

	dibujarPasilloSS();		//Se dibuja el pasillo

	//Se dibujan todos los obstáculos
	for (Obstaculo obstaculo : obstaculos) obstaculo.dibujar(esfera);

	dibujarTextoSS();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Función que dibuja el Crashing Cars

void dibujoCC() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	iluminacionCC();		//Se aplica la iluminación

	posicionarCamaraCC();	//Se posiciona la cámara

	dibujarFondoCC();		//Se dibuja el fondo

	//Dibujamos los coches
	for (int i = 0; i < coches.size(); i++) {
		coches[i].dibujar();
		//dibujarHitboxCoche(coches[i]);
	}

	dibujarTextoCC();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Función que dibuja el menú

void dibujoMenu() {

	//Se dibujará el texto de los récords color blanco
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	std::string textoRecords;

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	posicionarCamaraMenu();		//Se posiciona la cámara

	//Se dibuja el fondo
	dibujarImagen(texturaMenu, TAMANO_FONDO_MENU, TAMANO_FONDO_MENU, 0, 0, 0);

	//Se dibujan todos los téxtos que indican los récords
	textoRecords = "Record: " + std::to_string(records[0]);
	dibujarTexto(textoRecords, 220.0f, 499.0f, 1.0f, color);
	dibujarImagen(texturaImagenPong, 5.0, 5.0, -4.0, 0.1, -3.0);

	textoRecords = "Record: " + std::to_string(records[1]);
	dibujarTexto(textoRecords, 569.0f, 499.0f, 1.0f, color);
	dibujarImagen(texturaImagenFS, 5.0, 5.0, 4.0, 0.1, -3.0);

	textoRecords = "Record: " + std::to_string(records[2]);
	dibujarTexto(textoRecords, 220.0f, 194.0f, 1.0f, color);
	dibujarImagen(texturaImagenSS, 5.0, 5.0, -4.0, 0.1, 4.0);

	textoRecords = "Record: " + std::to_string(records[3]);
	dibujarTexto(textoRecords, 569.0f, 194.0f, 1.0f, color);
	dibujarImagen(texturaImagenCC, 5.0, 5.0, 4.0, 0.1, 4.0);

	//Se dibuja la información sobre los controles
	if (mostrarControles) {

		dibujarTexto("Enter: Seleccionar opcion", 680.0f, alturaVentana - 75.0f, 1.0f, color);
		dibujarTexto("<- / -> : Cambiar opcion", 715.0f, alturaVentana - 100.0f, 1.0f, color);
		dibujarTexto("ESC: Salir", 858.0f, alturaVentana - 125.0f, 1.0f, color);
	}
	else {

	dibujarTexto("C: Mostrar controles", 725.0, alturaVentana - 75.0, 1.0f, color);
	}

	iluminacionMenu();	//Se aplica la iluminación
}

////////////////////////////////////////////////////////////////////////////////////// Funciones de carga inicial //////////////////////////////////////////////////////////////////////////////////////


//Función que inicializa el vector de palas

void inicializarPalas() {

	for (int i = 0; i < NUM_NIVELES_PALAS_INICIAL; i++) {
		anadirNivelPalas();
	}
}


//Función que inicializa los vectores de pelotas

void inicializarPelotas() {
	anadirPelota(0); //Se añade una pelota normal
}


//Función que carga el VAO de un cuadrado

void cargarVAOCuadrado(GLuint* VAOCuadrado) {
	unsigned int VBO;

	float vertices[] = {
		-0.5f,  0.0f, -0.5f,		0.0f, 1.0f, 0.0f,		0, 0,
		 0.5f,  0.0f, -0.5f,		0.0f, 1.0f, 0.0f,		1, 0,
		 0.5f,  0.0f,  0.5f,		0.0f, 1.0f, 0.0f,		1, 1,
		 0.5f,  0.0f,  0.5f,		0.0f, 1.0f, 0.0f,		1, 1,
		-0.5f,  0.0f,  0.5f,		0.0f, 1.0f, 0.0f,		0, 1,
		-0.5f,  0.0f, -0.5f,		0.0f, 1.0f, 0.0f,		0, 0,
	};

	glGenVertexArrays(1, VAOCuadrado);
	glGenBuffers(1, &VBO);

	glBindVertexArray(*VAOCuadrado);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Coordenadas texturas

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}


//Función que carga el VAO de un cubo

void cargarVAOCubo(GLuint* VAOCubo) {
	unsigned int VBO;

	float  vertices[] = {							//(Se supone que el frente mira al positivo del eje X)

		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	1, 1,	//Cara superior
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	0, 0,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	1, 0,

		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	0, 0,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	1, 1,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,	0, 1,


		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f,-1.0f,	1, 0,	//Cara inferior
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,-1.0f,	0, 0,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,-1.0f,	1, 1,

		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f,-1.0f,	0, 1,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,-1.0f,	1, 1,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,-1.0f,	0, 0,


		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,	0, 0,	//Cara trasera
		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,	1, 1,
		-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,	1, 0,

		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,	1, 1,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,	0, 0,
		-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,	0, 1,


		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,	1, 0,	//Cara delantera
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,	1, 1,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,	0, 0,

		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,	0, 1,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,	0, 0,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,	1, 1,


		 0.5f, -0.5f,  0.5f,   0.0f,-1.0f, 0.0f,	1, 1,	//Cara derecha
		-0.5f, -0.5f, -0.5f,   0.0f,-1.0f, 0.0f,	0, 0,
		 0.5f, -0.5f, -0.5f,   0.0f,-1.0f, 0.0f,	1, 0,

		-0.5f, -0.5f, -0.5f,   0.0f,-1.0f, 0.0f,	0, 0,
		 0.5f, -0.5f,  0.5f,   0.0f,-1.0f, 0.0f,	1, 1,
		-0.5f, -0.5f,  0.5f,   0.0f,-1.0f, 0.0f,	0, 1,


		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,	1, 0,	//Cara izquierda
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,	0, 0,
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,	1, 1,

		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,	0, 1,
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,	1, 1,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,	0, 0,

	};

	//Inicializamos

	glGenVertexArrays(1, VAOCubo);
	glGenBuffers(1, &VBO);

	//Asignamos el buffer VAOCubo

	glBindVertexArray(*VAOCubo);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Posicion

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Normal

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Coordenadas texturas

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Liberamos

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}


//Función que carga el VAO de un círculo

void cargarVAOCirculo(GLuint* VAOCirculo) {

	unsigned int VBO;

	GLuint nValVertice = 8;
	GLuint tamanoArray = nValVertice * VERTICES_PRECISION_CIRCULO;
	double anguloActual = 0;

	float* vertices;
	vertices = (float*)malloc(tamanoArray * sizeof(float));

	vertices[0] = 0; vertices[1] = 0; vertices[2] = 0;
	vertices[3] = 0; vertices[4] = 1.0; vertices[5] = 0;
	vertices[6] = 0.5; vertices[7] = 0.5;


	for (int i = 1; i < VERTICES_PRECISION_CIRCULO; i++) {

		vertices[0 + i * nValVertice] = cos(anguloActual); vertices[1 + i * nValVertice] = 0; vertices[2 + i * nValVertice] = -sin(anguloActual);	//Coords

		vertices[3 + i * nValVertice] = 0; vertices[4 + i * nValVertice] = 1.0; vertices[5 + i * nValVertice] = 0;		//Normal

		vertices[6 + i * nValVertice] = 0.5 + 0.5 * cos(anguloActual); vertices[7 + i * nValVertice] = 0.5 - 0.5 * sin(anguloActual);	//Coords textura

		anguloActual += (9.0 * PI) / VERTICES_PRECISION_CIRCULO;

		//printf("Nuevo vertice. X: %lf, Z: %lf, angulo: %lf\n", cos(anguloActual * ARADIANES), sin(anguloActual * ARADIANES), anguloActual * AGRADOS);
	}

	//Inicializamos

	glGenVertexArrays(1, VAOCirculo);
	glGenBuffers(1, &VBO);

	glBindVertexArray(*VAOCirculo);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, tamanoArray, vertices, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);

	//Coordenadas texturas

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);

	free(vertices);
}


//Función que carga el VAO del texto

void cargarVAOTexto() {

	glGenVertexArrays(1, &VAOTexto);
	glGenBuffers(1, &VBOTexto);
	glBindVertexArray(VAOTexto);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTexto);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


//Función que carga una textura dado el nombre del archivo y devuelve su índice

GLuint cargarTextura(const char* nombreTextura) {

	GLuint indice;

	glGenTextures(1, &(indice));
	glBindTexture(GL_TEXTURE_2D, indice);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nCanales;
	unsigned char* data = stbi_load(nombreTextura, &width, &height, &nCanales, 0);

	if (data) {

		switch (nCanales) {
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;

		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;

		default:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		}

	}
	else
	{
		printf("Error al cargar la textura %s\n", nombreTextura);
	}

	stbi_image_free(data);

	return indice;
}


//Función que carga las texturas

void cargarTexturas() {

	texturaMenu = cargarTextura("Texturas/FondoMenu.png");
	texturaSuelo = cargarTextura("Texturas/Suelo.png");
	texturaLimite = cargarTextura("Texturas/Limite.jpg");
	texturaPalas = cargarTextura("Texturas/Pala.png");
	texturaPelotasTrampa = cargarTextura("Texturas/BolaTrampa.png");
	texturaPelotasBonus = cargarTextura("Texturas/BolaBonus.png");
	texturaLadrillos = cargarTextura("Texturas/Ladrillos.jpeg");
	texturaSteve = cargarTextura("Texturas/Steve.png");
	texturaFondoFS = cargarTextura("Texturas/FondoFS.png");
	texturaTorresFS = cargarTextura("Texturas/Torres.png");
	texturaMadera = cargarTextura("Texturas/Madera.jpg");
	texturaSueloSS = cargarTextura("Texturas/SueloSS.jpg");
	texturaSueloCC = cargarTextura("Texturas/SueloCC.jpg");

	texturaImagenPong = cargarTextura("Texturas/PongRadial.png");
	texturaImagenFS = cargarTextura("Texturas/FlappySteve.png");
	texturaImagenSS = cargarTextura("Texturas/ShadowStep.png");
	texturaImagenCC = cargarTextura("Texturas/CrashingCars.png");

	texturasCuadros.push_back(cargarTextura("Texturas/Cuadro1.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro2.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro3.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro4.png"));
	texturasCuadros.push_back(cargarTextura("Texturas/Cuadro5.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro6.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro7.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro8.png"));
	texturasCuadros.push_back(cargarTextura("Texturas/Cuadro9.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro10.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro11.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro12.png"));
	texturasCuadros.push_back(cargarTextura("Texturas/Cuadro13.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro14.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro15.png")); texturasCuadros.push_back(cargarTextura("Texturas/Cuadro16.png"));

	texturasCoches.push_back(cargarTextura("Texturas/CocheRojo.png")); texturasCoches.push_back(cargarTextura("Texturas/CocheAzul.png"));
	texturasCoches.push_back(cargarTextura("Texturas/CocheVerde.png")); texturasCoches.push_back(cargarTextura("Texturas/CocheAmarillo.png"));
}


//Función que inicializa los VAOs

void cargarVAOs() {

	//Cargamos los VAOs
	cargarVAOCuadrado(&VAOPlano);
	cargarVAOCubo(&VAOCubo);
	cargarVAOCirculo(&VAOCirculo);
	cargarVAOTexto();
}


//Función de inicialización de las variables de openGL

void openGlInit() {

	//Incializaciones varias
	glClearDepth(1.0f);										//Asignamos una profundidad de borrado
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					//Asignamos el valor de limpieza del buffer de color
	glEnable(GL_DEPTH_TEST);								//Activamos el Z-Buffer
	glEnable(GL_CULL_FACE);									//Activamos la ocultación de las caras traseras
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);				//Dibujamos en modo fill

	glEnable(GL_BLEND);										//Activamos la transparencia
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Función que carga los primeros 128 caracteres de la fuente indicada

void cargarCaracteres(const char* archivoFuente) {

	if (FT_Init_FreeType(&ft)) printf("Error al inicializar la libreria\n");				//Se inicializa la librería
	if (FT_New_Face(ft, archivoFuente, 0, &face)) printf("Error al cargar la fuente\n");	//Se carga la fuente del archivo
	FT_Set_Pixel_Sizes(face, 0, 28);														//Se asigna el tamaño de los caracteres en píxeles

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //Se deshabilita la restricción de alineamiento de bytes

	//Iteramos los 128 caracteres
	for (unsigned char c = 0; c < 128; c++)
	{
		//Cargamos el glifo del caracter
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		//Generamos la textura
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		//Indicamos las opciones de las texturas
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Almacenamos el caracter en el vector de caracteres
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);	//Cerramos el face y el ft
}


//Función que realiza las preparaciones necesarias antes de ejecutar el Pong Radial

void cargaInicialPong() {

	//Asignamos los valores iniciales a las variables
	juegoSeleccionado = 1;
	volverAlMenu = 0;
	nNivelesPalas = 0;
	contadorMensajeInfo = 1;
	contadorTotalPong = 0;
	contadorNuevoNivel = 10;
	contadorPelotaNormal = 8;
	contadorPelotaEspecial = 20;
	siguientePelotaEspecial = 0;
	velocidadNuevasPelotas = 0.3;
	intensidadAmbiente = 1.0;
	mostrarControles = 0;
	pausa = 0;
	sentido = 1.0;
	limiteCerca = 0.1;
	limiteLejos = 1000.0;
	fovy = 60.0;
	distanciaCamara = 28;
	mensajeInfo = "Start";
	colorMensajeInfo = glm::vec3(1.0f, 1.0f, 1.0f);

	//Inicialización de variables de openGL
	openGlInit();

	//Inicializar palas
	inicializarPalas();

	//Inicializar pelotas
	inicializarPelotas();

	//Activamos la música de fondo
	PlaySound(TEXT("Sonidos/MusicaPong.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Función que realiza las preparaciones necesarias antes de ejecutar el Flappy Steve

void cargaInicialFS() {

	//Asignamos los valores iniciales a las variables
	juegoSeleccionado = 2;
	volverAlMenu = 0;
	intensidadAmbiente = 1.0;
	mostrarControles = 0;
	pausa = 0;
	limiteCerca = 0.1;
	limiteLejos = 1000.0;
	fovy = 60.0;
	distanciaCamara = 30;
	desplazamientoFS1 = 0;
	desplazamientoFS2 = -TAMANO_FONDO_FS;
	desplazamientoFSLuz = 0;
	incrementoDesplazamientoFS = 0.1;
	contadorTotalFS = 0;

	steve.pz = 0;
	steve.velocidadCaida = 0;
	steve.velocidadSalto = VELOCIDAD_SALTO_BASE;

	//Inicialización de variables de openGL
	openGlInit();

	//Reiniciamos el temporizador
	cronometroFS = glfwGetTime();
	avanceCronometroFS = 0;

	//Añadimos la primera torre
	anadirTorresFS(0);

	//Activamos la música de fondo
	PlaySound(TEXT("Sonidos/MusicaFS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Función que realiza las preparaciones necesarias antes de ejecutar el Shadow Step

void cargaInicialSS() {

	//Asignamos los valores iniciales a las variables
	juegoSeleccionado = 3;
	volverAlMenu = 0;
	intensidadAmbiente = 0.2;
	mostrarControles = 0;
	pausa = 0;
	limiteCerca = 0.1;
	limiteLejos = 1000.0;
	fovy = 60.0;
	distanciaCamara = 30;

	contadorTotalSS = 0;

	alturaVisionSS = 3.0;
	distanciaVisionSS = 7.0;
	orientacion = 0;

	intervaloObstaculosSS = 2;
	velocidadObstaculosSS = 1.5;
	velocidadDesplazamientoSS = 0.2;

	//Inicialización de variables de openGL
	openGlInit();

	//Asignamos los valores iniciales a las distancias de las secciones del pasillo
	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS; i++) desplazamientoSeccionesSS[i] = -LARGO_SUELO_SS * i;

	//Asignamos los valores iniciales a los índices de las texturas de los cuadros
	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS * 2; i++) cuadros.push_back(texturaCuadroAleatoria());

	//Reiniciamos el temporizador
	cronometroSS = glfwGetTime();
	avanceCronometroSS = 0;

	//Activamos la música de fondo
	PlaySound(TEXT("Sonidos/MusicaSS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Función que realiza las preparaciones necesarias antes de ejecutar el Crashing Cars

void cargaInicialCC() {

	//Asignamos los valores iniciales a las variables
	juegoSeleccionado = 4;
	volverAlMenu = 0;
	intensidadAmbiente = 0.5;
	mostrarControles = 0;
	pausa = 0;
	limiteCerca = 0.1;
	limiteLejos = 1000.0;
	fovy = 60.0;
	distanciaCamara = 50;

	contadorTotalCC = 0;
	factorEscaladoVelocidadOtrosCoches = 0.75;

	//Inicialización de variables de openGL
	openGlInit();

	//Creamos los primeros coches
	coches.emplace_back(20.0, 20.0, VELOCIDAD_COCHE_ROJO, VAOPlano, texturasCoches[0]);
	coches.emplace_back(0, 20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
	coches.emplace_back(0, -20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
	coches.emplace_back(20.0, -20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
	coches.emplace_back(-20.0, -20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
	coches.emplace_back(-20.0, 0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
	coches.emplace_back(20.0, 0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);
	coches.emplace_back(-20.0, 20.0, VELOCIDAD_COCHE_ROJO * factorEscaladoVelocidadOtrosCoches, VAOPlano, texturasCoches[rand() % 3 + 1]);

	//Activamos la música de fondo
	PlaySound(TEXT("Sonidos/MusicaCC.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Función que realiza las preparaciones necesarias antes de ejecutar el menú

void cargaInicialMenu() {

	//Asignamos los valores iniciales a las variables
	juegoSeleccionado = 0;
	opcionMenuSeleccionada = 1;
	volverAlMenu = 0;
	intensidadAmbiente = 1.0;
	limiteCerca = 0.1;
	limiteLejos = 1000.0;
	fovy = 60.0;
	distanciaCamara = 20.0;
	mostrarControles = 0;

	//Inicialización de variables de openGL
	openGlInit();
}


//Función que inicializa los objetos globales que lo necesiten

void inicializarObjetosGlobales() {

	steve.VAO = VAOPlano;
	steve.textura = texturaSteve;

	desplazamientoSeccionesSS.reserve(NUM_SECCIONES_PASILLO_SS);
}


//Función que abre el archivo de guardado y lee los datos

void abrirArchivoGuardado() {

	std::string linea;

	std::ifstream archivoGuardado("Guardado/guardado.txt");
	if (!archivoGuardado.is_open()) {

		printf("No se ha podido abrir el archivo de guardado\n");
		exit(1);
	}
	else {

		while (getline(archivoGuardado, linea)) {

			records.emplace_back(std::stoi(linea));
		}
	}

	archivoGuardado.close();
}


//Función que guarda los records actuales en el archivo de guardado

void guardarArchivo() {

	std::string linea;

	std::ofstream archivoGuardado("Guardado/guardado.txt");
	if (!archivoGuardado.is_open()) {

		printf("No se ha podido abrir el archivo de guardado\n");
		exit(1);
	}
	else {

		for (int i = 0; i < records.size(); i++) {

			archivoGuardado << records[i];
			archivoGuardado << "\n";
		}
	}

	printf("Datos guardados\n");

	archivoGuardado.close();
}


//Función que realiza las preparaciones necesarias antes de poder comenzar el programa

void cargaInicialPrograma() {

	srand(time(0));	//Establecemos una semilla para el rand (momento actual, para que sea realmente aleatorio)

	shadersPrincipales = setShaders("Shaders/shaderPrincipal.vert", "Shaders/shaderPrincipal.frag");
	shadersTexto = setShaders("Shaders/shaderTexto.vert", "Shaders/shaderTexto.frag");

	//Cargamos los caracteres de la fuente que vamos a usar
	cargarCaracteres("Fuentes/digital-7.ttf");

	//Abrimos el archivo de guardado
	abrirArchivoGuardado();

	//Inicialización de las texturas
	cargarTexturas();

	//Inicialización de los VAOs
	cargarVAOs();

	//Inicializamos los atributos de los objetos globales
	inicializarObjetosGlobales();
}


//Función que se encarga de limitar los FPS a los indicados

void gestionFPS(double* medidorFPS) {

	double tiempoEntreFotogramas = 1000.0 / FPS_PROGRAMA;

	if (glfwGetTime() * 1000.0 < *medidorFPS + tiempoEntreFotogramas) {
		Sleep(tiempoEntreFotogramas);
	}
	*medidorFPS += tiempoEntreFotogramas;
}

////////////////////////////////////////////////////////////////////////////////////// Main //////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(alturaVentana, anchoVentana, "Space Games", NULL, NULL);
	glfwSetWindowPos(window, 400, 28);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Asignamos la función de gestion de teclado
	glfwSetKeyCallback(window, gestionTeclado);

	//Se realiza la carga inicial del programa
	cargaInicialPrograma();

	//Se realiza la carga inicial del menú
	cargaInicialMenu();

	//Asignamos los shaders principales
	glUseProgram(shadersPrincipales);

	//Inicializamos el contador para los FPS
	double medidorFPS = glfwGetTime() * 1000.0;

	//Bucle principal

	while (!glfwWindowShouldClose(window))
	{
		switch (juegoSeleccionado) {

		case 0:		//Menú

			dibujoMenu();			//Dibujamos la escena
			break;

		case 1:		//Pong Radial

			dibujoPong();			//Dibujamos la escena
			actualizacionPong();	//Actualizamos los valores
			break;

			/*Se aprecia mejor si se dibuja el estado anterior y después se actualiza al siguiente ya que, si se hace al revés,
			se tiene en cuenta en la actualización información que aún no se ha mostrado y resulta confuso visualmente*/

		case 2:		//Flappy Steve

			dibujoFS();
			actualizacionFS();
			break;

		case 3:		//Shadow Step

			dibujoSS();
			actualizacionSS();
			break;

		case 4:

			dibujoCC();
			actualizacionCC();
			break;

		default:	//Error

			printf("Opcion de juego incorrecta\n");
			break;
		}

		//Intercambiamos los buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		//Nos aseguramos de que el programa no vaya a más FPS de los indicados
		gestionFPS(&medidorFPS);
	}

	//Eliminamos los arrays de vértices
	glDeleteVertexArrays(1, &VAOPlano);
	glDeleteVertexArrays(1, &VAOCubo);
	glDeleteVertexArrays(1, &VAOCirculo);

	//Guardamos la información de los récords en el archivo de guardado
	guardarArchivo();

	glfwTerminate();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////// Otras funciones //////////////////////////////////////////////////////////////////////////////////////

//Función de gestión de la entrada por teclado

void gestionTeclado(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {		//P
		pausa = !pausa;

		if (pausa) {	//Al entrar en pausa, guardamos el avance del intervalo de los cronómetros del FS y el SS

			avanceCronometroFS = glfwGetTime() - cronometroFS;
			avanceCronometroSS = glfwGetTime() - cronometroSS;
		}
		else {			//Al salir de la pausa, restablecemos la diferencia entre el tiempo actual y el cronómetro a la almacenada anteriormente

			cronometroFS = glfwGetTime() - avanceCronometroFS;
			cronometroSS = glfwGetTime() - avanceCronometroSS;
		}
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {		//C
		mostrarControles = !mostrarControles;
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {		//M
		mostrarControles = !mostrarControles;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {	//Espacio

		switch (juegoSeleccionado) {

		case 1:

			sentido *= -1.0;	//En el Pong Radial, pulsar el espacio intercambia el sentido de giro de las palas
			break;

		case 2:					//En el Flappy Steve, pulsar el espacio hace que Steve salte

			steve.saltar();
			break;

		case 3:					//En el Shadow Step, pulsar el espacio alterna la orientación de la cámara entre el suelo y el techo

			orientacion = !orientacion;
			break;

		case 4:					//En el Crarshing Cars, pulsar el espacio hace que el coche avance hasta que encuentre un obstáculo

			for (int i = 0; i < coches.size(); i++) coches[i].movimiento = 1;
			break;

		default:
			break;
		}
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {	//Enter

		//Si se está en el menú, selecciona una opción
		if (!juegoSeleccionado) {

			switch (opcionMenuSeleccionada) {

			case 0:

				glfwSetWindowShouldClose(window, true);
				break;

			case 1:

				cargaInicialPong();
				break;

			case 2:

				cargaInicialFS();
				break;

			case 3:

				cargaInicialSS();
				break;

			case 4:

				cargaInicialCC();
				break;

			default:

				printf("Opcion menu incorrecta\n");
				break;
			}
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {	//Escape

		//Vuelve al menú o vuelve al menú si se está jugando a algún juego
		if (!juegoSeleccionado) glfwSetWindowShouldClose(window, true);
		else volverAlMenu = 1;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {	//Flecha derecha

		//Se cambia la opción seleccionada del menú
		if (!juegoSeleccionado) {

			opcionMenuSeleccionada++;
			PlaySound(TEXT("Sonidos/OpcionMenu.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
			if (opcionMenuSeleccionada >= OPCIONES_MENU) opcionMenuSeleccionada -= OPCIONES_MENU;
		}
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {		//Flecha derecha

		//Se cambia la opción seleccionada del menú
		if (!juegoSeleccionado) {

			opcionMenuSeleccionada--;
			PlaySound(TEXT("Sonidos/OpcionMenu.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
			if (opcionMenuSeleccionada < 0) opcionMenuSeleccionada += OPCIONES_MENU;
		}
	}
}