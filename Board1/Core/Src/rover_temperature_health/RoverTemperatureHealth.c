/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RoverTemperatureHealth.c
 *
 * Code generated for Simulink model 'RoverTemperatureHealth'.
 *
 * Model version                  : 20.6
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 19:37:45 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "RoverTemperatureHealth.h"
#include "sensors.h"
#include "rtwtypes.h"

/* Named constants for Chart: '<Root>/RoverTemperatureHealth' */
#define Rove_IN_RoverTemperature_NOT_OK ((uint8_T)2U)
#define RoverTem_IN_RoverTemperature_OK ((uint8_T)3U)
#define RoverTemperat_IN_KeepMonitoring ((uint8_T)1U)
#define RoverTemperatureHea_MAX_SAMPLES ((uint8_T)100U)

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

MdlrefDW_RoverTemperatureHeal_T RoverTemperatureHealth_MdlrefDW;

/* Block states (default storage) */
DW_RoverTemperatureHealth_f_T RoverTemperatureHealth_DW;

/* System initialize for referenced model: 'RoverTemperatureHealth' */
void RoverTemperatureHealth_Init(void)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateRoverTemperatureHealth' incorporates:
   *  Chart: '<Root>/RoverTemperatureHealth'
   */
  /* Chart: '<Root>/RoverTemperatureHealth' */
  RoverTemperatureHealth_DW.bitsForTID1.is_RoverTemperatureHandler =
    RoverTem_IN_RoverTemperature_OK;

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateRoverTemperatureHealth' */
}

/* Output and update for referenced model: 'RoverTemperatureHealth' */
void Ro_UpdateRoverTemperatureHealth(const Temperature *rtu_temperature,
  ENUM_TemperatureStatus *rty_roverTemperatureHealth)
{
  /* RootInportFunctionCallGenerator generated from: '<Root>/UpdateRoverTemperatureHealth' incorporates:
   *  Chart: '<Root>/RoverTemperatureHealth'
   */
  /* Chart: '<Root>/RoverTemperatureHealth' */
  switch (RoverTemperatureHealth_DW.bitsForTID1.is_RoverTemperatureHandler) {
   case RoverTemperat_IN_KeepMonitoring:
    if (RoverTemperatureHealth_DW.samples >= RoverTemperatureHea_MAX_SAMPLES) {
      RoverTemperatureHealth_DW.bitsForTID1.is_RoverTemperatureHandler =
        Rove_IN_RoverTemperature_NOT_OK;
      *rty_roverTemperatureHealth = TEMPERATURE_NOT_OK;
    } else if (*rtu_temperature < 60.0F) {
      RoverTemperatureHealth_DW.bitsForTID1.is_RoverTemperatureHandler =
        RoverTem_IN_RoverTemperature_OK;
      *rty_roverTemperatureHealth = TEMPERATURE_OK;
    } else {
      RoverTemperatureHealth_DW.samples++;
    }
    break;

   case Rove_IN_RoverTemperature_NOT_OK:
    *rty_roverTemperatureHealth = TEMPERATURE_NOT_OK;
    break;

   default:
    /* case IN_RoverTemperature_OK: */
    if (*rtu_temperature >= 60.0F) {
      RoverTemperatureHealth_DW.bitsForTID1.is_RoverTemperatureHandler =
        RoverTemperat_IN_KeepMonitoring;
      *rty_roverTemperatureHealth = TEMPERATURE_OK;
      RoverTemperatureHealth_DW.samples = 1U;
    }
    break;
  }

  /* End of Chart: '<Root>/RoverTemperatureHealth' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/UpdateRoverTemperatureHealth' */
}

/* Model initialize function */
void RoverTemperatureHeal_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_RoverTemperatureHeal_T *const RoverTemperatureHealth_M =
    &(RoverTemperatureHealth_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(RoverTemperatureHealth_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
