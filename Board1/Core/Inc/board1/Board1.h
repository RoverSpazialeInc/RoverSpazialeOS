/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Board1.h
 *
 * Code generated for Simulink model 'Board1'.
 *
 * Model version                  : 14.9
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 11 19:38:02 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Board1_h_
#define Board1_h_
#ifndef Board1_COMMON_INCLUDES_
#define Board1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Board1_COMMON_INCLUDES_ */

#include "Board1_types.h"
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
  ENUM_UserAction currentUserAction;   /* '<Root>/SupervisorB1' */
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
  ENUM_Error errorB1;                  /* '<Root>/SupervisorB1' */
  ENUM_Error errorB2;                  /* '<Root>/SupervisorB1' */
  ENUM_CycleResult cycleResult;        /* '<Root>/SupervisorB1' */
  ENUM_BoardStatus StatusBoard1;       /* '<Root>/BoardsHealth' */
  ENUM_BoardStatus StatusBoard2;       /* '<Root>/BoardsHealth' */
} B_Board1_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  BUS_GlobalState board2GlobalState;   /* '<Root>/SupervisorB1' */
  BUS_Decision board2Decision;         /* '<Root>/SupervisorB1' */
  BUS_LocalStateB2 board2LocalState;   /* '<Root>/SupervisorB1' */
  BUS_LocalStateB1 board1LocalState;   /* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_CommunicationPh;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_ComputeDecision;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_ErrorStateDecis;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_ExchangeDecisio;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_D_Receive;  /* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_D_Transmit; /* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_ExchangeGlobalS;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_GL_Receive; /* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_GL_Transmit;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_ExchangeLocalSt;/* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_LS_Receive; /* '<Root>/SupervisorB1' */
  uint32_T exit_port_index_LS_Transmit;/* '<Root>/SupervisorB1' */
  ENUM_CycleResult commCycleStatus;    /* '<Root>/SupervisorB1' */
  ENUM_StatusWhiteLed previousWhiteLeftLed;/* '<Root>/SupervisorB1' */
  ENUM_StatusWhiteLed previousWhiteRightLed;/* '<Root>/SupervisorB1' */
  uint16_T previousButtons;            /* '<Root>/SupervisorB1' */
  uint8_T Board1RTR;                   /* '<Root>/Data Store Memory' */
  uint8_T Board2RTR;                   /* '<Root>/Data Store Memory1' */
  uint8_T Board1Received;              /* '<Root>/Data Store Memory2' */
  uint8_T Board2Received;              /* '<Root>/Data Store Memory3' */
  uint8_T Board1AckReceived;           /* '<Root>/Data Store Memory4' */
  uint8_T Board2AckReceived;           /* '<Root>/Data Store Memory5' */
  uint8_T txPayload;                   /* '<Root>/SupervisorB1' */
  uint8_T rxPayload;                   /* '<Root>/SupervisorB1' */
  uint8_T flagCRC;                     /* '<Root>/SupervisorB1' */
  uint8_T receiveArmed;                /* '<Root>/SupervisorB1' */
  uint8_T result;                      /* '<Root>/SupervisorB1' */
  uint8_T is_active_c15_Board1;        /* '<Root>/SupervisorB1' */
  uint8_T is_RoverState;               /* '<Root>/SupervisorB1' */
  uint8_T is_CommunicationPhase;       /* '<Root>/SupervisorB1' */
  uint8_T is_ComputeDecision;          /* '<Root>/SupervisorB1' */
  uint8_T is_ErrorStateDecision;       /* '<Root>/SupervisorB1' */
  uint8_T is_ExchangeDecision;         /* '<Root>/SupervisorB1' */
  uint8_T is_D_Receive;                /* '<Root>/SupervisorB1' */
  uint8_T is_D_Transmit;               /* '<Root>/SupervisorB1' */
  uint8_T is_ExchangeGlobalState;      /* '<Root>/SupervisorB1' */
  uint8_T is_GL_Receive;               /* '<Root>/SupervisorB1' */
  uint8_T is_GL_Transmit;              /* '<Root>/SupervisorB1' */
  uint8_T is_ExchangeLocalState;       /* '<Root>/SupervisorB1' */
  uint8_T is_LS_Receive;               /* '<Root>/SupervisorB1' */
  uint8_T is_LS_Transmit;              /* '<Root>/SupervisorB1' */
  uint8_T timeoutOccurred_start;       /* '<Root>/SupervisorB1' */
} DW_Board1_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  BUS_Speed speed;                     /* '<Root>/speed' */
  Temperature temperature;             /* '<Root>/temperature' */
  BatteryLevel batteryLevel;           /* '<Root>/batteryLevel' */
  uint8_T rx_buffer[64];               /* '<Root>/rx_buffer' */
  uint8_T areSensorsValid;             /* '<Root>/areSensorsValid' */
  uint8_T timeoutOccurred;             /* '<Root>/timeoutOccurred' */
  uint8_T deadlineOccurred;            /* '<Root>/deadlineOccurred' */
} ExtU_Board1_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T tx_buffer[64];               /* '<Root>/tx_buffer' */
  uint8_T supervision_ended;           /* '<Root>/supervision_ended' */
  BUS_GlobalState board1GlobalState;   /* '<Root>/board1GlobalState' */
  BUS_Decision board1Decision;         /* '<Root>/board1Decision' */
} ExtY_Board1_T;

/* Real-time Model Data Structure */
struct tag_RTM_Board1_T {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_Board1_T Board1_B;

/* Block states (default storage) */
extern DW_Board1_T Board1_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Board1_T Board1_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Board1_T Board1_Y;

/* Model entry point functions */
extern void Board1_initialize(void);
extern void Board1_step(void);
extern void Board1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Board1_T *const Board1_M;

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
 * '<Root>' : 'Board1'
 * '<S1>'   : 'Board1/SupervisorB1'
 */
#endif                                 /* Board1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
