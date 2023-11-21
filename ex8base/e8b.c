#include <regx52.h>

// Declare UART function
void init_uart(); 

// Receive data
char recivevalue; 

void main() {
    init_uart();
    while (1); // Infinite loop
}

void init_uart() {
    SCON = 0x50; // Mode1
    TMOD = 0x20; // Timer1 Mode2
    TH1 = 0xe6; // Set Baud=1200
    TR1 = 1; // Enable TCON Timer1
    IE = 0x90; // Enable UART
}

void UART_Isr(void) interrupt 4 { // UART
    while (RI == 0); // Wait for receive flag == 1
    RI = 0; // Clear flag
    recivevalue = SBUF;
    P2 = recivevalue; // Display data on LED

    if (recivevalue == 'q') {
        SBUF = recivevalue; // Load data
        while (TI == 0); // Wait for transmit flag == 1
        TI=0; // Clear flag
    }
}