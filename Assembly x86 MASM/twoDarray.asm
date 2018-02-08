;Daniel Navarro
; 4/13/16
; Visual Studio 2015
;Better Hash Fn
INCLUDE Irvine32.inc

.data
prompt BYTE "Two Dimensional Array", 0
Parray SBYTE 01h, 03h, 05h
rowsize = ($-Parray)
	   SBYTE 1h, 1h, -2h
	   SBYTE 4h, -3h, 2h

Qarray SBYTE 3h, 5h, 7h
	   SBYTE 4h, -3h, 9h
	   SBYTE -1h, 2h, -6h
Rarray SBYTE 9 DUP(?)

row_index DWORD 0h
column_index DWORD 0h              
Sum_of_products SDWORD 0h
.code
main proc
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	mov ebp,0						;ebp is index for product array R

NextRow:
	mov ecx,OFFSET Parray
	add ecx,eax
	mov ebx,OFFSET Qarray
	add ebx,column_index
NextColumn:
	xor eax,eax
	mov esi, 0
	mov Sum_of_products,0
Traverse:
	mov al,[ecx+esi]				;al is multiplicand and dl is multiplier
	mov dl,[ebx]
	IMUL dl							
	mov edi,Sum_of_products
	add di,ax
	mov Sum_of_products, edi		;add it to the sum

	inc esi							;increment P row index
	add ebx, rowsize             	;increment to the next index in Q column
	cmp esi,rowsize					;if esi is passed the maximum index of 2 continue
	jne Traverse					;if not keep traversing

	mov esi,OFFSET Rarray			;grab the OFFSET of product 2d array R
	add esi,ebp						;go to the nth index of R array
	add ebp,1						;inc index
	mov ebx,Sum_of_products			
	mov [esi], ebx					;store sum into R array
	
	mov eax, column_index			;increment column_index by 1
	add eax,1
	mov column_index,eax

	mov ebx,OFFSET Qarray			;go to next address of Qarray
	add ebx,column_index

	mov esi,rowsize					;check to see if column_index has reached its max index
	cmp esi,column_index
	jne NextColumn
	
	mov esi,0						;resest column index
	mov column_index, esi
	mov eax, row_index				;increment row_index by 1
	add eax,1
	mov row_index,eax

	mov eax,row_index				;rowsize*row_index = nextrow in the eax register
	mov esi,rowsize
	MUL esi

	cmp ebp,LENGTHOF Rarray			; check index to see if we are at the end of Rarray
	jne NextRow

	mov esi,OFFSET Rarray
	mov ecx,LENGTHOF Rarray
	mov ebx,TYPE Rarray

	mov edx,OFFSET prompt
	call WriteString
	call Crlf
	call DumpTwoDArray				;Tried to make my own DumpMem, but specifically for this array
	call	WaitMsg
	exit
main ENDP
DumpTwoDArray PROC
	xor eax,eax
	mov edx,0
Array:
continue:

	mov al,[esi]				
	shr al,4					;since I've been storing the data by 8-bit register
	cmp eax,0					;I have the check if there's a sign bit since
	jge skip					;WriteInt writes the whole 32-bit I had to adjust to that
	sub eax,0FFFFFF00h
skip:
	cmp al,0Fh
	je signextend
	mov al,[esi]				;if the data is a non-negative then restore data before shr
	call WriteInt
	cmp edx,edx					;Dummy register to skip sign extend
	je no_extend
signextend:
	mov al,[esi]
	movsx eax,al
	call WriteInt
no_extend:
	mov al,' '
	call WriteChar
	add esi,TYPE Rarray
	add edx,1
	cmp edx,3
	je nextline
	loop Array
nextline:
	sub ecx,1
	call Crlf
	mov edx,0
	cmp ecx,0
	jne continue
	ret
DumpTwoDArray ENDP
END main