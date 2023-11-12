#include <iostream>
#include <random>
using namespace std;
//struct para las entidades
struct entidad{
int hp = 75, def = 1, atk = 10;
};

//funciones
int bonoPersonaje(entidad personaje){
    int bonusAtk;
    if(personaje.atk >= 10){
        bonusAtk = (personaje.atk - 10)/2;
    }
    return bonusAtk;
}
int bonoMonstruo(entidad*monstruos,int monstruoEnCombate){
    int bonusAtk;
    if(monstruos[monstruoEnCombate].atk >= 10){
        bonusAtk = (monstruos[monstruoEnCombate].atk - 10)/2;
    }
    return bonusAtk;
}

int dado(){
    random_device az;
    mt19937 gen(az());
    uniform_int_distribution<int> distribucion(1,20);
    return distribucion(gen); 
}

int TurnoPersonaje(int monstruoEnCombate, entidad*monstruos,int ataqueBonoPersonaje){
    int acertarAtaque = dado();
    if(acertarAtaque > monstruos[monstruoEnCombate].def){
        int daño = dado() + dado();
    }  
}

int TurnoMonstruo(entidad personaje){
    int acertarAtaque = dado();
    if(acertarAtaque > personaje.def){
        int daño = dado() + dado();
    }
}

int enfrentamiento(int monstruoEnCombate,entidad*monstruos,int ataqueBonoPersonaje, int ataqueBonoMonstruo){ //para el turno y enseñar los demas datos, igual del personaje
    int op;
    bool salida;
    cout<<"Empieza el combate!!"<<endl;
    cout<<"Aventurero, tira tu dado!"<<endl;
    cout<<"1. Tirar dado"<<endl;
    cout<<"2. Correr"<<endl;
    cin>>op;

    if(op == 1){
        int dadoPersonaje = dado();
        int dadoMonstruo = dado();
        cout<<"Obtuviste un "<<dadoPersonaje<<endl;
        cout<<"El enemigo tira el dado y obtiene un "<<dadoMonstruo<<endl;
        if(dadoPersonaje > dadoMonstruo){
            do{
            TurnoPersonaje(ataqueBonoPersonaje,monstruoEnCombate,monstruos,salida);

            }while(salida);
        }
    }

}

int main(){
    //variables
    int acertarAtaque, ataque1, ataque2, ataqueBonoPersonaje,ataqueBonoMonstruo, monstruoEnCombate,hp;
    entidad personaje;
    entidad monstruos[5];
    //posicion 0 es la del duende 
    //posicion 1 es la del esqueleto |hp45,def12,atk8 
    //posicion 2 es la del lobo     |hp50,def8,atk12 
    //posicion 3 es la del centauro |hp60,def14,atk10 
    //posicion 4 es la del dragon   |hp90,def16,atk16 
    monstruos[0].hp = 30;
    monstruos[0].def = 7;
    monstruos[0].atk = 6; //hacer descuento cuando sea 10

    monstruoEnCombate = 0;

    ataqueBonoPersonaje = bonoPersonaje(personaje);
    ataqueBonoMonstruo = bonoMonstruo(monstruos,monstruoEnCombate);
    
    hp = enfrentamiento(monstruoEnCombate,monstruos,ataqueBonoPersonaje,ataqueBonoMonstruo);

}