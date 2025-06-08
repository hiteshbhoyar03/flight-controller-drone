/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "eth.h"
#include "fdcan.h"
#include "i2c.h"
#include "memorymap.h"
#include "sdmmc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "BMI088.h"
#include "ICM45686.h"
#include "ICM42688P.h"
#include "ICP20100.h"
#include "MS5611.h"
#include "M8N.h"
#include "IBUS.h"
#include "CRSF.h"
#include "SBUS.h"
#include "MYFUNCTIONS.h"
#include "DSHOT.h"
#include "EEPROM.h"
#include "bmm350.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int _write(int file, char* p, int len)
{
	for(int i=0;i<len;i++)
	{
		while(!LL_USART_IsActiveFlag_TXE(USART3));
		LL_USART_TransmitData8(USART3, *(p+i));
	}
	return len;
}

//int __io_putchar (int ch)  	// ll example eeprom
//{
//  while (!LL_USART_IsActiveFlag_TXE(USART2));
//  LL_USART_TransmitData8(USART2, (char)ch);
//  return ch;
//}

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define DEBUG_NO 0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern uint8_t usart3_rx_flag;					// DEBUG
extern uint8_t usart3_rx_data;					// DEBUG

extern uint8_t gps1_ubx_rx_buffer[36];			// GPS1 BUFFER
extern uint8_t gps1_ubx_rx_complete_flag;		// GPS1 COMPLETE FLAG
extern uint8_t gps2_ubx_rx_buffer[36];			// GPS2 BUFFER
extern uint8_t gps2_ubx_rx_complete_flag;		// GPS2 COMPLETE FLAG

extern uint8_t ibus_rx_buffer[32];				// FLYSKY IBUS BUFFER
extern uint8_t ibus_rx_complete_flag;			// FLYSKY IBUS COMPLETE FLAG
extern uint8_t crsf_rx_buffer[26];				// CRSF BUFFER
extern uint8_t crsf_rx_complete_flag;			// CRSF COMPLETE FLAG
extern uint8_t sbus_rx_buffer[25];				// SBUS BUFFER
extern uint8_t sbus_rx_complete_flag;			// SBUS COMPLETE FLAG

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ETH_Init();
  MX_FDCAN1_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_I2C4_Init();
  MX_SDMMC1_MMC_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI4_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_UART4_Init();
  MX_UART7_Init();
  MX_UART8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_USB_OTG_HS_USB_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM12_Init();
  MX_USB_OTG_FS_HCD_Init();
  MX_ADC3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  	  /* BUZZER TIMER ------------------------------------------------------------------------------*/
	  LL_TIM_EnableCounter(TIM12);


	  /* ENABLE INTERRUPT --------------------------------------------------------------------------*/
	  /* THIS ENABLE INTERRUPT IRQ_HANDLER WHEN DATA IS RECEIVED */
	  LL_USART_EnableIT_RXNE(USART3);		// DEBUG
	  LL_USART_EnableIT_RXNE(USART1);		// GPS1
	  LL_USART_EnableIT_RXNE(UART8);		// GPS2
	  LL_USART_EnableIT_RXNE(USART6);		// RECEIVER
	  //  LL_USART_EnableIT_RXNE(UART4);		// EXTERNAL UART

	  /* INITIALIZATION ----------------------------------------------------------------------------*/
	  ICM45686_Initialization();
	  ICM42688P_Initialization();
	  BMI088_Initialization();
	  ICP20100_Initialization();
	  MS5611_Initialization();
	  BMM350_Initialization();
	  M8N_Initialization();
	  //	IBUS_USART6_Initialization();
	  //	CRSF_USART6_Initialization();
	  //	SBUS_USART6_Initialization();
	  Dshot_Init(TIM8 ,DSHOT150, timer8);
	  EEPROM_Initialization();

	  /* CHECK DATA RECEIVED -----------------------------------------------------------------------*/
	  while(Is_Data_Received() == 0)
	  {buzzer_Data_Not_Received();}

	  /* CALIBRATION -------------------------------------------------------------------------------*/
	  /* Only for analog protocol ; Dshot does not need calibration --------------------------------*/
	  if(iBus.switch_A == 2000)
	  {
		  buzzer_Calibration_Started();
		  Calibrate_ESC(TIM1,ONESHOT125);
//		  Calibrate_ESC(TIM8,ONESHOT125);// dshot is set to tim8
		  Calibrate_ESC(TIM5,MULTISHOT);
		  Calibrate_ESC(TIM4,ONESHOT42);
		  while(iBus.switch_A != 1000)
		  {
			  Is_Data_Received();
			  buzzer_Calibration_Done();
		  }
	  }

	  /* SAFETY ------------------------------------------------------------------------------------*/
	  while(Is_Throttle_Min() == 0)
	  {buzzer_Throttel_Safety();}

	  buzzer_All_Set();



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		/*--------------------------------------------------------------------------------------------*/
		/* DEBUG -------------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
//		LL_GPIO_TogglePin(GPIOG, LED_BLUE_Pin|LED_RED_Pin|LED_GREEN_Pin);
//		LL_GPIO_IsInputPinSet(GPIOx, PinMask);
//
//		HAL_Delay(1000);
//		if(usart3_rx_flag == 1)
//		{
//			usart3_rx_flag = 0;
//			LL_USART_TransmitData8(USART3, usart3_rx_data);
//
//			switch(usart3_rx_data)
//			{
//			case '0': LL_GPIO_TogglePin(GPIOG, LED_BLUE_Pin|LED_RED_Pin|LED_GREEN_Pin); break;
//			case '1': LL_TIM_CC_EnableChannel(TIM12, LL_TIM_CHANNEL_CH1); break;
//			case '2': LL_TIM_CC_DisableChannel(TIM12, LL_TIM_CHANNEL_CH1); break;
//			}
//		}
//		printf("%d %f\n",count++,f+=0.001 );

		/*--------------------------------------------------------------------------------------------*/
		/* ICM45686 IMU ------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(ICM45686_DataReady() == 1)
		{
			ICM45686_Get6AxisRawData(&ICM45686.accel_x_raw , &ICM45686.gyro_x_raw);
			//		  ICM45686_Get3AxisGyroRawData(&ICM45686.accel_x_raw);
			//		  ICM45686_Get3AxisAccRawData(&ICM45686.gyro_x_raw);
			ICM45686_TempRawData(&ICM45686.temperature_raw);
			ICM45686_Calculate_Accel_Gyro_Temp(&ICM45686, 16.f , 2000.f);	// ALREADY HAS FORMULA AND RAW DATA

			ICM45686.accel_x = ICM45686.accel_x_raw * 16.f / 32768.f;
			ICM45686.accel_y = ICM45686.accel_y_raw * 16.f / 32768.f;
			ICM45686.accel_z = ICM45686.accel_z_raw * 16.f / 32768.f;
			ICM45686.gyro_x  = ICM45686.gyro_x_raw  * 2000.f / 32768.f;
			ICM45686.gyro_y  = ICM45686.gyro_y_raw  * 2000.f / 32768.f;
			ICM45686.gyro_z  = ICM45686.gyro_z_raw  * 2000.f / 32768.f;
			ICM45686.temperature = (ICM45686.temperature_raw / 132.48f)+25.f;

#if DEBUG_NO == 0//1
			printf("%d\t%d\t%d\n", ICM45686.accel_x_raw, ICM45686.accel_y_raw, ICM45686.accel_z_raw);
			printf("%f\t%f\t%f\n", (float)(ICM45686.accel_x), (float)(ICM45686.accel_y), (float)(ICM45686.accel_z));
			printf("%d\t%d\t%d\n", ICM45686.gyro_x_raw, ICM45686.gyro_y_raw, ICM45686.gyro_z_raw);
			printf("%f\t%f\t%f\n", (float)(ICM45686.gyro_x), (float)(ICM45686.gyro_y), (float)(ICM45686.gyro_z));
#endif
		}

		/*--------------------------------------------------------------------------------------------*/
		/* ICM42688P IMU -----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(ICM42688P_DataReady() == 1)
		{
			ICM42688P_Get6AxisRawData(&ICM42688P.accel_x_raw , &ICM42688P.gyro_x_raw);
			//		  ICM42688P_Get3AxisGyroRawData(&ICM42688P.accel_x_raw);
			//		  ICM42688P_Get3AxisAccRawData(&ICM42688P.gyro_x_raw);
			ICM42688P_TempRawData(&ICM42688P.temperature_raw);
			ICM42688P_Calculate_Accel_Gyro_Temp(&ICM42688P, 16.f , 2000.f);  // ALREADY HAS FORMULA AND RAW DATA

			ICM42688P.temperature = (ICM42688P.temperature_raw / 132.48f)+25.f;
			ICM42688P.accel_x = ICM42688P.accel_x_raw * 16.f / 32768.f;
			ICM42688P.accel_y = ICM42688P.accel_y_raw * 16.f / 32768.f;
			ICM42688P.accel_z = ICM42688P.accel_z_raw * 16.f / 32768.f;
			ICM42688P.gyro_x  = ICM42688P.gyro_x_raw  * 2000.f / 32768.f;
			ICM42688P.gyro_y  = ICM42688P.gyro_y_raw  * 2000.f / 32768.f;
			ICM42688P.gyro_z  = ICM42688P.gyro_z_raw  * 2000.f / 32768.f;

#if DEBUG_NO == 0//2
			printf("%d\t%d\t%d\n", ICM42688P.accel_x_raw, ICM42688P.accel_y_raw, ICM42688P.accel_z_raw);
			printf("%f\t%f\t%f\n", (float)(ICM42688P.accel_x), (float)(ICM42688P.accel_y), (float)(ICM42688P.accel_z));
			printf("%d\t%d\t%d\n", ICM42688P.gyro_x_raw, ICM42688P.gyro_y_raw, ICM42688P.gyro_z_raw);
			printf("%f\t%f\t%f\n", (float)(ICM42688P.gyro_x), (float)(ICM42688P.gyro_y), (float)(ICM42688P.gyro_z));
#endif
		}

		/*--------------------------------------------------------------------------------------------*/
		/* BMI088 ACCEL ------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(BMI088_DataReady_ACCEL() == 1)
		{
			BMI088_Get3AxisAccelRawData(&BMI088.accel_x_raw);
			BMI088_TempRawData(&BMI088.temperature_raw);
			BMI088_Calculate_Accel_Temp(&BMI088, 24.f);	// ALREADY HAS FORMULA AND RAW DATA

			BMI088.accel_x = BMI088.accel_x_raw * 24.f / 32768.f;
			BMI088.accel_y = BMI088.accel_y_raw * 24.f / 32768.f;
			BMI088.accel_z = BMI088.accel_z_raw * 24.f / 32768.f;
			BMI088.temperature = (BMI088.temperature_raw / 132.48f)+25.f;

#if DEBUG_NO == 0//3
			printf("%d\t%d\t%d\n", BMI088.accel_x_raw, BMI088.accel_y_raw, BMI088.accel_z_raw);
			printf("%f\t%f\t%f\n", (float)(BMI088.accel_x), (float)(BMI088.accel_y), (float)(BMI088.accel_z));
#endif
		}

		/*--------------------------------------------------------------------------------------------*/
		/* BMI088 GYRO -------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(BMI088_DataReady_GYRO() == 1)
		{
			BMI088_Get3AxisGyroRawData(&BMI088.gyro_x_raw);
			BMI088_Calculate_Gyro(&BMI088, 2000.f);	// ALREADY HAS FORMULA AND RAW DATA

			BMI088.gyro_x = BMI088.gyro_x_raw * 2000.f / 32768.f;
			BMI088.gyro_y = BMI088.gyro_y_raw * 2000.f / 32768.f;
			BMI088.gyro_z = BMI088.gyro_z_raw * 2000.f / 32768.f;

#if DEBUG_NO == 0//4
			printf("%d\t%d\t%d\n", BMI088.gyro_x_raw, BMI088.gyro_y_raw, BMI088.gyro_z_raw);
			printf("%f\t%f\t%f\n", (float)(BMI088.gyro_x), (float)(BMI088.gyro_y), (float)(BMI088.gyro_z));
#endif
		}

		/*--------------------------------------------------------------------------------------------*/
		/* ICP20100 BARO -----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(ICP20100_DataReady() == 1)
		{
			ICP20100_Get_Raw_Pressure_And_Temp(&ICP20100.raw_pressure , &ICP20100.raw_temperature);
			//		  ICP20100_Get_Raw_Pressure(&ICP20100.raw_pressure);
			//		  ICP20100_Get_Raw_Temperature(&ICP20100.raw_temperature);
			//		  ICP20100_Get_Altitude(&ICP20100);					// ALREADY HAS FORMULA AND RAW DATA
			//		  ICP20100_Get_Altitude_Temp_Corrected(&ICP20100);	// ALREADY HAS FORMULA AND RAW DATA

			// FORMULA TO CONVERT RAW DATA TO MEANINGFUL DATA
			ICP20100.pressure    = (float)(ICP20100.raw_pressure    >> 17 )*40.f+70.f;
			ICP20100.temperature = (float)(ICP20100.raw_temperature >> 18 )*65.f+25.f;

#define BARO_FILTER1 0.90f // MOVE TO TOP
			ICP20100.filtered_altitude = (double)(ICP20100.filtered_altitude * BARO_FILTER1 + ICP20100.altitude * (1.0f - BARO_FILTER1));

#if DEBUG_NO == 0//5
			printf("%ld\t%ld\n", ICP20100.raw_pressure , ICP20100.raw_temperature);
			printf("%f\t%f\n", (float)(ICP20100.pressure) , (float)(ICP20100.temperature));
#endif
		}

		/*--------------------------------------------------------------------------------------------*/
		/* MS5611 BARO -------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		MS5611_Get_Raw_Pressure(&MS5611.raw_pressure);
		MS5611_Get_Raw_Temperature(&MS5611.raw_temperature);

		MS5611_Calculate_Temperature(&MS5611);			// ALREADY HAS RAW DATA FUNCTION
		MS5611_Calculate_Temperature_Compensated_Pressure(&MS5611);	// ALREADY HAS RAW DATA FUNCTION
		MS5611_Get_Altitude(&MS5611);					// NEED PRESSURE CALCULATION FIRST

#define BARO_FILTER2 0.90f // MOVE TO TOP
		MS5611.filtered_altitude = (double)(MS5611.filtered_altitude * BARO_FILTER2 + MS5611.altitude * (1.0f - BARO_FILTER2));


#if DEBUG_NO == 0//6
		printf("%lu\t%lu\n", MS5611.raw_pressure , MS5611.raw_temperature);
		printf("%f\t%f\t%f\n", (float)(MS5611.pressure), (float)(MS5611.temperature), (float)(MS5611.altitude));
#endif

		/*--------------------------------------------------------------------------------------------*/
		/* GPS UBX -----------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(gps1_ubx_rx_complete_flag == 1)
		{
			gps1_ubx_rx_complete_flag = 0;
			if(UBX_Check_CHKSUM(&gps1_ubx_rx_buffer[0], 36) == 1)
			{
				UBX_NAV_POSLLH_Parsing(&gps1_ubx_rx_buffer[0], &gps1_posllh);
#if DEBUG_NO == 0//7
				printf("LAT: %d\tLON: %d\tHeight: %d\n",
						gps1_posllh.lat, gps1_posllh.lon, gps1_posllh.height);
#endif
			}
		}

		if(gps2_ubx_rx_complete_flag == 1)
		{
			gps2_ubx_rx_complete_flag = 0;
			if(UBX_Check_CHKSUM(&gps2_ubx_rx_buffer[0], 36) == 1)
			{
				UBX_NAV_POSLLH_Parsing(&gps2_ubx_rx_buffer[0], &gps2_posllh);
#if DEBUG_NO == 0//8
				printf("LAT: %d\tLON: %d\tHeight: %d\n",
						gps2_posllh.lat, gps2_posllh.lon, gps2_posllh.height);
#endif
			}
		}

		/*--------------------------------------------------------------------------------------------*/
		/* IBUS PROTOCOL -----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(ibus_rx_complete_flag == 1)
		{
			ibus_rx_complete_flag = 0;
			if(IBUS_Check_CHKSUM(&ibus_rx_buffer[0], IBUS_PACKET_SIZE) == 1)
			{
				IBUS_Parsing(&ibus_rx_buffer[0], &iBus);
				if(IBUS_isActiveFailsafe(&iBus)==1)
				{			// FAILSAFE CODE HERE

				}
				else
				{

				}
#if DEBUG_NO == 0//9
				printf("%d\t%d\t%d\t%d\t%d\t%d\n",
						iBus.channel_1, iBus.channel_2,
						iBus.channel_3, iBus.channel_4,
						iBus.switch_A , iBus.switch_B);
				HAL_Delay(30);
#endif
			}
		}

		/*--------------------------------------------------------------------------------------------*/
		/* CRSF PROTOCOL -----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(crsf_rx_complete_flag == 1)
		{
			crsf_rx_complete_flag = 0;
			if(CRSF_Check_crc8(&crsf_rx_buffer[2], CRSF_FRAME_LENGTH - 1) == 1)
			{
				CRSF_Parsing(&crsf_rx_buffer[0], &CRSF);
				if(CRSF_isActiveFailsafe(&CRSF)==1)
				{			// FAILSAFE CODE HERE

				}
				else
				{

				}

#if DEBUG_NO == 0//10
				printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
						"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
						CRSF.channel[0] ,CRSF.channel[1] ,CRSF.channel[2] ,CRSF.channel[3],
						CRSF.channel[4] ,CRSF.channel[5] ,CRSF.channel[6] ,CRSF.channel[7],
						CRSF.channel[8] ,CRSF.channel[9] ,CRSF.channel[10],CRSF.channel[11],
						CRSF.channel[12],CRSF.channel[13],CRSF.channel[14],CRSF.channel[15]);
				HAL_Delay(30);
#endif
			}
		}

		/*--------------------------------------------------------------------------------------------*/
		/* SBUS PROTOCOL -----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		if(sbus_rx_complete_flag == 1)
		{
			sbus_rx_complete_flag = 0;
			SBUS_Parsing(&sbus_rx_buffer[0], &SBUS);
			if(SBUS_isActiveFailsafe(&SBUS)==1)
			{			// FAILSAFE CODE HERE

			}
			else
			{

			}

#if DEBUG_NO == 0//11
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%d\n",
					SBUS.channel[0] ,SBUS.channel[1] ,SBUS.channel[2] ,SBUS.channel[3],
					SBUS.channel[4] ,SBUS.channel[5] ,SBUS.channel[6] ,SBUS.channel[7],
					SBUS.channel[8] ,SBUS.channel[9] ,SBUS.channel[10],SBUS.channel[11],
					SBUS.channel[12],SBUS.channel[13],SBUS.channel[14],SBUS.channel[15],
					SBUS.channel_17,SBUS.channel_18,SBUS.frame_lost,SBUS.failsafe_activated,
					SBUS.footer);
			HAL_Delay(30);
#endif
		}


		/*--------------------------------------------------------------------------------------------*/
		/* PWM  PROTOCOL -----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
#if DEBUG_NO == 0//12

#define TIMx 			TIM1				// TIM1 , TIM2 , TIM3 , TIM4
#define ccr_max 		oneshot125_max_ccr 	// oneshot125_max_ccr, oneshot42_max_ccr, multishot_max_ccr
#define ccr_min 		oneshot125_min_ccr 	// oneshot125_min_ccr, oneshot42_min_ccr, multishot_min_ccr
#define channel_max 	IBUS_CHANNEL_MAX	// IBUS_CHANNEL_MAX  , CRSF_CHANNEL_MAX , SBUS_CHANNEL_MAX
#define channel_min 	IBUS_CHANNEL_MIN	// IBUS_CHANNEL_MIN  , CRSF_CHANNEL_MIN , SBUS_CHANNEL_MIN
#define TIMx_channel_1 	iBus.channel_1		// iBus.channel_1    , CRSF.channel[0] 	, SBUS.channel[0]
#define TIMx_channel_2 	iBus.channel_2		// iBus.channel_2    , CRSF.channel[1]  , SBUS.channel[1]
#define TIMx_channel_3 	iBus.channel_3		// iBus.channel_3    , CRSF.channel[2]  , SBUS.channel[2]
#define TIMx_channel_4 	iBus.channel_4		// iBus.channel_4    , CRSF.channel[3]  , SBUS.channel[3]

		TIMx->CCR1 = ccr_min + (ccr_max - ccr_min)*(TIMx_channel_1 - channel_min)/(channel_max-channel_min);
		TIMx->CCR2 = ccr_min + (ccr_max - ccr_min)*(TIMx_channel_2 - channel_min)/(channel_max-channel_min);
		TIMx->CCR3 = ccr_min + (ccr_max - ccr_min)*(TIMx_channel_3 - channel_min)/(channel_max-channel_min);
		TIMx->CCR4 = ccr_min + (ccr_max - ccr_min)*(TIMx_channel_4 - channel_min)/(channel_max-channel_min);

#endif


		/*--------------------------------------------------------------------------------------------*/
		/* DSHOT PROTOCOL ----------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		/* FOR Timer 8 -------------------------------------------------------------------------------*/
#if DEBUG_NO == 0//13

#define TIMx_channel_1 	iBus.channel_1		// iBus.channel_1    , CRSF.channel[0] 	, SBUS.channel[0]
#define TIMx_channel_2 	iBus.channel_2		// iBus.channel_2    , CRSF.channel[1]  , SBUS.channel[1]
#define TIMx_channel_3 	iBus.channel_3		// iBus.channel_3    , CRSF.channel[2]  , SBUS.channel[2]
#define TIMx_channel_4 	iBus.channel_4		// iBus.channel_4    , CRSF.channel[3]  , SBUS.channel[3]
		uint16_t motor_value[motor_count]={iBus.channel_1,iBus.channel_2,
				iBus.channel_3,iBus.channel_4};
		Dshot_Write(motor_value, timer8);
#endif

		/*--------------------------------------------------------------------------------------------*/
		/* EEPROM ------------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
		/* Functions ---------------------------------------------------------------------------------*/

		//		uint8_t EEPROM_ReadByte(uint32_t address);
		//		void EEPROM_Read_Buffer(uint32_t address, uint8_t *buffer, uint16_t length);
		//		void EEPROM_WriteByte(uint32_t address, uint8_t data);
		//		void EEPROM_Write_Buffer(uint32_t address, uint8_t *buffer, uint16_t length);
		//		void EEPROM_Erase_Chip(void);
		//		void EEPROM_Erase_Block(uint32_t address);
		//		void EEPROM_Erase_Sector(uint32_t address);
		//		void EEPROM_Erase_PAGE(uint32_t address);
#if DEBUG_NO == 0//14

		uint8_t data;
		char *sndBuffer = "hello world";
		char rcvBuffer[50];

		EEPROM_WriteByte(0x00, 'A');
		data = EEPROM_ReadByte(0x00);
		printf("EEPROM_ReadByte@0x00: %c\r\n", data);

		EEPROM_Write_Buffer(0x01, (uint8_t*)sndBuffer, strlen(sndBuffer));
		memset(rcvBuffer, 0, sizeof(rcvBuffer));
		EEPROM_Read_Buffer(0x01, (uint8_t*)rcvBuffer,strlen(sndBuffer));
		printf("EEPROM_ReadBuffer@0x02: %s\r\n", rcvBuffer);

		//		EEPROM_EraseAll();
		//		data = EEPROM_ReadByte(0x00);
		//		printf("EEPROM_ReadByte@0x00: %c\r\n", data);
		//
		//		void EEPROM_PID_Gain_Write(unsigned char id, float P_Gain, float I_Gain, float D_Gain);
		//		unsigned char EEPROM_PID_Gain_Read(unsigned char id, float* P_Gain, float* I_Gain, float* D_Gain);
		EEPROM_PID_Gain_Write(0, 1.1, 2.2, 3.3);
		float p = 0.0, i = 0.0, d = 0.0;
		EEPROM_PID_Gain_Read(0, &p, &i, &d);
		printf("%f %f %f", p, i, d);

#endif

		/*--------------------------------------------------------------------------------------------*/
		/* BMM350 ------------------------------------------------------------------------------------*/
		/*--------------------------------------------------------------------------------------------*/
#if DEBUG_NO == 0//15
		if(BMM350_DataReady() == 1)
		{
			//				void BMM350_GetAllRawData(uint32_t* mag , uint32_t* temperature , uint32_t* sensortime);
			//				void BMM350_Get3AxisMagRawData(uint32_t* mag);
			//				void BMM350_GetTemperatureRawData(uint32_t* temperature);
			//				void BMM350_GetSensortimeRawData(uint32_t* sensortime);

			BMM350_Get3AxisMagRawData(&BMM350.mag_x_raw);
			BMM350_GetTemperatureRawData(&BMM350.temperature_raw);

			//check datasheet for conversion

			printf("%ld\t%ld\t%ld\n", BMM350.mag_x_raw, BMM350.mag_y_raw, BMM350.mag_z_raw);
			printf("%f\t%f\t%f\n", (float)(BMM350.mag_x), (float)(BMM350.mag_y), (float)(BMM350.mag_z));
		}
#endif
























	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_SDMMC
                              |RCC_PERIPHCLK_SPI2|RCC_PERIPHCLK_SPI1
                              |RCC_PERIPHCLK_SPI4|RCC_PERIPHCLK_SPI5
                              |RCC_PERIPHCLK_FDCAN;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 10;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 1;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL2;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_PLL2;
  PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL2;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
