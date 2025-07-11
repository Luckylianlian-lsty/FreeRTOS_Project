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
#include"stream_buffer.h"
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
StreamBufferHandle_t StreamBufferHandle;
/* USER CODE END Variables */
/* Definitions for UARTTask */
osThreadId_t UARTTaskHandle;
const osThreadAttr_t UARTTask_attributes = {
  .name = "UARTTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for KeyTask */
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
  .name = "KeyTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppUARTTask(void *argument);
void KeyTaskApp(void *argument);

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
  /* creation of UARTTask */
  UARTTaskHandle = osThreadNew(AppUARTTask, NULL, &UARTTask_attributes);

  /* creation of KeyTask */
  KeyTaskHandle = osThreadNew(KeyTaskApp, NULL, &KeyTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  StreamBufferHandle=xStreamBufferCreate(20,1);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppUARTTask */
/**
  * @brief  Function implementing the UARTTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppUARTTask */
void AppUARTTask(void *argument)
{
  /* USER CODE BEGIN AppUARTTask */
  /* Infinite loop */
  for(;;)
  {

    osDelay(1);
  }
  /* USER CODE END AppUARTTask */
}

/* USER CODE BEGIN Header_KeyTaskApp */
/**
* @brief Function implementing the KeyTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KeyTaskApp */
void KeyTaskApp(void *argument)
{
  /* USER CODE BEGIN KeyTaskApp */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END KeyTaskApp */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==huart2)
	{
		uint8_t temp[20];
		xStreamBufferSendFromISR(StreamBufferHandle, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken)
	}
}
/* USER CODE END Application */

