# Jasmin Matrix Multiplication Tutorial

This repository provides a hands-on tutorial for implementing and optimizing code using [Jasmin](github.com/jasmin-lang/jasmin). Jasmin is designed to give predictable and verifiable low-level control, as each instruction compiles directly to a single assembly instruction.

## Goal

Demonstrate how to translate and optimize C code into Jasmin by analyzing compiler-generated assembly.
The main function studied here is:

```c
void multiply_matrices(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);
```

which performs matrix multiplication for n×n matrices.

## Files

```
├── Makefile                   # Build script to compile all programs
├── matrix.c                   # C implementation of multiply_matrices
├── matrix.jazz                # Naive Jasmin implementation
├── matrix_optimized.jazz      # Jasmin implementation optimized via reverse-engineered -O3 assembly
├── speed.c                    # Benchmarking code
├── test.c                     # Correctness testing code
└── README.md                  # This file
```

## Building

To compile all components, simply run:

```bash
make
```

This will generate the following executable:

* `test.out` — Runs correctness test and compares the performance of C, naive Jasmin, and optimized Jasmin implementations

## How It Works

1. **C baseline**
   The `matrix.c` file contains a simple, readable version of `multiply_matrices`.

2. **Naive Jasmin**
   The same algorithm is translated directly into Jasmin in `matrix.jazz`, without optimizations.

3. **Optimized Jasmin**
   The C code is compiled with `-O3` to assembly. That assembly is then manually translated to Jasmin in `matrix_optimized.jazz`.
