#include "vib_motor.h"

void VIBMOTOR_init(void)
{
  VIBMOTOR_vibrate_long_off();
}

void VIBMOTOR_vibrate_once(void)
{
  VIBMOTOR_vibrate_long_on();
  HAL_Delay(VIBRATE_INTERVAL);
  VIBMOTOR_vibrate_long_off();
}

void VIBMOTOR_vibrate_twice(void)
{
  VIBMOTOR_vibrate_long_on();
  HAL_Delay(VIBRATE_INTERVAL);
  VIBMOTOR_vibrate_long_off();
  HAL_Delay(VIBRATE_INTERVAL);
  VIBMOTOR_vibrate_long_on();
  HAL_Delay(VIBRATE_INTERVAL);
  VIBMOTOR_vibrate_long_off();
}

void VIBMOTOR_vibrate_long_on(void)
{
  HAL_GPIO_WritePin(VIB_MOTOR_GPIO_Port, VIB_MOTOR_Pin, GPIO_PIN_SET);
}

void VIBMOTOR_vibrate_long_off(void)
{
  HAL_GPIO_WritePin(VIB_MOTOR_GPIO_Port, VIB_MOTOR_Pin, GPIO_PIN_RESET);
}
