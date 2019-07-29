/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ADC�ɼ���ѹ��DMAģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./adc/bsp_adc.h"
#include "Config.h"
#include "./tim/bsp_general_tim.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal; 


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
struct InfoStruct Info;
int main(void)
{
		Info.cnt=0;
		Info.flag=-1;
		Info.finish1=0;
		Info.finish2=0;
		/*��ʼ��USART1*/
    Debug_USART_Config();
		LED_GPIO_Config();
		/* ��ʼ�������������õ���DAC��ADC���ݲɼ���ɺ�ֱ����DMA�������ݵ�ADC_ConvertedValue����
				DMAֱ�Ӹı�ADC_ConvertedValue��ֵ*/
    Rheostat_Init();
		DAC_Mode_Init();
		TIMx_Configuration();

    printf("\r\n ----����һ��ADCʵ��(DMA����)----\r\n");
		//DAC_SetChannel1Data(DAC_Align_12b_R,4095);
		//DAC_SetChannel2Data(DAC_Align_12b_R,4095);
  //DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	//DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
		for(;;)LOOP();
}



/*********************************************END OF FILE**********************/

