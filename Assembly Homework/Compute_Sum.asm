global sum

segment .text                                                

sum:                                                      


push       rbp                                               
mov        rbp, rsp                                          
;=========== Back up incoming parameters ===================================================================================================================================

mov        r14, rdi                                          ;Make a copy of the pointer to the incoming array
mov        r15, rsi                                          ;Make a second copy of the number elements in the array

;=========== Set up registers for the loop that follows ====================================================================================================================

mov qword  rcx,0                                               ;The loop counter is initialized to zero
push qword 0                                                 ;Push 64 zero bits on the stack
movsd      xmm8, [rsp]                                       ;Zero out the accumulating register
pop        rax                                               ;Reverse the previous push

;===== Begin loop that will sum all numbers in the array ===================================================================================================================

begin_loop:
cmp        rcx, r15                                          ;Determine if the loop should continue or exit
jge        end_loop                                          ;Exit from loop
mov        r8, [r14]                                         ;Copy one number from the array to a general purpose register
push       r8                                                ;Put that number on top of the stack
movsd      xmm9, [rsp]                                       ;Copy that same floating point number to a 64-bit floating point register
pop        rax                                               ;Return the stack to the state it held before the recent push
addsd      xmm8, xmm9                                        ;Add the floating point number to the accumulator
inc        rdx                                               ;Increment the loop counter
add        r14, 8                                            ;Advance the pointer to the next position in the array
jmp        begin_loop                                        ;Continue executing at the beginning of the loop
end_loop:                                                    ;A marker for the lower boundary of the loop

;===== The loop has finished.  Prepare to exit from this function ==========================================================================================================

movsd      xmm0, xmm8                                        ;Copy the accumulated sum to the register designated for return values
pop        rbp                                               ;Resort to rbp the value it had in the function that called this assembly function.
ret
