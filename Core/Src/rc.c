#include "rc.h"
#include "main.h"
#include "adc.h"
#include "oled_u8g2.h"
#include "com_rc.h"
#include "nrf24l01.h"

void RC_init(void)
{
  RK_init();
  
  while(NRF24L01_Check())
  {
    ERR_LOG("NRF24L01 check fail!\r\n"); 
    HAL_Delay(1000);
  }
	INF_LOG("NRF24L01 check done\r\n");
  NRF24L01_TX_Mode();
  INF_LOG("NRF24L01 tx mode\r\n");
}

uint16_t g_adc_raw_val[4];//缓存ADC采样值

void RK_init(void)
{
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_adc_raw_val, sizeof(g_adc_raw_val) / sizeof(g_adc_raw_val[0]));
}

void RK_get_xyzVal(void)
{ 
  INF_LOG("X = %d, Y = %d, Z = %d\r\n", g_adc_raw_val[0], g_adc_raw_val[1],HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4));
  // OLED_U8G2_draw_rocker_key(g_adc_raw_val[0],  g_adc_raw_val[1]);
}

rc_keys_t RC_get_keys(void)
{
  rc_keys_t r = {
    .rk_left = {
      .x = g_adc_raw_val[0],
      .y = g_adc_raw_val[1],
    },
    .rk_right = {
      .x = g_adc_raw_val[2],
      .y = g_adc_raw_val[3],
    },
    .key_left  = (uint8_t)HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin),
    .key_right = (uint8_t)HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin),
    .sw_left = {
      .sw_1 = (uint8_t)HAL_GPIO_ReadPin(SW1_1_GPIO_Port, SW1_1_Pin),
      .sw_2 = (uint8_t)HAL_GPIO_ReadPin(SW1_2_GPIO_Port, SW1_2_Pin),
      .sw_3 = (uint8_t)HAL_GPIO_ReadPin(SW1_3_GPIO_Port, SW1_3_Pin),
    },
    .sw_right = {
      .sw_1 = (uint8_t)HAL_GPIO_ReadPin(SW2_1_GPIO_Port, SW2_1_Pin),
      .sw_2 = (uint8_t)HAL_GPIO_ReadPin(SW2_2_GPIO_Port, SW2_2_Pin),
      .sw_3 = (uint8_t)HAL_GPIO_ReadPin(SW2_3_GPIO_Port, SW2_3_Pin),
    },
  };
  return r;
}

RC_MODE g_rc_mode= RC_KEYS;
void RC_control(void) 
{
  switch (g_rc_mode)
  {
  case RC_KEYS:
    {
      rc_keys_t rc_keys = RC_get_keys();
      // rc ={ // for test
      //   .rk_left = {
      //     .y = 4096,
      //     .z = 1,
      //   },
      //   .sw_left = {
      //     .sw_2 = 1,
      //   },
      //   .sw_right = {
      //     .sw_3 = 1,
      //   },
      //   .key_left = 1,
      // };
      OLED_U8G2_draw_rc_keys(&rc_keys);
      // assemble
        rc_data_t rc_data = {
        .rk_l_x = rc_keys.rk_left.x,
        .rk_l_y = rc_keys.rk_left.y,
        .rk_l_z = rc_keys.rk_left.z,

        .rk_r_x = rc_keys.rk_right.x,
        .rk_r_y = rc_keys.rk_right.y,
        .rk_r_z = rc_keys.rk_right.z,

        .key_l = rc_keys.key_left,
        .key_r = rc_keys.key_right,

        .sw_l_1 = rc_keys.sw_left.sw_1,
        .sw_l_2 = rc_keys.sw_left.sw_2,
        .sw_l_3 = rc_keys.sw_left.sw_3,
        .sw_r_1 = rc_keys.sw_right.sw_1,
        .sw_r_2 = rc_keys.sw_right.sw_2,
        .sw_r_3 = rc_keys.sw_right.sw_3,
      };
      uint8_t res = rc_data_encode(&rc_data);
      if(res) ERR_LOG("rc data encode fail: %d\r\n", res);
      // send
      // OLED_U8G2_draw_rc_com(&rc_data);
      if(NRF24L01_TxPacket(rc_data.buf)==TX_OK)
        INF_LOG("NRF24L01 send success\r\n");
      else
        ERR_LOG("NRF24L01 send fail!\r\n");
      }
    break;
  case RC_IMU:
    /* code */
    break;

  default:
    break;
  }
}
