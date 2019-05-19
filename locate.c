#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void show_pointer(void *p, char *descr) {
    //    printf("Pointer for %s at %p\n", descr, p);
    printf("%s\t%p\t%lu\n", descr, p, (unsigned long) p);
}

char big_array[1L<<24];    /*  16 MB */
//char huge_array[1L<<31];   /*   2 GB */
char huge_array[1L<<30];/*   1 GB */
int global = 0;

int useless() { return 0; }

int main ()
{
    void *p1, *p2, *p3, *p4;
    int local = 0;
    p1 = malloc(1L << 28);
    p2 = malloc(1L << 8);
    //p3 = malloc(1L << 32);
	p3 = malloc(1L << 16);
    p4 = malloc(1L << 8);

    show_pointer((void *) big_array, "big array");
    show_pointer((void *) huge_array, "huge array");
    show_pointer((void *) &local, "local");
    show_pointer((void *) &global, "global");
    show_pointer((void *) p1, "p1");
    show_pointer((void *) p2, "p2");
    show_pointer((void *) p3, "p3");
    show_pointer((void *) p4, "p4");
    show_pointer((void *) useless, "useless");
    show_pointer((void *) exit, "exit");
    show_pointer((void *) malloc, "malloc");
    return 0;
}

/*
gec@ubuntu:/mnt/hgfs/share/csapp_code$ gcc locate.c
gec@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out
big array	0x4804a060	1208262752
huge array	0x804a060	134520928
local	0xbfcc9fdc	3217858524
global	0x804a044	134520900
p1	0xa7545008	2807320584
p2	0x49a67008	1235644424
p3	0x49a67110	1235644688
p4	0x49a77118	1235710232
useless	0x80484b6	134513846
exit	0x8048370	134513520
malloc	0x8048350	134513488

*/