ORG 0 ; start from 0000H
MOV DPTR, #TABLE ; DPTR point to TABLE
MOV R5, #2
START:
		MOV R0, #1 ; initialize typed signal
		MOV R1, #4 ; set 3 rows
		MOV R2, #11110111B ; scan first row
SCAN:
		MOV A, R2 ; move R2 to A
		MOV P2, A ; input scanned signal
		JNB P2.7, KEYIN ; scan column 1
		INC R0 ; add #001H into R0
		JNB P2.6, KEYIN ; scan column 2
		INC R0 ; add #001H into R0
		JNB P2.5, KEYIN ; scan column 3
		INC R0 ; add #001H into R0
		JNB P2.4, CAL
		RR A ; next row
		MOV R2, A ; move A to R2
		DJNZ R1, SCAN ; scan 3 rows
		SJMP START ; jump to scan keypad again
KEYIN:
		CALL DEBOUNCE
		MOV A, R0
		DJNZ R5, KEYIN2
		MOV R6, A
		SJMP START
KEYIN2:	
		CALL DEBOUNCE
		MOV B, A
		SJMP START
CAL:
		JNB P2.3, PLUS
		JNB P2.2, MINUS
		JNB P2.1, DOT
		JNB P2.0, DIVIDE


PLUS:
		MOV A, R6
		ADD	A, B
		MOV	B, #10 
		DIV AB
		MOVC A, @A+DPTR
		MOV P1, A 
		CALL DELAY250
		MOV A, B
		MOVC A, @A+DPTR
		MOV P1, A 
		CALL DELAY250
		MOV R5,#2
		SJMP START
MINUS:
		MOV  A, R6
		SUBB A, B
		MOVC A, @A+DPTR 
		MOV P1, A 
		MOV R5, #2
		SJMP START
DOT:
		MOV A, R6
		MUL AB
		MOV	B, #10
		DIV AB
		MOVC A, @A+DPTR ;
		MOV P1, A
		CALL DELAY250
		MOV A, B
		MOVC A, @A+DPTR 
		MOV P1, A     
		CALL DELAY250
		MOV R5,#2;
		SJMP START
DIVIDE:
		MOV A, R6
		DIV AB
		MOVC A, @A+DPTR
		MOV P1, A 
		CALL DELAY250
		MOV  A, B
		MOVC A, @A+DPTR 
		MOV P1, A 
		MOV R5,#2
		LJMP START


DEBOUNCE:
		MOV R4, #50 ; move 50 times into R4
DE_500_us:
		MOV R3, #250 ; move 250 times into R3
		DJNZ R3, $ ; jump to itself R3 times
		DJNZ R4, DE_500_us ; delay 25ms
		RET ; return to main code
DELAY250:
		MOV R4, #250 ; move 50 times into R4
LOOP1:
		MOV R3, #250 ; move 250 times into R3
		DJNZ R3, $ ; jump to itself R3 times
		MOV R3, #250 ; move 250 times into R3
		DJNZ R3, $ ; jump to itself R3 times
		DJNZ R4, LOOP1 ; delay 25ms
		RET ; return to main code
TABLE:
		DB 00000011B ; 0
		DB 10011111B ; display "1"
		DB 00100101B ; display "2"
		DB 00001101B ; display "3"
		DB 10011001B ; display "4"
		DB 01001001B ; display "5"
		DB 01000001B ; display "6"
		DB 00011011B ; display "7"
		DB 00000001B ; display "8"
		DB 00001001B ; display "9"
END