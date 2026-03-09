/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t contador1 = 0;
uint8_t contador2 = 0;

typedef enum{
	ESTADO_ESPERA,
	ESTADO_CUENTA_REGRESIVA,
	ESTADO_JUGANDO,
	ESTADO_GANADOR
}EstadoJuego;

EstadoJuego estado = ESTADO_ESPERA;

uint8_t cuenta = 5;
uint32_t tiempoAnterior = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ActualizarLEDs1(uint8_t pos);
void ActualizarLEDs2(uint8_t pos);
void ActualizarGANADOR1(uint8_t a);
void ActualizarGANADOR2(uint8_t b);
void MostrarNumero(uint8_t valor);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (estado == ESTADO_CUENTA_REGRESIVA){
		  if(HAL_GetTick() -  tiempoAnterior >= 1000){ // Cuenta de 1000 ms
			  tiempoAnterior = HAL_GetTick(); // Guardamos el valor actual del timepo

			  if(cuenta > 0){
				  cuenta--; //Disminuimos le contador
				  MostrarNumero(cuenta);
			  }
			  else{
				  estado = ESTADO_JUGANDO;
			  }
		  }
	  }


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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DPLY_A_Pin|DPLY_B_Pin|DPLY_C_Pin|DPLY_D_Pin
                          |DPLY_E_Pin|DPLY_F_Pin|DPLY_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED1_10_Pin|LED1_20_Pin|LED1_30_Pin|LED1_40_Pin
                          |LED2_10_Pin|LED2_20_Pin|LED2_30_Pin|LED2_40_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DPLY_A_Pin DPLY_B_Pin DPLY_C_Pin DPLY_D_Pin
                           DPLY_E_Pin DPLY_F_Pin DPLY_G_Pin */
  GPIO_InitStruct.Pin = DPLY_A_Pin|DPLY_B_Pin|DPLY_C_Pin|DPLY_D_Pin
                          |DPLY_E_Pin|DPLY_F_Pin|DPLY_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : B_START_Pin B_P1_Pin B_P2_Pin */
  GPIO_InitStruct.Pin = B_START_Pin|B_P1_Pin|B_P2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_10_Pin LED1_20_Pin LED1_30_Pin LED1_40_Pin
                           LED2_10_Pin LED2_20_Pin LED2_30_Pin LED2_40_Pin */
  GPIO_InitStruct.Pin = LED1_10_Pin|LED1_20_Pin|LED1_30_Pin|LED1_40_Pin
                          |LED2_10_Pin|LED2_20_Pin|LED2_30_Pin|LED2_40_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void ActualizarLEDs1(uint8_t pos){

	HAL_GPIO_WritePin(LED1_10_GPIO_Port,LED1_10_Pin,(pos==1)?GPIO_PIN_SET:GPIO_PIN_RESET);//Preguntamos si el valor ingresado es menor o mayor para prednerlo
	HAL_GPIO_WritePin(LED1_20_GPIO_Port,LED1_20_Pin,(pos==2)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1_30_GPIO_Port,LED1_30_Pin,(pos==3)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1_40_GPIO_Port,LED1_40_Pin,(pos==4)?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void ActualizarLEDs2(uint8_t pos){

	HAL_GPIO_WritePin(LED2_10_GPIO_Port,LED2_10_Pin,(pos==1)?GPIO_PIN_SET:GPIO_PIN_RESET);//Preguntamos si el valor ingresado es menor o mayor para prednerlo
	HAL_GPIO_WritePin(LED2_20_GPIO_Port,LED2_20_Pin,(pos==2)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_30_GPIO_Port,LED2_30_Pin,(pos==3)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_40_GPIO_Port,LED2_40_Pin,(pos==4)?GPIO_PIN_SET:GPIO_PIN_RESET);

}

void ActualizarGANADOR1(uint8_t a){
HAL_GPIO_WritePin(LED1_10_GPIO_Port,LED1_10_Pin,(a >= 1)? GPIO_PIN_SET:GPIO_PIN_RESET);//Preguntamos si el valor ingresado es menor o mayor para prednerlo
HAL_GPIO_WritePin(LED1_20_GPIO_Port,LED1_20_Pin,(a >= 2)? GPIO_PIN_SET:GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED1_30_GPIO_Port,LED1_30_Pin,(a >= 3)? GPIO_PIN_SET:GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED1_40_GPIO_Port,LED1_40_Pin,(a >= 4)? GPIO_PIN_SET:GPIO_PIN_RESET);
}

void ActualizarGANADOR2(uint8_t b){
HAL_GPIO_WritePin(LED2_10_GPIO_Port,LED2_10_Pin,(b >= 1) ? GPIO_PIN_SET:GPIO_PIN_RESET);//Preguntamos si el valor ingresado es menor o mayor para prednerlo
HAL_GPIO_WritePin(LED2_20_GPIO_Port,LED2_20_Pin,(b >= 2)? GPIO_PIN_SET:GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED2_30_GPIO_Port,LED2_30_Pin,(b >= 3)? GPIO_PIN_SET:GPIO_PIN_RESET);
HAL_GPIO_WritePin(LED2_40_GPIO_Port,LED2_40_Pin,(b >= 4)? GPIO_PIN_SET:GPIO_PIN_RESET);
}

void MostrarNumero(uint8_t valor){

	uint8_t display = 0;

	switch(valor) {
		case 0:

			display = 0b0111111;
			break;

		case 1:

			display = 0b0000110;
			break;

		case 2:

			display = 0b1011011;
			break;

		case 3:

			display = 0b1001111;
			break;

		case 4:

			display = 0b1100110;
			break;

		case 5:

			display = 0b1101101;
			break;

		default:

			display = 0;
			break;
	}
	//Revisar y encender bits
	// Esta estructura es similar a la utilizada para la LCD por pablo.
	HAL_GPIO_WritePin(DPLY_A_GPIO_Port,DPLY_A_Pin,(display & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DPLY_B_GPIO_Port,DPLY_B_Pin,(display & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DPLY_C_GPIO_Port,DPLY_C_Pin,(display & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DPLY_D_GPIO_Port,DPLY_D_Pin,(display & 0x08)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DPLY_E_GPIO_Port,DPLY_E_Pin,(display & 0x10)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DPLY_F_GPIO_Port,DPLY_F_Pin,(display & 0x20)?GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DPLY_G_GPIO_Port,DPLY_G_Pin,(display & 0x40)?GPIO_PIN_SET:GPIO_PIN_RESET);
}

//Interupcion
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == B_START_Pin){ //START

		if(estado == ESTADO_GANADOR){ //Reiniciar cuando termine uno
			contador1 = 0;
			contador2 = 0;
			ActualizarLEDs1(0);
			ActualizarLEDs2(0);
			estado = ESTADO_ESPERA;
		}

		if(estado == ESTADO_ESPERA){
			cuenta = 5;
			estado = ESTADO_CUENTA_REGRESIVA;
			tiempoAnterior = HAL_GetTick();
			MostrarNumero(cuenta);
		}
	}

	if(GPIO_Pin == B_P1_Pin){//jugador 1
		if (estado == ESTADO_JUGANDO){

			if(contador2<4){//Revisar que no haya ganado
				contador1++;
				ActualizarLEDs1(contador1);
			}
			if(contador1 == 4){
				ActualizarGANADOR1(contador1);
				estado = ESTADO_GANADOR;
				MostrarNumero(1);
			}
		}
	}

	if(GPIO_Pin == B_P2_Pin){ //jugador 2
		if(estado == ESTADO_JUGANDO){

			if(contador1<4){
				contador2++;
				ActualizarLEDs2(contador2);
			}

			if(contador2 == 4){
				ActualizarGANADOR2(contador2);
				estado =  ESTADO_GANADOR;
				MostrarNumero(2);
			}
		}
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
#ifdef USE_FULL_ASSERT
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
