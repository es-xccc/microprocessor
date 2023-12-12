#include<regx52.h>

code char two_phase[] = {0x0c,0x06,0x03,0x09};
int dir, delay_time;

void delay(int);
void turn();

void main() {
    delay_time=500;
    dir=1;

    while(1) {
        if(P2 < 25){
            delay_time=4800;
            dir = 0;
        } else if(P2 < 50) {
            delay_time=2400;
            dir = 0;
        } else if(P2 < 75) {
            delay_time=1200;
            dir = 0;
        } else if(P2 < 100) {
            delay_time=600;
            dir = 0;
        } else if(P2 < 128){
            delay_time=300;
            dir = 0;
        }

        else if(P2 < 153){
            delay_time=4800;
            dir = 1;
        } else if(P2 < 178){
            delay_time=2400;
            dir = 1;
        } else if(P2 < 203){
            delay_time=1200;
            dir = 1;
        } else if(P2 < 228){
            delay_time=600;
            dir = 1;
        } else if(P2 < 257){
            delay_time=300;
            dir = 1;
        }
        turn();
    }
}

void turn() {
    int x;
    if(dir==1) {
        for(x=0;x<4;x++) {
            P1=two_phase[x];
            delay(delay_time);
        }
    } else {
        for(x=3;x>=0;x--) {
            P1=two_phase[x];
            delay(delay_time);
        }
    }
}

void delay(int t) {
    while(t--);
}
