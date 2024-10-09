#ifndef __OLED_U8G2_H_
#define __OLED_U8G2_H_	

#include "main.h"
#include "u8g2.h"
#include "mpu6050.h"
#include "com_rc.h"
#include "rc.h"


#define MAX_LEN    128  //
#define OLED_ADDRESS  0x78 // oled
#define OLED_CMD   0x00  // 
#define OLED_DATA  0x40  // 
 
void testDrawProcess(u8g2_t *u8g2);
void testShowFont(u8g2_t *u8g2);
void testDrawFrame(u8g2_t *u8g2);
void testDrawRBox(u8g2_t *u8g2);
void testDrawCircle(u8g2_t *u8g2);
void testDrawFilledEllipse(u8g2_t *u8g2);
void testDrawMulti(u8g2_t *u8g2);
void testDrawXBM(u8g2_t *u8g2);
 
void u8g2DrawTest(u8g2_t *u8g2);
void draw_logo(u8g2_t *u8g2);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

void OLED_U8G2_init(void);
void OLED_U8G2_init_animation(void);
void OLED_U8G2_draw_test(void);
void OLED_U8G2_draw_buf(uint8_t * buf, int buf_len);
void OLED_U8G2_draw_hex(uint8_t * buf, int buf_len);
void OLED_U8G2_draw_mpu6050(imu_data_t *);
void OLED_U8G2_draw_rocker_key(uint16_t x, uint16_t y);
void OLED_U8G2_draw_rc_com(rc_data_t *rc);
void OLED_U8G2_draw_rc_keys(rc_keys_t *rc);


#endif
