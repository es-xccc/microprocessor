ORG 00H ; start address 00H
MOV A, #11111110B ; set A to 11111110B
LOOP: MOV P1, A ; move A to P1
CALL DELAY ; delay 0.5 sec
RL A ; rotate left
SJMP LOOP ; main loop
DELAY: MOV R0, #4 ; loop 4 times
LOOP1: MOV R1, #250 ; loop 250 times
LOOP2: MOV R2, #250 ; loop 250 times
DJNZ R2, $ ; decrement R2 until 0
DJNZ R1, LOOP2 ; decrement R1 until 0
DJNZ R0, LOOP1 ; decrement R0 until 0
RET ; return from subroutine
END ; end of program