#include "delay.h"

void delay_ms(u32 x)
{
	u32 i, j;
	for(i=0; i<x; i++)
		for(j=0; j<33600; j++);
}

void delay_us(u32 x)
{
	u32 i, j;
	for(i=0; i<x; i++)
		for(j=0; j<3360; j++);
}
