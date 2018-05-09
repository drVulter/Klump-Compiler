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
	lea eax, [ebp - 4] 	 ; Use eax to store address of local var
	add esp, -4 	 ; Pad the stack
	push dword eax 	 ; put variable address on stack
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
	add esp, -4 	 ; Stack fix
	lea eax, [_L_2_] 
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
	push dword [ebp - 8] 	 ; Emitting a variable
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
_TEMP_INT_: resb 4 

	section .data 
_intStr: db "%d", 0 
_realStr: db "%f", 0 
_strStr: db "%s", 0 
_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
PI: dq 3.14159 
PROMPT1: db 'enter an integer number: ', 0 
RAD3: dq 1.41421 
_L_2_: db 'sum is', 0 
