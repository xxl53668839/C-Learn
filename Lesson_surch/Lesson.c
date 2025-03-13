#include <stdio.h>

int main()
{
    int lesson[5][6]={{0,2,0,2,0}, //利用陣列建立5行6列課表
                      {1,4,1,4,1},
                      {5,0,5,0,5},
                      {0,0,0,0,0},
                      {3,0,3,0,3},
                      {0,0,0,0,0}};
    int week;
    int class;
    int class_No;
    int i,j;
    int sum;
    sum=0;

    TOP:printf("請輸入星期(1到5):");
        scanf("%d",&week);
        printf("\n");
        printf("請輸入第幾堂課(1到6):");
        scanf("%d",&class);

    while (week!=0 && class!=0)
    {
    class_No=lesson[week-1][class-1]; //因為電腦是從0開始，而使用者是從1開始，故減1
    switch(class_No)
    {
        case 0:printf("這節沒課\n"); //0表示沒有課程
            goto PLUS;
        case 1:printf("這節是:計算機概論\n"); //1表示計算機概論
            goto PLUS;
        case 2:printf("這節是:工程數學\n"); //2表示工程數學
            goto PLUS;
        case 3:printf("這節是:英文課\n"); //3表示英文課
            goto PLUS;
        case 4:printf("這節是:國文課\n"); //4表示國文課
            goto PLUS;
        case 5:printf("這節是:機電整合\n"); //4表示機電整合
            goto PLUS;
    }

  PLUS:for(i=0;i<5;i++) //for迴圈將5行資料抓出來
       for(j=0;j<6;j++) //for迴圈將6列資料抓出來

    if (lesson[i][j]!=0) //如果陣列某一格資料不為0，SUM就進1位
    {
        sum++;
    }

    printf("本週總計:%d節課\n",sum); 
    break;
    }
printf("程式結束\n");
return 0;
}

