#include <stdio.h>

//九九乘法表
int main()
{
int i,j;
    
for (i=1;i<=9;i++) 
    {
        for(j=1;j<=9;j++)
            {
                printf("%dx%d=%d\n",i,j,i*j);
            }
    }
    return 0;
} 