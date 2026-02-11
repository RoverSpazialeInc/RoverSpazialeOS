/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsModel_private.h
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

#ifndef ActionsModel_private_h_
#define ActionsModel_private_h_
#include "rtwtypes.h"
#include "ActionsModel_types.h"
#include "decision_enums.h"
#include "sensors.h"

/* Block states (default storage) for system '<Root>/MovingObstacles' */
typedef struct {
  uint8_T is_c2_ActionsModel;          /* '<Root>/MovingObstacles' */
  uint8_T is_LeftSide;                 /* '<Root>/MovingObstacles' */
  uint8_T is_RightSide;                /* '<Root>/MovingObstacles' */
} DW_MovingObstacles_ActionsMod_T;

/* Block signals for model 'ActionsModel' */
typedef struct {
  ENUM_TrackingObstacles statusLeftObstacle;/* '<Root>/MovingObstacles' */
  ENUM_TrackingObstacles statusRightObstacle;/* '<Root>/MovingObstacles' */
  ENUM_StatusRedLed leftLed;           /* '<Root>/MovingObstacles' */
  ENUM_StatusRedLed rightLed;          /* '<Root>/MovingObstacles' */
  uint8_T set;                         /* '<Root>/RoverAction' */
} B_ActionsModel_c_T;

/* Block states (default storage) for model 'ActionsModel' */
typedef struct {
  int32_T accumulated_change;          /* '<Root>/RoverAction' */
  uint32_T exit_port_index_Backward;   /* '<Root>/RoverAction' */
  uint32_T exit_port_index_BW_Forward; /* '<Root>/RoverAction' */
  uint32_T exit_port_index_BW_FW_SafeActio;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_BW_RR_RotateRig;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_BW_RR_SafeActio;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_BW_RotateLeft;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_BW_RL_SafeActio;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_Forward;    /* '<Root>/RoverAction' */
  uint32_T exit_port_index_FW_SafeAction;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_RotateLeft; /* '<Root>/RoverAction' */
  uint32_T exit_port_index_RL_SafeAction;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_RotateRight;/* '<Root>/RoverAction' */
  uint32_T exit_port_index_RR_SafeAction;/* '<Root>/RoverAction' */
  Gyroscope previousGyroscope;         /* '<Root>/RoverAction' */
  uint8_T is_CurrentRoverAction;       /* '<Root>/RoverAction' */
  uint8_T is_Backward;                 /* '<Root>/RoverAction' */
  uint8_T is_BW_Forward;               /* '<Root>/RoverAction' */
  uint8_T is_BW_FW_SafeAction;         /* '<Root>/RoverAction' */
  uint8_T is_BW_RR_RotateRight;        /* '<Root>/RoverAction' */
  uint8_T is_BW_RotateLeft;            /* '<Root>/RoverAction' */
  uint8_T is_Forward;                  /* '<Root>/RoverAction' */
  uint8_T is_FW_SafeAction;            /* '<Root>/RoverAction' */
  uint8_T is_RotateLeft;               /* '<Root>/RoverAction' */
  uint8_T is_RL_RotateLeft;            /* '<Root>/RoverAction' */
  uint8_T is_RotateRight;              /* '<Root>/RoverAction' */
  uint8_T is_RR_RotateRight;           /* '<Root>/RoverAction' */
  DW_MovingObstacles_ActionsMod_T sf_MovingObstacles;/* '<Root>/MovingObstacles' */
} DW_ActionsModel_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_ActionsModel_T {
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
  RT_MODEL_ActionsModel_T rtm;
} MdlrefDW_ActionsModel_T;

extern void ActionsMod_MovingObstacles_Init(ENUM_TrackingObstacles
  *rty_statusLeftObstacle, ENUM_TrackingObstacles *rty_statusRightObstacle,
  ENUM_StatusRedLed *rty_leftLed, ENUM_StatusRedLed *rty_rightLed,
  DW_MovingObstacles_ActionsMod_T *localDW);
extern void ActionsModel_MovingObstacles(uint8_T rtu_set, const BUS_Sonar
  *rtu_sonar, ENUM_TrackingObstacles *rty_statusLeftObstacle,
  ENUM_TrackingObstacles *rty_statusRightObstacle, ENUM_StatusRedLed
  *rty_leftLed, ENUM_StatusRedLed *rty_rightLed, DW_MovingObstacles_ActionsMod_T
  *localDW);
extern MdlrefDW_ActionsModel_T ActionsModel_MdlrefDW;

/* Block signals (default storage) */
extern B_ActionsModel_c_T ActionsModel_B;

/* Block states (default storage) */
extern DW_ActionsModel_f_T ActionsModel_DW;

#endif                                 /* ActionsModel_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
