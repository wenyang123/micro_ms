#ifndef __MATHX_H
#define	__MATHX_H

#include "stm32f4xx.h"
#include "arm_math.h"

#define dsp_sin                      arm_sin_f32
#define dsp_cos                      arm_cos_f32

float dsp_sqrt(float x);

#endif


