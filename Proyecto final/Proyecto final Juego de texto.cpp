#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <cmath>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <random>




using namespace std;

struct entidad
{

	int hp, def, atk, agilidad;

};
struct Armas {
	int karambit = 12;
	int Katana = 14;
	int fierroGolpeadorDeParejasFelices = 16;
};

struct Armaduras {
	int liviana[2]{ 14,12 }; //posicion 0 es la defensa y la posicion 1 es la agilidad
	int pesada[2]{ 16,8 };
};




//variable global importante ya que se necesita cambiar en differentes funciones para correr el programa
int InstaciaDeCuarto = 0;
bool finalizar = true;
bool CuartoRevisado[10]{ true,true,true,true,true,true,true,true,true, true };
int monstruoEnCombate = 0;


//guardando progreso;
void GuardarProgreso(entidad& jugador);
// iniciar de ultima instancia de guardado
bool Leerprogreso(entidad& jugador);
//impresion con effecto
void type(const char* p);
//funcion de localicacion de cuartos
void SelecionDeCuarto(int Numcuarto, entidad& jugador, entidad* monstuos);
// impresion de menu de ayuda
void opcionAyuda();
// funcion individual de cuarto y su respective historia 
void Cuarto0(entidad& jugador);
void Cuarto1(entidad& jugador, entidad* monstruos);
void cuarto2(entidad& jugador);
void cuarto3(entidad& jugador, entidad* monstruos);
void cuarto4(entidad& jugador);
void cuarto5(entidad& jugador, entidad* monstruos);
void cuarto6(entidad& jugador);
void cuarto7(entidad& jugador, entidad* monstruos);
void cuarto8(entidad& jugador);
void cuarto9(entidad& jugador, entidad* monstruos);


//funciones de combate
int bono(entidad& personaje, entidad* monstruos, int monstruoEnCombate, int pPrincip, int ag);
int dado(int tipoDadoEnfrentamiento);
void displayClock(entidad& personaje, int seconds);
int correr(entidad& personaje);
int Descansar(entidad& personaje);
int AtaquePersonaje(int monstruoEnCombate, entidad* monstruos, entidad& personaje, int ataqueBonoPersonaje, int tipoDadoEnfrentamiento);
int TurnoMonstruo(entidad& personaje, int ataqueBonoMonstruo, int tipoDadoEnfrentamiento);
int enfrentamiento(int monstruoEnCombate, entidad* monstruos, entidad& personaje, bool finCombate);











// main llama la ubicacion del personaje para llamar la ubicacion .
int main(int argc, const char* avrg[])
{
	entidad jugador = {75,10,10,10};//estadisticas del personaje


	entidad monstruos[5];//estadisticas de los monstruos
	//posicion 0 es la del duende   |hp30,def07,atk06,ag12
	//posicion 1 es la del esqueleto|hp45,def12,atk08,ag08 
	//posicion 2 es la del mimic    |hp50,def08,atk12,ag10 
	//posicion 3 es la del centauro |hp60,def14,atk10,ag14
	//posicion 4 es la del dragon   |hp90,def16,atk16,ag16 

	//duende
	monstruos[0] = { 30,7,6,12 };

	//esqueleto
	monstruos[1] = { 45,12,8,8 };

	//mimic
	monstruos[2] = { 50,8,12,10 };

	//centauro
	monstruos[3] = { 60,14,10,14 };

	//dragon
	monstruos[4] = { 90,16,16,16 };


	string OpcionGuardado;

	type("Bienvenido aventuro , hoy demostraras tu coraje al intentar escapar el calabozo. Lograras salir un heroe? \n");
	type("Quieres : comenzar nueva partida o regresar al calabozo\n");

	do
	{
		type("Escribe una de las opciones aqui : ");
		getline(cin, OpcionGuardado);



		if (OpcionGuardado == "comenzar nueva partida")
		{

			//repite la busqueda de cuarto 
			do
			{
				SelecionDeCuarto(InstaciaDeCuarto, jugador, monstruos);


			} while (finalizar);


		}
		else if (OpcionGuardado == "regresar al calabozo")
		{

			if (Leerprogreso(jugador))
			{
				do
				{
					SelecionDeCuarto(InstaciaDeCuarto, jugador, monstruos);


				} while (finalizar);
			}
		}

	} while (finalizar);


}





// funcion de seleccion de cuarto en la historia
void SelecionDeCuarto(int Numcuarto, entidad& jugador, entidad* monstruos) {

	// utiliza la variable global como indicador de cuarto
	switch (Numcuarto)
	{
	case 0:
		Cuarto0(jugador);
		break;
	case 1:
		Cuarto1(jugador, monstruos);
		break;
	case 2:
		cuarto2(jugador);
		break;
	case 3:
		cuarto3(jugador, monstruos);
		break;
	case 4:
		cuarto4(jugador);
		break;
	case 5:
		cuarto5(jugador, monstruos);
		break;
	case 6:
		cuarto6(jugador);
		break;
	case 7:
		cuarto7(jugador, monstruos);
		break;
	case 8:
		cuarto8(jugador);
		break;
	case 9:
		cuarto9(jugador, monstruos);
		break;

		//no es necesario ya que el numero siempre va a estar en el valor correcto 
	default:
		break;
	}


}

/// <summary>
/// las siguientes funciones son funciones de cuartos que manejan todos los sistemas de peleas,armas y armadura ademas incluyen funciones de guardado y currar.
/// cada cuarto brinda una parte de historia y una parte de un cuarto ya explorado controolado por el array bool CuartoRevisado[] , para dodnde se revisa si se visito el cuarto.
/// corre las opciones de historria atraves de ifs que son designados comandos que corren funciones o soluciones de movimiento.
/// los cuartos contienen una funcion especifica ya sea encontrar armas, pelea o armadura , cuando una de estas funciones son cumplidas muestra que el cuartoo ya fue revisado.
/// finalmente para mas detalle la funcion cuartos0() esta detallada con todas las posibles acciones que se pueden tomar y como funciona el codigo que es similar atraves de todas.
/// </summary>
// cuarto de inicio
void Cuarto0(entidad& jugador) {

	Armas arma;
	// ingreso de lo escrito por jugador
	string opcion;

	// salida cierra el loop para mostar salida de cuarto
	bool Salida = true;
	// se cambia solamente cuando cuando un evento importante en el cuarto es completado (combate,armas,armadura) cambiando al final que el cuarto fue revisado 
	bool escogida = false;

	// el if revisa si el cuarto ah sido revisado 
	if (CuartoRevisado[InstaciaDeCuarto])
	{
		// historia y descripcion del cuarto
		type("\nAbres lentamente los ojos. Una sensacion de frio se apodera de tu piel mientras tus sentidos se ajustan al ambiente\noscuro que te rodeaba. El cuarto era apenas visible, iluminado por una tenue luz que se filtraba de antorchas\ndistantes.\n");
		type("Distingues las paredes rugosas de piedra que te rodean al sur, al este y al oeste. Frente a ti hay un cuchillo afilado\nsobre una mesa desgastada y  yace una puerta de aspecto antiguo, con runas inscritas que destellan con un\nresplandor debil al norte.\n\n");
		// repite las opciones que se pueden hacer mientras se encuentre en el cuarto 
		do
		{
			//pide ingreso de accion
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);


			// movimiento a diffrente cuarto 
			if (opcion == "moverse norte")
			{
				cout << "decides atravesar la antigua puerta que se alza frente a ti." << endl;
				// cambioo de cuarto y salida del looop actualizada
				InstaciaDeCuarto = 1;
				Salida = false;

			}
			//armas o armadura  incremento dirrecto a las estadisticas del personaje
			if (opcion == "recoger arma")
			{

				// intenta repetir accion pero no hay objeto que agarar
				if (escogida == true)
				{
					type("ya no hay nada que recoger\n\n");
				}
				// por primera ves se encuentra el arma o armadura
				else {
					type("\nEl arma es un cuchillo de hoja afilada con una longitud moderada.\n La hoja, de acero pulido, muestra marcas de uso y desgaste. La empuniadura envuelta en cuero envejecido,\n proporciona un agarre comodo y firme.\n");
					jugador.atk = 12;
					
					

					escogida = true;
				}

			}
			// siguiente se encuentra la funcion de ataque similar a la de armas cambia el valor final como parte crucial de la historia
			/*if (opcion == "Atacar duende")
			{

				/// funcion de atacar
				escogida = true;
			}*/

			// ayuda muestra un menu con todas la acciones possibles en el cuarto 
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			// guarda progreso 
			// posibles modificaciones para seguir jugando o cerrar el juego ;
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		// if determina si la parte esencial de la historia se completo  entonces cambia el valor de CuartoRevisado[InstaciaDeCuarto] en la pocicion del cuarto
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aqui se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		// repite el mismo esquema de la parte del if encontrado arriba solamente con opciones mas reducidas y una descripccio corta

		//insertar descripcion corta aqui
		do
		{
			type("Vuelves al cuarto donde inicio todo, todavia no comprendes porque estas ahi pero estas seguro de querer salir\n La puerta esta al norte\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			cout << opcion << endl;


			if (opcion == "moverse norte")
			{
				cout << "te mueves en direccion en la puerta al norte\n" << endl;
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
				GuardarProgreso(jugador);

			}



		} while (Salida);
	}

}

//cuarto de combate
void Cuarto1(entidad& jugador, entidad *monstruos) {

	string opcion;
	bool Salida = true;
	bool escogida = false;
	int monstruoEnCombate = 0;
	bool finCombate = false;



	if (CuartoRevisado[InstaciaDeCuarto])
	{
		//type("te encuentras en cuarto 1 que vas hacer  \n\n");
		type("\nAl entrar en el cuarto, te encuentras ahora en un reino de sombras iluminado por antorchas titilantes.\n Al este de ti parece encontrarse una puerta mas, pero esta es obstruida por un duende, de estatura diminuta,\n pero presencia magnetica, que te observa con ojos chispeantes, a quien deberas derrotar, antes de pasar.\n\n");
		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse este")
			{
				type("\ndecides atravesar la antigua puerta que se alza frente a ti.\n");
				InstaciaDeCuarto = 2;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 0;
				Salida = false;

			}

			if (opcion == "atacar duende")
			{
				if (escogida)
				{
					type("\nEl duende esta muerto\n");
				}
				else {

					jugador.hp = enfrentamiento(monstruoEnCombate, monstruos, jugador, finCombate);
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp > 0)
					{
						InstaciaDeCuarto = 0;
						Salida = false;
					}
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp <= 0)
					{
						escogida = true;
					}
					if (jugador.hp <= 0)
					{
						type("\n\n Game over");
						type("\n quieres : 'ultimo punto guardado' o 'cerrar juego' ");
						do
						{


							getline(cin, opcion);
							transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
							if (opcion == "ultimo punto guardado")
							{
								Leerprogreso(jugador);
								Salida = false;
							}
							if (opcion == "cerrar juego")
							{
								exit(0);
							}
						} while (Salida);
					}
				}



			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto- 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Vuelves al cuarto del duende, te da un poco de nostalgia por haber sido tu primera pelea\n La puerta esta al norte\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);



			if (opcion == "moverse este")
			{
				cout << "te mueves en direccion en la puerta al neste" << endl;
				InstaciaDeCuarto = 2;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 0;
				Salida = false;

			}

			if (opcion == "atacar duende")
			{
				type("el enemigo fue derotado ");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}

}

//cuarto de arma
void cuarto2(entidad& jugador) {

	Armas arma;
	string opcion;
	bool Salida = true;
	bool escogida = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("\nCruzas la antigua puerta y entras en un nuevo cuarto, dejando atras la mirada chispeante del duende. \nEste espacio esta iluminado por una luz mas intensa, revelando paredes gastadas, con dos puertas esta vez,\n una al sur y otra al este frente a ti, y en el centro del cuarto, sobre una superficie lisa, descansa una katana,\n su hoja resplandece con un brillo sutil, que puedes tomar.\n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse este")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti.\n\n");
				InstaciaDeCuarto = 5;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti.\n\n");
				InstaciaDeCuarto = 3;
				Salida = false;

			}
			if (opcion == "moverse oeste")
			{
				cout << "te mueves en direccion en la puerta al sur\n\n" << endl;
				InstaciaDeCuarto = 1;
				Salida = false;

			}
			if (opcion == "recoger arma")
			{


				if (escogida == true)
				{
					type("ya no hay nada que recoger\n\n");
				}
				else {
					type("La katana, elegante y mortal, La empuniuadura, envuelta en cuero oscuro, se ajusta a la perfeccion en la mano.\n La hoja, afilada como el filo de una promesa, parece haber sido forjada con una destreza maestra\n\n");
					jugador.atk =  arma.Katana;


					escogida = true;
				}


			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Este cuarto fue donde coneguiste esa brillante katana, que te ayudo mucho para seguir tu camino de vuelta a casa\n La puerta esta al sur\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse este")
			{
				cout << "te mueves en direccion en la puerta al este" << endl;
				InstaciaDeCuarto = 5;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 3;
				Salida = false;

			}
			if (opcion == "moverse oeste")
			{
				cout << "te mueves en direccion en la puerta al oeste" << endl;
				InstaciaDeCuarto = 1;
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
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}

//cuarto de combate
void cuarto3(entidad& jugador, entidad *monstruos) {


	string opcion;
	bool Salida = true;
	bool escogida = false;
	int monstruoEnCombate = 0;
	bool finCombate = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("Mientras avanzas hacia el siguiente cuarto. Este espacio está impregnado de un aire antiguo y polvoriento.\n Huesos y cráneos decoraban las esquinas como recordatorios silenciosos de aquellos que se aventuraron antes.\n De entre las sombras emerge un esqueleto,\n sosteniendo una espada oxidada en mano que te impide el paso hacia la puerta al este.\n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse este")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti.\n\n");
				InstaciaDeCuarto = 4;
				Salida = false;

			}
			if (opcion == "moverse norte")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 2;
				Salida = false;

			}
			//temporal diferente monstruo
			if (opcion == "atacar esqueleto")
			{
				if (escogida)
				{
					type("\nEl esqueleto esta muerto");
				}
				else {
					monstruoEnCombate = 1;
					jugador.hp = enfrentamiento(monstruoEnCombate, monstruos, jugador, finCombate);
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp > 0)
					{
						InstaciaDeCuarto = 0;
						Salida = false;
					}
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp <= 0)
					{
						escogida = true;
					}
					if (jugador.hp <= 0)
					{
						type("\n\n Game over");
						type("\n quieres : 'ultimo punto guardado' o 'cerrar juego' ");
						do
						{


							getline(cin, opcion);
							transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
							if (opcion == "ultimo punto guardado")
							{
								Leerprogreso(jugador);
								Salida = false;
							}
							if (opcion == "cerrar juego")
							{
								exit(0);
							}
						} while (Salida);
					}
				}
				if (opcion == "ayuda")
				{
					opcionAyuda();

				}
				if (opcion == "guardar progreso")
				{
					GuardarProgreso(jugador);

				}
			}

		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto-1] = false;
		}


	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Vuelves a la zona donde combatiste el esqueleto, ten cuidado que no se muevan esos huesos tirados\nLa puerta esta al este\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);



			if (opcion == "moverse este")
			{
				cout << "te mueves en direccion en la puerta al este" << endl;
				InstaciaDeCuarto = 4;
				Salida = false;

			}
			if (opcion == "moverse norte")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 2;
				Salida = false;

			}
			//temporal diferente monstruo
			if (opcion == "atacar esqueleto")
			{
				type("el enemigo fue derotado ");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}

//cuarto dee armadura
void cuarto4(entidad& jugador) {

	Armaduras armadura;
	string opcion;
	bool Salida = true;
	bool escogida = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("La puerta se abre y una luz tenue ilumina el espacio, destacando una figura imponente en el centro:\n una armadura liviana, cuidadosamente colocada sobre un soporte y al norte un cuarto nuevo\n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse oeste")
			{
				cout << "Te mueves en direccion en la puerta al oeste" << endl;
				InstaciaDeCuarto = 3;
				Salida = false;

			}
			if (opcion == "moverse norte")
			{
				cout << "te mueves en direccion en la puerta al norte" << endl;
				InstaciaDeCuarto = 5;
				Salida = false;

			}
			if (opcion == "recoger armadura")
			{


				if (escogida == true)
				{
					type("ya no hay nada que recoger\n\n");
				}
				else {
					type("La armadura, de aspecto pulido y elegante, brilla levemente en la penumbra.\n Su disenio es simple pero efectivo, ofreciendo una promesa de protección sin sacrificar la movilidad.\n\n");
					// funcion de equpar armadura 
					jugador.def =  armadura.liviana[0];
					jugador.agilidad = armadura.liviana[1];
					escogida = true;
				}


			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Vuelves al cuarto de tu primera armadura, una la cual no era la mejor pero te salvo de varias situaciones\nLa puerta esta al sur\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse oeste")
			{
				cout << "te mueves en direccion en la puerta al oeste" << endl;
				InstaciaDeCuarto = 3;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al norte" << endl;
				InstaciaDeCuarto = 5;
				Salida = false;

			}
			if (opcion == "recoger armadura")
			{
				type("ya no hay nada que recoger\n\n");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}

//cuarto con combate  Monstruo mimic pelea 
void cuarto5(entidad& jugador, entidad *monstruos) {

	string opcion;
	bool Salida = true;
	bool escogida = false;
	int monstruoEnCombate = 0;
	bool finCombate = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("La puerta se abre con un leve crujido, revelando un cuarto más amplio con una atmosfera cargada de expectacion.\n Al norte encuentras una puerta mas y al centro destaca un cofre,\n adornado con detalles intrincados que sugieren un botin tentador. \n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse oeste")
			{
				cout << "te mueves en direccion en la puerta al oeste" << endl;
				InstaciaDeCuarto = 3;
				Salida = false;

			}
			if (opcion == "moverse norte")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti.\n\n");
				InstaciaDeCuarto = 6;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 4;
				Salida = false;

			}
			if (opcion == "abrir cofre")
			{
				type("Te acercas para reclamar, pero al abrirlo el interior del cofre revela su verdadera naturaleza: un Mimic.\n Una criatura astuta que adopta la forma de la codicia misma.\nEl monstruo te logro morder mientras lo abrias\n\n");
				jugador.hp = jugador.hp - 8;
				// te ataca
				if (escogida)
				{
					type("\nEl mimic esta muerto");
				}
				else {
					monstruoEnCombate = 2;
					jugador.hp = enfrentamiento(monstruoEnCombate, monstruos, jugador, finCombate);
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp > 0)
					{
						InstaciaDeCuarto = 0;
						Salida = false;
					}
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp <= 0)
					{
						type("El cofre desaparece en polvo con todo el contenido\n");
						escogida = true;
					}
					if (jugador.hp <= 0)
					{
						type("\n\n Game over");
						type("\n quieres : 'ultimo punto guardado' o 'cerrar juego' ");
						do
						{


							getline(cin, opcion);
							transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
							if (opcion == "ultimo punto guardado")
							{
								Leerprogreso(jugador);
								Salida = false;
							}
							if (opcion == "cerrar juego")
							{
								exit(0);
							}
						} while (Salida);
					}
				}
			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Regresas al cuarto donde fuiste timado por un mimic, gracias a el ahora tienes mas cuidado al revisar cofres\nLa puerta esta al norte\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);



			if (opcion == "moverse oeste")
			{
				cout << "te mueves en direccion en la puerta al oeste" << endl;
				InstaciaDeCuarto = 3;
				Salida = false;

			}
			if (opcion == "moverse norte")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 6;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 4;
				Salida = false;

			}

			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}


// cuarto con arma
void cuarto6(entidad& jugador) {

	Armas arma;
	string opcion;
	bool Salida = true;
	bool escogida = false;


	if (CuartoRevisado[InstaciaDeCuarto - 1])
	{
		type("Al cruzar al siguiente cuarto, una luz revele en el centro una nueva arma: “El fierro golpeador de parejas felices”\n y al oeste un nuevo cuarto por explorar.\n Al acercarte al arma singular, sientes una extrania conexion con este objeto peculiar\n y la habitacion se llena de una atmosfera amigable y ligera.\n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse oeste")
			{
				cout << "te mueves en direccion en la puerta al oeste" << endl;
				InstaciaDeCuarto = 7;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 5;
				Salida = false;

			}
			if (opcion == "recoger arma")
			{


				if (escogida == true)
				{
					type("ya no hay nada que recoger\n\n");
				}
				else {
					type("Su diseño es encantadoramente inusual, con detalles que evocan la alegria y la complicidad.\n El mango, envuelto en colores vibrantes, presenta grabados de corazones entrelazados y pequeñas figuras sonrientes.\n\n");
					// funcion de equpar armadura 
					jugador.atk = arma.fierroGolpeadorDeParejasFelices;
					escogida = true;
				}


			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Vuelves al cuarto donde conociste por primera vez el fierro golpeador de parejas felices,\n gracias a el ahora eres feliz golpeando parejas\n La puerta esta al oeste\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse oeste")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti\n\n");
				InstaciaDeCuarto = 7;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 5;
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
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}

//cuarto combate
void cuarto7(entidad& jugador, entidad* monstruos) {

	string opcion;
	bool Salida = true;
	bool escogida = false;
	int monstruoEnCombate = 0;
	bool finCombate = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("La puerta se abre y la luz tenue danza sobre las paredes, destacando intrincados grabados mitologicos.\n En el centro, un centauro majestuoso emerge como guardian de este nuevo recinto,\n con arco en mano y armadura que destella debilmente. La atmosfera se carga con una mezcla de mito y majestuosidad,\n invitandote a enfrentar un desafio unico y asi pasar al siguiente cuarto al Norte.\n\n");

		do
		{

			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse norte")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti\n\n");
				InstaciaDeCuarto = 8;
				Salida = false;

			}
			if (opcion == "moverse este")
			{
				cout << "te mueves en direccion en la puerta al este" << endl;
				InstaciaDeCuarto = 6;
				cout << InstaciaDeCuarto;
				Salida = false;

			}
			if (opcion == "atacar centauro")
			{
				if (escogida)
				{
					type("\nEl Centauro esta muerto");
				}
				else {

					jugador.hp = enfrentamiento(monstruoEnCombate, monstruos, jugador, finCombate);
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp > 0)
					{
						InstaciaDeCuarto = 0;
						Salida = false;
					}
					if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp <= 0)
					{
						escogida = true;
					}
					if (jugador.hp <= 0)
					{
						type("\n\n Game over");
						type("\n quieres : 'ultimo punto guardado' o 'cerrar juego' ");
						do
						{


							getline(cin, opcion);
							transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
							if (opcion == "ultimo punto guardado")
							{
								Leerprogreso(jugador);
								Salida = false;
							}
							if (opcion == "cerrar juego")
							{
								exit(0);
							}
						} while (Salida);
					}
				}
			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Vuelves al cuarto del centauro, una batalla feroz y guerrera, nunca olvidaras a ese guerrero\nLa puerta esta al norte\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);



			if (opcion == "moverse este")
			{
				cout << "te mueves en direccion en la puerta al este" << endl;
				InstaciaDeCuarto = 6;
				Salida = false;

			}
			if (opcion == "moverse norte")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti\n\n");
				InstaciaDeCuarto = 8;
				Salida = false;

			}
			//temporal diferente monstruo
			if (opcion == "atacar centauro")
			{
				type("el enemigo fue derotado ");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}

//cuarto armadura
void cuarto8(entidad& jugador) {

	Armaduras armadura;
	string opcion;
	bool Salida = true;
	bool escogida = false;


	if (CuartoRevisado[InstaciaDeCuarto])
	{
		type("te encuentras en cuarto 8 que vas hacer  \n\n");

		do
		{
			type("Despues de una intensa confrontacion con el centauro, la puerta al siguiente cuarto se abre.\n Entrando en este destaca una figura imponente: una armadura pesada, majestuosamente dispuesta en el centro.\n La eleccion de recogerla no solo es una decisión tactica, ya que tu movilidad sera afectada.\n Posteriormente, puedes continuar al este hacia una puerta de aspecto de fuego.\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse norte")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti");
				InstaciaDeCuarto = 9;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al sur" << endl;
				InstaciaDeCuarto = 7;
				Salida = false;

			}
			if (opcion == "recoger armadura")
			{


				if (escogida == true)
				{
					type("Las placas se entrelazan de manera artistica, proporcionando una cobertura completa desde los hombros hasta los pies.\n Al levantarla, sientes la solidez de la defensa que proporcionará.\n\n");
				}
				else {
					type("descripcion de armarmadura\n\n");
					// funcion de equpar armadura 
					jugador.def =  armadura.pesada[0];
					jugador.agilidad = armadura.pesada[1];
					escogida = true;
				}


			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);

			}


		} while (Salida);
		if (escogida == true)
		{
			CuartoRevisado[InstaciaDeCuarto - 1] = false;
		}
	}

	/// <summary>
	/// aque se forma la divion entre la histria si a sido  visistado el cuarto revisando si la pocicion del array es verdadera o falsa. El else sirve para no mostrar nuevamente los desarollos de la historia
	/// </summary>
	else
	{
		do
		{
			type("Regresas al cuarto de la armadura, el ultimo regalo antes de pelear contra el jefe\nAgarrate los pantalones que viene el dragonsote\nLa puerta esta al norte\n\n");
			cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
			getline(cin, opcion);
			transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
			//cout << opcion << endl;


			if (opcion == "moverse norte")
			{
				type("decides atravesar la antigua puerta que se alza frente a ti\n");
				InstaciaDeCuarto = 9;
				Salida = false;

			}
			if (opcion == "moverse sur")
			{
				cout << "te mueves en direccion en la puerta al norte" << endl;
				InstaciaDeCuarto = 7;
				Salida = false;

			}
			if (opcion == "recoger armadura")
			{
				type("ya no hay nada que recoger\n\n");

			}
			if (opcion == "ayuda")
			{
				opcionAyuda();

			}
			if (opcion == "guardar progreso")
			{
				GuardarProgreso(jugador);
			}



		} while (Salida);
	}
}

//cuarto combate final
void cuarto9(entidad& jugador, entidad* monstruos) {

	string opcion;
	bool Salida = true;
	int monstruoEnCombate = 4;
	bool finCombate = false;


	do
	{
		type("Tras superar cada desafio, cada cuarto del laberinto oscuro, llegas finalmente al ultimo umbral.\n La puerta se abre con un retumbar, revelando una camara vasta, en el corazón de esta camara,\n yace majestuoso y temible, el jefe final: el dragon.\n\n");
		type("El dragon, con alas extendidas, se erige sobre un tesoro colosal\n que resplandece con la promesa de riquezas inimaginables.\n Tu reflejo en las gemas incrustadas revela la determinacion en tus ojos,\n la misma determinacion que te llevo a traves de cada prueba.\n Este enfrentamiento con el dragon es el pinaculo de tu odisea en el laberinto de sombras.\n\n");
		cout << "que accion vas a tomar aventurero (escribe 'ayuda' para ver comandos posibles) : ";
		getline(cin, opcion);
		transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);


		if (opcion == "atacar dragon")
		{


			jugador.hp = enfrentamiento(monstruoEnCombate, monstruos, jugador, finCombate);
			if (jugador.hp > 0 && monstruos[monstruoEnCombate].hp <= 0)
			{
				type("\nDerotas al dragon eres libre del calbaozo");
				finalizar = false;
			}
			if (jugador.hp <= 0)
			{
				type("\n\n Game over");
				type("\n quieres : 'ultimo punto guardado' o 'cerrar juego' ");
				do
				{


					getline(cin, opcion);
					transform(opcion.begin(), opcion.end(), opcion.begin(), ::tolower);
					if (opcion == "ultimo punto guardado")
					{
						Leerprogreso(jugador);
						Salida = false;
					}
					if (opcion == "cerrar juego")
					{
						exit(0);
					}
				} while (Salida);
			}

			if (opcion == "ayuda")
			{
				type("ataca por tu vida");

			}
			if (opcion == "guardar progreso")
			{
				type("no hay donde correr tu unica opcion es pelear...");

			}
		}
	} while (Salida);
}





//imprime lista de comandos 
void opcionAyuda() {

	cout << "\t\t********* Lista de comandos *********\n";
	printf("%-35s%-35s\n", "1. Moverse (norte,sur,este,oeste)", "2. Recoger (arma,armadura)");
	printf("%-35s%-35s\n\n", "3. Atacar (nombre mounstro)", "4. Guardar pogreso");


}

//funcion para el efecto de escribir el texto 

// idea: inheritence convetir en clase for innheritance a los otros programas.
void type(const char* p) {

	if (NULL == p)
		return;

	while (*p)
	{
		printf("%c\xDB", *p++);
		::Sleep(30);
		printf("\b \b");
		::Sleep(30);
	}
	::Sleep(50);
}

// sistema de guardado de variables para el progreso en el juego 
void GuardarProgreso(entidad& jugador) {
	ofstream ProgresoDelJugador("ProgresoGuardado.txt");



	//primeras 5 son elnombre y estadisticas del jugador

	ProgresoDelJugador << jugador.hp << endl;
	ProgresoDelJugador << jugador.def << endl;
	ProgresoDelJugador << jugador.atk << endl;
	ProgresoDelJugador << jugador.agilidad << endl;

	//en el cuarto que el presonaje se encuentra 
	ProgresoDelJugador << InstaciaDeCuarto << endl;


	//variables del arreglo de cuarto revisado
	for (int i = 0; i < 10; i++)
	{
		ProgresoDelJugador << CuartoRevisado[i] << endl;
	}

	type("se guardo el progreso\n");
	ProgresoDelJugador.close();

}

bool Leerprogreso(entidad& jugador) {
	ifstream JuegoGuardado;
	JuegoGuardado.open("ProgresoGuardado.txt");

	// se verifica si funciona y guarda todas las varibles y las inicia 
	if (JuegoGuardado.is_open() == true)
	{
		cout << "\nse encontro progreso";
		//primeras 5 son elnombre y estadisticas del jugador
		JuegoGuardado >> jugador.hp;
		JuegoGuardado >> jugador.def;
		JuegoGuardado >> jugador.atk;
		JuegoGuardado >> jugador.agilidad;

		//en el cuarto que el presonaje se encuentra 
		JuegoGuardado >> InstaciaDeCuarto;


		//variables del arreglo de cuarto revisado
		for (int i = 0; i < 10; i++)
		{
			JuegoGuardado >> CuartoRevisado[i];
		}

		JuegoGuardado.close();

		return true;
	}
	else
	{
		type("No hay progreso guardados\n");
		return false;

	}


}





//funciones
//===============================================================
//funciones para el bono de ataque
int bono(entidad& personaje, entidad* monstruos, int monstruoEnCombate, int pPrincip, int ag) {
	int bonus = 0;
	if (pPrincip == 1 && ag == 0) {           //sacar bono atk personaje
		if (personaje.atk != 10) {
			bonus = ((personaje.atk - 10) / 2);
		}
	}
	else if (pPrincip == 0 && ag == 0) {     //sacar bono atk monstruo
		if (monstruos[monstruoEnCombate].atk != 10) {
			bonus = ((monstruos[monstruoEnCombate].atk - 10) / 2);
		}
	}
	else if (pPrincip == 1 && ag == 1) {     //sacar bono agilidad personaje
		if (personaje.agilidad != 10) {
			bonus = ((personaje.agilidad - 10) / 2);
		}
	}
	else {                                 //sacar bono agilidad monstruo
		if (monstruos[monstruoEnCombate].agilidad != 10) {
			bonus = ((monstruos[monstruoEnCombate].agilidad - 10) / 2);
		}
	}
	return bonus;
}
//=================================================================
//funcion para el dado
int dado(int tipoDadoEnfrentamiento) {
	random_device az;
	mt19937 gen(az());
	if (tipoDadoEnfrentamiento == 1) {        //para que haga el dado del 1-20
		uniform_int_distribution<int> distribucion(1, 20);
		return distribucion(gen);
	}
	else {                                  //para que haga el dado del 1-10
		uniform_int_distribution<int> distribucion(1, 10);
		return distribucion(gen);
	}
}
//=========================================================================================================
//funciones para "descanzar"
//funcion para ense�ar los segundos y la vida adquirida
void displayClock(entidad& personaje, int seconds) {
	cout << setfill('0') << setw(2) << seconds << " sec | " << personaje.hp << " vida " << endl;
}
//funcion para que cada segundo suba la vida del personaje teniendo un limite de 30 segundos
int Descansar(entidad& personaje) {
	int seconds = 0;
	bool timer = true;
	while (seconds != 30 && personaje.hp < 75) {
		displayClock(personaje, seconds);
		Sleep(1000);
		personaje.hp++;
		seconds++;
	}
	cout << "Has descansado lo suficiente" << endl;
	timer = false;
	seconds = 0;
	return personaje.hp;
}
//=========================================================================================================
//funcion para "correr" o salir de combate
int correr(entidad& personaje) {
	int opDescansar=0;
	cout << "Corres y te escondes del monstruo mientras el se va" << endl;
	//el personaje vuelve a la camara anterior, resta de variable de la camara:

	do {
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Desea descansar?" << endl;
		cout << "1. Si" << endl;
		cout << "2. No" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cin >> opDescansar;

		switch (opDescansar) {
		case 1: {
			//llamar funcion descansar:
			personaje.hp = Descansar(personaje);
		}
			  break;

		case 2: {
			cout << "+++++++++++++++++++++++++++++" << endl;
			cout << "Decides no descanzar" << endl;
			cout << "+++++++++++++++++++++++++++++" << endl;
		}
			  break;

		default: {
			cout << "Opcion invalida!" << endl;
		}
			   break;
		}

	} while (opDescansar != 1 && opDescansar != 2);
	return personaje.hp;
}
//=========================================================================================================
//funciones para los turnos
//funcion para el ataque del personaje
int AtaquePersonaje(int monstruoEnCombate, entidad* monstruos, entidad& personaje, int ataqueBonoPersonaje, int tipoDadoEnfrentamiento) {
	int op, acertarAtaque, critico = 1;//variable opcion2 para poder tirar los dados y critico para aumentar el da�o dependiendo del numero que salga del primer dado

	acertarAtaque = dado(tipoDadoEnfrentamiento);//se obtiene el numero de este dado y ver si ataca o no
	cout << "-------------------------------------------------------" << endl;
	cout << "Tiras el dado y obtienes un " << acertarAtaque << endl;
	if (acertarAtaque == 20) {    //si el dado resulta dar 20 le dara un bono de x2
		critico = 2;
	}
	if (acertarAtaque > monstruos[monstruoEnCombate].def) {
		cout << "Enhorabuena, lograste acertar el ataque!" << endl;
		cout << "Ahora tira los dos dados para calcular el danio del ataque!!" << endl;
		do {
			cout << endl;
			cout << "1. Tirar ambos dados" << endl;
			cin >> op;
			cout << endl;

			if (op == 1) {
				tipoDadoEnfrentamiento = 2;//se usa el 2 para cambiar el modo del dado y solo sea de 1-10
				int da�o1 = dado(tipoDadoEnfrentamiento);
				int da�o2 = dado(tipoDadoEnfrentamiento);
				if (critico == 2) {
					cout << "------------------------------------------------------" << endl;
					cout << "Lograste pegar un golpe critico!!" << endl;
					cout << "Tu danio se multiplica por 2!" << endl;
				}
				cout << "-------------------------------------------------------" << endl;
				cout << "Con el primer dado salio un " << da�o1 << " y con el segundo un " << da�o2 << "!!" << endl;
				cout << "Tu bono de ataque es " << ataqueBonoPersonaje << " por lo que tu danio total es " << (da�o1 + da�o2 + ataqueBonoPersonaje) * critico << endl;
				cout << "-------------------------------------------------------" << endl;
				//llamar funcion quitar vida:
				monstruos[monstruoEnCombate].hp = monstruos[monstruoEnCombate].hp - ((da�o1 + da�o2 + ataqueBonoPersonaje) * critico);

				if (monstruos[monstruoEnCombate].hp <= 0) {
					cout << "Lo lograste!! Venciste al enemigo!" << endl;
					cout << "-------------------------------------------------------" << endl;
				}
			}
			else {
				cout << "Opcion invalida!" << endl;
			}
		} while (op != 1);
	}
	else {
		cout << "Intentas atacarlo, pero su defensa es mayor, por lo que fallas" << endl;
	}
	return monstruos[monstruoEnCombate].hp;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//funcion para el turno del monstruo
int TurnoMonstruo(entidad& personaje, int ataqueBonoMonstruo, int tipoDadoEnfrentamiento) {
	int acertarAtaque = 0;
	acertarAtaque = dado(tipoDadoEnfrentamiento);
	cout << "-------------------------------------------------------" << endl;
	cout << "El enemigo tira el dado y obtiene un " << acertarAtaque << endl;
	if (acertarAtaque >= personaje.def + 1) {
		cout << "-------------------------------------------------------" << endl;
		cout << "El enemigo logro pasar sobre tu defensa!!" << endl;
		cout << "Cuidado! Ahora el enemigo tirara los dados" << endl;
		tipoDadoEnfrentamiento = 2; //se usa el 2 para cambiar el modo del dado y solo sea de 1-10
		int da�o1 = dado(tipoDadoEnfrentamiento);
		int da�o2 = dado(tipoDadoEnfrentamiento);
		cout << "------------------------------------------------------" << endl;
		cout << "Con el primer dado salio un " << da�o1 << " y con el segundo un " << da�o2 << "!!" << endl;
		cout << "El bono de ataque del enemigo es " << ataqueBonoMonstruo << " por lo que su da�o total es " << da�o1 + da�o2 + ataqueBonoMonstruo << endl;
		//llamar funcion quitar vida:
		personaje.hp = personaje.hp - (da�o1 + da�o2 + ataqueBonoMonstruo);
		if (personaje.hp <= 0) {
			cout << "-------------------------------------------------------" << endl;
			cout << "EL enemigo logra vencerte, pides piedad pero lo unico que le importa al monstruo es sangre!" << endl;
			cout << "-------------------------------------------------------" << endl;
		}
	}
	else {
		cout << "-------------------------------------------------------" << endl;
		cout << "El enemigo corre furioso hacia ti, pero tu defensa logra repeler su ataque" << endl;
		cout << "-------------------------------------------------------" << endl;
	}
	return personaje.hp;
}



//=========================================================================================================
//Funcion principal del enfrentamiento entre ambas entidades
int enfrentamiento(int monstruoEnCombate, entidad* monstruos, entidad& personaje, bool finCombate) { //para el turno y ense�ar los demas datos, igual del personaje
	int op, op2,                //variables para los menus
		tipoDadoEnfrentamiento = 1,//la variable tipo de dado hara que la funcion de dado() pueda usarse para calcular si acierta el ataque y para el ataque, ya que para certar el dado puede conseguir un numero entre el 1 y 20, en cambio en el ataque los dos dados estan limitados a conseguir del 1 al 10
		// si la variable "tipoDadoEnfrentamiento" es 1, entonces usara el dado 1-20, si esta en 2 sera 1-10
		pPrincip, ag = 0,          //variables para la funcion combate
		ataqueBonoPersonaje, ataqueBonoMonstruo, agilidadBonoPersonaje, agilidadBonoMonstruo;//variables para el bono de agilidad y ataque

	//------------------------------------------------------------------------------------------------------------------------------
	//esta parte es para sacar el bono de ataque
	pPrincip = 1; //variable para saber si se esta sacando el bono de ataque del personaje principal o del monstruo
	ataqueBonoPersonaje = bono(personaje, monstruos, monstruoEnCombate, pPrincip, ag); //variable que solo se inicializa una vez

	pPrincip = 0;
	ataqueBonoMonstruo = bono(personaje, monstruos, monstruoEnCombate, pPrincip, ag); //variable que se usa cada vez que hay nuevo enfrentamiento
	//------------------------------------------------------------------------------------------------------------------------------
	//esta parte es para sacar el bono de agilidad
	pPrincip = 1;
	ag = 1;
	agilidadBonoPersonaje = bono(personaje, monstruos, monstruoEnCombate, pPrincip, ag); //variable que solo se inicializa una vez

	pPrincip = 0;
	agilidadBonoMonstruo = bono(personaje, monstruos, monstruoEnCombate, pPrincip, ag); //variable que se usa cada vez que hay nuevo enfrentamiento
	ag = 0;
	//------------------------------------------------------------------------------------------------------------------------------  
	do {
		if (InstaciaDeCuarto !=9 )
		{

		}
		cout << "Empieza el combate!!" << endl;
		Sleep(800);
		cout << "Aventurero, tira tu dado!" << endl;
		Sleep(800);
		cout << "1. Tirar dado" << endl;
		cout << "2. Correr" << endl;
		cin >> op;

		if (op == 1) {
			int dadoMonstruo, dadoPersonaje;
			do {
				dadoPersonaje = dado(tipoDadoEnfrentamiento);
				dadoMonstruo = dado(tipoDadoEnfrentamiento);
				cout << "Obtuviste un " << dadoPersonaje << endl;
				Sleep(500);
				cout << "Tu agilidad es de " << personaje.agilidad << ", por lo que obtuviste un " << dadoPersonaje + agilidadBonoPersonaje << endl;
				Sleep(1000);
				cout << "-----------------------------" << endl;
				cout << "El enemigo tira el dado y obtiene un " << dadoMonstruo << endl;
				Sleep(500);
				cout << "Su agilidad es de " << monstruos[monstruoEnCombate].agilidad << ", por lo que obtuvo un " << dadoMonstruo + agilidadBonoMonstruo << endl;
				Sleep(1000);

				//primer caso, si el usuario obtiene mayor numero al enemigo
				if (dadoPersonaje + agilidadBonoPersonaje > dadoMonstruo + agilidadBonoMonstruo) {
					cout << "======================================================================" << endl;
					cout << "Empiezas tu aventurero!" << endl;
					Sleep(500);
					do {
						cout << endl;
						cout << endl;
						cout << "Ahora vas tu aventurero!" << endl;
						Sleep(1000);
						cout << "-------------------------------------------------------" << endl;
						cout << "Tu vida es [" << personaje.hp << "]" << endl;
						Sleep(500);
						cout << "La vida de tu enemigo es [" << monstruos[monstruoEnCombate].hp << "] y su defensa es de [" << monstruos[monstruoEnCombate].def << "]" << endl;
						Sleep(500);
						cout << endl;
						cout << "1. Tirar dado" << endl;
						cout << "2. Correr" << endl;
						cin >> op2;
						do {
							switch (op2) {
							case 1: {
								monstruos[monstruoEnCombate].hp = AtaquePersonaje(monstruoEnCombate, monstruos, personaje, ataqueBonoPersonaje, tipoDadoEnfrentamiento);
							}
								  break;

							case 2: {
								//llamar funcion de correr  y descansar:
								if (InstaciaDeCuarto != 9)
								{
									correr(personaje);
									finCombate = true;
								}
								else
								{
									type("La puerta se a cerrado no hay donde correr...\n");
								}
							}
								  break;

							default: {
								cout << "Opcion invalida!!" << endl;
							}
								   break;
							}
						} while (op2 != 1 && op != 2);
						cout << "======================================================================" << endl;
						if (monstruos[monstruoEnCombate].hp > 0 && finCombate != true) {
							cout << endl;
							cout << endl;
							cout << "Ahora es el turno del enemigo!" << endl;
							personaje.hp = TurnoMonstruo(personaje, ataqueBonoMonstruo, tipoDadoEnfrentamiento);
							cout << "======================================================================" << endl;
							if (personaje.hp <= 0) {
								finCombate = true;
							}
						}
						else {
							finCombate = true;
						}
					} while (finCombate == false);

					//segundo caso, si el enemigo obtiene mayor numero al usuario
				}
				else if (dadoPersonaje + agilidadBonoPersonaje < dadoMonstruo + agilidadBonoMonstruo) {
					cout << "=====================================================================" << endl;
					cout << "Empieza el enemigo!" << endl;
					do {
						cout << endl;
						cout << endl;
						cout << "Ahora es el turno del enemigo!" << endl;
						personaje.hp = TurnoMonstruo(personaje, ataqueBonoMonstruo, tipoDadoEnfrentamiento);
						cout << "======================================================================" << endl;
						if (personaje.hp > 0) {
							cout << endl;
							cout << endl;
							cout << "Ahora es tu turno aventurero!" << endl;
							cout << "-------------------------------------------------------" << endl;
							cout << "Tu vida es [" << personaje.hp << "]" << endl;
							cout << "La vida de tu enemigo es [" << monstruos[monstruoEnCombate].hp << "] y su defensa es de [" << monstruos[monstruoEnCombate].def << "]" << endl;
							cout << endl;
							cout << "1. Tirar dado" << endl;
							cout << "2. Correr" << endl;
							cin >> op2;
							do {
								switch (op2) {
								case 1: {
									monstruos[monstruoEnCombate].hp = AtaquePersonaje(monstruoEnCombate, monstruos, personaje, ataqueBonoPersonaje, tipoDadoEnfrentamiento);
									if (monstruos[monstruoEnCombate].hp <=0)
									{
										finCombate = true;
									}
								}
									  break;

								case 2: {
									//llamar funcion de correr  y descansar:
									if (InstaciaDeCuarto != 9)
									{
										correr(personaje);
										finCombate = true;
									}
									else
									{
										type("La puerta se a cerrado no hay donde correr...\n");
									}
									
								}
									  break;

								default: {
									cout << "Opcion invalida!!" << endl;
								}
									   break;
								}
							} while (op2 != 1 && op2 != 2);
						}
						else {
							finCombate = true;
						}
					} while (finCombate == false);

					//tercer caso, si ambos obtienen un mismo numero
				}
				else {
					cout << endl;
					cout << "Ambos dados salieron iguales!!" << endl;
					cout << endl;
					cout << "Se repite!" << endl;
				}
			} while (dadoPersonaje != dadoMonstruo && finCombate == false);

		}
		else if (op == 2) {
			correr(personaje);

		}
		else {
			cout << "Opcion invalida" << endl;
		}
	} while (op != 1 && op != 2);
	return personaje.hp;
}
//==========================================================================================================
