#ifndef __ROCKER_KEY_H_
#define __ROCKER_KEY_H_	

#include "main.h"

typedef struct 
{
  uint16_t x;
  uint16_t y;
  uint8_t  z;
}rc_rk_t;

typedef struct 
{
  uint8_t sw_1;
  uint8_t sw_2;
  uint8_t sw_3;
}rc_sw_t;

typedef struct 
{
  rc_rk_t rk_left;
  rc_rk_t rk_right;

  uint8_t key_left;
  uint8_t key_right;

  rc_sw_t sw_left;
  rc_sw_t sw_right;
}rc_keys_t;

typedef enum {
  RC_KEYS = 0u,
  RC_IMU,
}RC_MODE;

void RK_init(void);
void RK_get_xyzVal(void);

void RC_init(void);
rc_keys_t RC_get_keys(void);
void RC_control(void);



#endif
