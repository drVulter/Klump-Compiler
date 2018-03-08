global _main
extern _printf

section .text
_main:
;; Emitting a number.
push 3
;; Emitting an assignment.
pop eax
mov [A], eax
;; Emitting a number.
push 14
;; Emitting an assignment.
pop eax
mov [C], eax
;; Emitting an identifier.
push dword [C]
;; Emitting an identifier.
push dword [A]
;; Emitting a mulop.
mov edx, 0
pop ebx
pop eax
div ebx
push eax
;; Emitting an assignment.
pop eax
mov [B], eax
;; Print statement
push ebp
mov ebp, esp
push dword [B]
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
C: resb 4
B: resb 4
A: resb 4

section .data
str: db "%d", 10, 0
