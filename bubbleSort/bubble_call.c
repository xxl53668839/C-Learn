#include <stdio.h>

void bubble(int data[],int n) //一個函數，用來排序data陣列內的數值
{
    int i,j,temp; //宣告變數i,j,temp
    for(i=0;i<n-1;i++) //外迴圈，用來比較data陣列內的數值
    {
        for(j=0;j<n-1-i;j++) //內迴圈，用來比較data陣列內的數值
        {
            if(data[j]>data[j+1]) //如果data[j]的數值大於data[j+1]的數值，則交換
            {
                temp=data[j]; 
                data[j]=data[j+1]; //交換data[j]和data[j+1]的數值
                data[j+1]=temp; 
            }
        } 
    }   
}


int main()
{
    int data[50];
    int i,j,n;

    printf("請輸入陣列data的最大數量:");
    scanf("%d",&n);
    
    for(i=0;i<n;i++)
    {
        printf("請輸入data陣列內的數值:");
        scanf("%d",&data[i]);
    }

    bubble(data,n);
       
    printf("排序結果:");
    for(i=0;i<n;i++)
    {
        printf("%d",data[i]);
    }

    return 0;
}