;; This was made by a machine!

	global _main  	 ; Entry point
	extern _printf  	 ; Output
	extern _fflush  	 ; Flush buffers to stdout

;; TEXT Section
	section .text  
_main:   	 ; Begin MAIN
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 92 	 ; Reserve memory for local variables
	push dword  	 ; Emitting a STRING var
;; Assignment
	pop dword esi 	 ; Source
	mov edi, STR 	 ; Destination
	mov ecx, _L_0_.len 	 ; length
	cld  
	rep movsb 	 ; Do the move
	add esp, -4 	 ; Stack fix
	push dword STR 	 ; Emitting a STRING var
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
	add esp, 92 	 ; Deallocate local memory
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
	NUM: resb 4
	STR: resb 0
	Y: resb 8
	_TEMP_INT_: resb 4

section .data
	_intStr: db "%d", 0
	_realStr: db "%f", 0
	_strStr: db "%s", 0
	_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
	I: dd 12
	R: dq 5.6
	R2: dq 6.5
	S: db 'hello world', 0
	_L_0_: db 'hello world!', 0
.len: equ $ - _L_0_ 	 ; Length in bytes
