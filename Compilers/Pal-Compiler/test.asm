global _main
extern _printf
section .text
_main:
push 3
pop eax
mov [A], eax
push 5
push dword [A]
pop ebx
pop eax
mul ebx
push eax
push 2
pop ebx
pop eax
sub eax, ebx
push eax
pop eax
mov [B], eax
push 2
pop eax
mov [C], eax
push 5
push dword [A]
pop ebx
pop eax
mul ebx
push eax
push dword [B]
push dword [C]
pop ebx
pop eax
mul ebx
push eax
push dword [A]
pop ebx
pop eax
mul ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax
push dword [C]
pop ebx
pop eax
add eax, ebx
push eax
push 12
push 3
pop ebx
pop eax
div ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
pop eax
mov [C], eax
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
;; Print statement
push ebp
mov ebp, esp
push dword [C]
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
