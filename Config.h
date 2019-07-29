#ifndef _CONFIG_
#define _CONFIG_
#include "stm32f4xx.h"
#include "function.h"
#include "SDS.h"
#include "arm_math.h"
#include "./tim/bsp_general_tim.h"
#include "./led/bsp_led.h"  
#include "./dac/bsp_dac.h"
#include <string.h>
//#define LEN 1024
struct InfoStruct {
	uint16_t adcbuff1[1024];
	uint16_t dacbuff1[1024];
	uint16_t adcbuff2[1024];
	uint16_t dacbuff2[1024];
	//uint16_t buff[1024];
	uint16_t cnt;
	int8_t flag;
	int8_t finish1;
	int8_t finish2;
};



#endif

