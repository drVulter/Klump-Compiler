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
	add esp, -4 	 ; Stack fix
	push dword _L_0_ 	 ; Emitting a STRING var
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
	push dword [_L_1_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp+4], eax 	 ; make the move
;; Call statement
	call _ENTER_PRINTER
_EXIT_MAIN:   	 ; End of MAIN
	add esp, 12 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call
_ENTER_PRINTER:   	 ; Begin PRINTER
  push ebp
	mov ebp, esp 	 ; new base
	sub esp, 12 	 ; Reserve memory for local variables
		add esp, -4 	 ; Stack fix
	push dword 12 	 ; Emitting a STRING var
	;; Writing a STRING
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
_EXIT_PRINTER:   	 ; End of PRINTER
	add esp, 12 	 ; Deallocate local memory
	mov esp, ebp
prePop:
  pop ebp
preRet: nop
	ret  

section .bss
	_TEMP_REAL_: resb 8 	 ; Temporary storage for reals
	_TEMP_INT_: resb 4

section .data
	_intStr: db "%d", 0
	_realStr: db "%f", 0
	_strStr: db "%s", 0
_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_L_3_: db  'hello', 0
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
	_L_0_: db 'check', 0
.len: equ $ - _L_0_ 	 ; Length in bytes
	_L_1_: dd 4
