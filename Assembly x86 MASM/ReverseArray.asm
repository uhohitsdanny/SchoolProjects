
;method 2

; Daniel Navarro
; 2/23/16
; Program uses indexed addressing that reverses the elements of the array

INCLUDE Irvine32.inc
.data
dwarray DWORD 3,5,7,9,13,15,17,19
count DWORD ?
.code
main proc
	mov esi,OFFSET dwarray
	mov edx,SIZEOF dwarray
	sub edx,TYPE dwarray		
;end pointer SIZEOF equivalent to LENGTHOF * TYPE which would be 32,
		;remember length-1 to get last index of array?, do 32 - TYPE which is 32 - 4 = 28
	mov edi,0		;beginning pointer
	mov ecx,LENGTHOF dwarray/2		;counter half of length

L1:
	mov eax,[esi + edi]		;swapping here
	mov ebx,[esi + edx]
	mov [esi+edi],ebx
	mov [esi+edx],eax	

	add edi,TYPE dwarray
	sub edx,TYPE dwarray
	loop L1		;loop always depends on ECX register


	mov esi, OFFSET dwarray
	mov ecx, LENGTHOF dwarray
	mov ebx, TYPE dwarray
	call	DumpMem

	call DumpRegs
	call	WaitMsg
	exit
main ENDP
END main

