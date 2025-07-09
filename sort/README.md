# Jasmin Code Development from C via Assembly

This repository documents the step-by-step development of Jasmin programs starting from high-level C code, going through low-level assembly, and finally arriving at structured Jasmin implementations.

## Files

```
├── README.md              # This file
├── sort.c                 # Original C implementation of odd-even merge sort
├── sort_asm_to_c.c        # Line-by-line translation of assembly output into C with gotos
├── sort_add_spills.c      # Same as above, with comments on visible spill operations
├── sort_high_level.c      # Structured version of sort_add_spills using high-level C constructs
└── sort.jazz              # Jasmin implementation derived from high-level C
```

## Project Description

The project explores how to manually derive a Jasmin implementation from C code by observing how compilers optimize and lower code.

### 1. `sort.c`: The Starting Point

* Implements an **odd-even merge sort** in high-level C.
* This file is compiled to assembly using a standard C compiler.

### 2. `sort_asm_to_c.c`: Assembly in C

* A **literal** translation of the generated assembly into C.
* Each assembly instruction maps to one line of C.
* Control flow is reconstructed using `goto` statements, mimicking labels and jumps in the assembly.
* No abstraction or restructuring yet.

### 3. `sort_add_spills.c`: Highlighting Compiler Behavior

* Based on `sort_asm_to_c.c`.
* Adds **comments marking register spills and reloads**, as seen in the assembly.
* This helps track where variables move between registers and memory.

### 4. `sort_high_level.c`: Structured C

* A **restructured version** of the assembly-inspired code.
* Uses only structured control flow: `if`, `for`, `while`, or `do...while` loops.
* Eliminates `goto`, `break`, and other unstructured constructs.
* Keeps the control/data flow as close as possible to the original assembly.
* This version is meant to be as **Jasmin-friendly** as possible.

### 5. `sort.jazz`: Final Jasmin Implementation

* Manual translation of `sort_high_level.c` to **Jasmin**.
* Follows the same control and data flow.
* May still benefit from manual optimizations. Try replacing `_comp_and_swap_64` call with `_comp_and_swap_256` which swaps the block using 256-bit registers.

## Motivation

The process models a **manual decompilation and re-abstraction pipeline**:

* Start with correct C code.
* Observe how the compiler lowers it.
* Reconstruct structured logic from the low-level code.
* Translate to Jasmin.
