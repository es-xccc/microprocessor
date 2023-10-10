ORG 0 ; start from 0000H
MOV DPTR, #TABLE ; DPTR point to TABLE
MOV R6, #9
START:
		MOV R0, #0 ; initialize typed signal
		MOV R1, #3 ; set 3 rows
		MOV R2, #11110111B ; scan first row
SCAN:
		MOV A, R2 ; move R2 to A
		MOV P2, A ; input scanned signal
		JNB P2.7, RE6 ; scan column 1
		INC R0 ; add #001H into R0
		JNB P2.6, RE6 ; scan column 2
		INC R0 ; add #001H into R0
		JNB P2.5, RE6 ; scan column 3
		INC R0 ; add #001H into R0
		RR A ; next row
		MOV R2, A ; move A to R2
		DJNZ R1, SCAN ; scan 3 rows
		SJMP START ; jump to scan keypad again
RE6:
		CJNE R6, #9, RE7
		MOV A, R0
		MOV R6, A
		SJMP SCAN
RE7:	
		MOV A, R0
		MOV R7, A
CAL:
		MOV P2, #11101111B
		JNB P2.3, PLUS
		JNB P2.2, MINUS
		JNB P2.1, DOT
		JNB P2.0, DIVIDE
		SJMP CAL


PLUS:
		CALL DEBOUNCE
		MOV A, R6
		MOV B, R7
		ADD A, B
		MOVC A, @A+DPTR
		MOV P1, A
		MOV R6, #9
		SJMP START
MINUS:
		CALL DEBOUNCE
		MOV A, R6
		MOV B, R7
		SUBB A, B
		MOVC A, @A+DPTR
		MOV P1, A
		MOV R6, #9
		SJMP START
DOT:
		CALL DEBOUNCE
		MOV A, R6
		MOV B, R7
		MUL AB
		MOV B, #10
		DIV AB
		MOV R6, A
		MOV A, B
		MOVC A, @A+DPTR
		MOV P1, A
		CALL DELAY250
		MOV A, R6
		MOVC A, @A+DPTR
		MOV P1, A
		MOV R6, #9
		SJMP START
DIVIDE:
		CALL DEBOUNCE
		MOV A, R6
		MOV B, R7
		DIV AB
		MOVC A, @A+DPTR
		MOV P1, A
		CALL DELAY250
		MOV A, B
		MOVC A, @A+DPTR
		MOV P1, #000H
		MOV P1, A
		MOV R6, #9
		LJMP START


DEBOUNCE: MOV R4, #50 ; move 50 times into R4
DE_500_us:
		MOV R3, #250 ; move 250 times into R3
		DJNZ R3, $ ; jump to itself R3 times
		DJNZ R4, DE_500_us ; delay 25ms
		RET ; return to main code
DELAY250:
		MOV R5, #10
		DJNZ R5, DE_500_us
		RET
TABLE:
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