#include <stdio.h>

int main()

    //輸入一個整數，判斷其為奇數或偶數。
{

int num;
    printf("請輸入任意數字: ");
    scanf("%d",&num);

    while(num!=0) //while的用法:1.先列出條件(當num不等於0時進入迴圈) 2.大括號內執行條件if或else
    {
        if (num%2==0) //如果num的餘數等於0時
        {
            printf("%d為偶數\n",num); //顯示為偶數
            
        }

        else //反之
        {
            printf("%d為奇數\n",num); //顯示為奇數
        }

    printf("請輸入任意數字: ");
    scanf("%d",&num); //if或else執行完畢後，再次輸入數字
    printf("輸入0可退出程式\n");

    }

    printf("程式結束\n");
return 0;

}
