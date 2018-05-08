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
;; Call statement
	call _ENTER_FUNC 
;; Assignment
	pop dword esi 	 ; Source
	lea edi, [ebp-8] 	 ; Destination
	mov ecx, 1000 	 ; mov up to 1000 characters
	cld  
	rep movsb 	 ; Do the move
	add esp, -4 	 ; Stack fix
	lea eax, [ebp - 8] 
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
	add esp, 28 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	push dword 0 
	mov eax, 0x1 
	sub esp, 4 
	int 0x80 	 ; Make exit call
_ENTER_FUNC:   	 ; Begin FUNC
	push ebp 	 ; Save base pointer
	mov ebp, esp 	 ; new base
	sub esp, 24 	 ; Reserve memory for local variables
	lea eax, [_L_0_] 
	push  eax 	 ; Emitting a STRING var
  ;; Assignment
preAssign:  
	pop dword esi 	 ; Source
	lea edi, [ebp-4] 	 ; Destination
	mov ecx, 1000 	 ; mov up to 1000 characters
	cld  
	rep movsb 	 ; Do the move
	lea eax, [ebp - 4]
postAssign: 
	push  eax 	 ; Emitting a STRING var
;; Return statement
	pop eax 
	jmp _EXIT_FUNC 
_EXIT_FUNC:   	 ; End of FUNC
	add esp, 28 	 ; Deallocate local memory
	mov esp, ebp 
	pop ebp 	 ; Fix stack
	ret  

	section .bss 
	_TEMP_REAL_: resb 8 	 ; Temporary storage for reals
H: resb 4 
_TEMP_INT_: resb 4 

	section .data 
_intStr: db "%d", 0 
_realStr: db "%f", 0 
_strStr: db "%s", 0 
_NEW_LINE_: db 10, 0 	 ; Just a carriage return
_NEGATIVE_: dq -1.0  	 ; Just negative one
_INT_IN_: db "%d", 0  
_REAL_IN_: db "%lf", 0  
_L_0_: db 'world', 0 
