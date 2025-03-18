#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 16 //限制記憶體大小為16byte
int MEMORY[MEMORY_SIZE]; //利用ARRY模擬建立一個記憶體

void memory_test(int *memory, int bit_set)  
{


    for (int i=0;i<MEMORY_SIZE;i++)
    {
        MEMORY[i]=bit_set;
    }

    for (int i=0;i<MEMORY_SIZE;i++)
    {
        if(MEMORY[i]==bit_set)
        {
            printf("測試成功! memory=%#x\n",MEMORY[i]);
        }
        else
        {
            printf("測試失敗! memory=%#x\n",MEMORY[i]);
        }
    }
}

int main()
{
    int *MEMORY = (int *)malloc(MEMORY_SIZE); //分配動態記憶體

    if(MEMORY==NULL)
    {
        printf("記憶體分配失敗");
        return 1;
    }

    printf("開始執行測試1，對記憶體寫入0x55\n");
    memory_test(MEMORY,0x55);
    printf("\n開始執行測試2，對記憶體寫入0xAA\n");
    memory_test(MEMORY,0xAA);

    free(MEMORY);
    printf("\n記憶體已釋放\n");
    return 0;
}