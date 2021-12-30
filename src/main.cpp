#include <iostream>
#include <unistd.h>
using namespace std;

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
        cout << sizeof(buf) << endl;
        buf_sz++;
        num /= 10;
    } while (num);
    if ( negative ) {
        buf_sz++;
        buf[sizeof(buf) - buf_sz] = '-';
    }

    write(1, &buf[sizeof(buf) - buf_sz], buf_sz);
}

int main () {
    print_nums(-345);
    print_nums(209);
    print_nums(-4345);
    print_nums(16);

    return 0;
}
