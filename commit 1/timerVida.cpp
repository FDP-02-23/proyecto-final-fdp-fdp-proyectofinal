#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void displayClock(int seconds, int vida) {

    cout << setfill('0') << setw(2) << seconds << " sec |"<< vida << " vida "<<endl;
}

int timer(int vida, int seconds) {

    bool timer = true;
    while (timer && vida <=75) {
        displayClock(vida, seconds);
        sleep(1);
        seconds++;
        vida++;

        if (seconds == 60 || vida==75) {
            cout<<"Has descansado lo suficiente"<<endl;
            timer = false;
            seconds = 0;
        }
    } 
    return vida;
}

int main(){

int vida = 0;
int seconds = 0;

    int hp = timer(vida,seconds);

    cout<<"Su vida es: "<<hp;
    return 0;
}