/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern uint8_t btnpressed;
extern uint8_t menu;
extern uint8_t clear_flag;
extern uint16_t pass;
extern uint8_t code_flag;

int count = 0;
uint8_t flag = 0;
int hour_rel_delay_math = 0;
int minute_rel_delay_math = 0;
uint8_t hour = 0;
uint8_t minute = 0;
int second = 0;
uint8_t hour_rel = 11;
uint8_t minute_rel = 0;
uint8_t hour_rel_two = 22;
uint8_t minute_rel_two = 0;
uint8_t hour_rel_delay = 0;
uint8_t minute_rel_delay = 0;
uint8_t second_time_flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void modecheck();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  HAL_RCC_NMI_IRQHandler();
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
  //Проверка попадания в разрешённый промежуток времени "("Вызов раз в 1с ")"
  if ((hour >= hour_rel) && (hour < hour_rel_two))
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  }
  else 
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  }
  //Часы
  if (second > 59)
  {
    second = 0;
    minute++;
    hour_rel_delay_math = ((hour_rel_two*60+minute_rel_two)-(hour*60+minute));
    minute_rel_delay_math = ((hour_rel_two*60+minute_rel_two)-(hour*60+minute));
    hour_rel_delay = (hour_rel_delay_math/60);
    minute_rel_delay = (minute_rel_delay_math%60);
  }
  if (minute > 59)
  {
    minute = 0;
    hour++;
  }
  if (hour > 23)
  {
    hour = 0;
  }
  second++;
  //Тот самый флаг, который подключает modecheck
  flag = 1;
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
  //Обработчик кнопок "("Вызов раз в 100мс ")"
  if (HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == 1 && menu == 0) 
  {
    btnpressed = 1;
    HAL_GPIO_WritePin(LED_BTN_1_GPIO_Port, LED_BTN_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_BTN_2_GPIO_Port, LED_BTN_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_3_GPIO_Port, LED_BTN_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_4_GPIO_Port, LED_BTN_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_6_GPIO_Port, LED_BTN_6_Pin, GPIO_PIN_RESET);
  }
  else if (HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == 1 && menu == 1 && code_flag != 1)
  {
    hour--;
  }
  else if (HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == 1 && menu == 1 && code_flag == 1)
  {
    pass--;
  }
  else if (HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == 1 && menu == 2)
  {
     hour_rel--;
  }
    else if (HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == 1 && menu == 2 && second_time_flag == 1)
  {
    hour_rel_two--;
  }
  if (HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == 1 && menu == 0) 
  {
    btnpressed = 2;
    HAL_GPIO_WritePin(LED_BTN_1_GPIO_Port, LED_BTN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_2_GPIO_Port, LED_BTN_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_BTN_3_GPIO_Port, LED_BTN_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_4_GPIO_Port, LED_BTN_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_6_GPIO_Port, LED_BTN_6_Pin, GPIO_PIN_RESET);
    clear_flag = 1;
  }
  else if (HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == 1 && menu == 1  && code_flag != 1)
  {
    hour++;
  }
  else if (HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == 1 && menu == 1 && code_flag == 1)
  {
    pass++;
  }
  else if (HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == 1 && menu == 2)
  {
     hour_rel++;
  }
  else if (HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == 1 && menu == 2 && second_time_flag == 1)
  {
    hour_rel_two++;
  }
  /*if (HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin) == 1 && menu == 0) 
  {
    btnpressed = 3;
    HAL_GPIO_WritePin(LED_BTN_1_GPIO_Port, LED_BTN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_2_GPIO_Port, LED_BTN_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_3_GPIO_Port, LED_BTN_3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_BTN_4_GPIO_Port, LED_BTN_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_6_GPIO_Port, LED_BTN_6_Pin, GPIO_PIN_RESET);
  }
  else if (HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin) == 1 && menu == 1)
  {
    minute++;
  }
  else if (HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin) == 1 && menu == 2)
  {
    minute_rel++;
  }
  else if (HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin) == 1 && menu == 2 && second_time_flag == 1)
  {
    minute_rel_two++;
  }
  */
  /*if (HAL_GPIO_ReadPin(BTN_4_GPIO_Port, BTN_4_Pin) == 1 && menu == 0) 
  {
    btnpressed = 4;
    HAL_GPIO_WritePin(LED_BTN_1_GPIO_Port, LED_BTN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_2_GPIO_Port, LED_BTN_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_3_GPIO_Port, LED_BTN_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_4_GPIO_Port, LED_BTN_4_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_6_GPIO_Port, LED_BTN_6_Pin, GPIO_PIN_RESET);
  }
  else if (HAL_GPIO_ReadPin(BTN_4_GPIO_Port, BTN_4_Pin) == 1 && menu == 1)
  {
    minute--;
  }
    else if (HAL_GPIO_ReadPin(BTN_4_GPIO_Port, BTN_4_Pin) == 1 && menu == 2)
  {
    minute_rel--;
  }
  else if (HAL_GPIO_ReadPin(BTN_4_GPIO_Port, BTN_4_Pin) == 1 && menu == 2 && second_time_flag == 1)
  {
    minute_rel_two--;
  }
  */
  if (HAL_GPIO_ReadPin(BTN_5_GPIO_Port, BTN_5_Pin) == 1 && menu == 0)
  {
    btnpressed = 5;
    HAL_GPIO_WritePin(LED_BTN_1_GPIO_Port, LED_BTN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_2_GPIO_Port, LED_BTN_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_3_GPIO_Port, LED_BTN_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_4_GPIO_Port, LED_BTN_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_BTN_6_GPIO_Port, LED_BTN_6_Pin, GPIO_PIN_RESET);
  }
  else if (HAL_GPIO_ReadPin(BTN_5_GPIO_Port, BTN_5_Pin) == 1 && menu == 1)
  {
    btnpressed = 1;
    menu = 0;
    clear_flag = 1;
    pass = 0;
  }
    else if (HAL_GPIO_ReadPin(BTN_5_GPIO_Port, BTN_5_Pin) == 1 && menu == 2)
  {
    menu = 0;
    btnpressed = 1;
    clear_flag = 1;
    second_time_flag = 0;
  }
  
  /*if (HAL_GPIO_ReadPin(BTN_6_GPIO_Port, BTN_6_Pin) == 1 && menu == 0)
  {
    btnpressed = 6; 
    HAL_GPIO_WritePin(LED_BTN_1_GPIO_Port, LED_BTN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_2_GPIO_Port, LED_BTN_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_3_GPIO_Port, LED_BTN_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_4_GPIO_Port, LED_BTN_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_5_GPIO_Port, LED_BTN_5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_BTN_6_GPIO_Port, LED_BTN_6_Pin, GPIO_PIN_SET);
  }
  else if (HAL_GPIO_ReadPin(BTN_6_GPIO_Port, BTN_6_Pin) == 1 && menu == 2)
  {
    second_time_flag = 1;
  }
  */
  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
