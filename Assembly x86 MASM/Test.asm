; Shelley Pham
; 5/4/16
; Visual Studio 2013
; 3x3 matrix multiplication

INCLUDE Irvine32.inc


.data
int1 WORD 4
.code
main PROC
	MOV ax,int1

	call	WaitMsg
	exit
main ENDP
END main