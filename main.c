/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ADC采集电压，DMA模式
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./adc/bsp_adc.h"
#include "Config.h"
#include "./tim/bsp_general_tim.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal; 


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
struct InfoStruct Info;
int main(void)
{
		Info.cnt=0;
		Info.flag=-1;
		Info.finish1=0;
		Info.finish2=0;
		/*初始化USART1*/
    Debug_USART_Config();
		LED_GPIO_Config();
		/* 初始化滑动变阻器用到的DAC，ADC数据采集完成后直接由DMA运输数据到ADC_ConvertedValue变量
				DMA直接改变ADC_ConvertedValue的值*/
    Rheostat_Init();
		DAC_Mode_Init();
		TIMx_Configuration();

    printf("\r\n ----这是一个ADC实验(DMA传输)----\r\n");
		//DAC_SetChannel1Data(DAC_Align_12b_R,4095);
		//DAC_SetChannel2Data(DAC_Align_12b_R,4095);
  //DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	//DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
		for(;;)LOOP();
}



/*********************************************END OF FILE**********************/

