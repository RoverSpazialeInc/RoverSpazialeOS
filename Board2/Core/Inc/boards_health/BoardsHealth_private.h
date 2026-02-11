/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BoardsHealth_private.h
 *
 * Code generated for Simulink model 'BoardsHealth'.
 *
 * Model version                  : 8.1
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 14:38:48 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef BoardsHealth_private_h_
#define BoardsHealth_private_h_
#include "rtwtypes.h"
#include "BoardsHealth_types.h"

/* Block states (default storage) for model 'BoardsHealth' */
typedef struct {
  uint8_T countUpdateB1;               /* '<Root>/BoardsHealth' */
  uint8_T countErrorB1;                /* '<Root>/BoardsHealth' */
  uint8_T countErrorB2;                /* '<Root>/BoardsHealth' */
  uint8_T countUpdateB2;               /* '<Root>/BoardsHealth' */
  uint8_T is_B1;                       /* '<Root>/BoardsHealth' */
  uint8_T is_B2;                       /* '<Root>/BoardsHealth' */
} DW_BoardsHealth_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_BoardsHealth_T {
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
  RT_MODEL_BoardsHealth_T rtm;
} MdlrefDW_BoardsHealth_T;

extern MdlrefDW_BoardsHealth_T BoardsHealth_MdlrefDW;

/* Block states (default storage) */
extern DW_BoardsHealth_f_T BoardsHealth_DW;

#endif                                 /* BoardsHealth_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
