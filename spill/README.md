## Files

- `spill.c` defines a function that applies high pressure on the CPU registers.

  * When compiled with `-O0`, the compiler is forced to spill many registers to memory, which is visible in the generated `spill.s` file.
  * With `-O3`, the compiler applies optimizations that eliminate most spills.

- `spill.jazz` is a direct translation of `spill.c` into Jasmin.
  Since Jasmin does not manage registers automatically, the programmer must decide when to spill variables to memory. Try to compile this code using `jasminc -pasm spill.jazz`

- `spill_success.jazz` includes a few spills to avoid register exhaustion. Now try to compile this program using `jasminc -pasm spill_success.jazz`.

- `complex_sum.c` provides another example where variables are spilled even when compiled with `-O3`. This highlights a useful strategy: We can look at the compiler-generated assembly (`.s` file) to guide our Jasmin implementation.

> Note: `-pasm` flag prints the generated assembly code by Jasmin compiler.

For instance, the following C compiler output:

```asm
movq	%rsi, -72(%rsp)     # spill
addq	-72(%rsp), %rax     # unspill
```

can be translated into Jasmin as:

```jasmin
() = #spill(rsi);
() = #unspill(rsi);
rax += rsi;
```

This approach helps mimic the compiler's register management strategy and can lead to more efficient Jasmin code.
