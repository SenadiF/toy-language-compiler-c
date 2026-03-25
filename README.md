# Toy Language Compiler in C

## 🎯 Project Goal

This project aims to understand how programming languages work internally by building a simple interpreter in C.

It focuses on:
- Lexical analysis (tokenization)
- Parsing into an Abstract Syntax Tree (AST)
- Interpreting and executing the AST
- Understanding pointers, memory, and data structures in C

---

## 🧠 Why C?

C is used for this project because it provides:

- Direct memory control using pointers  
- Manual memory allocation (`malloc`)  
- Efficient handling of low-level data structures  
- Better understanding of how compilers/interpreters work internally  

---

## 📌 Core Concepts

### Pointers

Pointers store memory addresses.

```c
int *p;
*p = 5;
```
### Lexer (Tokenizer)

The lexer converts raw source code into tokens.
Example

Input:
```c
let x = 5 + 3
```
Tokens:
```c
LET
IDENTIFIER(x)
EQUALS
NUMBER(5)
PLUS
NUMBER(3)
```
### Parser & AST (Abstract Syntax Tree)

The parser converts tokens into a tree structure representing the program.

Example Expression:
```c
5 + 3
```
AST
```c
   (+)
  /   \
(5)   (3)
```
### Operator Precedence

Handled using layered parsing:
```c
| Function             | Purpose                       |
| -------------------- | ----------------------------- |
| `parse_factor()`     | Handles numbers and variables |
| `parse_term()`       | Handles `*` and `/`           |
| `parse_expression()` | Handles `+` and `-`           |

```
Other Functions:
```c
parse_statement() → parses statements like let and print
parse_program() → handles multiple statements
parser_expect() → validates expected tokens
create_node() → creates AST nodes
```
### AST Structure

Each node represents part of the program.
```c
typedef struct ASTNode {
    ASTNodeType type;
    char value[64];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next; // used for chaining statements
} ASTNode;

left/right → used for expressions
next → used for linking multiple statements
```
### Interpreter

The interpreter executes the AST.

Context – Stores variables and their values:
```c
typedef struct {
    char names[MAX_VARS][MAX_NAME_LEN];
    int values[MAX_VARS];
    int count;
} Context;

```
```c
Key Functions:

eval() → evaluates expressions
execute() → executes statements
set_variable() → assigns values
get_variable() → retrieves values
```
### 🚀 Program Pipeline
```c
Source Code → Lexer (Tokens) → Parser → AST → Interpreter → Output
```

### ✅ Current Features

- Variable declaration (let)
- Arithmetic operations (+ - * /)
- Print statements
- Multiple statements
- AST-based execution

---


### 🔮 Future Improvements

-  Add conditionals (if, else)
-  Add loops (while, for)
- Add functions
- Improve symbol table
- Add better error reporting
-Extend to bytecode or compiled output

