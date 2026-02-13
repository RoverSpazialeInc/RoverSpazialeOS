/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2_private.h
 *
 * Code generated for Simulink model 'Board2'.
 *
 * Model version                  : 13.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Feb 13 16:30:02 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Board2_private_h_
#define Board2_private_h_
#include "rtwtypes.h"
#include "Board2.h"
#include "Board2_types.h"

/* Includes for objects with custom storage classes */
#include "controller_masks.h"
#include "crc_functions.h"
#include "frame_size.h"

/*
 * Check that imported macros with storage class "ImportedDefine" are defined
 */
#ifndef BRAKING_HARD_MASK
#error The value of parameter "BRAKING_HARD_MASK" is not defined
#endif

#ifndef BRAKING_SMOOTH_MASK
#error The value of parameter "BRAKING_SMOOTH_MASK" is not defined
#endif

#ifndef WHITE_LEFT_LED_MASK
#error The value of parameter "WHITE_LEFT_LED_MASK" is not defined
#endif

#ifndef WHITE_RIGHT_LED_MASK
#error The value of parameter "WHITE_RIGHT_LED_MASK" is not defined
#endif

#ifndef CRC_SIZE
#error The value of parameter "CRC_SIZE" is not defined
#endif

#ifndef DECISION_FRAME_SIZE
#error The value of parameter "DECISION_FRAME_SIZE" is not defined
#endif

#ifndef GLOBAL_STATE_FRAME_SIZE
#error The value of parameter "GLOBAL_STATE_FRAME_SIZE" is not defined
#endif

#ifndef LOCAL_STATE_B1_FRAME_SIZE
#error The value of parameter "LOCAL_STATE_B1_FRAME_SIZE" is not defined
#endif

#ifndef LOCAL_STATE_B2_FRAME_SIZE
#error The value of parameter "LOCAL_STATE_B2_FRAME_SIZE" is not defined
#endif
#endif                                 /* Board2_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
