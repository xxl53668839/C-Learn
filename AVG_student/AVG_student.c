#include <stdio.h>

float avg(float score[4][4], int n) //計算陣列內所有數值的平均，n是main傳回的值4
{
    float sum = 0;
    int i,j;
    for (i = 0; i < n; i++)  //外層迴圈將所有的行[4][[x]看一遍
    {
        for(j=0;j<n;j++) //內層迴圈將所有列[x][[4]看一遍
        {
        sum += score[i][j];  // 累加所有元素的值
        }

    }
    return sum / (n * n);  // 計算平均值並回傳
}

float avg1(float score[][4], int no) //計算單一個"no"學生的平均分數
{
    float sum = 0; 
    int i,j;
    for (i = 0; i < 4; i++) //將no學生的所有的分數看一遍
    {
        sum += score[no][i];  //累加no學生的所有的分數
    }
    return sum / 4; //計算平均值並回傳
}

int main()
{
    int no;
    float score[4][4] = {
        {76, 90, 92, 87}, //no0
        {68, 78, 69, 94}, //no1
        {89, 82, 81, 60}, //no2
        {87, 68, 60, 97}  //no3
    };

    printf("請輸入學生編號1~4:");
    scanf("%d", &no);
    no=no-1; //因為電腦是從0開始，而使用者是從1開始，故減1
    printf("\n學生%d的平均分數: %.2f\n", no+1, avg1(score,no));

    printf("所有學生平均分數: %.2f\n", avg(score,4));

    if (avg1(score, no) >= avg(score, 4)) //如果學生分數avg1的值大於全班分數avg的值
    {
        printf("學生%d的平均分數高於全班平均分數\n",no+1);
    }
    else
    {
        printf("學生%d的平均分數低於全班平均分數\n",no+1);
    }
    
    return 0;
}
