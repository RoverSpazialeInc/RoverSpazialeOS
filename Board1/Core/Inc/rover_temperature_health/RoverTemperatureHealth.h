/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RoverTemperatureHealth.h
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

#ifndef RoverTemperatureHealth_h_
#define RoverTemperatureHealth_h_
#ifndef RoverTemperatureHealth_COMMON_INCLUDES_
#define RoverTemperatureHealth_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                             /* RoverTemperatureHealth_COMMON_INCLUDES_ */

#include "sensors.h"

/* Forward declaration for rtModel */
typedef struct tag_RTM_RoverTemperatureHealt_T RT_MODEL_RoverTemperatureHeal_T;

#ifndef DEFINED_TYPEDEF_FOR_ENUM_TemperatureStatus_
#define DEFINED_TYPEDEF_FOR_ENUM_TemperatureStatus_

typedef enum {
  TEMPERATURE_OK = 0,                  /* Default value */
  TEMPERATURE_NOT_OK
} ENUM_TemperatureStatus;

#endif

/* Block signals and states (default storage) for model 'RoverTemperatureHealth' */
typedef struct {
  struct {
    uint_T is_RoverTemperatureHandler:2;/* '<Root>/RoverTemperatureHealth' */
  } bitsForTID1;

  uint8_T samples;                     /* '<Root>/RoverTemperatureHealth' */
} DW_RoverTemperatureHealth_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_RoverTemperatureHealt_T {
  const char_T **errorStatus;
};

typedef struct {
  RT_MODEL_RoverTemperatureHeal_T rtm;
} MdlrefDW_RoverTemperatureHeal_T;

extern MdlrefDW_RoverTemperatureHeal_T RoverTemperatureHealth_MdlrefDW;

/* Block states (default storage) */
extern DW_RoverTemperatureHealth_f_T RoverTemperatureHealth_DW;
extern void RoverTemperatureHealth_Init(void);
extern void Ro_UpdateRoverTemperatureHealth(const Temperature *rtu_temperature,
  ENUM_TemperatureStatus *rty_roverTemperatureHealth);

/* Model reference registration function */
extern void RoverTemperatureHeal_initialize(const char_T **rt_errorStatus);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'RoverTemperatureHealth'
 * '<S1>'   : 'RoverTemperatureHealth/RoverTemperatureHealth'
 */
#endif                                 /* RoverTemperatureHealth_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
