/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BoardsHealth.c
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

#include "BoardsHealth.h"
#include "BoardsHealth_types.h"
#include "rtwtypes.h"
#include "BoardsHealth_private.h"

/* Named constants for Chart: '<Root>/BoardsHealth' */
#define BoardsHealth_IN_Error          ((uint8_T)1U)
#define BoardsHealth_IN_Fault          ((uint8_T)2U)
#define BoardsHealth_IN_OK             ((uint8_T)3U)

MdlrefDW_BoardsHealth_T BoardsHealth_MdlrefDW;

/* Block states (default storage) */
DW_BoardsHealth_f_T BoardsHealth_DW;

/* System initialize for referenced model: 'BoardsHealth' */
void BoardsHealth_Init(void)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardsStatus' incorporates:
   *  Chart: '<Root>/BoardsHealth'
   */
  /* Chart: '<Root>/BoardsHealth' */
  BoardsHealth_DW.is_B1 = BoardsHealth_IN_OK;
  BoardsHealth_DW.is_B2 = BoardsHealth_IN_OK;

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardsStatus' */
}

/* Output and update for referenced model: 'BoardsHealth' */
void BoardsHealth_UpdateBoardsStatus(const ENUM_Error *rtu_errorB1, const
  ENUM_Error *rtu_errorB2, ENUM_BoardStatus *rty_StatusBoard1, ENUM_BoardStatus *
  rty_StatusBoard2)
{
  boolean_T guard1;

  /* RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardsStatus' incorporates:
   *  Chart: '<Root>/BoardsHealth'
   */
  /* Chart: '<Root>/BoardsHealth' */
  BoardsHealth_DW.countUpdateB1++;
  BoardsHealth_DW.countUpdateB2++;
  guard1 = false;
  switch (BoardsHealth_DW.is_B1) {
   case BoardsHealth_IN_Error:
    *rty_StatusBoard1 = BOARD_ERROR;
    if (BoardsHealth_DW.countUpdateB1 == 5) {
      BoardsHealth_DW.countUpdateB1 = 0U;
      if (BoardsHealth_DW.countErrorB1 >= 2) {
        guard1 = true;
      } else {
        BoardsHealth_DW.countErrorB1 = 0U;
        BoardsHealth_DW.is_B1 = BoardsHealth_IN_Error;
        *rty_StatusBoard1 = BOARD_ERROR;
      }
    } else if (*rtu_errorB1 == ERROR_PRESENT) {
      BoardsHealth_DW.countErrorB1++;
      guard1 = true;
    } else {
      BoardsHealth_DW.is_B1 = BoardsHealth_IN_OK;
      *rty_StatusBoard1 = BOARD_OK;
    }
    break;

   case BoardsHealth_IN_Fault:
    *rty_StatusBoard1 = BOARD_FAULT;
    break;

   default:
    /* case IN_OK: */
    *rty_StatusBoard1 = BOARD_OK;
    if (*rtu_errorB1 == ERROR_PRESENT) {
      BoardsHealth_DW.countErrorB1++;
      BoardsHealth_DW.is_B1 = BoardsHealth_IN_Error;
      *rty_StatusBoard1 = BOARD_ERROR;
    } else if (BoardsHealth_DW.countUpdateB1 == 5) {
      BoardsHealth_DW.countUpdateB1 = 0U;
      if (BoardsHealth_DW.countErrorB1 >= 2) {
        BoardsHealth_DW.is_B1 = BoardsHealth_IN_Fault;
        *rty_StatusBoard1 = BOARD_FAULT;
      } else {
        BoardsHealth_DW.countErrorB1 = 0U;
        BoardsHealth_DW.is_B1 = BoardsHealth_IN_OK;
        *rty_StatusBoard1 = BOARD_OK;
      }
    }
    break;
  }

  if (guard1) {
    BoardsHealth_DW.is_B1 = BoardsHealth_IN_Fault;
    *rty_StatusBoard1 = BOARD_FAULT;
  }

  guard1 = false;
  switch (BoardsHealth_DW.is_B2) {
   case BoardsHealth_IN_Error:
    *rty_StatusBoard2 = BOARD_ERROR;
    if (BoardsHealth_DW.countUpdateB2 == 5) {
      BoardsHealth_DW.countUpdateB2 = 0U;
      if (BoardsHealth_DW.countErrorB2 >= 2) {
        guard1 = true;
      } else {
        BoardsHealth_DW.countErrorB2 = 0U;
        BoardsHealth_DW.is_B2 = BoardsHealth_IN_Error;
        *rty_StatusBoard2 = BOARD_ERROR;
      }
    } else if (*rtu_errorB2 == ERROR_PRESENT) {
      BoardsHealth_DW.countErrorB2++;
      guard1 = true;
    } else {
      BoardsHealth_DW.is_B2 = BoardsHealth_IN_OK;
      *rty_StatusBoard2 = BOARD_OK;
    }
    break;

   case BoardsHealth_IN_Fault:
    *rty_StatusBoard2 = BOARD_FAULT;
    break;

   default:
    /* case IN_OK: */
    *rty_StatusBoard2 = BOARD_OK;
    if (*rtu_errorB2 == ERROR_PRESENT) {
      BoardsHealth_DW.countErrorB2++;
      BoardsHealth_DW.is_B2 = BoardsHealth_IN_Error;
      *rty_StatusBoard2 = BOARD_ERROR;
    } else if (BoardsHealth_DW.countUpdateB2 == 5) {
      BoardsHealth_DW.countUpdateB2 = 0U;
      if (BoardsHealth_DW.countErrorB2 >= 2) {
        BoardsHealth_DW.is_B2 = BoardsHealth_IN_Fault;
        *rty_StatusBoard2 = BOARD_FAULT;
      } else {
        BoardsHealth_DW.countErrorB2 = 0U;
        BoardsHealth_DW.is_B2 = BoardsHealth_IN_OK;
        *rty_StatusBoard2 = BOARD_OK;
      }
    }
    break;
  }

  if (guard1) {
    BoardsHealth_DW.is_B2 = BoardsHealth_IN_Fault;
    *rty_StatusBoard2 = BOARD_FAULT;
  }

  /* End of Chart: '<Root>/BoardsHealth' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/UpdateBoardsStatus' */
}

/* Model initialize function */
void BoardsHealth_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_BoardsHealth_T *const BoardsHealth_M = &(BoardsHealth_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(BoardsHealth_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
