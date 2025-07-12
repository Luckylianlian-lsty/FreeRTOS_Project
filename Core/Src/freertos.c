/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"event_groups.h"
#include"queue.h"
#include"timers.h"
#include"stdio.h"
#include"string.h"
#include"usart.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = { .name = "defaultTask",
		.stack_size = 128 * 4, .priority = (osPriority_t) osPriorityNormal, };
/* Definitions for TimerPeriod */
osTimerId_t TimerPeriodHandle;
const osTimerAttr_t TimerPeriod_attributes = { .name = "TimerPeriod" };
/* Definitions for TimerOnce */
osTimerId_t TimerOnceHandle;
const osTimerAttr_t TimerOnce_attributes = { .name = "TimerOnce" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void TimerPeriodCallback(void *argument);
void TimerOnceCallback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* Create the timer(s) */
	/* creation of TimerPeriod */
	TimerPeriodHandle = osTimerNew(TimerPeriodCallback, osTimerPeriodic, NULL,
			&TimerPeriod_attributes);

	/* creation of TimerOnce */
	TimerOnceHandle = osTimerNew(TimerOnceCallback, osTimerOnce, NULL,
			&TimerOnce_attributes);

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	xTimerChangePeriod(TimerOnceHandle, 3000, 100);
	xTimerChangePeriod(TimerPeriodHandle, 2000, 100);
	xTimerStart(TimerPeriodHandle, 100);
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* creation of defaultTask */
	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL,
			&defaultTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		if (HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin) == GPIO_PIN_RESET) {
			vTaskDelay(10);
			if (HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin) == GPIO_PIN_RESET) {
				xTimerStart(TimerOnceHandle, 100);
			}

		}
		vTaskDelay(100);
	}
	/* USER CODE END StartDefaultTask */
}

/* TimerPeriodCallback function */
void TimerPeriodCallback(void *argument) {
	/* USER CODE BEGIN TimerPeriodCallback */
	char temp[] = "Period\n";
	HAL_UART_Transmit(&huart2, (uint8_t*) temp, strlen(temp), 100);
	HAL_GPIO_TogglePin(Blue_GPIO_Port, Blue_Pin);
	/* USER CODE END TimerPeriodCallback */
}

/* TimerOnceCallback function */
void TimerOnceCallback(void *argument) {
	/* USER CODE BEGIN TimerOnceCallback */
	char temp[] = "Once\n";
	HAL_UART_Transmit(&huart2, (uint8_t*) temp, strlen(temp), 100);
	/* USER CODE END TimerOnceCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

