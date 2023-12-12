#include <regx52.h>

void main() {
    IT0 = 0; // enable a low-level signal on external interrupt
    EX0 = 1; // enable INT0
    EA = 1; // enable interrupt
    P3_4 = 0; // WR=0, clean the data
    P3_4 = 1; // WR=1, analog convert to digital
    while(1); // infinite loop
}

void int_0(void) interrupt 0 { // INT0 interrupt function
    P3_5 = 0; // RD=0, enable read
    if (P1 > 256 / 2) {
        P2 = 0;
    } else {
        P2 = 255;
    }
    P3_5 = 1; // RD=1, stop read
    P3_4 = 0; // WR=0, clean the data
    P3_4 = 1; // WR=1, analog convert to digital
}