#include<regx52.h>

bit receive_full = 0;
bit transmit_flag = 1;

char index = 0;
char rxbuf[9];

char *stuID = "E94106216";
char *correct = "\r\nCorrect\r\n";
char *wrong = "\r\nWrong\r\n";
int i = 0;

void init_UART() {
    SCON = 0x50;
    TMOD = 0x20;
    TH1 = 0xE6;
    TR1 = 1;
    IE = 0x90;
}

void UART_ISR() interrupt 4 {
    if(RI) {
        RI = 0;
        rxbuf[index++] = SBUF;
        P2 = rxbuf[index - 1];
        index %= 9;
        if(!index) receive_full = 1;
    } else {
        TI = 0;
        transmit_flag = 1;
    }
}

void send_msg(char *c) {
    for(; *c!= '\0'; c++) {
        while(!transmit_flag);
        transmit_flag = 0;
        SBUF = *c;
    }
}

int check() {
    for(i=0; i<9; i++) {
        if(*(stuID + i) != *(rxbuf + i))
            return 0;
    }
    return 1;
}

void main() {
    init_UART();

    while(1) {
        if(receive_full) {
            receive_full = 0;

            if(check()) {
                send_msg(correct);
            } else {
                send_msg(wrong);
            }
        }
    }
}