#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

int main(int argc, char *argv[]) {
  char prefix[BUFSIZE];
  char next[BUFSIZE];
    int i;
    float sum = 0.0;
    for (i = 1; i < argc; i++) {
	float x = atof(argv[i]);
	sum += x;
	if (i == 1) {
	  sprintf(prefix, "%.4g", x);
	} else {
	  sprintf(next, " + %.4g", x);
	  strcat(prefix, next);
	  printf("%s = %.4g\n", prefix, sum);
	}
    }
    return 0;
}
/*
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out 1e20 -1e20 3.14
1e+20 + -1e+20 = 0
1e+20 + -1e+20 + 3.14 = 3.14
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out -1e20 3.14  
-1e+20 + 3.14 = -1e+20
@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out -1e20 3.14  1e20
-1e+20 + 3.14 = -1e+20
-1e+20 + 3.14 + 1e+20 = 0

*/
