include ../Makefile.base

.PHONY: all clean

all: test.out

sortc.s: sort.c
	$(CC) $(CFLAGS) -O3 -S -o $@ sort.c

sortj.s: sort.jazz
	$(JASMINC) -nowarning -o $@ $<

test.out: test.c sortc.s sortj.s
	$(CC) $(CFLAGS) -O3 -o $@ test.c sortc.s sortj.s

clean:
	rm -f *.s *.out
