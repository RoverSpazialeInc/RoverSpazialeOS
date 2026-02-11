/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board2.h
 *
 * Code generated for Simulink model 'Board2'.
 *
 * Model version                  : 13.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 20:24:40 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Board2_h_
#define Board2_h_
#ifndef Board2_COMMON_INCLUDES_
#define Board2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Board2_COMMON_INCLUDES_ */

#include "Board2_types.h"
#include "sensors.h"
#include "states.h"
#include "decision.h"
#include "decision_enums.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

/* user code (top of header file) */
#include "controller_masks.h"
#include "serialize.h"
#include "deserialize.h"
#include "comparator.h"
#include "crc_functions.h"
#include "uart_functions.h"
#include "freeRTOS_functions.h"

/* Block signals (default storage) */
typedef struct {
  BUS_SetPoint setPoint;               /* '<Root>/ActionsModel' */
  BUS_RedLeds redLeds;                 /* '<Root>/ActionsModel' */
  ENUM_UserAction currentUserAction;   /* '<Root>/SupervisorB2' */
  ENUM_TemperatureStatus roverTemperatureHealth;/* '<Root>/RoverTemperatureHealth' */
  ENUM_SafeAction safeAction;          /* '<Root>/ActionsModel' */
  ENUM_RoverAction roverAction;        /* '<Root>/ActionsModel' */
  ENUM_PidMode pidMode;                /* '<Root>/ActionsModel' */
  ENUM_MotorsStatus motorsHealth;      /* '<Root>/MotorsHealth' */
  ENUM_MotorStatus LF_HealthMotor;     /* '<Root>/MotorsHealth' */
  ENUM_MotorStatus LR_HealthMotor;     /* '<Root>/MotorsHealth' */
  ENUM_MotorStatus RF_HealthMotor;     /* '<Root>/MotorsHealth' */
  ENUM_MotorStatus RR_HealthMotor;     /* '<Root>/MotorsHealth' */
  ENUM_LinkStatus communicationLinkHealth;/* '<Root>/Model' */
  ENUM_Error errorB1;                  /* '<Root>/SupervisorB2' */
  ENUM_Error errorB2;                  /* '<Root>/SupervisorB2' */
  ENUM_CycleResult cycleResult;        /* '<Root>/SupervisorB2' */
  ENUM_BoardStatus StatusBoard1;       /* '<Root>/BoardsHealth' */
  ENUM_BoardStatus StatusBoard2;       /* '<Root>/BoardsHealth' */
} B_Board2_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  BUS_GlobalState board1GlobalState;   /* '<Root>/SupervisorB2' */
  BUS_Decision board1Decision;         /* '<Root>/SupervisorB2' */
  BUS_LocalStateB2 board2LocalState;   /* '<Root>/SupervisorB2' */
  BUS_LocalStateB1 board1LocalState;   /* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_CommunicationPh;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_ComputeDecision;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_ErrorStateDecis;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_ExchangeDecisio;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_D_Receive;  /* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_D_Transmit; /* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_ExchangeGlobalS;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_GL_Receive; /* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_GL_Transmit;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_ExchangeLocalSt;/* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_LS_Receive; /* '<Root>/SupervisorB2' */
  uint32_T exit_port_index_LS_Transmit;/* '<Root>/SupervisorB2' */
  ENUM_CycleResult commCycleStatus;    /* '<Root>/SupervisorB2' */
  ENUM_StatusWhiteLed previousWhiteLeftLed;/* '<Root>/SupervisorB2' */
  ENUM_StatusWhiteLed previousWhiteRightLed;/* '<Root>/SupervisorB2' */
  uint16_T previousButtons;            /* '<Root>/SupervisorB2' */
  uint8_T Board1RTR;                   /* '<Root>/Data Store Memory' */
  uint8_T Board2RTR;                   /* '<Root>/Data Store Memory1' */
  uint8_T Board1Received;              /* '<Root>/Data Store Memory2' */
  uint8_T Board2Received;              /* '<Root>/Data Store Memory3' */
  uint8_T Board1AckReceived;           /* '<Root>/Data Store Memory4' */
  uint8_T Board2AckReceived;           /* '<Root>/Data Store Memory5' */
  uint8_T txPayload;                   /* '<Root>/SupervisorB2' */
  uint8_T rxPayload;                   /* '<Root>/SupervisorB2' */
  uint8_T flagCRC;                     /* '<Root>/SupervisorB2' */
  uint8_T receiveArmed;                /* '<Root>/SupervisorB2' */
  uint8_T result;                      /* '<Root>/SupervisorB2' */
  uint8_T is_active_c3_Board2;         /* '<Root>/SupervisorB2' */
  uint8_T is_RoverState;               /* '<Root>/SupervisorB2' */
  uint8_T is_CommunicationPhase;       /* '<Root>/SupervisorB2' */
  uint8_T is_ComputeDecision;          /* '<Root>/SupervisorB2' */
  uint8_T is_ErrorStateDecision;       /* '<Root>/SupervisorB2' */
  uint8_T is_ExchangeDecision;         /* '<Root>/SupervisorB2' */
  uint8_T is_D_Receive;                /* '<Root>/SupervisorB2' */
  uint8_T is_D_Transmit;               /* '<Root>/SupervisorB2' */
  uint8_T is_ExchangeGlobalState;      /* '<Root>/SupervisorB2' */
  uint8_T is_GL_Receive;               /* '<Root>/SupervisorB2' */
  uint8_T is_GL_Transmit;              /* '<Root>/SupervisorB2' */
  uint8_T is_ExchangeLocalState;       /* '<Root>/SupervisorB2' */
  uint8_T is_LS_Receive;               /* '<Root>/SupervisorB2' */
  uint8_T is_LS_Transmit;              /* '<Root>/SupervisorB2' */
  uint8_T timeoutOccurred_start;       /* '<Root>/SupervisorB2' */
} DW_Board2_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  BUS_Sonar sonar;                     /* '<Root>/sonar' */
  Gyroscope gyroscope;                 /* '<Root>/gyroscope' */
  BUS_RemoteController remoteController;/* '<Root>/remoteController' */
  uint8_T rx_buffer[64];               /* '<Root>/rx_buffer' */
  uint8_T areSensorsValid;             /* '<Root>/areSensorsValid' */
  uint8_T timeoutOccurred;             /* '<Root>/timeoutOccurred' */
  uint8_T deadlineOccurred;            /* '<Root>/deadlineOccurred' */
} ExtU_Board2_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T tx_buffer[64];               /* '<Root>/tx_buffer' */
  uint8_T supervision_ended;           /* '<Root>/supervision_ended' */
  BUS_GlobalState board2GlobalState;   /* '<Root>/board2GlobalState' */
  BUS_Decision board2Decision;         /* '<Root>/board2Decision' */
} ExtY_Board2_T;

/* Real-time Model Data Structure */
struct tag_RTM_Board2_T {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_Board2_T Board2_B;

/* Block states (default storage) */
extern DW_Board2_T Board2_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Board2_T Board2_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Board2_T Board2_Y;

/* Model entry point functions */
extern void Board2_initialize(void);
extern void Board2_step(void);
extern void Board2_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Board2_T *const Board2_M;

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
 * '<Root>' : 'Board2'
 * '<S1>'   : 'Board2/SupervisorB2'
 */
#endif                                 /* Board2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
