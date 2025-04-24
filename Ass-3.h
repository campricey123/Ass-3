/*
 * Ass-3.h
 *
 *  Created on: Apr 9, 2025
 *      Author: camer
 */
#ifndef SRC_ASS_3_H_
#define SRC_ASS_3_H_
#include "main.h"
// for printf
#include <stdio.h>
// Question to be completed
#define DO_QUESTION 4
// Parameters
#define TOGGLE_DELAY 100 // Period before toggling heartbeat LED (ms)
// Assignment functions
void Ass_3_main (void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin); // Interrupt callback declaration
void DMA_TransferCompleteCallback(DMA_HandleTypeDef *hdma); // DMA callback declar
extern DMA_HandleTypeDef hdma_memtomem_dma2_stream0;

// Joystick pin definitions (based on hardware)
#define JOY_A_Pin GPIO_PIN_4
#define JOY_A_GPIO_Port GPIOA
#define JOY_D_Pin GPIO_PIN_6
#define JOY_D_GPIO_Port GPIOC
#define JOY_C_Pin GPIO_PIN_15
#define JOY_C_GPIO_Port GPIOB
#define JOY_CTR_Pin GPIO_PIN_7
#define JOY_CTR_GPIO_Port GPIOC

#define LD4_Pin GPIO_PIN_12  // Green LED
#define LD4_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14  // Red LED
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15  // Blue LED
#define LD6_GPIO_Port GPIOD
extern volatile uint8_t flag_Joy_A;
extern volatile uint8_t flag_Joy_D;
extern volatile uint8_t flag_Joy_C;
extern volatile uint8_t flag_Joy_CTR;
extern volatile uint8_t dma_transfer_complete;




#endif /* SRC_ASS_3_H_ */
