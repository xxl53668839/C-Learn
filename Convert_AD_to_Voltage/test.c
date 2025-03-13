#include "AD.h"

int main()
{
 int AD[SAMPLEING_DATA_NO] = {700,732,680,500,820,702,693,717,704,699}  ;
 float voltage ;
 
 voltage = convert_AD_to_Voltage(AD,SAMPLEING_DATA_NO) ;
 printf("Voltage = %1.3fV\n",voltage) ;

 getchar() ;
}
