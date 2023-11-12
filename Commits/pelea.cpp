#include <iostream>
#include <random>
using namespace std;

struct entidad{
int hp = 75, def = 1, atk = 10;
};
entidad personaje;
entidad monstruos[3];


int bono(){
    int bonusAtk;
    if(personaje.atk >= 10){
        bonusAtk = (personaje.atk - 10)/2;
    }
    return bonusAtk;
}

int dado(){
    random_device az;
    mt19937 gen(az());
    uniform_int_distribution<int> distribucion(1,20);
    return distribucion(gen); 
}

int turnoPersonaje(int monstruoEnCombate, entidad*monstruos){
    int acertarAtaque = dado();
    if(acertarAtaque > monstruos[monstruoEnCombate].def){
        int daño = dado() + dado();
    }  
}

int turnoMosntruo(){

}

int enfrentamiento(int monstruoEnCombate,entidad*monstruos){ //para el turno y enseñar los demas datos, igual del personaje
    int op;
    cout<<"Empieza el combate!!"<<endl;
    cout<<"Aventurero, tira tu dado!"<<endl;
    cout<<"1. Tirar dado"<<endl;
    cout<<"2. Correr"<<endl;
    cin>>op;

    if(op == 1){
        int turnoPersonaje = dado();
        int turnoMonstruo = dado();
        cout<<"Obtuviste un "<<turnoPersonaje<<endl;
        cout<<"El enemigo tira el dado y obtiene un "<<turnoMonstruo<<endl;
        if(turnoPersonaje > turnoMonstruo){
            
        }
    }

}

int main(){
    //variables
    int acertarAtaque, ataque1, ataque2, monstruoEnCombate,hp;
    //posicion 0 es la del duende
    //posicion 1 es la del 
    monstruos[0].hp = 30;
    monstruos[0].def = 5;
    monstruos[0].hp = 10;
    
    monstruoEnCombate = 0;
    hp = enfrentamiento(monstruoEnCombate,monstruos);

    cout<<acertarAtaque<<" "<<ataque1<<" "<<ataque2;
}