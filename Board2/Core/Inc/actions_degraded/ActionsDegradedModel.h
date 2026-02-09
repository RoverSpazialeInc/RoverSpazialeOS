/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsDegradedModel.h
 *
 * Code generated for Simulink model 'ActionsDegradedModel'.
 *
 * Model version                  : 9.7
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Feb  9 11:35:59 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ActionsDegradedModel_h_
#define ActionsDegradedModel_h_
#ifndef ActionsDegradedModel_COMMON_INCLUDES_
#define ActionsDegradedModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                               /* ActionsDegradedModel_COMMON_INCLUDES_ */

#include "decision.h"
#include "decision_enums.h"
#include "sensors.h"
#include "ActionsDegradedModel_types.h"

/* user code (top of header file) */
#include "sensors.h"

extern void ActionsDegradedModel_Init(BUS_SetPoint *rty_setPoint);
extern void ActionsDegra_ComputeRoverAction(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_x_lever, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint);

/* Model reference registration function */
extern void ActionsDegradedModel_initialize(const char_T **rt_errorStatus);

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
 * '<Root>' : 'ActionsDegradedModel'
 * '<S1>'   : 'ActionsDegradedModel/DegradedRoverAction'
 */
#endif                                 /* ActionsDegradedModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
