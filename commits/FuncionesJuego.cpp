#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

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
    while (seconds < 30 && hp <75) {
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

int main(){
//Valores prototipos para probar su funcionalidad
int hp = 15;
int pocion = 20; //NOTA: valor de las pociones pendiente a especificar
    
    hp = Descansar(hp); //Funcion de descansa(Necesita los valores de la vida del jugador para funcionar)
    cout<<"Su vida es (utilizando funcion Descansar): "<<hp<<endl;

    hp = Pocion(hp, pocion); //Funcion de la pocion que necesita los valores de la vida del jugador y la cantidad de vida q recupera la pocion
    cout<<"Su vida es (utilizando funcion Pocion): "<<hp<<endl;

    return 0;
}