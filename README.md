What?
=====
DESCENT is a library that implements a simple [recursive descent parser](https://en.wikipedia.org/wiki/Recursive_descent_parser) to evaluate an algebraic expression described in a string. It handles tokenization, parsing and evaluation of the string.

DESCENT supports addition, subtraction, multiplication, division, exponentiation and negation. Whitespace and unrecognized characters are ignored. If an error occurs while parsing, it will return the index of the token where the error was encountered. Inputs of arbitrary length are supported, but an input string must be null-terminated.

Testing
=======
Run `make tests` to run a simple test suite that checks the tokenizer and mathematical correctness. Run `make fuzz` to fuzz the library (requires that clang be installed).

A simple calculator program is included for trying out the library, which can be run using `make calculator`.

How?
====
Run `make install` to install the library in your system. It can be statically linked in other programs with the header "descent.h" and the linker argument -ldescent.

Run `make uninstall` to remove it from your system.