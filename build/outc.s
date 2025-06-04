FORMAT ELF64 EXECUTABLE
entry start
start:
    mov rbx, 0
    mov rax, 0
    mov rdi, 0
    lea rsi, BYTE [tape+rbx]
    mov rdx, 1
    syscall
    inc rbx
    mov rax, 0
    mov rdi, 0
    lea rsi, BYTE [tape+rbx]
    mov rdx, 1
    syscall
    inc rbx
    mov rax, 0
    mov rdi, 0
    lea rsi, BYTE [tape+rbx]
    mov rdx, 1
    syscall
    inc BYTE [tape+rbx]
    mov rax, 1
    mov rdi, 1
    lea rsi, BYTE [tape+rbx]
    mov rdx, 1
    syscall
    dec rbx
    inc BYTE [tape+rbx]
    mov rax, 1
    mov rdi, 1
    lea rsi, BYTE [tape+rbx]
    mov rdx, 1
    syscall
    dec rbx
    inc BYTE [tape+rbx]
    mov rax, 1
    mov rdi, 1
    lea rsi, BYTE [tape+rbx]
    mov rdx, 1
    syscall
    mov rax, 60
    mov rdi, 0
    syscall
tape: times 2048 db 0
