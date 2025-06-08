/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);

  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
  /**ADC1 GPIO Configuration
  PA6   ------> ADC1_INP3
  PF12   ------> ADC1_INP6
  PF11   ------> ADC1_INP2
  PA4   ------> ADC1_INP18
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_12|LL_GPIO_PIN_11;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* ADC1 DMA Init */

  /* ADC1 Init */
  LL_DMA_SetPeriphRequest(DMA2, LL_DMA_STREAM_4, LL_DMAMUX1_REQ_ADC1);

  LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_4, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_4, LL_DMA_PRIORITY_MEDIUM);

  LL_DMA_SetMode(DMA2, LL_DMA_STREAM_4, LL_DMA_MODE_CIRCULAR);

  LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_4, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_4, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_4, LL_DMA_PDATAALIGN_HALFWORD);

  LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_4, LL_DMA_MDATAALIGN_HALFWORD);

  LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_4);

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B_OPT;
  ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
  LL_ADC_Init(ADC1, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS;
  ADC_REG_InitStruct.SequencerDiscont = DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_ASYNC_DIV16;
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);

  /* Disable ADC deep power down (enabled by default after reset state) */
  LL_ADC_DisableDeepPowerDown(ADC1);
  /* Enable ADC internal voltage regulator */
  LL_ADC_EnableInternalRegulator(ADC1);
  /* Delay for ADC internal voltage regulator stabilization. */
  /* Compute number of CPU cycles to wait for, from delay in us. */
  /* Note: Variable divided by 2 to compensate partially */
  /* CPU processing cycles (depends on compilation optimization). */
  /* Note: If system core clock frequency is below 200kHz, wait time */
  /* is only a few CPU processing cycles. */
  __IO uint32_t wait_loop_index;
  wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_2);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_2, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_2, LL_ADC_SINGLE_ENDED);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_3);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_3, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_3, LL_ADC_SINGLE_ENDED);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_3, LL_ADC_CHANNEL_6);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SINGLE_ENDED);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_4, LL_ADC_CHANNEL_18);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_18, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_18, LL_ADC_SINGLE_ENDED);
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}
/* ADC3 init function */
void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_ADC3);

  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
  /**ADC3 GPIO Configuration
  PF4   ------> ADC3_INP9
  PF10   ------> ADC3_INP6
  PH2   ------> ADC3_INP13
  PH3   ------> ADC3_INP14
  PH4   ------> ADC3_INP15
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4|LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /* ADC3 DMA Init */

  /* ADC3 Init */
  LL_DMA_SetPeriphRequest(DMA2, LL_DMA_STREAM_5, LL_DMAMUX1_REQ_ADC3);

  LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_5, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_5, LL_DMA_PRIORITY_MEDIUM);

  LL_DMA_SetMode(DMA2, LL_DMA_STREAM_5, LL_DMA_MODE_CIRCULAR);

  LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_5, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_5, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_5, LL_DMA_PDATAALIGN_HALFWORD);

  LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_5, LL_DMA_MDATAALIGN_HALFWORD);

  LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_5);

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  LL_ADC_SetOverSamplingScope(ADC3, LL_ADC_OVS_DISABLE);
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B_OPT;
  ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
  LL_ADC_Init(ADC3, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS;
  ADC_REG_InitStruct.SequencerDiscont = DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
  LL_ADC_REG_Init(ADC3, &ADC_REG_InitStruct);
  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_ASYNC_DIV16;
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC3), &ADC_CommonInitStruct);

  /* Disable ADC deep power down (enabled by default after reset state) */
  LL_ADC_DisableDeepPowerDown(ADC3);
  /* Enable ADC internal voltage regulator */
  LL_ADC_EnableInternalRegulator(ADC3);
  /* Delay for ADC internal voltage regulator stabilization. */
  /* Compute number of CPU cycles to wait for, from delay in us. */
  /* Note: Variable divided by 2 to compensate partially */
  /* CPU processing cycles (depends on compilation optimization). */
  /* Note: If system core clock frequency is below 200kHz, wait time */
  /* is only a few CPU processing cycles. */
  __IO uint32_t wait_loop_index;
  wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_6);
  LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC3, LL_ADC_CHANNEL_6, LL_ADC_SINGLE_ENDED);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_9);
  LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_9, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC3, LL_ADC_CHANNEL_9, LL_ADC_SINGLE_ENDED);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_3, LL_ADC_CHANNEL_14);
  LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_14, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC3, LL_ADC_CHANNEL_14, LL_ADC_SINGLE_ENDED);

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_4, LL_ADC_CHANNEL_15);
  LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_15, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC3, LL_ADC_CHANNEL_15, LL_ADC_SINGLE_ENDED);
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
