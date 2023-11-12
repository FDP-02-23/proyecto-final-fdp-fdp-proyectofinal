#include <iostream>
#include <random>
using namespace std;

struct entidad{
int hp = 100, def = 1, atk = 10;
};
int bono(){
    int bonusAtk;
    entidad personaje;
    if(personaje.atk >= 10){
        bonusAtk = (personaje.atk - 10)/2;
    }
}


int ataque(){
    random_device az;
    mt19937 gen(az());
    uniform_int_distribution<int> distribucion(1,20);
    return distribucion(gen); 

}
int enfrentamiento(){
    
}



int main(){
    //variables
    int dmg;
    entidad monstruos[3];
    
    
    dmg = ataque();  
}