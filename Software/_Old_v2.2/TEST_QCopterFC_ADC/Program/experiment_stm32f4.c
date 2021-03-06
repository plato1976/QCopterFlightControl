/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
#include "experiment_stm32f4.h"
#include "module_rs232.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  u16 ADC_AVE[2] = {0};

  SystemInit();
  GPIO_Config();
  ADC_Config();
  RS232_Config();

  while(1) {
    LED_G = !LED_G;
    Delay_100ms(1);
    ADC_Average(ADC_AVE, 128);
    RS232_SendStr((u8*)"\f");
    RS232_SendStr((u8*)"ADC_I = ");
    RS232_SendNum(Type_D, 4, ADC_AVE[0]);
    RS232_SendStr((u8*)"\r\n");
    RS232_SendStr((u8*)"ADC_V = ");
    RS232_SendNum(Type_D, 4, ADC_AVE[1]);
    RS232_SendStr((u8*)"\r\n");
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);

  /* LED_R PC13 */  /* LED_G PC14 */  /* LED_B PC15 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
