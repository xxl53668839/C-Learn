#include <stdio.h>

int main()
{
    int X,Y;
    int W=320;
    int H=240;
    int L=10,T=10,R=100,B=200;

    while(1)//無限迴圈
    {
        printf("\n");
        printf("請輸入X的座標:\n");
        scanf("%d",&X); //輸入X座標

        printf("請輸入Y的座標:\n");
        scanf("%d",&Y); //輸入Y座標

    if (X==0&&Y==0) //如果XY都等於0時
        {
            break; //跳出最近一個迴圈，結束程式
        }

    if((X>W)||(Y>H)) //如果X大於W或Y大於H時
        {
            printf("Err"); //顯示Err
            continue;
        }

    if ((X>=L)&&(X<=R)&&(Y>=T)&&(Y<=B)) //如果X大於等於10，且X小於等於100，且Y大於等於10，，且Y小於等於200時

            {
            printf("%d,%d在矩形內!!\n",X,Y);
            printf("輸入0,0可退出程式。\n");
            }
    else
            {
            printf("%d,%d不在矩形內!!\n",X,Y);
            printf("輸入0,0可退出程式。\n");
            }
        }

printf("程式結束");
return 0;
}
