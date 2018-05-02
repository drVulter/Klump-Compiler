;; This was made by a machine!

global _main
extern _printf

;; TEXT Section
section .text
_main:   	 ; Begin MAIN
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 84 	 ; Reserve memory for local variables
;; Emitting an addop (+)
	pop ebx 
	pop eax 
	add eax, ebx 	 ; Addop!
	push eax 	 ; Storing result on stack
_EXIT_MAIN:   	 ; End of MAIN
	push ebp 	 ; Fix stack
	mov ebp, esp 
	add esp, 84 	 ; Deallocate local memory
;; Exit
_exit_main:   
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call

section .bss
	Y: resb 8
	_TEMP_INT_: resb 4

section .data
	intStr: db "%d", 10, 0
	realStr: db "%f", 10, 0
	strStr: db "%s", 10, 0
	I: dd 12
	R: dq 5.6
	R2: dq 6.5
	S: db 'hello world'
	_L_0_: dd 2
