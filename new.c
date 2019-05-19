#include <stdlib.h>
#include <stdio.h>
typedef struct{
	int a[2];
	double d;
} struct_t;

double fun(int i) {
	volatile struct_t s;
	s.d = 3.14;
	s.a[i] = 1073741824; /* Possibly out of bounds */
	return s.d; /* Should be 3.14 */
}

int main(int argc, char *argv[])
{
	int i = 0;
	if(argc >= 2)
	i = atoi(argv[1]);
	double d = fun(i);
	printf("fun(%d) --> %.10f\n", i, d);
	return 0;
}
数组越界访问 低三十二位
不检查栈的边界