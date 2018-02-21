;; This was made by a machine!
section .text
global _main
_main:
;; Set up stack frame
push ebp
mov ebp, esp

;; Exit
push dword 0
mov eax, 0x1
sub esp, 4
int 0x80
