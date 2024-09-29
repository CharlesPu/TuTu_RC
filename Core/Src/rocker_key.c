#include "rocker_key.h"
#include "main.h"
#include "adc.h"
#include "oled_u8g2.h"

uint16_t g_iAdcx[2];//缓存ADC采样值

void RK_init(void)
{
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_iAdcx, sizeof(g_iAdcx) / sizeof(g_iAdcx[0]));
}

void RK_get_xyzVal(void)
{ 
  INF_LOG("X = %d, Y = %d, Z = %d\r\n", g_iAdcx[0], g_iAdcx[1],HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4));
  // OLED_U8G2_draw_rocker_key(g_iAdcx[0],  g_iAdcx[1]);
}

