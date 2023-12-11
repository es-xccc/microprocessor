#include<regx52.h>

code char one_and_half_phase[] = {0x01,0x09,0x08,0x0c,0x04,0x06,0x02,0x03};
int dir, speed, delay_time;

void delay(int);
void turn();

void main() {
    IT0=1;
    IT1=1;
    EX0=1;
    EX1=1;
    EA=1;
    delay_time=500;
    dir=1;
    speed=1;

    while(1) {
        turn();
    }
}

void turn() {
    int x;
    if(dir==1) {
        for(x=0;x<8;x++) {
            P1=one_and_half_phase[x];
            delay(delay_time);
        }
    } else {
        for(x=8;x>0;x--) {
            P1=one_and_half_phase[x];
            delay(delay_time);
        }
    }
}

void delay(int t) {
    while(t--);
}

void int_0(void) interrupt 0 {
    dir=(dir==1)?0:1;
}

void int_1(void) interrupt 2 {
    delay_time=(delay_time==500)?3000:500;
}