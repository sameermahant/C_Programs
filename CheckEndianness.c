#include <stdio.h>

int main(int argc, char  **argv)
{
    union {
        short s;
        char c[sizeof(short)];
    } data;
    data.s = 0x0102;

    if (sizeof(short) == 2) {
        if (data.c[0] == 1 && data.c[1] == 2) {
            printf("Big-endian\n");
        } else if (data.c[0] == 2 && data.c[1] == 1) {
            printf("Little-endian\n");
        } else {
            printf("Unknown\n");
        }
    } else {
        printf("sizeof(short) = %d\n", sizeof(short));
    }
    exit(0);
}
