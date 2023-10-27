ORG	0x00
				JMP	INIT
				ORG	0x03
				JMP	INT0_ISR
				ORG	0x30
INIT:			MOV	IE, #0x81			
				MOV	SP, #0x31
				SETB	IT0					
				SETB	RS0				
				MOV	R0, #0
				MOV	R1, #0
				MOV	R2, #0
				CLR	RS0					
				SETB	0x00			
			
MAIN:			CLR	RS0					
				MOV	R0, #0				
				MOV	R1, #4				
				MOV	R2, #0xF7			
SCAN:			SETB	P3.3			
				MOV	A, R2				
				MOV	P2, A				
				JNB	P3.3, EQUAL			
				JNB	P2.7, KEY_IN		
				INC	R0					
				JNB	P2.6, KEY_IN		
				INC	R0					
				JNB	P2.5, KEY_IN		
				INC	R0					
				JNB	P2.4, KEY_IN		
				INC	R0					
				RR	A					
				MOV	R2, A				
				DJNZ	R1, SCAN		
KEY_OUT:		CALL	DISPLAY			
			SJMP	MAIN
				
KEY_IN:			CALL	DEBOUNCE		
				MOV	DPTR, #KB_table		
				MOV	A, R0				
				MOVC	A, @A+DPTR		
				CJNE	A, #0x0A, NEXT1	
				SJMP	OP_IN			
NEXT1:			CJNE	A, #0x0B, NEXT2	
				SJMP	OP_IN			
NEXT2:			CJNE	A, #0x0C, NEXT3	
				SJMP	OP_IN			
NEXT3:			CJNE	A, #0x0D, NEXT4	
				SJMP	OP_IN			
NEXT4:			CJNE	A, #0x0F, NEXT5	
				SJMP	L_BRACKETS		
NEXT5:			CJNE	A, #0x0E, NEXT6	
				SJMP	R_BRACKETS		
NEXT6:			SJMP	SAVE_IN		

L_BRACKETS:		SETB	RS0				
				MOV	R0, #0			
				MOV	R1, #0			
				MOV	R2, #0			
				JMP	KEY_OUT			

R_BRACKETS:		SETB	RS0			
				POP	0x0E	;R6		
				POP	0x0D	;R5		
				POP	0x0C	;R4		
				CALL	CAL			
				PUSH	0x0B	;R3	
				MOV	R0, #0			
				MOV	R1, #0			
				MOV	R2, #0			
				JMP	KEY_OUT			

OP_IN:			SETB	RS0			
				PUSH	0xE0	;A	
				CLR	0x00			
				MOV	R0, #0			
				MOV	R1, #0			
				MOV	R2, #0			
				JMP	KEY_OUT		

EQUAL:			CALL	DEBOUNCE							
				SETB	RS0					
				MOV	A, SP					
				CJNE	A, #0x31, POP_CAL	
				POP	0x0B					
				CALL	SET_DEGITS			
				JMP	KEY_OUT		

SAVE_IN:		SETB	RS0								
				MOV	R7, A				
				MOV	A, R1				
				MOV	R0, A				
				MOV	A, R2				
				MOV	R1, A				
				MOV	A, R7				
				MOV	R2, A				
				MOV	A, R0				
				MOV	B, #100				
				MUL	AB					
				MOV	R3, A				
				MOV	A, R1				
				MOV	B, #10				
				MUL	AB					
				MOV	B, R3				
				ADD	A, B				
				MOV	B, R2				
				ADD	A, B				
				MOV	R3, A				
				JNB	0x00, SKIP_REFRESH	
				MOV	A, SP				
				SUBB	A, #0x01		
				MOV	SP, A				
				
SKIP_REFRESH:	PUSH	0x0B	//BANK1 R3	
				SETB	0x00		
				JMP	KEY_OUT			

POP_CAL:		POP	0x0E			
				POP	0x0D			
				POP	0x0C			
				CALL	CAL			
				PUSH	0x0B		
				JMP	KEY_OUT			
				
CAL:			MOV	A, R4					
				MOV	B, R6					
				CJNE	R5, #0x0A, SUB_CAL
				ADD	A, B				
				MOV	R3, A						
				CALL	SET_DEGITS			
				RET			       			
SUB_CAL:		CJNE	R5, #0x0B, MUL_CAL
				SUBB	A, B				
				MOV	R3, A					
				CALL	SET_DEGITS			
				RET							
MUL_CAL:		CJNE	R5, #0x0C, DIV_CAL
				MUL	AB						
				MOV	R3, A					
				CALL	SET_DEGITS			
				RET							
DIV_CAL:		DIV	AB						
				MOV	R3, A					
				CALL	SET_DEGITS			
				RET							

DEBOUNCE:		MOV	R5, #3					
DEL_100_MS:		MOV	R6, #200				
DEL_500_US:		MOV	R7, #250				
				DJNZ	R7, $				
				DJNZ 	R6, DEL_500_US 		
				DJNZ 	R5, DEL_100_MS 		
				RET 						
				
DISPLAY:		MOV	DPTR, #DP_table		
				SETB	RS0				
				CLR	P0.1 				
				MOV	A, R0				
				MOVC	A, @A+DPTR		
				MOV	P1, A				
				CALL	DEL_300_US		
				SETB	P0.1			
				CLR	P0.2				
				MOV	A, R1				
				MOVC	A, @A+DPTR		
				MOV	P1, A				
				CALL	DEL_300_US		
				SETB	P0.2			
				CLR	P0.3				
				MOV	A, R2				
				MOVC	A, @A+DPTR		
				MOV	P1, A				
				CALL	DEL_300_US		
				SETB	P0.3	
				RET 					

DEL_300_US:		MOV	R7, #164			
			DJNZ	R7, $
			RET

INT0_ISR:		SETB	RS0					
COUNTDOWN:		CALL	SET_DEGITS			
				MOV	R5, #10					
				CALL	SHOW				
				DJNZ	R3, COUNTDOWN		
				CALL	SET_DEGITS			
				RETI						
				
SET_DEGITS:		MOV	A, R3		
				MOV	B, #10		
				DIV	AB			
				MOV	R2, B		
				MOV	B, #10		
				DIV	AB			
				MOV	R1, B		
				MOV	R0, A		
				RET				

SHOW:			MOV	R6, #100	
SHOW1:			CALL	DISPLAY
			DJNZ	R6, SHOW1
			DJNZ	R5, SHOW
			RET

KB_table:		DB		01H		
				DB		02H		
				DB		03H		
				DB		0AH		
				DB		04H		
				DB		05H		
				DB		06H		
				DB		0BH		
				DB		07H		
				DB		08H		
				DB		09H		
				DB		0CH		
				DB		0FH		
				DB		00H		
				DB		0EH		
				DB		0DH		
				
DP_table:		DB		11000000B //0
				DB		11111001B
				DB		10100100B
				DB		10110000B
				DB		10011001B 
				DB		10010010B 
				DB		10000010B
				DB		11011000B
				DB		10000000B
				DB		10010000B
					
				END