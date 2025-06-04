
./PHONY: py
py: build/outp
	./build/outp

build/outp: build/outp.s
	fasm build/outp.s

build/outp.s: hello.bf
	./bfc.py hello.bf build/outp.s

./PHONY: cpp
cpp: build/outc
	./build/outc

build/outc: build/outc.s
	fasm build/outc.s

build/outc.s: build/bfcc hello.bf
	build/bfcc hello.bf build/outc.s

build/bfcc: bfc.cpp
	g++ bfc.cpp -Wall -Wextra -o build/bfcc




