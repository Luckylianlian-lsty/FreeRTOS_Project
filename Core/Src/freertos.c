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
#include"usart.h"
#include"stdio.h"
#include"string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define BIT0 (1<<0)
#define BIT1 (1<<1)
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
/* Definitions for AllTask */
osThreadId_t AllTaskHandle;
const osThreadAttr_t AllTask_attributes = {
  .name = "AllTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UARTTask */
osThreadId_t UARTTaskHandle;
const osThreadAttr_t UARTTask_attributes = {
  .name = "UARTTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Key1Task */
osThreadId_t Key1TaskHandle;
const osThreadAttr_t Key1Task_attributes = {
  .name = "Key1Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Key2Task */
osThreadId_t Key2TaskHandle;
const osThreadAttr_t Key2Task_attributes = {
  .name = "Key2Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for EventGroups */
osEventFlagsId_t EventGroupsHandle;
const osEventFlagsAttr_t EventGroups_attributes = {
  .name = "EventGroups"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppAllTask(void *argument);
void AppLedTask(void *argument);
void AppUARTTask(void *argument);
void AppKey1Task(void *argument);
void AppKey2Task(void *argument);

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

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of AllTask */
  AllTaskHandle = osThreadNew(AppAllTask, NULL, &AllTask_attributes);

  /* creation of LedTask */
  LedTaskHandle = osThreadNew(AppLedTask, NULL, &LedTask_attributes);

  /* creation of UARTTask */
  UARTTaskHandle = osThreadNew(AppUARTTask, NULL, &UARTTask_attributes);

  /* creation of Key1Task */
  Key1TaskHandle = osThreadNew(AppKey1Task, NULL, &Key1Task_attributes);

  /* creation of Key2Task */
  Key2TaskHandle = osThreadNew(AppKey2Task, NULL, &Key2Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of EventGroups */
  EventGroupsHandle = osEventFlagsNew(&EventGroups_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppAllTask */
/**
 * @brief  Function implementing the AllTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppAllTask */
void AppAllTask(void *argument)
{
  /* USER CODE BEGIN AppAllTask */
	/* Infinite loop */
	for (;;) {
		xEventGroupWaitBits(EventGroupsHandle, BIT0|BIT1, pdTRUE, pdTRUE, portMAX_DELAY);
		HAL_GPIO_TogglePin(Green_GPIO_Port, Green_Pin);
		HAL_GPIO_TogglePin(Red_GPIO_Port, Red_Pin);
		vTaskDelay(pdMS_TO_TICKS(500));
		HAL_GPIO_TogglePin(Green_GPIO_Port, Green_Pin);
		HAL_GPIO_TogglePin(Red_GPIO_Port, Red_Pin);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
  /* USER CODE END AppAllTask */
}

/* USER CODE BEGIN Header_AppLedTask */
/**
 * @brief Function implementing the LedTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppLedTask */
void AppLedTask(void *argument)
{
  /* USER CODE BEGIN AppLedTask */
	/* Infinite loop */
	for (;;) {
		xEventGroupWaitBits(EventGroupsHandle, BIT0|BIT1, pdFALSE, pdFALSE, portMAX_DELAY);
		HAL_GPIO_TogglePin(Blue_GPIO_Port, Blue_Pin);
		vTaskDelay(pdMS_TO_TICKS(1000));
		HAL_GPIO_TogglePin(Blue_GPIO_Port, Blue_Pin);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
  /* USER CODE END AppLedTask */
}

/* USER CODE BEGIN Header_AppUARTTask */
/**
 * @brief Function implementing the UARTTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppUARTTask */
void AppUARTTask(void *argument)
{
  /* USER CODE BEGIN AppUARTTask */
	/* Infinite loop */
	for (;;) {
		xEventGroupWaitBits(EventGroupsHandle, BIT0|BIT1, pdTRUE, pdTRUE, portMAX_DELAY);
		char temp[50]={};
		sprintf(temp,"All\n");
		HAL_UART_Transmit(&huart2, (uint8_t*)temp, strlen(temp), 100);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
  /* USER CODE END AppUARTTask */
}

/* USER CODE BEGIN Header_AppKey1Task */
/**
 * @brief Function implementing the Key1Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppKey1Task */
void AppKey1Task(void *argument)
{
  /* USER CODE BEGIN AppKey1Task */
	/* Infinite loop */
	for (;;) {
		if (HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin) == GPIO_PIN_RESET) {
			vTaskDelay(10);
			if (HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin) == GPIO_PIN_RESET) {
				xEventGroupSetBits(EventGroupsHandle, BIT0);
			}
		}
		vTaskDelay(100);
	}
  /* USER CODE END AppKey1Task */
}

/* USER CODE BEGIN Header_AppKey2Task */
/**
 * @brief Function implementing the Key2Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppKey2Task */
void AppKey2Task(void *argument)
{
  /* USER CODE BEGIN AppKey2Task */
	/* Infinite loop */
	for (;;) {
		if (HAL_GPIO_ReadPin(Key2_GPIO_Port, Key2_Pin) == GPIO_PIN_RESET) {
			vTaskDelay(10);
			if (HAL_GPIO_ReadPin(Key2_GPIO_Port, Key2_Pin) == GPIO_PIN_RESET) {
				xEventGroupSetBits(EventGroupsHandle, BIT1);
			}
		}
		vTaskDelay(100);
	}
  /* USER CODE END AppKey2Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

