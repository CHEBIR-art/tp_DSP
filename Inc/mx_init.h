
#ifndef MX_INIT_H_
#define MX_INIT_H_

void SystemClock_Config(void);
void MX_DMA2D_Init(void);
void MX_I2C3_Init(void);
void MX_LTDC_Init(void);
void MX_SAI2_Init(void);
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM5_Init(void);
void MX_TIM8_Init(void);
void MX_TIM12_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART6_UART_Init(void);
void MX_FMC_Init(void);
void MX_GPIO_Init(void);
void initGpio(void);
void lcd_start_page(void);
void BOARD_Init(void);

#endif
