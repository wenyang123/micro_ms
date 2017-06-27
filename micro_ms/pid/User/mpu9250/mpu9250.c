#include "mpu9250.h"

static LPF LPF_Acc_X,LPF_Acc_Y,LPF_Acc_Z;
static LPF LPF_Gyro_X,LPF_Gyro_Y,LPF_Gyro_Z;

MPU9250 mpu9250;

//---------------------MPU9250_I2C配置----------------------------//
static void MPU9250_I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	mpu9250_i2c_gpio_rcc_cmd(mpu9250_i2c_sda_clk|mpu9250_i2c_scl_clk|mpu9250_i2c_ad0_clk, ENABLE);
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	
	GPIO_InitStruct.GPIO_Pin = mpu9250_i2c_scl_pin;
	GPIO_Init(mpu9250_i2c_scl_port, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = mpu9250_i2c_sda_pin;
	GPIO_Init(mpu9250_i2c_sda_port, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = mpu9250_i2c_ad0_pin ;
	GPIO_Init(mpu9250_i2c_ad0_port, &GPIO_InitStruct);
	mpu9250_i2c_ad0_l;
}

static void MPU9250_I2C_Delay(void)
{
	u8 i;
	for(i=0; i<5; i++);
}

static void MPU9250_I2C_Start(void)
{
	mpu9250_i2c_sda_h;
	mpu9250_i2c_scl_h;
	MPU9250_I2C_Delay();
	mpu9250_i2c_sda_l;
	MPU9250_I2C_Delay();
	mpu9250_i2c_scl_l;
	MPU9250_I2C_Delay();
}

static void MPU9250_I2C_Stop(void)
{
	mpu9250_i2c_scl_h;
	mpu9250_i2c_sda_l;
	MPU9250_I2C_Delay();
	mpu9250_i2c_sda_h;
	MPU9250_I2C_Delay();
	mpu9250_i2c_scl_h;
	MPU9250_I2C_Delay();
}

static u8 MPU9250_I2C_Read(void)
{
	uint8_t i;  
  uint8_t value=0;
  
  for(i=0; i<8; i++)
  {
    value <<= 1 ;    
    mpu9250_i2c_scl_h;
    MPU9250_I2C_Delay();
		
    if(mpu9250_i2c_read_sda)
    {
      value++;
    }
		
    mpu9250_i2c_scl_l;      
    MPU9250_I2C_Delay();    
  }
  return value;
}

static void MPU9250_I2C_Write(u8 WT)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		if((WT<<i) &0x80)
			mpu9250_i2c_sda_h;
		else
			mpu9250_i2c_sda_l;
		
		MPU9250_I2C_Delay();
		mpu9250_i2c_scl_h;
		MPU9250_I2C_Delay();
		mpu9250_i2c_scl_l;
		MPU9250_I2C_Delay();
	}	
	mpu9250_i2c_sda_h;	
}

static u8 MPU9250_I2C_Wait_Ask(void)
{
	u8 askflag;
	
	mpu9250_i2c_scl_h;
	MPU9250_I2C_Delay();
	
	if(mpu9250_i2c_read_sda)
		askflag = 1;
	else 
		askflag = 0;
	
	mpu9250_i2c_scl_l;
	MPU9250_I2C_Delay();
	mpu9250_i2c_sda_h;
	MPU9250_I2C_Delay();
	return askflag;
}

static void MPU9250_I2C_Send_Ask(void)
{
	mpu9250_i2c_sda_l;
	mpu9250_i2c_scl_h;
	MPU9250_I2C_Delay();
	mpu9250_i2c_scl_l;
	mpu9250_i2c_sda_h;
	MPU9250_I2C_Delay();
}

static void MPU9250_I2C_Send_Disask(void)
{
	mpu9250_i2c_sda_h;
	mpu9250_i2c_scl_h;
	MPU9250_I2C_Delay();
	mpu9250_i2c_scl_l;
	MPU9250_I2C_Delay();
}

u8 MPU9250_I2C_Send_Word(u8 aadd,u8 add,u8 *data,u32 num)
{
	MPU9250_I2C_Start();
	
	MPU9250_I2C_Write(aadd|mpu9250_i2c_write_dir);
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto err;
	}
	
	MPU9250_I2C_Write(add);
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto err;
	}
	
	while(num--)
	{
		MPU9250_I2C_Write(*data);
	
		if(MPU9250_I2C_Wait_Ask()!=0)
		{ 
			goto err;
		}
		data++;
	}
	
	MPU9250_I2C_Stop();
	return 1;
	
	err:	printf("发送错误 \n"); 
	MPU9250_I2C_Stop();
	return 0;
}

u8 MPU9250_I2C_Send_Byte(u8 aadd,u8 add,u8 data)
{
	MPU9250_I2C_Start();
	
	MPU9250_I2C_Write(aadd|mpu9250_i2c_write_dir);
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto err;
	}
	
	MPU9250_I2C_Write(add);
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto err;
	}
	
	MPU9250_I2C_Write(data);
	
	if(MPU9250_I2C_Wait_Ask()!=0)
	{ 
		goto err;
	}
	
  MPU9250_I2C_Stop();
	return 1;

	err:	printf("发送错误 \n"); 
	MPU9250_I2C_Stop();
	return 0;
}

void MPU9250_I2C_Read_Wait_Ask(u8 add)
{
	do
	{
		MPU9250_I2C_Stop();
		MPU9250_I2C_Start();
		MPU9250_I2C_Write(add|mpu9250_i2c_write_dir);
	}while(MPU9250_I2C_Wait_Ask() !=0);
	
	MPU9250_I2C_Stop();
}

u8 MPU9250_I2C_Read_Word(u8 aadd,u8 add,u8 *Readbuff, u32 num)
{
	num++;
	MPU9250_I2C_Read_Wait_Ask(aadd);
	MPU9250_I2C_Start();
	
	MPU9250_I2C_Write(aadd|mpu9250_i2c_write_dir);	
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto Rerr;
	}
	
	MPU9250_I2C_Write(add);
	if(MPU9250_I2C_Wait_Ask()!=0)
	{	
		goto Rerr;
	}
	
	MPU9250_I2C_Start();
	
	MPU9250_I2C_Write(aadd|mpu9250_i2c_read_dir);
	
	if(MPU9250_I2C_Wait_Ask()!=0)
	{ 
		goto Rerr;
	}
	
 while(num)  
  {
    if(num == 1)
    {
      MPU9250_I2C_Send_Disask();
      MPU9250_I2C_Stop();
    }
	
      *Readbuff = MPU9250_I2C_Read();
      Readbuff++; 
      num--;
      MPU9250_I2C_Send_Ask();
	}
	
	MPU9250_I2C_Send_Disask();
	MPU9250_I2C_Stop();
	return 1;
	
  Rerr:	printf("读取错误 \n"); 
	MPU9250_I2C_Stop();
	return 0;
}

u8 MPU9250_I2C_Read_Byte(u8 aadd,u8 add)
{
	u8 Readnum;
	
	MPU9250_I2C_Read_Wait_Ask(aadd);
	MPU9250_I2C_Start();
	MPU9250_I2C_Write(aadd|mpu9250_i2c_write_dir);	
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto Rerr;
	}
	
	MPU9250_I2C_Write(add);
	if(MPU9250_I2C_Wait_Ask()!=0)
	{
		goto Rerr;
	}
	
	MPU9250_I2C_Start();
	
	MPU9250_I2C_Write(aadd|mpu9250_i2c_read_dir);
	
	if(MPU9250_I2C_Wait_Ask()!=0)
	{ 
		goto Rerr;
	}
	
	Readnum=MPU9250_I2C_Read();
	MPU9250_I2C_Send_Disask();
	MPU9250_I2C_Stop();
	return Readnum;
	
  Rerr:	printf("读取错误 \n"); 
	MPU9250_I2C_Stop();
	return 0;
}

//-------------------------------------MPU920使用配置-------------------------------------//
void MPU9250_Mode_Init(void)
{
	delay_ms(100);
	MPU9250_I2C_GPIO_Config();
	MPU9250_I2C_Read_Byte(mpu9250_i2c_myself_add,0x75);  
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_pwr_wait,mpu9250_i2c_ra_pwr_wait_val);
	delay_ms(100);
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_pwr_mgmt_1,mpu9250_i2c_ra_pwr_mgmt_1_val);
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_smplrt_div,mpu9250_i2c_ra_smplrt_div_val);
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_config,mpu9250_i2c_ra_config_val);
	
	#if MPU9250_MAG_FLAG
	MPU9250_I2C_SendByte(mpu9250_i2c_myself_add,mpu9250_i2c_int_pin_cfg,0x02);
	delay_ms(1);
	
		bb=MPU9250_ReadByte(I2C_MAG_ADD,0x00);
		printf("2:0x%x       \n\n",bb);
	  printf("      \n\n",bb);
	
	MPU9250_I2C_SendByte(mpu9250_i2c_mag_add,mpu9250_i2c_mag_rd,mpu9250_i2c_mag_rd_val);
	delay_ms( 1);
	#endif
	
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_gyro_config,mpu9250_i2c_ra_gyro_config_val);
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_accel_config,mpu9250_i2c_ra_accel_config_val);
	MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_ra_accel_config2,mpu9250_i2c_ra_accel_config2_val);
	delay_ms(100);
	
	mpu9250.x_accel=65536.0f/16.0f;
	mpu9250.x_gyro=65536.0f/4000.0f;
	mpu9250.imu_PIc=180.f/PI;
}

/*--------------------------------读取角速度------------------------------------*/
void MPU9250_Mode_Read_Gyro(int16_t *gyrodata)
{
    u8 buf[6];
	
		MPU9250_I2C_Read_Word(mpu9250_i2c_myself_add,mpu9250_i2c_gyro_out,buf,6);
    gyrodata[0] = (int16_t)(((buf[0] << 8) | buf[1])-mpu9250.gyro_Check[0]);   
    gyrodata[1] = (int16_t)(((buf[2] << 8) | buf[3])-mpu9250.gyro_Check[1]);   
    gyrodata[2] = (int16_t)(((buf[4] << 8) | buf[5])-mpu9250.gyro_Check[2]);
}

/*--------------------------------读取加速度------------------------------------*/
void MPU9250_Mode_Read_Acc(int16_t *accdata)
{
    u8 buf[6];
	
		MPU9250_I2C_Read_Word(mpu9250_i2c_myself_add,mpu9250_i2c_acc_out,buf,6);
    accdata[0] = (int16_t)(((buf[0] << 8) | buf[1])-mpu9250.acc_Check[0]);   
    accdata[1] = (int16_t)(((buf[2] << 8) | buf[3])-mpu9250.acc_Check[1]);   
    accdata[2] = (int16_t)(((buf[4] << 8) | buf[5])-mpu9250.acc_Check[2]);
}

/*--------------------------------读取磁力计·------------------------------------*/
void MPU9250_Mode_Read_Mag(int16_t *magdata)
{ 
	 u8 buf[6];
	
   MPU9250_I2C_Read_Word(mpu9250_i2c_myself_add,mpu9250_i2c_mag_out,buf,6);
	 delay_ms(1);
	 MPU9250_I2C_Send_Byte(mpu9250_i2c_myself_add,mpu9250_i2c_mag_rd,mpu9250_i2c_mag_rd_val);
	
   magdata[0] = ((buf[1] << 8) | buf[0]);//-acc_check[0];   
   magdata[1] = ((buf[3] << 8) | buf[2]);//-acc_check[1];   
   magdata[2] = ((buf[5] << 8) | buf[4]);//-acc_check[2];
	 delay_ms(1);
}

/*-------------------------------计算二阶低通滤波的计算因子------------------------------------*/
void MPU9250_Mode_LPD2p_Set_Cutoff(void)
{
	LPF2p_SetCutoffFreq(&LPF_Acc_X,mpu9250_i2c_sample_rate,mpu9250_i2c_filter_cutoff_acc);
	LPF2p_SetCutoffFreq(&LPF_Acc_Y,mpu9250_i2c_sample_rate,mpu9250_i2c_filter_cutoff_acc);
	LPF2p_SetCutoffFreq(&LPF_Acc_Z,mpu9250_i2c_sample_rate,mpu9250_i2c_filter_cutoff_acc);
	LPF2p_SetCutoffFreq(&LPF_Gyro_X,mpu9250_i2c_sample_rate,mpu9250_i2c_filter_cutoff_gyro);
	LPF2p_SetCutoffFreq(&LPF_Gyro_Y,mpu9250_i2c_sample_rate,mpu9250_i2c_filter_cutoff_gyro);
	LPF2p_SetCutoffFreq(&LPF_Gyro_Z,mpu9250_i2c_sample_rate,mpu9250_i2c_filter_cutoff_gyro);
}

/*--------------------------------读取新角速度·------------------------------------*/
void MPU9250_Mode_DataUp(void)
{ 
	uint8_t i=0;
	
	MPU9250_Mode_Read_Gyro(mpu9250.gyroADC);
	for(i=0; i<3; i++)
	{
	  if(abs(mpu9250.gyroADC[i]) <= 6)
				mpu9250.gyroGet[i] = 0;
		else
			mpu9250.gyroGet[i] = (float)mpu9250.gyroADC[i] / mpu9250.x_gyro;	
	}
	

#if 0
	mpu9250.gyroData[0] = LPF2p_Apply(&LPF_Gyro_X,mpu9250.gyroGet[0]);
	mpu9250.gyroData[1] = LPF2p_Apply(&LPF_Gyro_Y,mpu9250.gyroGet[1]);
	mpu9250.gyroData[2] = LPF2p_Apply(&LPF_Gyro_Z,mpu9250.gyroGet[2]);
#else
	mpu9250.gyroData[0] = mpu9250.gyroGet[0];
	mpu9250.gyroData[1] = mpu9250.gyroGet[1];
	mpu9250.gyroData[2] = mpu9250.gyroGet[2];
#endif
		
#if mpu9250_mag_flag
	MPU9250_Mode_Read_Mag(MagData);
#endif
		
#if mpu9250_accel_flag
	MPU9250_Mode_Read_Acc(mpu9250.accADC);
	for(i=0; i<3; i++)
	{
		mpu9250.accGet[i] = (float)mpu9250.accADC[i] / mpu9250.x_accel;
	}
	mpu9250.accData[0] = LPF2p_Apply(&LPF_Acc_X,mpu9250.accGet[0]);
	mpu9250.accData[1] = LPF2p_Apply(&LPF_Acc_Y,mpu9250.accGet[1]);
	mpu9250.accData[2] = LPF2p_Apply(&LPF_Acc_Z,mpu9250.accGet[2]);
#endif
}

/*--------------------------------偏移修正·------------------------------------*/
void MPU9250_Mode_MeCheck(void)
{
	u8 g=0, i=0, j=0;
	int32_t Acc_check[3]={0}, Gyro_check[3]={0};
	
	printf("\n正在进行传感器矫正，请水平放置   \n");
	for(j=0;j<10;j++)
	{
		led_f_def;
		delay_ms(200);
	}
	led_f_on;
	printf("\n开始修正   \n");
	
	for(g=0; g<100; g++)
	{
		MPU9250_Mode_Read_Acc(mpu9250.accADC); MPU9250_Mode_Read_Gyro(mpu9250.gyroADC);
		Acc_check[0] += mpu9250.accADC[0];
		Acc_check[1] += mpu9250.accADC[1];
		Acc_check[2] += mpu9250.accADC[2] - 4096;
		Gyro_check[0] += mpu9250.gyroADC[0];
		Gyro_check[1] += mpu9250.gyroADC[1];
		Gyro_check[2] += mpu9250.gyroADC[2];
	  delay_ms(1);
	}
	mpu9250.acc_Check[0] = (int32_t)Acc_check[0] / 100;
	mpu9250.acc_Check[1] = (int32_t)Acc_check[1] / 100;
	mpu9250.acc_Check[2] = (int32_t)Acc_check[2] / 100;
	
#if 1
	mpu9250.gyro_Check[0] = (int32_t)Gyro_check[0] / 100;
	mpu9250.gyro_Check[1] = (int32_t)Gyro_check[1] / 100;
	mpu9250.gyro_Check[2] = (int32_t)Gyro_check[2] / 100;
#endif
 
	for(i=0; i<10; i++)  //为了消除LPF初始时的误差
	{
	 MPU9250_Mode_DataUp();
	 delay_ms(10);
	}
	printf("\n矫正完成\n");
}

u32 imu_time_flag=0;
u32 imu_time_new=0;
float imu_dt=0.0f;
float imu_yaw=0.0f;

void IMU_DataUp(void)
{
	MPU9250_Mode_DataUp();
	imu_time_new = Test_Dt(&imu_time_flag);
	imu_dt = (float)imu_time_new/1000000.0f;
	imu_yaw += mpu9250.gyroData[2] * imu_dt;
	mpu9250.yaw = imu_yaw;
}


