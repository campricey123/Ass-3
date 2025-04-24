
#include "Ass-3.h"

#if DO_QUESTION == 4

volatile uint8_t flag_Joy_A   = 0;
volatile uint8_t flag_Joy_D   = 0;
volatile uint8_t flag_Joy_C   = 0;
volatile uint8_t flag_Joy_CTR = 0;
//volatile uint8_t dma_transfer_complete = 0; // Not needed if not polling
uint32_t last_press_time = 0; // For debouncing
uint32_t debounce_delay = 100;  // Debounce delay in ms

#ifndef LED_GREEN_Pin
#define LED_GREEN_Pin   GPIO_PIN_12
#endif
#ifndef LED_RED_Pin
#define LED_RED_Pin     GPIO_PIN_14
#endif
#ifndef LED_BLUE_Pin
#define LED_BLUE_Pin    GPIO_PIN_15
#endif

static uint32_t dma_cmd_green = (LED_GREEN_Pin) | ((LED_RED_Pin | LED_BLUE_Pin) << 16);
static uint32_t dma_cmd_red   = (LED_RED_Pin)   | ((LED_GREEN_Pin | LED_BLUE_Pin) << 16);
static uint32_t dma_cmd_blue  = (LED_BLUE_Pin)  | ((LED_GREEN_Pin | LED_RED_Pin) << 16);
static uint32_t dma_cmd_off   = 0U | ((LED_GREEN_Pin | LED_RED_Pin | LED_BLUE_Pin) << 16);

void DMA_TransferCompleteCallback(DMA_HandleTypeDef *hdma) {
    if (hdma == &hdma_memtomem_dma2_stream0) {
        // dma_transfer_complete = 1;  // Not needed if not polling
        // printf("DMA Transfer Complete Callback executed!\n");
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == JOY_A_Pin) {
        flag_Joy_A = 1;
    }
    else if (GPIO_Pin == JOY_D_Pin) {
        flag_Joy_D = 1;
    }
    else if (GPIO_Pin == JOY_C_Pin) {
        flag_Joy_C = 1;
    }
    else if (GPIO_Pin == JOY_CTR_Pin) {
        flag_Joy_CTR = 1;
    }
    // No debouncing here - do it in main loop
}

void Ass_3_main(void) {
    HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, DMA_TransferCompleteCallback);

    while (1) {
       uint32_t current_time = HAL_GetTick(); // Get current time for debouncing

        if (flag_Joy_A && (current_time - last_press_time >= debounce_delay)) {
            flag_Joy_A = 0;
            //dma_transfer_complete = 0; // Not needed
            HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)&dma_cmd_green, (uint32_t)&(GPIOD->BSRR), 1);
            last_press_time = current_time;
        }
        else if (flag_Joy_D && (current_time - last_press_time >= debounce_delay)) {
            flag_Joy_D = 0;
            //dma_transfer_complete = 0;
            HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)&dma_cmd_red, (uint32_t)&(GPIOD->BSRR), 1);
             last_press_time = current_time;
        }
        else if (flag_Joy_C && (current_time - last_press_time >= debounce_delay)) {
            flag_Joy_C = 0;
            //dma_transfer_complete = 0;
            HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)&dma_cmd_blue, (uint32_t)&(GPIOD->BSRR), 1);
             last_press_time = current_time;
        }
        else if (flag_Joy_CTR && (current_time - last_press_time >= debounce_delay)) {
            flag_Joy_CTR = 0;
            //dma_transfer_complete = 0;
            HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)&dma_cmd_off, (uint32_t)&(GPIOD->BSRR), 1);
             last_press_time = current_time;
        }
        // HAL_Delay(50); //  Not needed
    }
}

#endif // DO_QUESTION == 4
