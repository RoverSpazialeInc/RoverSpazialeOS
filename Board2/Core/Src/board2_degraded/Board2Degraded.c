/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2Degraded.c
 *
 * Code generated for Simulink model 'Board2Degraded'.
 *
 * Model version                  : 10.5
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Feb 13 16:46:04 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Board2Degraded.h"
#include "rtwtypes.h"
#include "decision_enums.h"
#include "sensors.h"
#include "Board2Degraded_types.h"
#include "controller_masks.h"
#include "ActionsDegradedModel.h"
#include "Board2Health.h"

/* Named constants for Chart: '<Root>/SupervisorB2' */
#define Board2Deg_IN_SupervisorInactive ((uint8_T)4U)
#define Board2Deg_IN_UpdateBoardsHealth ((uint8_T)3U)
#define Board2Degra_IN_SupervisionEnded ((uint8_T)2U)
#define Board2Degra_IN_SupervisorActive ((uint8_T)3U)
#define Board2Degrad_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Board2Degrad_IN_checkRTOSHealth ((uint8_T)6U)
#define Board2Degraded_IN_Emergency    ((uint8_T)1U)
#define Board2_IN_UserActionComputation ((uint8_T)4U)
#define Board_IN_EmergencyStateAnalysis ((uint8_T)1U)
#define Board_IN_RoverActionComputation ((uint8_T)2U)
#define IN_ValidateReceivedSensorReadin ((uint8_T)5U)

/* Block signals (default storage) */
B_Board2Degraded_T Board2Degraded_B;

/* Block states (default storage) */
DW_Board2Degraded_T Board2Degraded_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Board2Degraded_T Board2Degraded_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Board2Degraded_T Board2Degraded_Y;

/* Real-time model */
static RT_MODEL_Board2Degraded_T Board2Degraded_M_;
RT_MODEL_Board2Degraded_T *const Board2Degraded_M = &Board2Degraded_M_;

/* Forward declaration for local functions */
static ENUM_Error Board2De_validateSensorReadings(uint8_T sensorReadings, real_T
  errorMask);
static ENUM_Error Board2Degraded_emergencyCheck(uint16_T
  localStateRover_sonar_left, uint16_T localStateRover_sonar_front, uint16_T
  localStateRover_sonar_right, Gyroscope localStateRover_gyroscope, int16_T
  localStateRover_remoteControlle, int16_T localStateRover_remoteControl_0);
static ENUM_UserAction Board2Degrade_computeUserAction(int16_T x_lever, int16_T
  y_lever, uint16_T buttons, uint16_T braking_hard_mask);
static ENUM_Error Board2Degrad_validateRTOSHealth(uint8_T deadlineMissed);

/* Function for Chart: '<Root>/SupervisorB2' */
static ENUM_Error Board2De_validateSensorReadings(uint8_T sensorReadings, real_T
  errorMask)
{
  ENUM_Error resultSensorReadings;
  if ((sensorReadings & (uint8_T)errorMask) != 0) {
    resultSensorReadings = ERROR_PRESENT;
  } else {
    resultSensorReadings = NO_ERROR;
  }

  return resultSensorReadings;
}

/* Function for Chart: '<Root>/SupervisorB2' */
static ENUM_Error Board2Degraded_emergencyCheck(uint16_T
  localStateRover_sonar_left, uint16_T localStateRover_sonar_front, uint16_T
  localStateRover_sonar_right, Gyroscope localStateRover_gyroscope, int16_T
  localStateRover_remoteControlle, int16_T localStateRover_remoteControl_0)
{
  ENUM_Error errB2;
  errB2 = NO_ERROR;
  if ((localStateRover_sonar_left > 400) || (localStateRover_sonar_front > 400) ||
      (localStateRover_sonar_right > 400)) {
    errB2 = ERROR_PRESENT;
  }

  if (localStateRover_gyroscope > 360) {
    errB2 = ERROR_PRESENT;
  }

  if ((localStateRover_remoteControl_0 < -512) ||
      (localStateRover_remoteControl_0 > 512) ||
      (localStateRover_remoteControlle < -512) ||
      (localStateRover_remoteControlle > 512)) {
    errB2 = ERROR_PRESENT;
  }

  return errB2;
}

/* Function for Chart: '<Root>/SupervisorB2' */
static ENUM_UserAction Board2Degrade_computeUserAction(int16_T x_lever, int16_T
  y_lever, uint16_T buttons, uint16_T braking_hard_mask)
{
  ENUM_UserAction userAction;
  userAction = UA_NONE;
  if ((buttons & braking_hard_mask) == braking_hard_mask) {
    userAction = UA_BRAKING_HARD;
  } else if (x_lever < 0) {
    userAction = UA_ROTATE_LEFT;
  } else if (x_lever > 0) {
    userAction = UA_ROTATE_RIGHT;
  } else if (y_lever > 0) {
    userAction = UA_FORWARD;
  } else if (y_lever < 0) {
    userAction = UA_BACKWARD;
  }

  return userAction;
}

/* Function for Chart: '<Root>/SupervisorB2' */
static ENUM_Error Board2Degrad_validateRTOSHealth(uint8_T deadlineMissed)
{
  ENUM_Error resultBoardHealth;
  if (deadlineMissed == 1) {
    resultBoardHealth = ERROR_PRESENT;
  } else {
    resultBoardHealth = NO_ERROR;
  }

  return resultBoardHealth;
}

/* Model step function */
void Board2Degraded_step(void)
{
  /* Chart: '<Root>/SupervisorB2' incorporates:
   *  Inport: '<Root>/areSensorsValid'
   *  Inport: '<Root>/deadlineOccurred'
   *  Inport: '<Root>/gyroscope'
   *  Inport: '<Root>/remoteController'
   *  Inport: '<Root>/sonar'
   */
  if (Board2Degraded_DW.is_active_c3_Board2Degraded == 0U) {
    Board2Degraded_DW.is_active_c3_Board2Degraded = 1U;
    Board2Degraded_DW.is_c3_Board2Degraded = Board2Deg_IN_SupervisorInactive;

    /* Outport: '<Root>/supervision_ended' */
    Board2Degraded_Y.supervision_ended = 0U;
  } else {
    switch (Board2Degraded_DW.is_c3_Board2Degraded) {
     case Board2Degraded_IN_Emergency:
      break;

     case Board2Degra_IN_SupervisionEnded:
      Board2Degraded_DW.is_c3_Board2Degraded = Board2Deg_IN_SupervisorInactive;

      /* Outport: '<Root>/supervision_ended' */
      Board2Degraded_Y.supervision_ended = 0U;
      break;

     case Board2Degra_IN_SupervisorActive:
      switch (Board2Degraded_DW.is_SupervisorActive) {
       case Board_IN_EmergencyStateAnalysis:
        if (Board2Degraded_B.errorB2 == NO_ERROR) {
          Board2Degraded_DW.is_SupervisorActive =
            Board2Deg_IN_UpdateBoardsHealth;

          /* ModelReference: '<Root>/Board2Health' */
          Board2Health_UpdateBoardStatus(&Board2Degraded_B.errorB2,
            &Board2Degraded_B.StatusBoard2);
        } else {
          /* ModelReference: '<Root>/Board2Health' */
          Board2Health_UpdateBoardStatus(&Board2Degraded_B.errorB2,
            &Board2Degraded_B.StatusBoard2);
          Board2Degraded_DW.is_SupervisorActive =
            Board2Degrad_IN_NO_ACTIVE_CHILD;
          Board2Degraded_DW.exit_port_index_SupervisorActiv = 2U;
        }
        break;

       case Board_IN_RoverActionComputation:
        Board2Degraded_DW.is_SupervisorActive = Board2Degrad_IN_NO_ACTIVE_CHILD;
        Board2Degraded_DW.exit_port_index_SupervisorActiv = 2U;
        break;

       case Board2Deg_IN_UpdateBoardsHealth:
        Board2Degraded_DW.is_SupervisorActive = Board2_IN_UserActionComputation;
        Board2Degraded_B.computedUserAction = Board2Degrade_computeUserAction
          (Board2Degraded_B.board2LocalState.remoteController.x_lever,
           Board2Degraded_B.board2LocalState.remoteController.y_lever,
           Board2Degraded_B.board2LocalState.remoteController.buttons,
           ((uint16_T)BRAKING_HARD_MASK));
        break;

       case Board2_IN_UserActionComputation:
        Board2Degraded_DW.is_SupervisorActive = Board_IN_RoverActionComputation;

        /* ModelReference: '<Root>/ActionsModel' incorporates:
         *  Outport: '<Root>/setPoint'
         */
        ActionsDegra_ComputeRoverAction(&Board2Degraded_B.computedUserAction,
          &Board2Degraded_B.board2LocalState.remoteController.x_lever,
          &Board2Degraded_B.board2LocalState.remoteController.y_lever,
          &Board2Degraded_B.board2LocalState.gyroscope,
          &Board2Degraded_B.board2LocalState.sonar, &Board2Degraded_Y.setPoint);
        break;

       case IN_ValidateReceivedSensorReadin:
        if (Board2Degraded_B.errorB2 == NO_ERROR) {
          Board2Degraded_DW.is_SupervisorActive =
            Board2Degrad_IN_checkRTOSHealth;
          Board2Degraded_B.errorB2 = Board2Degrad_validateRTOSHealth
            (Board2Degraded_B.board2LocalState.deadlineOccurred);
        } else {
          /* ModelReference: '<Root>/Board2Health' */
          Board2Health_UpdateBoardStatus(&Board2Degraded_B.errorB2,
            &Board2Degraded_B.StatusBoard2);
          Board2Degraded_DW.is_SupervisorActive =
            Board2Degrad_IN_NO_ACTIVE_CHILD;
          Board2Degraded_DW.exit_port_index_SupervisorActiv = 2U;
        }
        break;

       default:
        /* case IN_checkRTOSHealth: */
        if (Board2Degraded_B.errorB2 == NO_ERROR) {
          Board2Degraded_DW.is_SupervisorActive =
            Board_IN_EmergencyStateAnalysis;
          Board2Degraded_B.errorB2 = Board2Degraded_emergencyCheck
            (Board2Degraded_B.board2LocalState.sonar.left,
             Board2Degraded_B.board2LocalState.sonar.front,
             Board2Degraded_B.board2LocalState.sonar.right,
             Board2Degraded_B.board2LocalState.gyroscope,
             Board2Degraded_B.board2LocalState.remoteController.y_lever,
             Board2Degraded_B.board2LocalState.remoteController.x_lever);
        } else {
          /* ModelReference: '<Root>/Board2Health' */
          Board2Health_UpdateBoardStatus(&Board2Degraded_B.errorB2,
            &Board2Degraded_B.StatusBoard2);
          Board2Degraded_DW.is_SupervisorActive =
            Board2Degrad_IN_NO_ACTIVE_CHILD;
          Board2Degraded_DW.exit_port_index_SupervisorActiv = 2U;
        }
        break;
      }

      if (Board2Degraded_DW.exit_port_index_SupervisorActiv == 2U) {
        Board2Degraded_DW.exit_port_index_SupervisorActiv = 0U;
        if (Board2Degraded_B.StatusBoard2 == BOARD_FAULT) {
          Board2Degraded_DW.is_c3_Board2Degraded = Board2Degraded_IN_Emergency;
          enterEmergency();
        } else {
          Board2Degraded_DW.is_c3_Board2Degraded =
            Board2Degra_IN_SupervisionEnded;

          /* Outport: '<Root>/supervision_ended' */
          Board2Degraded_Y.supervision_ended = 1U;

          /* printLocalStateB2(board2LocalState); */
        }
      }
      break;

     default:
      /* Outport: '<Root>/supervision_ended' */
      /* case IN_SupervisorInactive: */
      Board2Degraded_Y.supervision_ended = 0U;
      Board2Degraded_B.board2LocalState.sonar = Board2Degraded_U.sonar;
      Board2Degraded_B.board2LocalState.gyroscope = Board2Degraded_U.gyroscope;
      Board2Degraded_B.board2LocalState.remoteController =
        Board2Degraded_U.remoteController;
      Board2Degraded_B.board2LocalState.sensorReadings =
        Board2Degraded_U.areSensorsValid;
      Board2Degraded_B.board2LocalState.deadlineOccurred =
        Board2Degraded_U.deadlineOccurred;
      Board2Degraded_DW.is_c3_Board2Degraded = Board2Degra_IN_SupervisorActive;
      Board2Degraded_DW.is_SupervisorActive = IN_ValidateReceivedSensorReadin;
      Board2Degraded_B.errorB2 = Board2De_validateSensorReadings
        (Board2Degraded_B.board2LocalState.sensorReadings, 7.0);
      break;
    }
  }

  /* End of Chart: '<Root>/SupervisorB2' */
}

/* Model initialize function */
void Board2Degraded_initialize(void)
{
  /* Model Initialize function for ModelReference Block: '<Root>/ActionsModel' */
  ActionsDegradedModel_initialize(rtmGetErrorStatusPointer(Board2Degraded_M));

  /* Model Initialize function for ModelReference Block: '<Root>/Board2Health' */
  Board2Health_initialize(rtmGetErrorStatusPointer(Board2Degraded_M));

  /* SystemInitialize for ModelReference: '<Root>/ActionsModel' incorporates:
   *  Outport: '<Root>/setPoint'
   */
  ActionsDegradedModel_Init(&Board2Degraded_Y.setPoint);

  /* SystemInitialize for ModelReference: '<Root>/Board2Health' */
  Board2Health_Init();
}

/* Model terminate function */
void Board2Degraded_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
