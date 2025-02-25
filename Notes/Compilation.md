** Steps of compilation:
Compilation is the process of converting high-level source code (like C, C++, or Java) into machine code that can be executed by a computer. The compilation process can be broken down into several stages, each with specific tasks and intermediate states. The typical steps involved in compilation are:

1. Preprocessing
Input: Source code (e.g., main.c)
Output: Preprocessed source code
Purpose: The preprocessor handles directives like #include, #define, and #ifdef. It performs the following tasks:
Macro Expansion: Replaces macros (e.g., #define PI 3.14) with their actual values.
File Inclusion: Replaces #include statements with the contents of the included files (header files like #include <stdio.h>).
Conditional Compilation: Evaluates #ifdef and #ifndef directives to conditionally compile parts of the code.
Intermediate State: A file with all macros expanded, header files included, and conditional code blocks resolved. This is typically saved with an extension like .i for C or .ii for C++.

2. Lexical Analysis (Scanning)
Input: Preprocessed source code
Output: Tokens (atomic units like keywords, operators, literals, etc.)
Purpose: The lexical analyzer (scanner) reads the preprocessed code and breaks it down into tokens, which are the smallest syntactic units (e.g., int, main, =, 3, ;).
Intermediate State: A stream of tokens representing the source code.
Example: int main() { int a = 3; } might become tokens like [int, main, (, ), {, int, a, =, 3, ;, }]

3. Syntax Analysis (Parsing)
Input: Tokens
Output: Parse Tree (or Abstract Syntax Tree - AST)
Purpose: The parser checks the structure of the token stream against the grammar of the programming language (e.g., C or C++ grammar). It builds a Parse Tree or AST.
AST: A tree-like structure where nodes represent syntactic constructs such as statements, expressions, and declarations.
The parser ensures that the code follows the correct syntax. If there is a syntax error, the compilation will stop at this stage.
Intermediate State: The Parse Tree or AST, which represents the hierarchical structure of the source code.
Example: The expression a = 3 + 4 would be represented as an AST where = is the root, and 3 + 4 is a subtree under the assignment.

4. Semantic Analysis
Input: Parse Tree/AST
Output: Annotated AST with semantic information
Purpose: The semantic analyzer checks the meaning of the program. It performs checks such as:
Type Checking: Ensures that the types of variables and expressions match (e.g., you can't assign a float to an int).
Variable Declarations: Ensures variables are declared before they are used.
Function/Procedure Checks: Checks that functions are called with the correct number and types of arguments.
Intermediate State: The AST is now annotated with additional information like data types, symbol table references, and scoping rules.
Example: If the variable a is declared as int, the semantic analyzer ensures that it is only assigned integer values.

5. Intermediate Code Generation
Input: Annotated AST
Output: Intermediate Representation (IR)
Purpose: This step converts the high-level constructs into a lower-level, platform-independent representation known as Intermediate Code. The IR is not machine code but is easier to translate to machine code later.
Three-Address Code (TAC) is a common form of IR, where each operation has at most three operands.
Example: An expression like a = b + c * d may be broken down into intermediate instructions such as:
makefile
Copy code
t1 = c * d
t2 = b + t1
a = t2
Intermediate State: An IR that is more abstract than machine code but simpler than high-level source code.

6. Optimization
Input: Intermediate Code
Output: Optimized Intermediate Code
Purpose: The optimizer improves the intermediate code to make the final executable faster and/or smaller without changing the meaning of the program. Common optimizations include:
Constant Folding: Replacing constant expressions with their results (e.g., replacing 3 + 4 with 7).
Dead Code Elimination: Removing code that is never used or has no effect (e.g., variables that are assigned but never used).
Loop Optimization: Improving the performance of loops by techniques like loop unrolling or invariant code motion.
Intermediate State: Optimized IR, ready for translation to machine code.

7. Code Generation
Input: Optimized Intermediate Code
Output: Assembly Code (target-dependent)
Purpose: The code generator translates the optimized IR into assembly code for the target machine. This step involves mapping high-level constructs to hardware-level instructions.
Intermediate State: Assembly code, specific to the architecture for which the program is being compiled (e.g., x86, ARM).

8. Assembly
Input: Assembly Code
Output: Object Code (Machine Code)
Purpose: The assembler converts the assembly code into machine code (binary instructions that the CPU can understand). The output is typically an object file (.o or .obj), which contains the machine code but may also include unresolved references to external libraries or functions.
Intermediate State: An object file, which is a compiled but non-executable version of the program.

9. Linking
Input: Object Files, Libraries
Output: Executable File
Purpose: The linker takes one or more object files and links them together to form an executable. It resolves symbol references (e.g., function calls or global variables) between object files and links any necessary libraries (standard or user-defined).
Intermediate State: The final executable file that can be run on the target machine (e.g., a.out on Linux or .exe on Windows).

10. Loading and Execution (Runtime)
Input: Executable File
Output: Running Program
Purpose: When the program is run, the operating system loads the executable into memory, allocates resources, and starts executing the code.

