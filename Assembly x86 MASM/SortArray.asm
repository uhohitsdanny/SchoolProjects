; Daniel Navarro
; 2/23/16
; Program uses indexed addressing that reverses the elements of the array
;Visual Studios 2012

INCLUDE Irvine32.inc


.data
myArray BYTE 20, 10, 60, 5, 120, 90, 100, 7, 25, 12


.code
main PROC
	xor eax,eax		;zero out registers for cmp later.
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	xor ebp,ebp

	mov esi,OFFSET myArray		;move distance in bytes of the array into esi
	mov edx,LENGTHOF myArray	;The way I'm approaching this sort is starting from the end	
	sub edx,TYPE myArray		;and compare the max, that way I can use ecx register to traverse the list downwards
								;edx will be the starting point after each loop itll decrement once to next value to be cmp to the rest
	mov ebp,0					;This is the "index" of the array that I will save when I find a new max
	
W1:
	mov bl,[esi+edx] 			;this will be the "max" variable used in C++ code to temporarily hold the largest value as I cmp
	mov ecx,edx					;assign the loop counter
	sub ecx,TYPE myArray		;then decrement ecx so it's at the next value to cmp
FL:
	mov al,[esi+ecx]			;move the value into al
	cmp al,bl					;cmp al to bl which is the "max" variable
	jg savemax					;jump to savemax if al > bl
	jl next						;jump to next if al < bl
	je next						;or if al = bl

	swaplasttwo:				;procedure to get ready to swap last two
		mov bl,al				;If you're wondering why I didn't use savemax: to swap it's because I need to use jz for a different section
		mov ebp,ecx				
		cmp ecx,0
		jz Fini
	savemax:					;This is where we save the new max
		mov bl,al				
		mov ebp,ecx				;save the "index"
		loop FL					;Loop back to keep cmping
		cmp ecx,0				;This is to prevent going to next: for when ecx = 0 and it falls through
								;or else ecx will decrement to FFFFFFF on next: 's loop FL
		jz checklasttwo			;still need to check the last two elements
	
	next:						;next: just loops back up if value < max to keep cmping
		cmp ecx,0				;prevent from ecx going through loop when ecx is 0
		jz checklasttwo			;still need to check last two
		loop FL					;loop back to keep cmping

	checklasttwo:				;check last elements
	mov al,[esi+ecx]			
	cmp al,bl
	jg swaplasttwo				;jump to swap the last two if al > bl
		
	Fini:                           
	mov al,[esi+edx]			;this is where swapping happens
	mov bl,[esi+ebp]		
	mov [esi+edx],bl		
	mov [esi+ebp],al
	sub edx,TYPE myArray		;move target index down to next position

	cmp edx,0					;if target index is not at the end 
	jg W1						;then restart loop

	mov esi, OFFSET myArray	
	mov ecx, LENGTHOF myArray
	mov ebx, TYPE myArray

	call DumpMem

	call DumpRegs
	call	WaitMsg
	exit

main ENDP
END main
	
	
	
