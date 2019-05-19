/* Convert sequence of hex digits on command line into a string, terminated by \n */
#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
	unsigned long dig = strtoul(argv[i], NULL, 16);
	putchar((char) dig);
    }
    putchar('\n');
    return 0;
}
/* 输入参数：30 31 32 33 34 35 36 37 38 39 输出为：0123456789
