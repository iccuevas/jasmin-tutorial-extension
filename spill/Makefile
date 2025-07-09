include ../Makefile.base

.PHONY: all clean

all: spillO0.s spillO3.s complex_sum.s

complex_sum.s: complex_sum.c
	$(CC) $(CFLAGS) -O3 -S -o complex_sum.s complex_sum.c

spillO0.s: spill.c
	$(CC) $(CFLAGS) -O0 -S -o spillO0.s spill.c

spillO3.s: spill.c
	$(CC) $(CFLAGS) -O3 -S -o spillO3.s spill.c

clean:
	rm -f *.s
