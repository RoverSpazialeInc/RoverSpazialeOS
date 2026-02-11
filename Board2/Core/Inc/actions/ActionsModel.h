/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsModel.h
 *
 * Code generated for Simulink model 'ActionsModel'.
 *
 * Model version                  : 8.19
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 14:38:40 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ActionsModel_h_
#define ActionsModel_h_
#ifndef ActionsModel_COMMON_INCLUDES_
#define ActionsModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* ActionsModel_COMMON_INCLUDES_ */

#include "decision.h"
#include "decision_enums.h"
#include "sensors.h"
#include "ActionsModel_types.h"

/* user code (top of header file) */
#include "sensors.h"

extern void ActionsModel_Init(BUS_SetPoint *rty_setPoint, ENUM_RoverAction
  *rty_roverAction, BUS_RedLeds *rty_redLeds);
extern void ActionsModel_ComputeRoverAction(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_x_lever,
  const int16_T *rtu_y_lever, const Gyroscope *rtu_gyroscope, const BUS_Sonar
  *rtu_sonar, BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction,
  ENUM_SafeAction *rty_safeAction, BUS_RedLeds *rty_redLeds, ENUM_PidMode
  *rty_selectedPidMode);

/* Model reference registration function */
extern void ActionsModel_initialize(const char_T **rt_errorStatus);

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
 * '<Root>' : 'ActionsModel'
 * '<S1>'   : 'ActionsModel/MovingObstacles'
 * '<S2>'   : 'ActionsModel/RoverAction'
 * '<S3>'   : 'ActionsModel/Subsystem'
 * '<S4>'   : 'ActionsModel/Subsystem/MATLAB Function'
 */
#endif                                 /* ActionsModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
