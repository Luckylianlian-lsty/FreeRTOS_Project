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
/* Definitions for BLUETask */
osThreadId_t BLUETaskHandle;
const osThreadAttr_t BLUETask_attributes = { .name = "BLUETask", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityLow, };
/* Definitions for GREENTask */
osThreadId_t GREENTaskHandle;
const osThreadAttr_t GREENTask_attributes = { .name = "GREENTask", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityBelowNormal6, };
/* Definitions for REDTask */
osThreadId_t REDTaskHandle;
const osThreadAttr_t REDTask_attributes = { .name = "REDTask", .stack_size = 128
		* 4, .priority = (osPriority_t) osPriorityNormal, };
/* Definitions for CountingSem */
osSemaphoreId_t CountingSemHandle;
const osSemaphoreAttr_t CountingSem_attributes = { .name = "CountingSem" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppBLUETask(void *argument);
void AppGREENTask(void *argument);
void AppREDTask(void *argument);

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
	/* creation of CountingSem */
	CountingSemHandle = osSemaphoreNew(2, 2, &CountingSem_attributes);

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
	/* creation of BLUETask */
	BLUETaskHandle = osThreadNew(AppBLUETask, NULL, &BLUETask_attributes);

	/* creation of GREENTask */
	GREENTaskHandle = osThreadNew(AppGREENTask, NULL, &GREENTask_attributes);

	/* creation of REDTask */
	REDTaskHandle = osThreadNew(AppREDTask, NULL, &REDTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppBLUETask */
/**
 * @brief  Function implementing the BLUETask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppBLUETask */
void AppBLUETask(void *argument) {
	/* USER CODE BEGIN AppBLUETask */
	/* Infinite loop */
	for (;;) {
		if (xSemaphoreTake(CountingSemHandle,portMAX_DELAY) == pdTRUE) {
			HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, GPIO_PIN_SET);
			vTaskDelay(pdMS_TO_TICKS(2000));
			HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, GPIO_PIN_RESET);
			xSemaphoreGive(CountingSemHandle);
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	/* USER CODE END AppBLUETask */
}

/* USER CODE BEGIN Header_AppGREENTask */
/**
 * @brief Function implementing the GREENTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppGREENTask */
void AppGREENTask(void *argument) {
	/* USER CODE BEGIN AppGREENTask */
	/* Infinite loop */
	for (;;) {
		if (xSemaphoreTake(CountingSemHandle,portMAX_DELAY) == pdTRUE) {
			HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
			vTaskDelay(pdMS_TO_TICKS(2000));
			HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_RESET);
			xSemaphoreGive(CountingSemHandle);
		}
		vTaskDelay(pdMS_TO_TICKS(100));

	}
	/* USER CODE END AppGREENTask */
}

/* USER CODE BEGIN Header_AppREDTask */
/**
 * @brief Function implementing the REDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AppREDTask */
void AppREDTask(void *argument) {
	/* USER CODE BEGIN AppREDTask */
	/* Infinite loop */
	for (;;) {
		if (xSemaphoreTake(CountingSemHandle,portMAX_DELAY) == pdTRUE) {
			HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
			vTaskDelay(pdMS_TO_TICKS(2000));
			HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_RESET);
			xSemaphoreGive(CountingSemHandle);
		}
		vTaskDelay(pdMS_TO_TICKS(100));

	}
	/* USER CODE END AppREDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

