#include<stdio.h>


#define MAX 1000

int b,c;
int lines[10];
int *a;
char f;
double hgj;
float hello;

void haha(int x,int y)
{
    printf("hellow waorld");

}

void hudai()
{
	int i;
    haha(4,10);
    b = 0;
	for(i=0; i<5; i++)
	{
		printf("hudai");
	}

}

void ajaira()

{

	lines[5] = 45;
    printf("%d",b);
	hudai();
}

int main()
{
	printf("Hello World");

	for(int i=0;i<10;i++){
		printf("my name is zim");
		if(MAX<i){
			printf("Impossible");
			hudai();
		}
	}
	ajaira();
	a=b;
	b=c;


	return 0;
}
