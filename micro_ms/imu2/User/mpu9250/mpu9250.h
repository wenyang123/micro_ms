#ifndef __MPU9250_H_
#define __MPU9250_H_

#include "stm32f4xx.h"
#include "delay.h"
#include "uart.h"
#include "sysc.h"
#include "arm_math.h"
#include "filter.h"
#include "led.h"
#include "stdlib.h"

#define mpu9250_i2c              			 	 		  0
#define mpu9250_i2c_read_dir									0x01
#define mpu9250_i2c_write_dir									0x00
#define mpu9250_i2c_add                 			0X77

#define mpu9250_i2c_gpio_rcc_cmd			  			RCC_AHB1PeriphClockCmd

#define mpu9250_i2c_scl_port       						GPIOD  
#define mpu9250_i2c_scl_pin            	  		GPIO_Pin_0                  
#define mpu9250_i2c_scl_clk        						RCC_AHB1Periph_GPIOD
#define mpu9250_i2c_scl_h  			  					  mpu9250_i2c_scl_port->BSRRL = mpu9250_i2c_scl_pin		
#define mpu9250_i2c_scl_l 			  				  	mpu9250_i2c_scl_port->BSRRH = mpu9250_i2c_scl_pin	

#define mpu9250_i2c_sda_port       						GPIOC  
#define mpu9250_i2c_sda_pin            	 		  GPIO_Pin_12                 
#define mpu9250_i2c_sda_clk        						RCC_AHB1Periph_GPIOC
#define mpu9250_i2c_sda_h  			  					  mpu9250_i2c_sda_port->BSRRL = mpu9250_i2c_sda_pin		
#define mpu9250_i2c_sda_l			  				    	mpu9250_i2c_sda_port->BSRRH = mpu9250_i2c_sda_pin	

#define mpu9250_i2c_read_sda  								GPIO_ReadInputDataBit(mpu9250_i2c_sda_port,mpu9250_i2c_sda_pin)

#define mpu9250_i2c_ad0_port       						GPIOC 
#define mpu9250_i2c_ad0_pin            	 		  GPIO_Pin_11                  
#define mpu9250_i2c_ad0_clk        						RCC_AHB1Periph_GPIOC
#define mpu9250_i2c_ad0_h  			  					  mpu9250_i2c_ad0_port->BSRRL = mpu9250_i2c_ad0_pin		
#define mpu9250_i2c_ad0_l 			  					  mpu9250_i2c_ad0_port->BSRRH = mpu9250_i2c_ad0_pin	

#define mpu9250_i2c_myself_add          			0XD0  // 0XD0 ----ADD_0   0XD2 ---ADD_1   
#define mpu9250_i2c_mag_add    								0x18  //´ÅÁ¦¼ÆµØÖ·

#define mpu9250_i2c_ra_pwr_wait         			0x6B            //ÉèÖÃÉè±¸Ê±ÖÓ
#define mpu9250_i2c_ra_pwr_wait_val       	  			0x80        //
#define mpu9250_i2c_ra_pwr_mgmt_1       			0x6B            //ÉèÖÃÉè±¸Ê±ÖÓ
#define mpu9250_i2c_ra_pwr_mgmt_1_val       				0x03        //
#define mpu9250_i2c_ra_smplrt_div      			  0x19            //ÉèÖÃ²ÉÑùÆµÂÊ
#define mpu9250_i2c_ra_smplrt_div_val      	  			0x00        // 0x00
#define mpu9250_i2c_ra_config           			0x1A            //ÉèÖÃµÍÍ¨ÂË²¨Æ÷µÄÆµÂÊ                               èÖÃµÍÍ¨ÂË²¨Æ÷ÆµÂÊ
#define mpu9250_i2c_ra_config_val           				0x05        //  0x03
#define mpu9250_i2c_ra_gyro_config     				0x1B            //ÉèÖÃÍÓÂİÒÇ²ÎÊı·¶Î§
#define mpu9250_i2c_ra_gyro_config_val      				0x18        //
#define mpu9250_i2c_ra_accel_config    			  0x1C            //ÉèÖÃ¼ÓËÙ¶È¼Æ²ÎÊı·¶Î§
#define mpu9250_i2c_ra_accel_config_val     				0x10 
#define mpu9250_i2c_ra_accel_config2    			0x1D             //ÉèÖÃ¼ÓËÙ¶È¼ÆµÄÂË²¨
#define mpu9250_i2c_ra_accel_config2_val      			0x03
#define mpu9250_i2c_int_pin_cfg								0X37
#define mpu9250_i2c_int_pin_cfg_val									0X02
#define mpu9250_i2c_mag_rd              			0X0A
#define mpu9250_i2c_mag_rd_val                			0X01

#define mpu9250_i2c_gyro_out           				0x43     				//MPU9250ÍÓÂİÒÇÊı¾İ¼Ä´æÆ÷µØÖ·
#define mpu9250_i2c_acc_out             			0x3B    				//MPU9250¼ÓËÙ¶ÈÊı¾İ¼Ä´æÆ÷µØÖ·
#define mpu9250_i2c_mag_out             			0x03            //MPU9250´ÅÁ¦¼ÆÊı¾İ¼Ä´æÆ÷µØÖ·
//MAG_XOUT_L µÍÎ»ÔÚÇ°	
#define mpu9250_mag_flag											0
#define mpu9250_accel_flag										0

#define mpu9250_i2c_sample_rate        				100.0f  //83
#define mpu9250_i2c_filter_cutoff_acc	  			25.0f
#define mpu9250_i2c_filter_cutoff_gyro				45.0f


typedef struct
{
	int32_t acc_Check[3];
	int32_t gyro_Check[3];
	int16_t accADC[3];
	int16_t gyroADC[3];
	int16_t magADC[3];
	float accGet[3];
	float	gyroGet[3];
	float accData[3];
	float	gyroData[3];
	float x_accel;
	float x_gyro;
	float imu_PIc;
	float roll;
	float pitch;
	float yaw;
	float yawAct;
}MPU9250;

extern MPU9250 mpu9250;

static void MPU9250_I2C_GPIO_Config(void);
static void MPU9250_I2C_Delay(void);
static void MPU9250_I2C_Start(void);
static void MPU9250_I2C_Stop(void);
static u8 MPU9250_I2C_Read(void);
static void MPU9250_I2C_Write(u8 WT);
static u8 MPU9250_I2C_Wait_Ask(void);
void MPU9250_I2C_Read_Wait_Ask(u8 add);
static void MPU9250_I2C_Send_Ask(void);
static void MPU9250_I2C_Send_Disask(void);
u8 MPU9250_I2C_Send_Word(u8 aadd,u8 add,u8 *data,u32 num);
u8 MPU9250_I2C_Send_Byte(u8 aadd,u8 add,u8 data);
u8 MPU9250_I2C_Read_Word(u8 aadd,u8 add,u8 *Readbuff, u32 num);
u8 MPU9250_I2C_Read_Byte(u8 aadd,u8 add);

void MPU9250_Mode_Init(void);
void MPU9250_Mode_Read_Gyro(int16_t *gyrodata);
void MPU9250_Mode_Read_Acc(int16_t *accdata);
void MPU9250_Mode_Read_Mag(int16_t *magdata);
void MPU9250_Mode_LPD2p_Set_Cutoff(void);
void MPU9250_Mode_DataUp(void);
void MPU9250_Mode_MeCheck(void);

#endif

