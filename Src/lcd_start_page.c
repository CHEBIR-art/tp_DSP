#include "stdio.h"
#include "math.h"
#include "stm32746g_discovery.h"
//#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_audio.h"
#include "stlogo.h"

void lcd_start_page(void);

void lcd_start_page(void){
 	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FRAME_BUFFER);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
    BSP_LCD_DisplayStringAt(0, 10, (uint8_t *)"STM32F746G DSP", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 35, (uint8_t *)"Master ESET", CENTER_MODE);

    /* Draw Bitmap */
     //BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80) / 2, 65, (uint8_t *)logo_usmb);
     BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80) / 2, 65, (uint8_t *)stlogo);
     BSP_LCD_SetFont(&Font12);
     BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 20, (uint8_t *)"Copyright (c) Master ESET", CENTER_MODE);

     BSP_LCD_SetFont(&Font16);
     BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
     BSP_LCD_FillRect(0, BSP_LCD_GetYSize() / 2 + 15, BSP_LCD_GetXSize(), 60);
     BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
     BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
     //BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 + 30, (uint8_t *)"Press User Button to start :", CENTER_MODE);
}


