/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CommunicationLinkHealth.c
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

#include "CommunicationLinkHealth.h"
#include "rtwtypes.h"

/* Named constants for Chart: '<Root>/CommunicationLinkHealth' */
#define Communica_MIN_CONSECUTIVE_CLEAN (5.0)
#define Communica_MIN_CONSECUTIVE_DIRTY (10.0)
#define Communicat_MIN_CONSECUTIVE_FAIL (2.0)
#define CommunicationL_IN_Link_degraded ((uint8_T)3U)
#define CommunicationLinkH_IN_Link_Lost ((uint8_T)1U)
#define CommunicationLinkHea_IN_Link_OK ((uint8_T)2U)

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

MdlrefDW_CommunicationLinkHea_T CommunicationLinkHealt_MdlrefDW;

/* Block states (default storage) */
DW_CommunicationLinkHealth_f_T CommunicationLinkHealth_DW;

/* System initialize for referenced model: 'CommunicationLinkHealth' */
void CommunicationLinkHealth_Init(void)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateCommunicationLinkHealth' incorporates:
   *  Chart: '<Root>/CommunicationLinkHealth'
   */
  /* Chart: '<Root>/CommunicationLinkHealth' */
  CommunicationLinkHealth_DW.bitsForTID1.is_LinkHealth =
    CommunicationLinkHea_IN_Link_OK;

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateCommunicationLinkHealth' */
}

/* Output and update for referenced model: 'CommunicationLinkHealth' */
void C_UpdateCommunicationLinkHealth(const ENUM_CycleResult *rtu_cycleResult,
  ENUM_LinkStatus *rty_communicationLinkHealth)
{
  uint64_T qY;
  int32_T tmp;
  boolean_T guard1;
  boolean_T guard2;

  /* RootInportFunctionCallGenerator generated from: '<Root>/UpdateCommunicationLinkHealth' incorporates:
   *  Chart: '<Root>/CommunicationLinkHealth'
   */
  /* Chart: '<Root>/CommunicationLinkHealth' */
  guard1 = false;
  guard2 = false;
  switch (CommunicationLinkHealth_DW.bitsForTID1.is_LinkHealth) {
   case CommunicationLinkH_IN_Link_Lost:
    *rty_communicationLinkHealth = LINK_LOST;
    break;

   case CommunicationLinkHea_IN_Link_OK:
    *rty_communicationLinkHealth = LINK_OK;
    if (*rtu_cycleResult == CYCLE_OK_DIRTY) {
      CommunicationLinkHealth_DW.consecutive_fail = 0U;
      CommunicationLinkHealth_DW.consecutive_dirty = 1U;
      guard2 = true;
    } else if (*rtu_cycleResult == CYCLE_FAIL) {
      CommunicationLinkHealth_DW.consecutive_fail = 1U;
      CommunicationLinkHealth_DW.consecutive_dirty = 0U;
      guard2 = true;
    }
    break;

   default:
    /* case IN_Link_degraded: */
    *rty_communicationLinkHealth = LINK_DEGRADED;
    if (*rtu_cycleResult == CYCLE_OK_CLEAN) {
      qY = CommunicationLinkHealth_DW.ok_clean_streak + /*MW:OvSatOk*/ 1ULL;
      if (CommunicationLinkHealth_DW.ok_clean_streak + 1ULL <
          CommunicationLinkHealth_DW.ok_clean_streak) {
        qY = MAX_uint64_T;
      }

      CommunicationLinkHealth_DW.ok_clean_streak = qY;
      if (CommunicationLinkHealth_DW.ok_clean_streak >=
          Communica_MIN_CONSECUTIVE_CLEAN) {
        CommunicationLinkHealth_DW.bitsForTID1.is_LinkHealth =
          CommunicationLinkHea_IN_Link_OK;
        *rty_communicationLinkHealth = LINK_OK;
      } else {
        guard1 = true;
      }
    } else {
      if (*rtu_cycleResult == CYCLE_FAIL) {
        CommunicationLinkHealth_DW.ok_clean_streak = 0ULL;
        tmp = CommunicationLinkHealth_DW.consecutive_fail + 1;
        if (CommunicationLinkHealth_DW.consecutive_fail + 1 > 255) {
          tmp = 255;
        }

        CommunicationLinkHealth_DW.consecutive_fail = (uint8_T)tmp;
      } else {
        CommunicationLinkHealth_DW.ok_clean_streak = 0ULL;
        tmp = CommunicationLinkHealth_DW.consecutive_dirty + 1;
        if (CommunicationLinkHealth_DW.consecutive_dirty + 1 > 255) {
          tmp = 255;
        }

        CommunicationLinkHealth_DW.consecutive_dirty = (uint8_T)tmp;
      }

      if ((CommunicationLinkHealth_DW.consecutive_dirty >= (int32_T)
           Communica_MIN_CONSECUTIVE_DIRTY) ||
          (CommunicationLinkHealth_DW.consecutive_fail >= (int32_T)
           Communicat_MIN_CONSECUTIVE_FAIL)) {
        CommunicationLinkHealth_DW.bitsForTID1.is_LinkHealth =
          CommunicationLinkH_IN_Link_Lost;
        *rty_communicationLinkHealth = LINK_LOST;
      } else {
        guard1 = true;
      }
    }
    break;
  }

  if (guard2) {
    CommunicationLinkHealth_DW.ok_clean_streak = 0ULL;
    CommunicationLinkHealth_DW.bitsForTID1.is_LinkHealth =
      CommunicationL_IN_Link_degraded;
    *rty_communicationLinkHealth = LINK_DEGRADED;
  }

  if (guard1) {
    CommunicationLinkHealth_DW.bitsForTID1.is_LinkHealth =
      CommunicationL_IN_Link_degraded;
    *rty_communicationLinkHealth = LINK_DEGRADED;
  }

  /* End of Chart: '<Root>/CommunicationLinkHealth' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/UpdateCommunicationLinkHealth' */
}

/* Model initialize function */
void CommunicationLinkHea_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_CommunicationLinkHea_T *const CommunicationLinkHealth_M =
    &(CommunicationLinkHealt_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(CommunicationLinkHealth_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
