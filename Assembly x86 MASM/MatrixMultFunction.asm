;Daniel Navarro
; 4/13/16
; Visual Studio 2015
;Better Hash Fn
INCLUDE Irvine32.inc

.data
twodimarray BYTE 10h, 20h, 30h, 40h, 50h
rowsize = ($-twodimarray)
			BYTE 60h, 70h, 80h, 90h, 0A0h
			BYTE 0B0h, 0C0h, 0D0h, 0E0h, 0F0h
numofelements = ($-twodimarray)
row_index = 0
.code
main proc
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	mov eax,numofelements		    ;To get number of columnes I can use n elements
	mov ecx,rowsize					;divided by row size (15/5 = 3)
	div ecx
	mov row_index,eax				;row_index has the number of columns now which is 3
	sub row_index,1					;sub 1 since indexes for rows range from 0 to 2
	;xor eax,eax

	mov bl,rowsize					;bl holds the value 5 for modulus
	mov ecx,rowsize					;ecx is going to be used for loop and divisor
	div ecx							;I'm going to use modulus value as the column index
	mov esi,OFFSET twodimarray
	add esi,

	call DumpRegs
	call Crlf
	call	WaitMsg
	exit
main ENDP
END main