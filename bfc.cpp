#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]){ 
    if (argc < 3){
        std::cout << "Invalid number of arguments." << std::endl;
        return 1;
    }

    char c;
    std::ifstream ifs(argv[1]);
    std::ofstream out(argv[2]);

    std::vector<int> ls;
    int lc = 0;
    out << "FORMAT ELF64 EXECUTABLE\n";
    out << "entry start\n";
    out << "start:\n";
    out << "    mov rbx, 0\n";
 
    while (ifs.good()){
        c = ifs.get();
        switch (c){
            case '+': out << "    inc BYTE [tape+rbx]\n"; break;
            case '-': out << "    dec BYTE [tape+rbx]\n"; break;
            case '<': out << "    dec rbx\n"; break;
            case '>': out << "    inc rbx\n"; break;
            case '[':{
                out << "    cmp BYTE [tape+rbx], 0\n";
                out << ".again" << lc << ":\n";
                out << "    je .over" << lc << "\n";
                ls.push_back(lc);
                lc++;
                break;
            }
            case ']':{
                int ln = ls.back();
                ls.pop_back();
                out << "    cmp BYTE [tape+rbx], 0\n";
                out << "    jne .again" << ln << "\n";
                out << ".over" << ln << ":\n";
                break;
            }
            case '.':{
                out << "    mov rax, 1\n";
                out << "    mov rdi, 1\n";
                out << "    lea rsi, BYTE [tape+rbx]\n";
                out << "    mov rdx, 1\n";
                out << "    syscall\n";
                break;
            }
            case ',':{
                out << "    mov rax, 0\n";
                out << "    mov rdi, 0\n";
                out << "    lea rsi, BYTE [tape+rbx]\n";
                out << "    mov rdx, 1\n";
                out << "    syscall\n";
                break;
            }
        }
    }
    out << "    mov rax, 60\n";
    out << "    mov rdi, 0\n";
    out << "    syscall\n";
    out << "tape: times 2048 db 0\n";

    return 0;
}
