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
#include"semphr.h"
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
/* Definitions for LEDTask */
osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = { .name = "LEDTask", .stack_size = 128
		* 4, .priority = (osPriority_t) osPriorityNormal, };
/* Definitions for KEY1Task */
osThreadId_t KEY1TaskHandle;
const osThreadAttr_t KEY1Task_attributes = { .name = "KEY1Task", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityLow, };
/* Definitions for BinSema */
osSemaphoreId_t BinSemaHandle;
const osSemaphoreAttr_t BinSema_attributes = { .name = "BinSema" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppLEDTask(void *argument);
void AppKEY1Task(void *argument);

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

	/* Create the semaphores(s) */
	/* creation of BinSema */
	BinSemaHandle = osSemaphoreNew(1, 1, &BinSema_attributes);

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
	/* creation of LEDTask */
	LEDTaskHandle = osThreadNew(AppLEDTask, NULL, &LEDTask_attributes);

	/* creation of KEY1Task */
	KEY1TaskHandle = osThreadNew(AppKEY1Task, NULL, &KEY1Task_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppLEDTask */
/**
 * @brief  Function implementing the LEDTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppLEDTask */
void AppLEDTask(void *argument) {
	/* USER CODE BEGIN AppLEDTask */
	/* Infinite loop */
	for (;;) {
		if (xSemaphoreTake(BinSemaHandle,portMAX_DELAY) == pdTRUE) {
			for (int i = 0; i < 5; i++) {
				HAL_GPIO_TogglePin(BLUE_GPIO_Port, BLUE_Pin);
				vTaskDelay(pdMS_TO_TICKS(500));
			}
		}

		vTaskDelay(10);
	}
	/* USER CODE END AppLEDTask */
}

/* USER CODE BEGIN Header_AppKEY1Task */
/**
 * @brief Function implementing the KEY1Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppKEY1Task */
void AppKEY1Task(void *argument) {
	/* USER CODE BEGIN AppKEY1Task */
	/* Infinite loop */
	for (;;) {
		if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
			vTaskDelay(pdMS_TO_TICKS(10));
			if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
				xSemaphoreGive(BinSemaHandle);
			}
		}
		vTaskDelay(100);
	}
	/* USER CODE END AppKEY1Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

