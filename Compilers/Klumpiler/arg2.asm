;; This was made by a machine!

	global _main  	 ; Entry point
	extern _printf  	 ; Output
	extern _scanf  	 ; Input
	extern _getchar  	 ; Gobbler
	extern _fflush  	 ; Flush buffers to stdout

;; TEXT Section
	section .text  
_main:   	 ; Begin MAIN
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 28 	 ; Reserve memory for local variables
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	fld qword [_L_1_] 	 ; Emitting a real variable
;; Assignment
	fstp qword [ebp - 12] 
;; While statement
_L_2_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_4_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_6_ 	 ; make the jump
_L_5_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_7_ 	 ; move on
_L_6_: nop  
	push 1 	 ; result = TRUE
	jmp _L_7_ 
_L_7_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_3_ 	 ; not true so ELSE
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	mov esi, A 	 ; Store address of first element
	pop eax 	 ; get index
	mov ebx, 8 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	push dword [ebp - 4] 	 ; Emitting a variable
	pop dword [_TEMP_INT_] 	 ; put integer operand into temporary storage
	fild dword [_TEMP_INT_] 	 ; then put that value onto floating point stack
;; Assignment
	fstp qword [esi] 
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	mov esi, B 	 ; Store address of first element
	pop eax 	 ; get index
	mov ebx, 8 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	fld qword [_L_8_] 	 ; Emitting a real variable
;; Assignment
	fstp qword [esi] 
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_9_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	jmp _L_2_ 	 ; go again
_L_3_: nop  
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; While statement
_L_10_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_4_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_13_ 	 ; make the jump
_L_12_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_14_ 	 ; move on
_L_13_: nop  
	push 1 	 ; result = TRUE
	jmp _L_14_ 
_L_14_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_11_ 	 ; not true so ELSE
	fld qword [ebp - 12] 	 ; Emitting a real variable
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	mov esi, A 	 ; Store address of first element
	pop eax 	 ; get index
	mov ebx, 8 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	fld qword [esi] 	 ; push real array val to stack
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	mov esi, B 	 ; Store address of first element
	pop eax 	 ; get index
	mov ebx, 8 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	fld qword [esi] 	 ; push real array val to stack
;; Emitting a mulop (*)
	fmul  	 ; result stored in floating point stack
;; Emitting an addop (+)
	fadd  	 ; Addop, result on floating point stack
;; Assignment
	fstp qword [ebp - 12] 
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_9_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	jmp _L_10_ 	 ; go again
_L_11_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [_L_15_] 
	push  eax 	 ; Emitting a STRING var
;; Writing a STRING
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
;; Now FLUSH!
	sub esp, 8 
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
	add esp, -4 	 ; Stack fix
	fld qword [ebp - 12] 	 ; Emitting a real variable
;; Writing a REAL
	add esp, 4 	 ; Stack fix
	fstp qword [_TEMP_REAL_] 	 ; Put the real in temporary storage
	push dword [_TEMP_REAL_+4] 
	push dword [_TEMP_REAL_] 
	push dword _realStr 	 ; string for formatting
	call _printf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Now FLUSH!
	sub esp, 8 
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
_EXIT_MAIN:   	 ; End of MAIN
	add esp, 28 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call

	section .bss 
	_TEMP_REAL_: resb 8 	 ; Temporary storage for reals
A: resb 80 
B: resb 80 
H: resb 4 
_TEMP_INT_: resb 4 

	section .data 
_intStr: db "%d", 0 
_realStr: db "%f", 0 
_strStr: db "%s", 0 
_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
_L_15_: db 'dot product is ', 0 
_L_0_: dd 0 
_L_1_: dq 0.0 
_L_9_: dd 1 
_L_8_: dq 1.0 
_L_4_: dd 10 
