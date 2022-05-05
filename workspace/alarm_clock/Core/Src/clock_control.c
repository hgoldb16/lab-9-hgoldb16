/*
 * clock_control.c
 *
 *  Created on: May 3, 2022
 *      Author: goldbh
 */

#include "main.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "project_functions.h"


void set_time(void){
	RTC_TimeTypeDef new_time;
	RTC_DateTypeDef new_date;
	HAL_UART_AbortTransmit(&huart1);
	HAL_RTC_GetTime(&hrtc, &new_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &new_date, RTC_FORMAT_BIN);
	char msg[50] = {'\0'};

	TIM2->CNT = 4*new_time.Hours;
	uint32_t current_count = TIM2->CNT;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		current_count = TIM2->CNT;
		if (((current_count <= 65535)&(current_count > 65000))|(current_count == 1)){
	  		  current_count = 0;
	  		  TIM2->CNT = 0;
		}
		else if ((current_count > 95)&(current_count<200)){
			current_count = 95;
			TIM2->CNT = 95;
		}
		sprintf(msg, "%02d:%02d:%02d\r", (current_count>>2), new_time.Minutes, new_time.Seconds);
		HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(msg), 100);
	}
	new_time.Hours = current_count>>2;
	HAL_Delay(500);

	TIM2->CNT = 4*new_time.Minutes;
	current_count = TIM2->CNT;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		current_count = TIM2->CNT;
		if (((current_count <= 65535)&(current_count > 65000))|(current_count == 1)){
	  		  current_count = 0;
	  		  TIM2->CNT = 0;
		}
		else if ((current_count > 239)&(current_count<400)){
			current_count = 239;
			TIM2->CNT = 239;
		}
		sprintf(msg, "%02d:%02d:%02d\r", new_time.Hours, (current_count>>2), new_time.Seconds);
				HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(msg), 100);
	}
	new_time.Minutes = current_count>>2;
	HAL_Delay(500);

	TIM2->CNT = 4*new_time.Seconds;
	current_count = TIM2->CNT;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		current_count = TIM2->CNT;
		if (((current_count <= 65535)&(current_count > 65000))|(current_count == 1)){
	  		  current_count = 0;
	  		  TIM2->CNT = 0;
		}
		else if ((current_count > 239)&(current_count<400)){
			current_count = 239;
			TIM2->CNT = 239;
		}
		sprintf(msg, "%02d:%02d:%02d\r", new_time.Hours, new_time.Minutes, (current_count>>2));
		HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(msg), 100);
	}
	new_time.Seconds = current_count>>2;
	HAL_RTC_SetTime(&hrtc, &new_time, RTC_FORMAT_BIN);

	return;
}

void set_alarm(void){
	RTC_AlarmTypeDef new_alarm;
	HAL_UART_AbortTransmit(&huart1);
	HAL_RTC_GetAlarm(&hrtc, &new_alarm,RTC_ALARM_A, RTC_FORMAT_BIN);

	char msg[50] = {'\0'};

	TIM2->CNT = 4*new_alarm.AlarmTime.Hours;
	uint32_t current_count = TIM2->CNT;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		current_count = TIM2->CNT;
		if (((current_count <= 65535)&(current_count > 65000))|(current_count == 1)){
	  		  current_count = 0;
	  		  TIM2->CNT = 0;
		}
		else if ((current_count > 95)&(current_count<200)){
			current_count = 95;
			TIM2->CNT = 95;
		}
		sprintf(msg, "%02d:%02d:%02d\r", (current_count>>2), new_alarm.AlarmTime.Minutes, new_alarm.AlarmTime.Seconds);
		HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(msg), 100);
	}
	new_alarm.AlarmTime.Hours = current_count>>2;
	HAL_Delay(500);

	TIM2->CNT = 4*new_alarm.AlarmTime.Minutes;
	current_count = TIM2->CNT;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		current_count = TIM2->CNT;
		if (((current_count <= 65535)&(current_count > 65000))|(current_count == 1)){
	  		  current_count = 0;
	  		  TIM2->CNT = 0;
		}
		else if ((current_count > 239)&(current_count<400)){
			current_count = 239;
			TIM2->CNT = 239;
		}
		sprintf(msg, "%02d:%02d:%02d\r", new_alarm.AlarmTime.Hours, (current_count>>2), new_alarm.AlarmTime.Seconds);
				HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(msg), 100);
	}
	new_alarm.AlarmTime.Minutes = current_count>>2;
	HAL_Delay(500);

	TIM2->CNT = 4*new_alarm.AlarmTime.Seconds;
	current_count = TIM2->CNT;
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		current_count = TIM2->CNT;
		if (((current_count <= 65535)&(current_count > 65000))|(current_count == 1)){
	  		  current_count = 0;
	  		  TIM2->CNT = 0;
		}
		else if ((current_count > 239)&(current_count<400)){
			current_count = 239;
			TIM2->CNT = 239;
		}
		sprintf(msg, "%02d:%02d:%02d\r", new_alarm.AlarmTime.Hours, new_alarm.AlarmTime.Minutes, (current_count>>2));
		HAL_UART_Transmit(&huart1, (uint8_t *)msg, sizeof(msg), 100);
	}
	new_alarm.AlarmTime.Seconds = current_count>>2;
	HAL_RTC_SetAlarm_IT(&hrtc, &new_alarm, RTC_FORMAT_BIN);


	return;
}


void snooze_alarm(void){
	RTC_AlarmTypeDef new_alarm;
	HAL_UART_AbortTransmit(&huart1);
	HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);
	HAL_RTC_GetAlarm(&hrtc, &new_alarm,RTC_ALARM_A, RTC_FORMAT_BIN);

	new_alarm.AlarmTime.Minutes = new_alarm.AlarmTime.Minutes + 9;
	HAL_RTC_SetAlarm_IT(&hrtc, &new_alarm, RTC_FORMAT_BIN);
	return;
}
