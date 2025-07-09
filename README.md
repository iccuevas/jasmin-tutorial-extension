# Extended Jasmin Tutorial

> Before proceeding with this guide, I recommend starting with the [Jasmin Tutorial](https://github.com/formosa-crypto/jasmin-tutorial). It includes two exercises to help you get familiar with Jasmin’s syntax and core concepts.

In this guide, we focus on how Jasmin programs are typically developed and structured. Jasmin-based repositories are usually organized as follows:

```
├── c/            # C implementation (optionally optimized with AVX2)
└── jasmin/
    ├── ref/      # Jasmin reference implementation
    └── avx2/     # Jasmin AVX2-optimized implementation
```


## Functions

Jasmin supports three types of functions:

```
inline g() {}
```
The compiler inlines these functions—i.e., their content is directly inserted at each call site.

```
fn f() {}
```
This is a standard function. Calls to it are compiled into Assembly using the `call` instruction. These functions *can* be inlined as well (see `inline_functions.jazz`).

```
export h() {}
```
This is also a standard function, but the compiler only compiles functions marked as `export` (along with any other functions they use). If you try to compile a non-exported function directly, the output will be empty.

> **Note:** You can compile a specific function `f` by using the `-slice=[f]` flag.

Finally, there's a naming convention for file formats:

* `.jazz` files contain exported functions
* `.jinc` files contain all other code


## How to export and use Jasmin functions in a C program

Jasmin generates assembly code that follows the C [ABI](https://en.wikipedia.org/wiki/Application_binary_interface) convention. This makes it straightforward to call Jasmin functions from C.

A clean setup involves the following steps:

1. Declare the Jasmin function in your C code using `extern`:

   ```c
   extern void foo();
   ```

2. Compile the `.jazz` file that contains the exported Jasmin function.
    Make sure the function name matches exactly between Jasmin and C.

3. Link the generated assembly (`.s`) file when compiling your C program:

    ```
    gcc -o test.out test.c jasmin.s
    ```


## Examples

There are three examples in this repository to better understand how Jasmin compiler works and how we can optimize our code taking advantage of C compiler.

```
├── spill/
├── optimization/
└── sort/
```

### `spill`

In Jasmin, register management is manual. The programmer decides which variables are kept in registers and which are moved to memory. This level of control is crucial in cryptographic code, where loading a value from memory often marks it as secret. Managing spills properly helps avoid unnecessary memory access and minimizes side-channel risks.

This directory provides examples of how spilling works in Jasmin, and how Jasmin developers can use C register use optimizations to optimize their own code.

### `optimization`

This directory focuses on performance optimization in Jasmin. It demonstrates how to translate a C implementation of matrix multiplication into Jasmin and improve it by analyzing compiler-generated `-O3` assembly.

It includes a naive translation and an optimized version that mimics the C compiler’s register and instruction choices. Benchmarking and correctness tests are also provided to compare the performance of all implementations.

### `sort`

This directory presents a real-world Jasmin development based on a sorting algorithm used in Path ORAM implementation. From a high-level C implementation of odd-even merge sort, to analyzing the compiler’s generated assembly, reconstructing structured logic, and finally producing a Jasmin version.

The project demonstrates how to reverse-engineer compiler behavior, track spills, and structure code for Jasmin translation.