#include <iostream>
#include <random>
using namespace std;

//struct para las entidades
struct entidad{
int hp, def, atk, agilidad;
};

//funciones
//===============================================================
//funciones para el bono de ataque
int bonoPersonaje(entidad personaje, entidad*monstruos, int monstruoEnCombate, int pPrincip, int ag){
    int bonus = 0;
    if(pPrincip == 1 && ag == 0){
        if(personaje.atk != 10){
            bonus = ((personaje.atk - 10)/2);
        }
    }else if(pPrincip == 0 && ag == 0){
        if(monstruos[monstruoEnCombate].atk != 10){
            bonus = ((monstruos[monstruoEnCombate].atk - 10)/2);
        }
    }else if(pPrincip == 1 && ag == 1){
        if(personaje.agilidad != 10){
            bonus = ((personaje.agilidad - 10)/2);
        }
    }else {
        if(monstruos[monstruoEnCombate].agilidad != 10){
            bonus = ((monstruos[monstruoEnCombate].agilidad - 10)/2);
        }
    }
    return bonus;
}
/*int bonoMonstruo(entidad*monstruos,int monstruoEnCombate){
    int bonusAtk;
    if(monstruos[monstruoEnCombate].atk != 10){
        bonusAtk = ((monstruos[monstruoEnCombate].atk - 10)/2);
    }
    return bonusAtk;
}*/
//=================================================================
//funcion para el dado
int dado(int tipoDadoEnfrentamiento){
    random_device az;
    mt19937 gen(az());
    if(tipoDadoEnfrentamiento == 1){
        uniform_int_distribution<int> distribucion(1,20);
        return distribucion(gen); 
    }else{
        uniform_int_distribution<int> distribucion(1,10);
        return distribucion(gen); 
    } 
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
                if(opDescansar == 1){
                    //llamar funcion descansar:

                }else if(opDescansar == 2){
                    cout<<"+++++++++++++++++++++++++++++"<<endl;
                    cout<<"Decides no descanzar"<<endl;
                    cout<<"+++++++++++++++++++++++++++++"<<endl;

                }else{
                    cout<<"Opcion invalida!"<<endl;
                }
            }while(opDescansar != 1 && opDescansar != 2);
    return personaje.hp;
}
//=========================================================================================================
//funciones para los turnos
//funcion para el turno del personaje
int TurnoPersonaje(int monstruoEnCombate, entidad*monstruos,entidad personaje,int ataqueBonoPersonaje, int tipoDadoEnfrentamiento){
    int op,op2,acertarAtaque,critico = 1;//variable opcion2 para poder tirar los dados
    bool turnoTerminado = false;
        do{
            cout<<"-------------------------------------------------------"<<endl;
            cout<<"Tu vida es ["<<personaje.hp<<"]"<<endl;
            cout<<"La vida de tu enemigo es ["<<monstruos[monstruoEnCombate].hp<<"] y su defensa es de ["<<monstruos[monstruoEnCombate].def<<"]"<<endl;
            cout<<endl;
            cout<<"1. Tirar dado"<<endl;
            cout<<"3. Usar pocion"<<endl;
            cout<<"3. Correr"<<endl;
            cin>>op;
            switch(op){
                case 1:{
                        turnoTerminado = true;
                        acertarAtaque = dado(tipoDadoEnfrentamiento);
                        cout<<"-------------------------------------------------------"<<endl;
                        cout<<"Tiras el dado y obtienes un "<<acertarAtaque<<endl;
                        if(acertarAtaque == 20){
                            critico = 2;
                        }
                    if(acertarAtaque > monstruos[monstruoEnCombate].def){
                        cout<<"Enhorabuena, lograste acertar el ataque!"<<endl;
                        cout<<"Ahora tira los dos dados para calcular el danio del ataque!!"<<endl;
                        do{
                            cout<<endl;
                            cout<<"1. Tirar ambos dados"<<endl;
                            cin>>op2;

                            if(op2 == 1){
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
                        }while(op2 != 1);
                    }else{
                        cout<<"Intentas atacarlo, pero su defensa es mayor, por lo que fallas"<<endl;
                    }
                }      
                break;

                case 2:{
                    //llamar funcion de pocion:

                    cout<<"en construccion"<<endl;
                    turnoTerminado = true;
                }    
                break;

                case 3:{
                    //llamar funcion de correr  y descansar:
                    correr(personaje);
                    turnoTerminado = true;
                }
                break;

                default:
                    cout<<"Opcion invalida!!"<<endl;
                break;
            }
        }while(op != 1 && op != 2 && op != 3);
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
                                cout<<"EL enemigo logra vencerte, pides piedad pero lo unico que le importa al monstruo es sangre!"<<endl;
                                cout<<"-------------------------------------------------------"<<endl;
                            }
                }else{
                    cout<<"El enemigo corre furioso hacia ti, pero tu defensa logra repeler su ataque"<<endl;
                    cout<<"-------------------------------------------------------"<<endl;
                }
        return personaje.hp;
    }
//=========================================================================================================
//Funcion principal del enfrentamiento entre ambas entidades
int enfrentamiento(int monstruoEnCombate,entidad*monstruos,entidad personaje,int ataqueBonoPersonaje, int ataqueBonoMonstruo, int agilidadBonoPersonaje, int agilidadBonoMonstruo, bool finCombate){ //para el turno y enseñar los demas datos, igual del personaje
    int op, 
    tipoDadoEnfrentamiento = 1;//la variable tipo de dado hara que la funcion de dado() pueda usarse para calcular si acierta el ataque y para el ataque, ya que para certar el dado puede conseguir un numero entre el 1 y 20, en cambio en el ataque los dos dados estan limitados a conseguir del 1 al 10
    // si la variable "tipoDadoEnfrentamiento" es 1, entonces usara el dado 1-20, si esta en 2 sera 1-10 
    do{
        cout<<"Empieza el combate!!"<<endl;
        cout<<"Aventurero, tira tu dado!"<<endl;
        cout<<"1. Tirar dado"<<endl;
        cout<<"2. Correr"<<endl;
        cin>>op;

        if(op == 1){
            int dadoMonstruo,dadoPersonaje;
            do{
                dadoPersonaje = dado(tipoDadoEnfrentamiento);
                dadoMonstruo = dado(tipoDadoEnfrentamiento);
                cout<<"Obtuviste un "<<dadoPersonaje<<endl;
                cout<<"Tu agilidad es de "<<personaje.agilidad<<", por lo que obtuviste un "<<dadoPersonaje + agilidadBonoPersonaje<<endl;
                cout<<"-----------------------------"<<endl;
                cout<<"El enemigo tira el dado y obtiene un "<<dadoMonstruo<<endl;
                cout<<"Su agilidad es de "<<monstruos[monstruoEnCombate].agilidad<<", por lo que obtuvo un "<<dadoMonstruo + agilidadBonoMonstruo<<endl;

                //primer caso, si el usuario obtiene mayor numero al enemigo
                if(dadoPersonaje + agilidadBonoPersonaje > dadoMonstruo + agilidadBonoMonstruo){
                    cout<<"======================================================================"<<endl;
                    cout<<"Empiezas tu aventurero!"<<endl;
                    do{
                        cout<<endl;
                        cout<<endl;
                        cout<<"Ahora vas tu aventurero!"<<endl; //posible cambio de bool a hp y el bool quedaria afuera
/*cambio de bool a int*/    monstruos[monstruoEnCombate].hp = TurnoPersonaje(monstruoEnCombate,monstruos,personaje,ataqueBonoPersonaje,tipoDadoEnfrentamiento);
                        cout<<"======================================================================"<<endl;
                        if (monstruos[monstruoEnCombate].hp > 0){
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
                            monstruos[monstruoEnCombate].hp = TurnoPersonaje(monstruoEnCombate,monstruos,personaje,ataqueBonoPersonaje,tipoDadoEnfrentamiento);
                            cout<<"======================================================================"<<endl;
                                if(monstruos[monstruoEnCombate].hp <= 0){
                                    finCombate = true;
                                }
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
    int acertarAtaque, ataque1, ataque2, ataqueBonoPersonaje,ataqueBonoMonstruo, agilidadBonoPersonaje, agilidadBonoMonstruo,monstruoEnCombate, pPrincip, ag = 0;
    bool finCombate = false;

    entidad personaje;//estadisticas del personaje
    personaje.hp = 75;
    personaje.def = 1;
    personaje.atk = 10;
    personaje.agilidad = 10;

    entidad monstruos[5];//estadisticas de los monstruos
    //posicion 0 es la del duende   |hp30,def07,atk06 
    //posicion 1 es la del esqueleto|hp45,def12,atk08 
    //posicion 2 es la del mimic    |hp50,def08,atk12 
    //posicion 3 es la del centauro |hp60,def14,atk10 
    //posicion 4 es la del dragon   |hp90,def16,atk16 

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
    //esta parte es para sacar el bono de ataque
    pPrincip = 1; //variable para saber si se esta sacando el bono de ataque del personaje principal o del monstruo
    ataqueBonoPersonaje = bonoPersonaje(personaje,monstruos,monstruoEnCombate, pPrincip, ag);

    pPrincip = 0;
    ataqueBonoMonstruo = bonoPersonaje(personaje,monstruos,monstruoEnCombate, pPrincip, ag);
//------------------------------------------------------------------------------------------------------------------------------
    //esta parte es para sacar el bono de agilidad
    pPrincip = 1;
    ag = 1; 
    agilidadBonoPersonaje = bonoPersonaje(personaje,monstruos,monstruoEnCombate, pPrincip, ag);

    pPrincip = 0;
    agilidadBonoMonstruo = bonoPersonaje(personaje,monstruos,monstruoEnCombate, pPrincip, ag);
    ag = 0;
//------------------------------------------------------------------------------------------------------------------------------    
    personaje.hp = enfrentamiento(monstruoEnCombate,monstruos,personaje,ataqueBonoPersonaje,ataqueBonoMonstruo,agilidadBonoPersonaje, agilidadBonoMonstruo, finCombate);
    if(personaje.hp <= 0){
        cout<<"Game Over"<<endl;
        //variable para terminar todo el programa:

    }
}