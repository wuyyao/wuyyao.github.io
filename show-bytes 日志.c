/* show-bytes - prints byte representation of data */
/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
/* $begin show-bytes */

typedef unsigned char *byte_pointer;	/*unsigned char char��int�����з�                     						�ţ��޷��ź��ֽڳ������������չ*/
//typedef char *byte_pointer;
//typedef int *byte_pointer;

void show_bytes(byte_pointer start, size_t len) 
{
    size_t i;
    for (i = 0; i < len; i++)//�����ַ�
	printf("%p\t0x%.2x\n", &start[i], start[i]); //�õ��洢��ַ���ô洢��ַ����ַ�
    printf("\n");
}

void show_int(int x)//��ʾint�������Ĵ洢��ʽ
{
    show_bytes((byte_pointer) &x, sizeof(int)); 
}

void show_float(float x)//��ʾfloat�͸������Ĵ洢��ʽ 
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
    //float fval = (float) ival;	//��ival��int��ת��Ϊfloat
	double fval = (double) ival;	//��ival��int��ת��Ϊdouble
    int *pval = &ival;
    printf("Stack variable ival = %d\n", ival);	//���ת����ival��ֵ
    printf("(int)ival:\n");
    show_int(ival);	//��ʾint��ival�Ĵ洢��ʽ
    printf("(float)ival:\n");
    show_float(fval);	//��ʾfloat��ival�Ĵ洢��ʽ
    printf("&ival:\n");
    show_pointer(pval);	//��ʾival�ĵ�ַ
}
/* $end test-show-bytes */

//���жϻ����Ǵ�˴洢����С�˴洢
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
  float f = (float) x;	//��int��ת��Ϊfloat��
  printf("For x = %d\n", x);	//���ת�������ֵ
  show_int(x);	//���������Ϊint��ʱ�Ĵ洢��ʽ
  show_float(f);	//���������Ϊfloat��ʱ�Ĵ洢��ʽ

  x = 3510593;
  f = (float) x;
  printf("For x = %d\n", x);
  show_int(x);
  show_float(f);
}

void string_ueg() 	//��д��ĸ�ڼ�����еĴ洢��ʽ

{
/* $begin show-ustring */
const char *s = "ABCDEF";		//����Ϊconst����ʹ֮�������ı�
show_bytes((byte_pointer) s, strlen(s)); 
/* $end show-ustring */
}

void string_leg()	//Сд��ĸ�ڼ�����еĴ洢��ʽ 
{
/* $begin show-lstring */
const char *s = "abcdef";
show_bytes((byte_pointer) s, strlen(s)); 
/* $end show-lstring */
}

void show_twocomp() 	//��һ�����Ĳ���
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
    if (argc > 1) 	//�����������
    {
        val = strtol(argv[1], NULL, 0);
		printf("calling test_show_bytes\n");
		test_show_bytes(val);
    } 
    else	//δ�����������
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