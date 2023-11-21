#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include < cmath >
using namespace std;

//variable global importante ya que se necesita cambiar en differentes funciones para correr el programa
int InstaciaDeCuarto = 0 ;

//inicio de funciones
void SelecionDeCuarto(int Numcuarto);
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
int main()
{
	struct personaje jugador;
	
	cout << "cual es tu nuombre aventurero? : ";
	cin >> jugador.Nombre;

	//repite la busqueda de cuarto 
	do
	{
		SelecionDeCuarto(InstaciaDeCuarto);


	} while (true);
	
   
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

	cout << "te encuentras en cuarto 0 que vas hacer : \n" ;

	cin.ignore();
	getline(cin , opcion); 

	transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
	

	
	
	do
	{

		if (opcion == "moverse norte")
		{
			cout << "te mueves en direccion en la puerta al norte" << endl;
			InstaciaDeCuarto = 1;
			Salida = false;

		}
		if (opcion == "recoger arma")
		{
			

			if (escogida == true)
			{
				cout << "ya no hay nada que recoger" << endl;
				
			}
			else {
				cout << "descripcion de la arma "<<endl;
				//stats.ataque = stats.ataque + ; //equipamiento.nombredearma

				escogida = true;
			}
				

		}
		if (opcion == "ayuda") 
		{


		}

		

	} while (Salida);

}

void Cuarto1() {

	cout << "te encuentras en cuarto 2" << endl;
}


