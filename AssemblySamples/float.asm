  global _main
  extern _printf

  section .text
_main:
  push dword [i]
  pop dword [integer]
  fild dword [integer]
  fld qword [y]
  fdiv 
  fstp qword [result]
  mov eax, [result]
  mov ebx, [result+4]
	push	dword [result+4]
  push dword [result]
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
integer: resb 4
result:  resb 8
r_temp:  resb 8
intres: resb 4
tempLo: resb 4
tempHi:  resb 4
  section .data
x:  dq 1.5
y:  dq -6.6
i:  dd 5                        
str: db "%f", 10, 0
