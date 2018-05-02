  global _main
  extern _printf
  extern _fflush
  section .text
_main:
  push ebp
  mov ebp, esp
  sub esp, 84
  sub esp, 8
  sub esp, 4
  push dword astr
  push dword strFmt
  jmp print
print:  
  call _printf
  add esp, 12
  sub esp, 8
  push dword 0                  ; sub esp, 8 WORKS
  call _fflush
  mov esp, ebp
  pop ebp
  jmp _exit
_exit:  
	;; Exit
	push dword 0
	mov eax, 0x1
	sub esp, 4
	int 0x80

  section .bss
realTmp:  resb 8
  section .data
newLine:  db 10, 0
a:  dd 10
x:  dq 1.5
astr: db "Hello", 0
bstr:  db "world", 0
strFmt:   db "%s", 0
intFmt: db "%d", 0
realFmt:  db "%f", 0

