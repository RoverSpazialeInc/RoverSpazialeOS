/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsDegradedModel.c
 *
 * Code generated for Simulink model 'ActionsDegradedModel'.
 *
 * Model version                  : 9.7
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 20:26:22 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ActionsDegradedModel.h"
#include "decision.h"
#include "decision_enums.h"
#include "rtwtypes.h"
#include "sensors.h"
#include "ActionsDegradedModel_private.h"

/* Named constants for Chart: '<Root>/DegradedRoverAction' */
#define Action_IN_BW_FW_EndedSafeAction ((uint8_T)1U)
#define Action_IN_BW_RL_EndedSafeAction ((uint8_T)1U)
#define Action_IN_BW_RR_EndedSafeAction ((uint8_T)1U)
#define ActionsD_MIN_DISTANCE_TO_ROTATE ((uint16_T)30U)
#define ActionsDe_IN_FW_EndedSafeAction ((uint8_T)1U)
#define ActionsDe_IN_RL_EndedSafeAction ((uint8_T)1U)
#define ActionsDe_IN_RR_EndedSafeAction ((uint8_T)1U)
#define ActionsDeg_IN_BW_RR_RotateRight ((uint8_T)2U)
#define ActionsDegr_IN_BW_FW_SafeAction ((uint8_T)2U)
#define ActionsDegr_IN_BW_FW_UserAction ((uint8_T)3U)
#define ActionsDegr_IN_BW_RL_SafeAction ((uint8_T)2U)
#define ActionsDegr_IN_BW_RL_UserAction ((uint8_T)3U)
#define ActionsDegr_IN_BW_RR_SafeAction ((uint8_T)2U)
#define ActionsDegr_IN_BW_RR_UserAction ((uint8_T)3U)
#define ActionsDegra_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define ActionsDegrad_IN_BW_StopMotors1 ((uint8_T)4U)
#define ActionsDegrad_IN_BW_StopMotors2 ((uint8_T)5U)
#define ActionsDegrad_IN_RR_RotateRight ((uint8_T)1U)
#define ActionsDegrad_OBSTACLE_DETECTED ((uint16_T)300U)
#define ActionsDegrade_IN_BW_RotateLeft ((uint8_T)3U)
#define ActionsDegrade_IN_FW_SafeAction ((uint8_T)2U)
#define ActionsDegrade_IN_FW_UserAction ((uint8_T)3U)
#define ActionsDegrade_IN_RL_RotateLeft ((uint8_T)1U)
#define ActionsDegrade_IN_RL_SafeAction ((uint8_T)2U)
#define ActionsDegrade_IN_RL_StopMotors ((uint8_T)2U)
#define ActionsDegrade_IN_RL_UserAction ((uint8_T)3U)
#define ActionsDegrade_IN_RR_SafeAction ((uint8_T)2U)
#define ActionsDegrade_IN_RR_StopMotors ((uint8_T)2U)
#define ActionsDegrade_IN_RR_UserAction ((uint8_T)3U)
#define ActionsDegradedM_IN_BrakingHard ((uint8_T)2U)
#define ActionsDegradedM_IN_RotateRight ((uint8_T)6U)
#define ActionsDegradedMo_IN_BW_Forward ((uint8_T)1U)
#define ActionsDegradedMo_IN_RotateLeft ((uint8_T)5U)
#define ActionsDegradedMode_IN_Backward ((uint8_T)1U)
#define ActionsDegradedMode_MAX_SPEED_X (50.0F)
#define ActionsDegradedMode_MAX_SPEED_Y (70.0F)
#define ActionsDegradedModel_IN_Forward ((uint8_T)3U)
#define ActionsDegradedModel_IN_None   ((uint8_T)4U)
#define ActionsDegraded_BACKWARD_DEGREE ((uint16_T)180U)

MdlrefDW_ActionsDegradedModel_T ActionsDegradedModel_MdlrefDW;

/* Block states (default storage) */
DW_ActionsDegradedModel_f_T ActionsDegradedModel_DW;

/* Forward declaration for local functions */
static ENUM_SafeAction ActionsD_checkSafetyFromForward(uint16_T sonarLeft,
  uint16_T sonarFront, uint16_T sonarRight);
static ENUM_SafeAction ActionsDe_checkSafetyFromRotate(uint16_T obstacleDetected);
static uint8_T ActionsDeg_trackGyroAngleChange(int32_T *accumulatedChange,
  uint16_T previousValue, uint16_T currentValue, uint16_T threshold);
static uint8_T ActionsDegrade_areAllSpeedsZero(void);
static void ActionsDegradedMo_BW_RotateLeft(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint);
static void ActionsDegradedModel_Backward(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint);
static void ActionsDegradedModel_RotateLeft(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_x_lever, const int16_T *rtu_y_lever,
  const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint);
static void ActionsDegradedMode_RotateRight(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_x_lever, const int16_T *rtu_y_lever,
  const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint);

/* Function for Chart: '<Root>/DegradedRoverAction' */
static ENUM_SafeAction ActionsD_checkSafetyFromForward(uint16_T sonarLeft,
  uint16_T sonarFront, uint16_T sonarRight)
{
  ENUM_SafeAction emergencyAction;
  emergencyAction = SA_NONE;
  if (sonarLeft < ActionsDegrad_OBSTACLE_DETECTED) {
    emergencyAction = SA_BRAKING_HARD;
  } else if (sonarFront < ActionsDegrad_OBSTACLE_DETECTED) {
    emergencyAction = SA_BRAKING_HARD;
  } else if (sonarRight < ActionsDegrad_OBSTACLE_DETECTED) {
    emergencyAction = SA_BRAKING_HARD;
  }

  return emergencyAction;
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static ENUM_SafeAction ActionsDe_checkSafetyFromRotate(uint16_T obstacleDetected)
{
  ENUM_SafeAction emergencyAction;
  emergencyAction = SA_NONE;
  if (obstacleDetected <= ActionsD_MIN_DISTANCE_TO_ROTATE) {
    emergencyAction = SA_BRAKING_HARD;
  }

  return emergencyAction;
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static uint8_T ActionsDeg_trackGyroAngleChange(int32_T *accumulatedChange,
  uint16_T previousValue, uint16_T currentValue, uint16_T threshold)
{
  int32_T deltaRaw;
  deltaRaw = currentValue - previousValue;
  if (deltaRaw > 180) {
    deltaRaw -= 360;
  } else if (deltaRaw < -180) {
    deltaRaw += 360;
  }

  if ((*accumulatedChange < 0) && (deltaRaw < MIN_int32_T - *accumulatedChange))
  {
    *accumulatedChange = MIN_int32_T;
  } else if ((*accumulatedChange > 0) && (deltaRaw > MAX_int32_T
              - *accumulatedChange)) {
    *accumulatedChange = MAX_int32_T;
  } else {
    *accumulatedChange += deltaRaw;
  }

  if (*accumulatedChange < 0) {
    if (*accumulatedChange <= MIN_int32_T) {
      deltaRaw = MAX_int32_T;
    } else {
      deltaRaw = -*accumulatedChange;
    }
  } else {
    deltaRaw = *accumulatedChange;
  }

  return (uint8_T)(deltaRaw >= threshold);
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static uint8_T ActionsDegrade_areAllSpeedsZero(void)
{
  uint8_T out;
  ActionsDegradedModel_DW.callCount++;
  if (ActionsDegradedModel_DW.callCount == 4.0) {
    out = 1U;
    ActionsDegradedModel_DW.callCount = 0.0;
  } else {
    out = 0U;
  }

  return out;
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static void ActionsDegradedMo_BW_RotateLeft(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint)
{
  int32_T safeAction;
  uint8_T rotation_ended;
  safeAction = (int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->left);
  switch (ActionsDegradedModel_DW.is_BW_RotateLeft) {
   case Action_IN_BW_RL_EndedSafeAction:
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsDegradedModel_DW.is_BW_RotateLeft = ActionsDegra_IN_NO_ACTIVE_CHILD;
      ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft = 2U;
    } else if (safeAction == 0) {
      /* l'utente vorrebbe ruotare a SX e non c'è più l'ostacolo */
      ActionsDegradedModel_DW.is_BW_RotateLeft = ActionsDegr_IN_BW_RL_UserAction;

      /*  Degrees */
      ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

      /*  Set point */
      rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
        ActionsDegradedMode_MAX_SPEED_X;
      rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
    }
    break;

   case ActionsDegr_IN_BW_RL_SafeAction:
    if (ActionsDegrade_areAllSpeedsZero() != 0) {
      ActionsDegradedModel_DW.exit_port_index_BW_RL_SafeActio = 2U;
    }

    if (ActionsDegradedModel_DW.exit_port_index_BW_RL_SafeActio == 2U) {
      ActionsDegradedModel_DW.exit_port_index_BW_RL_SafeActio = 0U;
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsDegradedModel_DW.is_BW_RotateLeft =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft = 2U;
      } else if (safeAction == 0) {
        /* l'utente vorrebbe ruotare a SX e non c'è più l'ostacolo */
        ActionsDegradedModel_DW.is_BW_RotateLeft =
          ActionsDegr_IN_BW_RL_UserAction;

        /*  Degrees */
        ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      } else {
        ActionsDegradedModel_DW.is_BW_RotateLeft =
          Action_IN_BW_RL_EndedSafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      }
    }
    break;

   default:
    /* case IN_BW_RL_UserAction: */
    if (safeAction != 0) {
      ActionsDegradedModel_DW.is_BW_RotateLeft = ActionsDegr_IN_BW_RL_SafeAction;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsDegradedModel_DW.is_BW_RotateLeft = ActionsDegra_IN_NO_ACTIVE_CHILD;
      ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft = 2U;
    } else {
      rotation_ended = ActionsDeg_trackGyroAngleChange
        (&ActionsDegradedModel_DW.accumulated_change,
         ActionsDegradedModel_DW.previousGyroscope, *rtu_gyroscope,
         ActionsDegraded_BACKWARD_DEGREE);
      if (rotation_ended == 1) {
        ActionsDegradedModel_DW.is_BW_RotateLeft =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft = 3U;
      } else {
        /*  Degrees */
        ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      }
    }
    break;
  }

  switch (ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft) {
   case 2:
    ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft = 0U;
    ActionsDegradedModel_DW.is_Backward = ActionsDegra_IN_NO_ACTIVE_CHILD;
    ActionsDegradedModel_DW.exit_port_index_Backward = 2U;
    break;

   case 3:
    ActionsDegradedModel_DW.exit_port_index_BW_RotateLeft = 0U;
    ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors2;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;
  }
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static void ActionsDegradedModel_Backward(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint)
{
  int32_T safeAction;
  uint8_T rotation_ended;
  switch (ActionsDegradedModel_DW.is_Backward) {
   case ActionsDegradedMo_IN_BW_Forward:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    safeAction = (int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
      rtu_sonar->front, rtu_sonar->right);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    switch (ActionsDegradedModel_DW.is_BW_Forward) {
     case Action_IN_BW_FW_EndedSafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/DegradedRoverAction'
       */
      /* Chart: '<Root>/DegradedRoverAction' */
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsDegradedModel_DW.is_BW_Forward = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_BW_Forward = 2U;
      } else if (safeAction == 0) {
        /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
        ActionsDegradedModel_DW.is_BW_Forward = ActionsDegr_IN_BW_FW_UserAction;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;

     case ActionsDegr_IN_BW_FW_SafeAction:
      if (ActionsDegrade_areAllSpeedsZero() != 0) {
        ActionsDegradedModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      }

      if (ActionsDegradedModel_DW.exit_port_index_BW_FW_SafeActio == 2U) {
        ActionsDegradedModel_DW.exit_port_index_BW_FW_SafeActio = 0U;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        if (*rtu_currentUserAction != UA_BACKWARD) {
          ActionsDegradedModel_DW.is_BW_Forward =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.exit_port_index_BW_Forward = 2U;
        } else if (safeAction == 0) {
          /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
          ActionsDegradedModel_DW.is_BW_Forward =
            ActionsDegr_IN_BW_FW_UserAction;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_Y;
          rty_setPoint->leftAxis = rty_setPoint->rightAxis;
        } else {
          ActionsDegradedModel_DW.is_BW_Forward =
            Action_IN_BW_FW_EndedSafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;

     default:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/DegradedRoverAction'
       */
      /* Chart: '<Root>/DegradedRoverAction' */
      /* case IN_BW_FW_UserAction: */
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsDegradedModel_DW.is_BW_Forward = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_BW_Forward = 2U;
      } else if (safeAction != 0) {
        ActionsDegradedModel_DW.is_BW_Forward = ActionsDegr_IN_BW_FW_SafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else {
        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;
    }

    if (ActionsDegradedModel_DW.exit_port_index_BW_Forward == 2U) {
      ActionsDegradedModel_DW.exit_port_index_BW_Forward = 0U;
      ActionsDegradedModel_DW.is_Backward = ActionsDegra_IN_NO_ACTIVE_CHILD;
      ActionsDegradedModel_DW.exit_port_index_Backward = 2U;
    }
    break;

   case ActionsDeg_IN_BW_RR_RotateRight:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    /* Chart: '<Root>/DegradedRoverAction' */
    safeAction = (int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->right);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    switch (ActionsDegradedModel_DW.is_BW_RR_RotateRight) {
     case Action_IN_BW_RR_EndedSafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/DegradedRoverAction'
       */
      /* Chart: '<Root>/DegradedRoverAction' */
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsDegradedModel_DW.is_BW_RR_RotateRight =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig = 2U;
      } else if (safeAction == 0) {
        /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
        ActionsDegradedModel_DW.is_BW_RR_RotateRight =
          ActionsDegr_IN_BW_RR_UserAction;

        /*  Degrees */
        ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->leftAxis = -rty_setPoint->rightAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;

     case ActionsDegr_IN_BW_RR_SafeAction:
      if (ActionsDegrade_areAllSpeedsZero() != 0) {
        ActionsDegradedModel_DW.exit_port_index_BW_RR_SafeActio = 2U;
      }

      if (ActionsDegradedModel_DW.exit_port_index_BW_RR_SafeActio == 2U) {
        ActionsDegradedModel_DW.exit_port_index_BW_RR_SafeActio = 0U;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        if (*rtu_currentUserAction != UA_BACKWARD) {
          ActionsDegradedModel_DW.is_BW_RR_RotateRight =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig = 2U;
        } else if (safeAction == 0) {
          /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
          ActionsDegradedModel_DW.is_BW_RR_RotateRight =
            ActionsDegr_IN_BW_RR_UserAction;

          /*  Degrees */
          ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_X;
          rty_setPoint->leftAxis = -rty_setPoint->rightAxis;
        } else {
          ActionsDegradedModel_DW.is_BW_RR_RotateRight =
            Action_IN_BW_RR_EndedSafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;

     default:
      /* case IN_BW_RR_UserAction: */
      if (safeAction != 0) {
        ActionsDegradedModel_DW.is_BW_RR_RotateRight =
          ActionsDegr_IN_BW_RR_SafeAction;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
      } else if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsDegradedModel_DW.is_BW_RR_RotateRight =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig = 2U;
      } else {
        /* Chart: '<Root>/DegradedRoverAction' */
        rotation_ended = ActionsDeg_trackGyroAngleChange
          (&ActionsDegradedModel_DW.accumulated_change,
           ActionsDegradedModel_DW.previousGyroscope, *rtu_gyroscope,
           ActionsDegraded_BACKWARD_DEGREE);
        if (rotation_ended == 1) {
          ActionsDegradedModel_DW.is_BW_RR_RotateRight =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig = 3U;
        } else {
          /* Chart: '<Root>/DegradedRoverAction' */
          /*  Degrees */
          ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_X;
          rty_setPoint->leftAxis = -rty_setPoint->rightAxis;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;
    }

    switch (ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig) {
     case 2:
      ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig = 0U;
      ActionsDegradedModel_DW.is_Backward = ActionsDegra_IN_NO_ACTIVE_CHILD;
      ActionsDegradedModel_DW.exit_port_index_Backward = 2U;
      break;

     case 3:
      ActionsDegradedModel_DW.exit_port_index_BW_RR_RotateRig = 0U;
      ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors2;

      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/DegradedRoverAction'
       */
      /* Chart: '<Root>/DegradedRoverAction' */
      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;
    }
    break;

   case ActionsDegrade_IN_BW_RotateLeft:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    ActionsDegradedMo_BW_RotateLeft(rtu_currentUserAction, rtu_y_lever,
      rtu_gyroscope, rtu_sonar, rty_setPoint);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   case ActionsDegrad_IN_BW_StopMotors1:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsDegradedModel_DW.is_Backward = ActionsDegra_IN_NO_ACTIVE_CHILD;
      ActionsDegradedModel_DW.exit_port_index_Backward = 2U;
    } else if (ActionsDegrade_areAllSpeedsZero() != 0) {
      if (rtu_sonar->left > ActionsD_MIN_DISTANCE_TO_ROTATE) {
        ActionsDegradedModel_DW.is_Backward = ActionsDegrade_IN_BW_RotateLeft;

        /*  I valori per la rotazione vanno resettati nel Superstate
           Se interrompessi la user action per eseguire la safe action, al mio ritorno non devo perdere gli accumulated change del delta  */
        ActionsDegradedModel_DW.accumulated_change = 0;
        if ((int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->left) != 0) {
          ActionsDegradedModel_DW.is_BW_RotateLeft =
            ActionsDegr_IN_BW_RL_SafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /* [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsDegradedModel_DW.is_BW_RotateLeft =
            ActionsDegr_IN_BW_RL_UserAction;

          /*  Degrees */
          ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

          /*  Set point */
          rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_X;
          rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
        }
      } else if (rtu_sonar->right > ActionsD_MIN_DISTANCE_TO_ROTATE) {
        ActionsDegradedModel_DW.is_Backward = ActionsDeg_IN_BW_RR_RotateRight;

        /*  I valori per la rotazione vanno resettati nel Superstate
           Se interrompessi la user action per eseguire la safe action, al mio ritorno non devo perdere gli accumulated change del delta  */
        ActionsDegradedModel_DW.accumulated_change = 0;
        if ((int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->right) != 0) {
          ActionsDegradedModel_DW.is_BW_RR_RotateRight =
            ActionsDegr_IN_BW_RR_SafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /* [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsDegradedModel_DW.is_BW_RR_RotateRight =
            ActionsDegr_IN_BW_RR_UserAction;

          /*  Degrees */
          ActionsDegradedModel_DW.previousGyroscope = *rtu_gyroscope;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_X;
          rty_setPoint->leftAxis = -rty_setPoint->rightAxis;
        }
      }
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   default:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    /* case IN_BW_StopMotors2: */
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsDegradedModel_DW.is_Backward = ActionsDegra_IN_NO_ACTIVE_CHILD;
      ActionsDegradedModel_DW.exit_port_index_Backward = 2U;
    } else if (ActionsDegrade_areAllSpeedsZero() != 0) {
      ActionsDegradedModel_DW.is_Backward = ActionsDegradedMo_IN_BW_Forward;
      if ((int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
           rtu_sonar->front, rtu_sonar->right) != 0) {
        ActionsDegradedModel_DW.is_BW_Forward = ActionsDegr_IN_BW_FW_SafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else {
        /*  [safeAction == ENUM_SafeAction.SA_NONE] */
        ActionsDegradedModel_DW.is_BW_Forward = ActionsDegr_IN_BW_FW_UserAction;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;
  }

  if (ActionsDegradedModel_DW.exit_port_index_Backward == 2U) {
    ActionsDegradedModel_DW.exit_port_index_Backward = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedMode_IN_Backward;
      ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors1;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_ROTATE_RIGHT:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedM_IN_RotateRight;
      ActionsDegradedModel_DW.is_RotateRight = ActionsDegrade_IN_RR_StopMotors;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_ROTATE_LEFT:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedMo_IN_RotateLeft;
      ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_StopMotors;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_FORWARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedModel_IN_Forward;
      if ((int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
           rtu_sonar->front, rtu_sonar->right) != 0) {
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else {
        /*  [safeAction == ENUM_SafeAction.SA_NONE] */
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }
      break;

     case UA_BRAKING_HARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedM_IN_BrakingHard;

      /*  Action */
      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedModel_IN_None;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static void ActionsDegradedModel_RotateLeft(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_x_lever, const int16_T *rtu_y_lever,
  const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint)
{
  int32_T safeAction;
  if (ActionsDegradedModel_DW.is_RotateLeft == ActionsDegrade_IN_RL_RotateLeft)
  {
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    /* Chart: '<Root>/DegradedRoverAction' */
    safeAction = (int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->left);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    switch (ActionsDegradedModel_DW.is_RL_RotateLeft) {
     case ActionsDe_IN_RL_EndedSafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/DegradedRoverAction'
       */
      /* Chart: '<Root>/DegradedRoverAction' */
      if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
        ActionsDegradedModel_DW.is_RL_RotateLeft =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.is_RotateLeft = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_RotateLeft = 2U;
      } else if (safeAction == 0) {
        /* l'utente vorrebbe continuare a ruotare a SX e non c'è più l'ostacolo */
        ActionsDegradedModel_DW.is_RL_RotateLeft =
          ActionsDegrade_IN_RL_UserAction;
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;

     case ActionsDegrade_IN_RL_SafeAction:
      if (ActionsDegrade_areAllSpeedsZero() != 0) {
        ActionsDegradedModel_DW.exit_port_index_RL_SafeAction = 2U;
      }

      if (ActionsDegradedModel_DW.exit_port_index_RL_SafeAction == 2U) {
        ActionsDegradedModel_DW.exit_port_index_RL_SafeAction = 0U;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
          ActionsDegradedModel_DW.is_RL_RotateLeft =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.is_RotateLeft =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.exit_port_index_RotateLeft = 2U;
        } else if (safeAction == 0) {
          /* l'utente vorrebbe continuare a ruotare a SX e non c'è più l'ostacolo */
          ActionsDegradedModel_DW.is_RL_RotateLeft =
            ActionsDegrade_IN_RL_UserAction;
          rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_X;
          rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
        } else {
          ActionsDegradedModel_DW.is_RL_RotateLeft =
            ActionsDe_IN_RL_EndedSafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;

     default:
      /* case IN_RL_UserAction: */
      if (safeAction != 0) {
        ActionsDegradedModel_DW.is_RL_RotateLeft =
          ActionsDegrade_IN_RL_SafeAction;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
      } else if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
        ActionsDegradedModel_DW.is_RL_RotateLeft =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.is_RotateLeft = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_RotateLeft = 2U;
      } else {
        /* Chart: '<Root>/DegradedRoverAction' */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;
    }

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    /* case IN_RL_StopMotors: */
  } else if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
    ActionsDegradedModel_DW.is_RotateLeft = ActionsDegra_IN_NO_ACTIVE_CHILD;
    ActionsDegradedModel_DW.exit_port_index_RotateLeft = 2U;
  } else if (ActionsDegrade_areAllSpeedsZero() != 0) {
    ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_RotateLeft;
    if ((int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->left) != 0) {
      ActionsDegradedModel_DW.is_RL_RotateLeft = ActionsDegrade_IN_RL_SafeAction;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else {
      /* [safeAction == ENUM_SafeAction.SA_NONE] */
      ActionsDegradedModel_DW.is_RL_RotateLeft = ActionsDegrade_IN_RL_UserAction;
      rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
        ActionsDegradedMode_MAX_SPEED_X;
      rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }

  if (ActionsDegradedModel_DW.exit_port_index_RotateLeft == 2U) {
    ActionsDegradedModel_DW.exit_port_index_RotateLeft = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedMode_IN_Backward;
      ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors1;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_ROTATE_RIGHT:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedM_IN_RotateRight;
      ActionsDegradedModel_DW.is_RotateRight = ActionsDegrade_IN_RR_StopMotors;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_ROTATE_LEFT:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedMo_IN_RotateLeft;
      ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_StopMotors;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_FORWARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedModel_IN_Forward;
      if ((int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
           rtu_sonar->front, rtu_sonar->right) != 0) {
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else {
        /*  [safeAction == ENUM_SafeAction.SA_NONE] */
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }
      break;

     case UA_BRAKING_HARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedM_IN_BrakingHard;

      /*  Action */
      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedModel_IN_None;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* Function for Chart: '<Root>/DegradedRoverAction' */
static void ActionsDegradedMode_RotateRight(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_x_lever, const int16_T *rtu_y_lever,
  const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint)
{
  int32_T safeAction;
  if (ActionsDegradedModel_DW.is_RotateRight == ActionsDegrad_IN_RR_RotateRight)
  {
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    /* Chart: '<Root>/DegradedRoverAction' */
    safeAction = (int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->right);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    switch (ActionsDegradedModel_DW.is_RR_RotateRight) {
     case ActionsDe_IN_RR_EndedSafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/DegradedRoverAction'
       */
      /* Chart: '<Root>/DegradedRoverAction' */
      if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
        ActionsDegradedModel_DW.is_RR_RotateRight =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.is_RotateRight = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_RotateRight = 2U;
      } else if (safeAction == 0) {
        /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
        ActionsDegradedModel_DW.is_RR_RotateRight =
          ActionsDegrade_IN_RR_UserAction;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;

     case ActionsDegrade_IN_RR_SafeAction:
      if (ActionsDegrade_areAllSpeedsZero() != 0) {
        ActionsDegradedModel_DW.exit_port_index_RR_SafeAction = 2U;
      }

      if (ActionsDegradedModel_DW.exit_port_index_RR_SafeAction == 2U) {
        ActionsDegradedModel_DW.exit_port_index_RR_SafeAction = 0U;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
          ActionsDegradedModel_DW.is_RR_RotateRight =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.is_RotateRight =
            ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.exit_port_index_RotateRight = 2U;
        } else if (safeAction == 0) {
          /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
          ActionsDegradedModel_DW.is_RR_RotateRight =
            ActionsDegrade_IN_RR_UserAction;

          /*  Set point */
          rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_X;
          rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
        } else {
          ActionsDegradedModel_DW.is_RR_RotateRight =
            ActionsDe_IN_RR_EndedSafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;

     default:
      /* case IN_RR_UserAction: */
      if (safeAction != 0) {
        ActionsDegradedModel_DW.is_RR_RotateRight =
          ActionsDegrade_IN_RR_SafeAction;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
        /* Chart: '<Root>/DegradedRoverAction' */
        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/DegradedRoverAction'
         */
      } else if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
        ActionsDegradedModel_DW.is_RR_RotateRight =
          ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.is_RotateRight = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_RotateRight = 2U;
      } else {
        /* Chart: '<Root>/DegradedRoverAction' */
        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;
    }

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    /* case IN_RR_StopMotors: */
  } else if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
    ActionsDegradedModel_DW.is_RotateRight = ActionsDegra_IN_NO_ACTIVE_CHILD;
    ActionsDegradedModel_DW.exit_port_index_RotateRight = 2U;
  } else if (ActionsDegrade_areAllSpeedsZero() != 0) {
    ActionsDegradedModel_DW.is_RotateRight = ActionsDegrad_IN_RR_RotateRight;
    if ((int32_T)ActionsDe_checkSafetyFromRotate(rtu_sonar->right) != 0) {
      ActionsDegradedModel_DW.is_RR_RotateRight =
        ActionsDegrade_IN_RR_SafeAction;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else {
      /* [safeAction == ENUM_SafeAction.SA_NONE] */
      ActionsDegradedModel_DW.is_RR_RotateRight =
        ActionsDegrade_IN_RR_UserAction;

      /*  Set point */
      rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
        ActionsDegradedMode_MAX_SPEED_X;
      rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }

  if (ActionsDegradedModel_DW.exit_port_index_RotateRight == 2U) {
    ActionsDegradedModel_DW.exit_port_index_RotateRight = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/DegradedRoverAction'
     */
    /* Chart: '<Root>/DegradedRoverAction' */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedMode_IN_Backward;
      ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors1;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_ROTATE_RIGHT:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedM_IN_RotateRight;
      ActionsDegradedModel_DW.is_RotateRight = ActionsDegrade_IN_RR_StopMotors;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_ROTATE_LEFT:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedMo_IN_RotateLeft;
      ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_StopMotors;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     case UA_FORWARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedModel_IN_Forward;
      if ((int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
           rtu_sonar->front, rtu_sonar->right) != 0) {
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else {
        /*  [safeAction == ENUM_SafeAction.SA_NONE] */
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }
      break;

     case UA_BRAKING_HARD:
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedM_IN_BrakingHard;

      /*  Action */
      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsDegradedModel_DW.is_CurrentRoverAction =
        ActionsDegradedModel_IN_None;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* System initialize for referenced model: 'ActionsDegradedModel' */
void ActionsDegradedModel_Init(BUS_SetPoint *rty_setPoint)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
   *  Chart: '<Root>/DegradedRoverAction'
   */
  /* Chart: '<Root>/DegradedRoverAction' */
  /*  Outputs initialization */
  /*  Superstate inutile? Forse con lo stato degradato ha senso se questo chart cambia stato */
  ActionsDegradedModel_DW.is_CurrentRoverAction = ActionsDegradedModel_IN_None;

  /*  Set point */
  rty_setPoint->rightAxis = 0.0F;
  rty_setPoint->leftAxis = 0.0F;

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
}

/* Output and update for referenced model: 'ActionsDegradedModel' */
void ActionsDegra_ComputeRoverAction(const ENUM_UserAction
  *rtu_currentUserAction, const int16_T *rtu_x_lever, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint)
{
  int32_T safeAction_tmp;

  /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
   *  Chart: '<Root>/DegradedRoverAction'
   */
  /* Chart: '<Root>/DegradedRoverAction' */
  switch (ActionsDegradedModel_DW.is_CurrentRoverAction) {
   case ActionsDegradedMode_IN_Backward:
    ActionsDegradedModel_Backward(rtu_currentUserAction, rtu_y_lever,
      rtu_gyroscope, rtu_sonar, rty_setPoint);
    break;

   case ActionsDegradedM_IN_BrakingHard:
    if (*rtu_currentUserAction != UA_BRAKING_HARD) {
      switch (*rtu_currentUserAction) {
       case UA_BACKWARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedMode_IN_Backward;
        ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors1;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_ROTATE_RIGHT:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedM_IN_RotateRight;
        ActionsDegradedModel_DW.is_RotateRight = ActionsDegrade_IN_RR_StopMotors;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_ROTATE_LEFT:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedMo_IN_RotateLeft;
        ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_StopMotors;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_FORWARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedModel_IN_Forward;
        if ((int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
             rtu_sonar->front, rtu_sonar->right) != 0) {
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /*  [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_Y;
          rty_setPoint->leftAxis = rty_setPoint->rightAxis;
        }
        break;

       case UA_BRAKING_HARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedM_IN_BrakingHard;

        /*  Action */
        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       default:
        /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
           [currentUserAction == ENUM_UserAction.UA_NONE] */
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedModel_IN_None;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;
      }
    }
    break;

   case ActionsDegradedModel_IN_Forward:
    safeAction_tmp = (int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
      rtu_sonar->front, rtu_sonar->right);
    switch (ActionsDegradedModel_DW.is_Forward) {
     case ActionsDe_IN_FW_EndedSafeAction:
      if (*rtu_currentUserAction != UA_FORWARD) {
        ActionsDegradedModel_DW.is_Forward = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_Forward = 2U;
      } else if (safeAction_tmp == 0) {
        /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }
      break;

     case ActionsDegrade_IN_FW_SafeAction:
      if (ActionsDegrade_areAllSpeedsZero() != 0) {
        ActionsDegradedModel_DW.exit_port_index_FW_SafeAction = 2U;
      }

      if (ActionsDegradedModel_DW.exit_port_index_FW_SafeAction == 2U) {
        ActionsDegradedModel_DW.exit_port_index_FW_SafeAction = 0U;
        if (*rtu_currentUserAction != UA_FORWARD) {
          ActionsDegradedModel_DW.is_Forward = ActionsDegra_IN_NO_ACTIVE_CHILD;
          ActionsDegradedModel_DW.exit_port_index_Forward = 2U;
        } else if (safeAction_tmp == 0) {
          /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_Y;
          rty_setPoint->leftAxis = rty_setPoint->rightAxis;
        } else {
          ActionsDegradedModel_DW.is_Forward = ActionsDe_IN_FW_EndedSafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }
      }
      break;

     default:
      /* case IN_FW_UserAction: */
      if (*rtu_currentUserAction != UA_FORWARD) {
        ActionsDegradedModel_DW.is_Forward = ActionsDegra_IN_NO_ACTIVE_CHILD;
        ActionsDegradedModel_DW.exit_port_index_Forward = 2U;
      } else if (safeAction_tmp != 0) {
        ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else {
        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsDegradedMode_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;
      }
      break;
    }

    if (ActionsDegradedModel_DW.exit_port_index_Forward == 2U) {
      ActionsDegradedModel_DW.exit_port_index_Forward = 0U;
      switch (*rtu_currentUserAction) {
       case UA_BACKWARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedMode_IN_Backward;
        ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors1;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_ROTATE_RIGHT:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedM_IN_RotateRight;
        ActionsDegradedModel_DW.is_RotateRight = ActionsDegrade_IN_RR_StopMotors;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_ROTATE_LEFT:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedMo_IN_RotateLeft;
        ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_StopMotors;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_FORWARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedModel_IN_Forward;
        if (safeAction_tmp != 0) {
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /*  [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_Y;
          rty_setPoint->leftAxis = rty_setPoint->rightAxis;
        }
        break;

       case UA_BRAKING_HARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedM_IN_BrakingHard;

        /*  Action */
        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       default:
        /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
           [currentUserAction == ENUM_UserAction.UA_NONE] */
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedModel_IN_None;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;
      }
    }
    break;

   case ActionsDegradedModel_IN_None:
    if (*rtu_currentUserAction != UA_NONE) {
      switch (*rtu_currentUserAction) {
       case UA_BACKWARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedMode_IN_Backward;
        ActionsDegradedModel_DW.is_Backward = ActionsDegrad_IN_BW_StopMotors1;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_ROTATE_RIGHT:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedM_IN_RotateRight;
        ActionsDegradedModel_DW.is_RotateRight = ActionsDegrade_IN_RR_StopMotors;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_ROTATE_LEFT:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedMo_IN_RotateLeft;
        ActionsDegradedModel_DW.is_RotateLeft = ActionsDegrade_IN_RL_StopMotors;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       case UA_FORWARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedModel_IN_Forward;
        if ((int32_T)ActionsD_checkSafetyFromForward(rtu_sonar->left,
             rtu_sonar->front, rtu_sonar->right) != 0) {
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_SafeAction;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /*  [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsDegradedModel_DW.is_Forward = ActionsDegrade_IN_FW_UserAction;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsDegradedMode_MAX_SPEED_Y;
          rty_setPoint->leftAxis = rty_setPoint->rightAxis;
        }
        break;

       case UA_BRAKING_HARD:
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedM_IN_BrakingHard;

        /*  Action */
        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;

       default:
        /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
           [currentUserAction == ENUM_UserAction.UA_NONE] */
        ActionsDegradedModel_DW.is_CurrentRoverAction =
          ActionsDegradedModel_IN_None;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
        break;
      }
    }
    break;

   case ActionsDegradedMo_IN_RotateLeft:
    ActionsDegradedModel_RotateLeft(rtu_currentUserAction, rtu_x_lever,
      rtu_y_lever, rtu_sonar, rty_setPoint);
    break;

   default:
    /* case IN_RotateRight: */
    ActionsDegradedMode_RotateRight(rtu_currentUserAction, rtu_x_lever,
      rtu_y_lever, rtu_sonar, rty_setPoint);
    break;
  }

  /* End of Chart: '<Root>/DegradedRoverAction' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
}

/* Model initialize function */
void ActionsDegradedModel_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_ActionsDegradedModel_T *const ActionsDegradedModel_M =
    &(ActionsDegradedModel_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(ActionsDegradedModel_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
