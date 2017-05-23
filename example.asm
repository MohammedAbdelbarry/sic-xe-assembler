PROG12   START   1000
P        JSUB    COMPU
FIN2     J       FIN2
COMPU    LDX     ZERO
LOOP     TD      INPUT
         JEQ     LOOP
	     RD      INPUT
         COMP    FOUR
    	 JEQ     FIN
    	 STCH    BUFFER,X
    	 TIX     HUND
    	 JLT     LOOP
FIN	     STX     LENGTH
         RSUB 		 
ZERO     WORD    0
FOUR     WORD    4
HUND     WORD    100
INPUT    BYTE    X'F3'
BUFFER   RESB    100
LENGTH   RESW    1
         END     1000