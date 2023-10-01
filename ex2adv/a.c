#include <8051.h>

#define TABLE_SIZE 4

code unsigned char TABLE[TABLE_SIZE] = {0x83, 0xA4, 0xF9, 0x83};

void delay() {
    unsigned char i = 250;
    while (i > 0) {
        i--;
    }
}

void main() {
    unsigned char R0 = 4; // 4 LED
    unsigned char R1 = 0; // table index
    unsigned char R2 = 0xFE; // LED drive pin (c0~c3)

    while (1) {
        P2 = R2; // select LED
        unsigned char value = TABLE[R1];
        P1 = value; // move value to P1
        delay(); // delay 0.5 ms
        R1++; // increase R1
        R2 = (R2 << 1) | (R2 >> 7); // rotate R2

        if (--R0 == 0) {
            R0 = 4;
        }
    }
}
