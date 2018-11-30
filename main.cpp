/**
**	Sergio Ramos Mesa y Pablo Jiménez Cruz
**	1ºB 
**/

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//DEFINICIONES DE CONSTANTES, ENUMERADOS Y ARRAYS
const int TAM_CODIGO = 4;
const int JUGADAS_MAX = 15;
const int NUM_COLORES = 6;
typedef enum { Rojo, Azul, Verde, Amarillo, Marron, Blanco, Incorrecto }tColor;
typedef tColor tCodigo[TAM_CODIGO];

//PROTOTIPOS DE FUNCIONES	
int menu();
int resultado(tCodigo codigo, tCodigo hipotesis);
void bienvenida();
void codigoAleatorio(tCodigo codigo, bool admiteRepetidos);
void compararCodigos(const tCodigo codigo, const tCodigo hipotesis, int & colocados, int & descolocados);
void mostrarResultados(tCodigo codigo, tCodigo hipotesis, int colocados, int descolocados);
char color2Char(tColor color);
bool pedirCodigo(tCodigo codigo);
tColor char2Color(char caracter);
tColor generaColor();

//FUNCIONES DEL PROGRAMA
int main(){
	srand(time(NULL));
	bienvenida();
	int opc = menu();
	while (opc != 0) { opc = menu(); }
	system("pause");
	return 0;
}

void bienvenida(){
	char caracter;
	cout << "[ Este programa no usa tildes por motivos tecnicos ]" << endl;
	cout << "                     MASTERMIND" << endl << endl;
	cout << "Descubre el codigo secreto! En cada partida, pensare un codigo de" << endl;
	cout << "colores que tendras que adivinar.En cada intento que hagas te" << endl;
	cout << "dare pistas, diciendote cuantos colores de los que has dicho estan" << endl;
	cout << "bien colocados, y cuantos no." << endl << endl;
	cout << "Averigua el codigo secreto en el menor numero posible de intentos!" << endl << endl;
	cout << "Has de saber que el programa solo funciona en el modo (NO REPETIDOS)\nsi y solo si hay colores suficientes para rellenar todas las posiciones" << endl << endl;
	cout << "Las letras disponibles son: ";
}



int menu(){
	tCodigo hipotesis, codigo;
	bool admiteRepetidos = false;
	int opc, jugadas;
	cout << "1 -> Jugar con colores repetidos" << endl;
	cout << "2 -> Jugar sin colores repetidos" << endl;
	cout << "0 -> Salir" << endl;
	cout << "Elige una opcion para continuar: ";
	cin >> opc;
	while ((opc < 0) && (opc > 2)){
		cout << "Error inesperado, introduzca de nuevo la opcion: ";
		cin >> opc;
	}
	if (opc > 0){
		if (opc == 1){
			cout << endl << "JUGAR CON COLORES REPETIDOS" << endl << endl;
			admiteRepetidos = true;
		}
		else{ cout << endl << "JUGAR SIN COLORES REPETIDOS" << endl << endl; }
		codigoAleatorio(codigo, admiteRepetidos);
		jugadas = resultado(codigo, hipotesis);
		cout << "Te ha costado " << jugadas << " intento(s)" << endl;
	}
	return opc;
}

bool repetido(tCodigo codigo, tColor color, int posicion) {
	bool repetido = false;
	for (int contador = 0; contador < posicion; contador++) {
		if (codigo[contador] == color) {
			repetido = true;
		}
	}
	return repetido;
}

tColor generaColor() {
	int numero;
	tColor color;
	numero = rand() % 6;
	switch (numero) {
	case 0: color = Rojo; break;
	case 1: color = Azul; break;
	case 2: color = Verde; break;
	case 3: color = Amarillo; break;
	case 4: color = Marron; break;
	case 5: color = Blanco; break;
	default: color = Incorrecto; break;
	}
	return color;
}

void codigoAleatorio(tCodigo codigo, bool admiteRepetidos){
	tColor color;
	int posicion = 0;
	color = generaColor();
	codigo[posicion] = color;
	posicion++;

	while (posicion < TAM_CODIGO){
		color = generaColor();
		if (admiteRepetidos) { codigo[posicion] = color; }
		else{
			while (repetido(codigo, color, posicion)) { color = generaColor(); }
			codigo[posicion] = color;
		}
		posicion++;
	}
}


bool pedirCodigo(tCodigo hipotesis){
	tColor codigoColor;
	char ap, caracter;
	int posicion = 0;
	bool fallo = false;
	cout << "Introduzca el codigo (Palabras de " << TAM_CODIGO << "letras con alguna de ";
	for (int i = 0; i < NUM_COLORES; i++){
		caracter = color2Char(tColor(i));
		cout << caracter <<" ";
	}
	cout << ")" << endl;

	while (posicion < TAM_CODIGO){
		cin >> ap;
		ap = toupper(ap);
		codigoColor = char2Color(ap);
		if (codigoColor == Incorrecto) { fallo = true; }
		hipotesis[posicion] = codigoColor;
		posicion++;
	}
	return fallo;
}

int resultado(tCodigo codigo, tCodigo hipotesis) {
	int jugadas = 0;
	bool encontrado = false, fallo = false;
	while ((!encontrado) && (jugadas < JUGADAS_MAX)) {
		int colocados = 0, descolocados = 0;
		fallo = pedirCodigo(hipotesis);
		if (!fallo){
			compararCodigos(codigo, hipotesis, colocados, descolocados);
			mostrarResultados(codigo, hipotesis, colocados, descolocados);
			jugadas++;
		}
		else { cout << "Error inesperado, jugada no valida" << endl; }
		if (colocados == TAM_CODIGO) { encontrado = true; }
	}
	return jugadas;
}

void compararCodigos(const tCodigo codigo, const tCodigo hipotesis, int & colocados, int & descolocados) {
	int j;
	bool encontrado;
	bool leidosCodigo[TAM_CODIGO], leidosHipotesis[TAM_CODIGO];
	for (int pos = 0; pos < TAM_CODIGO; pos++) {
		if (codigo[pos] == hipotesis[pos]) {
			colocados++;
			leidosCodigo[pos] = true;
			leidosHipotesis[pos] = true;
		}
		else {
			leidosCodigo[pos] = false;
			leidosHipotesis[pos] = false;
		}
	}
	for (int i = 0; i < TAM_CODIGO; i++) {
		j = 0;
		encontrado = false;
		while ((leidosCodigo[i] == false) && (j < TAM_CODIGO)) {
			if ((leidosHipotesis[j] == false) && (!encontrado)) {
				if ((codigo[i] == hipotesis[j]) && (leidosCodigo[i] == false) && (leidosHipotesis[j] == false)) {
					descolocados++;
					leidosHipotesis[j] = true;
					encontrado = true;
				}
			}
			j++;
		}
	}
}

void mostrarResultados(tCodigo codigo, tCodigo hipotesis, int colocados, int descolocados){
	cout << "HIPOTESIS\tCOLOCADOS\tDESCOLOCADOS" << endl;
	for (int i = 0; i < TAM_CODIGO; i++){
		switch (hipotesis[i]){
		case 0: cout << "R"; break;
		case 1: cout << "Z"; break;
		case 2: cout << "V"; break;
		case 3: cout << "A"; break;
		case 4: cout << "M"; break;
		case 5: cout << "B"; break;
		default: cout << "_";  break;
		}
	}
	cout << "\t\t" << colocados << "\t\t" << descolocados << endl;
}

tColor char2Color(char caracter) {
	tColor color;
	switch (caracter) {
	case 'R': color = Rojo; break;
	case 'Z': color = Azul; break;
	case 'V': color = Verde; break;
	case 'A': color = Amarillo; break;
	case 'M': color = Marron; break;
	case 'B': color = Blanco; break;
	default: color = Incorrecto; break;
	}
	return color;
}

char color2Char(tColor color){
	char caracter;
	switch (color){
	case Rojo: caracter = 'R'; break;
	case Azul: caracter = 'Z'; break;
	case Verde: caracter = 'V'; break;
	case Amarillo: caracter = 'A'; break;
	case Marron: caracter = 'M'; break;
	case Blanco: caracter = 'B'; break;
	default: caracter = 'I'; break;
	}
	return caracter;
}