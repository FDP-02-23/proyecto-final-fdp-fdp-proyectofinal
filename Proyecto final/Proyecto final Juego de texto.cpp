#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include < cmath >
#include <windows.h>
#include <stdio.h>
#include <fstream>


using namespace std;

//variable global importante ya que se necesita cambiar en differentes funciones para correr el programa
int InstaciaDeCuarto = 0 ;
bool finalizar = true;
bool CuartoRevisado[10] {true,true,true,true,true,true,true,true,true, true};

//guardando progreso;
void GuardarProgreso();
// iniciar de ultima instancia de guardado
bool Leerprogreso();
//impresion con effecto
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
int main(int argc, const char* avrg[])
{
	struct personaje jugador;
	string OpcionGuardado;


	type("comenzar nueva partida o regresar al calabozo\n");

	do
	{
		type("Escribe una de las opciones aqui : ");
		getline(cin, OpcionGuardado);

		if (OpcionGuardado == "comenzar nueva partida")
		{
			type("cual es tu nombre ? :");
			getline(cin, jugador.Nombre);

			//repite la busqueda de cuarto 
			do
			{
				SelecionDeCuarto(InstaciaDeCuarto);


			} while (finalizar);


		}
		else if (OpcionGuardado == "regresar al calabozo")
		{

			if (Leerprogreso())
			{
				do
				{
					SelecionDeCuarto(InstaciaDeCuarto);


				} while (finalizar);
			}
		}

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

		//no es necesario ya que el numero siempre va a estar en el valor correcto 
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

	
	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("te encuentras en cuarto 0 que vas hacer  \n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


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
				void GuardarProgreso();

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
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
				type("ya no hay nada que recoger\n\n");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				void GuardarProgreso();
			}



		} while (Salida);
	}

}



void Cuarto1() {

	struct personaje stats;
	string opcion;
	bool Salida = true;
	bool escogida = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("te encuentras en cuarto 1 que vas hacer  \n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse este")
			{
				cout << "te mueves en direccion en la puerta al este" << endl;
				InstaciaDeCuarto = 2;
				cout << InstaciaDeCuarto;
				Salida = false;

			}
			
			if (opcion == "Atacar duende")
			{
				
				/// funcion de atacar
				escogida = true;
			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				void GuardarProgreso();

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
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
				type("ya no hay nada que recoger\n\n");

			}
			if (opcion == "Atacar duende")
			{
				type("el enemigo fue derotado ");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				void GuardarProgreso();
			}



		} while (Salida);
	}

}

//imprime lista de comandos 
void opcionAyuda() {
	
	cout << "\t\t********* Lista de comandos *********\n";
	printf("%-35s%-35s\n", "1. Moverse (norte,sur,este,oeste)", "2. Recoger (arma,armadura)");
	printf("%-35s%-35s\n\n", "3. Atacar (nombre mounstro)", "4. Guardar pogreso")
		;
	

}

//funcion para el efecto de escribir el texto 

// inheritence convetir en clase for innheritance a los otros programas.
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
	::Sleep(350);
}

// sistema de guardado de variables para el progreso en el juego 
void GuardarProgreso() {

	ofstream ProgresoDelJugador("ProgresoGuardado.txt");
	struct personaje jugador;

	//primeras 5 son elnombre y estadisticas del jugador
	ProgresoDelJugador << jugador.Nombre<<endl;
	ProgresoDelJugador << jugador.HP<<endl;
	ProgresoDelJugador << jugador.defensa << endl;
	ProgresoDelJugador << jugador.ataque << endl;
	ProgresoDelJugador << jugador.movilidad << endl;

	//en el cuarto que el presonaje se encuentra 
	ProgresoDelJugador << InstaciaDeCuarto << endl;

	cout << "se encontro ";

	//variables del arreglo de cuarto revisado
	for (int i = 0; i < 10; i++)
	{
		ProgresoDelJugador << CuartoRevisado[i] << endl;
	}

	ProgresoDelJugador.close();

}

bool Leerprogreso() {
	struct personaje jugador;
	ifstream JuegoGuardado;
	JuegoGuardado.open("ProgresoGuardado.txt");

	if (JuegoGuardado.is_open() == true)
	{
		//primeras 5 son elnombre y estadisticas del jugador
		JuegoGuardado >> jugador.Nombre;
		JuegoGuardado >> jugador.HP;
		JuegoGuardado >> jugador.defensa;
		JuegoGuardado >> jugador.ataque;
		JuegoGuardado >> jugador.movilidad;

		//en el cuarto que el presonaje se encuentra 
		JuegoGuardado >> InstaciaDeCuarto;


		//variables del arreglo de cuarto revisado
		for (int i = 0; i < 10; i++)
		{
			JuegoGuardado >> CuartoRevisado[i];
		}

		JuegoGuardado.close();

		return true;
	}else
	{
		type("No hay progreso guardados\n");
		return false;

	}


}