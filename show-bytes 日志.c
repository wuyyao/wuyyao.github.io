/* show-bytes - prints byte representation of data */
/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
/* $begin show-bytes */

typedef unsigned char *byte_pointer;	/*unsigned char char和int由于有符                     						号，无符号和字节长短区别会有扩展*/
//typedef char *byte_pointer;
//typedef int *byte_pointer;

void show_bytes(byte_pointer start, size_t len) 
{
    size_t i;
    for (i = 0; i < len; i++)//历遍字符
	printf("%p\t0x%.2x\n", &start[i], start[i]); //得到存储地址及该存储地址里的字符
    printf("\n");
}

void show_int(int x)//显示int型整数的存储方式
{
    show_bytes((byte_pointer) &x, sizeof(int)); 
}

void show_float(float x)//显示float型浮点数的存储方式 
{
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) 
{
    show_bytes((byte_pointer) &x, sizeof(void *));
}
/* $end show-bytes */


/* $begin test-show-bytes */
void test_show_bytes(int val)
 {
    int ival = val;
    //float fval = (float) ival;	//将ival从int型转化为float
	double fval = (double) ival;	//将ival从int型转化为double
    int *pval = &ival;
    printf("Stack variable ival = %d\n", ival);	//输出转换后ival的值
    printf("(int)ival:\n");
    show_int(ival);	//显示int型ival的存储方式
    printf("(float)ival:\n");
    show_float(fval);	//显示float型ival的存储方式
    printf("&ival:\n");
    show_pointer(pval);	//显示ival的地址
}
/* $end test-show-bytes */

//可判断机器是大端存储还是小端存储
void simple_show_a()
{
/* $begin simple-show-a */
int val = 0x87654321;
byte_pointer valp = (byte_pointer) &val;
show_bytes(valp, 1); /* A. */
show_bytes(valp, 2); /* B. */
show_bytes(valp, 3); /* C. */
/* $end simple-show-a */
}

void simple_show_b() 
{
/* $begin simple-show-b */
int val = 0x12345678;
byte_pointer valp = (byte_pointer) &val;
show_bytes(valp, 1); /* A. */
show_bytes(valp, 2); /* B. */
show_bytes(valp, 3); /* C. */
/* $end simple-show-b */
}

void float_eg() 
{
  int x = 3490593;
  float f = (float) x;	//将int型转化为float型
  printf("For x = %d\n", x);	//输出转化后的数值
  show_int(x);	//输出该数据为int型时的存储方式
  show_float(f);	//输出该数据为float型时的存储方式

  x = 3510593;
  f = (float) x;
  printf("For x = %d\n", x);
  show_int(x);
  show_float(f);
}

void string_ueg() 	//大写字母在计算机中的存储方式

{
/* $begin show-ustring */
const char *s = "ABCDEF";		//定义为const常量使之不允许被改变
show_bytes((byte_pointer) s, strlen(s)); 
/* $end show-ustring */
}

void string_leg()	//小写字母在计算机中的存储方式 
{
/* $begin show-lstring */
const char *s = "abcdef";
show_bytes((byte_pointer) s, strlen(s)); 
/* $end show-lstring */
}

void show_twocomp() 	//求一个数的补码
{
/* $begin show-twocomp */
    short x = 12345; 
    short mx = -x; 
    
    show_bytes((byte_pointer) &x, sizeof(short)); 
    show_bytes((byte_pointer) &mx, sizeof(short)); 
/* $end show-twocomp */
}

int main(int argc, char *argv[])
{
    int val = 12345;
    if (argc > 1) 	//输入测试数据
    {
        val = strtol(argv[1], NULL, 0);
		printf("calling test_show_bytes\n");
		test_show_bytes(val);
    } 
    else	//未输入测试数据
    {
		printf("calling show_twocomp\n");
		show_twocomp();
		printf("Calling simple_show_a\n");
		simple_show_a();
		printf("Calling simple_show_b\n");
		simple_show_b();
		printf("Calling float_eg\n");
		float_eg();
		printf("Calling string_ueg\n");
		string_ueg();
		printf("Calling string_leg\n");
		string_leg();
    }
    return 0;
}