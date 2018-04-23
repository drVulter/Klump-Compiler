  global _main
  extern _printf

  section .text
_main:
  fld qword [x]
  fld qword [y]
  fadd
  fstp qword [result]
  mov eax, [result]
  mov ebx, [result+4]
  	push	dword [result+4] 		; push temp as 2 32-bit words
	push	dword [result]
	        push    dword str		; address of format string
	        call    _printf			; Call C function
	        add     esp, 12			; pop stack 3*4 bytes
  jmp _exit
_exit:  
	;; Exit
	push dword 0
	mov eax, 0x1
	sub esp, 4
	int 0x80

  section .bss
result:  resb 8
  section .data
x:  dq 1.5
y:  dq 4.6
str: db "%f", 10, 0
