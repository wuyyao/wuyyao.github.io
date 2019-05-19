#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a[2];
    double d;
} struct_t;

double fun(int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824; /* Possibly out of bounds */
    return s.d; /* Should be 3.14 */
}

int main(int argc, char *argv[]) {
    int i = 0;
    if (argc >= 2)
	i = atoi(argv[1]);
    double d = fun(i);
    printf("fun(%d) --> %.10f\n", i, d);
    return 0;
}
/*
gec@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 0
fun(0) --> 3.1400000000
gec@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 1
fun(1) --> 3.1400000000
gec@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 2
fun(2) --> 3.1399998665
gec@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 3
fun(3) --> 2.0000006104
gec@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 4
fun(4) --> 3.1400000000
段错�?(核心已转�?

*/

