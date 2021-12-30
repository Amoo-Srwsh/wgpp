# WGPP - Programming language

This is the continuation of my first ["programming language"](https://github.com/jdpmm/wgdi) which is interpreted, but i wanna go beyond it, and make a better programming language, so this is my compiled programming language.

## Printing numbers with assembly

In assembly could not print numbers like in high-level programming languages, to print any number you must indicate the ascii code of each character, so isn't so easy like on C++ or C, on C++ you can make:

```c
#include <iostream>
using namespace std;

int main () {
    cout << 5 << endl;
    return 0;
}
```

But in assembly you should make somehting like:

```asm
section .data
	msg db 53     ; poi5 in ascii code
 
section .text
	global _start
 
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
	mov rdx, 1
    syscall
; more code...
```

So i've copied the next code from [here](https://youtu.be/8QP2fDBIxjM?list=PLpM-Dvs8t0VbMZA7wW9aR3EtBqe2kinu4&t=4552) to print only **unsigned numbers** but i make a new thing to print negative numbers, well, the the same thing but with '-' symbol.

```cpp
void print_nums (int64_t num) {
    bool negative = false;
    if ( (int) num <= -1 ) {
        negative = !negative;
        num *= -1;
    }

    char buf[32];
    size_t buf_sz = 1;
    buf[sizeof(buf) - buf_sz] = '\n';

    do {
        buf[sizeof(buf) - buf_sz - 1] = num % 10 + '0';
        buf_sz++;
        num /= 10;
    } while (num);
    if ( negative ) {
        buf_sz++;
        buf[sizeof(buf) - buf_sz] = '-';
    }

    write(1, &buf[sizeof(buf) - buf_sz], buf_sz);
}
```
Yes! i copied this code, but i got it!, so:

```cpp
char buf[32];
size_t buf_sz = 1;
buf[sizeof(buf) - buf_sz] = '\n';
```

`buf` make reference to `rsi` register, and has 32 idxs because the number to print always will be of 64 bits, the last line is to print the number with a new line, it means all array is empty yet, but his last element is a new line

```cpp
buf[sizeof(buf) - buf_sz - 1] = num % 10 + '0';
buf_sz++;
num /= 10;
```

`sizeof(buf)` always will be 32, `- buf_sz` indicates in which bite we are, `-1` because we already push a element (\n).
`num % 10 + '0'` The mod of the number by 10 indicate the last current digit, so if we have `345` then `345 % 10 = 5`, `+ '0'` we added 0 (or 48 in ascii code) to get the ascii code of the current digit, for example, we had '5' char and his position is 53 in the ascii code, but at this moment the 5 points to `ENQ` in ascii table, hey, but if we add 5 + 48 we'll have 53 and 53 points to '5' in ascii code :D.

`buf_sz++`:

```
buf_sz                = 1;
buf                   = [NULL, NULL, ..., NULL, NULL, NULL]
sizeof(buf) - 1 = 32  =                           ^    \n

buf_sz                = 2;
buf                   = [NULL, NULL, ..., NULL, NULL, NULL]
sizeof(buf) - 2 = 31  =                    ^    digit \n
```

 `num /= 10`:

```
345 % 10 = 5; 345 / 10 = 34.5
34.5 % 10 = 4; 34.5 % 10 = 3.45
3.45 % 10 = 3; 3.45 % 10 = 0.345 -> While loop stop here
```

```cpp
if ( negative ) {
	buf_sz++;
	buf[sizeof(buf) - buf_sz] = '-';
}
```

If the number to print is negative the number was multiplicated by -1 to become it to positive :D, but now we're gotta add '-' symbol.

```cpp
write(1, &buf[sizeof(buf) - buf_sz], buf_sz);
```

Basically asm code but in C++.

## References

* [x86_64 assembly](https://en.wikipedia.org/wiki/X86_assembly_language)
* [Ascii code](https://elcodigoascii.com.ar/)
