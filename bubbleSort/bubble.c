#include <stdio.h>
int main() {
    int data[5];//限制陣列數量為5
    int n;  // 陣列的總數
    int i,j,temp; //演算法用的宣告

    printf("請輸入數量: ");
    scanf("%d",&n);

    if(n>5)
    {
        printf("輸入數量超過陣列數量");
        return 0;
    }


    for(i=0;i<n;i++)
        {
            printf("請輸入數字");
            scanf("%d",&data[i]); //將輸入的數字存入data[i]中
        }


    for (i=0; i <n-1;i++) //n 是總數量，假如n=5，共只會比較4回合，也就是說會比較N-1回合
        {
            for (j=0;j<n-1-i; j++) //i是回合數，所以比較的次數會限制在(N-1-i)*i回合次數內
                {
                    if (data[j] > data[j + 1]) //例如:第一格5>第二格2時,5和2位置交換
                        {
                            // 交換相鄰元素
                            temp = data[j]; //將data[j]移動到暫存區temp
                            data[j] = data[j + 1]; //將data[j]右移一格
                            data[j + 1] = temp;  //原本右邊的值覆蓋於暫存區temp
            }
        }
    }

    printf("\n排序結果: ");
    for (int i = 0; i < n; i++)
        {
            printf("%d ",data[i]);
        }

    return 0;
}