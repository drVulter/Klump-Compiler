global _main
extern _printf

section .text
_main:
;; Print statement
push ebp
mov ebp, esp
push dword 3
push dword str
call _printf
add esp, 8
mov esp, ebp
pop ebp
;; Stack frame torn down.
;; Exit
push dword 0
mov eax, 0x1
sub esp, 4
int 0x80

section .bss

section .data
str: db "%d", 10, 0
