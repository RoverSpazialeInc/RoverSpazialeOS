/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2Degraded.h
 *
 * Code generated for Simulink model 'Board2Degraded'.
 *
 * Model version                  : 10.2
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 20:26:41 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Board2Degraded_h_
#define Board2Degraded_h_
#ifndef Board2Degraded_COMMON_INCLUDES_
#define Board2Degraded_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Board2Degraded_COMMON_INCLUDES_ */

#include "Board2Degraded_types.h"
#include "sensors.h"
#include "states.h"
#include "decision.h"
#include "decision_enums.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

/* user code (top of header file) */
#include "controller_masks.h"
#include "serialize.h"
#include "deserialize.h"
#include "comparator.h"
#include "uart_functions.h"
#include "crc_functions.h"
#include "freeRTOS_functions.h"

/* Block signals (default storage) */
typedef struct {
  BUS_LocalStateB2 board2LocalState;   /* '<Root>/SupervisorB2' */
  BUS_SetPoint setPoint;               /* '<Root>/ActionsModel' */
  ENUM_UserAction computedUserAction;  /* '<Root>/SupervisorB2' */
  ENUM_Error errorB2;                  /* '<Root>/SupervisorB2' */
  ENUM_BoardStatus StatusBoard2;       /* '<Root>/Board2Health' */
} B_Board2Degraded_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint32_T exit_port_index_SupervisorActiv;/* '<Root>/SupervisorB2' */
  uint8_T is_active_c3_Board2Degraded; /* '<Root>/SupervisorB2' */
  uint8_T is_c3_Board2Degraded;        /* '<Root>/SupervisorB2' */
  uint8_T is_SupervisorActive;         /* '<Root>/SupervisorB2' */
} DW_Board2Degraded_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  BUS_Sonar sonar;                     /* '<Root>/sonar' */
  Gyroscope gyroscope;                 /* '<Root>/gyroscope' */
  BUS_RemoteController remoteController;/* '<Root>/remoteController' */
  uint8_T areSensorsValid;             /* '<Root>/areSensorsValid' */
  uint8_T deadlineOccurred;            /* '<Root>/deadlineOccurred' */
} ExtU_Board2Degraded_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T supervision_ended;           /* '<Root>/supervision_ended' */
} ExtY_Board2Degraded_T;

/* Real-time Model Data Structure */
struct tag_RTM_Board2Degraded_T {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_Board2Degraded_T Board2Degraded_B;

/* Block states (default storage) */
extern DW_Board2Degraded_T Board2Degraded_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Board2Degraded_T Board2Degraded_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Board2Degraded_T Board2Degraded_Y;

/* Model entry point functions */
extern void Board2Degraded_initialize(void);
extern void Board2Degraded_step(void);
extern void Board2Degraded_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Board2Degraded_T *const Board2Degraded_M;

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
 * '<Root>' : 'Board2Degraded'
 * '<S1>'   : 'Board2Degraded/SupervisorB2'
 */
#endif                                 /* Board2Degraded_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
