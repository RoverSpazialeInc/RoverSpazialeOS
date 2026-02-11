/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board1.c
 *
 * Code generated for Simulink model 'Board1'.
 *
 * Model version                  : 13.71
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 12:48:49 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Board1.h"
#include "rtwtypes.h"
#include "sensors.h"
#include "states.h"
#include "Board1_types.h"
#include "decision_enums.h"
#include <math.h>
#include "controller_masks.h"
#include "frame_size.h"
#include "crc_functions.h"
#include "ActionsModel.h"
#include "BoardsHealth.h"
#include "CommunicationLinkHealth.h"
#include "MotorsHealth.h"
#include "RedLedsActuation.h"
#include "RoverTemperatureHealth.h"

/* Named constants for Chart: '<Root>/SupervisorB1' */
#define B_IN_StateCoherenceVerification ((uint8_T)7U)
#define Boar_IN_ComputingOwnGlobalState ((uint8_T)1U)
#define Board1_IN_ArmingReceive        ((uint8_T)1U)
#define Board1_IN_CheckBatteryHealth   ((uint8_T)1U)
#define Board1_IN_CheckCRC             ((uint8_T)2U)
#define Board1_IN_CheckMotorsHealth    ((uint8_T)2U)
#define Board1_IN_CommunicationPhase   ((uint8_T)1U)
#define Board1_IN_CompareDecision      ((uint8_T)1U)
#define Board1_IN_ComputeDecision      ((uint8_T)1U)
#define Board1_IN_D_Receive            ((uint8_T)2U)
#define Board1_IN_D_Transmit           ((uint8_T)3U)
#define Board1_IN_Degraded             ((uint8_T)2U)
#define Board1_IN_DegradedCase         ((uint8_T)1U)
#define Board1_IN_Emergency            ((uint8_T)3U)
#define Board1_IN_EmergencyCase        ((uint8_T)2U)
#define Board1_IN_ErrorStateDecision   ((uint8_T)2U)
#define Board1_IN_ExchangeDecision     ((uint8_T)3U)
#define Board1_IN_ExchangeGlobalState  ((uint8_T)4U)
#define Board1_IN_ExchangeLocalState   ((uint8_T)5U)
#define Board1_IN_Faulty               ((uint8_T)4U)
#define Board1_IN_GL_Receive           ((uint8_T)2U)
#define Board1_IN_GL_Transmit          ((uint8_T)3U)
#define Board1_IN_IF_B1isFaulty        ((uint8_T)4U)
#define Board1_IN_IF_B2isFaulty1       ((uint8_T)5U)
#define Board1_IN_IF_Emergency         ((uint8_T)6U)
#define Board1_IN_Idle                 ((uint8_T)5U)
#define Board1_IN_LS_Receive           ((uint8_T)1U)
#define Board1_IN_LS_Transmit          ((uint8_T)2U)
#define Board1_IN_LightEvaluation      ((uint8_T)5U)
#define Board1_IN_NO_ACTIVE_CHILD      ((uint8_T)0U)
#define Board1_IN_NotCommunicating     ((uint8_T)6U)
#define Board1_IN_R_ArmingReceive      ((uint8_T)3U)
#define Board1_IN_R_CheckCRC           ((uint8_T)4U)
#define Board1_IN_R_ReadyToReceive     ((uint8_T)5U)
#define Board1_IN_R_ReceivingRTR       ((uint8_T)1U)
#define Board1_IN_R_SendNack           ((uint8_T)6U)
#define Board1_IN_R_Trasmit            ((uint8_T)2U)
#define Board1_IN_R_WaitAck            ((uint8_T)3U)
#define Board1_IN_ReadyToReceive       ((uint8_T)7U)
#define Board1_IN_ReceivingRTR         ((uint8_T)4U)
#define Board1_IN_RedLedsActuation     ((uint8_T)7U)
#define Board1_IN_SendAck              ((uint8_T)8U)
#define Board1_IN_SendNack             ((uint8_T)9U)
#define Board1_IN_SupervisionEnded     ((uint8_T)7U)
#define Board1_IN_Trasmit              ((uint8_T)5U)
#define Board1_IN_UpdateBoardsHealth   ((uint8_T)8U)
#define Board1_IN_UpdateDecision       ((uint8_T)3U)
#define Board1_IN_UpdateRoverState     ((uint8_T)4U)
#define Board1_IN_UserActionComputation ((uint8_T)9U)
#define Board1_IN_WaitAck              ((uint8_T)6U)
#define Board1_IN_checkRTOSHealth      ((uint8_T)4U)
#define Board_IN_EmergencyStateAnalysis ((uint8_T)4U)
#define Board_IN_RoverActionComputation ((uint8_T)6U)
#define IN_CheckRoverTemperatureHealth ((uint8_T)3U)
#define IN_UpdateCommunicationCycleStat ((uint8_T)6U)
#define IN_UpdateCommunicationLinkHealt ((uint8_T)8U)
#define IN_ValidateReceivedSensorReadin ((uint8_T)3U)

/* Block signals (default storage) */
B_Board1_T Board1_B;

/* Block states (default storage) */
DW_Board1_T Board1_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Board1_T Board1_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Board1_T Board1_Y;

/* Real-time model */
static RT_MODEL_Board1_T Board1_M_;
RT_MODEL_Board1_T *const Board1_M = &Board1_M_;

/* Forward declaration for local functions */
static ENUM_StatusWhiteLed Board1_evaluateLed(uint16_T buttons, uint16_T
  lastButtons, ENUM_StatusWhiteLed previousLedStatus, uint16_T button_mask);
static void Board1_emergencyCheck(real32_T globalStateRover_localStateB1_s,
  real32_T globalStateRover_localStateB1_0, real32_T
  globalStateRover_localStateB1_1, real32_T globalStateRover_localStateB1_2,
  Temperature globalStateRover_localStateB1_t, BatteryLevel
  globalStateRover_localStateB1_b, uint16_T globalStateRover_localStateB2_s,
  uint16_T globalStateRover_localStateB2_0, uint16_T
  globalStateRover_localStateB2_1, Gyroscope globalStateRover_localStateB2_g,
  int16_T globalStateRover_localStateB2_r, int16_T
  globalStateRover_localStateB2_2, ENUM_Error *errB1, ENUM_Error *errB2);
static ENUM_StatusRover Board1_convertInENUMRoverStatus(ENUM_BoardStatus
  B1_status, ENUM_BoardStatus B2_status);
static ENUM_UserAction Board1_computeUserAction(int16_T x_lever, int16_T y_lever,
  uint16_T buttons, uint16_T braking_hard_mask, uint16_T braking_smooth_mask);
static void Board1_ExchangeDecision(void);
static boolean_T Board1_isequal(uint16_T varargin_1_sonar_left, uint16_T
  varargin_1_sonar_front, uint16_T varargin_1_sonar_right, Gyroscope
  varargin_1_gyroscope, int16_T varargin_1_remoteController_y_l, int16_T
  varargin_1_remoteController_x_l, uint16_T varargin_1_remoteController_but,
  uint8_T varargin_1_sensorReadings, uint8_T varargin_1_deadlineOccurred,
  uint16_T varargin_2_sonar_left, uint16_T varargin_2_sonar_front, uint16_T
  varargin_2_sonar_right, Gyroscope varargin_2_gyroscope, int16_T
  varargin_2_remoteController_y_l, int16_T varargin_2_remoteController_x_l,
  uint16_T varargin_2_remoteController_but, uint8_T varargin_2_sensorReadings,
  uint8_T varargin_2_deadlineOccurred);
static void Board1_coherenceVerification(real32_T localStateSent_speed_motor1,
  real32_T localStateSent_speed_motor2, real32_T localStateSent_speed_motor3,
  real32_T localStateSent_speed_motor4, Temperature localStateSent_temperature,
  BatteryLevel localStateSent_batteryLevel, uint8_T
  localStateSent_sensorReadings, uint8_T localStateSent_deadlineOccurred,
  uint16_T localStateReceived_sonar_left, uint16_T
  localStateReceived_sonar_front, uint16_T localStateReceived_sonar_right,
  Gyroscope localStateReceived_gyroscope, int16_T
  localStateReceived_remoteContro, int16_T localStateReceived_remoteCont_0,
  uint16_T localStateReceived_remoteCont_1, uint8_T
  localStateReceived_sensorReadin, uint8_T localStateReceived_deadlineOccu,
  const BUS_LocalStateB1 globalStateReceived_localStateB, const BUS_LocalStateB2
  globalStateReceived_localStat_0, ENUM_Error *errB1, ENUM_Error *errB2);
static void Board1_ExchangeGlobalState(void);
static ENUM_Error Board1_validateSensorReadings(uint8_T sensorReadings, real_T
  errorMask);
static ENUM_Error Board1_validateRTOSHealth(uint8_T deadlineMissed);
static void Board1_ExchangeLocalState(void);
static void exit_internal_CommunicationPhas(void);

/* Function for Chart: '<Root>/SupervisorB1' */
static ENUM_StatusWhiteLed Board1_evaluateLed(uint16_T buttons, uint16_T
  lastButtons, ENUM_StatusWhiteLed previousLedStatus, uint16_T button_mask)
{
  ENUM_StatusWhiteLed nextLedStatus;

  /*  Carico il vecchio stato di default */
  nextLedStatus = previousLedStatus;

  /*  se � premuto */
  if (((buttons & button_mask) == button_mask) && ((lastButtons & button_mask)
       != button_mask)) {
    /*  prima non era stato premuto (rising edge) */
    if (previousLedStatus == WHITE_OFF) {
      nextLedStatus = WHITE_ON;
    } else {
      nextLedStatus = WHITE_OFF;
    }
  }

  return nextLedStatus;
}

/* Function for Chart: '<Root>/SupervisorB1' */
static void Board1_emergencyCheck(real32_T globalStateRover_localStateB1_s,
  real32_T globalStateRover_localStateB1_0, real32_T
  globalStateRover_localStateB1_1, real32_T globalStateRover_localStateB1_2,
  Temperature globalStateRover_localStateB1_t, BatteryLevel
  globalStateRover_localStateB1_b, uint16_T globalStateRover_localStateB2_s,
  uint16_T globalStateRover_localStateB2_0, uint16_T
  globalStateRover_localStateB2_1, Gyroscope globalStateRover_localStateB2_g,
  int16_T globalStateRover_localStateB2_r, int16_T
  globalStateRover_localStateB2_2, ENUM_Error *errB1, ENUM_Error *errB2)
{
  *errB1 = NO_ERROR;
  *errB2 = NO_ERROR;
  if (fabsf(globalStateRover_localStateB1_s) > 200.0F) {
    *errB1 = ERROR_PRESENT;
  } else if (fabsf(globalStateRover_localStateB1_0) > 200.0F) {
    *errB1 = ERROR_PRESENT;
  } else if (fabsf(globalStateRover_localStateB1_1) > 200.0F) {
    *errB1 = ERROR_PRESENT;
  } else if (fabsf(globalStateRover_localStateB1_2) > 200.0F) {
    *errB1 = ERROR_PRESENT;
  }

  if ((globalStateRover_localStateB1_t < -55.0F) ||
      (globalStateRover_localStateB1_t > 125.0F)) {
    *errB1 = ERROR_PRESENT;
  }

  if (globalStateRover_localStateB1_b > 100) {
    *errB1 = ERROR_PRESENT;
  }

  if ((globalStateRover_localStateB2_s > 400) ||
      (globalStateRover_localStateB2_0 > 400) ||
      (globalStateRover_localStateB2_1 > 400)) {
    *errB2 = ERROR_PRESENT;
  }

  if (globalStateRover_localStateB2_g > 360) {
    *errB2 = ERROR_PRESENT;
  }

  if ((globalStateRover_localStateB2_2 < -512) ||
      (globalStateRover_localStateB2_2 > 512) ||
      (globalStateRover_localStateB2_r < -512) ||
      (globalStateRover_localStateB2_r > 512)) {
    *errB2 = ERROR_PRESENT;
  }
}

/* Function for Chart: '<Root>/SupervisorB1' */
static ENUM_StatusRover Board1_convertInENUMRoverStatus(ENUM_BoardStatus
  B1_status, ENUM_BoardStatus B2_status)
{
  ENUM_StatusRover res;
  if ((B1_status == BOARD_FAULT) && (B2_status == BOARD_FAULT)) {
    res = EMERGENCY;
  } else if (B1_status == BOARD_FAULT) {
    res = FAULTY_B1_DEGRADED_B2;
  } else if (B2_status == BOARD_FAULT) {
    res = FAULTY_B2_DEGRADED_B1;
  } else if ((B1_status == BOARD_ERROR) && (B2_status == BOARD_ERROR)) {
    res = ERROR_BOTH;
  } else if (B1_status == BOARD_ERROR) {
    res = ERROR_B1;
  } else if (B2_status == BOARD_ERROR) {
    res = ERROR_B2;
  } else {
    res = NORMAL;
  }

  return res;
}

/* Function for Chart: '<Root>/SupervisorB1' */
static ENUM_UserAction Board1_computeUserAction(int16_T x_lever, int16_T y_lever,
  uint16_T buttons, uint16_T braking_hard_mask, uint16_T braking_smooth_mask)
{
  ENUM_UserAction userAction;
  userAction = UA_NONE;
  if ((buttons & braking_hard_mask) == braking_hard_mask) {
    userAction = UA_BRAKING_HARD;
  } else if ((buttons & braking_smooth_mask) == braking_smooth_mask) {
    userAction = UA_BRAKING_SMOOTH;
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

/* Function for Chart: '<Root>/SupervisorB1' */
static void Board1_ExchangeDecision(void)
{
  switch (Board1_DW.is_ExchangeDecision) {
   case Board1_IN_CompareDecision:
    /* [result == 1 || result == 0] */
    if (Board1_DW.result == 1) {
      Board1_DW.is_ExchangeDecision = Board1_IN_RedLedsActuation;

      /* ModelReference: '<Root>/RedLedsActuation' incorporates:
       *  Outport: '<Root>/board1Decision'
       */
      RedLedsActuation_ActuateRedLeds(&Board1_Y.board1Decision.leds.red.left,
        &Board1_Y.board1Decision.leds.red.right);
    }
    break;

   case Board1_IN_D_Receive:
    switch (Board1_DW.is_D_Receive) {
     case Board1_IN_ArmingReceive:
      if (Board1_DW.receiveArmed == 1) {
        Board1_DW.is_D_Receive = Board1_IN_ReadyToReceive;
        setRTR();
      }
      break;

     case Board1_IN_CheckCRC:
      switch (Board1_DW.flagCRC) {
       case 1:
        Board1_DW.is_D_Receive = Board1_IN_SendAck;
        UART_SendAckIT();
        break;

       case 0:
        Board1_DW.is_D_Receive = Board1_IN_SendNack;
        UART_SendNackIT();
        break;
      }
      break;

     case Board1_IN_R_ArmingReceive:
      if (Board1_DW.receiveArmed == 1) {
        Board1_DW.is_D_Receive = Board1_IN_R_ReadyToReceive;
        setRTR();
      }
      break;

     case Board1_IN_R_CheckCRC:
      switch (Board1_DW.flagCRC) {
       case 1:
        Board1_DW.is_D_Receive = Board1_IN_SendAck;
        UART_SendAckIT();
        break;

       case 0:
        Board1_DW.is_D_Receive = Board1_IN_R_SendNack;
        UART_SendNackIT();
        break;
      }
      break;

     case Board1_IN_R_ReadyToReceive:
      if (errorReceived() == 1) {
        resetRTR();
        Board1_DW.is_D_Receive = Board1_IN_R_SendNack;
        UART_SendNackIT();
      } else if (hasReceived() == 1) {
        Board1_DW.flagCRC = 0U;
        resetRTR();
        Board1_DW.is_D_Receive = Board1_IN_R_CheckCRC;

        /* Inport: '<Root>/rx_buffer' */
        Board1_DW.flagCRC = compareCRC(&Board1_U.rx_buffer[0],
          Board1_DW.rxPayload);
      }
      break;

     case Board1_IN_R_SendNack:
      Board1_DW.is_D_Receive = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_D_Receive = 2U;
      break;

     case Board1_IN_ReadyToReceive:
      if (errorReceived() == 1) {
        resetRTR();
        Board1_DW.is_D_Receive = Board1_IN_SendNack;
        UART_SendNackIT();
      } else if (hasReceived() == 1) {
        Board1_DW.flagCRC = 0U;
        resetRTR();
        Board1_DW.is_D_Receive = Board1_IN_CheckCRC;

        /* Inport: '<Root>/rx_buffer' */
        Board1_DW.flagCRC = compareCRC(&Board1_U.rx_buffer[0],
          Board1_DW.rxPayload);
      }
      break;

     case Board1_IN_SendAck:
      Board1_DW.is_D_Receive = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_D_Receive = 3U;
      break;

     default:
      /* case IN_SendNack: */
      Board1_DW.is_D_Receive = Board1_IN_R_ArmingReceive;

      /* Inport: '<Root>/rx_buffer' */
      Board1_DW.receiveArmed = UART_ReceiveIT(&Board1_U.rx_buffer[0], (uint64_T)
        (Board1_DW.rxPayload + ((uint8_T)CRC_SIZE)));
      Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
      break;
    }

    switch (Board1_DW.exit_port_index_D_Receive) {
     case 2:
      Board1_DW.exit_port_index_D_Receive = 0U;
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeDecisio = 2U;
      break;

     case 3:
      Board1_DW.exit_port_index_D_Receive = 0U;

      /* Inport: '<Root>/rx_buffer' */
      deserializeDecision(&Board1_U.rx_buffer[0], Board1_DW.rxPayload,
                          &Board1_DW.board2Decision);
      Board1_DW.is_ExchangeDecision = Board1_IN_CompareDecision;

      /* Outport: '<Root>/board1Decision' */
      Board1_DW.result = BUS_Decision_Equals(&Board1_Y.board1Decision,
        &Board1_DW.board2Decision);
      break;
    }
    break;

   case Board1_IN_D_Transmit:
    switch (Board1_DW.is_D_Transmit) {
     case Board1_IN_R_ReceivingRTR:
      if (checkRTR() != 0) {
        Board1_DW.is_D_Transmit = Board1_IN_R_Trasmit;
        UART_ReceiveAckIT();

        /* Outport: '<Root>/tx_buffer' */
        UART_TransmitIT(&Board1_Y.tx_buffer[0], (uint64_T)(Board1_DW.txPayload +
          ((uint8_T)CRC_SIZE)));
      } else {
        Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
      }
      break;

     case Board1_IN_R_Trasmit:
      Board1_DW.is_D_Transmit = Board1_IN_R_WaitAck;
      break;

     case Board1_IN_R_WaitAck:
      if (hasReceived() == 1) {
        if (UART_CheckAck() == 0) {
          Board1_DW.is_D_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_D_Transmit = 2U;
        } else if (UART_CheckAck() == 1) {
          Board1_DW.is_D_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_D_Transmit = 3U;
        }
      }
      break;

     case Board1_IN_ReceivingRTR:
      if (checkRTR() != 0) {
        Board1_DW.is_D_Transmit = Board1_IN_Trasmit;
        UART_ReceiveAckIT();

        /* Outport: '<Root>/tx_buffer' */
        UART_TransmitIT(&Board1_Y.tx_buffer[0], (uint64_T)(Board1_DW.txPayload +
          ((uint8_T)CRC_SIZE)));
      }
      break;

     case Board1_IN_Trasmit:
      Board1_DW.is_D_Transmit = Board1_IN_WaitAck;
      break;

     default:
      /* case IN_WaitAck: */
      if (hasReceived() == 1) {
        if (UART_CheckAck() == 1) {
          Board1_DW.is_D_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_D_Transmit = 3U;
        } else if (UART_CheckAck() == 0) {
          Board1_DW.is_D_Transmit = Board1_IN_R_ReceivingRTR;
          Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
        }
      }
      break;
    }

    switch (Board1_DW.exit_port_index_D_Transmit) {
     case 2:
      Board1_DW.exit_port_index_D_Transmit = 0U;
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeDecisio = 2U;
      break;

     case 3:
      Board1_DW.exit_port_index_D_Transmit = 0U;
      Board1_DW.is_ExchangeDecision = Board1_IN_D_Receive;
      Board1_DW.is_D_Receive = Board1_IN_ArmingReceive;

      /* Inport: '<Root>/rx_buffer' */
      Board1_DW.receiveArmed = UART_ReceiveIT(&Board1_U.rx_buffer[0], (uint64_T)
        (Board1_DW.rxPayload + ((uint8_T)CRC_SIZE)));
      break;
    }
    break;

   case Board1_IN_IF_B1isFaulty:
    /* Outport: '<Root>/board1Decision' */
    if (Board1_Y.board1Decision.roverState == FAULTY_B1_DEGRADED_B2) {
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeDecisio = 5U;
    } else {
      Board1_DW.is_ExchangeDecision = Board1_IN_IF_B2isFaulty1;
    }
    break;

   case Board1_IN_IF_B2isFaulty1:
    /* Outport: '<Root>/board1Decision' */
    if (Board1_Y.board1Decision.roverState == FAULTY_B2_DEGRADED_B1) {
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeDecisio = 3U;
    } else {
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeDecisio = 6U;
    }
    break;

   case Board1_IN_IF_Emergency:
    /* Outport: '<Root>/board1Decision' */
    if (Board1_Y.board1Decision.roverState == EMERGENCY) {
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeDecisio = 4U;
    } else {
      Board1_DW.is_ExchangeDecision = Board1_IN_IF_B1isFaulty;
    }
    break;

   default:
    /* case IN_RedLedsActuation: */
    Board1_DW.is_ExchangeDecision = Board1_IN_IF_Emergency;
    break;
  }

  switch (Board1_DW.exit_port_index_ExchangeDecisio) {
   case 2:
    Board1_DW.exit_port_index_ExchangeDecisio = 0U;
    Board1_DW.is_CommunicationPhase = IN_UpdateCommunicationCycleStat;
    Board1_DW.commCycleStatus = CYCLE_FAIL;
    break;

   case 3:
    Board1_DW.exit_port_index_ExchangeDecisio = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    Board1_DW.exit_port_index_CommunicationPh = 2U;
    break;

   case 4:
    Board1_DW.exit_port_index_ExchangeDecisio = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    Board1_DW.exit_port_index_CommunicationPh = 3U;
    break;

   case 5:
    Board1_DW.exit_port_index_ExchangeDecisio = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    Board1_DW.exit_port_index_CommunicationPh = 4U;
    break;

   case 6:
    Board1_DW.exit_port_index_ExchangeDecisio = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    Board1_DW.exit_port_index_CommunicationPh = 5U;
    break;
  }
}

/* Function for Chart: '<Root>/SupervisorB1' */
static boolean_T Board1_isequal(uint16_T varargin_1_sonar_left, uint16_T
  varargin_1_sonar_front, uint16_T varargin_1_sonar_right, Gyroscope
  varargin_1_gyroscope, int16_T varargin_1_remoteController_y_l, int16_T
  varargin_1_remoteController_x_l, uint16_T varargin_1_remoteController_but,
  uint8_T varargin_1_sensorReadings, uint8_T varargin_1_deadlineOccurred,
  uint16_T varargin_2_sonar_left, uint16_T varargin_2_sonar_front, uint16_T
  varargin_2_sonar_right, Gyroscope varargin_2_gyroscope, int16_T
  varargin_2_remoteController_y_l, int16_T varargin_2_remoteController_x_l,
  uint16_T varargin_2_remoteController_but, uint8_T varargin_2_sensorReadings,
  uint8_T varargin_2_deadlineOccurred)
{
  boolean_T e_p;
  boolean_T p;
  p = false;
  if (varargin_1_deadlineOccurred == varargin_2_deadlineOccurred) {
    if (varargin_1_sensorReadings == varargin_2_sensorReadings) {
      if (varargin_1_remoteController_but == varargin_2_remoteController_but) {
        e_p = ((varargin_1_remoteController_x_l ==
                varargin_2_remoteController_x_l) &&
               (varargin_1_remoteController_y_l ==
                varargin_2_remoteController_y_l));
      } else {
        e_p = false;
      }

      if (e_p) {
        if (varargin_1_gyroscope == varargin_2_gyroscope) {
          if (varargin_1_sonar_right == varargin_2_sonar_right) {
            e_p = ((varargin_1_sonar_front == varargin_2_sonar_front) &&
                   (varargin_1_sonar_left == varargin_2_sonar_left));
          } else {
            e_p = false;
          }
        } else {
          e_p = false;
        }
      } else {
        e_p = false;
      }
    } else {
      e_p = false;
    }
  } else {
    e_p = false;
  }

  if (e_p) {
    p = true;
  }

  return p;
}

/* Function for Chart: '<Root>/SupervisorB1' */
static void Board1_coherenceVerification(real32_T localStateSent_speed_motor1,
  real32_T localStateSent_speed_motor2, real32_T localStateSent_speed_motor3,
  real32_T localStateSent_speed_motor4, Temperature localStateSent_temperature,
  BatteryLevel localStateSent_batteryLevel, uint8_T
  localStateSent_sensorReadings, uint8_T localStateSent_deadlineOccurred,
  uint16_T localStateReceived_sonar_left, uint16_T
  localStateReceived_sonar_front, uint16_T localStateReceived_sonar_right,
  Gyroscope localStateReceived_gyroscope, int16_T
  localStateReceived_remoteContro, int16_T localStateReceived_remoteCont_0,
  uint16_T localStateReceived_remoteCont_1, uint8_T
  localStateReceived_sensorReadin, uint8_T localStateReceived_deadlineOccu,
  const BUS_LocalStateB1 globalStateReceived_localStateB, const BUS_LocalStateB2
  globalStateReceived_localStat_0, ENUM_Error *errB1, ENUM_Error *errB2)
{
  boolean_T p;
  boolean_T tmp;
  *errB1 = NO_ERROR;
  *errB2 = NO_ERROR;
  p = false;
  if (localStateSent_deadlineOccurred ==
      globalStateReceived_localStateB.deadlineOccurred) {
    if (localStateSent_sensorReadings ==
        globalStateReceived_localStateB.sensorReadings) {
      if (localStateSent_batteryLevel ==
          globalStateReceived_localStateB.batteryLevel) {
        if (localStateSent_temperature ==
            globalStateReceived_localStateB.temperature) {
          if (localStateSent_speed_motor4 ==
              globalStateReceived_localStateB.speed.motor4) {
            if (localStateSent_speed_motor3 ==
                globalStateReceived_localStateB.speed.motor3) {
              tmp = ((localStateSent_speed_motor2 ==
                      globalStateReceived_localStateB.speed.motor2) &&
                     (localStateSent_speed_motor1 ==
                      globalStateReceived_localStateB.speed.motor1));
            } else {
              tmp = false;
            }
          } else {
            tmp = false;
          }
        } else {
          tmp = false;
        }
      } else {
        tmp = false;
      }
    } else {
      tmp = false;
    }
  } else {
    tmp = false;
  }

  if (tmp) {
    p = true;
  }

  if (!p) {
    *errB1 = ERROR_PRESENT;
  }

  if (!Board1_isequal(localStateReceived_sonar_left,
                      localStateReceived_sonar_front,
                      localStateReceived_sonar_right,
                      localStateReceived_gyroscope,
                      localStateReceived_remoteContro,
                      localStateReceived_remoteCont_0,
                      localStateReceived_remoteCont_1,
                      localStateReceived_sensorReadin,
                      localStateReceived_deadlineOccu,
                      globalStateReceived_localStat_0.sonar.left,
                      globalStateReceived_localStat_0.sonar.front,
                      globalStateReceived_localStat_0.sonar.right,
                      globalStateReceived_localStat_0.gyroscope,
                      globalStateReceived_localStat_0.remoteController.y_lever,
                      globalStateReceived_localStat_0.remoteController.x_lever,
                      globalStateReceived_localStat_0.remoteController.buttons,
                      globalStateReceived_localStat_0.sensorReadings,
                      globalStateReceived_localStat_0.deadlineOccurred)) {
    *errB2 = ERROR_PRESENT;
  }
}

/* Function for Chart: '<Root>/SupervisorB1' */
static void Board1_ExchangeGlobalState(void)
{
  switch (Board1_DW.is_ExchangeGlobalState) {
   case Boar_IN_ComputingOwnGlobalState:
    /* Outport: '<Root>/tx_buffer' incorporates:
     *  Outport: '<Root>/board1GlobalState'
     */
    serializeGlobalState(&Board1_Y.tx_buffer[0], &Board1_Y.board1GlobalState);
    computeCRC(&Board1_Y.tx_buffer[0], Board1_DW.txPayload);
    Board1_DW.is_ExchangeGlobalState = Board1_IN_GL_Transmit;
    Board1_DW.is_GL_Transmit = Board1_IN_ReceivingRTR;
    break;

   case Board1_IN_GL_Receive:
    switch (Board1_DW.is_GL_Receive) {
     case Board1_IN_ArmingReceive:
      if (Board1_DW.receiveArmed == 1) {
        Board1_DW.is_GL_Receive = Board1_IN_ReadyToReceive;
        setRTR();
      }
      break;

     case Board1_IN_CheckCRC:
      switch (Board1_DW.flagCRC) {
       case 1:
        Board1_DW.is_GL_Receive = Board1_IN_SendAck;
        UART_SendAckIT();
        break;

       case 0:
        Board1_DW.is_GL_Receive = Board1_IN_SendNack;
        UART_SendNackIT();
        break;
      }
      break;

     case Board1_IN_R_ArmingReceive:
      if (Board1_DW.receiveArmed == 1) {
        Board1_DW.is_GL_Receive = Board1_IN_R_ReadyToReceive;
        setRTR();
      }
      break;

     case Board1_IN_R_CheckCRC:
      switch (Board1_DW.flagCRC) {
       case 1:
        Board1_DW.is_GL_Receive = Board1_IN_SendAck;
        UART_SendAckIT();
        break;

       case 0:
        Board1_DW.is_GL_Receive = Board1_IN_R_SendNack;
        UART_SendNackIT();
        break;
      }
      break;

     case Board1_IN_R_ReadyToReceive:
      if (errorReceived() == 1) {
        resetRTR();
        Board1_DW.is_GL_Receive = Board1_IN_R_SendNack;
        UART_SendNackIT();
      } else if (hasReceived() == 1) {
        Board1_DW.flagCRC = 0U;
        resetRTR();
        Board1_DW.is_GL_Receive = Board1_IN_R_CheckCRC;

        /* Inport: '<Root>/rx_buffer' */
        Board1_DW.flagCRC = compareCRC(&Board1_U.rx_buffer[0],
          Board1_DW.rxPayload);
      }
      break;

     case Board1_IN_R_SendNack:
      Board1_DW.is_GL_Receive = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_GL_Receive = 2U;
      break;

     case Board1_IN_ReadyToReceive:
      if (errorReceived() == 1) {
        resetRTR();
        Board1_DW.is_GL_Receive = Board1_IN_SendNack;
        UART_SendNackIT();
      } else if (hasReceived() == 1) {
        Board1_DW.flagCRC = 0U;
        resetRTR();
        Board1_DW.is_GL_Receive = Board1_IN_CheckCRC;

        /* Inport: '<Root>/rx_buffer' */
        Board1_DW.flagCRC = compareCRC(&Board1_U.rx_buffer[0],
          Board1_DW.rxPayload);
      }
      break;

     case Board1_IN_SendAck:
      Board1_DW.is_GL_Receive = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_GL_Receive = 3U;
      break;

     default:
      /* case IN_SendNack: */
      Board1_DW.is_GL_Receive = Board1_IN_R_ArmingReceive;

      /* Inport: '<Root>/rx_buffer' */
      Board1_DW.receiveArmed = UART_ReceiveIT(&Board1_U.rx_buffer[0], (uint64_T)
        (Board1_DW.rxPayload + ((uint8_T)CRC_SIZE)));
      Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
      break;
    }

    switch (Board1_DW.exit_port_index_GL_Receive) {
     case 2:
      Board1_DW.exit_port_index_GL_Receive = 0U;
      Board1_DW.is_ExchangeGlobalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeGlobalS = 2U;
      break;

     case 3:
      Board1_DW.exit_port_index_GL_Receive = 0U;

      /* Inport: '<Root>/rx_buffer' */
      deserializeGlobalState(&Board1_U.rx_buffer[0], Board1_DW.rxPayload,
        &Board1_DW.board2GlobalState);
      Board1_DW.is_ExchangeGlobalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeGlobalS = 3U;
      break;
    }
    break;

   default:
    /* case IN_GL_Transmit: */
    switch (Board1_DW.is_GL_Transmit) {
     case Board1_IN_R_ReceivingRTR:
      if (checkRTR() != 0) {
        Board1_DW.is_GL_Transmit = Board1_IN_R_Trasmit;
        UART_ReceiveAckIT();

        /* Outport: '<Root>/tx_buffer' */
        UART_TransmitIT(&Board1_Y.tx_buffer[0], (uint64_T)(Board1_DW.txPayload +
          ((uint8_T)CRC_SIZE)));
      } else {
        Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
      }
      break;

     case Board1_IN_R_Trasmit:
      Board1_DW.is_GL_Transmit = Board1_IN_R_WaitAck;
      break;

     case Board1_IN_R_WaitAck:
      if (hasReceived() == 1) {
        if (UART_CheckAck() == 0) {
          Board1_DW.is_GL_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_GL_Transmit = 2U;
        } else if (UART_CheckAck() == 1) {
          Board1_DW.is_GL_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_GL_Transmit = 3U;
        }
      }
      break;

     case Board1_IN_ReceivingRTR:
      if (checkRTR() != 0) {
        Board1_DW.is_GL_Transmit = Board1_IN_Trasmit;
        UART_ReceiveAckIT();

        /* Outport: '<Root>/tx_buffer' */
        UART_TransmitIT(&Board1_Y.tx_buffer[0], (uint64_T)(Board1_DW.txPayload +
          ((uint8_T)CRC_SIZE)));
      }
      break;

     case Board1_IN_Trasmit:
      Board1_DW.is_GL_Transmit = Board1_IN_WaitAck;
      break;

     default:
      /* case IN_WaitAck: */
      if (hasReceived() == 1) {
        if (UART_CheckAck() == 1) {
          Board1_DW.is_GL_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_GL_Transmit = 3U;
        } else if (UART_CheckAck() == 0) {
          Board1_DW.is_GL_Transmit = Board1_IN_R_ReceivingRTR;
          Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
        }
      }
      break;
    }

    switch (Board1_DW.exit_port_index_GL_Transmit) {
     case 2:
      Board1_DW.exit_port_index_GL_Transmit = 0U;
      Board1_DW.is_ExchangeGlobalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeGlobalS = 2U;
      break;

     case 3:
      Board1_DW.exit_port_index_GL_Transmit = 0U;
      Board1_DW.is_ExchangeGlobalState = Board1_IN_GL_Receive;
      Board1_DW.is_GL_Receive = Board1_IN_ArmingReceive;

      /* Inport: '<Root>/rx_buffer' */
      Board1_DW.receiveArmed = UART_ReceiveIT(&Board1_U.rx_buffer[0], (uint64_T)
        (Board1_DW.rxPayload + ((uint8_T)CRC_SIZE)));
      break;
    }
    break;
  }

  switch (Board1_DW.exit_port_index_ExchangeGlobalS) {
   case 2:
    Board1_DW.exit_port_index_ExchangeGlobalS = 0U;
    Board1_DW.is_CommunicationPhase = IN_UpdateCommunicationCycleStat;
    Board1_DW.commCycleStatus = CYCLE_FAIL;
    break;

   case 3:
    Board1_DW.exit_port_index_ExchangeGlobalS = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_ComputeDecision;

    /*  Entry compute decision */
    Board1_DW.is_ComputeDecision = B_IN_StateCoherenceVerification;

    /* Outport: '<Root>/board1GlobalState' */
    Board1_coherenceVerification(Board1_DW.board1LocalState.speed.motor1,
      Board1_DW.board1LocalState.speed.motor2,
      Board1_DW.board1LocalState.speed.motor3,
      Board1_DW.board1LocalState.speed.motor4,
      Board1_DW.board1LocalState.temperature,
      Board1_DW.board1LocalState.batteryLevel,
      Board1_DW.board1LocalState.sensorReadings,
      Board1_DW.board1LocalState.deadlineOccurred,
      Board1_DW.board2LocalState.sonar.left,
      Board1_DW.board2LocalState.sonar.front,
      Board1_DW.board2LocalState.sonar.right,
      Board1_DW.board2LocalState.gyroscope,
      Board1_DW.board2LocalState.remoteController.y_lever,
      Board1_DW.board2LocalState.remoteController.x_lever,
      Board1_DW.board2LocalState.remoteController.buttons,
      Board1_DW.board2LocalState.sensorReadings,
      Board1_DW.board2LocalState.deadlineOccurred,
      Board1_Y.board1GlobalState.localStateB1,
      Board1_Y.board1GlobalState.localStateB2, &Board1_B.errorB1,
      &Board1_B.errorB2);
    break;
  }
}

/* Function for Chart: '<Root>/SupervisorB1' */
static ENUM_Error Board1_validateSensorReadings(uint8_T sensorReadings, real_T
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

/* Function for Chart: '<Root>/SupervisorB1' */
static ENUM_Error Board1_validateRTOSHealth(uint8_T deadlineMissed)
{
  ENUM_Error resultBoardHealth;
  if (deadlineMissed == 1) {
    resultBoardHealth = ERROR_PRESENT;
  } else {
    resultBoardHealth = NO_ERROR;
  }

  return resultBoardHealth;
}

/* Function for Chart: '<Root>/SupervisorB1' */
static void Board1_ExchangeLocalState(void)
{
  switch (Board1_DW.is_ExchangeLocalState) {
   case Board1_IN_LS_Receive:
    switch (Board1_DW.is_LS_Receive) {
     case Board1_IN_ArmingReceive:
      if (Board1_DW.receiveArmed == 1) {
        Board1_DW.is_LS_Receive = Board1_IN_ReadyToReceive;
        setRTR();
      }
      break;

     case Board1_IN_CheckCRC:
      switch (Board1_DW.flagCRC) {
       case 1:
        Board1_DW.is_LS_Receive = Board1_IN_SendAck;
        UART_SendAckIT();
        break;

       case 0:
        Board1_DW.is_LS_Receive = Board1_IN_SendNack;
        UART_SendNackIT();
        break;
      }
      break;

     case Board1_IN_R_ArmingReceive:
      if (Board1_DW.receiveArmed == 1) {
        Board1_DW.is_LS_Receive = Board1_IN_R_ReadyToReceive;
        setRTR();
      }
      break;

     case Board1_IN_R_CheckCRC:
      switch (Board1_DW.flagCRC) {
       case 1:
        Board1_DW.is_LS_Receive = Board1_IN_SendAck;
        UART_SendAckIT();
        break;

       case 0:
        Board1_DW.is_LS_Receive = Board1_IN_R_SendNack;
        UART_SendNackIT();
        break;
      }
      break;

     case Board1_IN_R_ReadyToReceive:
      if (errorReceived() == 1) {
        resetRTR();
        Board1_DW.is_LS_Receive = Board1_IN_R_SendNack;
        UART_SendNackIT();
      } else if (hasReceived() == 1) {
        Board1_DW.flagCRC = 0U;
        resetRTR();
        Board1_DW.is_LS_Receive = Board1_IN_R_CheckCRC;

        /* Inport: '<Root>/rx_buffer' */
        Board1_DW.flagCRC = compareCRC(&Board1_U.rx_buffer[0],
          Board1_DW.rxPayload);
      }
      break;

     case Board1_IN_R_SendNack:
      Board1_DW.is_LS_Receive = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_LS_Receive = 2U;
      break;

     case Board1_IN_ReadyToReceive:
      if (errorReceived() == 1) {
        resetRTR();
        Board1_DW.is_LS_Receive = Board1_IN_SendNack;
        UART_SendNackIT();
      } else if (hasReceived() == 1) {
        Board1_DW.flagCRC = 0U;
        resetRTR();
        Board1_DW.is_LS_Receive = Board1_IN_CheckCRC;

        /* Inport: '<Root>/rx_buffer' */
        Board1_DW.flagCRC = compareCRC(&Board1_U.rx_buffer[0],
          Board1_DW.rxPayload);
      }
      break;

     case Board1_IN_SendAck:
      Board1_DW.is_LS_Receive = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_LS_Receive = 3U;
      break;

     default:
      /* case IN_SendNack: */
      Board1_DW.is_LS_Receive = Board1_IN_R_ArmingReceive;

      /* Inport: '<Root>/rx_buffer' */
      Board1_DW.receiveArmed = UART_ReceiveIT(&Board1_U.rx_buffer[0], (uint64_T)
        (Board1_DW.rxPayload + ((uint8_T)CRC_SIZE)));
      Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
      break;
    }

    switch (Board1_DW.exit_port_index_LS_Receive) {
     case 2:
      Board1_DW.exit_port_index_LS_Receive = 0U;
      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeLocalSt = 3U;
      break;

     case 3:
      Board1_DW.exit_port_index_LS_Receive = 0U;

      /* Inport: '<Root>/rx_buffer' */
      deserializeLocalStateB2(&Board1_U.rx_buffer[0], Board1_DW.rxPayload,
        &Board1_DW.board2LocalState);
      Board1_DW.is_ExchangeLocalState = IN_ValidateReceivedSensorReadin;
      Board1_B.errorB1 = Board1_validateSensorReadings
        (Board1_DW.board1LocalState.sensorReadings, 7.0);
      Board1_B.errorB2 = Board1_validateSensorReadings
        (Board1_DW.board2LocalState.sensorReadings, 7.0);
      break;
    }
    break;

   case Board1_IN_LS_Transmit:
    switch (Board1_DW.is_LS_Transmit) {
     case Board1_IN_R_ReceivingRTR:
      if (checkRTR() != 0) {
        Board1_DW.is_LS_Transmit = Board1_IN_R_Trasmit;
        UART_ReceiveAckIT();

        /* Outport: '<Root>/tx_buffer' */
        UART_TransmitIT(&Board1_Y.tx_buffer[0], (uint64_T)(Board1_DW.txPayload +
          ((uint8_T)CRC_SIZE)));
      } else {
        Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
      }
      break;

     case Board1_IN_R_Trasmit:
      Board1_DW.is_LS_Transmit = Board1_IN_R_WaitAck;
      break;

     case Board1_IN_R_WaitAck:
      if (hasReceived() == 1) {
        if (UART_CheckAck() == 0) {
          Board1_DW.is_LS_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_LS_Transmit = 2U;
        } else if (UART_CheckAck() == 1) {
          Board1_DW.is_LS_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_LS_Transmit = 3U;
        }
      }
      break;

     case Board1_IN_ReceivingRTR:
      if (checkRTR() != 0) {
        Board1_DW.is_LS_Transmit = Board1_IN_Trasmit;
        UART_ReceiveAckIT();

        /* Outport: '<Root>/tx_buffer' */
        UART_TransmitIT(&Board1_Y.tx_buffer[0], (uint64_T)(Board1_DW.txPayload +
          ((uint8_T)CRC_SIZE)));
      }
      break;

     case Board1_IN_Trasmit:
      Board1_DW.is_LS_Transmit = Board1_IN_WaitAck;
      break;

     default:
      /* case IN_WaitAck: */
      if (hasReceived() == 1) {
        if (UART_CheckAck() == 1) {
          Board1_DW.is_LS_Transmit = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_LS_Transmit = 3U;
        } else if (UART_CheckAck() == 0) {
          Board1_DW.is_LS_Transmit = Board1_IN_R_ReceivingRTR;
          Board1_DW.commCycleStatus = CYCLE_OK_DIRTY;
        }
      }
      break;
    }

    switch (Board1_DW.exit_port_index_LS_Transmit) {
     case 2:
      Board1_DW.exit_port_index_LS_Transmit = 0U;
      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeLocalSt = 3U;
      break;

     case 3:
      Board1_DW.exit_port_index_LS_Transmit = 0U;
      Board1_DW.is_ExchangeLocalState = Board1_IN_LS_Receive;
      resetRTR();
      Board1_DW.is_LS_Receive = Board1_IN_ArmingReceive;

      /* Inport: '<Root>/rx_buffer' */
      Board1_DW.receiveArmed = UART_ReceiveIT(&Board1_U.rx_buffer[0], (uint64_T)
        (Board1_DW.rxPayload + ((uint8_T)CRC_SIZE)));
      break;
    }
    break;

   case IN_ValidateReceivedSensorReadin:
    if ((Board1_B.errorB1 == NO_ERROR) && (Board1_B.errorB2 == NO_ERROR)) {
      Board1_DW.is_ExchangeLocalState = Board1_IN_checkRTOSHealth;
      Board1_B.errorB1 = Board1_validateRTOSHealth
        (Board1_DW.board1LocalState.deadlineOccurred);
      Board1_B.errorB2 = Board1_validateRTOSHealth
        (Board1_DW.board2LocalState.deadlineOccurred);
    } else {
      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeLocalSt = 2U;
    }
    break;

   default:
    /* case IN_checkRTOSHealth: */
    if ((Board1_B.errorB1 == NO_ERROR) && (Board1_B.errorB2 == NO_ERROR)) {
      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeLocalSt = 4U;
    } else {
      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.exit_port_index_ExchangeLocalSt = 2U;
    }
    break;
  }

  switch (Board1_DW.exit_port_index_ExchangeLocalSt) {
   case 2:
    Board1_DW.exit_port_index_ExchangeLocalSt = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_ErrorStateDecision;
    Board1_DW.is_ErrorStateDecision = Board1_IN_UpdateRoverState;

    /* ModelReference: '<Root>/BoardsHealth' */
    BoardsHealth_UpdateBoardsStatus(&Board1_B.errorB1, &Board1_B.errorB2,
      &Board1_B.StatusBoard1, &Board1_B.StatusBoard2);
    break;

   case 3:
    Board1_DW.exit_port_index_ExchangeLocalSt = 0U;
    Board1_DW.is_CommunicationPhase = IN_UpdateCommunicationCycleStat;
    Board1_DW.commCycleStatus = CYCLE_FAIL;
    break;

   case 4:
    Board1_DW.exit_port_index_ExchangeLocalSt = 0U;
    Board1_DW.is_CommunicationPhase = Board1_IN_ExchangeGlobalState;

    /*  Entry exchange global state */
    Board1_DW.txPayload = ((uint8_T)GLOBAL_STATE_FRAME_SIZE);
    Board1_DW.rxPayload = ((uint8_T)GLOBAL_STATE_FRAME_SIZE);
    Board1_DW.is_ExchangeGlobalState = Boar_IN_ComputingOwnGlobalState;

    /* Outport: '<Root>/board1GlobalState' */
    Board1_Y.board1GlobalState.localStateB1 = Board1_DW.board1LocalState;
    Board1_Y.board1GlobalState.localStateB2 = Board1_DW.board2LocalState;
    break;
  }
}

/* Function for Chart: '<Root>/SupervisorB1' */
static void exit_internal_CommunicationPhas(void)
{
  switch (Board1_DW.is_CommunicationPhase) {
   case Board1_IN_ComputeDecision:
    if (Board1_DW.is_ComputeDecision == Board1_IN_UpdateBoardsHealth) {
      /* Outport: '<Root>/board1Decision' */
      Board1_Y.board1Decision.roverState = Board1_convertInENUMRoverStatus
        (Board1_B.StatusBoard1, Board1_B.StatusBoard2);
      Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
    } else {
      Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
    }

    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    break;

   case Board1_IN_ErrorStateDecision:
    if (Board1_DW.is_ErrorStateDecision == Board1_IN_UpdateRoverState) {
      /* Outport: '<Root>/board1Decision' */
      Board1_Y.board1Decision.roverState = Board1_convertInENUMRoverStatus
        (Board1_B.StatusBoard1, Board1_B.StatusBoard2);
      Board1_DW.is_ErrorStateDecision = Board1_IN_NO_ACTIVE_CHILD;
    } else {
      Board1_DW.is_ErrorStateDecision = Board1_IN_NO_ACTIVE_CHILD;
    }

    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    break;

   case Board1_IN_ExchangeDecision:
    if (Board1_DW.is_ExchangeDecision == Board1_IN_D_Receive) {
      switch (Board1_DW.is_D_Receive) {
       case Board1_IN_R_ReadyToReceive:
        resetRTR();
        Board1_DW.is_D_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;

       case Board1_IN_ReadyToReceive:
        resetRTR();
        Board1_DW.is_D_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;

       default:
        Board1_DW.is_D_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;
      }

      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
    } else {
      Board1_DW.is_D_Transmit = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.is_ExchangeDecision = Board1_IN_NO_ACTIVE_CHILD;
    }

    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    break;

   case Board1_IN_ExchangeGlobalState:
    if (Board1_DW.is_ExchangeGlobalState == Board1_IN_GL_Receive) {
      switch (Board1_DW.is_GL_Receive) {
       case Board1_IN_R_ReadyToReceive:
        resetRTR();
        Board1_DW.is_GL_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;

       case Board1_IN_ReadyToReceive:
        resetRTR();
        Board1_DW.is_GL_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;

       default:
        Board1_DW.is_GL_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;
      }

      Board1_DW.is_ExchangeGlobalState = Board1_IN_NO_ACTIVE_CHILD;
    } else {
      Board1_DW.is_GL_Transmit = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.is_ExchangeGlobalState = Board1_IN_NO_ACTIVE_CHILD;
    }

    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    break;

   case Board1_IN_ExchangeLocalState:
    if (Board1_DW.is_ExchangeLocalState == Board1_IN_LS_Receive) {
      switch (Board1_DW.is_LS_Receive) {
       case Board1_IN_R_ReadyToReceive:
        resetRTR();
        Board1_DW.is_LS_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;

       case Board1_IN_ReadyToReceive:
        resetRTR();
        Board1_DW.is_LS_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;

       default:
        Board1_DW.is_LS_Receive = Board1_IN_NO_ACTIVE_CHILD;
        break;
      }

      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
    } else {
      Board1_DW.is_LS_Transmit = Board1_IN_NO_ACTIVE_CHILD;
      Board1_DW.is_ExchangeLocalState = Board1_IN_NO_ACTIVE_CHILD;
    }

    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    break;

   default:
    Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Model step function */
void Board1_step(void)
{
  uint8_T timeoutOccurred_prev;

  /* Chart: '<Root>/SupervisorB1' incorporates:
   *  Inport: '<Root>/areSensorsValid'
   *  Inport: '<Root>/batteryLevel'
   *  Inport: '<Root>/deadlineOccurred'
   *  Inport: '<Root>/speed'
   *  Inport: '<Root>/temperature'
   *  Inport: '<Root>/timeoutOccurred'
   *  Outport: '<Root>/board1Decision'
   *  Outport: '<Root>/board1GlobalState'
   *  Outport: '<Root>/tx_buffer'
   */
  timeoutOccurred_prev = Board1_DW.timeoutOccurred_start;
  Board1_DW.timeoutOccurred_start = Board1_U.timeoutOccurred;
  if (Board1_DW.is_active_c15_Board1 == 0U) {
    Board1_DW.is_active_c15_Board1 = 1U;
    Board1_Y.board1Decision.actuator = BOARD1;
    Board1_B.previousUserAction = UA_NONE;
    Board1_DW.previousButtons = 0U;
    Board1_DW.previousWhiteLeftLed = WHITE_OFF;
    Board1_DW.previousWhiteRightLed = WHITE_OFF;
    Board1_DW.is_RoverState = Board1_IN_NotCommunicating;

    /* Outport: '<Root>/supervision_ended' incorporates:
     *  Outport: '<Root>/board1Decision'
     */
    Board1_Y.supervision_ended = 0U;
  } else {
    switch (Board1_DW.is_RoverState) {
     case Board1_IN_CommunicationPhase:
      /* Timeout, aggiorno come � andato il ciclo
         e vedo se si � rotto il link */
      if (timeoutOccurred_prev != Board1_DW.timeoutOccurred_start) {
        Board1_DW.commCycleStatus = CYCLE_FAIL;

        /* Il link potrebbe essere degradato oppure ok */
        exit_internal_CommunicationPhas();
        Board1_DW.is_RoverState = IN_UpdateCommunicationLinkHealt;
        Board1_B.cycleResult = Board1_DW.commCycleStatus;

        /* ModelReference: '<Root>/Model' */
        C_UpdateCommunicationLinkHealth(&Board1_B.cycleResult,
          &Board1_B.communicationLinkHealth);
      } else {
        switch (Board1_DW.is_CommunicationPhase) {
         case Board1_IN_ComputeDecision:
          switch (Board1_DW.is_ComputeDecision) {
           case Board1_IN_CheckBatteryHealth:
            if (Board1_Y.board1GlobalState.localStateB1.batteryLevel <= 23) {
              Board1_B.errorB1 = ERROR_PRESENT;
              Board1_B.errorB2 = ERROR_PRESENT;
              Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
              Board1_DW.exit_port_index_ComputeDecision = 2U;
            } else {
              Board1_DW.is_ComputeDecision = Board1_IN_CheckMotorsHealth;

              /* ModelReference: '<Root>/MotorsHealth' incorporates:
               *  Outport: '<Root>/board1Decision'
               */
              MotorsHealth_UpdateMotorsHealth(&Board1_Y.board1Decision.setPoint,
                &Board1_Y.board1GlobalState.localStateB1.speed,
                &Board1_B.pidMode, &Board1_B.motorsHealth,
                &Board1_B.LF_HealthMotor, &Board1_B.LR_HealthMotor,
                &Board1_B.RF_HealthMotor, &Board1_B.RR_HealthMotor);
            }
            break;

           case Board1_IN_CheckMotorsHealth:
            if (Board1_B.motorsHealth == MOTORS_NOT_OK) {
              Board1_B.errorB1 = ERROR_PRESENT;
              Board1_B.errorB2 = ERROR_PRESENT;

              /* Caso in cui i motori non seguono il setpoint */
              Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
              Board1_DW.exit_port_index_ComputeDecision = 2U;
            } else {
              Board1_DW.is_ComputeDecision = IN_CheckRoverTemperatureHealth;

              /* ModelReference: '<Root>/RoverTemperatureHealth' incorporates:
               *  Outport: '<Root>/board1GlobalState'
               */
              Ro_UpdateRoverTemperatureHealth
                (&Board1_Y.board1GlobalState.localStateB1.temperature,
                 &Board1_B.roverTemperatureHealth);
            }
            break;

           case IN_CheckRoverTemperatureHealth:
            if (Board1_B.roverTemperatureHealth == TEMPERATURE_NOT_OK) {
              Board1_B.errorB1 = ERROR_PRESENT;
              Board1_B.errorB2 = ERROR_PRESENT;

              /* Caso in cui la temperatura interna del rover supera la soglia per x tempo */
              Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
              Board1_DW.exit_port_index_ComputeDecision = 2U;
            } else {
              /* Non ci sono stati errori
                 Lettura sensori e coerenza dei valori OK
                 Motori OK
                 Temperatura OK */
              Board1_DW.is_ComputeDecision = Board1_IN_UpdateBoardsHealth;

              /* ModelReference: '<Root>/BoardsHealth' */
              BoardsHealth_UpdateBoardsStatus(&Board1_B.errorB1,
                &Board1_B.errorB2, &Board1_B.StatusBoard1,
                &Board1_B.StatusBoard2);
            }
            break;

           case Board_IN_EmergencyStateAnalysis:
            if ((Board1_B.errorB1 == NO_ERROR) && (Board1_B.errorB2 == NO_ERROR))
            {
              Board1_DW.is_ComputeDecision = Board1_IN_CheckBatteryHealth;
            } else {
              Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
              Board1_DW.exit_port_index_ComputeDecision = 2U;
            }
            break;

           case Board1_IN_LightEvaluation:
            Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
            Board1_DW.exit_port_index_ComputeDecision = 3U;
            break;

           case Board_IN_RoverActionComputation:
            Board1_DW.is_ComputeDecision = Board1_IN_LightEvaluation;
            Board1_Y.board1Decision.leds.white.left = Board1_evaluateLed
              (Board1_Y.board1GlobalState.localStateB2.remoteController.buttons,
               Board1_DW.previousButtons, Board1_DW.previousWhiteLeftLed,
               ((uint16_T)WHITE_LEFT_LED_MASK));
            Board1_Y.board1Decision.leds.white.right = Board1_evaluateLed
              (Board1_Y.board1GlobalState.localStateB2.remoteController.buttons,
               Board1_DW.previousButtons, Board1_DW.previousWhiteRightLed,
               ((uint16_T)WHITE_RIGHT_LED_MASK));

            /*  Aggiornamento variabili di stato */
            Board1_DW.previousButtons =
              Board1_Y.board1GlobalState.localStateB2.remoteController.buttons;
            Board1_DW.previousWhiteLeftLed =
              Board1_Y.board1Decision.leds.white.left;
            Board1_DW.previousWhiteRightLed =
              Board1_Y.board1Decision.leds.white.right;
            break;

           case B_IN_StateCoherenceVerification:
            if ((Board1_B.errorB1 == NO_ERROR) && (Board1_B.errorB2 == NO_ERROR))
            {
              Board1_DW.is_ComputeDecision = Board_IN_EmergencyStateAnalysis;
              Board1_emergencyCheck
                (Board1_Y.board1GlobalState.localStateB1.speed.motor1,
                 Board1_Y.board1GlobalState.localStateB1.speed.motor2,
                 Board1_Y.board1GlobalState.localStateB1.speed.motor3,
                 Board1_Y.board1GlobalState.localStateB1.speed.motor4,
                 Board1_Y.board1GlobalState.localStateB1.temperature,
                 Board1_Y.board1GlobalState.localStateB1.batteryLevel,
                 Board1_Y.board1GlobalState.localStateB2.sonar.left,
                 Board1_Y.board1GlobalState.localStateB2.sonar.front,
                 Board1_Y.board1GlobalState.localStateB2.sonar.right,
                 Board1_Y.board1GlobalState.localStateB2.gyroscope,
                 Board1_Y.board1GlobalState.localStateB2.remoteController.y_lever,
                 Board1_Y.board1GlobalState.localStateB2.remoteController.x_lever,
                 &Board1_B.errorB1, &Board1_B.errorB2);
            } else {
              Board1_DW.is_ComputeDecision = Board1_IN_NO_ACTIVE_CHILD;
              Board1_DW.exit_port_index_ComputeDecision = 2U;
            }
            break;

           case Board1_IN_UpdateBoardsHealth:
            Board1_Y.board1Decision.roverState = Board1_convertInENUMRoverStatus
              (Board1_B.StatusBoard1, Board1_B.StatusBoard2);
            Board1_DW.is_ComputeDecision = Board1_IN_UserActionComputation;
            Board1_Y.board1Decision.userAction = Board1_computeUserAction
              (Board1_Y.board1GlobalState.localStateB2.remoteController.x_lever,
               Board1_Y.board1GlobalState.localStateB2.remoteController.y_lever,
               Board1_Y.board1GlobalState.localStateB2.remoteController.buttons,
               ((uint16_T)BRAKING_HARD_MASK), ((uint16_T)BRAKING_SMOOTH_MASK));
            Board1_B.previousUserAction = Board1_Y.board1Decision.userAction;
            break;

           default:
            /* case IN_UserActionComputation: */
            Board1_DW.is_ComputeDecision = Board_IN_RoverActionComputation;

            /* ModelReference: '<Root>/ActionsModel' incorporates:
             *  Outport: '<Root>/board1GlobalState'
             */
            ActionsModel_ComputeRoverAction(&Board1_B.previousUserAction,
              &Board1_Y.board1GlobalState.localStateB1.speed,
              &Board1_Y.board1GlobalState.localStateB2.remoteController.x_lever,
              &Board1_Y.board1GlobalState.localStateB2.remoteController.y_lever,
              &Board1_Y.board1GlobalState.localStateB2.gyroscope,
              &Board1_Y.board1GlobalState.localStateB2.sonar, &Board1_B.setPoint,
              &Board1_B.roverAction, &Board1_B.safeAction, &Board1_B.redLeds,
              &Board1_B.pidMode);
            Board1_Y.board1Decision.roverAction = Board1_B.roverAction;
            Board1_Y.board1Decision.safeAction = Board1_B.safeAction;
            Board1_Y.board1Decision.setPoint = Board1_B.setPoint;

            /*  Light update */
            Board1_Y.board1Decision.leds.red = Board1_B.redLeds;
            break;
          }

          switch (Board1_DW.exit_port_index_ComputeDecision) {
           case 2:
            Board1_DW.exit_port_index_ComputeDecision = 0U;
            Board1_DW.is_CommunicationPhase = Board1_IN_ErrorStateDecision;
            Board1_DW.is_ErrorStateDecision = Board1_IN_UpdateRoverState;

            /* ModelReference: '<Root>/BoardsHealth' */
            BoardsHealth_UpdateBoardsStatus(&Board1_B.errorB1, &Board1_B.errorB2,
              &Board1_B.StatusBoard1, &Board1_B.StatusBoard2);
            break;

           case 3:
            Board1_DW.exit_port_index_ComputeDecision = 0U;
            Board1_DW.is_CommunicationPhase = Board1_IN_ExchangeDecision;

            /*  Entry exchange decision */
            Board1_DW.txPayload = ((uint8_T)DECISION_FRAME_SIZE);
            Board1_DW.rxPayload = ((uint8_T)DECISION_FRAME_SIZE);
            serializeDecision(&Board1_Y.tx_buffer[0], &Board1_Y.board1Decision);
            computeCRC(&Board1_Y.tx_buffer[0], Board1_DW.txPayload);
            Board1_DW.is_ExchangeDecision = Board1_IN_D_Transmit;
            Board1_DW.is_D_Transmit = Board1_IN_ReceivingRTR;
            break;
          }
          break;

         case Board1_IN_ErrorStateDecision:
          switch (Board1_DW.is_ErrorStateDecision) {
           case Board1_IN_DegradedCase:
            Board1_DW.is_ErrorStateDecision = Board1_IN_NO_ACTIVE_CHILD;
            Board1_DW.exit_port_index_ErrorStateDecis = 2U;
            break;

           case Board1_IN_EmergencyCase:
            Board1_DW.is_ErrorStateDecision = Board1_IN_NO_ACTIVE_CHILD;
            Board1_DW.exit_port_index_ErrorStateDecis = 2U;
            break;

           case Board1_IN_UpdateDecision:
            switch (Board1_Y.board1Decision.roverState) {
             case FAULTY_B1_DEGRADED_B2:
              Board1_DW.is_ErrorStateDecision = Board1_IN_DegradedCase;
              Board1_Y.board1Decision.actuator = BOARD2;
              break;

             case EMERGENCY:
              Board1_DW.is_ErrorStateDecision = Board1_IN_EmergencyCase;

              /* CHI DEVE ATTUARE? */
              Board1_Y.board1Decision.safeAction = SA_BRAKING_HARD;
              Board1_Y.board1Decision.roverAction = RA_BRAKING_HARD;
              Board1_Y.board1Decision.userAction = UA_BRAKING_HARD;
              Board1_Y.board1Decision.setPoint.leftAxis = 0.0F;
              Board1_Y.board1Decision.setPoint.rightAxis = 0.0F;
              break;

             default:
              Board1_DW.is_ErrorStateDecision = Board1_IN_NO_ACTIVE_CHILD;
              Board1_DW.exit_port_index_ErrorStateDecis = 2U;
              break;
            }
            break;

           default:
            /* case IN_UpdateRoverState: */
            Board1_Y.board1Decision.roverState = Board1_convertInENUMRoverStatus
              (Board1_B.StatusBoard1, Board1_B.StatusBoard2);
            Board1_DW.is_ErrorStateDecision = Board1_IN_UpdateDecision;

            /*  printRoverState(board1Decision); */
            Board1_Y.board1Decision.leds.red.left = RED_BLINKING;
            Board1_Y.board1Decision.leds.red.right =
              Board1_Y.board1Decision.leds.red.left;
            break;
          }

          if (Board1_DW.exit_port_index_ErrorStateDecis == 2U) {
            Board1_DW.exit_port_index_ErrorStateDecis = 0U;
            Board1_DW.is_CommunicationPhase = Board1_IN_ExchangeDecision;

            /*  Entry exchange decision */
            Board1_DW.txPayload = ((uint8_T)DECISION_FRAME_SIZE);
            Board1_DW.rxPayload = ((uint8_T)DECISION_FRAME_SIZE);
            serializeDecision(&Board1_Y.tx_buffer[0], &Board1_Y.board1Decision);
            computeCRC(&Board1_Y.tx_buffer[0], Board1_DW.txPayload);
            Board1_DW.is_ExchangeDecision = Board1_IN_D_Transmit;
            Board1_DW.is_D_Transmit = Board1_IN_ReceivingRTR;
          }
          break;

         case Board1_IN_ExchangeDecision:
          Board1_ExchangeDecision();
          break;

         case Board1_IN_ExchangeGlobalState:
          Board1_ExchangeGlobalState();
          break;

         case Board1_IN_ExchangeLocalState:
          Board1_ExchangeLocalState();
          break;

         default:
          /* case IN_UpdateCommunicationCycleStatus: */
          Board1_DW.is_CommunicationPhase = Board1_IN_NO_ACTIVE_CHILD;
          Board1_DW.exit_port_index_CommunicationPh = 5U;
          break;
        }

        switch (Board1_DW.exit_port_index_CommunicationPh) {
         case 2:
          Board1_DW.exit_port_index_CommunicationPh = 0U;
          Board1_DW.is_RoverState = Board1_IN_Degraded;
          enterDegraded();
          break;

         case 3:
          Board1_DW.exit_port_index_CommunicationPh = 0U;
          Board1_DW.is_RoverState = Board1_IN_Emergency;
          enterEmergency();
          break;

         case 4:
          Board1_DW.exit_port_index_CommunicationPh = 0U;
          Board1_DW.is_RoverState = Board1_IN_Faulty;
          enterFaulty();
          break;

         case 5:
          Board1_DW.exit_port_index_CommunicationPh = 0U;

          /* Il link potrebbe essere degradato oppure ok */
          Board1_DW.is_RoverState = IN_UpdateCommunicationLinkHealt;
          Board1_B.cycleResult = Board1_DW.commCycleStatus;

          /* ModelReference: '<Root>/Model' */
          C_UpdateCommunicationLinkHealth(&Board1_B.cycleResult,
            &Board1_B.communicationLinkHealth);
          break;
        }
      }
      break;

     case Board1_IN_Degraded:
     case Board1_IN_Emergency:
     case Board1_IN_Faulty:
     case Board1_IN_Idle:
      break;

     case Board1_IN_NotCommunicating:
      /* Outport: '<Root>/supervision_ended' */
      Board1_Y.supervision_ended = 0U;
      Board1_DW.board1LocalState.speed = Board1_U.speed;
      Board1_DW.board1LocalState.temperature = Board1_U.temperature;
      Board1_DW.board1LocalState.batteryLevel = Board1_U.batteryLevel;
      Board1_DW.board1LocalState.sensorReadings = Board1_U.areSensorsValid;
      Board1_DW.board1LocalState.deadlineOccurred = Board1_U.deadlineOccurred;
      Board1_DW.is_RoverState = Board1_IN_CommunicationPhase;
      Board1_DW.commCycleStatus = CYCLE_OK_CLEAN;
      setRTR();
      Board1_DW.is_CommunicationPhase = Board1_IN_ExchangeLocalState;

      /*  Entry exchange local state */
      Board1_DW.txPayload = ((uint8_T)LOCAL_STATE_B1_FRAME_SIZE);
      Board1_DW.rxPayload = ((uint8_T)LOCAL_STATE_B2_FRAME_SIZE);
      serializeLocalStateB1(&Board1_Y.tx_buffer[0], &Board1_DW.board1LocalState);
      computeCRC(&Board1_Y.tx_buffer[0], Board1_DW.txPayload);
      Board1_DW.is_ExchangeLocalState = Board1_IN_LS_Transmit;
      Board1_DW.is_LS_Transmit = Board1_IN_ReceivingRTR;
      break;

     case Board1_IN_SupervisionEnded:
      Board1_DW.is_RoverState = Board1_IN_NotCommunicating;

      /* Outport: '<Root>/supervision_ended' */
      Board1_Y.supervision_ended = 0U;
      break;

     default:
      /* case IN_UpdateCommunicationLinkHealth: */
      if (Board1_B.communicationLinkHealth == LINK_LOST) {
        Board1_DW.is_RoverState = Board1_IN_Idle;
        enterEmergency();
      } else {
        Board1_DW.is_RoverState = Board1_IN_SupervisionEnded;

        /* Outport: '<Root>/supervision_ended' */
        Board1_Y.supervision_ended = 1U;

        /* printGlobalState(board1GlobalState); printGlobalState(board2GlobalState);
           printDecision(board1Decision); printDecision(board2Decision); */
      }
      break;
    }
  }

  /* End of Chart: '<Root>/SupervisorB1' */
}

/* Model initialize function */
void Board1_initialize(void)
{
  /* Model Initialize function for ModelReference Block: '<Root>/ActionsModel' */
  ActionsModel_initialize(rtmGetErrorStatusPointer(Board1_M));

  /* Model Initialize function for ModelReference Block: '<Root>/BoardsHealth' */
  BoardsHealth_initialize(rtmGetErrorStatusPointer(Board1_M));

  /* Model Initialize function for ModelReference Block: '<Root>/Model' */
  CommunicationLinkHea_initialize(rtmGetErrorStatusPointer(Board1_M));

  /* Model Initialize function for ModelReference Block: '<Root>/MotorsHealth' */
  MotorsHealth_initialize(rtmGetErrorStatusPointer(Board1_M));

  /* Model Initialize function for ModelReference Block: '<Root>/RedLedsActuation' */
  RedLedsActuation_initialize(rtmGetErrorStatusPointer(Board1_M));

  /* Model Initialize function for ModelReference Block: '<Root>/RoverTemperatureHealth' */
  RoverTemperatureHeal_initialize(rtmGetErrorStatusPointer(Board1_M));

  /* SystemInitialize for ModelReference: '<Root>/RedLedsActuation' incorporates:
   *  Outport: '<Root>/board1Decision'
   */
  RedLedsActuation_Init();

  /* SystemInitialize for ModelReference: '<Root>/ActionsModel' incorporates:
   *  Outport: '<Root>/board1GlobalState'
   */
  ActionsModel_Init(&Board1_B.setPoint, &Board1_B.roverAction, &Board1_B.redLeds);

  /* SystemInitialize for ModelReference: '<Root>/BoardsHealth' */
  BoardsHealth_Init();

  /* SystemInitialize for ModelReference: '<Root>/Model' */
  CommunicationLinkHealth_Init();

  /* SystemInitialize for ModelReference: '<Root>/MotorsHealth' incorporates:
   *  Outport: '<Root>/board1Decision'
   *  Outport: '<Root>/board1GlobalState'
   */
  MotorsHealth_Init();

  /* SystemInitialize for ModelReference: '<Root>/RoverTemperatureHealth' incorporates:
   *  Outport: '<Root>/board1GlobalState'
   */
  RoverTemperatureHealth_Init();
}

/* Model terminate function */
void Board1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
