#include<regx52.h>

code char two_phase[] = {0x0c,0x06,0x03,0x09};
int delay_time;

void delay(int);
void turn();

void main() {
    delay_time=500;

    while(1) {
        if(P2 < 50){
            delay_time=1600;
        }
        else if(P2 < 100){
            delay_time=800;
        }
        else if(P2 < 150){
            delay_time=400;
        }
        else if(P2 < 200){
            delay_time=200;
        }
        else{
            delay_time=100;
        }
        // do not use delay_time=100, the motor will not turn;
        turn();
    }
}

void turn() {
    int x;
    for(x=0;x<4;x++) {
        P1=two_phase[x];
        delay(delay_time);
    }
}

void delay(int t) {
    while(t--);
}
