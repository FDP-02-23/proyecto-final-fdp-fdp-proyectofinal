#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include < cmath >
#include <windows.h>
#include <stdio.h>

using namespace std;

//variable global importante ya que se necesita cambiar en differentes funciones para correr el programa
int InstaciaDeCuarto = 0 ;
bool finalizar = true;

void type(const char* p);
//funcion de localicacion de cuartos
void SelecionDeCuarto(int Numcuarto);
// impresion de menu de ayuda
void opcionAyuda();
// funcion individual de cuarto y su respective historia 
void Cuarto0();
void Cuarto1();

struct personaje
{
	string Nombre;
	int HP = 75;
	int defensa = 10;
	int ataque = 10;
	int movilidad = 10;


};


// main llama la ubicacion del personaje para llamar la ubicacion .
int main(int argc, const char * avrg[])
{
	struct personaje jugador;
	
	type("cual es tu nombre ? :");
		getline(cin, jugador.Nombre);

	//repite la busqueda de cuarto 
	do
	{
		SelecionDeCuarto(InstaciaDeCuarto);


	} while (finalizar);
	
   
}

// funcion de seleccion de cuarto en la historia
void SelecionDeCuarto(int Numcuarto) {

// utiliza la variable global como indicador de cuarto
	switch (Numcuarto)
	{
	case 0:
		Cuarto0();
		break;
	case 1:
		Cuarto1();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	default:
		break;
	}
	

}

void Cuarto0() {
	// la opcion muestra 
	struct personaje stats;
	string opcion;
	bool Salida = true; 
	bool escogida = false;

	type("te encuentras en cuarto 0 que vas hacer  \n\n");

	
	

	
	
	do
	{
		
		cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
		getline(cin, opcion);
		transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
		cout << opcion << endl;
		

		if (opcion == "moverse norte")
		{
			cout << "te mueves en direccion en la puerta al norte" << endl;
			InstaciaDeCuarto = 1;
			cout << InstaciaDeCuarto;
			Salida = false;

		}
		if (opcion == "recoger arma")
		{
			

			if (escogida == true)
			{
				type("ya no hay nada que recoger\n\n");
			}
			else {
				type("descripcion de arma\n\n");
				// funcion de equpar armadura 

				escogida = true;
			}
				

		}
		if (opcion == "ayuda") 
		{
			opcionAyuda();

		}
		if (opcion == "guardar progreso")
		{
			
		}

		

	} while (Salida);

}



void Cuarto1() {

	cout << "te encuentras en cuarto 2" << endl;
}

//imprime lista de comandos 
void opcionAyuda() {
	
	cout << "\t\t********* Lista de comandos *********\n";
	printf("%-35s%-35s\n", "1. Moverse (norte,sur,este,oeste)", "2. Recoger (arma,armadura)");
	printf("%-35s%-35s\n\n", "3. Pelear (nombre mounstro)", "4. Guardar pogreso");
	

}

//funcion para el efecto de escribir el texto 
void type(const char *p) {

	if (NULL == p)
		return;
	
	while (*p)
	{
		printf("%c\xDB", *p++);
		::Sleep(40);
		printf("\b \b");
		::Sleep(40);
	}
	::Sleep(300);
}




