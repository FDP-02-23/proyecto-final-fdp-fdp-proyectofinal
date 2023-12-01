#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <random>
#include <windows.h>
#include <stdio.h>
using namespace std;

//struct para las entidades
struct entidad{
    int hp, def, atk, agilidad;
};

struct Armas{
    int karambit = 2;
    int Katana = 2;
    int fierroGolpeadorDeParejasFelices = 2;
};

struct Armaduras{
    int liviana [2] {4,2}; //posicion 0 es la defensa y la posicion 1 es la agilidad
    int pesada [2] {6,-2};
};

struct Pociones{
    int pequenia = 20;
    int mediana = 40;
    int grande = 75;
};

struct Equipamiento{
    Armas arma;
    Armaduras armadura;
    Pociones pocion;
};

//funciones
//===============================================================
//funciones para el bono de ataque
int bono(entidad personaje, entidad*monstruos, int monstruoEnCombate, int pPrincip, int ag){
    int bonus = 0;
    if(pPrincip == 1 && ag == 0){           //sacar bono atk personaje
        if(personaje.atk != 10){
            bonus = ((personaje.atk - 10)/2);
        }
    }else if(pPrincip == 0 && ag == 0){     //sacar bono atk monstruo
        if(monstruos[monstruoEnCombate].atk != 10){
            bonus = ((monstruos[monstruoEnCombate].atk - 10)/2);
        }
    }else if(pPrincip == 1 && ag == 1){     //sacar bono agilidad personaje
        if(personaje.agilidad != 10){
            bonus = ((personaje.agilidad - 10)/2);
        }
    }else {                                 //sacar bono agilidad monstruo
        if(monstruos[monstruoEnCombate].agilidad != 10){
            bonus = ((monstruos[monstruoEnCombate].agilidad - 10)/2);
        }
    }
    return bonus;
}
//=================================================================
//funcion para el dado
int dado(int tipoDadoEnfrentamiento){
    random_device az;
    mt19937 gen(az());
    if(tipoDadoEnfrentamiento == 1){        //para que haga el dado del 1-20
        uniform_int_distribution<int> distribucion(1,20);
        return distribucion(gen); 
    }else{                                  //para que haga el dado del 1-10
        uniform_int_distribution<int> distribucion(1,10);
        return distribucion(gen); 
    } 
}
//=========================================================================================================
//funciones para "descanzar"
//funcion para enseñar los segundos y la vida adquirida
void displayClock(entidad personaje, int seconds) {
    cout << setfill('0') << setw(2) << seconds << " sec | "<< personaje.hp<< " vida "<<endl;
}
//funcion para que cada segundo suba la vida del personaje teniendo un limite de 30 segundos
int Descansar(entidad personaje) {
    int seconds=0;
    bool timer = true;
    while (seconds != 30 && personaje.hp <75) {
        displayClock(personaje,seconds);
        sleep(1);
        personaje.hp++;
        seconds++;
    } 
    cout<<"Has descansado lo suficiente"<<endl;
    timer = false;
    seconds = 0;
    return personaje.hp;
}
//=========================================================================================================
//funcion para "correr" o salir de combate
int correr(entidad personaje){
    int opDescansar;
    cout<<"Corres y te escondes del monstruo mientras el se va"<<endl;
            //el personaje vuelve a la camara anterior, resta de variable de la camara:

            do{
                cout<<"++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
                cout<<"Desea descansar?"<<endl;
                cout<<"1. Si"<<endl;
                cout<<"2. No"<<endl;
                cout<<"++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
                cin>>opDescansar;

                switch(opDescansar){
                    case 1:{
                        //llamar funcion descansar:
                        personaje.hp = Descansar(personaje);
                    }
                    break;

                    case 2:{
                        cout<<"+++++++++++++++++++++++++++++"<<endl;
                        cout<<"Decides no descanzar"<<endl;
                        cout<<"+++++++++++++++++++++++++++++"<<endl;
                    }
                    break;

                    default:{
                        cout<<"Opcion invalida!"<<endl;
                    }
                    break;
                }
            
            }while(opDescansar != 1 && opDescansar != 2);
    return personaje.hp;
}
//=========================================================================================================
//funciones para los turnos
//funcion para el ataque del personaje
int AtaquePersonaje(int monstruoEnCombate, entidad*monstruos,entidad personaje,int ataqueBonoPersonaje, int tipoDadoEnfrentamiento){
    int op,acertarAtaque,critico = 1;//variable opcion2 para poder tirar los dados y critico para aumentar el daño dependiendo del numero que salga del primer dado

                        acertarAtaque = dado(tipoDadoEnfrentamiento);//se obtiene el numero de este dado y ver si ataca o no
                        cout<<"-------------------------------------------------------"<<endl;
                        cout<<"Tiras el dado y obtienes un "<<acertarAtaque<<endl;
                        if(acertarAtaque == 20){    //si el dado resulta dar 20 le dara un bono de x2
                            critico = 2;
                        }
                    if(acertarAtaque > monstruos[monstruoEnCombate].def){
                        cout<<"Enhorabuena, lograste acertar el ataque!"<<endl;
                        cout<<"Ahora tira los dos dados para calcular el danio del ataque!!"<<endl;
                        do{
                            cout<<endl;
                            cout<<"1. Tirar ambos dados"<<endl;
                            cin>>op;

                            if(op == 1){
                                tipoDadoEnfrentamiento = 2;//se usa el 2 para cambiar el modo del dado y solo sea de 1-10
                                int daño1 = dado(tipoDadoEnfrentamiento);
                                int daño2 = dado(tipoDadoEnfrentamiento);
                                if(critico == 2){
                                    cout<<"------------------------------------------------------"<<endl;
                                    cout<<"Lograste pegar un golpe critico!!"<<endl;
                                    cout<<"Tu danio se multiplica por 2!"<<endl;
                                }
                                cout<<"-------------------------------------------------------"<<endl;
                                cout<<"Con el primer dado salio un "<<daño1<<" y con el segundo un "<<daño2<<"!!"<<endl;
                                cout<<"Tu bono de ataque es "<<ataqueBonoPersonaje<<" por lo que tu danio total es "<<(daño1 + daño2 + ataqueBonoPersonaje)*critico<<endl;
                                cout<<"-------------------------------------------------------"<<endl;
                                //llamar funcion quitar vida:
                                monstruos[monstruoEnCombate].hp = monstruos[monstruoEnCombate].hp - ((daño1 + daño2 + ataqueBonoPersonaje)*critico);

                                if(monstruos[monstruoEnCombate].hp <= 0){
                                    cout<<"Lo lograste!! Venciste al enemigo!"<<endl;
                                    cout<<"-------------------------------------------------------"<<endl;
                                }
                            }else{
                                cout<<"Opcion invalida!"<<endl;
                            }
                        }while(op != 1);
                    }else{
                        cout<<"Intentas atacarlo, pero su defensa es mayor, por lo que fallas"<<endl;
                    }
    return monstruos[monstruoEnCombate].hp;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//funcion para el turno del monstruo
int TurnoMonstruo(entidad personaje, int ataqueBonoMonstruo, int tipoDadoEnfrentamiento){
    int acertarAtaque = 0;
    acertarAtaque = dado(tipoDadoEnfrentamiento);
        cout<<"-------------------------------------------------------"<<endl;
        cout<<"El enemigo tira el dado y obtiene un "<<acertarAtaque<<endl;
        if(acertarAtaque >= personaje.def + 1){
            cout<<"-------------------------------------------------------"<<endl;
            cout<<"El enemigo logro pasar sobre tu defensa!!"<<endl;
            cout<<"Cuidado! Ahora el enemigo tirara los dados"<<endl;
                tipoDadoEnfrentamiento = 2; //se usa el 2 para cambiar el modo del dado y solo sea de 1-10
                int daño1 = dado(tipoDadoEnfrentamiento);
                int daño2 = dado(tipoDadoEnfrentamiento);
                cout<<"------------------------------------------------------"<<endl;
                cout<<"Con el primer dado salio un "<<daño1<<" y con el segundo un "<<daño2<<"!!"<<endl;
                cout<<"El bono de ataque del enemigo es "<<ataqueBonoMonstruo<<" por lo que su daño total es "<<daño1 + daño2 + ataqueBonoMonstruo<<endl;
                //llamar funcion quitar vida:
                personaje.hp = personaje.hp - (daño1 + daño2 + ataqueBonoMonstruo);
                    if(personaje.hp <= 0){
                        cout<<"-------------------------------------------------------"<<endl;
                        cout<<"EL enemigo logra vencerte, pides piedad pero lo unico que le importa al monstruo es sangre!"<<endl;
                        cout<<"-------------------------------------------------------"<<endl;
                    }
        }else{
                    cout<<"-------------------------------------------------------"<<endl;
                    cout<<"El enemigo corre furioso hacia ti, pero tu defensa logra repeler su ataque"<<endl;
                    cout<<"-------------------------------------------------------"<<endl;
        }
    return personaje.hp;
}
//=========================================================================================================
//Funcion principal del enfrentamiento entre ambas entidades
int enfrentamiento(int monstruoEnCombate,entidad*monstruos,entidad personaje, bool finCombate){ //para el turno y enseñar los demas datos, igual del personaje
    int op,op2,                //variables para los menus
    tipoDadoEnfrentamiento = 1,//la variable tipo de dado hara que la funcion de dado() pueda usarse para calcular si acierta el ataque y para el ataque, ya que para certar el dado puede conseguir un numero entre el 1 y 20, en cambio en el ataque los dos dados estan limitados a conseguir del 1 al 10
                                // si la variable "tipoDadoEnfrentamiento" es 1, entonces usara el dado 1-20, si esta en 2 sera 1-10
    pPrincip, ag = 0,          //variables para la funcion combate
    ataqueBonoPersonaje, ataqueBonoMonstruo, agilidadBonoPersonaje, agilidadBonoMonstruo;//variables para el bono de agilidad y ataque

    //------------------------------------------------------------------------------------------------------------------------------
    //esta parte es para sacar el bono de ataque
    pPrincip = 1; //variable para saber si se esta sacando el bono de ataque del personaje principal o del monstruo
    ataqueBonoPersonaje = bono(personaje,monstruos,monstruoEnCombate, pPrincip, ag); //variable que solo se inicializa una vez

    pPrincip = 0;
    ataqueBonoMonstruo = bono(personaje,monstruos,monstruoEnCombate, pPrincip, ag); //variable que se usa cada vez que hay nuevo enfrentamiento
    //------------------------------------------------------------------------------------------------------------------------------
    //esta parte es para sacar el bono de agilidad
    pPrincip = 1;
    ag = 1; 
    agilidadBonoPersonaje = bono(personaje,monstruos,monstruoEnCombate, pPrincip, ag); //variable que solo se inicializa una vez

    pPrincip = 0;
    agilidadBonoMonstruo = bono(personaje,monstruos,monstruoEnCombate, pPrincip, ag); //variable que se usa cada vez que hay nuevo enfrentamiento
    ag = 0;
    //------------------------------------------------------------------------------------------------------------------------------  
    do{
        cout<<"Empieza el combate!!"<<endl;
        Sleep(800);
        cout<<"Aventurero, tira tu dado!"<<endl;
        Sleep(800);
        cout<<"1. Tirar dado"<<endl;
        cout<<"2. Correr"<<endl;
        cin>>op;

        if(op == 1){
            int dadoMonstruo,dadoPersonaje;
            do{
                dadoPersonaje = dado(tipoDadoEnfrentamiento);
                dadoMonstruo = dado(tipoDadoEnfrentamiento);
                cout<<"Obtuviste un "<<dadoPersonaje<<endl;
                Sleep(500);
                cout<<"Tu agilidad es de "<<personaje.agilidad<<", por lo que obtuviste un "<<dadoPersonaje + agilidadBonoPersonaje<<endl;
                Sleep(1000);
                cout<<"-----------------------------"<<endl;
                cout<<"El enemigo tira el dado y obtiene un "<<dadoMonstruo<<endl;
                Sleep(500);
                cout<<"Su agilidad es de "<<monstruos[monstruoEnCombate].agilidad<<", por lo que obtuvo un "<<dadoMonstruo + agilidadBonoMonstruo<<endl;
                Sleep(1000);

                //primer caso, si el usuario obtiene mayor numero al enemigo
                if(dadoPersonaje + agilidadBonoPersonaje > dadoMonstruo + agilidadBonoMonstruo){
                    cout<<"======================================================================"<<endl;
                    cout<<"Empiezas tu aventurero!"<<endl;
                    Sleep(500);
                    do{
                        cout<<endl;
                        cout<<endl;
                        cout<<"Ahora vas tu aventurero!"<<endl;
                        Sleep(1000);
                        cout<<"-------------------------------------------------------"<<endl;
                        cout<<"Tu vida es ["<<personaje.hp<<"]"<<endl;
                        Sleep(500);
                        cout<<"La vida de tu enemigo es ["<<monstruos[monstruoEnCombate].hp<<"] y su defensa es de ["<<monstruos[monstruoEnCombate].def<<"]"<<endl;
                        Sleep(500);
                        cout<<endl;
                        cout<<"1. Tirar dado"<<endl;
                        cout<<"2. Correr"<<endl;
                        cin>>op2;
                        do{
                            switch(op2){
                                case 1:{
                                    monstruos[monstruoEnCombate].hp = AtaquePersonaje(monstruoEnCombate,monstruos,personaje,ataqueBonoPersonaje,tipoDadoEnfrentamiento);
                                }
                                break;

                                case 2:{
                                    //llamar funcion de correr  y descansar:
                                    correr(personaje);
                                    finCombate = true;
                                }
                                break;

                                default:{
                                    cout<<"Opcion invalida!!"<<endl;                              
                                }
                                break;
                            }
                        }while(op2 != 1 && op != 2);    
                        cout<<"======================================================================"<<endl;
                        if (monstruos[monstruoEnCombate].hp > 0 && finCombate != true){
                            cout<<endl;
                            cout<<endl;
                            cout<<"Ahora es el turno del enemigo!"<<endl;
                            personaje.hp =TurnoMonstruo(personaje,ataqueBonoMonstruo,tipoDadoEnfrentamiento);
                            cout<<"======================================================================"<<endl;
                                if(personaje.hp <= 0){
                                    finCombate = true;
                                }
                        }else{
                            finCombate = true;
                        }
                    }while(finCombate == false);

                //segundo caso, si el enemigo obtiene mayor numero al usuario
                }else if(dadoPersonaje + agilidadBonoPersonaje < dadoMonstruo + agilidadBonoMonstruo){
                    cout<<"====================================================================="<<endl;
                    cout<<"Empieza el enemigo!"<<endl;
                        do{
                            cout<<endl;
                            cout<<endl;
                            cout<<"Ahora es el turno del enemigo!"<<endl;
                            personaje.hp =TurnoMonstruo(personaje,ataqueBonoMonstruo,tipoDadoEnfrentamiento);
                            cout<<"======================================================================"<<endl;
                            if (personaje.hp > 0){
                                cout<<endl;
                                cout<<endl;
                                cout<<"Ahora es tu turno aventurero!"<<endl;
                                cout<<"-------------------------------------------------------"<<endl;
                                cout<<"Tu vida es ["<<personaje.hp<<"]"<<endl;
                                cout<<"La vida de tu enemigo es ["<<monstruos[monstruoEnCombate].hp<<"] y su defensa es de ["<<monstruos[monstruoEnCombate].def<<"]"<<endl;
                                cout<<endl;
                                cout<<"1. Tirar dado"<<endl;
                                cout<<"2. Correr"<<endl;
                                cin>>op2;
                                do{
                                    switch(op2){
                                        case 1:{
                                            monstruos[monstruoEnCombate].hp = AtaquePersonaje(monstruoEnCombate,monstruos,personaje,ataqueBonoPersonaje,tipoDadoEnfrentamiento);
                                        }
                                        break;

                                        case 2:{
                                            //llamar funcion de correr  y descansar:
                                            correr(personaje);
                                            finCombate = true;
                                        }
                                        break;

                                        default:{
                                            cout<<"Opcion invalida!!"<<endl;                                    
                                        }
                                        break;
                                    }
                                }while(op2 != 1 && op2 != 2);
                            }else{
                                finCombate = true;
                            }
                    }while(finCombate == false);

                //tercer caso, si ambos obtienen un mismo numero
                }else{
                    cout<<endl;
                    cout<<"Ambos dados salieron iguales!!"<<endl;
                    cout<<endl;
                    cout<<"Se repite!"<<endl;
                }
            }while(dadoPersonaje != dadoMonstruo && finCombate == false);

        }else if(op == 2){
            correr(personaje);

        }else{
            cout<<"Opcion invalida"<<endl;
        }
    }while(op != 1 && op != 2);
    return personaje.hp;
}
//==========================================================================================================

int main(){
    //variables
    int acertarAtaque, monstruoEnCombate; //variables para funcion
    bool finCombate = false;

    entidad personaje;//estadisticas del personaje
    personaje.hp = 75;
    personaje.def = 1;
    personaje.atk = 10;
    personaje.agilidad = 10;

    entidad monstruos[5];//estadisticas de los monstruos
    //posicion 0 es la del duende   |hp30,def07,atk06,ag12
    //posicion 1 es la del esqueleto|hp45,def12,atk08,ag08 
    //posicion 2 es la del mimic    |hp50,def08,atk12,ag10 
    //posicion 3 es la del centauro |hp60,def14,atk10,ag14
    //posicion 4 es la del dragon   |hp90,def16,atk16,ag16 

    //duende
    monstruos[0].hp = 30;
    monstruos[0].def = 7;
    monstruos[0].atk = 6;
    monstruos[0].agilidad = 12;

    //esqueleto
    monstruos[1].hp = 45;
    monstruos[1].def = 12;
    monstruos[1].atk = 5;
    monstruos[1].agilidad = 8;

    //mimic
    monstruos[2].hp = 50;
    monstruos[2].def = 8;
    monstruos[2].atk = 12;
    monstruos[2].agilidad = 10;

    //centauro
    monstruos[3].hp = 60;
    monstruos[3].def = 14;
    monstruos[3].atk = 10;
    monstruos[3].agilidad = 14;

    //dragon
    monstruos[4].hp = 90;
    monstruos[4].def = 16;
    monstruos[4].atk = 16;
    monstruos[4].agilidad = 16;

    monstruoEnCombate = 0;//esta variable sirve para saber contra que monstruo peleara, es la posicion del array monstruos

//------------------------------------------------------------------------------------------------------------------------------    
    personaje.hp = enfrentamiento(monstruoEnCombate,monstruos,personaje,finCombate);

    if(personaje.hp <= 0){
        cout<<"Game Over"<<endl;
        //variable para terminar todo el programa:

    }
}