#include "filter.h"

void LPF2p_SetCutoffFreq(LPF *LPFSetCutoff,float _sample_freq, float _cutoff_freq)
{
	float fr=0;  
	float ohm=0;
  float c=0;
	
	fr =  _sample_freq / _cutoff_freq;
	ohm = tanf(PI/fr);
	c = 1.0f + 2.0f * dsp_cos(PI/4.0f) * ohm  + ohm * ohm;
  LPFSetCutoff->cutoff_freq = _cutoff_freq;
  if(LPFSetCutoff->cutoff_freq > 0.0f) 
	{
		LPFSetCutoff->b0 = ohm * ohm / c;
		LPFSetCutoff->b1 = 2.0f * LPFSetCutoff->b0;
		LPFSetCutoff->b2 = LPFSetCutoff->b0;
		LPFSetCutoff->a1 = 2.0f * (ohm*ohm-1.0f) / c;
		LPFSetCutoff->a2 = (1.0f-2.0f*dsp_cos(PI/4.0f)*ohm+ohm*ohm) / c;
	}	
}

float LPF2p_Apply(LPF *LPFApply,float sample)
{
	float delay_element_0=0, output=0;
  if (LPFApply->cutoff_freq <= 0.0f)
	{
		return sample;
  }
	else
	{
		delay_element_0 = sample - LPFApply->delay_element_1 * LPFApply->a1 - LPFApply->delay_element_2 * LPFApply->a2;
		if (isnan(delay_element_0) || isinf(delay_element_0))
		{
			delay_element_0 = sample;
		}
		output = (float)delay_element_0 * LPFApply->b0 + LPFApply->delay_element_1 * LPFApply->b1 + LPFApply->delay_element_2 * LPFApply->b2;
		LPFApply->delay_element_2 = LPFApply->delay_element_1;
		LPFApply->delay_element_1 = delay_element_0;
		return output;
	}
}



