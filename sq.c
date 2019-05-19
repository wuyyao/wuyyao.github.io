#include <stdio.h>
#include <stdlib.h>

int sq(int x) {
    return x*x;
}

int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
	int x = atoi(argv[i]);
	int sx = sq(x);
	printf("sq(%d) = %d\n", x, sx);
    }
    return 0;
}

/*@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 12
sq(12) = 144
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 65535
sq(65535) = -131071
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 40000
sq(40000) = 1600000000
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 50000
sq(50000) = -1794967296
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 400000
sq(400000) = 1086210048
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 500000
sq(500000) = 891896832
*/
