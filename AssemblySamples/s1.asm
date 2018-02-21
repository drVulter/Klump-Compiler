  ;; Example assembly program
  ;; Demonstrates code that might need to be generated for a PAL program
  ;; 		nasm -fmacho32 s1.asm && 	gcc -arch i386 -o s1 s1.o && ./s1
global _main
extern _printf 

  section .bss
  ;; x : int;
x:  resb 4
  ;; y : int;
y:  resb 4

  section .data
str:  db "%d", 10, 0               ; will print the number followed by a newline

  section .text
  global _main
_main: 
  ;; x := 7
  push 7
  pop eax
  mov [x], eax
  ;; y := x + x + 12
  push dword [x]
  push dword [x]
  push 12
  xor eax, eax                  ; clear eax
  pop ebx
  add eax, ebx                  ; eax <- 0 + 7
  pop ebx
  add eax, ebx                  ; eax <- 7 + x
  pop ebx
  add eax, ebx                  ; eax <- (7 + x) + x
  mov [y], eax                  ; do the assignment i.e. y := x + x + 7
  ;; y := 5 * x + 7
  ;; first 5*x mulOp
  push 5
  push dword [x]
  pop ebx                       ; ebx <- x
  pop eax                       ; eax <- 5
  mul ebx                       ; eax <- 5 * x
  push eax
  ;;  now 7
  push 7
  ;;  now addOp
  pop ebx                       ; ebx <- 7 (term2)
  pop eax                       ; eax <- 5*x (term 1)
  add eax, ebx                  ; eax <- 5*x + 7
  push eax                      ; save for later
  ;; now actual assignment
  pop eax
  mov [y], eax                  ; y <- 5*x
  ;; writeln(y)
  push ebp                      ; setup STACK FRAME
  mov ebp, esp
  push dword [y]
  push dword str
  call _printf
  add esp, 8                    ; pushed two bytes
  mov esp, ebp                  ; take down stack frame
  pop ebp                       ; puts original bp back into ebp

  ;; Exit
	push dword 0 		; exit status
	mov eax, 0x1 		; syscall number for exit, return 0
	sub esp, 4 		; extra space on stack
	int 0x80 		; make the call, no need to clear stack

