//Autor: Miguel Torres Est�vez

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
#define FPS_PROGRAMA 60.0	//N�mero de FPS que va a tener el programa

//VAO
#define VERTICES_PRECISION_CIRCULO 300.0		//N�mero de v�rtices de precisi�n que tendr� el VAO del c�rculo

//Men�
#define TAMANO_FONDO_MENU 23.2	//Tama�o del fondo del men�
#define OPCIONES_MENU 5			//N�mero de opciones que tiene el men�					

//Pong Radial
#define V_PALAS_BASE 1.4						//Velocidad base del primer nivel de palas
#define DECREMENTO_VELOCIDAD_NIVEL_PALAS 0.85	//Indica cu�nto se reduce la velocidad de giro en cada nivel de palas (los niveles mayores van m�s lentos)

#define DISTANCIA_ENTRE_PALAS 20.0				//Distancia entre los distintos niveles de palas
#define NUM_NIVELES_PALAS_INICIAL 3				//N�mero de niveles de palas al iniciar la partida
#define NUM_NIVELES_PALAS_MAX 6					//N�mero m�ximo de niveles de palas
#define TAMANO_PALAS_BASE 12					//Tama�o base de las palas del primer nivel
#define FACTOR_ESCALADO_TAMANO_PALAS 2.3		//Ajusta el incremento de tama�o de las palas por nivel

#define INCREMENTO_DISTANCIA_CAMARA_PONG 44.0	//Desplazamiento vertical de la c�mara del Pong Radial al a�adir o eliminar un nivel de palas

//Flappy Steve
#define TAMANO_FONDO_FS	35.0	//Tama�o del fondo del FS

//Crashing Cars
#define TAMANO_FONDO_CC 60.0	//Tama�o del fondo del CC


//Variables de la ventana

double anchoVentana = 1000;		//Ancho
double alturaVentana = 1000;	//Alto


//Variables de entorno

//Pong Radial
int nNivelesPalas = 0;					//Indica el n�mero de niveles de palas que hay actualmente
int contadorMensajeInfo = 1;			//Indica cu�ntos rebotes quedan para que desaparezca el mensaje de informaci�n
long int contadorTotalPong = 0;			//Indica el n�mero total de rebotes que se han obtenido en la partida del Pong Radial
long int contadorNuevoNivel = 10;		//Indica cu�ntos rebotes quedan para conseguir un nuevo nivel de palas
long int contadorPelotaNormal = 8;		//Indica cu�ntos rebotes quedan para que aparezca una nueva pelota normal
long int contadorPelotaEspecial = 20;	//Indica cu�ntos rebotes quedan para que aparezca una nueva pelota especial (bonus o trampa)

int siguientePelotaEspecial = 0;		//Indicador binario que indica si la siguiente pelota especial va a ser de tipo bonus o tipo trampa
double velocidadNuevasPelotas = 0.3;	//Velocidad que tendr�n las nuevas pelotas al crearse (aumenta a medida que el juego avanza)

std::string mensajeInfo = "Start";							//Valor actual del mensaje de informaci�n del Pong Radial
glm::vec3 colorMensajeInfo = glm::vec3(1.0f, 1.0f, 1.0f);	//Color actual del mensaje de informaci�n del Pong Radial	

//Flappy Steve
long int contadorTotalFS = 0;			//Indica el n�mero total de tuber�as que has superado en el Flappy Steve

double desplazamientoFS1 = 0;						//Desplazamiento lateral de los fondos del Flappy Steve
double desplazamientoFS2 = -TAMANO_FONDO_FS;
double desplazamientoFSLuz = 0;						//Desplazamiento actual de la luz del Flappy Steve
double incrementoDesplazamientoFS = 0.1;			//Marca la velocidad de desplazamiento de los elementos del Flappy Steve

double cronometroFS = 0;				//Variable para cronometrar los eventos del Flappy Steve
double avanceCronometroFS = 0;			//Variable para almacenar cu�nto ha avanzado el cron�metro dentro del intervalo al pausar

//Shadow Step
long int contadorTotalSS = 0;		//Indica el n�mero total de tuber�as que has superado en el Flappy Steve 	

double alturaVisionSS = 3.0;		//Altura a la que est� posicionada la c�mara respecto del suelo
double distanciaVisionSS = 7.0;		//Distancia a la que mira la c�mara respecto de su posici�n actual
int orientacion = 0;				//Orientaci�n actual de la c�mara (suelo o techo)

double intervaloObstaculosSS = 3.0;				//Intervalo de tiempo (en segundos) que hay entre los obst�culos
double velocidadObstaculosSS = 0.5;				//Velocidad de acercamiento de los obst�culos hacia la c�mara
double velocidadDesplazamientoSS = 0.2;			//Velocidad de desplazamiento de la c�mara
std::vector<double> desplazamientoSeccionesSS;	//Vector de doubles que almacena el desplazamiento actual de cada secci�n del pasillo

double cronometroSS;				//Variable para cronometrar los eventos del Shadow Step
double avanceCronometroSS = 0;			//Variable para almacenar cu�nto ha avanzado el cron�metro dentro del intervalo al pausar

//Crashing Cars
long int contadorTotalCC = 0;		//Indica el n�mero total de coches a los que has chocado en el Crashing Cars

int posicionSiguenteCoche = 0;						//Indica en cual de las 8 posiciones posibles va a salir el pr�ximo coche
double factorEscaladoVelocidadOtrosCoches = 0.75;	//Escalado de la velocidad del resto de coches respecto de la del coche rojo


//Iluminaci�n
float tonalidadFoco[3] = { 1.0f, 1.0f, 0.0f };	//Tonalidad de la luz del foco
float intensidadAmbiente = 1.0;					//Intensidad de la luz ambiente


//Variables de control

//Generales
int juegoSeleccionado = 0;			//Indica qu� juego est� seleccionado actualmente
int mostrarControles = 0;			//Indicador binario que indica si se deben mostrar los controles
int pausa = 0;						//Indicador binario que indica si el juego est� actualmente en pausa	

//Men�
int volverAlMenu = 0;				//Indicador binario que indica si se ha solicitado volver al men�
int opcionMenuSeleccionada = 1;		//Opci�n seleccionada actualmente del men� (por defecto, el Pong Radial)

//Pong Radial
double sentido = 1.0;				//Indica en qu� sentido se mueven actualmente las palas del Pong Radial


//Variables de la c�mara

float limiteCerca = 0.1;		//No puedo llamarlos near y far porque esas variables ya est�n definidas, pero son justo eso
float limiteLejos = 1000.0;
float fovy = 60.0;				//�ngulo del campo de visi�n

float distanciaCamara = 25;		//Distancia actual de la c�mara


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

FT_Library ft;								//Librer�a
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
std::vector<Obstaculo> obstaculos;		//Vector que almacena los obst�culos
std::vector<GLuint> cuadros;			//Vector que almacena los �ndices de los cuadros del pasillo

//Crashing Cars
std::vector<Coche> coches;		//Vector que almacena los coches


//El programa se divide en tres modulos principales: Actualizaci�n, dibujo y carga inicial (en ese orden), he separado las funciones correspondientes a cada m�dulo para hacer m�s claro el c�digo

//////////////////////////////////////////////////////////////////////////////////////  Declaraciones de funciones //////////////////////////////////////////////////////////////////////////////////////

//Estas funciones son necesarias antes de su declaraci�n, por lo que las declaro antes aqu�

void cargaInicialMenu();

void cargaInicialCC();

void cargaInicialSS();

void cargaInicialFS();

void cargaInicialPong();

void sumarContadorPong();

void dibujarTexto(std::string text, float x, float y, float scale, glm::vec3 color);

void gestionTeclado(GLFWwindow* window, int key, int scancode, int action, int mods);

////////////////////////////////////////////////////////////////////////////////////// Funciones de actualizaci�n //////////////////////////////////////////////////////////////////////////////////////

//Funci�n que a�ade un nivel de palas

void anadirNivelPalas() {

	//Se comprueba que el nivel de palas actual no exceda el m�ximo
	if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) {

		//Se indica que hay un nuevo nivel de palas
		nNivelesPalas++;

		//Se crean e introducen tantas palas en el vector como sean necesarias
		for (int i = 0; i < nNivelesPalas + 2; i++) {
			palas.emplace_back(Pala(0.6, 0.1, TAMANO_PALAS_BASE * (1.0 + nNivelesPalas / FACTOR_ESCALADO_TAMANO_PALAS), nNivelesPalas * DISTANCIA_ENTRE_PALAS, i * (360.0 / (nNivelesPalas + 2.0)), VAOCubo, texturaPalas, 36));
		}

		//Se aleja la c�mara para enfocar el nuevo nivel
		distanciaCamara += INCREMENTO_DISTANCIA_CAMARA_PONG;
	}
}


//Funci�n que elimina un nivel de palas

void eliminarNivelPalas() {

	//Se comprueba que el nivel de palas actual no llegue a 0
	if (nNivelesPalas > 1) {

		//Se eliminan las palas del �ltimo nivel del vector
		for (int i = 0; i < nNivelesPalas + 2; i++) {
			palas.pop_back();
		}

		//Se indica que hay un nivel de palas menos
		nNivelesPalas--;

		//Se acerca la c�mara para que no enfocar espacio vac�o
		distanciaCamara -= INCREMENTO_DISTANCIA_CAMARA_PONG;
	}
}


//Funci�n que rota las palas

void rotarPalas() {

	double velocidadNivel = V_PALAS_BASE;	//Se parte de la velocidad base del nivel 0
	int aux = 0;							//Se parte de la posici�n 0 del vector de palas

	for (int i = 0; i < nNivelesPalas; i++) {	//Recorremos todas las palas
		for (int j = 0; j < i + 3; j++) {

			if (i % 2 == 0) {	//Las palas de niveles alternos girar�n en sentido opuesto

				palas[j + aux].actualizarPosicion(sentido * velocidadNivel);
			}
			else {

				palas[j + aux].actualizarPosicion(-sentido * velocidadNivel);
			}

		}
		aux += 3 + i;											//Se avanza al siguiente nivel de palas en el vector
		velocidadNivel *= DECREMENTO_VELOCIDAD_NIVEL_PALAS;		//Se reduce la velocidad de los niveles m�s lejanos
	}
}


//Funci�n que a�ade una pelota dado su tipo a su respectivo vector

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


//Funci�n que elimina una pelota del array indicado

void eliminarPelota(std::vector<Pelota>& vectorPelotas, int posicion) {
	if (posicion == -1) vectorPelotas.pop_back();							//Si se indica la posici�n -1, se elimina la �ltima
	else vectorPelotas.erase(vectorPelotas.begin() + posicion);
}


//Funci�n que mueve las pelotas

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


//Funci�n que comprueba si una pelota se ha salido del l�mite

int comprobarSalidaLimite(Pelota pelota) {
	return pelota.distanciaAlCentro >= (nNivelesPalas + 1.0) * DISTANCIA_ENTRE_PALAS;
}


//Funci�n que elimina el par de torres m�s antiguo en el FS

void eliminarTorresFS() {
	if (torres.size() > 0) torres.erase(torres.begin());
}


//Funci�n que a�ade un par de torres en el FS

void anadirTorresFS(double alturaHueco) {
	torres.emplace_back(15.0, alturaHueco, VAOPlano, texturaTorresFS);
}


//Funci�n que mueve las torres en el FS

void moverTorresFS() {
	for (int i = 0; i < torres.size(); i++) {
		torres[i].desplazamiento += incrementoDesplazamientoFS;
	}
}


//Funci�n que gestiona la derrota del Pong Radial

void derrotaPong(int opcion) {	//La opci�n es para diferenciar si ha sido llamada desde el men� (no sonar� el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaPong.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[0] < contadorTotalPong) records[0] = contadorTotalPong;		//Si la puntuaci�n obtenida supera el r�cord, se actualiza el r�cord

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

	cargaInicialMenu();		//Se vuelve al men�
}


//Funci�n que gestiona la derrota del Flappy Steve

void derrotaFS(int opcion) {	//La opci�n es para diferenciar si ha sido llamada desde el men� (no sonar� el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaFS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[1] < contadorTotalFS) records[1] = contadorTotalFS;		//Si la puntuaci�n obtenida supera el r�cord, se actualiza el r�cord

	//Vaciamos los vectores

	while (torres.size() > 0) torres.pop_back();

	cargaInicialMenu();		//Se vuelve al men�
}


//Funci�n que gestiona la derrota del Shadow Step

void derrotaSS(int opcion) {	//La opci�n es para diferenciar si ha sido llamada desde el men� (no sonar� el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaSS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[2] < contadorTotalSS) records[2] = contadorTotalSS;		//Si la puntuaci�n obtenida supera el r�cord, se actualiza el r�cord

	//Vaciamos los vectores

	while (obstaculos.size() > 0) obstaculos.pop_back();
	while (cuadros.size() > 0) cuadros.pop_back();

	cargaInicialMenu();		//Se vuelve al men�
}


//Funci�n que gestiona la derrota del Crashing Cars

void derrotaCC(int opcion) {	//La opci�n es para diferenciar si ha sido llamada desde el men� (no sonar� el sonido de derrota) o desde el propio juego

	if (opcion) PlaySound(TEXT("Sonidos/DerrotaCC.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
	else PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME); //Al poner el sonido a NULL, cancela lo que estuviera sonando

	if (records[3] < contadorTotalCC) records[3] = contadorTotalCC;		//Si la puntuaci�n obtenida supera el r�cord, se actualiza el r�cord

	//Vaciamos los vectores

	while (coches.size() > 0) coches.pop_back();

	cargaInicialMenu();		//Se vuelve al men�
}


//Funci�n que gestiona la salida de una pelota normal fuera del l�mite

void gestionarSalidaPelotaNormalLimite() {

	if (palas.size() < 4) derrotaPong(1);	//Si solo quedaba el �ltimo nivel de palas, se pierde la partida
	else {									//Si hab�a mas niveles, se devuelven todas las pelotas al centro, se reduce tanto su velocidad como la de las nuevas pelotas y se elimina el �ltimo nivel de palas

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


//Funci�n que comprueba las colisiones de una pelota con las palas

int comprobarColisionPelota(Pelota* pelota, std::vector<Pala>& palas) {

	for (Pala pala : palas) {
		if (pelota->comprobarColision(pala, esfera)) {
			return true;
		}
	}
	return false;
}


//Funci�n que aplica la bonificaci�n de las pelotas bonus

void accionPelotaBonus() {

	char mensaje[50];

	switch (rand() % 3) {

	case 0:			//Reducci�n de velocidad de las pelotas

		for (int i = 0; i < pelotasNormales.size(); i++) pelotasNormales[i].velocidad *= 0.8;

		for (int i = 0; i < pelotasBonus.size(); i++) pelotasBonus[i].velocidad *= 0.8;

		for (int i = 0; i < pelotasTrampa.size(); i++) pelotasTrampa[i].velocidad *= 0.8;

		velocidadNuevasPelotas *= 0.8;
		mensajeInfo = "Reduccion de velocidad de las pelotas";
		break;

	case 1:			//Nivel de palas extra > Se elimina una pelota > Reducci�n de velocidad de las pelotas

		if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) {	//Si alg�n bonus no es posible porque ya se ha alcanzado el m�ximo o el m�nimo de entidades posible, se asigna alguno de los otros

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

	case 2:			//Se elimina una pelota > Nivel de palas extra > Reducci�n de velocidad de las pelotas

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
	contadorMensajeInfo = 3.0 * pelotasNormales.size();		//Aumentamos el contador del mensaje de informaci�n para que se imprima
	colorMensajeInfo = glm::vec3(0.0f, 1.0f, 0.0f);			//Asignamos el color verde al mensaje de informaci�n
}


//Funci�n que realiza la penalizaci�n de las pelotas trampa (mismo funcionamiento que las de bonus, pero con penalizaciones)

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

		if (palas.size() < 4) derrotaPong(1);	//Si pierdes un nivel de palas y s�lo te quedaba el �ltimo, pierdes autom�ticamente la partida
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
	colorMensajeInfo = glm::vec3(1.0f, 0.0f, 0.0f);			//En el caso de las penalizaciones, el mensaje de informaci�n aparecer� en rojo
}


//Funci�n que comprueba las colisiones de todas las pelotas

void comprobarColisionPelotas() {


	//Pelotas normales
	for (int i = 0; i < pelotasNormales.size(); i++) {

		//Cuando una pelota normal rebota, se aumenta el contador de rebotes y se incrementa ligeramente la velocidad de las nuevas pelotas
		if (comprobarColisionPelota(&pelotasNormales[i], palas)) {

			velocidadNuevasPelotas += INCREMENTO_VELOCIDAD_PELOTAS / (pelotasNormales.size() * 2.0);
			sumarContadorPong();
		}

		//Cuando una pelota normal sale del l�mite, se elimina y se llama a la funci�n que gestiona las acciones correspondientes
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
		else {	//El else es necesario, ya que podr�a haberse eliminado la pelota antes de comprobar su salida

			//Si una pelota bonus sale del l�mite, simplemente desaparece
			if (comprobarSalidaLimite(pelotasBonus[i])) {
				eliminarPelota(pelotasBonus, i);
			}
		}
	}

	//Pelotas trampa
	for (int i = 0; i < pelotasTrampa.size(); i++) {

		//Cuando una pelota bonus rebota 5 veces, se aplica la penalizaci�n y se elimina la pelota
		if (comprobarColisionPelota(&pelotasTrampa[i], palas)) {

			if (pelotasTrampa[i].contadorRebotes >= 5) {
				accionPelotaTrampa();
				eliminarPelota(pelotasTrampa, i);
			}
		}
		else {	//El else es necesario, ya que podr�a haberse eliminado la pelota antes de comprobar su salida

			//Si una pelota trampa sale del l�mite, simplemente desaparece
			if (comprobarSalidaLimite(pelotasTrampa[i])) {
				eliminarPelota(pelotasTrampa, i);
			}
		}
	}
}


//Funci�n que suma un rebote al contador y realiza las acciones correspondientes

void sumarContadorPong() {

	int auxColor = 0;	//Variable auxiliar para asegurarnos de que haya luz

	contadorTotalPong++;			//Se incrementa el contador total de rebotes
	contadorPelotaNormal--;			//Se reducen los contadores de los nuevos elementos
	contadorPelotaEspecial--;
	if (nNivelesPalas <= NUM_NIVELES_PALAS_MAX) contadorNuevoNivel--;	//El contador para el pr�ximo nivel de palas no se modifica si ya se ha alcanzado el n�mero m�ximo de niveles de palas
	if (contadorMensajeInfo > 0) contadorMensajeInfo--;					//Se reducen los rebotes restantes del mensaje de informaci�n
	intensidadAmbiente *= 0.995;										//Se reduce la intensidad de la luz ambiente, de forma que cada vez el exterior c�rculo de palas est� m�s oscuro

	//Cuando los contadores de los nuevos elementos llegan a 0, se a�ade el elemento a la partida y se asigna un nuevo valor al contador, dependiente del n�mero actual de pelotas
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

	while (!auxColor) {						//Por cada rebote, el color de la luz del foco cambia (se asegura que haya alg�n color)
		for (int i = 0; i < 3; i++) {

			float intensidadColor = (rand() % 4) / 2.0;
			tonalidadFoco[i] = intensidadColor;
			if (intensidadColor > 0) auxColor = 1;
		}
	}
}


//Funci�n que mueve y alterna los planos del fondo del FS

void actualizarPosicionFondo() {

	//Los desplazamientos van aumentando y, en cuanto salen del l�mite, vuelven a su posici�n inicial, de forma que se mueven en bucle

	desplazamientoFS1 += incrementoDesplazamientoFS;
	if (desplazamientoFS1 > TAMANO_FONDO_FS) desplazamientoFS1 -= TAMANO_FONDO_FS;
	desplazamientoFS2 += incrementoDesplazamientoFS;
	if (desplazamientoFS2 > 0) desplazamientoFS2 -= TAMANO_FONDO_FS;
	desplazamientoFSLuz += incrementoDesplazamientoFS / 10.0;
	if (desplazamientoFSLuz > 40.0) desplazamientoFSLuz -= TAMANO_FONDO_FS + 12.0;
}


//Funci�n que elige una textura de cuadro aleatoria y devuelve el �ndice

GLuint texturaCuadroAleatoria() {

	return texturasCuadros[rand() % 16];
}


//Funci�n que actualiza la posici�n de las secciones del pasillo y las alterna

void actualizarPosicionPasillo() {

	double limiteSecciones = LARGO_SUELO_SS / 2.0;

	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS; i++) {		//Aumentamos el desplazamieto de las secciones del pasillo y, cuando dejan de ser visibles, las devolvemos a la posici�n m�s lejana y cambiamos sus cuadros

		desplazamientoSeccionesSS[i] += velocidadDesplazamientoSS;
		if (desplazamientoSeccionesSS[i] > limiteSecciones) {
			desplazamientoSeccionesSS[i] -= distanciaMaximaSS;
			cuadros[2 * i] = texturaCuadroAleatoria();
			cuadros[2 * i + 1] = texturaCuadroAleatoria();
		}
	}

	for (int i = 0; i < obstaculos.size(); i++) {			//Desplazamos los obst�culos y los rotamos

		obstaculos[i].desplazamiento += velocidadObstaculosSS;
		obstaculos[i].rotacion += 8.0;

		if (obstaculos[i].desplazamiento >= distanciaMaximaSS) {	//Cuando los obst�culos llegan a la posici�n de la c�mara, se eliminan si est�n en el otro nivel o se termina la partida si est�n ene l mismo

			if (obstaculos[i].orientacion == orientacion) derrotaSS(1);
			else {

				obstaculos.erase(obstaculos.begin());

				if (velocidadObstaculosSS <= 7.0) velocidadObstaculosSS += 0.05;	//Cuando se elimina un obst�culo, se aumenta la velocidad y se reduce el intervalo para los nuevos obst�culos
				if (intervaloObstaculosSS >= 0.5) intervaloObstaculosSS -= 0.05;

				contadorTotalSS++;
			}
		}
	}
}


//Funci�n que a�ade un nuevo coche al mapa

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


//Funci�n que comprueba las colisiones de un coche con el resto en el Crashing Cars

void comprobarColisionesCoches(Coche coche, int pos) {

	for (int i = 0; i < coches.size(); i++) {
		if (i != pos) {

			switch (coche.comprobarColision(coches[i])) {

			case 1:		//Colisi�n lateral

				if (!i) derrotaCC(1);	//Si le chocan al coche rojo, se pierde la partida
				else {

					coches.erase(coches.begin() + i);
					contadorTotalCC++;
					nuevoCoche();
				}
				break;

			case 2:		//Colisi�n frontal

				coches[i].movimiento = 1;
				coches[i].velocidad = -VELOCIDAD_REBOTE;
				coches[pos].movimiento = 1;
				coches[pos].velocidad = -VELOCIDAD_REBOTE;
				break;

			case 3:		//Colisi�n est�tica

				coches[pos].movimiento = 1;
				coches[pos].velocidad = -VELOCIDAD_REBOTE;
				break;

			default:
				break;
			}
		}
	}
}


//Funci�n de actualizaci�n del Pong Radial

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


//Funci�n de actualizaci�n del Flappy Steve

void actualizacionFS() {

	if (volverAlMenu) {
		derrotaFS(0);
	}
	else {

		if (!pausa) {

			if (glfwGetTime() - 3 >= cronometroFS) {	//Cada 3 segundos, se a�ade un nuevo par de torres de altura aleatoria, se elimina el par de torres que ha salido del l�mite de visi�n y se aumenta el contador
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
			steve.caer();						//Se gestiona la ca�da
		}
	}
}


//Funci�n de actualizaci�n del Shadow Step

void actualizacionSS() {

	if (volverAlMenu) {
		derrotaSS(0);
	}
	else {

		if (!pausa) {

			if (glfwGetTime() - intervaloObstaculosSS >= cronometroSS) {		//Cada vez que se cumple el intervalo, se a�ade un nuevo obst�culo

				cronometroSS = glfwGetTime();
				obstaculos.emplace_back(rand() % 2, VAOCubo, texturaMadera);	//La orientaci�n del obst�culo ser� aleatoria
			}

			actualizarPosicionPasillo();	//Se actualiza el desplazamiento de las secciones del pasillo
		}
	}
}


//Funci�n de actualizaci�n del Crushing Cars

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

//Funci�n que dibuja la hitbbox de las palas (solo para comprobaciones)

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

	//Dividimos el �rea de la pala en tantos c�rculos hacia cada lateral como indique la variable de divisiones (es m�s f�cil usar c�rculos, ya que la pala va a estar rotando)

	for (int i = 0; i < divisiones - divisionesLaterales; i++) {

		//Repartimos los c�rculos de forma uniforme a trav�s de la pala

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


//Funci�n que dibuja la hitbbox de los coches (solo para comprobaciones)

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

	double divisiones = 10;		//N�mero de divisiones a realizar
	double distancia;			//Variable para almacenar la distancia

	double incrementoX = moduloXLargo / (divisiones * 2.0);
	double incrementoZ = moduloZLargo / (divisiones * 2.0);

	double circuloDerechoX = coche.px;
	double circuloDerechoZ = coche.pz;

	double circuloIzquierdoX = coche.px;
	double circuloIzquierdoZ = coche.pz;

	for (int i = 0; i < divisiones; i++) {	//Dividimos el �rea de la pala en tantos c�rculos hacia cada lateral como indique la variable de divisiones (es m�s f�cil usar c�rculos, ya que la pala va a estar rotando)

		//Repartimos los c�rculos de forma uniforme a trav�s de la pala y comprobamos si han colisionado con las esquinas del coche

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


//Funci�n que dibuja el fondo exterior del Pong Radial

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


//Funci�n que dibuja el suelo circular y la marca del l�mite del Pong Radial

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


//Funci�n que dibuja el fondo del Flappy Steve

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


//Funci�n que dibuja una secci�n del pasillo dada la distancia

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


//Funci�n que dibuja todas las secciones del pasillo

void dibujarPasilloSS() {

	glDisable(GL_CULL_FACE);

	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS; i++) dibujarSeccionPasillo(i);

	glEnable(GL_CULL_FACE);
}


//Funci�n que dibuja el fondo del Crashing Cars

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


//Funci�n que dibuja una imagen en un plano con una textura, tama�o y coordenadas dadas

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


//Funci�n que dibuja una cadena de texto en pantalla

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

		//Calculamos las coordenadas y tama�o del caracter
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

		//Asignamos los nuevos v�rtices a VBOTexto
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


//Funci�n de iluminaci�n del Pong Radial

void iluminacionPong() {

	//Color de la luz del foco
	unsigned int lightColorLoc = glGetUniformLocation(shadersPrincipales, "lightColor");
	glUniform3f(lightColorLoc, tonalidadFoco[0], tonalidadFoco[1], tonalidadFoco[2]); //La tonalidad ser� la indicada por el vector de tonalidadFoco, que se habr� generado aleatoriamente con cada rebote

	//Color de la luz ambiental
	unsigned int ambientColorLoc = glGetUniformLocation(shadersPrincipales, "ambientColor");
	glUniform3f(ambientColorLoc, 1.0f, 1.0f, 1.0f);

	//Intensidad de la luz ambiental
	unsigned int ambientIntensityLoc = glGetUniformLocation(shadersPrincipales, "ambientIntensity");
	glUniform1f(ambientIntensityLoc, intensidadAmbiente); //La intensidad ser� la indicada por intensidadAmbiente, que disminuir� con cada rebote

	//Posici�n de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 0.0, distanciaCamara, 0.0);

	//Posici�n a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, 0.0, 0.0, 0.0);

	//Posici�n de la c�mara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0, distanciaCamara, 0.0);

	//�ngulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 21.5 + 0.3 * nNivelesPalas); //El �ngulo de apertura del foco var�a con el n�mero de niveles de palas
}


//Funci�n de iluminaci�n del Flappy Steve

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

	//Posici�n de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 14.0 - desplazamientoFSLuz, distanciaCamara, -14.0); //La luz se desplazar� progresivamente hacia la izquierda seg�n la variable de desplazamientoFSLuz

	//Posici�n a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, 14.0 - desplazamientoFSLuz, 0.0, -14.0);

	//Posici�n de la c�mara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0, distanciaCamara, 0.0);

	//�ngulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 4.0);
}


//Funci�n de iluminaci�n del Shadow Step

void iluminacionSS() {

	//Seg�n la orientaci�n, asignamos la altura de la c�mara y la altura a la que mira la luz
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

	//Posici�n de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 0.0f, alturaVisionSS, 0.0f);

	//Posici�n a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, distanciaVisionSS * 3.0, alturaLuz, 0.0f); //La luz mira 3 veces m�s lejos de lo que mira la c�mara y a la altura indicada

	//Posici�n de la c�mara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0f, distanciaCamara, 0.0f);

	//�ngulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 8.0f);
}


//Funci�n de iluminaci�n del Crashing Cars

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

	//Posici�n de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, coches[0].px + LARGO_COCHE / 2.0 * cos(coches[0].giro * ARADIANES), 1.5f, coches[0].pz + LARGO_COCHE / 2.0 * -sin(coches[0].giro * ARADIANES));

	//Posici�n a donde mira la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");
	glUniform3f(lookAtLoc, coches[0].px + 3.0 * cos(coches[0].giro * ARADIANES), 0.0f, coches[0].pz + 3.0 * -sin(coches[0].giro * ARADIANES)); //La luz mira al frente del coche

	//Posici�n de la c�mara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0f, distanciaCamara, 0.0f);

	//�ngulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 45.0f);
}


//Funci�n de iluminaci�n del men�

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

	//Posici�n de la luz
	unsigned int lightPosLoc = glGetUniformLocation(shadersPrincipales, "lightPos");
	glUniform3f(lightPosLoc, 0.0, distanciaCamara, 0.0);

	//Objetivo de la luz
	unsigned int lookAtLoc = glGetUniformLocation(shadersPrincipales, "lookAt");

	switch (opcionMenuSeleccionada) {	//El lugar que iluminca el foco depender� de la opci�n seleccionada en el men�
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


	//Posici�n de la c�mara
	unsigned int viewPosLoc = glGetUniformLocation(shadersPrincipales, "viewPos");
	glUniform3f(viewPosLoc, 0.0, distanciaCamara, 0.0);

	//�ngulo apertura
	unsigned int cutoffLoc = glGetUniformLocation(shadersPrincipales, "spotCutoff");
	glUniform1f(cutoffLoc, 8);
}


//Funci�n de posicionamiento de la c�mara del Pong Radial

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

	//Matriz de proyecci�n

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}


//Funci�n de posicionamiento de la c�mara del Flappy Steve

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

	//Matriz de proyecci�n

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


//Funci�n de posicionamiento de la c�mara del Shadow Step

void posicionarCamaraSS() {

	//Seg�n la orientaci�n seleccionada, se cambiar� la orientaci�n de la c�mara, su altura y la altura a la que mirar� (alturaLuz, ya que es la misma que la de la luz)
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

	//Matriz de proyecci�n

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}


//Funci�n de posicionamiento de la c�mara del Crashing Cars

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

	//Matriz de proyecci�n

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


//Funci�n de posicionamiento de la c�mara del men�

void posicionarCamaraMenu() {

	glViewport(0, 0, anchoVentana, alturaVentana);	//Vista de tama�o de la ventana

	//Matriz de vista

	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(0.0f, distanciaCamara, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f));
	unsigned int viewLoc = glGetUniformLocation(shadersPrincipales, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//Matriz de proyecci�n

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(fovy), (float)anchoVentana / (float)alturaVentana, limiteCerca, limiteLejos);
	unsigned int proyectionLoc = glGetUniformLocation(shadersPrincipales, "projection");
	glUniformMatrix4fv(proyectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}


//Funci�n que dibuja el texto del pong

void dibujarTextoPong() {

	//El brillo de las letras se reducir� al reducirse la intensidad ambiente
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

	//Se dibuja la informaci�n sobre los controles
	if (mostrarControles) {

		dibujarTexto("Espacio: Cambiar sentido", 725.0, alturaVentana - 25.0, 1.0f, color);
		dibujarTexto("ESC: Volver al menu", 770.0, alturaVentana - 50.0, 1.0f, color);
		dibujarTexto("P: Pausar", 886.0, alturaVentana - 75.0, 1.0f, color);
	}
	else {

		dibujarTexto("C: Mostrar controles", 751.0, alturaVentana - 25.0, 1.0f, color);
	}

	//El mensaje de informaci�n s�lo se dibujar� si su contador es mayor que 0
	if (contadorMensajeInfo > 0) {
		dibujarTexto(mensajeInfo, (anchoVentana / 2.0) - 12.0 * mensajeInfo.size() / 2.0, alturaVentana / 2.0, 1.0f, colorMensajeInfo);
	}
}


//Funci�n que dibuja el texto del Flappy Steve

void dibujarTextoFS() {

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	//Se dibuja el contador
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalFS);
	dibujarTexto(cadena, 25.0, 25.0, 1.0f, color);

	//Se dibuja la informaci�n sobre los controles
	if (mostrarControles) {

		dibujarTexto("ESC: Volver al menu", 750.0, 25.0, 1.0f, color);
		dibujarTexto("Espacio: Saltar", 798.0, 50.0, 1.0f, color);
		dibujarTexto("P: Pausar", 866.0, 75.0, 1.0f, color);
	}
	else {

		dibujarTexto("C: Mostrar controles", 732.0, 25.0, 1.0f, color);
	}
}


//Funci�n que dibuja el texto del Shadow Step

void dibujarTextoSS() {

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	//Se dibuja el contador
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalSS);
	dibujarTexto(cadena, 25.0, 25.0, 1.0f, color);

	//Se dibuja la informaci�n sobre los controles
	if (mostrarControles) {

	dibujarTexto("Espacio: Invertir altura", 703.0, 25.0, 1.0f, color);
	dibujarTexto("ESC: Volver al menu", 750.0, 50.0, 1.0f, color);
	dibujarTexto("P: Pausar", 866.0, 75.0, 1.0f, color);
	}
	else {

		dibujarTexto("C: Mostrar controles", 732.0, 25.0, 1.0f, color);
	}
}


//Funci�n que dibuja el texto del Crashing Cars

void dibujarTextoCC() {

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	//Se dibuja el contador
	std::string cadena = "Puntuacion: " + std::to_string(contadorTotalCC);
	dibujarTexto(cadena, 25.0, 25.0, 1.0f, color);

	//Se dibuja la informaci�n sobre los controles
	if (mostrarControles) {

	dibujarTexto("Espacio: Mover coches", 730.0, 25.0, 1.0f, color);
	dibujarTexto("ESC: Volver al menu", 750.0, 50.0, 1.0f, color);
	dibujarTexto("P: Pausar", 866.0, 75.0, 1.0f, color);
	}
	else {

	dibujarTexto("C: Mostrar controles", 732.0, 25.0, 1.0f, color);
	}
}


//Funci�n que dibuja el texto de pausa centrado en pantalla (si se ha seleccionado la opci�n)

void dibujarMensajePausa() {
	if (pausa) dibujarTexto("Pausa", (anchoVentana / 2.0) - 12.0 * 5 / 2.0, alturaVentana / 2.0, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}


//Funci�n de dibujo del Pong Radial

void dibujoPong() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	posicionarCamaraPong();		//Se posiciona la c�mara

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

	iluminacionPong();			//Se aplica la iluminaci�n
	dibujarTextoPong();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Funci�n que dibuja el Flappy Steve

void dibujoFS() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	iluminacionFS();		//Se aplica la iluminaci�n

	posicionarCamaraFS();	//Se posiciona la c�mara

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


//Funci�n que dibuja el Shadow Step

void dibujoSS() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	iluminacionSS();		//Se aplica la iluminaci�n

	posicionarCamaraSS();	//Se posiciona la c�mara

	dibujarPasilloSS();		//Se dibuja el pasillo

	//Se dibujan todos los obst�culos
	for (Obstaculo obstaculo : obstaculos) obstaculo.dibujar(esfera);

	dibujarTextoSS();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Funci�n que dibuja el Crashing Cars

void dibujoCC() {

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	iluminacionCC();		//Se aplica la iluminaci�n

	posicionarCamaraCC();	//Se posiciona la c�mara

	dibujarFondoCC();		//Se dibuja el fondo

	//Dibujamos los coches
	for (int i = 0; i < coches.size(); i++) {
		coches[i].dibujar();
		//dibujarHitboxCoche(coches[i]);
	}

	dibujarTextoCC();			//Se dibuja el texto
	dibujarMensajePausa();		//Se dibuja (o no) el mensaje de pausa
}


//Funci�n que dibuja el men�

void dibujoMenu() {

	//Se dibujar� el texto de los r�cords color blanco
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	std::string textoRecords;

	//Limpiamos los buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, anchoVentana, alturaVentana);

	posicionarCamaraMenu();		//Se posiciona la c�mara

	//Se dibuja el fondo
	dibujarImagen(texturaMenu, TAMANO_FONDO_MENU, TAMANO_FONDO_MENU, 0, 0, 0);

	//Se dibujan todos los t�xtos que indican los r�cords
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

	//Se dibuja la informaci�n sobre los controles
	if (mostrarControles) {

		dibujarTexto("Enter: Seleccionar opcion", 680.0f, alturaVentana - 75.0f, 1.0f, color);
		dibujarTexto("<- / -> : Cambiar opcion", 715.0f, alturaVentana - 100.0f, 1.0f, color);
		dibujarTexto("ESC: Salir", 858.0f, alturaVentana - 125.0f, 1.0f, color);
	}
	else {

	dibujarTexto("C: Mostrar controles", 725.0, alturaVentana - 75.0, 1.0f, color);
	}

	iluminacionMenu();	//Se aplica la iluminaci�n
}

////////////////////////////////////////////////////////////////////////////////////// Funciones de carga inicial //////////////////////////////////////////////////////////////////////////////////////


//Funci�n que inicializa el vector de palas

void inicializarPalas() {

	for (int i = 0; i < NUM_NIVELES_PALAS_INICIAL; i++) {
		anadirNivelPalas();
	}
}


//Funci�n que inicializa los vectores de pelotas

void inicializarPelotas() {
	anadirPelota(0); //Se a�ade una pelota normal
}


//Funci�n que carga el VAO de un cuadrado

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


//Funci�n que carga el VAO de un cubo

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


//Funci�n que carga el VAO de un c�rculo

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


//Funci�n que carga el VAO del texto

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


//Funci�n que carga una textura dado el nombre del archivo y devuelve su �ndice

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


//Funci�n que carga las texturas

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


//Funci�n que inicializa los VAOs

void cargarVAOs() {

	//Cargamos los VAOs
	cargarVAOCuadrado(&VAOPlano);
	cargarVAOCubo(&VAOCubo);
	cargarVAOCirculo(&VAOCirculo);
	cargarVAOTexto();
}


//Funci�n de inicializaci�n de las variables de openGL

void openGlInit() {

	//Incializaciones varias
	glClearDepth(1.0f);										//Asignamos una profundidad de borrado
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					//Asignamos el valor de limpieza del buffer de color
	glEnable(GL_DEPTH_TEST);								//Activamos el Z-Buffer
	glEnable(GL_CULL_FACE);									//Activamos la ocultaci�n de las caras traseras
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);				//Dibujamos en modo fill

	glEnable(GL_BLEND);										//Activamos la transparencia
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Funci�n que carga los primeros 128 caracteres de la fuente indicada

void cargarCaracteres(const char* archivoFuente) {

	if (FT_Init_FreeType(&ft)) printf("Error al inicializar la libreria\n");				//Se inicializa la librer�a
	if (FT_New_Face(ft, archivoFuente, 0, &face)) printf("Error al cargar la fuente\n");	//Se carga la fuente del archivo
	FT_Set_Pixel_Sizes(face, 0, 28);														//Se asigna el tama�o de los caracteres en p�xeles

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //Se deshabilita la restricci�n de alineamiento de bytes

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


//Funci�n que realiza las preparaciones necesarias antes de ejecutar el Pong Radial

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

	//Inicializaci�n de variables de openGL
	openGlInit();

	//Inicializar palas
	inicializarPalas();

	//Inicializar pelotas
	inicializarPelotas();

	//Activamos la m�sica de fondo
	PlaySound(TEXT("Sonidos/MusicaPong.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Funci�n que realiza las preparaciones necesarias antes de ejecutar el Flappy Steve

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

	//Inicializaci�n de variables de openGL
	openGlInit();

	//Reiniciamos el temporizador
	cronometroFS = glfwGetTime();
	avanceCronometroFS = 0;

	//A�adimos la primera torre
	anadirTorresFS(0);

	//Activamos la m�sica de fondo
	PlaySound(TEXT("Sonidos/MusicaFS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Funci�n que realiza las preparaciones necesarias antes de ejecutar el Shadow Step

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

	//Inicializaci�n de variables de openGL
	openGlInit();

	//Asignamos los valores iniciales a las distancias de las secciones del pasillo
	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS; i++) desplazamientoSeccionesSS[i] = -LARGO_SUELO_SS * i;

	//Asignamos los valores iniciales a los �ndices de las texturas de los cuadros
	for (int i = 0; i < NUM_SECCIONES_PASILLO_SS * 2; i++) cuadros.push_back(texturaCuadroAleatoria());

	//Reiniciamos el temporizador
	cronometroSS = glfwGetTime();
	avanceCronometroSS = 0;

	//Activamos la m�sica de fondo
	PlaySound(TEXT("Sonidos/MusicaSS.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Funci�n que realiza las preparaciones necesarias antes de ejecutar el Crashing Cars

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

	//Inicializaci�n de variables de openGL
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

	//Activamos la m�sica de fondo
	PlaySound(TEXT("Sonidos/MusicaCC.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP | SND_FILENAME);
}


//Funci�n que realiza las preparaciones necesarias antes de ejecutar el men�

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

	//Inicializaci�n de variables de openGL
	openGlInit();
}


//Funci�n que inicializa los objetos globales que lo necesiten

void inicializarObjetosGlobales() {

	steve.VAO = VAOPlano;
	steve.textura = texturaSteve;

	desplazamientoSeccionesSS.reserve(NUM_SECCIONES_PASILLO_SS);
}


//Funci�n que abre el archivo de guardado y lee los datos

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


//Funci�n que guarda los records actuales en el archivo de guardado

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


//Funci�n que realiza las preparaciones necesarias antes de poder comenzar el programa

void cargaInicialPrograma() {

	srand(time(0));	//Establecemos una semilla para el rand (momento actual, para que sea realmente aleatorio)

	shadersPrincipales = setShaders("Shaders/shaderPrincipal.vert", "Shaders/shaderPrincipal.frag");
	shadersTexto = setShaders("Shaders/shaderTexto.vert", "Shaders/shaderTexto.frag");

	//Cargamos los caracteres de la fuente que vamos a usar
	cargarCaracteres("Fuentes/digital-7.ttf");

	//Abrimos el archivo de guardado
	abrirArchivoGuardado();

	//Inicializaci�n de las texturas
	cargarTexturas();

	//Inicializaci�n de los VAOs
	cargarVAOs();

	//Inicializamos los atributos de los objetos globales
	inicializarObjetosGlobales();
}


//Funci�n que se encarga de limitar los FPS a los indicados

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

	//Asignamos la funci�n de gestion de teclado
	glfwSetKeyCallback(window, gestionTeclado);

	//Se realiza la carga inicial del programa
	cargaInicialPrograma();

	//Se realiza la carga inicial del men�
	cargaInicialMenu();

	//Asignamos los shaders principales
	glUseProgram(shadersPrincipales);

	//Inicializamos el contador para los FPS
	double medidorFPS = glfwGetTime() * 1000.0;

	//Bucle principal

	while (!glfwWindowShouldClose(window))
	{
		switch (juegoSeleccionado) {

		case 0:		//Men�

			dibujoMenu();			//Dibujamos la escena
			break;

		case 1:		//Pong Radial

			dibujoPong();			//Dibujamos la escena
			actualizacionPong();	//Actualizamos los valores
			break;

			/*Se aprecia mejor si se dibuja el estado anterior y despu�s se actualiza al siguiente ya que, si se hace al rev�s,
			se tiene en cuenta en la actualizaci�n informaci�n que a�n no se ha mostrado y resulta confuso visualmente*/

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

		//Nos aseguramos de que el programa no vaya a m�s FPS de los indicados
		gestionFPS(&medidorFPS);
	}

	//Eliminamos los arrays de v�rtices
	glDeleteVertexArrays(1, &VAOPlano);
	glDeleteVertexArrays(1, &VAOCubo);
	glDeleteVertexArrays(1, &VAOCirculo);

	//Guardamos la informaci�n de los r�cords en el archivo de guardado
	guardarArchivo();

	glfwTerminate();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////// Otras funciones //////////////////////////////////////////////////////////////////////////////////////

//Funci�n de gesti�n de la entrada por teclado

void gestionTeclado(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {		//P
		pausa = !pausa;

		if (pausa) {	//Al entrar en pausa, guardamos el avance del intervalo de los cron�metros del FS y el SS

			avanceCronometroFS = glfwGetTime() - cronometroFS;
			avanceCronometroSS = glfwGetTime() - cronometroSS;
		}
		else {			//Al salir de la pausa, restablecemos la diferencia entre el tiempo actual y el cron�metro a la almacenada anteriormente

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

		case 3:					//En el Shadow Step, pulsar el espacio alterna la orientaci�n de la c�mara entre el suelo y el techo

			orientacion = !orientacion;
			break;

		case 4:					//En el Crarshing Cars, pulsar el espacio hace que el coche avance hasta que encuentre un obst�culo

			for (int i = 0; i < coches.size(); i++) coches[i].movimiento = 1;
			break;

		default:
			break;
		}
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {	//Enter

		//Si se est� en el men�, selecciona una opci�n
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

		//Vuelve al men� o vuelve al men� si se est� jugando a alg�n juego
		if (!juegoSeleccionado) glfwSetWindowShouldClose(window, true);
		else volverAlMenu = 1;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {	//Flecha derecha

		//Se cambia la opci�n seleccionada del men�
		if (!juegoSeleccionado) {

			opcionMenuSeleccionada++;
			PlaySound(TEXT("Sonidos/OpcionMenu.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
			if (opcionMenuSeleccionada >= OPCIONES_MENU) opcionMenuSeleccionada -= OPCIONES_MENU;
		}
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {		//Flecha derecha

		//Se cambia la opci�n seleccionada del men�
		if (!juegoSeleccionado) {

			opcionMenuSeleccionada--;
			PlaySound(TEXT("Sonidos/OpcionMenu.wav"), NULL, SND_NODEFAULT | SND_ASYNC | SND_FILENAME);
			if (opcionMenuSeleccionada < 0) opcionMenuSeleccionada += OPCIONES_MENU;
		}
	}
}