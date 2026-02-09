/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2Health.c
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

#include "Board2Health.h"
#include "Board2Health_types.h"
#include "rtwtypes.h"
#include "Board2Health_private.h"

/* Named constants for Chart: '<Root>/BoardsHealth' */
#define Board2Health_IN_Error          ((uint8_T)1U)
#define Board2Health_IN_Fault          ((uint8_T)2U)
#define Board2Health_IN_OK             ((uint8_T)3U)

MdlrefDW_Board2Health_T Board2Health_MdlrefDW;

/* Block states (default storage) */
DW_Board2Health_f_T Board2Health_DW;

/* System initialize for referenced model: 'Board2Health' */
void Board2Health_Init(void)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardStatus' incorporates:
   *  Chart: '<Root>/BoardsHealth'
   */
  /* Chart: '<Root>/BoardsHealth' */
  Board2Health_DW.is_B2 = Board2Health_IN_OK;

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardStatus' */
}

/* Output and update for referenced model: 'Board2Health' */
void Board2Health_UpdateBoardStatus(const ENUM_Error *rtu_errorB2,
  ENUM_BoardStatus *rty_StatusBoard2)
{
  boolean_T guard1;

  /* RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardStatus' incorporates:
   *  Chart: '<Root>/BoardsHealth'
   */
  /* Chart: '<Root>/BoardsHealth' */
  guard1 = false;
  switch (Board2Health_DW.is_B2) {
   case Board2Health_IN_Error:
    *rty_StatusBoard2 = BOARD_ERROR;
    if (Board2Health_DW.countUpdateB2 == 5) {
      Board2Health_DW.countUpdateB2 = 0U;
      if (Board2Health_DW.countErrorB2 >= 2) {
        guard1 = true;
      } else {
        Board2Health_DW.countErrorB2 = 0U;
        Board2Health_DW.is_B2 = Board2Health_IN_Error;
        *rty_StatusBoard2 = BOARD_ERROR;
      }
    } else if (*rtu_errorB2 == ERROR_PRESENT) {
      Board2Health_DW.countErrorB2++;
      guard1 = true;
    } else {
      Board2Health_DW.is_B2 = Board2Health_IN_OK;
      *rty_StatusBoard2 = BOARD_OK;
    }
    break;

   case Board2Health_IN_Fault:
    *rty_StatusBoard2 = BOARD_FAULT;
    break;

   default:
    /* case IN_OK: */
    *rty_StatusBoard2 = BOARD_OK;
    if (*rtu_errorB2 == ERROR_PRESENT) {
      Board2Health_DW.countErrorB2++;
      Board2Health_DW.is_B2 = Board2Health_IN_Error;
      *rty_StatusBoard2 = BOARD_ERROR;
    } else if (Board2Health_DW.countUpdateB2 == 5) {
      Board2Health_DW.countUpdateB2 = 0U;
      if (Board2Health_DW.countErrorB2 >= 2) {
        Board2Health_DW.is_B2 = Board2Health_IN_Fault;
        *rty_StatusBoard2 = BOARD_FAULT;
      } else {
        Board2Health_DW.countErrorB2 = 0U;
        Board2Health_DW.is_B2 = Board2Health_IN_OK;
        *rty_StatusBoard2 = BOARD_OK;
      }
    }
    break;
  }

  if (guard1) {
    Board2Health_DW.is_B2 = Board2Health_IN_Fault;
    *rty_StatusBoard2 = BOARD_FAULT;
  }

  /* End of Chart: '<Root>/BoardsHealth' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardStatus' */
}

/* Model initialize function */
void Board2Health_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_Board2Health_T *const Board2Health_M = &(Board2Health_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(Board2Health_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
