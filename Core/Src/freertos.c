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
StreamBufferHandle_t StreamBufferHandle;
extern uint8_t rxbuffer[50];

/* USER CODE END Variables */
/* Definitions for UARTTask */
osThreadId_t UARTTaskHandle;
const osThreadAttr_t UARTTask_attributes = { .name = "UARTTask", .stack_size =
		128 * 4, .priority = (osPriority_t) osPriorityNormal, };
/* Definitions for KeyTask */
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = { .name = "KeyTask", .stack_size = 128
		* 4, .priority = (osPriority_t) osPriorityLow, };

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
	StreamBufferHandle = xStreamBufferCreate(20, 1);
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
void AppUARTTask(void *argument) {
	/* USER CODE BEGIN AppUARTTask */
	/* Infinite loop */
	for (;;) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		char temp[20] = { };
		xStreamBufferReceive(StreamBufferHandle, temp, 20, portMAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t*) temp, strlen(temp), 100);
		vTaskDelay(200);
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
void KeyTaskApp(void *argument) {
	/* USER CODE BEGIN KeyTaskApp */
	/* Infinite loop */
	for (;;) {
		if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
			vTaskDelay(10);
			if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
				uint8_t len = xStreamBufferBytesAvailable(StreamBufferHandle);
				if (len > 0) {
					xTaskNotifyGive(UARTTaskHandle);
				}

			}
		}
		vTaskDelay(200);
	}
	/* USER CODE END KeyTaskApp */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	if (huart->Instance == huart2.Instance) {
//
//		BaseType_t HigherPriorityTaskWoken = pdFALSE;
//		if (StreamBufferHandle != NULL) {
//			xStreamBufferSendFromISR(StreamBufferHandle, rxbuffer, 50,
//					&HigherPriorityTaskWoken);
//			portYIELD_FROM_ISR(HigherPriorityTaskWoken);
//
//		}
//		HAL_UART_Receive_IT(huart, rxbuffer, 4);
//
//	}
//}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart->Instance == huart2.Instance) {

		BaseType_t HigherPriorityTaskWoken = pdFALSE;
		if (StreamBufferHandle != NULL) {
			xStreamBufferSendFromISR(StreamBufferHandle, rxbuffer, 50,
					&HigherPriorityTaskWoken);
			portYIELD_FROM_ISR(HigherPriorityTaskWoken);

		}
		HAL_UARTEx_ReceiveToIdle_IT(&huart2, rxbuffer, 20);

	}
}
/* USER CODE END Application */

