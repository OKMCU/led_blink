#include <stdio.h>
#include <stdint.h>

/* LL drivers common to all LL examples */
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_utils.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_exti.h"
#include "stm32l0xx_ll_gpio.h"
/* LL drivers specific to LL examples IPs */
#include "stm32l0xx_ll_adc.h"
#include "stm32l0xx_ll_comp.h"
#include "stm32l0xx_ll_cortex.h"
#include "stm32l0xx_ll_crc.h"
#include "stm32l0xx_ll_dac.h"
#include "stm32l0xx_ll_dma.h"
#include "stm32l0xx_ll_lptim.h"
#include "stm32l0xx_ll_i2c.h"
#include "stm32l0xx_ll_iwdg.h"
#include "stm32l0xx_ll_rtc.h"
#include "stm32l0xx_ll_spi.h"
#include "stm32l0xx_ll_tim.h"
#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_wwdg.h"
#include "stm32l0xx_ll_crs.h"
#include "stm32l0xx_ll_lpuart.h"
#include "stm32l0xx_ll_rng.h"

/* Private function implementations ------------------------------------------*/
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = 4
  *            PLLDIV                         = 2
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
static void SystemClock_Config( void )
{
    LL_FLASH_EnablePreRead();
    LL_FLASH_EnablePrefetch();
     
    /* Enable Power Control clock */
    LL_APB1_GRP1_EnableClock( LL_APB1_GRP1_PERIPH_PWR );
    
    /* The voltage scaling allows optimizing the power consumption when the device is 
       clocked below the maximum system frequency, to update the voltage scaling value 
       regarding system frequency refer to product datasheet.  */
    LL_PWR_SetRegulVoltageScaling( LL_PWR_REGU_VOLTAGE_SCALE1 );
    /* Disable Power Control clock */
    LL_APB1_GRP1_DisableClock( LL_APB1_GRP1_PERIPH_PWR );
    
    /* Enable HSI Oscillator */
    LL_RCC_HSI_Enable();
    while( !LL_RCC_HSI_IsReady() );
    
    LL_RCC_HSI_SetCalibTrimming( 16 );
    LL_RCC_PLL_ConfigDomain_SYS( LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_4, LL_RCC_PLL_DIV_2 );
    LL_RCC_PLL_Enable();
    while( !LL_RCC_PLL_IsReady() );

    LL_RCC_LSI_Enable();
    while( !LL_RCC_LSI_IsReady() );

    LL_FLASH_SetLatency( LL_FLASH_LATENCY_1 );              // Range 1 (1.65V~1.95V), 32MHz, Flash latency should be set to 1
                                                            // Refer to RM0377, section 3.7.1.
    LL_RCC_SetSysClkSource( LL_RCC_SYS_CLKSOURCE_PLL );     // Use PLL output as SYSCLK
    LL_RCC_SetAHBPrescaler( LL_RCC_SYSCLK_DIV_1 );          // HCLK 32MHz
    LL_RCC_SetAPB1Prescaler( LL_RCC_APB1_DIV_1 );           // APB1 CLK 32MHz
    LL_RCC_SetAPB2Prescaler( LL_RCC_APB2_DIV_1 );           // APB2 CLK 32MHz
}


int main(void)
{
    SystemClock_Config();
    SysTick_Config( 32000 );
    LL_IOP_GRP1_EnableClock( LL_IOP_GRP1_PERIPH_GPIOA );
    LL_IOP_GRP1_EnableClock( LL_IOP_GRP1_PERIPH_GPIOB );
    LL_IOP_GRP1_EnableClock( LL_IOP_GRP1_PERIPH_GPIOC );
    
    LL_GPIO_SetPinPull( GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_NO );
    LL_GPIO_SetPinMode( GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT );
    LL_GPIO_SetPinOutputType( GPIOB, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL );
    
    while(1)
    {
    
    }
}