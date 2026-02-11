/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsModel_types.h
 *
 * Code generated for Simulink model 'ActionsModel'.
 *
 * Model version                  : 8.19
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 12:42:42 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ActionsModel_types_h_
#define ActionsModel_types_h_
#include "decision_enums.h"
#include "sensors.h"
#include "rtwtypes.h"
#include "decision.h"
#ifndef DEFINED_TYPEDEF_FOR_ENUM_TrackingObstacles_
#define DEFINED_TYPEDEF_FOR_ENUM_TrackingObstacles_

typedef enum {
  NOT_TRACKING = 0,                    /* Default value */
  NO_OBSTACLE_MOVING,
  OBSTACLE_MOVING
} ENUM_TrackingObstacles;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ENUM_PidMode_
#define DEFINED_TYPEDEF_FOR_ENUM_PidMode_

typedef enum {
  FAST = 0,                            /* Default value */
  MEDIUM,
  SLOW
} ENUM_PidMode;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_ActionsModel_T RT_MODEL_ActionsModel_T;

#endif                                 /* ActionsModel_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
