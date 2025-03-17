#include <stdio.h>

int recu(int n) //(int n)是函數的參數n，並接收main傳入的1
{
    int i;
    for(i=0;i<=4;i++) //n接收到1，所以n小於4，所以進入迴圈
        {
            n=n+1;
            printf("等級%d\n",n);
        }
    return n;
}

int main()
{
    recu(0);
    return 0;
}
