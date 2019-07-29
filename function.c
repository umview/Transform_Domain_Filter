#include "function.h"
#include "./usart/bsp_debug_usart.h"
#include "arm_math.h"
#include "arm_const_structs.h"
//#define TEST_LENGTH_SAMPLES 2048
extern struct InfoStruct Info;
extern volatile uint16_t buff;
extern float data[4];

/************************FOR FFT*************************/
#define LEN 1024
float input[LEN*2];
float output[LEN*2];
float mag[LEN];
uint16_t tmp[LEN];
void Process1(void){
	uint16_t i=0;
	for(i=0;i<LEN;i++){
		input[i*2]=Info.adcbuff1[i];
		input[i*2-1]=0;
	}
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 0, 1);
	Filter();
	//arm_cmplx_mag_f32(input, mag, LEN);


	arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 1, 1);
//		for(i=0;i<LEN;i++){
////		Info.dacbuff1[i]=(uint16_t)input[i*2];
////		data[0]=(int16_t)(Info.dacbuff1[i]);
//		data[1]=i;
////		data[2]=tmp[i];
//		data[3]=(int16_t)(input[2*i]);
//		Plot(data);
//	}
//	for(;;);
	for(i=0;i<LEN;i++){
		Info.dacbuff1[i]=(uint16_t)input[i*2];
//		data[0]=(int16_t)(Info.dacbuff1[i]);
//		data[1]=i;
//		data[2]=Info.adcbuff1[i];
//		Plot(data);
	}
//	for(i=0;i<LEN;i++){
//		data[0]=(int16_t)(output[i]);
//		data[1]=i;
//		data[2]=Info.adcbuff[i];
//		Plot(data);
//	}
}
void Process2(void){
	uint16_t i=0;
	for(i=0;i<LEN;i++){
		input[i*2]=Info.adcbuff2[i];
		input[i*2-1]=0;
	}
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 0, 1);
	Filter();
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 1, 1);
	//arm_cmplx_mag_f32(input, output, LEN);
	for(i=0;i<LEN;i++){
		Info.dacbuff2[i]=(uint16_t)input[i*2];
//		data[0]=(int16_t)(Info.dacbuff2[i]);
//		data[1]=i;
//		data[2]=Info.adcbuff2[i];
//		Plot(data);
	}
//	for(i=0;i<LEN;i++){
//		data[0]=(int16_t)(output[i]);
//		data[1]=i;
//		data[2]=Info.buff2[i];
//		Plot(data);
//	}
}


/********************************************************/
void Delay(__IO u32 nCount); 
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
void  TIM3_IRQHandler (void)
{
  
  if (((TIM3->SR & TIM_IT_Update)!= (uint16_t)RESET) && ((TIM3->DIER & TIM_IT_Update)!= (uint16_t)RESET))
  {
				GPIOI->ODR ^= GPIO_Pin_8;
				if(Info.flag==-1){
						Info.adcbuff1[Info.cnt]=buff;//&0x0fff;
					//for ifft
						*(__IO uint32_t *)(((uint32_t)0x40000000)+0x7400+((uint32_t)0x00000008) + ((uint32_t)0x00000004))=Info.dacbuff1[Info.cnt++];
					//for raw data
						*(__IO uint32_t *)(((uint32_t)0x40000000)+0x7400+((uint32_t)0x00000014) + ((uint32_t)0x00000004))=buff;

					if(Info.cnt>LEN-1)Info.flag*=-1,Info.finish1=0,Info.cnt=0;
				}else{
						Info.adcbuff2[Info.cnt]=buff;//&0x0fff;
					//for ifft
						*(__IO uint32_t *)(((uint32_t)0x40000000)+0x7400+((uint32_t)0x00000008) + ((uint32_t)0x00000004))=Info.dacbuff2[Info.cnt++];
					//for raw data							
					*(__IO uint32_t *)(((uint32_t)0x40000000)+0x7400+((uint32_t)0x00000014) + ((uint32_t)0x00000004))=buff;
	
					if(Info.cnt>LEN-1)Info.flag*=-1,Info.finish2=0,Info.cnt=0;
				}
				//Info.adcbuff[Info.cnt]=buff;//&0x0fff;
				//DAC_SetChannel1Data(DAC_Align_12b_L,buff);
				//*(__IO uint32_t *)(((uint32_t)0x40000000)+0x7400+((uint32_t)0x00000008) + ((uint32_t)0x00000004))=Info.dacbuff[Info.cnt++];
				//if(Info.cnt>LEN-1)TIM3->CR1 &= (uint16_t)~TIM_CR1_CEN;
				//Info.cnt=Info.cnt>1023?0:Info.cnt;
				//if(Info.cnt>LEN-1)Info.flag*=-1,Info.cnt=0;
				TIM3->SR = (uint16_t)~TIM_FLAG_Update;
  }
}
uint16_t i=0;
void LOOP(){
				//	GPIOI->ODR ^= GPIO_Pin_8;

	if(Info.flag==1&&Info.finish1==0){
//		for(i=0;i<1023;i++){
//			data[0]=Info.adcbuff[i];
//			Plot(data);
//		}
		Process1();
		Info.finish1=1;
	}else if(Info.flag==-1&&Info.finish2==0){
		Process2();
		Info.finish2=1;
	}
			//	GPIOI->ODR ^= GPIO_Pin_8;

}
#define CutoffHz 100000.0f
void Filter(void){
	memset(&input[(uint16_t)(CutoffHz/(1000000.0f/LEN))*2],0,(uint16_t)(LEN*2-(uint16_t)(CutoffHz/(1000000.0f/LEN))*4+1)*sizeof(float));
}
