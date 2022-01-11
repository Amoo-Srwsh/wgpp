# WGPP - Programming language

This is the continuation of my first ["programming language"](https://github.com/jdpmm/wgdi) which is interpreted, but i wanna go beyond it, and make a better programming language, so this is my compiled programming language.

Every assembly code will be saved at `./src/out`

## Difference between wout and printf

The difference between these functions is that `wout` only can print strings or the value of any variable with a new line at the end, instead `printf` function works like `printf` function in C programming language, you can print strings and values of variables in the same line

## Issue with pot function

An error happen when you make something like: `n^-n` in the `pot` function between variables because the assembly code
looks like:

```asm
powM:
	cmpl %edi, %r15d
	jne powH
	ret
powH:
	imul %r13d, %edx
	incl %r15d
	jmp powM

# Is my code to make a power math function (i don't know how to say it)
# Maybe there is a better way to do it, but i wanted to make it
```

Where:

```asm
movl %r14d, %edx      # edx      = n
movl %r14d, %r13d     # r13d     = n (saves the value of n, is an auxiliar)
movl $2, %edi         # edi      = power
movl $1, %r15d        # r15d     = current number something like: r15d <= edi
```

So all code together would be like in C++

```cpp
// int because the registers used are of 32 bits
int pow (int edx, int r13d) {
    for (int r15d = 0; i <= edi; ++r15d) {
        /* edx at the start was n but now is n*n, so r13d saves the original
         * value of n */
        edx *= r13d;
    }
}
```

So when you set a negative number on edi i don't know why but the proccess is so slow, can take until 3 seconds!! i don't know what happend with that yet.

When you set a negative number on edx the result will always be positive `(-edx^edi) >= 1`

## Done
* [x] Exit function with numbers
* [x] Ignore comments and whitespaces
* [x] Print strings
* [x] Many instructions in one line
* [x] Intger variables
* [x] Print integer variables
* [x] Exit with variable
* [x] Printf function
* [x] Scape characters
* [x] Arithmetic

## To Do
* With GNU Assembly
* Fix `pot` mathematical function (between variables)
* Make better error reports
* Check type variables in exit and print functions
* Overwrite variables

## References
* [x86_64 Assembly](https://en.wikipedia.org/wiki/X86_assembly_language)
* [Ascii code](https://elcodigoascii.com.ar/)
* [GNU Assembly](https://es.wikipedia.org/wiki/GNU_Assembler)
