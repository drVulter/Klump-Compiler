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
_L_0_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [PROMPT] 
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
;; Read!
	lea eax, [ebp - 4] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _INT_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_1_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_1_ 	 ; gobble gobble gobble!
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_6_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jle _L_8_ 	 ; make the jump
_L_7_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_9_ 	 ; move on
_L_8_: nop  
	push 1 	 ; result = TRUE
	jmp _L_9_ 
_L_9_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_5_ 	 ; not true so ELSE
;; Begin THEN clause
_L_4_: nop  
	jmp _L_10_ 
;; finsihed so go to done
	jmp _L_3_ 
;; Else
_L_5_: nop  
	jmp _L_3_ 
_L_3_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_15_] 	 ; Emitting a variable
;; Emitting a mulop (%)
	xor edx, edx 	 ; EDX holds remainder
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	idiv ebx 	 ; Perform operation (like a surgeon)
	push edx 	 ; PIOTFS
	push dword [_L_6_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	je _L_17_ 	 ; make the jump
_L_16_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_18_ 	 ; move on
_L_17_: nop  
	push 1 	 ; result = TRUE
	jmp _L_18_ 
_L_18_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_14_ 	 ; not true so ELSE
;; Begin THEN clause
_L_13_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [_L_19_] 
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
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_15_] 	 ; Emitting a variable
;; Emitting a mulop (/)
	xor edx, edx 	 ; EDX holds remainder
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	idiv ebx 	 ; Perform operation (like a surgeon)
	push eax 	 ; PIOTFS
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
;; finsihed so go to done
	jmp _L_12_ 
;; Else
_L_14_: nop  
	push dword [_L_6_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 8], eax 	 ; make the move
	push dword [_L_20_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 12], eax 	 ; make the move
;; While statement
_L_21_: nop  
	push dword [ebp - 12] 	 ; Emitting a variable
	push dword [ebp - 4] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jle _L_24_ 	 ; make the jump
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
	jne _L_22_ 	 ; not true so ELSE
	push dword [ebp - 8] 	 ; Emitting a variable
	push dword [ebp - 12] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 8], eax 	 ; make the move
	push dword [ebp - 12] 	 ; Emitting a variable
	push dword [_L_20_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 12], eax 	 ; make the move
	jmp _L_21_ 	 ; go again
_L_22_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [_L_26_] 
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
	push dword [ebp - 8] 	 ; Emitting a variable
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
;; Finished with else
	jmp _L_12_ 
_L_12_: nop  
	jmp _L_0_ 
_L_10_: nop  
	push dword [_L_27_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; While statement
_L_28_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_30_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jle _L_32_ 	 ; make the jump
_L_31_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_33_ 	 ; move on
_L_32_: nop  
	push 1 	 ; result = TRUE
	jmp _L_33_ 
_L_33_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_29_ 	 ; not true so ELSE
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_38_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	je _L_40_ 	 ; make the jump
_L_39_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_41_ 	 ; move on
_L_40_: nop  
	push 1 	 ; result = TRUE
	jmp _L_41_ 
_L_41_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_37_ 	 ; not true so ELSE
;; Begin THEN clause
_L_36_: nop  
	add esp, -4 	 ; Stack fix
	push dword [ebp - 4] 	 ; Emitting a variable
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
	jmp _L_29_ 
;; finsihed so go to done
	jmp _L_35_ 
;; Else
_L_37_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_20_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	jmp _L_28_ 
;; Finished with else
	jmp _L_35_ 
_L_35_: nop  
	jmp _L_28_ 	 ; go again
_L_29_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [PROMPT] 
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
;; Read!
	lea eax, [ebp - 4] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _INT_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_42_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_42_ 	 ; gobble gobble gobble!
;; While statement
_L_43_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_20_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jg _L_46_ 	 ; make the jump
_L_45_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_47_ 	 ; move on
_L_46_: nop  
	push 1 	 ; result = TRUE
	jmp _L_47_ 
_L_47_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_44_ 	 ; not true so ELSE
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_15_] 	 ; Emitting a variable
;; Emitting a mulop (%)
	xor edx, edx 	 ; EDX holds remainder
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	idiv ebx 	 ; Perform operation (like a surgeon)
	push edx 	 ; PIOTFS
	push dword [_L_6_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	je _L_53_ 	 ; make the jump
_L_52_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_54_ 	 ; move on
_L_53_: nop  
	push 1 	 ; result = TRUE
	jmp _L_54_ 
_L_54_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_51_ 	 ; not true so ELSE
;; Begin THEN clause
_L_50_: nop  
	push dword [ebp - 4] 	 ; Emitting a variable
	push dword [_L_15_] 	 ; Emitting a variable
;; Emitting a mulop (/)
	xor edx, edx 	 ; EDX holds remainder
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	idiv ebx 	 ; Perform operation (like a surgeon)
	push eax 	 ; PIOTFS
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; finsihed so go to done
	jmp _L_49_ 
;; Else
_L_51_: nop  
	push dword [_L_27_] 	 ; Emitting a variable
	push dword [ebp - 4] 	 ; Emitting a variable
;; Emitting a mulop (*)
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	mul ebx 	 ; Perform operation (like a surgeon)
	push eax 	 ; PIOTFS
	push dword [_L_20_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
;; Finished with else
	jmp _L_49_ 
_L_49_: nop  
	add esp, -4 	 ; Stack fix
	push dword [ebp - 4] 	 ; Emitting a variable
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
	jmp _L_43_ 	 ; go again
_L_44_: nop  
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
_TEMP_INT_: resb 4 

	section .data 
_intStr: db "%d", 0 
_realStr: db "%f", 0 
_strStr: db "%s", 0 
_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
PROMPT: db 'enter a positive integer (0 terminates): ', 0 
_L_19_: db 'half is ', 0 
_L_26_: db 'total is ', 0 
_L_6_: dd 0 
_L_20_: dd 1 
_L_30_: dd 100 
_L_15_: dd 2 
_L_27_: dd 3 
_L_38_: dd 7 
