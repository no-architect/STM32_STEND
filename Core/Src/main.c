/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MAX31865.h"
#include "MCP23S17.h"
#include <stm32746g_discovery_qspi.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define REFRESH_COUNT        1835

#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

QSPI_HandleTypeDef hqspi;

SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi5;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim8;

SDRAM_HandleTypeDef hsdram1;

osThreadId defaultTaskHandHandle;
osThreadId myTask02Handle;
/* USER CODE BEGIN PV */
//MAX31865_GPIO max_gpio;
Max31865_t  pt100;
bool        pt100isOK;
float       pt100Temp;
MCP23x17_t MCP23S17_CIP0059_MOTOR;//

MCP23x17_t MCP23S17[8];

MCP23x17_t MCP23S17_0;	//---Opcode = 0b000;
MCP23x17_t MCP23S17_1;	//---Opcode = 0b001;
MCP23x17_t MCP23S17_2;	//---Opcode = 0b010;
MCP23x17_t MCP23S17_3;	//---Opcode = 0b011;
MCP23x17_t MCP23S17_4;	//---Opcode = 0b100;
MCP23x17_t MCP23S17_5;	//---Opcode = 0b101;
MCP23x17_t MCP23S17_6;	//---Opcode = 0b110;
MCP23x17_t MCP23S17_7;	//---Opcode = 0b111;
//{
//	com.protocole -> MCP23S17_SPI,
//	com.hspix -> hspi2,
//}
static FMC_SDRAM_CommandTypeDef Command;
int counter;
int pos = 0;
volatile char sim;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_I2C3_Init(void);
static void MX_SPI5_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM8_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart6)
	{
		HAL_UART_Transmit(&huart6, (uint8_t*)&sim, 1, 1000);
		HAL_UART_Receive_IT(&huart6, (uint8_t*)&sim, 1);
	}
}

HAL_StatusTypeDef HAL_UART_ReceiveString(
		UART_HandleTypeDef *huart, uint8_t *pData,
		uint16_t Size, uint32_t Timeout) {
	const char newLine[] = "r\n";
	const char delete[] = "\x08 \x08";
	HAL_StatusTypeDef status;

	if(Size == 0)
		return HAL_ERROR;

	int i = 0;
	for(;;) {
		status = HAL_UART_Receive(huart, &pData[i], 1, Timeout);
		if(status != HAL_OK)
			return status;

		if((pData[i] == '\x08')||(pData[i] == 'x7F')) {
			if (i > 0) {
				status = HAL_UART_Transmit(huart, (uint8_t*)delete, sizeof(delete) - 1, Timeout);
				//status = HAL_UART_Transmit(huart, (uint8_t*)newLine, sizeof(newLine) - 1, Timeout);
				if(status != HAL_OK)
					return status;
				i--;
			}
			continue;
		}

		if((pData[i] =='\r') || (pData[i] == '\n')) {
			pData[i] = '\0';
			status = HAL_UART_Transmit(huart, (uint8_t*)newLine, sizeof(newLine) - 1, Timeout);
			if(status != HAL_OK)
				return status;
			break;
		}

		if(i == (Size - 1))
			continue;

		status = HAL_UART_Transmit(huart, &pData[i], 1, Timeout);
		if(status != HAL_OK)
			return status;

		i++;
	}
}
*/

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

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_QUADSPI_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_I2C3_Init();
  MX_SPI5_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TouchGFX_Init();
  /* USER CODE BEGIN 2 */



  //MCP23S17_EXPANDER.config.portA = IODIR;
  //MCP23S17_EXPANDER.config.portB = IODIR;
/*
  = {
   	.com.protocole = MCP23S17_SPI,
   	.com.hspix = hspi2,
 //  	.com.mutex = hspi2_mutex,
   	.com.Opcode = 0b000,
   	.config.BANK = MCP23x17_BANK0,
   	//.config.portA.default_GPIO = 0xFF,
   	//.config.portA.IODIR = 0xFF,
   };

*/
/*
  MCP23S17_CIP0059_MOTOR.com.protocole = MCP23S17_SPI;
  MCP23S17_CIP0059_MOTOR.com.hspix = hspi2;

  //--- address MCP devices
  MCP23S17_CIP0059_MOTOR.com.Opcode = 0b000;
  MCP23S17_CIP0059_MOTOR.config.portA.IOCON = 0x28;
  MCP23S17_CIP0059_MOTOR.config.portB.IOCON = 0x28;
  MCP23S17_CIP0059_MOTOR.config.portA.IODIR = 0x00;
  MCP23S17_CIP0059_MOTOR.config.portB.IODIR = 0x00;
  MCP23S17_CIP0059_MOTOR.config.portA.default_GPIO = 0xFE;
  MCP23S17_CIP0059_MOTOR.config.portB.default_GPIO = 0xFF;
  MCP23S17_CIP0059_MOTOR.config.portA.OLAT = 0xFF;
  MCP23S17_CIP0059_MOTOR.config.portB.OLAT = 0xFF;
*/
  /*
  //---setting MCP23S17`s commutation
  MCP23S17_0.com.protocole = MCP23S17_SPI; MCP23S17_0.com.hspix = hspi2; MCP23S17_0.com.Opcode = 0b000;
  MCP23S17_1.com.protocole = MCP23S17_SPI; MCP23S17_1.com.hspix = hspi2; MCP23S17_1.com.Opcode = 0b001;
  MCP23S17_2.com.protocole = MCP23S17_SPI; MCP23S17_2.com.hspix = hspi2; MCP23S17_2.com.Opcode = 0b010;
  MCP23S17_3.com.protocole = MCP23S17_SPI; MCP23S17_3.com.hspix = hspi2; MCP23S17_3.com.Opcode = 0b011;
  MCP23S17_4.com.protocole = MCP23S17_SPI; MCP23S17_4.com.hspix = hspi2; MCP23S17_4.com.Opcode = 0b100;
  MCP23S17_5.com.protocole = MCP23S17_SPI; MCP23S17_5.com.hspix = hspi2; MCP23S17_5.com.Opcode = 0b101;
  MCP23S17_6.com.protocole = MCP23S17_SPI; MCP23S17_6.com.hspix = hspi2; MCP23S17_6.com.Opcode = 0b110;
  MCP23S17_7.com.protocole = MCP23S17_SPI; MCP23S17_7.com.hspix = hspi2; MCP23S17_7.com.Opcode = 0b111;
*/
  int kol;
  for (kol=0;kol<8;kol++)
  {
	  MCP23S17[kol].com.protocole = MCP23S17_SPI;
	  MCP23S17[kol].com.hspix = hspi2;
	  MCP23S17[kol].com.Opcode = kol;
	  MCP23S17[kol].config.portA.IOCON = 0x28;				//---(default = 0x00) GPA0-GPA7 interrupt on change control register
	  MCP23S17[kol].config.portA.IODIR = 0x00;				//---(default = 0xFF) GPA0-GPA7 configured as an output
	  MCP23S17[kol].config.portA.OLAT = 0xFF;				//---(default = 0x00) output latch register
	  MCP23S17[kol].config.portB.IOCON = 0x28;				//---(default = 0x00) GPA0-GPA7 interrupt on change control register
	  MCP23S17[kol].config.portB.IODIR = 0x00;				//---(default = 0xFF) GPA0-GPA7 configured as an output
	  MCP23S17[kol].config.portB.OLAT = 0xFF;				//---(default = 0x00) output latch register
	  MCP23x17_init(&MCP23S17[kol]);						//---initialize MCP
  }
  MCP23x17_write(&MCP23S17[7], MCP23x17_portB, MCP23x17_OLAT, 0x7F);	//--- disable LED2
  MCP23x17_write(&MCP23S17[0], MCP23x17_portA, MCP23x17_OLAT, 0xFE);	//--- disable LED1
  //---setting MCP23S17`s commutation
    //MCP23S17_0.com.protocole = MCP23S17_SPI; MCP23S17_0.com.hspix = hspi2; MCP23S17_0.com.Opcode = 0b000; MCP23S17_0.config.portA.IOCON = 0x28; MCP23S17_0.config.portA.IODIR = 0x00; MCP23S17_0.config.portA.OLAT = 0x00; MCP23S17_0.config.portB.IOCON = 0x28; MCP23S17_0.config.portB.IODIR = 0x00; MCP23S17_0.config.portB.OLAT = 0xFF;
    //MCP23S17_1.com.protocole = MCP23S17_SPI; MCP23S17_1.com.hspix = hspi2; MCP23S17_1.com.Opcode = 0b001;
    //MCP23S17_2.com.protocole = MCP23S17_SPI; MCP23S17_2.com.hspix = hspi2; MCP23S17_2.com.Opcode = 0b010;
    //MCP23S17_3.com.protocole = MCP23S17_SPI; MCP23S17_3.com.hspix = hspi2; MCP23S17_3.com.Opcode = 0b011;
    //MCP23S17_4.com.protocole = MCP23S17_SPI; MCP23S17_4.com.hspix = hspi2; MCP23S17_4.com.Opcode = 0b100;
    //MCP23S17_5.com.protocole = MCP23S17_SPI; MCP23S17_5.com.hspix = hspi2; MCP23S17_5.com.Opcode = 0b101;
    //MCP23S17_6.com.protocole = MCP23S17_SPI; MCP23S17_6.com.hspix = hspi2; MCP23S17_6.com.Opcode = 0b110;
    //MCP23S17_7.com.protocole = MCP23S17_SPI; MCP23S17_7.com.hspix = hspi2; MCP23S17_7.com.Opcode = 0b111; MCP23S17_7.config.portA.IOCON = 0x28; MCP23S17_7.config.portA.IODIR = 0x00; MCP23S17_7.config.portA.OLAT = 0xFF; MCP23S17_7.config.portB.IOCON = 0x28; MCP23S17_7.config.portB.IODIR = 0x00; MCP23S17_7.config.portB.OLAT = 0x00;
    //MCP23x17_init(&MCP23S17_0);
    //MCP23x17_init(&MCP23S17_7);

/*
  //---setting MCP23S17_0 portA and portB configuration
  MCP23S17_0.config.portA.IOCON = 0x28;				//---(default = 0x00) GPA0-GPA7 interrupt on change control register
  MCP23S17_0.config.portA.IODIR = 0x00;				//---(default = 0xFF) GPA0-GPA7 configured as an output
  MCP23S17_0.config.portA.OLAT = 0xFE;				//---(default = 0x00) output latch register
  MCP23S17_0.config.portB.IOCON = 0x28;				//---(default = 0x00) GPA0-GPA7 interrupt on change control register
  MCP23S17_0.config.portB.IODIR = 0x00;				//---(default = 0xFF) GPA0-GPA7 configured as an output
  MCP23S17_0.config.portB.OLAT = 0xFF;				//---(default = 0x00) output latch register
  //---setting MCP23S17_7 portA and portB configuration
  MCP23S17_7.config.portA.IOCON = 0x28;				//---(default = 0x00) GPA0-GPA7 interrupt on change control register
  MCP23S17_7.config.portA.IODIR = 0x00;				//---(default = 0xFF) GPA0-GPA7 configured as an output
  MCP23S17_7.config.portA.OLAT = 0xFF;				//---(default = 0x00) output latch register
  MCP23S17_7.config.portB.IOCON = 0x28;				//---(default = 0x00) GPA0-GPA7 interrupt on change control register
  MCP23S17_7.config.portB.IODIR = 0x00;				//---(default = 0xFF) GPA0-GPA7 configured as an output
  MCP23S17_7.config.portB.OLAT = 0x7F;				//---(default = 0x00) output latch register
*/
  //MCP23x17_init(&MCP23S17_CIP0059_MOTOR);


  HAL_Delay(100);

  Max31865_init_index(&pt100, &hspi5, SENSOR_CS1_GPIO_Port, SENSOR_CS1_Pin, 2, 50, 0);
  MCP23x17_write(&MCP23S17[7], MCP23x17_portB, MCP23x17_OLAT, 0x7F);	//--- disable LED2
  MCP23x17_write(&MCP23S17[0], MCP23x17_portA, MCP23x17_OLAT, 0xFE);	//--- disable LED1
/**
  // Define SPI pinout
  max_gpio.MISO_PIN = GPIO_PIN_8;
  max_gpio.MISO_PORT = GPIOF;
  max_gpio.MOSI_PIN = GPIO_PIN_9;
  max_gpio.MOSI_PORT = GPIOF;
  max_gpio.CLK_PIN = GPIO_PIN_7;
  max_gpio.CLK_PORT = GPIOF;
  max_gpio.CE_PIN = SENSOR_CS1_Pin;
  max_gpio.CE_PORT = SENSOR_CS1_GPIO_Port;

  MAX31865_init(&max_gpio, 2);
**/

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTaskHand */
  osThreadDef(defaultTaskHand, StartDefaultTask, osPriorityNormal, 0, 4096);
  defaultTaskHandHandle = osThreadCreate(osThread(defaultTaskHand), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00C0EAFF;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 40;
  hltdc.Init.VerticalSync = 9;
  hltdc.Init.AccumulatedHBP = 53;
  hltdc.Init.AccumulatedVBP = 11;
  hltdc.Init.AccumulatedActiveW = 533;
  hltdc.Init.AccumulatedActiveH = 283;
  hltdc.Init.TotalWidth = 565;
  hltdc.Init.TotalHeigh = 285;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 24;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */
  BSP_QSPI_Init();

  BSP_QSPI_MemoryMappedMode();
  HAL_NVIC_DisableIRQ(QUADSPI_IRQn);

  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI5_Init(void)
{

  /* USER CODE BEGIN SPI5_Init 0 */

  /* USER CODE END SPI5_Init 0 */

  /* USER CODE BEGIN SPI5_Init 1 */

  /* USER CODE END SPI5_Init 1 */
  /* SPI5 parameter configuration*/
  hspi5.Instance = SPI5;
  hspi5.Init.Mode = SPI_MODE_MASTER;
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi5.Init.NSS = SPI_NSS_SOFT;
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi5.Init.CRCPolynomial = 7;
  hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi5.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI5_Init 2 */

  /* USER CODE END SPI5_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 199;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 31999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC1REF;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 16000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 199;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 31;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_GATED;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim8, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 16;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 3;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */
    __IO uint32_t tmpmrd = 0;

    /* Step 1: Configure a clock configuration enable command */
    Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
    Command.CommandTarget          =  FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

    /* Step 2: Insert 100 us minimum delay */
    /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
    HAL_Delay(1);

    /* Step 3: Configure a PALL (precharge all) command */
    Command.CommandMode            = FMC_SDRAM_CMD_PALL;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

    /* Step 4: Configure an Auto Refresh command */
    Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 8;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

    /* Step 5: Program the external memory mode register */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | \
             SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL    | \
             SDRAM_MODEREG_CAS_LATENCY_3            | \
             SDRAM_MODEREG_OPERATING_MODE_STANDARD  | \
             SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 1;
    Command.ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

    /* Step 6: Set the refresh rate counter */
    /* Set the device refresh rate */
    HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT);
    
    //Deactivate speculative/cache access to first FMC Bank to save FMC bandwidth
    FMC_Bank1->BTCR[0] = 0x000030D2;
  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_DISP_GPIO_Port, LCD_DISP_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DCMI_PWR_EN_GPIO_Port, DCMI_PWR_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SENSOR_CS1_GPIO_Port, SENSOR_CS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EXT_RST_GPIO_Port, EXT_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OTG_HS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_HS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_HS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D7_Pin ULPI_D6_Pin ULPI_D5_Pin ULPI_D3_Pin
                           ULPI_D2_Pin ULPI_D1_Pin ULPI_D4_Pin */
  GPIO_InitStruct.Pin = ULPI_D7_Pin|ULPI_D6_Pin|ULPI_D5_Pin|ULPI_D3_Pin
                          |ULPI_D2_Pin|ULPI_D1_Pin|ULPI_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SPDIF_RX0_Pin */
  GPIO_InitStruct.Pin = SPDIF_RX0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF8_SPDIFRX;
  HAL_GPIO_Init(SPDIF_RX0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SDMMC_CK_Pin SDMMC_D3_Pin SDMMC_D2_Pin PC9
                           PC8 */
  GPIO_InitStruct.Pin = SDMMC_CK_Pin|SDMMC_D3_Pin|SDMMC_D2_Pin|GPIO_PIN_9
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_D6_Pin DCMI_D7_Pin */
  GPIO_InitStruct.Pin = DCMI_D6_Pin|DCMI_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TX_EN_Pin */
  GPIO_InitStruct.Pin = RMII_TX_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TX_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_VBUS_Pin */
  GPIO_InitStruct.Pin = OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_VBUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_D5_Pin */
  GPIO_InitStruct.Pin = DCMI_D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_D5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_CTRL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_VSYNC_Pin */
  GPIO_InitStruct.Pin = DCMI_VSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_VSYNC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SDMMC_CMD_Pin */
  GPIO_InitStruct.Pin = SDMMC_CMD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
  HAL_GPIO_Init(SDMMC_CMD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TP3_Pin NC2_Pin */
  GPIO_InitStruct.Pin = TP3_Pin|NC2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_DISP_Pin */
  GPIO_InitStruct.Pin = LCD_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_DISP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_PWR_EN_Pin */
  GPIO_InitStruct.Pin = DCMI_PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DCMI_PWR_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_D4_Pin */
  GPIO_InitStruct.Pin = DCMI_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_D4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_BTN_Pin */
  GPIO_InitStruct.Pin = USER_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_INT_Pin */
  GPIO_InitStruct.Pin = LCD_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ULPI_NXT_Pin */
  GPIO_InitStruct.Pin = ULPI_NXT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(ULPI_NXT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PG6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : SENSOR_CS1_Pin */
  GPIO_InitStruct.Pin = SENSOR_CS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SENSOR_CS1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_STP_Pin ULPI_DIR_Pin */
  GPIO_InitStruct.Pin = ULPI_STP_Pin|ULPI_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : EXT_RST_Pin */
  GPIO_InitStruct.Pin = EXT_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EXT_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_HSYNC_Pin PA6 */
  GPIO_InitStruct.Pin = DCMI_HSYNC_Pin|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_CLK_Pin ULPI_D0_Pin */
  GPIO_InitStruct.Pin = ULPI_CLK_Pin|ULPI_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void SET_TIM1_PWM_PULSE(int setPWM)
{

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
	int read = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
	int proba = __HAL_TIM_GET_COUNTER(&htim1);

	if ((setPWM < 100) && (setPWM > 0))
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 320 * setPWM);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	}


	//HAL_StatusTypeDef status;
	//char name[32];


	//status = HAL_UART_ReceiveString(&huart6, (uint8_t*)name, sizeof(name) - 1, HAL_MAX_DELAY);
	//HAL_UART_Transmit(&huart6, (uint8_t *) "HELLO\r\n", 6, 100);
	//uint8_t str2[] = str + "\r\n";
	//HAL_UART_Transmit(&huart6, (uint8_t*)name, sizeof(name) - 1, 100);
	//HAL_UART_Transmit(&huart6, (uint8_t*)"\r\n", 1, 100);
//	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	osDelay(1000);
//	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	osDelay(1000);
}

volatile uint32_t userButtonPressed = 0;
volatile uint32_t userButtonPressed2 = 0;

float TEMP_SENSOR_GetValue(void)
{
	float t;
	uint32_t pro;
	pt100isOK = Max31865_readTempC_index(&pt100,&t, 0);

	MCP23x17_write(&MCP23S17[7], MCP23x17_portB, MCP23x17_OLAT, 0x7F);	//--- disable LED2
	MCP23x17_write(&MCP23S17[0], MCP23x17_portA, MCP23x17_OLAT, 0xFE);	//--- disable LED1

	//		 Max31865_readTempC(&pt100,&t);
	//pt100Temp = MAX31865_readTemp();;   //  << For Smoothing data
	pt100Temp = t; //Max31865_Filter(t, pt100Temp, 0.1);
	if (pt100isOK) {
		return pt100Temp;
	}
	return 0xFFFFFFFF;

}

float TEMP_SENSOR_INDEX_GetValue(int index)
{
	float t;
	uint32_t pro;

	if (index < MAX_COUNT)
	{
		pt100isOK = Max31865_readTempC_index(&pt100, &t, index);

		  MCP23x17_write(&MCP23S17[7], MCP23x17_portB, MCP23x17_OLAT, 0x7F);	//--- disable LED2
		  MCP23x17_write(&MCP23S17[0], MCP23x17_portA, MCP23x17_OLAT, 0xFE);	//--- disable LED1

		//		 Max31865_readTempC(&pt100,&t);
		//pt100Temp = MAX31865_readTemp();;   //  << For Smoothing data
		pt100Temp = t; //Max31865_Filter(t, pt100Temp, 0.1);
		if (pt100isOK) {
			return pt100Temp;
		}
		else
		{
			return 88.8888;
		}
	}

	return 99.9999;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint8_t ppp;
	if (GPIO_Pin == USER_BTN_Pin)
	{
		if (userButtonPressed2 == 0)
		{
		    userButtonPressed = 1;
		    userButtonPressed2 = 1;
//            ppp = MCP23x17_readportA(&MCP23S17_CIP0059_MOTOR);
//            HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		    //MCP23x17_writeportA(&MCP23S17_CIP0059_MOTOR, 0x00);
		}
		else
		{
			userButtonPressed2 = 0;
		    userButtonPressed = 1;
		    //MCP23x17_writeportA(&MCP23S17_CIP0059_MOTOR, 0xF0);
		}

		HAL_Delay(100);
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTaskHand thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  MX_TouchGFX_Process();
  /* Infinite loop */
  for(;;)
  {
    
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */

  /* Infinite loop */
  for(;;)
  {
	//TOGGLE_LED3();
	//HAL_UART_Receive_IT(&huart6, (uint8_t*)&sim, 1);
    //osDelay(500);
  }
  /* USER CODE END StartTask02 */
}

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
  MPU_InitStruct.BaseAddress = 0x90000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16MB;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

