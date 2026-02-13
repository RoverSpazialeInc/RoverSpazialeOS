/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ActionsModel.c
 *
 * Code generated for Simulink model 'ActionsModel'.
 *
 * Model version                  : 9.8
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Feb 13 16:27:15 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ActionsModel.h"
#include "ActionsModel_types.h"
#include "decision_enums.h"
#include "ActionsModel_private.h"
#include "rtwtypes.h"
#include "sensors.h"
#include "decision.h"
#include <math.h>

/* Named constants for Chart: '<Root>/MovingObstacles' */
#define Ac_IN_PossibleStartingFromRight ((uint8_T)2U)
#define Act_IN_PossibleStartingFromLeft ((uint8_T)4U)
#define ActionsMod_IN_RightSideDetected ((uint8_T)4U)
#define ActionsMode_IN_LeftSideDetected ((uint8_T)2U)
#define ActionsModel_IN_LeftSideClear  ((uint8_T)1U)
#define ActionsModel_IN_MovedFromLeft  ((uint8_T)3U)
#define ActionsModel_IN_MovedFromRight ((uint8_T)1U)
#define ActionsModel_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define ActionsModel_IN_NotTracking    ((uint8_T)1U)
#define ActionsModel_IN_RightSideClear ((uint8_T)3U)
#define ActionsModel_IN_Tracking       ((uint8_T)2U)
#define ActionsModel_OBSTACLE_DETECTED ((uint16_T)300U)
#define ActionsModel_OFF               ((uint8_T)0U)
#define ActionsModel_ON                ((uint8_T)1U)

/* Named constants for Chart: '<Root>/RoverAction' */
#define Action_IN_BW_FW_EndedSafeAction ((uint8_T)1U)
#define Action_IN_BW_RL_EndedSafeAction ((uint8_T)1U)
#define Action_IN_BW_RR_EndedSafeAction ((uint8_T)1U)
#define ActionsM_MIN_DISTANCE_TO_ROTATE ((uint16_T)30U)
#define ActionsMo_IN_FW_EndedSafeAction ((uint8_T)1U)
#define ActionsMo_IN_RL_EndedSafeAction ((uint8_T)1U)
#define ActionsMo_IN_RR_EndedSafeAction ((uint8_T)1U)
#define ActionsMod_IN_BW_RR_RotateRight ((uint8_T)2U)
#define ActionsMod_IN_FW_BH_RotateRight ((uint8_T)2U)
#define ActionsMod_IN_FW_SR_RotateRight ((uint8_T)8U)
#define ActionsMod_IN_NO_ACTIVE_CHILD_h ((uint8_T)0U)
#define ActionsMode_IN_BW_FW_SafeAction ((uint8_T)2U)
#define ActionsMode_IN_BW_FW_UserAction ((uint8_T)3U)
#define ActionsMode_IN_BW_RL_SafeAction ((uint8_T)2U)
#define ActionsMode_IN_BW_RL_UserAction ((uint8_T)3U)
#define ActionsMode_IN_BW_RR_SafeAction ((uint8_T)2U)
#define ActionsMode_IN_BW_RR_UserAction ((uint8_T)3U)
#define ActionsMode_IN_FW_BH_RotateLeft ((uint8_T)1U)
#define ActionsMode_IN_FW_BrakingHard_e ((uint8_T)4U)
#define ActionsMode_IN_FW_BrakingSmooth ((uint8_T)5U)
#define ActionsMode_IN_FW_SL_RotateLeft ((uint8_T)6U)
#define ActionsMode_IN_FW_SL_StopMotors ((uint8_T)7U)
#define ActionsMode_IN_FW_SR_StopMotors ((uint8_T)9U)
#define ActionsMode_OBSTACLE_DETECTED_d ((uint16_T)300U)
#define ActionsModel_BACKWARD_DEGREE   ((uint16_T)180U)
#define ActionsModel_BRAKE_DISTANCE    ((uint16_T)150U)
#define ActionsModel_CRITICAL_DISTANCE ((uint16_T)70U)
#define ActionsModel_IN_BW_Forward     ((uint8_T)1U)
#define ActionsModel_IN_BW_RotateLeft  ((uint8_T)3U)
#define ActionsModel_IN_BW_StopMotors1 ((uint8_T)4U)
#define ActionsModel_IN_BW_StopMotors2 ((uint8_T)5U)
#define ActionsModel_IN_Backward       ((uint8_T)1U)
#define ActionsModel_IN_BrakingHard    ((uint8_T)2U)
#define ActionsModel_IN_BrakingSmooth  ((uint8_T)3U)
#define ActionsModel_IN_FW_BrakingHard ((uint8_T)3U)
#define ActionsModel_IN_FW_SafeAction  ((uint8_T)2U)
#define ActionsModel_IN_FW_UserAction  ((uint8_T)3U)
#define ActionsModel_IN_Forward        ((uint8_T)4U)
#define ActionsModel_IN_None           ((uint8_T)5U)
#define ActionsModel_IN_RL_RotateLeft  ((uint8_T)1U)
#define ActionsModel_IN_RL_SafeAction  ((uint8_T)2U)
#define ActionsModel_IN_RL_StopMotors  ((uint8_T)2U)
#define ActionsModel_IN_RL_UserAction  ((uint8_T)3U)
#define ActionsModel_IN_RR_RotateRight ((uint8_T)1U)
#define ActionsModel_IN_RR_SafeAction  ((uint8_T)2U)
#define ActionsModel_IN_RR_StopMotors  ((uint8_T)2U)
#define ActionsModel_IN_RR_UserAction  ((uint8_T)3U)
#define ActionsModel_IN_RotateLeft     ((uint8_T)6U)
#define ActionsModel_IN_RotateRight    ((uint8_T)7U)
#define ActionsModel_MAX_SPEED_X       (100.0F)
#define ActionsModel_MAX_SPEED_Y       (140.0F)
#define ActionsModel_NO_SPEED          (10.0F)
#define ActionsModel_SPEED_SWERVE      (40.0F)
#define ActionsModel_SWERVE_DEGREE     ((uint16_T)45U)
#define ActionsModel_SWITCH_BRAKING    ((uint16_T)35U)

MdlrefDW_ActionsModel_T ActionsModel_MdlrefDW;

/* Block signals (default storage) */
B_ActionsModel_c_T ActionsModel_B;

/* Block states (default storage) */
DW_ActionsModel_f_T ActionsModel_DW;

/* Forward declaration for local functions */
static ENUM_SafeAction ActionsM_checkSafetyFromForward(ENUM_TrackingObstacles
  trackingLeft, ENUM_TrackingObstacles trackingRight, uint16_T sonarFront);
static ENUM_SafeAction ActionsMod_checkSafetyToForward(uint16_T sonarFront);
static uint8_T ActionsMod_trackGyroAngleChange(int32_T *accumulatedChange,
  uint16_T previousValue, uint16_T currentValue, uint16_T threshold);
static uint8_T ActionsModel_areAllSpeedsZero(real32_T speed1, real32_T speed2,
  real32_T speed3, real32_T speed4, real32_T zero_velocity);
static void enter_internal_BW_FW_SafeAction(const Gyroscope *rtu_gyroscope,
  BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction);
static void ActionsModel_BW_Forward(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint,
  ENUM_RoverAction *rty_roverAction, ENUM_SafeAction *rty_safeAction,
  BUS_RedLeds *rty_redLeds);
static ENUM_SafeAction ActionsMo_checkSafetyFromRotate(uint16_T obstacleDetected);
static void ActionsModel_BW_RR_RotateRight(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds);
static void ActionsModel_BW_RotateLeft(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds);
static void Ac_enter_internal_FW_SafeAction(const Gyroscope *rtu_gyroscope,
  BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction);
static void ActionsM_enter_internal_Forward(const int16_T *rtu_y_lever, const
  Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds);
static void ActionsModel_Backward(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint,
  ENUM_RoverAction *rty_roverAction, ENUM_SafeAction *rty_safeAction,
  BUS_RedLeds *rty_redLeds);
static void ActionsModel_FW_SafeAction(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds);
static void ActionsModel_Forward(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint,
  ENUM_RoverAction *rty_roverAction, ENUM_SafeAction *rty_safeAction,
  BUS_RedLeds *rty_redLeds);
static void ActionsModel_RotateLeft(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_x_lever, const int16_T
  *rtu_y_lever, const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar,
  BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds);
static void ActionsModel_RotateRight(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_x_lever,
  const int16_T *rtu_y_lever, const Gyroscope *rtu_gyroscope, const BUS_Sonar
  *rtu_sonar, BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction,
  ENUM_SafeAction *rty_safeAction, BUS_RedLeds *rty_redLeds);

/* System initialize for function-call system: '<Root>/MovingObstacles' */
void ActionsMod_MovingObstacles_Init(ENUM_TrackingObstacles
  *rty_statusLeftObstacle, ENUM_TrackingObstacles *rty_statusRightObstacle,
  ENUM_StatusRedLed *rty_leftLed, ENUM_StatusRedLed *rty_rightLed,
  DW_MovingObstacles_ActionsMod_T *localDW)
{
  /* Chart: '<Root>/MovingObstacles' */
  localDW->is_c2_ActionsModel = ActionsModel_IN_NotTracking;
  *rty_statusLeftObstacle = NOT_TRACKING;
  *rty_statusRightObstacle = NOT_TRACKING;
  *rty_leftLed = RED_OFF;
  *rty_rightLed = RED_OFF;
}

/* Output and update for function-call system: '<Root>/MovingObstacles' */
void ActionsModel_MovingObstacles(uint8_T rtu_set, const BUS_Sonar *rtu_sonar,
  ENUM_TrackingObstacles *rty_statusLeftObstacle, ENUM_TrackingObstacles
  *rty_statusRightObstacle, ENUM_StatusRedLed *rty_leftLed, ENUM_StatusRedLed
  *rty_rightLed, DW_MovingObstacles_ActionsMod_T *localDW)
{
  if (localDW->is_c2_ActionsModel == ActionsModel_IN_NotTracking) {
    *rty_statusLeftObstacle = NOT_TRACKING;
    *rty_statusRightObstacle = NOT_TRACKING;
    *rty_leftLed = RED_OFF;
    *rty_rightLed = RED_OFF;
    if (rtu_set == ActionsModel_ON) {
      localDW->is_c2_ActionsModel = ActionsModel_IN_Tracking;
      if ((rtu_sonar->left <= ActionsModel_OBSTACLE_DETECTED) &&
          (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED)) {
        localDW->is_LeftSide = Act_IN_PossibleStartingFromLeft;
        *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
        *rty_leftLed = RED_BLINKING;
      } else if ((rtu_sonar->left <= ActionsModel_OBSTACLE_DETECTED) &&
                 (rtu_sonar->front > ActionsModel_OBSTACLE_DETECTED)) {
        localDW->is_LeftSide = ActionsMode_IN_LeftSideDetected;
        *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
        *rty_leftLed = RED_BLINKING;
      } else {
        localDW->is_LeftSide = ActionsModel_IN_LeftSideClear;
        *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
        *rty_leftLed = RED_OFF;
      }

      if ((rtu_sonar->right <= ActionsModel_OBSTACLE_DETECTED) &&
          (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED)) {
        localDW->is_RightSide = Ac_IN_PossibleStartingFromRight;
        *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
        *rty_rightLed = RED_BLINKING;
      } else if ((rtu_sonar->right <= ActionsModel_OBSTACLE_DETECTED) &&
                 (rtu_sonar->front > ActionsModel_OBSTACLE_DETECTED)) {
        localDW->is_RightSide = ActionsMod_IN_RightSideDetected;
        *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
        *rty_rightLed = RED_BLINKING;
      } else {
        localDW->is_RightSide = ActionsModel_IN_RightSideClear;
        *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
        *rty_rightLed = RED_OFF;
      }
    }

    /* case IN_Tracking: */
  } else if (rtu_set == ActionsModel_OFF) {
    localDW->is_RightSide = ActionsModel_IN_NO_ACTIVE_CHILD;
    localDW->is_LeftSide = ActionsModel_IN_NO_ACTIVE_CHILD;
    localDW->is_c2_ActionsModel = ActionsModel_IN_NotTracking;
    *rty_statusLeftObstacle = NOT_TRACKING;
    *rty_statusRightObstacle = NOT_TRACKING;
    *rty_leftLed = RED_OFF;
    *rty_rightLed = RED_OFF;
  } else {
    switch (localDW->is_LeftSide) {
     case ActionsModel_IN_LeftSideClear:
      *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
      *rty_leftLed = RED_OFF;
      if (rtu_sonar->left <= ActionsModel_OBSTACLE_DETECTED) {
        if (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED) {
          localDW->is_LeftSide = Act_IN_PossibleStartingFromLeft;
          *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
          *rty_leftLed = RED_BLINKING;
        } else {
          /* [sonar.front > OBSTACLE_DETECTED] */
          localDW->is_LeftSide = ActionsMode_IN_LeftSideDetected;
          *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
          *rty_leftLed = RED_BLINKING;
        }
      }
      break;

     case ActionsMode_IN_LeftSideDetected:
      *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
      *rty_leftLed = RED_BLINKING;
      if (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED) {
        if (rtu_sonar->left > ActionsModel_OBSTACLE_DETECTED) {
          localDW->is_LeftSide = ActionsModel_IN_MovedFromLeft;
          *rty_statusLeftObstacle = OBSTACLE_MOVING;
          *rty_leftLed = RED_OFF;

          /*  Lo stato è bloccante in quanto Model Action provvederà a resettarlo */
        } else {
          /*  [sonar.left <= OBSTACLE_DETECTED] */
          localDW->is_LeftSide = Act_IN_PossibleStartingFromLeft;
          *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
          *rty_leftLed = RED_BLINKING;
        }
      } else if (rtu_sonar->left > ActionsModel_OBSTACLE_DETECTED) {
        localDW->is_LeftSide = ActionsModel_IN_LeftSideClear;
        *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
        *rty_leftLed = RED_OFF;
      }
      break;

     case ActionsModel_IN_MovedFromLeft:
      *rty_statusLeftObstacle = OBSTACLE_MOVING;
      *rty_leftLed = RED_OFF;
      break;

     default:
      /* case IN_PossibleStartingFromLeft: */
      *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
      *rty_leftLed = RED_BLINKING;
      if ((rtu_sonar->left > ActionsModel_OBSTACLE_DETECTED) &&
          (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED)) {
        localDW->is_LeftSide = ActionsModel_IN_MovedFromLeft;
        *rty_statusLeftObstacle = OBSTACLE_MOVING;
        *rty_leftLed = RED_OFF;

        /*  Lo stato è bloccante in quanto Model Action provvederà a resettarlo */
      } else if (rtu_sonar->front > ActionsModel_OBSTACLE_DETECTED) {
        if (rtu_sonar->left <= ActionsModel_OBSTACLE_DETECTED) {
          localDW->is_LeftSide = ActionsMode_IN_LeftSideDetected;
          *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
          *rty_leftLed = RED_BLINKING;
        } else {
          localDW->is_LeftSide = ActionsModel_IN_LeftSideClear;
          *rty_statusLeftObstacle = NO_OBSTACLE_MOVING;
          *rty_leftLed = RED_OFF;
        }
      }
      break;
    }

    switch (localDW->is_RightSide) {
     case ActionsModel_IN_MovedFromRight:
      *rty_statusRightObstacle = OBSTACLE_MOVING;
      *rty_rightLed = RED_OFF;
      break;

     case Ac_IN_PossibleStartingFromRight:
      *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
      *rty_rightLed = RED_BLINKING;
      if ((rtu_sonar->right > ActionsModel_OBSTACLE_DETECTED) &&
          (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED)) {
        localDW->is_RightSide = ActionsModel_IN_MovedFromRight;
        *rty_statusRightObstacle = OBSTACLE_MOVING;
        *rty_rightLed = RED_OFF;

        /*  Lo stato è bloccante in quanto Model Action provvederà a resettarlo */
      } else if (rtu_sonar->front > ActionsModel_OBSTACLE_DETECTED) {
        if (rtu_sonar->right <= ActionsModel_OBSTACLE_DETECTED) {
          localDW->is_RightSide = ActionsMod_IN_RightSideDetected;
          *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
          *rty_rightLed = RED_BLINKING;
        } else {
          localDW->is_RightSide = ActionsModel_IN_RightSideClear;
          *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
          *rty_rightLed = RED_OFF;
        }
      }
      break;

     case ActionsModel_IN_RightSideClear:
      *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
      *rty_rightLed = RED_OFF;
      if (rtu_sonar->right <= ActionsModel_OBSTACLE_DETECTED) {
        if (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED) {
          localDW->is_RightSide = Ac_IN_PossibleStartingFromRight;
          *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
          *rty_rightLed = RED_BLINKING;
        } else {
          /* [sonar.front > OBSTACLE_DETECTED] */
          localDW->is_RightSide = ActionsMod_IN_RightSideDetected;
          *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
          *rty_rightLed = RED_BLINKING;
        }
      }
      break;

     default:
      /* case IN_RightSideDetected: */
      *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
      *rty_rightLed = RED_BLINKING;
      if (rtu_sonar->front <= ActionsModel_OBSTACLE_DETECTED) {
        if (rtu_sonar->right > ActionsModel_OBSTACLE_DETECTED) {
          localDW->is_RightSide = ActionsModel_IN_MovedFromRight;
          *rty_statusRightObstacle = OBSTACLE_MOVING;
          *rty_rightLed = RED_OFF;

          /*  Lo stato è bloccante in quanto Model Action provvederà a resettarlo */
        } else {
          /*  [sonar.right <= OBSTACLE_DETECTED] */
          localDW->is_RightSide = Ac_IN_PossibleStartingFromRight;
          *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
          *rty_rightLed = RED_BLINKING;
        }
      } else if (rtu_sonar->right > ActionsModel_OBSTACLE_DETECTED) {
        localDW->is_RightSide = ActionsModel_IN_RightSideClear;
        *rty_statusRightObstacle = NO_OBSTACLE_MOVING;
        *rty_rightLed = RED_OFF;
      }
      break;
    }
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static ENUM_SafeAction ActionsM_checkSafetyFromForward(ENUM_TrackingObstacles
  trackingLeft, ENUM_TrackingObstacles trackingRight, uint16_T sonarFront)
{
  ENUM_SafeAction emergencyAction;
  emergencyAction = SA_NONE;
  if (sonarFront < ActionsMode_OBSTACLE_DETECTED_d) {
    if (sonarFront <= ActionsModel_CRITICAL_DISTANCE) {
      emergencyAction = SA_BRAKING_HARD;
    } else if (sonarFront <= ActionsModel_BRAKE_DISTANCE) {
      if (trackingRight == OBSTACLE_MOVING) {
        if (trackingLeft == OBSTACLE_MOVING) {
          emergencyAction = SA_BRAKING_SMOOTH;
        } else {
          emergencyAction = SA_SWERVE_RIGHT;
        }
      } else if (trackingLeft == OBSTACLE_MOVING) {
        emergencyAction = SA_SWERVE_LEFT;
      } else {
        emergencyAction = SA_BRAKING_SMOOTH;
      }
    }
  }

  return emergencyAction;
}

/* Function for Chart: '<Root>/RoverAction' */
static ENUM_SafeAction ActionsMod_checkSafetyToForward(uint16_T sonarFront)
{
  ENUM_SafeAction emergencyAction;
  emergencyAction = SA_BRAKING_HARD;
  if (sonarFront > ActionsModel_BRAKE_DISTANCE) {
    emergencyAction = SA_NONE;
  }

  return emergencyAction;
}

/* Function for Chart: '<Root>/RoverAction' */
static uint8_T ActionsMod_trackGyroAngleChange(int32_T *accumulatedChange,
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

/* Function for Chart: '<Root>/RoverAction' */
static uint8_T ActionsModel_areAllSpeedsZero(real32_T speed1, real32_T speed2,
  real32_T speed3, real32_T speed4, real32_T zero_velocity)
{
  return (uint8_T)((fabsf(speed1) <= zero_velocity) && ((fabsf(speed2) <=
    zero_velocity) && ((fabsf(speed3) <= zero_velocity) && (fabsf(speed4) <=
    zero_velocity))));
}

/* Function for Chart: '<Root>/RoverAction' */
static void enter_internal_BW_FW_SafeAction(const Gyroscope *rtu_gyroscope,
  BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction)
{
  switch (*rty_safeAction) {
   case SA_BRAKING_HARD:
    ActionsModel_DW.is_BW_FW_SafeAction = ActionsModel_IN_FW_BrakingHard;
    *rty_roverAction = RA_BRAKING_HARD;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;

   case SA_BRAKING_SMOOTH:
    ActionsModel_DW.is_BW_FW_SafeAction = ActionsMode_IN_FW_BrakingSmooth;
    *rty_roverAction = RA_BRAKING_SMOOTH;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;

   case SA_SWERVE_RIGHT:
    ActionsModel_DW.accumulated_change = 0;
    ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    ActionsModel_DW.is_BW_FW_SafeAction = ActionsMode_IN_FW_SR_StopMotors;
    *rty_roverAction = RA_BRAKING_HARD;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;

   default:
    /* [safeAction == ENUM_SafeAction.SA_SWERVE_LEFT] */
    ActionsModel_DW.accumulated_change = 0;
    ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    ActionsModel_DW.is_BW_FW_SafeAction = ActionsMode_IN_FW_SL_StopMotors;
    *rty_roverAction = RA_BRAKING_HARD;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_BW_Forward(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint,
  ENUM_RoverAction *rty_roverAction, ENUM_SafeAction *rty_safeAction,
  BUS_RedLeds *rty_redLeds)
{
  uint8_T rotation_ended;
  switch (ActionsModel_DW.is_BW_Forward) {
   case Action_IN_BW_FW_EndedSafeAction:
    *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_BW_Forward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_BW_Forward = 2U;
    } else if (*rty_safeAction == SA_NONE) {
      /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
      ActionsModel_DW.is_BW_Forward = ActionsMode_IN_BW_FW_UserAction;

      /*  Start tracking */
      ActionsModel_B.set = 1U;

      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      ActionsModel_MovingObstacles(1, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);

      /*  Action */
      *rty_roverAction = RA_FORWARD;

      /*  Set point */
      rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
        ActionsModel_MAX_SPEED_Y;
      rty_setPoint->leftAxis = rty_setPoint->rightAxis;

      /*  Led */
      rty_redLeds->left = ActionsModel_B.leftLed;
      rty_redLeds->right = ActionsModel_B.rightLed;
    }
    break;

   case ActionsMode_IN_BW_FW_SafeAction:
    switch (ActionsModel_DW.is_BW_FW_SafeAction) {
     case ActionsMode_IN_FW_BH_RotateLeft:
      rotation_ended = ActionsMod_trackGyroAngleChange
        (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
         *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
      if (rotation_ended == 1) {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      } else {
        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      }
      break;

     case ActionsMod_IN_FW_BH_RotateRight:
      rotation_ended = ActionsMod_trackGyroAngleChange
        (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
         *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
      if (rotation_ended == 1) {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      } else {
        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      }
      break;

     case ActionsModel_IN_FW_BrakingHard:
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        if (rtu_sonar->left > ActionsModel_BRAKE_DISTANCE) {
          ActionsModel_DW.accumulated_change = 0;
          ActionsModel_DW.is_BW_FW_SafeAction = ActionsMode_IN_FW_BH_RotateLeft;
          *rty_roverAction = RA_ROTATE_LEFT;

          /*  Set point */
          rty_setPoint->rightAxis = ActionsModel_SPEED_SWERVE;
          rty_setPoint->leftAxis = -40.0F;

          /*  Degree */
          ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
        } else if (rtu_sonar->right > ActionsModel_BRAKE_DISTANCE) {
          ActionsModel_DW.accumulated_change = 0;
          ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_FW_BH_RotateRight;
          *rty_roverAction = RA_ROTATE_RIGHT;

          /*  Set point */
          rty_setPoint->rightAxis = -40.0F;
          rty_setPoint->leftAxis = ActionsModel_SPEED_SWERVE;

          /*  Degree */
          ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
        } else {
          *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
          ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
          ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
        }
      }
      break;

     case ActionsMode_IN_FW_BrakingHard_e:
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      }
      break;

     case ActionsMode_IN_FW_BrakingSmooth:
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      } else if (rtu_sonar->front < ActionsModel_SWITCH_BRAKING) {
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMode_IN_FW_BrakingHard_e;
        *rty_roverAction = RA_BRAKING_HARD;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      }
      break;

     case ActionsMode_IN_FW_SL_RotateLeft:
      rotation_ended = ActionsMod_trackGyroAngleChange
        (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
         *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
      if (rotation_ended == 1) {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      } else {
        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      }
      break;

     case ActionsMode_IN_FW_SL_StopMotors:
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMode_IN_FW_SL_RotateLeft;
        *rty_roverAction = RA_ROTATE_LEFT;

        /*  Set point */
        rty_setPoint->rightAxis = ActionsModel_SPEED_SWERVE;
        rty_setPoint->leftAxis = -40.0F;

        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      }
      break;

     case ActionsMod_IN_FW_SR_RotateRight:
      rotation_ended = ActionsMod_trackGyroAngleChange
        (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
         *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
      if (rotation_ended == 1) {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 2U;
      } else {
        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      }
      break;

     default:
      /* case IN_FW_SR_StopMotors: */
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        ActionsModel_DW.is_BW_FW_SafeAction = ActionsMod_IN_FW_SR_RotateRight;
        *rty_roverAction = RA_ROTATE_RIGHT;

        /*  Set point */
        rty_setPoint->rightAxis = -40.0F;
        rty_setPoint->leftAxis = ActionsModel_SPEED_SWERVE;

        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      }
      break;
    }

    if (ActionsModel_DW.exit_port_index_BW_FW_SafeActio == 2U) {
      ActionsModel_DW.exit_port_index_BW_FW_SafeActio = 0U;
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsModel_DW.is_BW_Forward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_Forward = 2U;
      } else if (*rty_safeAction == SA_NONE) {
        /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
        ActionsModel_DW.is_BW_Forward = ActionsMode_IN_BW_FW_UserAction;

        /*  Start tracking */
        ActionsModel_B.set = 1U;

        /* Chart: '<Root>/MovingObstacles' */
        /* Chart: '<Root>/MovingObstacles' */
        ActionsModel_MovingObstacles(1, rtu_sonar,
          &ActionsModel_B.statusLeftObstacle,
          &ActionsModel_B.statusRightObstacle, &ActionsModel_B.leftLed,
          &ActionsModel_B.rightLed, &ActionsModel_DW.sf_MovingObstacles);

        /*  Action */
        *rty_roverAction = RA_FORWARD;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;

        /*  Led */
        rty_redLeds->left = ActionsModel_B.leftLed;
        rty_redLeds->right = ActionsModel_B.rightLed;
      } else {
        ActionsModel_DW.is_BW_Forward = Action_IN_BW_FW_EndedSafeAction;
        *rty_roverAction = RA_IDLE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      }
    }
    break;

   default:
    /* case IN_BW_FW_UserAction: */
    if (*rtu_currentUserAction != UA_BACKWARD) {
      /*  Stop tracking */
      ActionsModel_B.set = 0U;

      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      ActionsModel_MovingObstacles(0, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);
      ActionsModel_DW.is_BW_Forward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_BW_Forward = 2U;
    } else {
      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      /*  Keep tracking */
      ActionsModel_MovingObstacles(ActionsModel_B.set, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);

      /*  Check Safety */
      *rty_safeAction = ActionsM_checkSafetyFromForward
        (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
         rtu_sonar->front);
      if (*rty_safeAction != SA_NONE) {
        /*  Stop tracking */
        ActionsModel_B.set = 0U;

        /* Chart: '<Root>/MovingObstacles' */
        /* Chart: '<Root>/MovingObstacles' */
        ActionsModel_MovingObstacles(0, rtu_sonar,
          &ActionsModel_B.statusLeftObstacle,
          &ActionsModel_B.statusRightObstacle, &ActionsModel_B.leftLed,
          &ActionsModel_B.rightLed, &ActionsModel_DW.sf_MovingObstacles);
        ActionsModel_DW.is_BW_Forward = ActionsMode_IN_BW_FW_SafeAction;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        enter_internal_BW_FW_SafeAction(rtu_gyroscope, rty_setPoint,
          rty_roverAction, rty_safeAction);
      } else {
        /*  Action */
        *rty_roverAction = RA_FORWARD;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;

        /*  Led */
        rty_redLeds->left = ActionsModel_B.leftLed;
        rty_redLeds->right = ActionsModel_B.rightLed;
      }
    }
    break;
  }

  if (ActionsModel_DW.exit_port_index_BW_Forward == 2U) {
    ActionsModel_DW.exit_port_index_BW_Forward = 0U;
    ActionsModel_DW.is_Backward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
    ActionsModel_DW.exit_port_index_Backward = 2U;
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static ENUM_SafeAction ActionsMo_checkSafetyFromRotate(uint16_T obstacleDetected)
{
  ENUM_SafeAction emergencyAction;
  emergencyAction = SA_NONE;
  if (obstacleDetected <= ActionsM_MIN_DISTANCE_TO_ROTATE) {
    emergencyAction = SA_BRAKING_HARD;
  }

  return emergencyAction;
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_BW_RR_RotateRight(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds)
{
  uint8_T rotation_ended;
  *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->right);
  switch (ActionsModel_DW.is_BW_RR_RotateRight) {
   case Action_IN_BW_RR_EndedSafeAction:
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_BW_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_BW_RR_RotateRig = 2U;
    } else if (*rty_safeAction == SA_NONE) {
      /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
      ActionsModel_DW.is_BW_RR_RotateRight = ActionsMode_IN_BW_RR_UserAction;

      /*  Degrees */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

      /*  Action */
      *rty_roverAction = RA_ROTATE_RIGHT;

      /*  Set point */
      rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
        ActionsModel_MAX_SPEED_X;
      rty_setPoint->leftAxis = -rty_setPoint->rightAxis;

      /*  Led */
      rty_redLeds->left = RED_BLINKING;
      rty_redLeds->right = RED_BLINKING;
    }
    break;

   case ActionsMode_IN_BW_RR_SafeAction:
    /*     */
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      ActionsModel_DW.exit_port_index_BW_RR_SafeActio = 2U;
    }

    if (ActionsModel_DW.exit_port_index_BW_RR_SafeActio == 2U) {
      ActionsModel_DW.exit_port_index_BW_RR_SafeActio = 0U;
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsModel_DW.is_BW_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_RR_RotateRig = 2U;
      } else if (*rty_safeAction == SA_NONE) {
        /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
        ActionsModel_DW.is_BW_RR_RotateRight = ActionsMode_IN_BW_RR_UserAction;

        /*  Degrees */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Action */
        *rty_roverAction = RA_ROTATE_RIGHT;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->leftAxis = -rty_setPoint->rightAxis;

        /*  Led */
        rty_redLeds->left = RED_BLINKING;
        rty_redLeds->right = RED_BLINKING;
      } else {
        ActionsModel_DW.is_BW_RR_RotateRight = Action_IN_BW_RR_EndedSafeAction;
        *rty_roverAction = RA_IDLE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      }
    }
    break;

   default:
    /* case IN_BW_RR_UserAction: */
    if (*rty_safeAction != SA_NONE) {
      ActionsModel_DW.is_BW_RR_RotateRight = ActionsMode_IN_BW_RR_SafeAction;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      *rty_roverAction = RA_BRAKING_HARD;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_BW_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_BW_RR_RotateRig = 2U;
    } else {
      rotation_ended = ActionsMod_trackGyroAngleChange
        (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
         *rtu_gyroscope, ActionsModel_BACKWARD_DEGREE);
      if (rotation_ended == 1) {
        ActionsModel_DW.is_BW_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_RR_RotateRig = 3U;
      } else {
        /*  Degrees */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Action */
        *rty_roverAction = RA_ROTATE_RIGHT;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->leftAxis = -rty_setPoint->rightAxis;
      }
    }
    break;
  }

  switch (ActionsModel_DW.exit_port_index_BW_RR_RotateRig) {
   case 2:
    ActionsModel_DW.exit_port_index_BW_RR_RotateRig = 0U;
    ActionsModel_DW.is_Backward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
    ActionsModel_DW.exit_port_index_Backward = 2U;
    break;

   case 3:
    ActionsModel_DW.exit_port_index_BW_RR_RotateRig = 0U;
    ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors2;

    /*  Actions */
    *rty_roverAction = RA_BRAKING_HARD;
    *rty_safeAction = SA_NONE;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;

    /*  Led */
    rty_redLeds->left = RED_OFF;
    rty_redLeds->right = RED_OFF;
    break;
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_BW_RotateLeft(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds)
{
  uint8_T rotation_ended;
  *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->left);
  switch (ActionsModel_DW.is_BW_RotateLeft) {
   case Action_IN_BW_RL_EndedSafeAction:
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_BW_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_BW_RotateLeft = 2U;
    } else if (*rty_safeAction == SA_NONE) {
      /* l'utente vorrebbe ruotare a SX e non c'è più l'ostacolo */
      ActionsModel_DW.is_BW_RotateLeft = ActionsMode_IN_BW_RL_UserAction;

      /*  Degrees */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

      /*  Action */
      *rty_roverAction = RA_ROTATE_LEFT;

      /*  Set point */
      rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
        ActionsModel_MAX_SPEED_X;
      rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

      /*  Led */
      rty_redLeds->left = RED_BLINKING;
      rty_redLeds->right = RED_BLINKING;
    }
    break;

   case ActionsMode_IN_BW_RL_SafeAction:
    /*     */
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      ActionsModel_DW.exit_port_index_BW_RL_SafeActio = 2U;
    }

    if (ActionsModel_DW.exit_port_index_BW_RL_SafeActio == 2U) {
      ActionsModel_DW.exit_port_index_BW_RL_SafeActio = 0U;
      if (*rtu_currentUserAction != UA_BACKWARD) {
        ActionsModel_DW.is_BW_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_RotateLeft = 2U;
      } else if (*rty_safeAction == SA_NONE) {
        /* l'utente vorrebbe ruotare a SX e non c'è più l'ostacolo */
        ActionsModel_DW.is_BW_RotateLeft = ActionsMode_IN_BW_RL_UserAction;

        /*  Degrees */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Action */
        *rty_roverAction = RA_ROTATE_LEFT;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

        /*  Led */
        rty_redLeds->left = RED_BLINKING;
        rty_redLeds->right = RED_BLINKING;
      } else {
        ActionsModel_DW.is_BW_RotateLeft = Action_IN_BW_RL_EndedSafeAction;
        *rty_roverAction = RA_IDLE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      }
    }
    break;

   default:
    /* case IN_BW_RL_UserAction: */
    if (*rty_safeAction != SA_NONE) {
      ActionsModel_DW.is_BW_RotateLeft = ActionsMode_IN_BW_RL_SafeAction;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      *rty_roverAction = RA_BRAKING_HARD;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_BW_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_BW_RotateLeft = 2U;
    } else {
      rotation_ended = ActionsMod_trackGyroAngleChange
        (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
         *rtu_gyroscope, ActionsModel_BACKWARD_DEGREE);
      if (rotation_ended == 1) {
        ActionsModel_DW.is_BW_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_BW_RotateLeft = 3U;
      } else {
        /*  Degrees */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

        /*  Action */
        *rty_roverAction = RA_ROTATE_LEFT;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      }
    }
    break;
  }

  switch (ActionsModel_DW.exit_port_index_BW_RotateLeft) {
   case 2:
    ActionsModel_DW.exit_port_index_BW_RotateLeft = 0U;
    ActionsModel_DW.is_Backward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
    ActionsModel_DW.exit_port_index_Backward = 2U;
    break;

   case 3:
    ActionsModel_DW.exit_port_index_BW_RotateLeft = 0U;
    ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors2;

    /*  Actions */
    *rty_roverAction = RA_BRAKING_HARD;
    *rty_safeAction = SA_NONE;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;

    /*  Led */
    rty_redLeds->left = RED_OFF;
    rty_redLeds->right = RED_OFF;
    break;
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void Ac_enter_internal_FW_SafeAction(const Gyroscope *rtu_gyroscope,
  BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction)
{
  switch (*rty_safeAction) {
   case SA_BRAKING_HARD:
    ActionsModel_DW.is_FW_SafeAction = ActionsModel_IN_FW_BrakingHard;
    *rty_roverAction = RA_BRAKING_HARD;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;

   case SA_BRAKING_SMOOTH:
    ActionsModel_DW.is_FW_SafeAction = ActionsMode_IN_FW_BrakingSmooth;
    *rty_roverAction = RA_BRAKING_SMOOTH;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;

   case SA_SWERVE_RIGHT:
    ActionsModel_DW.accumulated_change = 0;
    ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    ActionsModel_DW.is_FW_SafeAction = ActionsMode_IN_FW_SR_StopMotors;
    *rty_roverAction = RA_BRAKING_HARD;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;

   default:
    /* [safeAction == ENUM_SafeAction.SA_SWERVE_LEFT] */
    ActionsModel_DW.accumulated_change = 0;
    ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    ActionsModel_DW.is_FW_SafeAction = ActionsMode_IN_FW_SL_StopMotors;
    *rty_roverAction = RA_BRAKING_HARD;

    /*  Set point */
    rty_setPoint->rightAxis = 0.0F;
    rty_setPoint->leftAxis = 0.0F;
    break;
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsM_enter_internal_Forward(const int16_T *rtu_y_lever, const
  Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds)
{
  if (*rty_safeAction != SA_NONE) {
    ActionsModel_DW.is_Forward = ActionsModel_IN_FW_SafeAction;

    /*  Led */
    rty_redLeds->left = RED_ON;
    rty_redLeds->right = RED_ON;
    Ac_enter_internal_FW_SafeAction(rtu_gyroscope, rty_setPoint, rty_roverAction,
      rty_safeAction);
  } else {
    /*  [safeAction == ENUM_SafeAction.SA_NONE] */
    ActionsModel_DW.is_Forward = ActionsModel_IN_FW_UserAction;

    /*  Start tracking */
    ActionsModel_B.set = 1U;

    /* Chart: '<Root>/MovingObstacles' */
    /* Chart: '<Root>/MovingObstacles' */
    ActionsModel_MovingObstacles(1, rtu_sonar,
      &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
      &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
      &ActionsModel_DW.sf_MovingObstacles);

    /*  Action */
    *rty_roverAction = RA_FORWARD;

    /*  Set point */
    rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
      ActionsModel_MAX_SPEED_Y;
    rty_setPoint->leftAxis = rty_setPoint->rightAxis;

    /*  Led */
    rty_redLeds->left = ActionsModel_B.leftLed;
    rty_redLeds->right = ActionsModel_B.rightLed;
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_Backward(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint,
  ENUM_RoverAction *rty_roverAction, ENUM_SafeAction *rty_safeAction,
  BUS_RedLeds *rty_redLeds)
{
  switch (ActionsModel_DW.is_Backward) {
   case ActionsModel_IN_BW_Forward:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    ActionsModel_BW_Forward(rtu_currentUserAction, rtu_speed, rtu_y_lever,
      rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction, rty_safeAction,
      rty_redLeds);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   case ActionsMod_IN_BW_RR_RotateRight:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    ActionsModel_BW_RR_RotateRight(rtu_currentUserAction, rtu_speed, rtu_y_lever,
      rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction, rty_safeAction,
      rty_redLeds);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   case ActionsModel_IN_BW_RotateLeft:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    ActionsModel_BW_RotateLeft(rtu_currentUserAction, rtu_speed, rtu_y_lever,
      rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction, rty_safeAction,
      rty_redLeds);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   case ActionsModel_IN_BW_StopMotors1:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_Backward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_Backward = 2U;

      /*     */
    } else if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1,
                rtu_speed->motor2, rtu_speed->motor3, rtu_speed->motor4,
                ActionsModel_NO_SPEED) != 0) {
      if (rtu_sonar->left > ActionsM_MIN_DISTANCE_TO_ROTATE) {
        ActionsModel_DW.is_Backward = ActionsModel_IN_BW_RotateLeft;
        *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->left);

        /*  I valori per la rotazione vanno resettati nel Superstate
           Se interrompessi la user action per eseguire la safe action, al mio ritorno non devo perdere gli accumulated change del delta  */
        ActionsModel_DW.accumulated_change = 0;
        if (*rty_safeAction != SA_NONE) {
          ActionsModel_DW.is_BW_RotateLeft = ActionsMode_IN_BW_RL_SafeAction;

          /*  Led */
          rty_redLeds->left = RED_ON;
          rty_redLeds->right = RED_ON;
          *rty_roverAction = RA_BRAKING_HARD;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /* [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsModel_DW.is_BW_RotateLeft = ActionsMode_IN_BW_RL_UserAction;

          /*  Degrees */
          ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

          /*  Action */
          *rty_roverAction = RA_ROTATE_LEFT;

          /*  Set point */
          rty_setPoint->leftAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsModel_MAX_SPEED_X;
          rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

          /*  Led */
          rty_redLeds->left = RED_BLINKING;
          rty_redLeds->right = RED_BLINKING;
        }
      } else if (rtu_sonar->right > ActionsM_MIN_DISTANCE_TO_ROTATE) {
        ActionsModel_DW.is_Backward = ActionsMod_IN_BW_RR_RotateRight;
        *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->right);

        /*  I valori per la rotazione vanno resettati nel Superstate
           Se interrompessi la user action per eseguire la safe action, al mio ritorno non devo perdere gli accumulated change del delta  */
        ActionsModel_DW.accumulated_change = 0;
        if (*rty_safeAction != SA_NONE) {
          ActionsModel_DW.is_BW_RR_RotateRight = ActionsMode_IN_BW_RR_SafeAction;

          /*  Led */
          rty_redLeds->left = RED_ON;
          rty_redLeds->right = RED_ON;
          *rty_roverAction = RA_BRAKING_HARD;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        } else {
          /* [safeAction == ENUM_SafeAction.SA_NONE] */
          ActionsModel_DW.is_BW_RR_RotateRight = ActionsMode_IN_BW_RR_UserAction;

          /*  Degrees */
          ActionsModel_DW.previousGyroscope = *rtu_gyroscope;

          /*  Action */
          *rty_roverAction = RA_ROTATE_RIGHT;

          /*  Set point */
          rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
            ActionsModel_MAX_SPEED_X;
          rty_setPoint->leftAxis = -rty_setPoint->rightAxis;

          /*  Led */
          rty_redLeds->left = RED_BLINKING;
          rty_redLeds->right = RED_BLINKING;
        }
      }
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   default:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    /* case IN_BW_StopMotors2: */
    if (*rtu_currentUserAction != UA_BACKWARD) {
      ActionsModel_DW.is_Backward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_Backward = 2U;

      /*      */
    } else if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1,
                rtu_speed->motor2, rtu_speed->motor3, rtu_speed->motor4,
                ActionsModel_NO_SPEED) != 0) {
      ActionsModel_DW.is_Backward = ActionsModel_IN_BW_Forward;
      *rty_safeAction = ActionsM_checkSafetyFromForward
        (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
         rtu_sonar->front);
      if (*rty_safeAction != SA_NONE) {
        ActionsModel_DW.is_BW_Forward = ActionsMode_IN_BW_FW_SafeAction;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        enter_internal_BW_FW_SafeAction(rtu_gyroscope, rty_setPoint,
          rty_roverAction, rty_safeAction);
      } else {
        /*  [safeAction == ENUM_SafeAction.SA_NONE] */
        ActionsModel_DW.is_BW_Forward = ActionsMode_IN_BW_FW_UserAction;

        /*  Start tracking */
        ActionsModel_B.set = 1U;

        /* Chart: '<Root>/MovingObstacles' */
        /* Chart: '<Root>/MovingObstacles' */
        ActionsModel_MovingObstacles(1, rtu_sonar,
          &ActionsModel_B.statusLeftObstacle,
          &ActionsModel_B.statusRightObstacle, &ActionsModel_B.leftLed,
          &ActionsModel_B.rightLed, &ActionsModel_DW.sf_MovingObstacles);

        /*  Action */
        *rty_roverAction = RA_FORWARD;

        /*  Set point */
        rty_setPoint->rightAxis = (real32_T)-*rtu_y_lever / 512.0F *
          ActionsModel_MAX_SPEED_Y;
        rty_setPoint->leftAxis = rty_setPoint->rightAxis;

        /*  Led */
        rty_redLeds->left = ActionsModel_B.leftLed;
        rty_redLeds->right = ActionsModel_B.rightLed;
      }
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;
  }

  if (ActionsModel_DW.exit_port_index_Backward == 2U) {
    ActionsModel_DW.exit_port_index_Backward = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
      ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_RIGHT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
      ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_LEFT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
      ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_FORWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
      *rty_safeAction = ActionsM_checkSafetyFromForward
        (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
         rtu_sonar->front);
      ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
        rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
      break;

     case UA_BRAKING_SMOOTH:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingSmooth;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_SMOOTH;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     case UA_BRAKING_HARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_HARD;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_FW_SafeAction(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever,
  const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint
  *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds)
{
  uint8_T rotation_ended;
  switch (ActionsModel_DW.is_FW_SafeAction) {
   case ActionsMode_IN_FW_BH_RotateLeft:
    rotation_ended = ActionsMod_trackGyroAngleChange
      (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
       *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
    if (rotation_ended == 1) {
      *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
    } else {
      /*  Degree */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    }
    break;

   case ActionsMod_IN_FW_BH_RotateRight:
    rotation_ended = ActionsMod_trackGyroAngleChange
      (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
       *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
    if (rotation_ended == 1) {
      *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
    } else {
      /*  Degree */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    }
    break;

   case ActionsModel_IN_FW_BrakingHard:
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      if (rtu_sonar->left > ActionsModel_BRAKE_DISTANCE) {
        ActionsModel_DW.accumulated_change = 0;
        ActionsModel_DW.is_FW_SafeAction = ActionsMode_IN_FW_BH_RotateLeft;
        *rty_roverAction = RA_ROTATE_LEFT;

        /*  Set point */
        rty_setPoint->rightAxis = ActionsModel_SPEED_SWERVE;
        rty_setPoint->leftAxis = -40.0F;

        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      } else if (rtu_sonar->right > ActionsModel_BRAKE_DISTANCE) {
        ActionsModel_DW.accumulated_change = 0;
        ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_FW_BH_RotateRight;
        *rty_roverAction = RA_ROTATE_RIGHT;

        /*  Set point */
        rty_setPoint->rightAxis = -40.0F;
        rty_setPoint->leftAxis = ActionsModel_SPEED_SWERVE;

        /*  Degree */
        ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
      } else {
        *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
        ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
      }
    }
    break;

   case ActionsMode_IN_FW_BrakingHard_e:
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
    }
    break;

   case ActionsMode_IN_FW_BrakingSmooth:
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
    } else if (rtu_sonar->front < ActionsModel_SWITCH_BRAKING) {
      ActionsModel_DW.is_FW_SafeAction = ActionsMode_IN_FW_BrakingHard_e;
      *rty_roverAction = RA_BRAKING_HARD;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    }
    break;

   case ActionsMode_IN_FW_SL_RotateLeft:
    rotation_ended = ActionsMod_trackGyroAngleChange
      (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
       *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
    if (rotation_ended == 1) {
      *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
    } else {
      /*  Degree */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    }
    break;

   case ActionsMode_IN_FW_SL_StopMotors:
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      ActionsModel_DW.is_FW_SafeAction = ActionsMode_IN_FW_SL_RotateLeft;
      *rty_roverAction = RA_ROTATE_LEFT;

      /*  Set point */
      rty_setPoint->rightAxis = ActionsModel_SPEED_SWERVE;
      rty_setPoint->leftAxis = -40.0F;

      /*  Degree */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    }
    break;

   case ActionsMod_IN_FW_SR_RotateRight:
    rotation_ended = ActionsMod_trackGyroAngleChange
      (&ActionsModel_DW.accumulated_change, ActionsModel_DW.previousGyroscope,
       *rtu_gyroscope, ActionsModel_SWERVE_DEGREE);
    if (rotation_ended == 1) {
      *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_FW_SafeAction = 2U;
    } else {
      /*  Degree */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    }
    break;

   default:
    /* case IN_FW_SR_StopMotors: */
    if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
         rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
      ActionsModel_DW.is_FW_SafeAction = ActionsMod_IN_FW_SR_RotateRight;
      *rty_roverAction = RA_ROTATE_RIGHT;

      /*  Set point */
      rty_setPoint->rightAxis = -40.0F;
      rty_setPoint->leftAxis = ActionsModel_SPEED_SWERVE;

      /*  Degree */
      ActionsModel_DW.previousGyroscope = *rtu_gyroscope;
    }
    break;
  }

  if (ActionsModel_DW.exit_port_index_FW_SafeAction == 2U) {
    ActionsModel_DW.exit_port_index_FW_SafeAction = 0U;
    if (*rtu_currentUserAction != UA_FORWARD) {
      ActionsModel_DW.is_Forward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_Forward = 2U;
    } else if (*rty_safeAction == SA_NONE) {
      /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
      ActionsModel_DW.is_Forward = ActionsModel_IN_FW_UserAction;

      /*  Start tracking */
      ActionsModel_B.set = 1U;

      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      ActionsModel_MovingObstacles(1, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);

      /*  Action */
      *rty_roverAction = RA_FORWARD;

      /*  Set point */
      rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
        ActionsModel_MAX_SPEED_Y;
      rty_setPoint->leftAxis = rty_setPoint->rightAxis;

      /*  Led */
      rty_redLeds->left = ActionsModel_B.leftLed;
      rty_redLeds->right = ActionsModel_B.rightLed;
    } else {
      ActionsModel_DW.is_Forward = ActionsMo_IN_FW_EndedSafeAction;
      *rty_roverAction = RA_IDLE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    }
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_Forward(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_y_lever, const Gyroscope
  *rtu_gyroscope, const BUS_Sonar *rtu_sonar, BUS_SetPoint *rty_setPoint,
  ENUM_RoverAction *rty_roverAction, ENUM_SafeAction *rty_safeAction,
  BUS_RedLeds *rty_redLeds)
{
  switch (ActionsModel_DW.is_Forward) {
   case ActionsMo_IN_FW_EndedSafeAction:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    *rty_safeAction = ActionsMod_checkSafetyToForward(rtu_sonar->front);
    if (*rtu_currentUserAction != UA_FORWARD) {
      ActionsModel_DW.is_Forward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_Forward = 2U;
    } else if (*rty_safeAction == SA_NONE) {
      /* l'utente vorrebbe continuare ad andare avanti e non c'è più l'ostacolo */
      ActionsModel_DW.is_Forward = ActionsModel_IN_FW_UserAction;

      /*  Start tracking */
      ActionsModel_B.set = 1U;

      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      ActionsModel_MovingObstacles(1, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);

      /*  Action */
      *rty_roverAction = RA_FORWARD;

      /*  Set point */
      rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
        ActionsModel_MAX_SPEED_Y;
      rty_setPoint->leftAxis = rty_setPoint->rightAxis;

      /*  Led */
      rty_redLeds->left = ActionsModel_B.leftLed;
      rty_redLeds->right = ActionsModel_B.rightLed;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   case ActionsModel_IN_FW_SafeAction:
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    ActionsModel_FW_SafeAction(rtu_currentUserAction, rtu_speed, rtu_y_lever,
      rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction, rty_safeAction,
      rty_redLeds);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;

   default:
    /* Chart: '<Root>/RoverAction' incorporates:
     *  Chart: '<Root>/MovingObstacles'
     */
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    /* Chart: '<Root>/MovingObstacles' */
    /* case IN_FW_UserAction: */
    /*  Keep tracking */
    ActionsModel_MovingObstacles(ActionsModel_B.set, rtu_sonar,
      &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
      &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
      &ActionsModel_DW.sf_MovingObstacles);

    /*  Check Safety */
    *rty_safeAction = ActionsM_checkSafetyFromForward
      (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
       rtu_sonar->front);
    if (*rty_safeAction != SA_NONE) {
      /*  Stop tracking */
      ActionsModel_B.set = 0U;

      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      ActionsModel_MovingObstacles(0, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);
      ActionsModel_DW.is_Forward = ActionsModel_IN_FW_SafeAction;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      Ac_enter_internal_FW_SafeAction(rtu_gyroscope, rty_setPoint,
        rty_roverAction, rty_safeAction);
    } else if (*rtu_currentUserAction != UA_FORWARD) {
      /*  Stop tracking */
      ActionsModel_B.set = 0U;

      /* Chart: '<Root>/MovingObstacles' */
      /* Chart: '<Root>/MovingObstacles' */
      ActionsModel_MovingObstacles(0, rtu_sonar,
        &ActionsModel_B.statusLeftObstacle, &ActionsModel_B.statusRightObstacle,
        &ActionsModel_B.leftLed, &ActionsModel_B.rightLed,
        &ActionsModel_DW.sf_MovingObstacles);
      ActionsModel_DW.is_Forward = ActionsMod_IN_NO_ACTIVE_CHILD_h;
      ActionsModel_DW.exit_port_index_Forward = 2U;
    } else {
      /*  Action */
      *rty_roverAction = RA_FORWARD;

      /*  Set point */
      rty_setPoint->rightAxis = (real32_T)*rtu_y_lever / 512.0F *
        ActionsModel_MAX_SPEED_Y;
      rty_setPoint->leftAxis = rty_setPoint->rightAxis;

      /*  Led */
      rty_redLeds->left = ActionsModel_B.leftLed;
      rty_redLeds->right = ActionsModel_B.rightLed;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    break;
  }

  if (ActionsModel_DW.exit_port_index_Forward == 2U) {
    ActionsModel_DW.exit_port_index_Forward = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
      ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_RIGHT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
      ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_LEFT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
      ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_FORWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
      *rty_safeAction = ActionsM_checkSafetyFromForward
        (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
         rtu_sonar->front);
      ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
        rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
      break;

     case UA_BRAKING_SMOOTH:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingSmooth;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_SMOOTH;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     case UA_BRAKING_HARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_HARD;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_RotateLeft(const ENUM_UserAction *rtu_currentUserAction,
  const BUS_Speed *rtu_speed, const int16_T *rtu_x_lever, const int16_T
  *rtu_y_lever, const Gyroscope *rtu_gyroscope, const BUS_Sonar *rtu_sonar,
  BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction, ENUM_SafeAction
  *rty_safeAction, BUS_RedLeds *rty_redLeds)
{
  if (ActionsModel_DW.is_RotateLeft == ActionsModel_IN_RL_RotateLeft) {
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->left);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    switch (ActionsModel_DW.is_RL_RotateLeft) {
     case ActionsMo_IN_RL_EndedSafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/RoverAction'
       */
      /* Chart: '<Root>/RoverAction' */
      if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
        ActionsModel_DW.is_RL_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.is_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_RotateLeft = 2U;
      } else if (*rty_safeAction == SA_NONE) {
        /* l'utente vorrebbe continuare a ruotare a SX e non c'è più l'ostacolo */
        ActionsModel_DW.is_RL_RotateLeft = ActionsModel_IN_RL_UserAction;
        *rty_roverAction = RA_ROTATE_LEFT;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;

     case ActionsModel_IN_RL_SafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/RoverAction'
       */
      /* Chart: '<Root>/RoverAction' */
      /*     */
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        ActionsModel_DW.exit_port_index_RL_SafeAction = 2U;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      if (ActionsModel_DW.exit_port_index_RL_SafeAction == 2U) {
        ActionsModel_DW.exit_port_index_RL_SafeAction = 0U;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/RoverAction'
         */
        /* Chart: '<Root>/RoverAction' */
        if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
          ActionsModel_DW.is_RL_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
          ActionsModel_DW.is_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
          ActionsModel_DW.exit_port_index_RotateLeft = 2U;
        } else if (*rty_safeAction == SA_NONE) {
          /* l'utente vorrebbe continuare a ruotare a SX e non c'è più l'ostacolo */
          ActionsModel_DW.is_RL_RotateLeft = ActionsModel_IN_RL_UserAction;
          *rty_roverAction = RA_ROTATE_LEFT;

          /*  Set point */
          rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
            ActionsModel_MAX_SPEED_X;
          rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

          /*  Led */
          rty_redLeds->left = RED_OFF;
          rty_redLeds->right = RED_OFF;
        } else {
          ActionsModel_DW.is_RL_RotateLeft = ActionsMo_IN_RL_EndedSafeAction;
          *rty_roverAction = RA_IDLE;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;

     default:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/RoverAction'
       */
      /* Chart: '<Root>/RoverAction' */
      /* case IN_RL_UserAction: */
      if (*rty_safeAction != SA_NONE) {
        ActionsModel_DW.is_RL_RotateLeft = ActionsModel_IN_RL_SafeAction;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        *rty_roverAction = RA_BRAKING_HARD;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
        ActionsModel_DW.is_RL_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.is_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_RotateLeft = 2U;
      } else {
        *rty_roverAction = RA_ROTATE_LEFT;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;
    }

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    /* case IN_RL_StopMotors: */
  } else if (*rtu_currentUserAction != UA_ROTATE_LEFT) {
    ActionsModel_DW.is_RotateLeft = ActionsMod_IN_NO_ACTIVE_CHILD_h;
    ActionsModel_DW.exit_port_index_RotateLeft = 2U;
  } else if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
              rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0)
  {
    ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_RotateLeft;
    *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->left);
    if (*rty_safeAction != SA_NONE) {
      ActionsModel_DW.is_RL_RotateLeft = ActionsModel_IN_RL_SafeAction;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      *rty_roverAction = RA_BRAKING_HARD;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else {
      /* [safeAction == ENUM_SafeAction.SA_NONE] */
      ActionsModel_DW.is_RL_RotateLeft = ActionsModel_IN_RL_UserAction;
      *rty_roverAction = RA_ROTATE_LEFT;

      /*  Set point */
      rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
        ActionsModel_MAX_SPEED_X;
      rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }

  if (ActionsModel_DW.exit_port_index_RotateLeft == 2U) {
    ActionsModel_DW.exit_port_index_RotateLeft = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
      ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_RIGHT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
      ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_LEFT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
      ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_FORWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
      *rty_safeAction = ActionsM_checkSafetyFromForward
        (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
         rtu_sonar->front);
      ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
        rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
      break;

     case UA_BRAKING_SMOOTH:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingSmooth;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_SMOOTH;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     case UA_BRAKING_HARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_HARD;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* Function for Chart: '<Root>/RoverAction' */
static void ActionsModel_RotateRight(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_x_lever,
  const int16_T *rtu_y_lever, const Gyroscope *rtu_gyroscope, const BUS_Sonar
  *rtu_sonar, BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction,
  ENUM_SafeAction *rty_safeAction, BUS_RedLeds *rty_redLeds)
{
  if (ActionsModel_DW.is_RotateRight == ActionsModel_IN_RR_RotateRight) {
    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->right);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
    switch (ActionsModel_DW.is_RR_RotateRight) {
     case ActionsMo_IN_RR_EndedSafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/RoverAction'
       */
      /* Chart: '<Root>/RoverAction' */
      if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
        ActionsModel_DW.is_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.is_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_RotateRight = 2U;
      } else if (*rty_safeAction == SA_NONE) {
        /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
        ActionsModel_DW.is_RR_RotateRight = ActionsModel_IN_RR_UserAction;
        *rty_roverAction = RA_ROTATE_RIGHT;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;

     case ActionsModel_IN_RR_SafeAction:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/RoverAction'
       */
      /* Chart: '<Root>/RoverAction' */
      /*     */
      if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
           rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0) {
        ActionsModel_DW.exit_port_index_RR_SafeAction = 2U;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      if (ActionsModel_DW.exit_port_index_RR_SafeAction == 2U) {
        ActionsModel_DW.exit_port_index_RR_SafeAction = 0U;

        /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
         *  Chart: '<Root>/RoverAction'
         */
        /* Chart: '<Root>/RoverAction' */
        if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
          ActionsModel_DW.is_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
          ActionsModel_DW.is_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
          ActionsModel_DW.exit_port_index_RotateRight = 2U;
        } else if (*rty_safeAction == SA_NONE) {
          /* l'utente vorrebbe continuare a ruotare a DX e non c'è più l'ostacolo */
          ActionsModel_DW.is_RR_RotateRight = ActionsModel_IN_RR_UserAction;
          *rty_roverAction = RA_ROTATE_RIGHT;

          /*  Set point */
          rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
            ActionsModel_MAX_SPEED_X;
          rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

          /*  Led */
          rty_redLeds->left = RED_OFF;
          rty_redLeds->right = RED_OFF;
        } else {
          ActionsModel_DW.is_RR_RotateRight = ActionsMo_IN_RR_EndedSafeAction;
          *rty_roverAction = RA_IDLE;

          /*  Set point */
          rty_setPoint->rightAxis = 0.0F;
          rty_setPoint->leftAxis = 0.0F;
        }

        /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      }
      break;

     default:
      /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
       *  Chart: '<Root>/RoverAction'
       */
      /* Chart: '<Root>/RoverAction' */
      /* case IN_RR_UserAction: */
      if (*rty_safeAction != SA_NONE) {
        ActionsModel_DW.is_RR_RotateRight = ActionsModel_IN_RR_SafeAction;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        *rty_roverAction = RA_BRAKING_HARD;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;
      } else if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
        ActionsModel_DW.is_RR_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.is_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
        ActionsModel_DW.exit_port_index_RotateRight = 2U;
      } else {
        *rty_roverAction = RA_ROTATE_RIGHT;

        /*  Set point */
        rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
          ActionsModel_MAX_SPEED_X;
        rty_setPoint->rightAxis = -rty_setPoint->leftAxis;
      }

      /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
      break;
    }

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    /* case IN_RR_StopMotors: */
  } else if (*rtu_currentUserAction != UA_ROTATE_RIGHT) {
    ActionsModel_DW.is_RotateRight = ActionsMod_IN_NO_ACTIVE_CHILD_h;
    ActionsModel_DW.exit_port_index_RotateRight = 2U;

    /*     */
  } else if (ActionsModel_areAllSpeedsZero(rtu_speed->motor1, rtu_speed->motor2,
              rtu_speed->motor3, rtu_speed->motor4, ActionsModel_NO_SPEED) != 0)
  {
    ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_RotateRight;
    *rty_safeAction = ActionsMo_checkSafetyFromRotate(rtu_sonar->right);
    if (*rty_safeAction != SA_NONE) {
      ActionsModel_DW.is_RR_RotateRight = ActionsModel_IN_RR_SafeAction;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      *rty_roverAction = RA_BRAKING_HARD;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;
    } else {
      /* [safeAction == ENUM_SafeAction.SA_NONE] */
      ActionsModel_DW.is_RR_RotateRight = ActionsModel_IN_RR_UserAction;
      *rty_roverAction = RA_ROTATE_RIGHT;

      /*  Set point */
      rty_setPoint->leftAxis = (real32_T)*rtu_x_lever / 512.0F *
        ActionsModel_MAX_SPEED_X;
      rty_setPoint->rightAxis = -rty_setPoint->leftAxis;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }

  if (ActionsModel_DW.exit_port_index_RotateRight == 2U) {
    ActionsModel_DW.exit_port_index_RotateRight = 0U;

    /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
     *  Chart: '<Root>/RoverAction'
     */
    /* Chart: '<Root>/RoverAction' */
    switch (*rtu_currentUserAction) {
     case UA_BACKWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
      ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_RIGHT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
      ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_ROTATE_LEFT:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
      ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;

     case UA_FORWARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
      *rty_safeAction = ActionsM_checkSafetyFromForward
        (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
         rtu_sonar->front);
      ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
        rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
      break;

     case UA_BRAKING_SMOOTH:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingSmooth;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_SMOOTH;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     case UA_BRAKING_HARD:
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_HARD;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_ON;
      rty_redLeds->right = RED_ON;
      break;

     default:
      /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
         [currentUserAction == ENUM_UserAction.UA_NONE] */
      ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

      /*  Actions */
      *rty_roverAction = RA_BRAKING_MODERATE;
      *rty_safeAction = SA_NONE;

      /*  Set point */
      rty_setPoint->rightAxis = 0.0F;
      rty_setPoint->leftAxis = 0.0F;

      /*  Led */
      rty_redLeds->left = RED_OFF;
      rty_redLeds->right = RED_OFF;
      break;
    }

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
  }
}

/* System initialize for referenced model: 'ActionsModel' */
void ActionsModel_Init(BUS_SetPoint *rty_setPoint, ENUM_RoverAction
  *rty_roverAction, BUS_RedLeds *rty_redLeds)
{
  /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
   *  Chart: '<Root>/RoverAction'
   */
  /* Chart: '<Root>/RoverAction' */
  /*  Outputs initialization */
  /*  Superstate inutile? Forse con lo stato degradato ha senso se questo chart cambia stato */
  ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

  /*  Actions */
  *rty_roverAction = RA_BRAKING_MODERATE;

  /*  Set point */
  rty_setPoint->rightAxis = 0.0F;
  rty_setPoint->leftAxis = 0.0F;

  /*  Led */
  rty_redLeds->left = RED_OFF;
  rty_redLeds->right = RED_OFF;

  /* SystemInitialize for Chart: '<Root>/RoverAction' incorporates:
   *  Chart: '<Root>/MovingObstacles'
   */
  /* SystemInitialize for Chart: '<Root>/MovingObstacles' */
  ActionsMod_MovingObstacles_Init(&ActionsModel_B.statusLeftObstacle,
    &ActionsModel_B.statusRightObstacle, &ActionsModel_B.leftLed,
    &ActionsModel_B.rightLed, &ActionsModel_DW.sf_MovingObstacles);

  /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
}

/* Output and update for referenced model: 'ActionsModel' */
void ActionsModel_ComputeRoverAction(const ENUM_UserAction
  *rtu_currentUserAction, const BUS_Speed *rtu_speed, const int16_T *rtu_x_lever,
  const int16_T *rtu_y_lever, const Gyroscope *rtu_gyroscope, const BUS_Sonar
  *rtu_sonar, BUS_SetPoint *rty_setPoint, ENUM_RoverAction *rty_roverAction,
  ENUM_SafeAction *rty_safeAction, BUS_RedLeds *rty_redLeds, ENUM_PidMode
  *rty_selectedPidMode)
{
  /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
   *  Chart: '<Root>/RoverAction'
   */
  /* Chart: '<Root>/RoverAction' */
  switch (ActionsModel_DW.is_CurrentRoverAction) {
   case ActionsModel_IN_Backward:
    ActionsModel_Backward(rtu_currentUserAction, rtu_speed, rtu_y_lever,
                          rtu_gyroscope, rtu_sonar, rty_setPoint,
                          rty_roverAction, rty_safeAction, rty_redLeds);
    break;

   case ActionsModel_IN_BrakingHard:
    if (*rtu_currentUserAction != UA_BRAKING_HARD) {
      switch (*rtu_currentUserAction) {
       case UA_BACKWARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
        ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_ROTATE_RIGHT:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
        ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_ROTATE_LEFT:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
        ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_FORWARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
        *rty_safeAction = ActionsM_checkSafetyFromForward
          (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
           rtu_sonar->front);
        ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
          rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
        break;

       case UA_BRAKING_SMOOTH:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingSmooth;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_SMOOTH;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        break;

       case UA_BRAKING_HARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_HARD;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        break;

       default:
        /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
           [currentUserAction == ENUM_UserAction.UA_NONE] */
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;
      }
    }
    break;

   case ActionsModel_IN_BrakingSmooth:
    if (*rtu_currentUserAction != UA_BRAKING_SMOOTH) {
      switch (*rtu_currentUserAction) {
       case UA_BACKWARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
        ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_ROTATE_RIGHT:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
        ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_ROTATE_LEFT:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
        ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_FORWARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
        *rty_safeAction = ActionsM_checkSafetyFromForward
          (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
           rtu_sonar->front);
        ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
          rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
        break;

       case UA_BRAKING_HARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_HARD;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        break;

       default:
        /*  Transizione incondizionata siccome le exit junction hanno bisogno di uno stato garantito in cui entrare
           [currentUserAction == ENUM_UserAction.UA_NONE] */
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_None;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;
      }
    }
    break;

   case ActionsModel_IN_Forward:
    ActionsModel_Forward(rtu_currentUserAction, rtu_speed, rtu_y_lever,
                         rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction,
                         rty_safeAction, rty_redLeds);
    break;

   case ActionsModel_IN_None:
    if (*rtu_currentUserAction != UA_NONE) {
      switch (*rtu_currentUserAction) {
       case UA_BACKWARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Backward;
        ActionsModel_DW.is_Backward = ActionsModel_IN_BW_StopMotors1;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_ROTATE_RIGHT:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateRight;
        ActionsModel_DW.is_RotateRight = ActionsModel_IN_RR_StopMotors;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_ROTATE_LEFT:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_RotateLeft;
        ActionsModel_DW.is_RotateLeft = ActionsModel_IN_RL_StopMotors;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_MODERATE;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_OFF;
        rty_redLeds->right = RED_OFF;
        break;

       case UA_FORWARD:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_Forward;
        *rty_safeAction = ActionsM_checkSafetyFromForward
          (ActionsModel_B.statusLeftObstacle, ActionsModel_B.statusRightObstacle,
           rtu_sonar->front);
        ActionsM_enter_internal_Forward(rtu_y_lever, rtu_gyroscope, rtu_sonar,
          rty_setPoint, rty_roverAction, rty_safeAction, rty_redLeds);
        break;

       case UA_BRAKING_SMOOTH:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingSmooth;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_SMOOTH;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        break;

       default:
        ActionsModel_DW.is_CurrentRoverAction = ActionsModel_IN_BrakingHard;

        /*  Actions */
        *rty_roverAction = RA_BRAKING_HARD;
        *rty_safeAction = SA_NONE;

        /*  Set point */
        rty_setPoint->rightAxis = 0.0F;
        rty_setPoint->leftAxis = 0.0F;

        /*  Led */
        rty_redLeds->left = RED_ON;
        rty_redLeds->right = RED_ON;
        break;
      }
    }
    break;

   case ActionsModel_IN_RotateLeft:
    ActionsModel_RotateLeft(rtu_currentUserAction, rtu_speed, rtu_x_lever,
      rtu_y_lever, rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction,
      rty_safeAction, rty_redLeds);
    break;

   default:
    /* case IN_RotateRight: */
    ActionsModel_RotateRight(rtu_currentUserAction, rtu_speed, rtu_x_lever,
      rtu_y_lever, rtu_gyroscope, rtu_sonar, rty_setPoint, rty_roverAction,
      rty_safeAction, rty_redLeds);
    break;
  }

  /* End of Chart: '<Root>/RoverAction' */

  /* RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' incorporates:
   *  SubSystem: '<Root>/Subsystem'
   */
  /* MATLAB Function: '<S3>/MATLAB Function' */
  switch (*rty_roverAction) {
   case RA_BRAKING_SMOOTH:
    *rty_selectedPidMode = SLOW;
    break;

   case RA_BRAKING_MODERATE:
    *rty_selectedPidMode = MEDIUM;
    break;

   default:
    *rty_selectedPidMode = FAST;
    break;
  }

  /* End of MATLAB Function: '<S3>/MATLAB Function' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/ComputeRoverAction' */
}

/* Model initialize function */
void ActionsModel_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_ActionsModel_T *const ActionsModel_M = &(ActionsModel_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(ActionsModel_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
