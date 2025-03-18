#include <stdio.h>
#include "student.h"

int main()
{
    FILE *fp;
    int n; //n是用於使用者自定義輸入筆數
    int i,j; //i,j用於跑for迴圈
    fp=fopen("C:\\Users\\USER\\Desktop\\grade.txt","w"); //使用fopen開啟檔案，fopen("檔案路徑",指令"w")

    if(fp==NULL) 
    {
        printf("Err檔案啟動失敗");
        return 0;
    }
    else
    {
        printf("\n請輸入資料筆數: ");
        scanf("%d",&n);
            if(n>NAME)
            {
                printf("Err超過最大限值!!");
                return 1;
            }
    
    
        for(i=0;i<n;i++)
        {
            printf("\n請輸入姓名: ");
            scanf("%s",name); //注意%s字串不用加入'&'
            
            printf("\n請輸入學號: ");
            scanf("%d",&ID);
            fprintf(fp,"%s %d ",name,ID); //每一格內容都要空格!!很重要!!不然資料格式會錯誤!!
     
            for(j=0;j<CLASS;j++)
            {
                printf("\n請輸入3科成績: ");
                scanf("%d",&grade[j]);
                if(grade[j]>=100)
                {
                    printf("Err超過最大限值!!");
                    return 1;
                }
                fprintf(fp,"%d ",grade[j]);
            }
            fprintf(fp,"\n"); //每一筆資料都要分行!!
        }
    }
    fclose(fp);
    printf("已儲存%d筆資料",n);
    return 0;
}