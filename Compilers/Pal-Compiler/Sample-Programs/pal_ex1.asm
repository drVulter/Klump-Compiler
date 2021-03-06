global _main
extern _printf

section .text
_main:
;; Emitting a number.
push 3
;; Emitting a number.
push 4
;; Emitting an addop.
pop ebx
pop eax
add eax, ebx
push eax
;; Emitting a number.
push 12
;; Emitting an addop.
pop ebx
pop eax
sub eax, ebx
push eax
;; Emitting an assignment.
pop eax
mov [A], eax
;; Emitting a number.
push 12
;; Emitting a number.
push 5
;; Emitting a mulop.
mov edx, 0
pop ebx
pop eax
cdq
idiv ebx
push eax
;; Emitting an assignment.
pop eax
mov [B], eax
;; Print statement
push ebp
mov ebp, esp
push dword [A]
push dword str
call _printf
add esp, 8
mov esp, ebp
pop ebp
;; Stack frame torn down.
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
