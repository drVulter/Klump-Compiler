  global _main
  extern _printf

  section .bss

x: resb 4

y:  resb 4

  section .data
intStr:   db "%d", 10, 0

  section .text
  global _main

_main:
  push 8
  pop eax
  mov [x], eax
  push dword [x]


  	;; Exit
	push dword 0 		; exit status
	mov eax, 0x1 		; syscall number for exit, return 0
	sub esp, 4 		; extra space on stack
	int 0x80 		; make the call, no need to clear stack
