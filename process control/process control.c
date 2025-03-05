#include <stdio.h>

int main()

    //輸入一個整數，判斷其為奇數或偶數。
{

int num;
    printf("請輸入任意數字: \n");
    scanf("%d",&num);

    while(num!=0) //當num不等於0時進入迴圈
    {
        if (num%2==0) //如果num的餘數等於0時
        {
            printf("%d為偶數",num); //顯示為偶數
        }

        else //反之
        {
            printf("%d為奇數",num); //顯示為奇數
        }

    printf("請輸入任意數字: \n");
    printf("輸入0可退出程式\n");
    scanf("%d",&num); //if或else執行完畢後，再次輸入數字

    }

    printf("程式結束\n");
return 0;

}
