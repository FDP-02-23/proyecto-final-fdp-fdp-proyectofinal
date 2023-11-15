#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void displayClock(int vida, int seconds) {
    cout << setfill('0') << setw(2) << seconds << " sec | "<< vida<< " vida "<<endl;
}

int Descansar(int vida, int seconds) {

    bool timer = true;
    while (seconds != 30 && vida <75) {
        displayClock(vida,seconds);
        sleep(1);
        vida++;
        seconds++;
    } 
        cout<<"Has descansado lo suficiente"<<endl;
        timer = false;
        seconds = 0;
    return vida;

}
int main(){

int vida = 60;
int seconds = 1;

    int hp = Descansar(vida,seconds);
    cout<<"Su vida es: "<<hp;
    return 0;
}
