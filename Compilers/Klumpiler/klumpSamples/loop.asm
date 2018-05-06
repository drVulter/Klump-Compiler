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
	sub esp, 12 	 ; Reserve memory for local variables
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [I], eax 	 ; make the move
;; While statement
_L_1_: nop  
	push dword [I] 	 ; Emitting a variable
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
	push dword [_L_0_] 	 ; Emitting an integer literal
;; Assignment
	pop dword eax 
	mov [J], eax 	 ; make the move
;; While statement
_L_7_: nop  
	push dword [J] 	 ; Emitting a variable
	push dword [_L_3_] 	 ; Emitting an integer literal
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_10_ 	 ; make the jump
_L_9_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_11_ 	 ; move on
_L_10_: nop  
	push 1 	 ; result = TRUE
	jmp _L_11_ 
_L_11_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_8_ 	 ; not true so ELSE
	push dword [_L_0_] 	 ; Emitting an integer literal
;; Assignment
	pop dword eax 
	mov [K], eax 	 ; make the move
;; While statement
_L_12_: nop  
	push dword [K] 	 ; Emitting a variable
	push dword [_L_3_] 	 ; Emitting an integer literal
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_15_ 	 ; make the jump
_L_14_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_16_ 	 ; move on
_L_15_: nop  
	push 1 	 ; result = TRUE
	jmp _L_16_ 
_L_16_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_13_ 	 ; not true so ELSE
	push dword [K] 	 ; Emitting a variable
	push dword [_L_17_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [K], eax 	 ; make the move
	push dword [K] 	 ; Emitting a variable
	push dword [_L_22_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	je _L_24_ 	 ; make the jump
_L_23_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_25_ 	 ; move on
_L_24_: nop  
	push 1 	 ; result = TRUE
	jmp _L_25_ 
_L_25_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_21_ 	 ; not true so ELSE
;; Begin THEN clause
_L_20_: nop  
	jmp _L_13_ 
;; finsihed so go to done
	jmp _L_19_ 
;; Else
_L_21_: nop  
	jmp _L_19_ 
_L_19_: nop  
	add esp, -4 	 ; Stack fix
	push dword [I] 	 ; Emitting a variable
;; Writing an INT
	push dword _intStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
;; Now FLUSH!
	sub esp, 8 
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
	add esp, -4 	 ; Stack fix
	push dword [J] 	 ; Emitting a variable
;; Writing an INT
	push dword _intStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
;; Now FLUSH!
	sub esp, 8 
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
	add esp, -4 	 ; Stack fix
	push dword [K] 	 ; Emitting a variable
;; Writing an INT
	push dword _intStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
;; Now FLUSH!
	sub esp, 8 
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
	add esp, -4 	 ; Stack fix
	push dword _L_26_ 	 ; Emitting a STRING var
;; Writing a STRING
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 12 	 ; stack fixed
;; Now FLUSH!
	sub esp, 8 
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
	jmp _L_12_ 	 ; go again
_L_13_: nop  
	push dword [J] 	 ; Emitting a variable
	push dword [_L_17_] 	 ; Emitting an integer literal
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [J], eax 	 ; make the move
	jmp _L_7_ 	 ; go again
_L_8_: nop  
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	push dword [I] 	 ; Emitting a variable
	push dword [_L_17_] 	 ; Emitting an integer literal
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [I], eax 	 ; make the move
	jmp _L_1_ 	 ; go again
_L_2_: nop  
_EXIT_MAIN:   	 ; End of MAIN
	add esp, 4 	 ; Deallocate local memory
	mov ebp, esp 
	pop ebp 	 ; Fix stack
;; Exit
_exit_main:   
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call

section .bss
	_TEMP_REAL_: resb 8 	 ; Temporary storage for reals
	I: resb 4
	J: resb 4
	K: resb 4
	_TEMP_INT_: resb 4

section .data
	_intStr: db "%d", 0
	_realStr: db "%f", 0
	_strStr: db "%s", 0
	_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
	_L_26_: db ' ', 0
.len: equ $ - _L_26_ 	 ; Length in bytes
	_L_0_: dd 0
	_L_17_: dd 1
	_L_22_: dd 2
	_L_3_: dd 5
