#ifndef __DRIVER_H_
#define __DRIVER_H_

#include "stm32f4xx.h"
#include "motor.h"
#include "led.h"
#include "delay.h"
#include "ir.h"
#include "encode.h"
#include "pid.h"
#include "mpu9250.h" 
#include "sysc.h"

#define beeline_speed_init 									70

extern int16_t Motor[4];
extern float beeline_speed_desired;

void Ready_Start_Mode(void);
void Modo_DataUp(void);

#endif
