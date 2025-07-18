## Files

- `spill.c` defines a function that applies high pressure on the CPU registers.

  * When compiled with `-O0`, the compiler is forced to spill many registers to memory, which is visible in the generated `spillO0.s` file.
  * With `-O3`, the compiler applies optimizations that eliminate most spills (see `spillO3.s`).

- `spill.jazz` is a direct translation of `spill.c` into Jasmin.
  Since Jasmin does not manage registers automatically, the programmer must decide when to spill variables to memory. Try to compile this code using `jasminc -pasm spill.jazz`

- `spill_success.jazz` includes a few spills to avoid register exhaustion. Now try to compile this program using `jasminc -pasm spill_success.jazz`.

- `complex_sum.c` provides another example where variables are spilled even when compiled with `-O3`. This highlights a useful strategy: We can look at the compiler-generated assembly (`.s` file) to guide our Jasmin implementation.

> Note: `-pasm` flag prints the generated assembly code by Jasmin compiler.

For instance, the following C compiler output:

```asm
movq	%rax, -96(%rsp)     # spill
movq	-96(%rsp), %rdi     # unspill
...
leaq	(%rcx,%rdi), %rax   # lea
```

can be translated into Jasmin as:

```jasmin
() = #spill(var);
...
() = #unspill(var);
rax = #LEA(rcx + var);
```

But, this notation doesn't consider the following case which can save a register:

```asm
movq	%rsi, -72(%rsp)     # spill
...
addq	-72(%rsp), %rax     # unspill
```

we can replicate that case by declaring a `stack` variable as follows:

```jasmin
reg u64 rsi;
stack u64 rsi_s;
rsi_s = rsi;
...
rax += rsi_s;
```

This approach helps mimic the compiler's register management strategy and can lead to more efficient Jasmin code.

## Exercise

`complex_sum.jazz` contains an uncompleted function. Try to complete the function by looking at `complex_sum.s`. Once completed, run `make && ./complex.out`.

> The solution is provided in `complex_sum_solution.txt`.