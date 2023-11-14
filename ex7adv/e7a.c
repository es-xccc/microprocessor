#include <regx52.h>		// include header file for 8051
#define TH0_init (15536/256)		//TH0_init= 256 - 250
#define TL0_init (15536%256)		//TL0_init = 256 - 250
#define Timer0_int_exe_time 10	//the parameter can be changed	

int counter;

void main(){
	TCON = 0x10;
	TMOD = 0x09;	//set timer0 to mode 2(8-bits and autoo-reload)
	IE = 0x82;	//enable timer0 interrupt1
	P2 = 0xFE;	
	P3_2 = 0;
	TL0 = TL0_init;	//set TH0 & TL0
	TH0 = TH0_init;
	while(1){
		
	}
}

void timer0_interrupt(void)interrupt 1{		//"interrupt 1" is intvector of INT0
	counter++;
	if(counter == Timer0_int_exe_time){		//250clock cycle * 2000 = 0.5 second
		int temp;
		if(P2_7 == 0){
			P2 = 0xFE;
		}else{
			temp = ~P2;
			temp = temp<<1;
			P2 = ~temp;
		}
		counter =0;
	}
}
