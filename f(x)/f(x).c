#include <stdio.h>
#include <math.h>

int f(int x,int a[],int n)//定義函數f(x,a,n)
    {
        int sum=0;//sum初始化
        int i;
        for(i=0;i<n;i++)
        {
            sum=sum+a[i]*pow(x,i);//意思是sum+a陣列乘以x的i次方
        }
        return sum;//回傳sum，f(x,a,n)的值=sum
    }

int main()
{
    int n,x,i;
    int a[10];
    printf("\n請輸入n值:");
    scanf("%d",&n);

    for (i=0;i<n;i++)
    {
        printf("\n請輸入陣列元素:");
        scanf("%d",&a[i]);
    }

    printf("\n請輸入x值:");
    scanf("%d",&x);

    printf("\n計算結果f(x)=%d\n",f(x,a,n));//呼叫函數f(x,a,n)

    return 0;
}