/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: RedLedsActuation.c
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

#include "RedLedsActuation.h"
#include "decision_enums.h"
#include "rtwtypes.h"

/* Named constants for Chart: '<Root>/RedLeds' */
#define RedLedsActua_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define RedLedsActuation_IN_BLINKING   ((uint8_T)1U)
#define RedLedsActuation_IN_OFF        ((uint8_T)2U)
#define RedLedsActuation_IN_ON         ((uint8_T)3U)

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

MdlrefDW_RedLedsActuation_T RedLedsActuation_MdlrefDW;

/* Block states (default storage) */
DW_RedLedsActuation_f_T RedLedsActuation_DW;

/* System initialize for referenced model: 'RedLedsActuation' */
void RedLedsActuation_Init(void)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ActuateRedLeds' incorporates:
   *  Chart: '<Root>/RedLeds'
   */
  /* SystemInitialize for Chart: '<Root>/RedLeds' */
  RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActua_IN_NO_ACTIVE_CHILD;

  /* Chart: '<Root>/RedLeds' */
  RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_OFF;
  leftRedLedOff();
  RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_OFF;
  rightRedLedOff();

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ActuateRedLeds' */
}

/* Output and update for referenced model: 'RedLedsActuation' */
void RedLedsActuation_ActuateRedLeds(const ENUM_StatusRedLed *rtu_leftRedLed,
  const ENUM_StatusRedLed *rtu_rightRedLed)
{
  /* RootInportFunctionCallGenerator generated from: '<Root>/ActuateRedLeds' incorporates:
   *  Chart: '<Root>/RedLeds'
   */
  /* Chart: '<Root>/RedLeds' */
  switch (RedLedsActuation_DW.bitsForTID1.is_Left) {
   case RedLedsActuation_IN_BLINKING:
    if (*rtu_leftRedLed != RED_BLINKING) {
      switch (*rtu_leftRedLed) {
       case RED_BLINKING:
        stopPeriodicLeftRedLed();
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_BLINKING;
        leftRedLedOn();
        startPeriodicLeftRedLed();
        break;

       case RED_ON:
        stopPeriodicLeftRedLed();
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_ON;
        leftRedLedOn();
        break;

       default:
        stopPeriodicLeftRedLed();
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_OFF;
        leftRedLedOff();
        break;
      }
    }
    break;

   case RedLedsActuation_IN_OFF:
    if (*rtu_leftRedLed != RED_OFF) {
      if (*rtu_leftRedLed == RED_BLINKING) {
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_BLINKING;
        leftRedLedOn();
        startPeriodicLeftRedLed();
      } else {
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_ON;
        leftRedLedOn();
      }
    }
    break;

   default:
    /* case IN_ON: */
    if (*rtu_leftRedLed != RED_ON) {
      if (*rtu_leftRedLed == RED_BLINKING) {
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_BLINKING;
        leftRedLedOn();
        startPeriodicLeftRedLed();
      } else {
        RedLedsActuation_DW.bitsForTID1.is_Left = RedLedsActuation_IN_OFF;
        leftRedLedOff();
      }
    }
    break;
  }

  switch (RedLedsActuation_DW.bitsForTID1.is_Right) {
   case RedLedsActuation_IN_BLINKING:
    if (*rtu_rightRedLed != RED_BLINKING) {
      switch (*rtu_rightRedLed) {
       case RED_BLINKING:
        stopPeriodicRightRedLed();
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_BLINKING;
        rightRedLedOn();
        startPeriodicRightRedLed();
        break;

       case RED_ON:
        stopPeriodicRightRedLed();
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_ON;
        rightRedLedOn();
        break;

       default:
        stopPeriodicRightRedLed();
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_OFF;
        rightRedLedOff();
        break;
      }
    }
    break;

   case RedLedsActuation_IN_OFF:
    if (*rtu_rightRedLed != RED_OFF) {
      if (*rtu_rightRedLed == RED_BLINKING) {
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_BLINKING;
        rightRedLedOn();
        startPeriodicRightRedLed();
      } else {
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_ON;
        rightRedLedOn();
      }
    }
    break;

   default:
    /* case IN_ON: */
    if (*rtu_rightRedLed != RED_ON) {
      if (*rtu_rightRedLed == RED_BLINKING) {
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_BLINKING;
        rightRedLedOn();
        startPeriodicRightRedLed();
      } else {
        RedLedsActuation_DW.bitsForTID1.is_Right = RedLedsActuation_IN_OFF;
        rightRedLedOff();
      }
    }
    break;
  }

  /* End of Chart: '<Root>/RedLeds' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ActuateRedLeds' */
}

/* Model initialize function */
void RedLedsActuation_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_RedLedsActuation_T *const RedLedsActuation_M =
    &(RedLedsActuation_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(RedLedsActuation_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
