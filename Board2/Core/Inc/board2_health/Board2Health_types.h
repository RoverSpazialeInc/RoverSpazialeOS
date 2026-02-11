/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2Health_types.h
 *
 * Code generated for Simulink model 'Board2Health'.
 *
 * Model version                  : 8.0
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 14:41:06 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Board2Health_types_h_
#define Board2Health_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_ENUM_Error_
#define DEFINED_TYPEDEF_FOR_ENUM_Error_

typedef enum {
  NO_ERROR = 0,                        /* Default value */
  ERROR_PRESENT
} ENUM_Error;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ENUM_BoardStatus_
#define DEFINED_TYPEDEF_FOR_ENUM_BoardStatus_

typedef enum {
  BOARD_OK = 0,                        /* Default value */
  BOARD_ERROR,
  BOARD_FAULT
} ENUM_BoardStatus;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Board2Health_T RT_MODEL_Board2Health_T;

#endif                                 /* Board2Health_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
