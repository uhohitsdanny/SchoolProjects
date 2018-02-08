; Daniel Navarro
; 2/23/16
; Program uses indexed addressing that reverses the elements of the array

INCLUDE Irvine32.inc


.data
myArray WORD 1, 2, 3, 4, 5

.code
main proc
	mov ax,myArray
	mov bx,[myArray + 2]
	     

	call DumpRegs
	call	WaitMsg
	exit
main ENDP
END main

