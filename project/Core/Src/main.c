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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ring_buffer.h"
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
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint32_t left_toggles = 0;
uint32_t left_last_press_tick = 0;

uint8_t data_usart3;
uint8_t data_usart2;

/* control variables for ring buffer in USART */
#define CAPACITY_USART3 5
uint8_t mem_usart3[CAPACITY_USART3];
ring_buffer_t rb_usart3;

/* control variables for ring buffer in USART2 */
#define CAPACITY_USART2 10
uint8_t mem_usart2[CAPACITY_USART2];
ring_buffer_t rb_usart2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
void heartbeat(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Data received in USART3 */
  if (huart->Instance == USART3) {
	  ring_buffer_write(&rb_usart3, data_usart3);
	  HAL_UART_Receive_IT(&huart3, &data_usart3, 1);
  }
  /* Data received in USART2 */
  if (huart->Instance == USART2) {
	  ring_buffer_write(&rb_usart2, data_usart2); // put the data received in buffer
	  HAL_UART_Receive_IT(&huart2, &data_usart2, 1); // enable interrupt to continue receiving
  }
}
uint8_t key_pressed = 0xFF;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint16_t last_pressed = 0xFFFF;
	static uint32_t last_tick = 0;

	if (last_pressed == GPIO_Pin)  {
		if (HAL_GetTick() < (last_tick + 200))	{
			return;
		}
	}
	uint8_t key_pressed = 0xFF;

	switch (GPIO_Pin) {
	case COLUMN1_Pin:
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(COLUMN1_GPIO_Port, COLUMN1_Pin) == 0){
			key_pressed = '1';
			break;
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(COLUMN1_GPIO_Port, COLUMN1_Pin) == 0){
					key_pressed = '4';
					break;
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(COLUMN1_GPIO_Port, COLUMN1_Pin) == 0){
					key_pressed = '7';
					break;
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(COLUMN1_GPIO_Port, COLUMN1_Pin) == 0){
					key_pressed = '*';
					break;
		}
	case COLUMN2_Pin:
			HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN2_GPIO_Port, COLUMN2_Pin) == 0){
				key_pressed = '1';
				break;
			HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN2_GPIO_Port, COLUMN2_Pin) == 0){
						key_pressed = '4';
						break;
			HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN2_GPIO_Port, COLUMN2_Pin) == 0){
						key_pressed = '7';
						break;
			HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN2_GPIO_Port, COLUMN2_Pin) == 0){
						key_pressed = '*';
						break;
			}
	case COLUMN3_Pin:
			HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN3_GPIO_Port, COLUMN3_Pin) == 0){
				key_pressed = '1';
				break;
			HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN3_GPIO_Port, COLUMN3_Pin) == 0){
						key_pressed = '4';
						break;
			HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN1_GPIO_Port, COLUMN1_Pin) == 0){
						key_pressed = '7';
						break;
			HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN3_GPIO_Port, COLUMN3_Pin) == 0){
						key_pressed = '*';
						break;
			}
	case COLUMN4_Pin:
			HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN4_GPIO_Port, COLUMN4_Pin) == 0){
				key_pressed = '1';
				break;
			HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN4_GPIO_Port, COLUMN4_Pin) == 0){
						key_pressed = '4';
						break;
			HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN4_GPIO_Port, COLUMN4_Pin) == 0){
						key_pressed = '7';
						break;
			HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
			if(HAL_GPIO_ReadPin(COLUMN4_GPIO_Port, COLUMN4_Pin) == 0){
						key_pressed = '*';
						break;
			}

	default:
		break;
	}
	if (GPIO_Pin == S1_Pin) {
		HAL_UART_Transmit(&huart2, (uint8_t *)"S1\r\n", 4, 10);
		if (HAL_GetTick() < (left_last_press_tick + 300)) { // if last press was in the last 300ms
			left_toggles = 0xFFFFFF; // a long time toggling (infinite)
		} else {
			left_toggles = 6;
		}
		left_last_press_tick = HAL_GetTick();
	} else if (GPIO_Pin == S2_Pin) {
		left_toggles = 0;
	}
}

void heartbeat(void)
{
	static uint32_t heartbeat_tick = 0;
	if (heartbeat_tick < HAL_GetTick()) {
		heartbeat_tick = HAL_GetTick() + 500;
		HAL_GPIO_TogglePin(D1_GPIO_Port, D1_Pin);
	}
}

void turn_signal_left(void)
{
	static uint32_t turn_toggle_tick = 0;
	if (turn_toggle_tick < HAL_GetTick()) {
		if (left_toggles > 0) {
			turn_toggle_tick = HAL_GetTick() + 500;
			HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
			left_toggles--;
		} else {
			HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
		}

	}
}
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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  /* Initialize ring buffer (control, memory, and capacity) */
  ring_buffer_init(&rb_usart3, mem_usart3, CAPACITY_USART3);
  ring_buffer_init(&rb_usart2, mem_usart2, CAPACITY_USART2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* Enable USART Rx interrupt to start receiving */
  HAL_UART_Receive_IT(&huart3, &data_usart3, 1);
  HAL_UART_Receive_IT(&huart2, &data_usart2, 1);
  while (1)
  {
	  uint8_t byte = 0;
	  if (ring_buffer_is_full(&rb_usart2) != 0) {
		  int8_t id_incorrect = 0;
		  char my_id[] = "1053821948";
		  for (uint8_t idx = 0; idx < sizeof(my_id); idx++) {
			  if (ring_buffer_read(&rb_usart2, &byte) != 0) { // 0x20
				  if (byte != my_id[idx]) {
					  id_incorrect = 1;
				  }
			  }
		  }
		  if (id_incorrect == 0) {
			  HAL_UART_Transmit(&huart2, "Sam C\r\n", 7, 10);
		  } else {
			  HAL_UART_Transmit(&huart2, "Error\r\n", 7, 10);
		  }
	  }
	  if (ring_buffer_is_empty(&rb_usart3) == 0) {
		  uint8_t data;
		  ring_buffer_read(&rb_usart3, &data);
		  HAL_UART_Transmit(&huart2, &data, 1, 10);
	  }
	  heartbeat();
	  turn_signal_left();

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D1_Pin|D3_Pin|ROW1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ROW2_Pin|ROW4_Pin|ROW3_Pin|D4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : S1_Pin S2_Pin */
  GPIO_InitStruct.Pin = S1_Pin|S2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D1_Pin D3_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = D1_Pin|D3_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : COLUMN1_Pin */
  GPIO_InitStruct.Pin = COLUMN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(COLUMN1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : COLUMN4_Pin */
  GPIO_InitStruct.Pin = COLUMN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(COLUMN4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : COLUMN2_Pin COLUMN3_Pin */
  GPIO_InitStruct.Pin = COLUMN2_Pin|COLUMN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW2_Pin ROW4_Pin ROW3_Pin D4_Pin */
  GPIO_InitStruct.Pin = ROW2_Pin|ROW4_Pin|ROW3_Pin|D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
