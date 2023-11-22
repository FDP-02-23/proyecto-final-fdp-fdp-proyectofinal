#include <iomanip>
#include <iostream>
#include <stdlib.h> 
#include <unistd.h> //utilizada para manejar las funciones de tiempo (sleep)
#include <chrono> //utilizada para controlar la funcion de escribir lento
#include <thread> //utilizada para controlar la funcion de escribir lento

using namespace std;

struct Armas //Struct donde se almacenaran las armas del juego y sus respetivos valores de ataque (la cantidad de atk q le suman al atk base del jugador)
{    
    int karambit = 2;
    int Katana = 4;
    int hacha = 6;
};

struct Armaduras //Struct donde se almacenan las 2 Armaduras del juego, esta afecta los valores de defensa y movilidad del jugador
{
    int liviana [2] {6,-2};
    int pesada [2] {4,2};
};

struct Pociones // Struct q almacena los valores de las 3 diferentes pociones q existen en el juego y la cantidad que cura cada una
{
    int pequenia = 20;
    int mediana = 40;
    int grande = 75;
};

struct Equipamiento //Struct de equipamiento que almacena todo lo anterior
{
    Armas arma;
    Armaduras armadura;
    Pociones pocion;
};

//Funcion utilizada para mostrale un temporizador al jugador de los segundos transcurridos y la vida que esta recuperando (valores dados por la funcion Descansar)
void displayTimer(int hp, int seconds) {
    cout << setfill('0') << setw(2) << seconds << " sec | "<< hp<< " vida "<<endl;
}

//Funcion activada cuando el jugador desea descansar para recuperar vida (necesita el valor de la vida del jugador para llevarse acabo)
int Descansar(int hp) {
    int seconds=0;
    //Se inicializa un boolean utilizado para el temporizador
    bool timer = true;
    //Maneja los parametros del temporizador, ya que este llega a un maximo de 30 seg o hasta que la vida del jugador este al maximo
    while (seconds < 30 && hp <75) { //se removio el signo = de los 30 segundos
        displayTimer(hp,seconds); //datos utilizado por la funcion displayTimer
        sleep(1);
        hp++;
        seconds++;
    } 
        cout<<"Has descansado lo suficiente"<<endl;
        timer = false; //Una vez haya cumplido con su utilidad cerramos el timer
        //reinciamos los segundos a 0, para cuando se vuelva a utilizar
        seconds = 0;
    return hp;
}

//Funcion creada para poder sumar la vida mas la pocion del jugador
int Pocion(int hp, int pocion){

    hp = hp + pocion;
    //Debido a que el maximo en el juego es 75 de vida, siempre que se exceda automaticamente se limita a 75
    if (hp >= 75)
    {
        hp = 75;  //regresa el valor del hp
    }
    return hp;
}
//Funcion para reducir la salud del jugador al recibir daño, necesita recibir la vida del jugador y el daño que ha recibido
int Reducirhp(int hp, int danio){
   if (hp <= 75)
   {
    hp= hp - danio;
   }else if (hp <= 0)
   {
    cout<<"Game over";
   }
   return hp;
}
// Funcion utilizada para imprimir lentamente el texto en pantalla para el usuario (se mejoro la eficiencia)
void EscribirLento(const string & texto) {  // en esta linea el const string& mensaje represntan el mensaje a escribir y la velociada deseada
    chrono::milliseconds velocidad(100); //poneindo la velocidad aqui, esta siempre será 1 seg
    for (char c : texto) { //el for es utilizada para ir caracter por caracter 
        cout << c << flush; // lo muetra
        this_thread::sleep_for(velocidad); //hace una pausa (dependera de la velocidad)
    }
}

int main(){

int hp, danio, atk, op; 
Pociones pocion1;
Armas arma1;
struct entidad{
int hp, def, atk;

//se intregaron las estadisticas del jugador y de los monstruos
};
entidad personaje;//estadisticas del personaje
    personaje.hp = 75;
    personaje.def = 1;
    personaje.atk = 10;

    entidad monstruos[5];//estadisticas de los monstruos
    //posicion 0 es la del duende   |hp30,def7,atk6 
    //posicion 1 es la del esqueleto|hp45,def12,atk8 
    //posicion 2 es la del mimic    |hp50,def8,atk12 
    //posicion 3 es la del centauro |hp60,def14,atk10 
    //posicion 4 es la del dragon   |hp90,def16,atk16 

    //duende
    monstruos[0].hp = 30;
    monstruos[0].def = 7;
    monstruos[0].atk = 6;

    //esqueleto
    monstruos[1].hp = 45;
    monstruos[1].def = 12;
    monstruos[1].atk = 5;

    //mimic
    monstruos[2].hp = 50;
    monstruos[2].def = 8;
    monstruos[2].atk = 12;

    //centauro
    monstruos[3].hp = 60;
    monstruos[3].def = 14;
    monstruos[3].atk = 10;

    //dragon
    monstruos[4].hp = 90;
    monstruos[4].def = 16;
    monstruos[4].atk = 16;
    
    hp = Reducirhp(personaje.hp,60); //invocando funcion de reducir vida, el valor del daño cambia, esto es un ejemplo

    //simulando caso en el que se le pregunte al jugador si desea curarse con la pocion y simulando como se escibira el texto para el jugador
    string texto = "Te hicieron daño, tu vida ahora es: "; 
    EscribirLento(texto);
    cout<<hp<<endl;
    string texto2 = "Deseas curarte con una pocion? 1(si)  2(No)";
    EscribirLento(texto2);
    cout<<endl;
    cin>>op;
        //Ejemplo de como se usarian las pociones
        if (op == 1)
        {
            cout<<"Cual pocion desea usar: pequenia(1), mediana(2), grande(3)"<<endl;
            cin>>op;
            switch (op)
            {
            case 1:
            hp = Pocion(hp, pocion1.pequenia); 
                break;
            case 2:
            hp = Pocion(hp, pocion1.mediana); 
            cout<<"Su vida es: "<<hp<<endl;
                break;
            case 3:
            hp = Pocion(hp, pocion1.grande); 
            cout<<"Su vida es: "<<hp<<endl;
                break;
            
            default:
                break;
            }
        }else
        cout<<"tu vida es: "<<hp<<endl;
        //ejemplo de uso de funcion Descansar
        if (hp <= 30)
        {
            cout<<"Tu vida es muy baja deseas descansar? si(1)  no(2)"<<endl;
            cin>>op;
            if (op == 1)
            {
                hp = Descansar(hp);
                cout<<"Su vida despues de descansar es: "<<hp;
            }else 
            cout<<"Tu vida es: "<<hp;            
        }
        //Ejemplo de como se sumara el atk del jugador con las armas q encuentre
        cout<<"Has encontrado un karambit, quiero recogerlo: si(1)  no(2)"<<endl;
        cin>>op;
        if (op == 1)
        {
            atk = (personaje.atk + arma1.karambit);
            cout<<"Has recogido un karambit, tu atk ahora es: "<<atk<<endl;
        }else
            atk = personaje.atk;
        
    return 0;
}