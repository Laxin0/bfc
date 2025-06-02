out: out.s
	fasm out.s

out.s: hello.bf
	./bfc.py hello.bf

main: main.cpp
	g++ main.cpp -Wall -Wextra -o main
