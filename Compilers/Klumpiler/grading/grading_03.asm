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
	add esp, -4 	 ; Stack fix
	lea eax, [PROMPT1] 
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
	lea eax, [ebp - 8] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _REAL_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_0_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_0_ 	 ; gobble gobble gobble!
	add esp, -4 	 ; Stack fix
	lea eax, [_L_1_] 
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
	fld qword [ebp - 8] 	 ; Emitting a real variable
;; Real arg, needs to go on normal stack
	fstp qword [_TEMP_REAL_] 
	push dword [_TEMP_REAL_+4] 
	push dword [_TEMP_REAL_] 
;; Call statement
	call _ENTER_CUBE 
	add esp, 8 
	fld qword [_TEMP_REAL_] 
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
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	add esp, -4 	 ; Stack fix
	lea eax, [PROMPT2] 
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
	lea eax, [ebp - 12] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _INT_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_2_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_2_ 	 ; gobble gobble gobble!
	add esp, -4 	 ; Stack fix
	lea eax, [_L_3_] 
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
	push dword [ebp - 12] 	 ; Emitting a variable
;; Call statement
	call _ENTER_FACTORIAL 
	add esp, 4 
	push eax 	 ; put value back on stack
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
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	add esp, -4 	 ; Stack fix
	lea eax, [PROMPT3] 
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
	lea eax, [ebp - 20] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _REAL_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Read!
	lea eax, [ebp - 28] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _REAL_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Read!
	lea eax, [ebp - 36] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
	push dword _REAL_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_4_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_4_ 	 ; gobble gobble gobble!
	fld qword [ebp - 20] 	 ; Emitting a real variable
;; Real arg, needs to go on normal stack
	fstp qword [_TEMP_REAL_] 
	push dword [_TEMP_REAL_+4] 
	push dword [_TEMP_REAL_] 
	fld qword [ebp - 28] 	 ; Emitting a real variable
;; Real arg, needs to go on normal stack
	fstp qword [_TEMP_REAL_] 
	push dword [_TEMP_REAL_+4] 
	push dword [_TEMP_REAL_] 
	fld qword [ebp - 36] 	 ; Emitting a real variable
;; Real arg, needs to go on normal stack
	fstp qword [_TEMP_REAL_] 
	push dword [_TEMP_REAL_+4] 
	push dword [_TEMP_REAL_] 
;; Call statement
	call _ENTER_SORT 
	add esp, 24 
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	add esp, -4 	 ; Stack fix
	lea eax, [_L_5_] 
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
_ENTER_CUBE:   	 ; Begin CUBE
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 16 	 ; Reserve memory for local variables
	fld qword [ebp + 8] 	 ; Emitting a real variable
	fld qword [ebp + 8] 	 ; Emitting a real variable
;; Emitting a mulop (*)
	fmul  	 ; result stored in floating point stack
	fld qword [ebp + 8] 	 ; Emitting a real variable
;; Emitting a mulop (*)
	fmul  	 ; result stored in floating point stack
;; Return statement
	fstp qword [_TEMP_REAL_] 
	jmp _EXIT_CUBE 
_EXIT_CUBE:   	 ; End of CUBE
	add esp, 28 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	ret  
_ENTER_FACTORIAL:   	 ; Begin FACTORIAL
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 20 	 ; Reserve memory for local variables
	push dword [ebp + 8] 	 ; Emitting a variable
	push dword [_L_10_] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	je _L_12_ 	 ; make the jump
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
	jne _L_9_ 	 ; not true so ELSE
;; Begin THEN clause
_L_8_: nop  
	push dword [_L_14_] 	 ; Emitting a variable
;; Return statement
	pop eax 	 ; put into register
	jmp _EXIT_FACTORIAL 
;; finsihed so go to done
	jmp _L_7_ 
;; Else
_L_9_: nop  
	push dword [ebp + 8] 	 ; Emitting a variable
	push dword [ebp + 8] 	 ; Emitting a variable
	push dword [_L_14_] 	 ; Emitting a variable
;; Emitting an addop (-)
	pop ebx 
	pop eax 
	sub eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Call statement
	call _ENTER_FACTORIAL 
	add esp, 4 
	push eax 	 ; put value back on stack
;; Emitting a mulop (*)
	pop ebx 
	pop eax 
	cdq  	 ; Deal with signs
	mul ebx 	 ; Perform operation (like a surgeon)
	push eax 	 ; PIOTFS
;; Return statement
	pop eax 	 ; put into register
	jmp _EXIT_FACTORIAL 
;; Finished with else
	jmp _L_7_ 
_L_7_: nop  
_EXIT_FACTORIAL:   	 ; End of FACTORIAL
	add esp, 28 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	ret  
_ENTER_SORT:   	 ; Begin SORT
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 16 	 ; Reserve memory for local variables
	fld qword [ebp + 24] 	 ; Emitting a real variable
	fld qword [ebp + 16] 	 ; Emitting a real variable
;; Comparison
	fcom st0, st1 	 ; compare top two elements of floating point stack
	fstsw ax 
	and eax, 0100011100000000B 
	cmp eax, 0000000100000000B 
	je _L_20_ 	 ; make the jump
_L_19_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_21_ 	 ; move on
_L_20_: nop  
	push 1 	 ; result = TRUE
	jmp _L_21_ 
_L_21_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_18_ 	 ; not true so ELSE
;; Begin THEN clause
_L_17_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [_L_22_] 
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
	fld qword [ebp + 24] 	 ; Emitting a real variable
	fstp qword [_TEMP_REAL_] 	 ; pop into temp storage
	cvtsd2si eax, [_TEMP_REAL_] 	 ; Convert the heathen
	push eax 	 ; Put back onto stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	fld qword [ebp + 16] 	 ; Emitting a real variable
;; Assignment
	fstp qword [ebp + 24] 
	push dword [ebp - 4] 	 ; Emitting a variable
	pop dword [_TEMP_INT_] 	 ; put integer operand into temporary storage
	fild dword [_TEMP_INT_] 	 ; then put that value onto floating point stack
;; Assignment
	fstp qword [ebp + 16] 
;; finsihed so go to done
	jmp _L_16_ 
;; Else
_L_18_: nop  
	jmp _L_16_ 
_L_16_: nop  
	fld qword [ebp + 16] 	 ; Emitting a real variable
	fld qword [ebp + 8] 	 ; Emitting a real variable
;; Comparison
	fcom st0, st1 	 ; compare top two elements of floating point stack
	fstsw ax 
	and eax, 0100011100000000B 
	cmp eax, 0000000100000000B 
	je _L_28_ 	 ; make the jump
_L_27_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_29_ 	 ; move on
_L_28_: nop  
	push 1 	 ; result = TRUE
	jmp _L_29_ 
_L_29_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_26_ 	 ; not true so ELSE
;; Begin THEN clause
_L_25_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [_L_30_] 
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
	fld qword [ebp + 16] 	 ; Emitting a real variable
	fstp qword [_TEMP_REAL_] 	 ; pop into temp storage
	cvtsd2si eax, [_TEMP_REAL_] 	 ; Convert the heathen
	push eax 	 ; Put back onto stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	fld qword [ebp + 8] 	 ; Emitting a real variable
;; Assignment
	fstp qword [ebp + 16] 
	push dword [ebp - 4] 	 ; Emitting a variable
	pop dword [_TEMP_INT_] 	 ; put integer operand into temporary storage
	fild dword [_TEMP_INT_] 	 ; then put that value onto floating point stack
;; Assignment
	fstp qword [ebp + 8] 
	fld qword [ebp + 24] 	 ; Emitting a real variable
	fld qword [ebp + 16] 	 ; Emitting a real variable
;; Comparison
	fcom st0, st1 	 ; compare top two elements of floating point stack
	fstsw ax 
	and eax, 0100011100000000B 
	cmp eax, 0000000100000000B 
	je _L_36_ 	 ; make the jump
_L_35_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_37_ 	 ; move on
_L_36_: nop  
	push 1 	 ; result = TRUE
	jmp _L_37_ 
_L_37_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_34_ 	 ; not true so ELSE
;; Begin THEN clause
_L_33_: nop  
	add esp, -4 	 ; Stack fix
	lea eax, [_L_38_] 
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
	fld qword [ebp + 24] 	 ; Emitting a real variable
	fstp qword [_TEMP_REAL_] 	 ; pop into temp storage
	cvtsd2si eax, [_TEMP_REAL_] 	 ; Convert the heathen
	push eax 	 ; Put back onto stack
;; Assignment
	pop dword eax 
	mov [ebp - 4], eax 	 ; make the move
	fld qword [ebp + 16] 	 ; Emitting a real variable
;; Assignment
	fstp qword [ebp + 24] 
	push dword [ebp - 4] 	 ; Emitting a variable
	pop dword [_TEMP_INT_] 	 ; put integer operand into temporary storage
	fild dword [_TEMP_INT_] 	 ; then put that value onto floating point stack
;; Assignment
	fstp qword [ebp + 16] 
;; finsihed so go to done
	jmp _L_32_ 
;; Else
_L_34_: nop  
	jmp _L_32_ 
_L_32_: nop  
;; finsihed so go to done
	jmp _L_24_ 
;; Else
_L_26_: nop  
	jmp _L_24_ 
_L_24_: nop  
	add esp, -4 	 ; Stack fix
	fld qword [ebp + 24] 	 ; Emitting a real variable
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
	add esp, -4 	 ; Stack fix
	lea eax, [_L_39_] 
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
	fld qword [ebp + 16] 	 ; Emitting a real variable
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
	add esp, -4 	 ; Stack fix
	lea eax, [_L_39_] 
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
	fld qword [ebp + 8] 	 ; Emitting a real variable
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
_EXIT_SORT:   	 ; End of SORT
	add esp, 44 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	ret  

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
PROMPT1: db 'enter x: ', 0 
PROMPT2: db 'enter n: ', 0 
PROMPT3: db 'enter three real numbers: ', 0 
_L_39_: db '  ', 0 
_L_5_: db 'all done!', 0 
_L_3_: db 'n! is ', 0 
_L_22_: db 'one', 0 
_L_38_: db 'three', 0 
_L_30_: db 'two', 0 
_L_1_: db 'x^3 is ', 0 
_L_10_: dd 0 
_L_14_: dd 1 
