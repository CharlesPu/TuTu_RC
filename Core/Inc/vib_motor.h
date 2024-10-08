#ifndef __VIBMOTOR_H_
#define __VIBMOTOR_H_	

#include "main.h"

#define VIBRATE_INTERVAL 150 // ms


void VIBMOTOR_init(void);
void VIBMOTOR_vibrate_once(void);
void VIBMOTOR_vibrate_twice(void);
void VIBMOTOR_vibrate_long_on(void);
void VIBMOTOR_vibrate_long_off(void);


#endif
