#include <stdio.h>
    int main()
{
    int nurse,val;
    int *ptr;
    nurse=22;
    ptr=&nurse; // ptr = nurse 的地址，&nurse = nurse 的地址
    val=*ptr;   // val = ptr 指向的值，又即 nurse 的變數值

printf("ptr=%x,address of nurse=%x,ptr=%d\n",ptr,&nurse,*ptr);
printf("val=%d\n",val);

return 0;
}
