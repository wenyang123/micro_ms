#include "driver.h"

void Ready_Start_Mode(void)
{
	Motor_Pwm_Flash(0,0,0,0);
	while(encode_1_pulse_total/4 < 500);
	led_s1_on;
	while(encode_2_pulse_total/4 < 500);
	led_s2_on;
	delay_ms(50);
	ir_1_on;
	while(ir_adc_1a_value_new < ir_start_value);
	led_s1_off;led_s2_off;
	ir_1_off;
	led_r_on;
	delay_ms(200);
	led_l_off;led_r_off;
	//Motor_Pwm_Flash(130,0,100,0);
}
