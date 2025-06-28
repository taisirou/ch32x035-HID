/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32x035_pwr.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/04/06
 * Description        : This file provides all the PWR firmware functions.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32x035_pwrz.h"
#include "ch32x035_rcc.h"

/* PWR registers bit mask */
/* CTLR register bit mask */
#define CTLR_DS_MASK     ((uint32_t)0xFFFFFFFD)
#define CTLR_PLS_MASK    ((uint32_t)0xFFFFFF9F)

/*********************************************************************
 * @fn      PWR_VDD_SupplyVoltage
 *
 * @brief   Checks VDD Supply Voltage.
 *
 * @param   none
 *
 * @return  PWR_VDD - VDD Supply Voltage.
 *            PWR_VDD_5V - VDD = 5V
 *            PWR_VDD_3V3 - VDD = 3.3V
 */
PWR_VDD PWR_VDD_SupplyVoltage(void)
{

    PWR_VDD VDD_Voltage = PWR_VDD_3V3;
    Delay_Init();
	/*
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR, ENABLE);
    Delay_Us(50);
    PWR_PVDLevelConfig(PWR_PVDLevel_4V0);
    Delay_Us(50);
    if( PWR_GetFlagStatus(PWR_FLAG_PVDO) == (uint32_t)RESET)
    {
        VDD_Voltage = PWR_VDD_5V;
    }
	Delay_Us(50);
    PWR_PVDLevelConfig(PWR_PVDLevel_2V1);
	Delay_Us(50);
	*/
    return VDD_Voltage;
}