/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "lcd.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_it.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CODE 637
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

//����������, � �������� �������� ������
extern uint8_t flag;
extern int second;
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t hour_rel;
extern uint8_t minute_rel;
extern uint8_t hour_rel_two;
extern uint8_t minute_rel_two;
extern uint8_t hour_rel_delay;
extern uint8_t minute_rel_delay;

//�����
uint8_t btnpressed = 1;
uint8_t menu = 0;
uint8_t clear_flag = 0;
uint8_t code_flag = 0;

//���������� ��� ������ ������ �� �������
uint8_t digit_one_h = 0;
uint8_t digit_two_h  = 0;
uint8_t digit_one_m = 0;
uint8_t digit_two_m = 0;
uint8_t digit_one_pass = 0;
uint8_t digit_two_pass = 0;
uint8_t digit_three_pass = 0;
uint8_t digit_one_rel_h = 0;
uint8_t digit_one_rel_m = 0;
uint8_t digit_two_rel_h = 0;
uint8_t digit_two_rel_m = 0;
uint8_t digit_one_rel_two_h = 0;
uint8_t digit_one_rel_two_m = 0;
uint8_t digit_two_rel_two_h = 0;
uint8_t digit_two_rel_two_m = 0;
uint8_t digit_one_rel_delay_h = 0;
uint8_t digit_one_rel_delay_m = 0;
uint8_t digit_two_rel_delay_h = 0;
uint8_t digit_two_rel_delay_m = 0;

//���������� ������
uint16_t pass = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
void delay(void);
void LCD_WriteData(uint8_t dt);
void LCD_Command(uint8_t dt);
void LCD_Data(uint8_t dt);
void LCD_ini();
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_SetPos(uint8_t x, uint8_t y);
void LCD_String(char* st, uint8_t n);
void display (char* dsp);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void digit_one()                        //������� ������ ������ ����� ����� - ������� �� 10
{
  digit_one_h = hour/10;
  digit_one_m = minute/10;
  digit_one_pass = (pass/100)%10;
  digit_one_rel_h = hour_rel/10;
  digit_one_rel_m = minute_rel/10;
  digit_one_rel_two_h = hour_rel_two/10;
  digit_one_rel_two_m = minute_rel_two/10;
  digit_one_rel_delay_h = hour_rel_delay/10;
  digit_one_rel_delay_m = minute_rel_delay/10;
  
}


void digit_two()                        //������� ������ ������ ����� ����� - ������� �� ������� �� 10
{
  digit_two_h = hour%10;
  digit_two_m = minute%10;
  digit_two_pass = (pass/10)%10;
  digit_two_rel_h = hour_rel%10;
  digit_two_rel_m = minute_rel%10;
  digit_two_rel_two_h = hour_rel_two%10;
  digit_two_rel_two_m = minute_rel_two%10;
  digit_two_rel_delay_h = hour_rel_delay%10;
  digit_two_rel_delay_m = minute_rel_delay%10;
}

void digit_three()
{
 digit_three_pass = pass%10; 
}

//�������-����������, � ����������� �� �������� �����, ��������� �� ��� ���� ��������, ���������� � ����������� ����� ��� ����� ���������� flag
void modecheck()
{
  switch(btnpressed)
  {
    case 1:
      if (clear_flag == 1)
      {
        LCD_Clear();
        /*LCD_SetPos(0,0);
        LCD_String("Time is:", 0);*/
      }
      digit_one();
      digit_two();
      /*LCD_SetPos(10,0);
      LCD_SendChar((char)digit_one_h + 0x30);                           //����� � �����: +0x30 - ���������� 48 � �������� ��� ������������ ������� ASCII
      LCD_SetPos(11,0);
      LCD_SendChar((char)digit_two_h + 0x30);
      LCD_SetPos(12,0);
      LCD_SendChar(':');
      LCD_SetPos(13,0);
      LCD_SendChar((char)digit_one_m + 0x30);
      LCD_SetPos(14,0);
      LCD_SendChar((char)digit_two_m + 0x30);*/
      display("Time is: " + ((char)digit_one_h+0x30) + ((char)digit_two_h+0x30) + ':' + ((char)digit_one_m + 0x30) + ((char)digit_two_m + 0x30));
      LCD_SetPos(0,1);
      LCD_String("Time del: ", 1);
      LCD_SetPos(10, 1);
      LCD_SendChar((char)digit_one_rel_delay_h + 0x30);
      LCD_SetPos(11, 1);
      LCD_SendChar((char)digit_two_rel_delay_h + 0x30);
      LCD_SetPos(12, 1);
      LCD_SendChar(':');
      LCD_SetPos(13, 1);
      LCD_SendChar((char)digit_one_rel_delay_m + 0x30);
      LCD_SetPos(14, 1);
      LCD_SendChar((char)digit_two_rel_delay_m + 0x30);
      clear_flag = 0;
      break;
    case 2:
      if (pass != CODE)
      {
        code_flag = 1;
      }
      else if (pass == CODE)
      {
        code_flag = 0;
      }
      menu = 1;
      //�����������, ���� �� ������ ������ ���
      
      if (code_flag == 1)                               //1. �������� ����� ����, ���� ���������� - ��������� ���
      {
        digit_one();
        digit_two();
        digit_three();
        if (clear_flag != 0)
        {
          LCD_Clear();
          LCD_SetPos(0,0);
          LCD_String("Enter password:", 0);
        }
        LCD_SetPos(0,1);
        LCD_SendChar((char)digit_one_pass + 0x30);
        LCD_SetPos(1,1);
        LCD_SendChar((char)digit_two_pass + 0x30);
        LCD_SetPos(2,1);
        LCD_SendChar((char)digit_three_pass + 0x30);
        clear_flag = 0;
      }
      if (code_flag == 0 && pass == CODE)               //2. ���� ���� �� ��� ��������� � 1, ��� �� �����������
      {
        clear_flag = 1;                                 //��������� ����� ������� �������
      }
      //�� �����������, ���� �� ������ ������ ���
      if (code_flag == 0)                               //3. �������� ����� ����, ���� ������� - ��������� ���
      {
        if (clear_flag == 1)
        {
          LCD_Clear();
          LCD_SetPos(3, 0);
          LCD_String("Set Time: ", 0);
        }
        digit_one();
        digit_two();
        LCD_SetPos(0, 1);
        LCD_SendChar((char)digit_one_h + 0x30);
        LCD_SetPos(1,1);
        LCD_SendChar((char)digit_two_h + 0x30);
        LCD_SetPos(2,1);
        LCD_SendChar(':');
        LCD_SetPos(3,1);
        LCD_SendChar((char)digit_one_m + 0x30);
        LCD_SetPos(4,1);
        LCD_SendChar((char)digit_two_m + 0x30);
        clear_flag = 0;
      }
      break;
    /*case 3:
      menu = 2;
      if (clear_flag == 1)
      {
        LCD_Clear();
        LCD_SetPos(0,0);
        LCD_String("Set rel time:", 0);
      }
      digit_one();
      digit_two();
      LCD_SetPos(0,1);
      LCD_SendChar((char)digit_one_rel_h + 0x30);
      LCD_SetPos(1,1);
      LCD_SendChar((char)digit_two_rel_h + 0x30);
      LCD_SetPos(2,1);
      LCD_SendChar(':');
      LCD_SetPos(3,1);
      LCD_SendChar((char)digit_one_rel_m + 0x30);
      LCD_SetPos(4,1);
      LCD_SendChar((char)digit_two_rel_m + 0x30);
      LCD_SetPos(6,1);
      LCD_SendChar((char)digit_one_rel_two_h + 0x30);
      LCD_SetPos(7,1);
      LCD_SendChar((char)digit_two_rel_two_h + 0x30);
      LCD_SetPos(8,1);
      LCD_SendChar(':');
      LCD_SetPos(9,1);
      LCD_SendChar((char)digit_one_rel_m + 0x30);
      LCD_SetPos(10,1);
      LCD_SendChar((char)digit_two_rel_m + 0x30);
      clear_flag = 0;
      */
    case 4:
      digit_one();
      digit_two();
      LCD_SetPos(10,0);
      LCD_SendChar((char)digit_one_h + 0x30);
      LCD_SetPos(11,0);
      LCD_SendChar((char)digit_two_h + 0x30);
      LCD_SetPos(12,0);
      LCD_SendChar(':');
      LCD_SetPos(13,0);
      LCD_SendChar((char)digit_one_m + 0x30);
      LCD_SetPos(14,0);
      LCD_SendChar((char)digit_two_m + 0x30);
      break;
    default:
      btnpressed = 1;
      break;
  }
}

void display(char* dsp)
  {
    for (uint8_t i = 0; i<sizeof(dsp); i++)
    {
      if (i <= 15)
      {
        LCD_SetPos(i, 0);
        LCD_SendChar(dsp[i]);
      }
      else if (i > 15 && i <= 31)
      {
        LCD_SetPos(i, 1);
        LCD_SendChar(dsp[i]);
      }
      else
      {
        LCD_Clear();
        LCD_String("Error Input", 0);
        HAL_Delay(5000);
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
  char hello[] = "CUD Home Station";
  char ver[] = "ver. 0.3 (dev)";
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
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  LCD_ini();
  LCD_SetPos(0, 0);
  LCD_String(hello, 0);
  LCD_SetPos(0, 1);
  LCD_String(ver, 1);
  HAL_Delay(5000);
  LCD_Clear();
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start(&htim4);
  HAL_TIM_Base_Start_IT(&htim4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      modecheck();
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Enables the Clock Security System 
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  NVIC_SetPriority(TIM2_IRQn, 1);
  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7199;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */
  NVIC_SetPriority(TIM4_IRQn, 2);
  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D7_Pin|D6_Pin|D5_Pin|D4_Pin 
                          |LED_BTN_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, E_Pin|R_W_Pin|RS_Pin|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|LED_BTN_6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|LED_BTN_2_Pin|LED_BTN_3_Pin 
                          |LED_BTN_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D7_Pin D6_Pin D5_Pin D4_Pin 
                           LED_BTN_1_Pin */
  GPIO_InitStruct.Pin = D7_Pin|D6_Pin|D5_Pin|D4_Pin 
                          |LED_BTN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : E_Pin R_W_Pin RS_Pin PB12 
                           PB13 PB14 PB15 LED_BTN_6_Pin */
  GPIO_InitStruct.Pin = E_Pin|R_W_Pin|RS_Pin|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|LED_BTN_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 LED_BTN_2_Pin LED_BTN_3_Pin 
                           LED_BTN_4_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|LED_BTN_2_Pin|LED_BTN_3_Pin 
                          |LED_BTN_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_4_Pin BTN_3_Pin */
  GPIO_InitStruct.Pin = BTN_4_Pin|BTN_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_BTN_5_Pin */
  GPIO_InitStruct.Pin = LED_BTN_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_BTN_5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_1_Pin BTN_2_Pin BTN_5_Pin BTN_6_Pin */
  GPIO_InitStruct.Pin = BTN_1_Pin|BTN_2_Pin|BTN_5_Pin|BTN_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
