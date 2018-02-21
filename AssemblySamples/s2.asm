  ;; Extremely simple assembly example
  ;; 	nasm -fmacho32 s1.asm && 	gcc -arch i386 -o s1 s1.o && ./s1
  section .text
  global _main
_main:
  ;;  set up stack frame
  push ebp
  mov ebp, esp
  ;; Exit
  push dword 0
  mov eax, 0x1
  sub esp, 4
  int 0x80
