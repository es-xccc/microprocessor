#include <regx52.h>
#include <string.h>

void print_msg(char[]);
void write(char, int); 
void delay(unsigned int);
int counter0 = 0;
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int int0dis = 0;
char int0_msg[3];
int i = 0;
int hundreds, tens, ones;
char roll_msg[] = "I love embedded system.";
char temp;
int k = 0;
int icopy = 0;
char icopy_msg[16];

void main() {
    TMOD = 0x22;
    PX1=1;
    ET0=1;
    ET1=1;
    TL0=0x00;
    TH0=0x00;
    TL1=0x00;
    TH1=0x00;
    IT0=0;
    IT1=0;
    EX0=0;
    EX1=1;
    EA=1;
    write(0x38, 0); // use 2 lines and 5x7 matrix
    write(0x08, 0);
    delay(65535);
    delay(65535);
    delay(65535);
    write(0x0F, 0); // LCD ON, cursor ON, cursor blinking ON
    write(0x06, 0); // increment cursor
    write(0x01, 0); // clear screen
    while(1){
        if(P0 < 120){
            TR1 = 0;
            P2_0 = 0;
            P2_1 = 1;
            P2_2 = 1;
            if(P3_2 == 0){
                TR0 = 1;
            }
            else{
                TR0 = 0;
            }
        }
        else if(P0 < 180){
            P2_0 = 1;
            P2_1 = 0;
            P2_2 = 1;
            TR0 = 0;
            TR1 = 0;
            write(0x0F, 0);
            write(0x01, 0);
            write(0x80, 0);
            print_msg("E94106216");

            //skull
            write(0x40,0); //RAM POSITION
            write(0x00,1);
            write(0x0E,1);
            write(0x1F,1);
            write(0x15,1);
            write(0x0E,1);
            write(0x0E,1);
            write(0x00,1);
            write(0x00,1); //CURSOR
            //smile------------------------------------
            write(0x48,0); //RAM POSITION
            write(0x00,1);
            write(0x0A,1);
            write(0x0A,1);
            write(0x00,1);
            write(0x11,1);
            write(0x0E,1);
            write(0x00,1);	
            write(0x00,1);	//CURSOR

            write(0x8E,0);//PRINT POSITION
            write(0x00,1);
            write(0x8F,0);//PRINT POSITION
            write(0x01,1);

            write(0xC0,0);
            print_msg("Final exam");
            delay(65535);
            write(0x01, 0);
        }
        else if(P0 < 256){
            P2_0 = 1;
            P2_1 = 1;
            P2_2 = 0;
            TR0 = 0;
            TR1 = 1;
        }
    }
}

void int_1(void) interrupt 2 {
    if(P0 >= 120 && P0 < 180){
        write(0x01, 0);
        write(0x80, 0);
        print_msg("1");
        write(0xC0, 0);
        print_msg("2");
        delay(65535);
        delay(65535);
        delay(65535);
        delay(65535);
        delay(65535);
        delay(65535);
    }
}

void timer_0(void) interrupt 1 {
    counter0++;
    hundreds = int0dis / 100;
    tens = (int0dis / 10) % 10;
    ones = int0dis % 10;
    int0_msg[0] = hundreds + 48;
    int0_msg[1] = tens + 48;
    int0_msg[2] = ones + 48;
    if(counter0 == 255){
        counter1++;
        counter0 = 0;
    }
    if(counter1 == 10){
        if(int0dis < 100){
            int0dis += 5;
        }
        counter1 = 0;
        write(0x01, 0);
        write(0x80, 0);
        print_msg(int0_msg);
        print_msg("%");
        write(0xC0, 0);
        for(i = 0; i < int0dis / 10; i++){
            print_msg("=");
        }
        print_msg(">");
    }
}

void timer_1(void) interrupt 3 {
    counter2++;
    if(counter2 == 255){
        counter3++;
        counter2 = 0;
    }
    if(counter3 == 10){
        temp = roll_msg[0];
        for(k=0; k<22; k++){
            roll_msg[k] = roll_msg[k+1];
        }
        roll_msg[22] = temp;
        write(0x01, 0);
        write(0x80, 0);
        for(icopy = 0; icopy < 16; icopy++){
            icopy_msg[icopy] = roll_msg[icopy];
        }
        print_msg(icopy_msg);
        counter3=0;
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