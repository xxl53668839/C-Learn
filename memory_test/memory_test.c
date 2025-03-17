#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 16 //限制記憶體大小為16byte
int MEMORY[MEMORY_SIZE]; //利用ARRY模擬建立一個記憶體

void memory_test0() //記憶體寫入0x55測試
{
    for (int i=0;i<MEMORY_SIZE;i++)
    {
        MEMORY[i]=0x55;
    }

    for (int i=0;i<MEMORY_SIZE;i++)
    {
        if(MEMORY[i]==0x55)
        {
            printf("測試0測試成功! memory=%#x\n",MEMORY[i]);
        }
        else
        {
            printf("測試0測試失敗! memory=%#x\n",MEMORY[i]);
        }
    }
}

void memory_test1()
{
    for (int i=0;i<MEMORY_SIZE;i++)
    {
        MEMORY[i]=0xAA;
    }

    for (int i=0;i<MEMORY_SIZE;i++)
    {
        if(MEMORY[i]==0xAA)
        {
            printf("測試1測試成功! memory=%#x\n",MEMORY[i]);
        }
        else
        {
            printf("測試1測試失敗! memory=%#x\n",MEMORY[i]);
        }
    }
}

int main()
{
    printf("開始執行測試0，對記憶體寫入0x55\n");
    memory_test0();
    printf("\n開始執行測試1，對記憶體寫入0xAA\n");
    memory_test1();
    return 0;
}