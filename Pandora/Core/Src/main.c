/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "bdma.h"
#include "dma.h"
#include "eth.h"
#include "fdcan.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "definitions.h"
#include "timing.h"
#include "peripherals.h"
#include "can_messages.h"
#include "cocking_handle_maingun.h"
#include "gun_control.h"
#include "error.h"
#include "flash.h"
#include "power_management.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
pandoraStructer pandora;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
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
	/* #DUZENLENECEK
	 SILAH_SURELERI();
	 SON_MERMI_GRUBU_ANAHTARI_KONTROL();
	 FREN_AKIMI_KONTROL();


	 */

  /* USER CODE END 1 */

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
  MX_BDMA_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ETH_Init();
  MX_FDCAN2_Init();
  MX_I2C1_Init();
  MX_UART4_Init();
  MX_UART7_Init();
  MX_ADC1_Init();
  MX_UART8_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim4);

  HAL_ADC_Start_DMA(&hadc1, pandora.analogDigitalConverter.hadc1Buffer, 1);
  HAL_ADC_Start_DMA(&hadc2, pandora.analogDigitalConverter.hadc2Buffer, 1);
  HAL_ADC_Start_DMA(&hadc3, pandora.analogDigitalConverter.hadc3Buffer, 1);

  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  __HAL_TIM_SET_COUNTER(&htim3,0);
  /*
   * 	BEGIN
   */
  //functionLoadFromFlash();														//kayıtlı verileri flashtan al

  /*
   * 	SYSTEM CHECK
   */
//  pandora.error.AKBOK 		= FEEDBACK_READ(AKB_LOOP);
//  pandora.error.EOSOK 		= FEEDBACK_READ(EOS_LOOP);
//  pandora.error.GDBOK 		= FEEDBACK_READ(GDB_LOOP);
//  pandora.error.HERCULEOK 	= FEEDBACK_READ(HERCULE_LOOP);
//  pandora.error.KKUOK		= FEEDBACK_READ(KKU_LOOP);
//
//
//
//  pandora.error.isPluggedAKB 	 = (pandora.powerManagement.actualAKBOK 	|| pandora.configurations.overrideAKBOK); // takılı olmadan da çalışabilmesi için override'a bak
//  pandora.error.isPluggedEOS	 = (pandora.powerManagement.actualEOSOK 	|| pandora.configurations.overrideEOSOK);
//  pandora.error.isPluggedHERCULE = (pandora.powerManagement.actualHERCULEOK || pandora.configurations.overrideHERCULEOK);
//  pandora.error.isPluggedKKU	 = (pandora.powerManagement.actualKKUOK	    || pandora.configurations.overrideKKUOK);

  pandora.error.system 			 =!(pandora.error.AKBOK &&
										pandora.error.EOSOK &&
											pandora.error.GDBOK &&
												pandora.error.HERCULEOK &&
													pandora.error.KKUOK);

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
   * 	SWITCHES CHECK
   */

  pandora.states.firePermission = !pandora.switches.switches_smga;

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
   * 	SYSTEM CHECK
   */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
   * 	SYSTEM CHECK
   */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
   * 	SYSTEM CHECK
   */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
   * 	SYSTEM CHECK
   */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
   * 	SYSTEM CHECK
   */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  functionGunControlInit();
  /*
   * 	END
   */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  startTimeScanFlags();

	  if(_100msFlag)
	  {
		  functionMeasureVoltage();
		  functionMeasureCurrent();

		  functionErrorCurrentVoltageCheck();
		  functionErrorMosfetCheck();
	  }

	  if(!pandora.error.system 						&&
		 pandora.gun.cockingHandle.armed 			&&
	  	 pandora.switches.switches_movement_allowed &&
		 pandora.switches.switches_safety 			&&
		 (!pandora.switches.switches_smga || pandora.canMessages.AKB.commandSmgaOveride) &&
		 pandora.switches.switches_fire_order 		&&
		 !pandora.canMessages.AKB.commandEmergencyStop 				&&
		 (!pandora.canMessages.AKB.commandFireBlockedArea || pandora.canMessages.AKB.commandFireBlockedAreaOveride))
	  {
		  pandora.states.firePermission = true;
	  }
	  else
	  {
		  pandora.states.firePermission = false;
	  }

	  /* COCKING HANDLE LOOP BEGIN */
	  if(pandora.gun.cockingHandle.motorState != IDLE)
	  {
		  functionEncoderRead(&htim3);
	  }

	  if(pandora.switches.switches_cocking_handle_order && pandora.switches.switches_safety && !pandora.gun.cockingHandle.armed)
	  {
		  functionCockingHandleGoArm();
	  }

	  else if (!pandora.switches.switches_safety && !pandora.gun.cockingHandle.safe)
	  {
		  functionCockingHandleGoSafe();
	  }
	  /* COCKING HANDLE LOOP END */

	  /* SOLENOID LOOP BEGIN */
	  functionGunControlProcess(HAL_GetTick());

	  if((pandora.switches.switches_fire_order ||  pandora.canMessages.AKB.commandGunFireOveride)		&&   // ama bence tehlikeli
		 pandora.switches.switches_safety 			&&
		 pandora.switches.switches_movement_allowed &&
		(!pandora.switches.switches_smga || pandora.states.overrideSmga)) // atış emniyet anahtarı ve hareket anahtarı
	  {
		  functionGunControlTriggerPressed();
	  }
	  else
	  {
		  functionGunControlTriggerReleased();
	  }
	  /* SOLENOID LOOP END */

	  clearTimeScanFlags();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL2.PLL2M = 2;
  PeriphClkInitStruct.PLL2.PLL2N = 12;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 4096;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
    {
    	FDCAN_ReceiveMessage(hfdcan);
    }
}

/* USER CODE END 4 */

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
