#include <stdio.h>

int main() {
    int num;
    printf("請輸入一個數字 (輸入 0 結束):\n");
    scanf("%d", &num); //輸入一個數字並存入 num

    while (num != 0)   //當 num 不等於 0 時執行迴圈
    {
        if (num % 2 == 0) //判斷 num 是否為偶數
        {
            printf("%d 是偶數\n", num); //是偶數則印出
        } 
        else //否則為奇數
        {
            printf("%d 是奇數\n", num);  
        }
        printf("請輸入一個數字 (輸入 0 結束):\n"); 
        scanf("%d", &num); //再次輸入一個數字並存入 num
    }

    printf("程式結束。\n");
    return 0;
}


