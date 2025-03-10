#include <stdio.h>
void recu(int); //宣告函數:recu，並且宣告函數的參數為整數型態(int)

int main()

{
    recu(1); //呼叫函數recu，並且傳入1
    return 0;
}

void recu(int n) //(int n)是函數的參數n，並接收上方傳入的1
{
    printf("等級%d\n",n);
    if(n<4) //n接收到1，所以n小於4，所以進入迴圈
    {
        recu(n+1);
        printf("等級%d\n",n);
    }
}
