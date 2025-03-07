#include <stdio.h>
int main()
{
    unsigned short crc=0xFFFF;
    unsigned short i;
    unsigned short data;
   
    printf("請輸入16進制:");
    scanf("%x",&data);
   for (i=0; i<16; i++)
    {
        if ((data^crc)&0x0001)
            {
                crc = (crc>>1)^0x8408; 
            }
        else
            {
                crc = crc>>1;
            }
    }
    printf("CRC值: %#x\n",crc);
printf("程式結束\n");
return 0;
}
