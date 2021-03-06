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
	sub esp, 60 	 ; Reserve memory for local variables
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; While statement
_L_1_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_3_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_5_ 	 ; make the jump
_L_4_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_6_ 	 ; move on
_L_5_: nop  
	push 1 	 ; result = TRUE
	jmp _L_6_ 
_L_6_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_2_ 	 ; not true so ELSE
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp - 44] 
	pop eax 	 ; get index
	mov ebx, 4 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	push dword [_L_7_] 	 ; Emitting a variable
	push dword [ebp - 4] 	 ; Emitting a variable
;; Emitting a mulop (*)
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	mul ebx 	 ; Perform operation (like a surgeon)
	push eax 	 ; PIOTFS
;; Assignment
	pop dword eax 
	mov [esi], eax 	 ; make the move
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	jmp _L_1_ 	 ; go again
_L_2_: nop  
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; While statement
_L_9_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [SIZE] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_12_ 	 ; make the jump
_L_11_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_13_ 	 ; move on
_L_12_: nop  
	push 1 	 ; result = TRUE
	jmp _L_13_ 
_L_13_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_10_ 	 ; not true so ELSE
	add esp, -4 	 ; Stack fix
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp - 44] 
	pop eax 	 ; get index
	mov ebx, 4 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	push dword [esi] 	 ; push value to stack
;; Writing an INT
	push dword _intStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
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
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	jmp _L_9_ 	 ; go again
_L_10_: nop  
;; Pushing array element onto the stack
	lea esi, [ebp - 44]
  push dword 0
	pop eax 	 ; get index
	mov ebx, 4 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	push dword esi 	 ; push value to stack
;; Call statement
	call _ENTER_FUNC 
	add esp, 4 
	add esp, -4 	 ; Stack fix
	lea eax, [_L_14_] 
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
	add esp, 60 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call
_ENTER_FUNC:   	 ; Begin FUNC
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 56 	 ; Reserve memory for local variables
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; While statement
_L_15_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_3_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_18_ 	 ; make the jump
_L_17_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_19_ 	 ; move on
_L_18_: nop  
	push 1 	 ; result = TRUE
	jmp _L_19_ 
_L_19_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_16_ 	 ; not true so ELSE
	add esp, -4 	 ; Stack fix
	push dword [ebp - 4] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp + 28] 
	pop eax 	 ; get index
	mov ebx, 4 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	push dword [esi] 	 ; push value to stack
;; Writing an INT
	push dword _intStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
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
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	jmp _L_15_ 	 ; go again
_L_16_: nop  
_EXIT_FUNC:   	 ; End of FUNC
	add esp, 60 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	ret  

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
SIZE: dd 10 
_L_14_: db 'check', 0 
_L_0_: dd 0 
_L_8_: dd 1 
_L_3_: dd 10 
_L_7_: dd 2 
