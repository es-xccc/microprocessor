#include <regx51.h>

void print_msg(char *);
void write(char, int);
void delay(unsigned int);

void main() {
    write(0x38, 0); //00111000
    write(0x0F, 0); //00001111
    write(0x06, 0); //00000110
    write(0x01, 0); //00000001
    write(0x80, 0); //10000000
    print_msg("E94106216");
    write(0x40,0); //ROW1
    write(0x0A,1);
    write(0x41,0); //ROW2
    write(0x0A,1);
    write(0x42,0); //ROW3
    write(0x1F,1);
    write(0x43,0); //ROW4
    write(0x15,1);
    write(0x44,0); //ROW5
    write(0x1B,1);
    write(0x45,0); //ROW6
    write(0x1F,1);
    write(0x46,0); //ROW7
    write(0x00,1);
    write(0xC0, 0); //10000000
    write(0x00,1); //write icon 
    while (1);
}

void print_msg(char *msg){
    for (;*msg!='\0'; msg++){ 
        write(*msg,1); 
    }
}

void write(char cmd, int rs_value){
    P1 = cmd;          //D0-D7
    P3_0= rs_value;    //RS
    P3_1=1;            // write 0.1ms
    delay(100);        
    P3_1=0;
}

void delay(unsigned int i){
    while (i--);
}