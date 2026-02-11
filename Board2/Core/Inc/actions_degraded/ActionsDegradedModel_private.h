/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsDegradedModel_private.h
 *
 * Code generated for Simulink model 'ActionsDegradedModel'.
 *
 * Model version                  : 9.7
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 14:41:02 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ActionsDegradedModel_private_h_
#define ActionsDegradedModel_private_h_
#include "rtwtypes.h"
#include "sensors.h"
#include "ActionsDegradedModel_types.h"

/* Block states (default storage) for model 'ActionsDegradedModel' */
typedef struct {
  real_T callCount;                    /* '<Root>/DegradedRoverAction' */
  int32_T accumulated_change;          /* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_Backward;   /* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_BW_Forward; /* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_BW_FW_SafeActio;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_BW_RR_RotateRig;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_BW_RR_SafeActio;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_BW_RotateLeft;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_BW_RL_SafeActio;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_Forward;    /* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_FW_SafeAction;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_RotateLeft; /* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_RL_SafeAction;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_RotateRight;/* '<Root>/DegradedRoverAction' */
  uint32_T exit_port_index_RR_SafeAction;/* '<Root>/DegradedRoverAction' */
  Gyroscope previousGyroscope;         /* '<Root>/DegradedRoverAction' */
  uint8_T is_CurrentRoverAction;       /* '<Root>/DegradedRoverAction' */
  uint8_T is_Backward;                 /* '<Root>/DegradedRoverAction' */
  uint8_T is_BW_Forward;               /* '<Root>/DegradedRoverAction' */
  uint8_T is_BW_RR_RotateRight;        /* '<Root>/DegradedRoverAction' */
  uint8_T is_BW_RotateLeft;            /* '<Root>/DegradedRoverAction' */
  uint8_T is_Forward;                  /* '<Root>/DegradedRoverAction' */
  uint8_T is_RotateLeft;               /* '<Root>/DegradedRoverAction' */
  uint8_T is_RL_RotateLeft;            /* '<Root>/DegradedRoverAction' */
  uint8_T is_RotateRight;              /* '<Root>/DegradedRoverAction' */
  uint8_T is_RR_RotateRight;           /* '<Root>/DegradedRoverAction' */
} DW_ActionsDegradedModel_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_ActionsDegradedModel_T {
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
  RT_MODEL_ActionsDegradedModel_T rtm;
} MdlrefDW_ActionsDegradedModel_T;

extern MdlrefDW_ActionsDegradedModel_T ActionsDegradedModel_MdlrefDW;

/* Block states (default storage) */
extern DW_ActionsDegradedModel_f_T ActionsDegradedModel_DW;

#endif                                 /* ActionsDegradedModel_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
