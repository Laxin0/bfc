out: out.s
	fasm out.s

out.s: hello.bf
	./bfc.py hello.bf
