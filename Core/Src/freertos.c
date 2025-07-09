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
#include"stdio.h"
#include"string.h"
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
/* Definitions for KEY1Task */
osThreadId_t KEY1TaskHandle;
const osThreadAttr_t KEY1Task_attributes = {
  .name = "KEY1Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UARTTask */
osThreadId_t UARTTaskHandle;
const osThreadAttr_t UARTTask_attributes = {
  .name = "UARTTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Queue */
osMessageQueueId_t QueueHandle;
const osMessageQueueAttr_t Queue_attributes = {
  .name = "Queue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppKEY1Task(void *argument);
void AppUARTTask(void *argument);

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

  /* Create the queue(s) */
  /* creation of Queue */
  QueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of KEY1Task */
  KEY1TaskHandle = osThreadNew(AppKEY1Task, NULL, &KEY1Task_attributes);

  /* creation of UARTTask */
  UARTTaskHandle = osThreadNew(AppUARTTask, NULL, &UARTTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppKEY1Task */
/**
  * @brief  Function implementing the KEY1Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppKEY1Task */
void AppKEY1Task(void *argument)
{
  /* USER CODE BEGIN AppKEY1Task */
  /* Infinite loop */
  for(;;)
  {
	  if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)==GPIO_PIN_RESET)
	  {
		  uint16_t key1=1;
		  xQueueSendToBack(QueueHandle,&key1,pdMS_TO_TICKS(100));
		  vTaskDelay(pdMS_TO_TICKS(500));
	  }
    osDelay(1);
  }
  /* USER CODE END AppKEY1Task */
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
  for(;;)
  {
	  uint16_t rxbuffer=0;
	  char temp[50];
	  if(xQueueReceive(QueueHandle, &rxbuffer, portMAX_DELAY)==pdPASS)
	  {
		  sprintf(temp,"接收data为：%d",rxbuffer);
		  HAL_UART_Transmit(&huart2, (uint8_t*)temp, strlen(temp), 100);
		  vTaskDelay(pdMS_TO_TICKS(100));
	  }
    osDelay(1);
  }
  /* USER CODE END AppUARTTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

