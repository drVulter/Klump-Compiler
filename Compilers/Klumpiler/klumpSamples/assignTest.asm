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
	fld qword [_L_0_] 	 ; Emitting a real variable
;; Assignment
	fstp qword [Y]
afterAss: 
	add esp, -4 	 ; Stack fix
	fld qword [Y] 	 ; Emitting a real variable
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
	add esp, 12 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call

section .bss
	_TEMP_REAL_: resb 8 	 ; Temporary storage for reals
	M: resb 4
	Y: resb 8
	_TEMP_INT_: resb 4

section .data
	_intStr: db "%d", 0
	_realStr: db "%f", 0
	_strStr: db "%s", 0
	_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
	_L_0_: dq 12.4
