/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CommunicationLinkHealth.h
 *
 * Code generated for Simulink model 'CommunicationLinkHealth'.
 *
 * Model version                  : 20.13
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Feb  9 11:34:32 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#ifndef CommunicationLinkHealth_h_
#define CommunicationLinkHealth_h_
#ifndef CommunicationLinkHealth_COMMON_INCLUDES_
#define CommunicationLinkHealth_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                            /* CommunicationLinkHealth_COMMON_INCLUDES_ */

/* Forward declaration for rtModel */
typedef struct tag_RTM_CommunicationLinkHeal_T RT_MODEL_CommunicationLinkHea_T;

#ifndef DEFINED_TYPEDEF_FOR_ENUM_CycleResult_
#define DEFINED_TYPEDEF_FOR_ENUM_CycleResult_

typedef enum {
  CYCLE_OK_CLEAN = 0,                  /* Default value */
  CYCLE_OK_DIRTY,
  CYCLE_FAIL
} ENUM_CycleResult;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ENUM_LinkStatus_
#define DEFINED_TYPEDEF_FOR_ENUM_LinkStatus_

typedef enum {
  LINK_OK = 0,                         /* Default value */
  LINK_DEGRADED,
  LINK_LOST
} ENUM_LinkStatus;

#endif

/* Block signals and states (default storage) for model 'CommunicationLinkHealth' */
typedef struct {
  uint64_T ok_clean_streak;            /* '<Root>/CommunicationLinkHealth' */
  struct {
    uint_T is_LinkHealth:2;            /* '<Root>/CommunicationLinkHealth' */
  } bitsForTID1;

  uint8_T consecutive_fail;            /* '<Root>/CommunicationLinkHealth' */
  uint8_T consecutive_dirty;           /* '<Root>/CommunicationLinkHealth' */
} DW_CommunicationLinkHealth_f_T;

/* Real-time Model Data Structure */
struct tag_RTM_CommunicationLinkHeal_T {
  const char_T **errorStatus;
};

typedef struct {
  RT_MODEL_CommunicationLinkHea_T rtm;
} MdlrefDW_CommunicationLinkHea_T;

extern MdlrefDW_CommunicationLinkHea_T CommunicationLinkHealt_MdlrefDW;

/* Block states (default storage) */
extern DW_CommunicationLinkHealth_f_T CommunicationLinkHealth_DW;
extern void CommunicationLinkHealth_Init(void);
extern void C_UpdateCommunicationLinkHealth(const ENUM_CycleResult
  *rtu_cycleResult, ENUM_LinkStatus *rty_communicationLinkHealth);

/* Model reference registration function */
extern void CommunicationLinkHea_initialize(const char_T **rt_errorStatus);

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
 * '<Root>' : 'CommunicationLinkHealth'
 * '<S1>'   : 'CommunicationLinkHealth/CommunicationLinkHealth'
 */
#endif                                 /* CommunicationLinkHealth_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
