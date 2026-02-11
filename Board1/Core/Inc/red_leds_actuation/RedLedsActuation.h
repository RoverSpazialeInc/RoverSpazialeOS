/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RedLedsActuation.h
 *
 * Code generated for Simulink model 'RedLedsActuation'.
 *
 * Model version                  : 18.1
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 12:43:10 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#ifndef RedLedsActuation_h_
#define RedLedsActuation_h_
#ifndef RedLedsActuation_COMMON_INCLUDES_
#define RedLedsActuation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* RedLedsActuation_COMMON_INCLUDES_ */

#include "decision_enums.h"

/* Forward declaration for rtModel */
typedef struct tag_RTM_RedLedsActuation_T RT_MODEL_RedLedsActuation_T;

/* user code (top of header file) */
#include "decision.h"
#include "redLeds_functions.h"

/* Block signals and states (default storage) for model 'RedLedsActuation' */
typedef struct {
  struct {
    uint_T is_Left:2;                  /* '<Root>/RedLeds' */
    uint_T is_Right:2;                 /* '<Root>/RedLeds' */
  } bitsForTID1;
} DW_RedLedsActuation_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_RedLedsActuation_T {
  const char_T **errorStatus;
};

typedef struct {
  RT_MODEL_RedLedsActuation_T rtm;
} MdlrefDW_RedLedsActuation_T;

extern MdlrefDW_RedLedsActuation_T RedLedsActuation_MdlrefDW;

/* Block states (default storage) */
extern DW_RedLedsActuation_f_T RedLedsActuation_DW;
extern void RedLedsActuation_Init(void);
extern void RedLedsActuation_ActuateRedLeds(const ENUM_StatusRedLed
  *rtu_leftRedLed, const ENUM_StatusRedLed *rtu_rightRedLed);

/* Model reference registration function */
extern void RedLedsActuation_initialize(const char_T **rt_errorStatus);

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
 * '<Root>' : 'RedLedsActuation'
 * '<S1>'   : 'RedLedsActuation/RedLeds'
 */
#endif                                 /* RedLedsActuation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
