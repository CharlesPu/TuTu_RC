#include "rc.h"
#include "main.h"
#include "adc.h"
#include "oled_u8g2.h"
#include "com_rc.h"
#include "nrf24l01.h"

void RC_init(void)
{
  RK_init();
#ifdef MODULE_NRF24L01_TX
  NRF24L01_init();
#endif
}

uint16_t g_adc_raw_val[4];//缓存ADC采样值

void RK_init(void)
{
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_adc_raw_val, sizeof(g_adc_raw_val) / sizeof(g_adc_raw_val[0]));
}

void RK_get_xyzVal(void)
{ 
  // INF_LOG("X1 = %d, Y1 = %d\r\n", g_adc_raw_val[0], g_adc_raw_val[1]);
  INF_LOG("X1 = %d, Y1 = %d, X2 = %d, Y2 = %d\r\n", g_adc_raw_val[0], g_adc_raw_val[1], g_adc_raw_val[2], g_adc_raw_val[3]);
  OLED_U8G2_draw_rocker_key(g_adc_raw_val[0],  g_adc_raw_val[1]);
  // OLED_U8G2_draw_rocker_key(g_adc_raw_val[0], g_adc_raw_val[1]);
}

rc_keys_t RC_get_keys(void)
{
  rc_keys_t r = {
    .rk_left = {
      .x = g_adc_raw_val[0],
      .y = g_adc_raw_val[1],
      .z = !(uint8_t)HAL_GPIO_ReadPin(RK1_Z_GPIO_Port, RK1_Z_Pin),
    },
    .rk_right = {
      .x = g_adc_raw_val[2],
      .y = g_adc_raw_val[3],
      .z = !(uint8_t)HAL_GPIO_ReadPin(RK2_Z_GPIO_Port, RK2_Z_Pin),
    },
    .key_left  = !(uint8_t)HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin),
    .key_right = !(uint8_t)HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin),
    .sw_left = {
      .sw_1 = !(uint8_t)HAL_GPIO_ReadPin(SW1_1_GPIO_Port, SW1_1_Pin),
      .sw_2 = !(uint8_t)HAL_GPIO_ReadPin(SW1_2_GPIO_Port, SW1_2_Pin),
      .sw_3 = !(uint8_t)HAL_GPIO_ReadPin(SW1_3_GPIO_Port, SW1_3_Pin),
    },
    .sw_right = {
      .sw_1 = !(uint8_t)HAL_GPIO_ReadPin(SW2_1_GPIO_Port, SW2_1_Pin),
      .sw_2 = !(uint8_t)HAL_GPIO_ReadPin(SW2_2_GPIO_Port, SW2_2_Pin),
      .sw_3 = !(uint8_t)HAL_GPIO_ReadPin(SW2_3_GPIO_Port, SW2_3_Pin),
    },
  };
  return r;
}

RC_MODE g_rc_mode= RC_KEYS; // 没用到
void RC_control(imu_data_t* imu_data, rc_keys_t *rc_keys) 
{
  switch (g_rc_mode)
  {
  case RC_KEYS:
    {
      // OLED_U8G2_draw_rc_keys(rc_keys);
      // assemble
        rc_data_t rc_data = {
        .rk_l_x = rc_keys->rk_left.x,
        .rk_l_y = rc_keys->rk_left.y,
        .rk_l_z = rc_keys->rk_left.z,

        .rk_r_x = rc_keys->rk_right.x,
        .rk_r_y = rc_keys->rk_right.y,
        .rk_r_z = rc_keys->rk_right.z,

        .key_l = rc_keys->key_left,
        .key_r = rc_keys->key_right,

        .sw_l_1 = rc_keys->sw_left.sw_1,
        .sw_l_2 = rc_keys->sw_left.sw_2,
        .sw_l_3 = rc_keys->sw_left.sw_3,
        .sw_r_1 = rc_keys->sw_right.sw_1,
        .sw_r_2 = rc_keys->sw_right.sw_2,
        .sw_r_3 = rc_keys->sw_right.sw_3,

        .imu_pitch = imu_data->pitch,
        .imu_roll  = imu_data->roll,
        .imu_yaw   = imu_data->yaw,
      };
      uint8_t res = rc_data_encode(&rc_data);
      if(res) ERR_LOG("rc data encode fail: %d\r\n", res);
      // send
      // OLED_U8G2_draw_rc_com(&rc_data);
#ifdef MODULE_NRF24L01_TX
      if(NRF24L01_TxPacket(rc_data.buf)==TX_OK)
        {
          // INF_LOG("NRF24L01 send success\r\n");
        }
      else
        ERR_LOG("NRF24L01 send fail!\r\n");
#endif
      }
    break;
  case RC_IMU:
    /* code */
    break;

  default:
    break;
  }
}
