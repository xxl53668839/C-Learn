#ifndef AD_HHHH 
#define AD_HHHH

#include <stdio.h>

#define DEBUG_VERSION

#define MAX_AD_VALUE 1024
#define MAX_VOLTAGE_VALUE 3.3f

#define SAMPLEING_DATA_NO 10


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  PUBLIC Function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float convert_AD_to_Voltage(int AD_Value[],int data_no) ;  //


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  PRIVATE Function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float calculate_adv_and_skip2data(int AD_Value[],int data_no) ;

#endif
