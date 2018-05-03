;; This was made by a machine!

	global _main  	 ; Entry point
	extern _printf  	 ; Output
	extern _fflush  	 ; Flush buffers to stdout
	extern _scanf

;; TEXT Section
	section .text
_main:   	 ; Begin MAIN
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 92 	 ; Reserve memory for local variables
	add esp, -4
	push dword NUM ; push int
	push dword _int_in_
	call _scanf
	add esp, 12
	add esp, -4
	push Y
	push dword _real_in_
	call _scanf
	add esp, 12
	push dword [Y+4]
	push dword [Y]
	push dword _realStr
	call _printf
	add esp,12
;; Now FLUSH!
	sub esp, 8
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
	add esp, -4
	push dword [NUM]
	push dword _intStr
	call _printf
	add esp, 12
;; Now FLUSH!
	sub esp, 8
	push dword 0 	 ; flush all buffers to stdout
	call _fflush 	 ; make the call
	add esp, 12 	 ; Clean up stack
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
_int_in_: db "%i", 0
_real_in_: db "%lf", 0
	_intStr: db "%d", 0
	_realStr: db "%f", 0
	_strStr: db "%s", 0
	_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
	I: dd 12
	R: dq 5.6
	R2: dq 6.5
	S: db 'hello world', 0
