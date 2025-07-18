include ../Makefile.base

.PHONY: all clean

all: test spillO0.s spillO3.s

test: complex_sum.s complex_sum_jazz.s test_complex_sum.c
	$(CC) $(CFLAGS) -O3 -o complex.out test_complex_sum.c complex_sum.s complex_sum_jazz.s

complex_sum_jazz.s: complex_sum.jazz
	$(JASMINC) -nowarning -o complex_sum_jazz.s complex_sum.jazz

complex_sum.s: complex_sum.c
	$(CC) $(CFLAGS) -O3 -S -o complex_sum.s complex_sum.c

spillO0.s: spill.c
	$(CC) $(CFLAGS) -O0 -S -o spillO0.s spill.c

spillO3.s: spill.c
	$(CC) $(CFLAGS) -O3 -S -o spillO3.s spill.c

clean:
	rm -f spillO0.s spillO3.s complex_sum_jazz.s *.out
