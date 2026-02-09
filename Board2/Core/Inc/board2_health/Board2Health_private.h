/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2Health_private.h
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

#ifndef Board2Health_private_h_
#define Board2Health_private_h_
#include "rtwtypes.h"
#include "Board2Health_types.h"

/* Block states (default storage) for model 'Board2Health' */
typedef struct {
  uint8_T countErrorB2;                /* '<Root>/BoardsHealth' */
  uint8_T countUpdateB2;               /* '<Root>/BoardsHealth' */
  uint8_T is_B2;                       /* '<Root>/BoardsHealth' */
} DW_Board2Health_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_Board2Health_T {
  const char_T **errorStatus;
};

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

typedef struct {
  RT_MODEL_Board2Health_T rtm;
} MdlrefDW_Board2Health_T;

extern MdlrefDW_Board2Health_T Board2Health_MdlrefDW;

/* Block states (default storage) */
extern DW_Board2Health_f_T Board2Health_DW;

#endif                                 /* Board2Health_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
