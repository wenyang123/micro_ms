#ifndef __FILTER_H
#define	__FILTER_H

#include "stm32f4xx.h"
#include "uart.h"
#include "mathx.h"

typedef struct{
		float   cutoff_freq; 
		float   a1;
		float   a2;
		float   b0;
		float   b1;
		float   b2;
		float   delay_element_1;        
		float   delay_element_2; 
	
}LPF;

void  LPF2p_SetCutoffFreq(LPF *LPFSetCutoff,float _sample_freq, float _cutoff_freq);
float LPF2p_Apply(LPF *LPFSetCutoff,float sample);

#endif
