#include <stdio.h>
#include "AD.h"


/***************************************************************
	Function: convert_AD_to_Voltage
***************************************************************/
float convert_AD_to_Voltage(int AD_Value[],int data_no) 
{
 float voltage_value ;
 float adv_AD_Value ;
 
 adv_AD_Value = calculate_adv_and_skip2data(AD_Value,data_no) ; 
 
 // AD vaalue ==> voltage
 voltage_value = MAX_VOLTAGE_VALUE * adv_AD_Value / (float)MAX_AD_VALUE ;

 return voltage_value ;
}


/***************************************************************
	Function: convert_AD_to_Voltage
***************************************************************/
float calculate_adv_and_skip2data(int data[],int data_no) 
{
 int max_value = data[0] ;
 int min_value = data[0] ;
	
 int max_index = 0 ;
 int min_index = 0 ;

 int i ;
 int sum = 0 ;
 float adv_value ;

 // get index of MAX & Min value 
 for(i=1;i<data_no;i++)
 {
 		if(data[i] > max_value)
 		{
 			max_value = data[i] ;	
 			max_index = i ;
 		} 
 	
 		if(data[i] < min_value)
 		{
 			min_value = data[i] ;	
 			min_index = i ;
 		} 
 }	
 
 #ifdef DEBUG_VERSION
 printf("\nSkip MAX data: index = %d, value = %d\n",max_index,max_value) ;
 printf("Skip MIN data: index = %d, value = %d\n\n",min_index,min_value) ;
 #endif
 
 // calculate average value
 if(max_index == min_index)
 {
 			adv_value = data[0] ;
 }
 else
 {
		 for(i=0;i<data_no;i++)
		 {
				if(i == max_index || i == min_index)
					continue ; 			
		 	
		 		sum += data[i] ;
		 }
		 
		 adv_value = (float)(sum)/(data_no-2) ;
 }
 
 return adv_value ; 	
}

