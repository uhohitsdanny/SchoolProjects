; Shelley Pham
; 3/14/16
; Visual Studio 2013
; Program sorts array from lower to higher numbers using selection type sort

INCLUDE Irvine32.inc

WriteString PROTO


.data
str1 BYTE "Herman Smith", 0
str2 BYTE "Louie Jones", 0
str3 BYTE "Robert Sherman", 0
str4 BYTE "Barbara Goldenstein", 0
str5 BYTE "Johnny Unitas", 0
str6 BYTE "Tyler Abrams", 0
str7 BYTE "April Perkins", 0
str8 BYTE "William Jones", 0
str9 BYTE "Steve Schockley", 0
str10 BYTE "Steve Williams", 0

prompt BYTE "Total collisions: ", 0
array BYTE 11h, 11h, 11h, 11h, 11h, 11h, 11h, 11h, 11h, 11h, 11h
TABLE_SIZE = 11
collision BYTE 0

.code
hashfn PROC
	call Crlf
	mov edx,0
 	mov al,[esi+0]
	mov ecx,TABLE_SIZE
	div ecx
	mov esi,edx
	mov al,[array + esi]
	cmp al,dl
	jne Fini
	inc bl
	Fini:
	mov [array+esi],dl
	mov al,[array+esi]
	call WriteDec
	call Crlf
	ret
hashfn ENDP
main proc
	xor eax,eax
	xor ebx,ebx
	xor edx,edx
	xor ecx,ecx
	mov bl, collision
	

	mov esi,OFFSET str1	
	mov edx,OFFSET str1
	call WriteString
	call hashfn

	mov esi,OFFSET str2	
	mov edx,OFFSET str2
	call WriteString
	call hashfn

	mov esi,OFFSET str3
	mov edx,OFFSET str3
	call WriteString
	call hashfn

	mov esi,OFFSET str4	
	mov edx,OFFSET str4 
	call WriteString
	call hashfn

	mov esi,OFFSET str5	
	mov edx,OFFSET str5
	call WriteString
	call hashfn

	mov esi,OFFSET str6
	mov edx,OFFSET str6
	call WriteString	
	call hashfn

	mov esi,OFFSET str7	
	mov edx,OFFSET str7
	call WriteString
	call hashfn

	mov esi,OFFSET str8
	mov edx,OFFSET str8
	call WriteString
	call hashfn

	mov esi,OFFSET str9
	mov edx,OFFSET str9
	call WriteString
	call hashfn

	mov esi,OFFSET str10
	mov edx,OFFSET str10
	call WriteString
	call hashfn

	mov al,bl
	mov edx,OFFSET prompt
	call WriteString
	call WriteDec
	call Crlf
	call	WaitMsg
	exit
main ENDP
END main


