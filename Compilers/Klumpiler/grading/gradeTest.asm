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
	sub esp, 844 	 ; Reserve memory for local variables
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
	add esp, -4 	 ; Pad the stack
	push dword ACTUALSIZE 	 ; put variable address on stack
	push dword _INT_IN_ 	 ; temp storage
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_0_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_0_ 	 ; gobble gobble gobble!
	push dword [_L_1_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
;; While statement
_L_2_: nop  
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [ACTUALSIZE] 	 ; Emitting a variable
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
	jne _L_3_ 	 ; not true so ELSE
	add esp, -4 	 ; Stack fix
	lea eax, [_L_7_] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
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
	lea eax, [_L_9_] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp - 400] 
	pop eax 	 ; get index
	mov ebx, 4 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	add esp, -4 	 ; Stack fix
	push dword esi 	 ; putting addresss on top of stack
	push dword _INT_IN_ 
	call _scanf 	 ; Make the call
	add esp, 12 	 ; Fix the stack
;; Readln!
_L_10_:   	 ; read line loop
	add esp, -12 
	call _getchar 
	add esp, 12 
	cmp eax, 0xa 	 ; check for carriage return
	jne _L_10_ 	 ; gobble gobble gobble!
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
	jmp _L_2_ 	 ; go again
_L_3_: nop  
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	push dword [_L_1_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
;; While statement
_L_11_: nop  
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [ACTUALSIZE] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_14_ 	 ; make the jump
_L_13_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_15_ 	 ; move on
_L_14_: nop  
	push 1 	 ; result = TRUE
	jmp _L_15_ 
_L_15_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_12_ 	 ; not true so ELSE
	add esp, -4 	 ; Stack fix
	lea eax, [_L_7_] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
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
	lea eax, [_L_16_] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp - 400] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
	jmp _L_11_ 	 ; go again
_L_12_: nop  
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	lea edi, [ebp - 800] 	 ; Loading address to DESTINATION
	lea esi, [ebp - 400] 	 ; loading base array address
;; Copying an array...
	mov ecx, 100 	 ; Counter
	mov ebx, 4 	 ; size of each element
_L_17_: nop  
	push dword [esi] 	 ; load source data
	pop dword [edi] 	 ; into dest.
	add esi, ebx 	 ; Increment addresses
	add edi, ebx 	 ; Increment addresses
	loop _L_17_ 
	push dword [_L_1_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
;; While statement
_L_18_: nop  
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [ACTUALSIZE] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_21_ 	 ; make the jump
_L_20_: nop  	 ; first since default
	push 0 	 ; result = FALSE
	jmp _L_22_ 	 ; move on
_L_21_: nop  
	push 1 	 ; result = TRUE
	jmp _L_22_ 
_L_22_:   
;; Check for if statement
	pop eax 	 ; get truth value
	cmp eax, 1 
	jne _L_19_ 	 ; not true so ELSE
	add esp, -4 	 ; Stack fix
	lea eax, [_L_23_] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
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
	lea eax, [_L_16_] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp - 800] 
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
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
	jmp _L_18_ 	 ; go again
_L_19_: nop  
;; Printing a linebreak
	push ebp 
	mov ebp, esp 
	push dword _NEW_LINE_ 	 ; pushing line break
	push dword _strStr 
	call _printf 	 ; Make the call
	add esp, 8 	 ; Fix stack
	mov esp, ebp 
	pop ebp 	 ; Stack frame restored
	push dword [_L_1_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
	fld qword [_L_24_] 	 ; Emitting a real variable
;; Assignment
	fstp qword [ebp - 808] 
;; While statement
_L_25_: nop  
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [ACTUALSIZE] 	 ; Emitting a variable
;; Comparison
	pop ebx 
	pop eax 
	cmp eax, ebx 	 ; make comparison
	jl _L_28_ 	 ; make the jump
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
	fld qword [ebp - 808] 	 ; Emitting a real variable
	push dword [ebp - 820] 	 ; Emitting a variable
;; Pushing array element onto the stack
	lea esi, [ebp - 400] 
	pop eax 	 ; get index
	mov ebx, 4 
	mul ebx 	 ; Adjust for size
	add esi, eax 	 ; Get element at corrent index
	push dword [esi] 	 ; push value to stack
	pop dword [_TEMP_INT_] 	 ; put integer operand into temporary storage
	fild dword [_TEMP_INT_] 	 ; then put that value onto floating point stack
;; Emitting an addop (+)
	fadd  	 ; Addop, result on floating point stack
;; Assignment
	fstp qword [ebp - 808] 
	push dword [ebp - 820] 	 ; Emitting a variable
	push dword [_L_8_] 	 ; Emitting a variable
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
;; Assignment
	pop dword eax 
	mov [ebp - 820], eax 	 ; make the move
	jmp _L_25_ 	 ; go again
_L_26_: nop  
	fld qword [ebp - 808] 	 ; Emitting a real variable
	push dword [ACTUALSIZE] 	 ; Emitting a variable
	pop dword [_TEMP_INT_] 	 ; put integer operand into temporary storage
	fild dword [_TEMP_INT_] 	 ; then put that value onto floating point stack
;; Emitting a mulop (/)
	fdiv  	 ; result stored in floating point stack
;; Assignment
	fstp qword [ebp - 816] 
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
	add esp, -4 	 ; Stack fix
	push dword [ACTUALSIZE] 	 ; Emitting a variable
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
	lea eax, [_L_31_] 
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
	fld qword [ebp - 816] 	 ; Emitting a real variable
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
_EXIT_MAIN:   	 ; End of MAIN
	add esp, 844 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call

	section .bss 
	_TEMP_REAL_: resb 8 	 ; Temporary storage for reals
ACTUALSIZE: resb 4 
_TEMP_INT_: resb 4 

	section .data 
_intStr: db "%d", 0 
_realStr: db "%f", 0 
_strStr: db "%s", 0 
_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
MAXSIZE: dd 100 
PROMPT: db 'enter the number of actual elements (1 <= n <= 100)', 0 
_L_31_: db ' is ', 0 
_L_16_: db '] = ', 0 
_L_9_: db ']: ', 0 
_L_7_: db 'data [', 0 
_L_23_: db 'duplicate [', 0 
_L_30_: db 'the mean for the sample of size ', 0 
_L_1_: dd 0 
_L_24_: dq 0.0 
_L_8_: dd 1 
