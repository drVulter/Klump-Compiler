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
	push dword [_L_0_] 	 ; Emitting a variable
;; Assignment
	pop dword eax 
	mov [ebp-4], eax 	 ; make the move
;; Call statement
	call _ENTER_NUMGET 
