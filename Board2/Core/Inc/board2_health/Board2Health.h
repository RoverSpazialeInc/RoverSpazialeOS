/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2Health.h
 *
 * Code generated for Simulink model 'Board2Health'.
 *
 * Model version                  : 8.0
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Feb  9 11:36:04 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Board2Health_h_
#define Board2Health_h_
#ifndef Board2Health_COMMON_INCLUDES_
#define Board2Health_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Board2Health_COMMON_INCLUDES_ */

#include "Board2Health_types.h"

/* user code (top of header file) */
#include "controller_masks.h"
#include "serialize.h"
#include "deserialize.h"
#include "comparator.h"
#include "uart_functions.h"
#include "crc_functions.h"
#include "freeRTOS_functions.h"

extern void Board2Health_Init(void);
extern void Board2Health_UpdateBoardStatus(const ENUM_Error *rtu_errorB2,
  ENUM_BoardStatus *rty_StatusBoard2);

/* Model reference registration function */
extern void Board2Health_initialize(const char_T **rt_errorStatus);

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
 * '<Root>' : 'Board2Health'
 * '<S1>'   : 'Board2Health/BoardsHealth'
 */
#endif                                 /* Board2Health_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
