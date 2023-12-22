#include <regx52.h>
#include <string.h>

void print_msg(char[]);
void write(char, int); 
void delay(unsigned int);
int itr0 = 0; // interrupt 0 counter
int itr1 = 0; // interrupt 1 counter

void main() {
    write(0x38, 0); // use 2 lines and 5x7 matrix
    write(0x0F, 0); // LCD ON, cursor ON, cursor blinking ON
    write(0x06, 0); // increment cursor
    write(0x01, 0); // clear screen
    while(1){
        write(0x01, 0); // clear screen
        write(0x80, 0); // DDRAM 1st row 1st column (00H)
        if(P0 < 81){
            print_msg("LOW");
        }
        else if(P0 < 171){
            print_msg("MIDDLE");
        }
        else if(P0 < 256){
            print_msg("HIGH");
        }
        write(0xC0, 0); // DDRAM 2nd row 1st column (40H)
        if(P0 < 20){
            print_msg("=");
        }
        else if(P0 < 40){
            print_msg("==");
        }
        else if(P0 < 60){
            print_msg("===");
        }
        else if(P0 < 80){
            print_msg("====");
        }
        else if(P0 < 120){
            print_msg("=====");
        }
        else if(P0 < 140){
            print_msg("======");
        }
        else if(P0 < 160){
            print_msg("=======");
        }
        else if(P0 < 180){
            print_msg("========");
        }
        else if(P0 < 200){
            print_msg("=========");
        }
        else if(P0 < 220){
            print_msg("==========");
        }
        else if(P0 < 240){
            print_msg("===========");
        }
        else if(P0 < 256){
            print_msg("============");
        }
        delay(16384);
    }
}

void print_msg(char msg[]) {
    int i;
    for (i=0; i<strlen(msg); i++) // for every character
        write(msg[i], 1); // monitor displays character
}

void write(char cmd, int rs_value) {
    P1 = cmd; // P1=cmd
    P3_6 = rs_value; // RS=rs (1or0)
    P3_7 = 1; // ENABLE high
    delay(100);
    P3_7 = 0; // ENABLE low
}

void delay(unsigned int i) {
    while (i--); 
}