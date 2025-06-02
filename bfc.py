#!/usr/bin/python3

from sys import argv

src: str

if len(argv) < 3:
    print("Invalid number of arguments.")
    exit(1)

with open(argv[1]) as in_file:
    src = in_file.read()

with open(argv[2], "w") as out:
    lc = 0
    ls = []
    out.write("FORMAT ELF64 EXECUTABLE\n")
    out.write("entry start\n")
    out.write("start:\n")
    out.write("    mov rbx, 0\n")
    for c in src:
        match c:
            case '+': out.write("    inc BYTE [tape+rbx]\n")
            case '-': out.write("    dec BYTE [tape+rbx]\n")
            case '<': out.write("    dec rbx\n")
            case '>': out.write("    inc rbx\n")
            case '[':
                out.write( "    cmp BYTE [tape+rbx], 0\n")
                out.write(f".again{lc}:\n")
                out.write(f"    je .over{lc}\n")
                ls.append(lc)
                lc += 1
            case ']':
                ln = ls.pop()
                out.write( "    cmp BYTE [tape+rbx], 0\n")
                out.write(f"    jne .again{ln}\n")
                out.write(f".over{ln}:")
            case '.':
                out.write("    mov rax, 1\n")
                out.write("    mov rdi, 1\n")
                out.write("    lea rsi, BYTE [tape+rbx]\n")
                out.write("    mov rdx, 1\n")
                out.write("    syscall\n")
            case ',':
                out.write("    mov rax, 0\n")
                out.write("    mov rdi, 0\n")
                out.write("    lea rsi, BYTE [tape+rbx]\n")
                out.write("    mov rdx, 1\n")
                out.write("    syscall\n")
    out.write("    mov rax, 60\n")
    out.write("    mov rdi, 0\n")
    out.write("    syscall\n")
    out.write("tape: times 2048 db 0\n")

