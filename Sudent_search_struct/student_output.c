#include <stdio.h>
#include "student.h"

int main()
{
    FILE *fp;
    int search_ID;
    int found=0; //found用於判斷搜尋學號是否正確。
    fp=fopen("C:\\Users\\xxl53\\Desktop\\grade.txt","r"); //使用fopen開啟檔案，fopen("檔案路徑","指令r")
    
    if(fp==NULL) //如果檔案開啟回傳為NULL
    {
        printf("Err檔案開啟失敗!");
        return 0;
    }

    else
    {
        printf("搜尋學號: ");
        scanf("%d",&search_ID);

        while(fscanf(fp,"%s%d%d%d%d",student.name,&student.ID,&student.grade[0],&student.grade[1],&student.grade[2])!=EOF) //將所有資料讀一遍 name,ID,grade；EOF表示檔案結尾，也就是說fp檔案讀到結尾時會跳脫while迴圈。
        {
            if(student.ID==search_ID)
            {
                found=1; //注意found這時變成1，表示有搜尋到資料
                printf("姓名:%s\n",student.name);
                printf("學號: %d\n", student.ID);
                printf("成績: %d, %d, %d\n", student.grade[0], student.grade[1], student.grade[2]);
            }
        }
        
        if(found==0)
            {
                printf("找不到該名學生!!\n");
            }
    }

fclose(fp);
return 0;
}

