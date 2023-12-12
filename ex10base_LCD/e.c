#include <regx52.h>
#include <string.h>

void print_msg(char[]);
void write(char, int); 
void delay(unsigned int);

void main() {
    write(0x38, 0); // use 2 lines and 5x7 matrix
    write(0x0F, 0); // LCD ON, cursor ON, cursor blinking ON
    write(0x06, 0); // increment cursor
    write(0x01, 0); // clear screen
    write(0x80, 0); // DDRAM 1st row 1st column (00H)
    print_msg("Hello, world!"); // display ‘Hello world!’
    while (1);
}

void print_msg(char msg[]) {
    int i;
    for (i=0; i<strlen(msg); i++) // for every character
        write(msg[i], 1); // monitor displays character
}

void write(char cmd, int rs_value) {
    P1 = cmd; // P1=cmd
    P3_0 = rs_value; // RS=rs (1or0)
    P3_1 = 1; // ENABLE high
    delay(100);
    P3_1 = 0; // ENABLE low
}

void delay(unsigned int i) {
    while (i--); 
}