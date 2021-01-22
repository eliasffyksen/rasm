
# RISC-V (RV32I) Assembler written in C with GNU Flex & Bison

A simple and fast assembler for risc-v architecture

## Goal of the project

To create a minimalistic and readable assembler for RISC-V.
Mainly for educational purposes.

## Building and running the code

To build the system run: `make`
To run it, run: `bin/rasm`

*NB: Flex and bison must be installed to build*

## Current state of the project

Right now the assembler only accepts from stdin, and spits
out the encoded instructions in a nice and readable format
for debugging.

Example (`make && bin/rasm`):
```
add s0, s1, s2
+---------+-----+-----+--------+-----+---------+
|  funct7 | rs2 | rs1 | funct3 |  rd |  opcode |
+---------+-----+-----+--------+-----+---------+
| 0000000 | x18 | x09 |    000 | x08 | 0110011 |
+---------+-----+-----+--------+-----+---------+
addi s0, s1, 666
+---------------+-----+--------+-----+---------+
|    immi[11:0] | rs1 | funct3 |  rd |  opcode |
+---------------+-----+--------+-----+---------+
|         0x29a | x09 |    000 | x08 | 0010011 |
+---------------+-----+--------+-----+---------+
slli s0, s1, 3
+---------+-----+-----+--------+-----+---------+
|  funct7 |shamt| rs1 | funct3 |  rd |  opcode |
+---------+-----+-----+--------+-----+---------+
| 0000000 | 0x09| x09 |    001 | x08 | 0010011 |
+---------------+-----+--------+-----+---------+
```

## TODO:

### RV31I Base Instructions

 - [x] Registers and register ABI
 - [x] ALU register-register instructions
 - [ ] ***BLOCKED*** ALU Immidiate instructions
 - [x] Basic instruction implementation with decimal numbers
 - [ ] ***BLOCKED*** Allow hex numbers
 - [x] Immidiate validation
 - [ ] ***DOING*** Conditional branch instructions
 - [ ] Upper immediate instructions
 - [ ] Unconditional jumps
 - [ ] Indirect jump instruction
 - [ ] Load and store instruction
 - [ ] Memory ordering instructions

### Misc

 - [ ] Lables
 - [ ] Symbol table
 - [ ] Psudo-instructions
 - [ ] Hi low macro

### Command line options

 - [ ] Interactive mode *(only mode, for the time beeing)*
 - [ ] Pretty print assembly table
 - [ ] Verbosity
 - [ ] Input file
 - [ ] Output filename
 - [ ] Target

### Output formats
 - [ ] Hex dump
 - [ ] ELF .o File


## Understanding the code base

The instructions are defined in the `tokenizer.l`, and passes down options for op-code
funct3, funct7, etc. And a token representing the instruction type (f.ex. R_TYPE).
This means that you only need to write one line to implement a new instruction.

Instruction types has to be defined in `parser.y`. A token and a grammar must be created for them.
In the `instr.c` there should be a generator function, like `instr_R_type`, used by the grammar,
There should also be a entry in the `enum instr_type` in `decode.h`, a pretty print function in
`decode.c`, like `print_instr_R_type`, and a case should be added in both the `print_instr` and
`get_instr_type` functions (also in `decode.c`).

The registers and register ABI is also defined in `tokenizer.l`.

Further types data types are also defined in `AST.h`.

With this knowladge the rest of the code base should be fairly easy to understand,
given knowledge about GNU Flex & Bison.
