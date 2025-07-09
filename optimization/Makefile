include ../Makefile.base

ASM_O0=matrixO0.s
ASM_O3=matrixO3.s
ASM_JAZZ=matrix.s matrix_optimized.s

TEST_OUT=test.out

.PHONY: all clean

all: $(ASM_O0) $(ASM_O3) $(ASM_JAZZ) $(TEST_OUT) $(SPEED_OUT)

$(ASM_O0): matrix.c
	$(CC) -O0 -S -DFUNC_NAME=multiply_matrices -o $@ $<

$(ASM_O3): matrix.c
	$(CC) -O3 -S -DFUNC_NAME=multiply_matrices_optimized -o $@ $<

%.s: %.jazz
	$(JASMINC) -nowarning -o $@ $<

%.out: %.c $(ASM_O0) $(ASM_O3) $(ASM_JAZZ)
	$(CC) $(CFLAGS) -o $@ $< $(ASM_O0) $(ASM_O3) $(ASM_JAZZ)

clean:
	rm -f *.s *.out
