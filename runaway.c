/* Example of deep recursion */
#include <stdio.h>
#include <stdlib.h>

int recurse(int x) {
    int a[1<<15];  /* 4 * 2^15 =  64 KiB */
    printf("x = %d.  a at %p\n", x, a); 
    a[0] = (1<<14)-1;
    a[a[0]] = x-1;
    if (a[a[0]] == 0)
	return -1;
    return recurse(a[a[0]]) - 1;
}

int main(int argc, char *argv[]) {
    int x = 100;
    if (argc > 1)
	x = atoi(argv[1]);
    int v = recurse(x);
    printf("x = %d.  recurse(x) = %d\n", x, v);
    return 0;
}
/*不带参数
x = 100.  a at 0xbfd3f8b0
x = 99.  a at 0xbfd1f890
x = 98.  a at 0xbfcff870
x = 97.  a at 0xbfcdf850
x = 96.  a at 0xbfcbf830
x = 95.  a at 0xbfc9f810
x = 94.  a at 0xbfc7f7f0
x = 93.  a at 0xbfc5f7d0
x = 92.  a at 0xbfc3f7b0
x = 91.  a at 0xbfc1f790
x = 90.  a at 0xbfbff770
x = 89.  a at 0xbfbdf750
x = 88.  a at 0xbfbbf730
x = 87.  a at 0xbfb9f710
x = 86.  a at 0xbfb7f6f0
x = 85.  a at 0xbfb5f6d0
x = 84.  a at 0xbfb3f6b0
x = 83.  a at 0xbfb1f690
x = 82.  a at 0xbfaff670
x = 81.  a at 0xbfadf650
x = 80.  a at 0xbfabf630
x = 79.  a at 0xbfa9f610
x = 78.  a at 0xbfa7f5f0
x = 77.  a at 0xbfa5f5d0
x = 76.  a at 0xbfa3f5b0
x = 75.  a at 0xbfa1f590
x = 74.  a at 0xbf9ff570
x = 73.  a at 0xbf9df550
x = 72.  a at 0xbf9bf530
x = 71.  a at 0xbf99f510
x = 70.  a at 0xbf97f4f0
x = 69.  a at 0xbf95f4d0
x = 68.  a at 0xbf93f4b0
x = 67.  a at 0xbf91f490
x = 66.  a at 0xbf8ff470
x = 65.  a at 0xbf8df450
x = 64.  a at 0xbf8bf430
x = 63.  a at 0xbf89f410
x = 62.  a at 0xbf87f3f0
x = 61.  a at 0xbf85f3d0
x = 60.  a at 0xbf83f3b0
x = 59.  a at 0xbf81f390
x = 58.  a at 0xbf7ff370
x = 57.  a at 0xbf7df350
x = 56.  a at 0xbf7bf330
x = 55.  a at 0xbf79f310
x = 54.  a at 0xbf77f2f0
x = 53.  a at 0xbf75f2d0
x = 52.  a at 0xbf73f2b0
x = 51.  a at 0xbf71f290
x = 50.  a at 0xbf6ff270
x = 49.  a at 0xbf6df250
x = 48.  a at 0xbf6bf230
x = 47.  a at 0xbf69f210
x = 46.  a at 0xbf67f1f0
x = 45.  a at 0xbf65f1d0
x = 44.  a at 0xbf63f1b0
x = 43.  a at 0xbf61f190
x = 42.  a at 0xbf5ff170
x = 41.  a at 0xbf5df150
x = 40.  a at 0xbf5bf130
x = 39.  a at 0xbf59f110
x = 38.  a at 0xbf57f0f0
段错误 (核心已转储)
输入参数如 20
x = 20.  a at 0xbfb0c910
x = 19.  a at 0xbfaec8f0
x = 18.  a at 0xbfacc8d0
x = 17.  a at 0xbfaac8b0
x = 16.  a at 0xbfa8c890
x = 15.  a at 0xbfa6c870
x = 14.  a at 0xbfa4c850
x = 13.  a at 0xbfa2c830
x = 12.  a at 0xbfa0c810
x = 11.  a at 0xbf9ec7f0
x = 10.  a at 0xbf9cc7d0
x = 9.  a at 0xbf9ac7b0
x = 8.  a at 0xbf98c790
x = 7.  a at 0xbf96c770
x = 6.  a at 0xbf94c750
x = 5.  a at 0xbf92c730
x = 4.  a at 0xbf90c710
x = 3.  a at 0xbf8ec6f0
x = 2.  a at 0xbf8cc6d0
x = 1.  a at 0xbf8ac6b0
x = 20.  recurse(x) = -20
 思考练习以下命令：
 -d:将代码段反汇编
-S:将代码段反汇编的同时，将反汇编代码和源代码交替显示，编译时需要给出-g，即需要调试信息。
-l:反汇编代码中插入源代码的文件名和行号。
-j section:仅反汇编指定的section。可以有多个-j参数来选择多个section。

 objdump -d a.out # 简单反汇编
 objdump -S a.out # 反汇编代码中混入对应的源代码
 objdump -j .text -l -S a.out # 打印源文件名和行号 
*/