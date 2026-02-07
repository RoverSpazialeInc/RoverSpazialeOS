/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* OS */
#include "scheduling_constants.h"
#include "event_flags_constant.h"
#include "sync_start.h"
#include "freeRTOS_functions.h"

/* Simulink Model */
#include "Board2.h"

/* Drivers */
#include "pad_receiver.h"
#include "gyroscope_init.h" // #include "mpu6050.h"
#include "sonar_init.h"     // #include "HCSR04.h"
#include "motors_init.h"
/*
#include "motors_control.h"
#include "motor_constants.h"
#include "regulator.h"
*/
#include "timer.h"

/* Utility */
#include "DWT.h"
#include "print.h"
#include "debug.h"
#include "phase.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticEventGroup_t osStaticEventGroupDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define MAX_WAIT_SONAR (40)

#if SEGGER_BUILD
#include "SEGGER_SYSVIEW_FreeRTOS.h"
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* Global start tick (set after synchronization) */
volatile uint32_t start_tick = 0;

/* MISS COUNTERS */
volatile uint32_t MissReadController = 0;
volatile uint32_t MissReadGyroscope = 0;
volatile uint32_t MissSupervisor = 0;
volatile uint32_t MissReadSonars = 0;
volatile uint32_t MissPollingServer = 0;

/* STATUS FLAGS */
uint8_t pad_receiver_read_failed = 0;
uint8_t gyroscope_read_failed = 0;
uint8_t sonar_read_failed = 0;

/* DEFAULT VALUES */
const BUS_RemoteController default_controller = { 0, 0, 0 };

/* Timer Handler from main.c */
extern timer_t timerSupervisor;

/* USER CODE END Variables */
/* Definitions for ReadController */
osThreadId_t ReadControllerHandle;
uint32_t ReadControllerBuffer[ 1024 ];
osStaticThreadDef_t ReadControllerControlBlock;
const osThreadAttr_t ReadController_attributes = {
  .name = "ReadController",
  .stack_mem = &ReadControllerBuffer[0],
  .stack_size = sizeof(ReadControllerBuffer),
  .cb_mem = &ReadControllerControlBlock,
  .cb_size = sizeof(ReadControllerControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for ReadGyroscope */
osThreadId_t ReadGyroscopeHandle;
uint32_t ReadGyroscopeBuffer[ 1024 ];
osStaticThreadDef_t ReadGyroscopeControlBlock;
const osThreadAttr_t ReadGyroscope_attributes = {
  .name = "ReadGyroscope",
  .stack_mem = &ReadGyroscopeBuffer[0],
  .stack_size = sizeof(ReadGyroscopeBuffer),
  .cb_mem = &ReadGyroscopeControlBlock,
  .cb_size = sizeof(ReadGyroscopeControlBlock),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Supervisor */
osThreadId_t SupervisorHandle;
uint32_t SupervisorBuffer[ 2048 ];
osStaticThreadDef_t SupervisorControlBlock;
const osThreadAttr_t Supervisor_attributes = {
  .name = "Supervisor",
  .stack_mem = &SupervisorBuffer[0],
  .stack_size = sizeof(SupervisorBuffer),
  .cb_mem = &SupervisorControlBlock,
  .cb_size = sizeof(SupervisorControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ReadSonars */
osThreadId_t ReadSonarsHandle;
uint32_t ReadSonarsBuffer[ 1024 ];
osStaticThreadDef_t ReadSonarsControlBlock;
const osThreadAttr_t ReadSonars_attributes = {
  .name = "ReadSonars",
  .stack_mem = &ReadSonarsBuffer[0],
  .stack_size = sizeof(ReadSonarsBuffer),
  .cb_mem = &ReadSonarsControlBlock,
  .cb_size = sizeof(ReadSonarsControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for StartSegger */
osThreadId_t StartSeggerHandle;
uint32_t StartSeggerBuffer[ 128 ];
osStaticThreadDef_t StartSeggerControlBlock;
const osThreadAttr_t StartSegger_attributes = {
  .name = "StartSegger",
  .stack_mem = &StartSeggerBuffer[0],
  .stack_size = sizeof(StartSeggerBuffer),
  .cb_mem = &StartSeggerControlBlock,
  .cb_size = sizeof(StartSeggerControlBlock),
  .priority = (osPriority_t) osPriorityHigh7,
};
/* Definitions for Synchronization */
osThreadId_t SynchronizationHandle;
uint32_t SynchronizationBuffer[ 128 ];
osStaticThreadDef_t SynchronizationControlBlock;
const osThreadAttr_t Synchronization_attributes = {
  .name = "Synchronization",
  .stack_mem = &SynchronizationBuffer[0],
  .stack_size = sizeof(SynchronizationBuffer),
  .cb_mem = &SynchronizationControlBlock,
  .cb_size = sizeof(SynchronizationControlBlock),
  .priority = (osPriority_t) osPriorityHigh6,
};
/* Definitions for PollingServer */
osThreadId_t PollingServerHandle;
uint32_t PollingServerBuffer[ 2048 ];
osStaticThreadDef_t PollingServerControlBlock;
const osThreadAttr_t PollingServer_attributes = {
  .name = "PollingServer",
  .stack_mem = &PollingServerBuffer[0],
  .stack_size = sizeof(PollingServerBuffer),
  .cb_mem = &PollingServerControlBlock,
  .cb_size = sizeof(PollingServerControlBlock),
  .priority = (osPriority_t) osPriorityHigh5,
};
/* Definitions for SupervisorDeg */
osThreadId_t SupervisorDegHandle;
uint32_t SupervisorDegBuffer[ 2048 ];
osStaticThreadDef_t SupervisorDegControlBlock;
const osThreadAttr_t SupervisorDeg_attributes = {
  .name = "SupervisorDeg",
  .stack_mem = &SupervisorDegBuffer[0],
  .stack_size = sizeof(SupervisorDegBuffer),
  .cb_mem = &SupervisorDegControlBlock,
  .cb_size = sizeof(SupervisorDegControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SonarMonitoring */
osTimerId_t SonarMonitoringHandle;
osStaticTimerDef_t SonarMonitoringControlBlock;
const osTimerAttr_t SonarMonitoring_attributes = {
  .name = "SonarMonitoring",
  .cb_mem = &SonarMonitoringControlBlock,
  .cb_size = sizeof(SonarMonitoringControlBlock),
};
/* Definitions for flagsOS */
osEventFlagsId_t flagsOSHandle;
osStaticEventGroupDef_t flagsOSControlBlock;
const osEventFlagsAttr_t flagsOS_attributes = {
  .name = "flagsOS",
  .cb_mem = &flagsOSControlBlock,
  .cb_size = sizeof(flagsOSControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* SCHEDULING FUNCTIONS */
static uint32_t ms_to_ticks(uint32_t ms);
static void periodic_wait(uint32_t *next_release, uint32_t period_ticks,
		volatile uint32_t *miss_counter);

/* ERROR DRIVER FUNCTIONS */
static inline void error_pad_receiver(void);
static inline void error_gyroscope(void);
static inline void error_sonar(void);

/* PRODUCTION FUNCTIONS */
static inline void manage_fake_sonar_toggle(void);

/* USER CODE END FunctionPrototypes */

void StartReadController(void *argument);
void StartReadGyroscope(void *argument);
void StartSupervisor(void *argument);
void StartReadSonars(void *argument);
void StartSeggerTask(void *argument);
void StartSynchronization(void *argument);
void StartPollingServer(void *argument);
void StartSupervisorDeg(void *argument);
void SonarTimeout(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of SonarMonitoring */
  SonarMonitoringHandle = osTimerNew(SonarTimeout, osTimerOnce, NULL, &SonarMonitoring_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
	timer_set_period(&timerSupervisor, WCET_SUPERVISOR_MS);
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ReadController */
  ReadControllerHandle = osThreadNew(StartReadController, NULL, &ReadController_attributes);

  /* creation of ReadGyroscope */
  ReadGyroscopeHandle = osThreadNew(StartReadGyroscope, NULL, &ReadGyroscope_attributes);

  /* creation of Supervisor */
  SupervisorHandle = osThreadNew(StartSupervisor, NULL, &Supervisor_attributes);

  /* creation of ReadSonars */
  ReadSonarsHandle = osThreadNew(StartReadSonars, NULL, &ReadSonars_attributes);

  /* creation of StartSegger */
  StartSeggerHandle = osThreadNew(StartSeggerTask, NULL, &StartSegger_attributes);

  /* creation of Synchronization */
  SynchronizationHandle = osThreadNew(StartSynchronization, NULL, &Synchronization_attributes);

  /* creation of PollingServer */
  PollingServerHandle = osThreadNew(StartPollingServer, NULL, &PollingServer_attributes);

  /* creation of SupervisorDeg */
  SupervisorDegHandle = osThreadNew(StartSupervisorDeg, NULL, &SupervisorDeg_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of flagsOS */
  flagsOSHandle = osEventFlagsNew(&flagsOS_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
	Sync_Init(flagsOSHandle,
				RTR_IN_GPIO_Port, RTR_IN_Pin,
	            RTR_OUT_GPIO_Port, RTR_OUT_Pin,
	            FLAG_START, FLAG_SYNC, FLAG_ACK);
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartReadController */
/**
 * @brief  Function implementing the ReadController thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReadController */
void StartReadController(void *argument)
{
  /* USER CODE BEGIN StartReadController */
#if RUN_READ_CONTROLLER

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_REMOTE_CONTROLLER);
	uint32_t next = start_tick;

	/* Return code of the last I2C request:
	 * PAD_OK  -> request started successfully (asynchronous reception in progress)
	 * PAD_ERR -> request not started (I2C busy or HAL start error)
	 */
	int8_t result = PAD_ERR;

	/* Infinite loop */
	for (;;) {

#if REAL_TASK


		/* Start an asynchronous I2C read from the remote controller.
		 * Note: PAD_OK only means the reception was successfully started.
		 * The final outcome (success/error) is reported later via callbacks
		 * and can be eventually checked through PadReceiver_GetStatus().
		 */
		result = PadReceiver_Request();

		/* Handle immediate start failure:
		 * If the request could not be started (bus busy or HAL error),
		 * raise an error flag to notify other tasks/components.
		 */
		if (result == PAD_ERR) {
            error_pad_receiver();
			// osEventFlagsSet(flagsOSHandle, FLAG_PAD_ERROR);
            // No need to use the Polling Server for error handling
		}

#else
		DWT_DelayUs(WCET_CONTROLLER);
#endif

		/* Wait until next period and track deadline miss if any */
		periodic_wait(&next, T, &MissReadController);
	}
#endif

	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartReadController */
}

/* USER CODE BEGIN Header_StartReadGyroscope */
/**
 * @brief Function implementing the ReadGyroscope thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReadGyroscope */
void StartReadGyroscope(void *argument)
{
  /* USER CODE BEGIN StartReadGyroscope */
#if RUN_READ_GYROSCOPE

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_GYROSCOPE);
	uint32_t next = start_tick;

	/* Return code of the last gyroscope read request:
	 * MPU_OK  -> request started successfully (asynchronous I2C reception in progress)
	 * MPU_ERR -> request not started (I2C busy or HAL start error)
	 *
	 * Note: MPU_OK does NOT mean that MPU6050_Yaw has been updated yet.
	 * The final outcome is provided later by callbacks / driver status.
	 */
	int8_t result = MPU_ERR;

	/* Infinite loop */
	for (;;) {

#if REAL_TASK

		/* Start an asynchronous read of the yaw value from the MPU6050 via I2C interrupt.
		 * If the request starts correctly, the driver will update MPU6050_Yaw later
		 * (typically in the Rx complete callback).
		 */
		result = MPU6050_Read_Yaw_IT(&hi2c3, &MPU6050_Yaw);

		/* Handle immediate start failure:
		 * If the read request cannot be started (bus busy or HAL error),
		 * raise an error flag to notify other tasks/components.
		 */
		if (result == MPU_ERR) {
			error_gyroscope();
			// osEventFlagsSet(flagsOSHandle, FLAG_GYRO_ERROR);
			// No need to use the Polling Server for error handling
		}

#else
		DWT_DelayUs(WCET_GYROSCOPE);
#endif

		/* Wait until next period and track deadline miss if any */
		periodic_wait(&next, T, &MissReadGyroscope);
	}
#endif
	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartReadGyroscope */
}

/* USER CODE BEGIN Header_StartSupervisor */
/**
 * @brief Function implementing the Supervisor thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSupervisor */
void StartSupervisor(void *argument)
{
  /* USER CODE BEGIN StartSupervisor */
#if RUN_SUPERVISOR

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_SUPERVISOR);
	uint32_t next = start_tick;

	periodic_wait(&next, T, &MissSupervisor);  // Skip first communication

	/* Infinite loop */
	for (;;) {

		/* Convert singular errors into global flags for the Simulink model */
		uint8_t temp = 0;
		temp |= (pad_receiver_read_failed & 0x01) << 0;
		temp |= (gyroscope_read_failed     & 0x01) << 1;
		temp |= (sonar_read_failed        & 0x01) << 2;
		//Board2_U.areSensorsValid = temp;

		/* Clear previous error flags */
		pad_receiver_read_failed = 0;
		gyroscope_read_failed = 0;
		sonar_read_failed = 0;

		manage_fake_sonar_toggle();

		/* START TIMER FOR MONITORING WCET */
		//timer_start(&timerSupervisor);

		do {
			Board2_step();
		} while (Board2_Y.supervision_ended != 1);

		/* STOP TIMER FOR MONITORING WCET */
		//timer_reset(&timerSupervisor);


		/* BEGIN PRINT SECTION */

//		static uint32_t cycle_count = 0;
//		cycle_count++;
//
//
//		printMsg("Cycle Count B2: ");
//		printInt((int32_t)cycle_count);
//		printNewLine();
//
//		if (cycle_count >= 100) { // Approx 2 seconds (50ms * 40)
//			printGlobalState(&Board2_Y.board1GlobalState);
//			printDecision(&Board2_Y.board1Decision);
//			cycle_count = 0;
//		}

		/* END PRINT SECTION */

		if(Board2_Y.board1Decision.roverState == EMERGENCY ||
				Board2_Y.board1Decision.roverState == FAULTY_B1_DEGRADED_B2){
			break;
		}
		periodic_wait(&next, T, &MissSupervisor);
	}
#endif

	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartSupervisor */
}

/* USER CODE BEGIN Header_StartReadSonars */
/**
 * @brief Function implementing the ReadSonars thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReadSonars */
void StartReadSonars(void *argument)
{
  /* USER CODE BEGIN StartReadSonars */
#if RUN_READ_SONARS

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_SONAR);
	uint32_t next = start_tick;

	const uint32_t TIMEOUT_TICKS = ms_to_ticks(MAX_WAIT_SONAR);
	/* Infinite loop */
	for (;;) {

#if REAL_TASK

		hcsr04_trigger(&sonarLeft);
		hcsr04_trigger(&sonarFront);
		hcsr04_trigger(&sonarRight);

		/* Safe stop and start timer */
#if SEGGER_BUILD == 0 //pezzotto per evitare conflitti con SysView
		osTimerStop(SonarMonitoringHandle);
		osTimerStart(SonarMonitoringHandle, TIMEOUT_TICKS);
#endif

#else
		DWT_DelayUs(WCET_SONAR);
#endif

		/* Wait until next period and track deadline miss if any */
		periodic_wait(&next, T, &MissReadSonars);
	}

#endif

	osThreadTerminate(osThreadGetId());
  /* USER CODE END StartReadSonars */
}

/* USER CODE BEGIN Header_StartSeggerTask */
/**
 * @brief Function implementing the StartSegger thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSeggerTask */
void StartSeggerTask(void *argument)
{
  /* USER CODE BEGIN StartSeggerTask */

#if SEGGER_BUILD
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();
	#endif

	/* Infinite loop */
	for (;;) {
		break;
	}
	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartSeggerTask */
}

/* USER CODE BEGIN Header_StartSynchronization */
// This feature is extern to the library behavior
extern volatile system_phase_t system_phase;
/**
 * @brief Function implementing the Synchronization thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSynchronization */
void StartSynchronization(void *argument)
{
  /* USER CODE BEGIN StartSynchronization */
#if RUN_SYNCHRONIZATION

	system_phase = SYNCHRONIZATION_PHASE;

	SyncThread();

	/* Synchronization completed: define common time-base for periodic tasks */
	start_tick = osKernelGetTickCount();

	system_phase = WORKING_PHASE;

	HAL_GPIO_WritePin(RTR_OUT_GPIO_Port, RTR_OUT_Pin, GPIO_PIN_RESET);

	#if LED_DEBUG
	HAL_GPIO_WritePin(LedDebug_GPIO_Port, LedDebug_Pin, GPIO_PIN_SET);
	#endif

#endif


	// Termination, if clock drift is not critical
	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartSynchronization */
}

/* USER CODE BEGIN Header_StartPollingServer */
/**
 * @brief Function implementing the PollingServer thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartPollingServer */
void StartPollingServer(void *argument)
{
  /* USER CODE BEGIN StartPollingServer */
#if RUN_POLLING_SERVER

    Sync_WaitStart();

    const uint32_t T = ms_to_ticks(T_POLLING_SERVER);
	uint32_t next = start_tick;

    /* Infinite loop */
    for (;;) {

#if REAL_TASK

        /* Upon server activation, process all pending requests, if any */
        uint32_t flags = osEventFlagsWait(flagsOSHandle,
        FLAGS_POLLING_SERVER_WAIT,
        osFlagsWaitAny | osFlagsNoClear, 0);

        if ((int32_t) flags > 0) {
            
            /* ---------------- REMOTE CONTROLLER ---------------- */
            if (flags & FLAG_PAD_OK) {
                PadReceiver_Read(&Board2_U.remoteController);
                pad_receiver_read_failed = 0;
                // Clear both to prioritize OK and prevent double handling
                osEventFlagsClear(flagsOSHandle, FLAG_PAD_OK | FLAG_PAD_ERROR);
            }
            else if (flags & FLAG_PAD_ERROR) {
                error_pad_receiver();
                osEventFlagsClear(flagsOSHandle, FLAG_PAD_ERROR);
            }

            /* ------------------- GYROSCOPE ------------------- */
            if (flags & FLAG_GYRO_OK) {
                MPU6050_Process_Yaw_IT_Data();
                Board2_U.gyroscope = MPU6050_Yaw.KalmanAngleZ;
                gyroscope_read_failed = 0;
                osEventFlagsClear(flagsOSHandle, FLAG_GYRO_OK | FLAG_GYRO_ERROR);
            }
            else if (flags & FLAG_GYRO_ERROR) {
                error_gyroscope();
                osEventFlagsClear(flagsOSHandle, FLAG_GYRO_ERROR);
            }

            /* ------------------ SONAR LEFT ------------------- */
            if (flags & FLAG_SONAR_LEFT_OK) {
                hcsr04_process_distance(&sonarLeft);
                Board2_U.sonar.left = sonarLeft.distance;
                osEventFlagsClear(flagsOSHandle, FLAG_SONAR_LEFT_OK | FLAG_SONAR_LEFT_TIMEOUT);
            }
            else if (flags & FLAG_SONAR_LEFT_TIMEOUT) {
                hcsr04_reset_sonar(&sonarLeft); 
                osEventFlagsClear(flagsOSHandle, FLAG_SONAR_LEFT_TIMEOUT);
            }

            /* ------------------ SONAR FRONT ------------------ */
            if (flags & FLAG_SONAR_FRONT_OK) {
                hcsr04_process_distance(&sonarFront);
                Board2_U.sonar.front = sonarFront.distance;
                osEventFlagsClear(flagsOSHandle, FLAG_SONAR_FRONT_OK | FLAG_SONAR_FRONT_TIMEOUT);
            }
            else if (flags & FLAG_SONAR_FRONT_TIMEOUT) {
                hcsr04_reset_sonar(&sonarFront);
                osEventFlagsClear(flagsOSHandle, FLAG_SONAR_FRONT_TIMEOUT);
            }

            /* ------------------ SONAR RIGHT ------------------ */
            if (flags & FLAG_SONAR_RIGHT_OK) {
                hcsr04_process_distance(&sonarRight);
                Board2_U.sonar.right = sonarRight.distance;
                osEventFlagsClear(flagsOSHandle, FLAG_SONAR_RIGHT_OK | FLAG_SONAR_RIGHT_TIMEOUT);
            }
            else if (flags & FLAG_SONAR_RIGHT_TIMEOUT) {
                hcsr04_reset_sonar(&sonarRight);
                osEventFlagsClear(flagsOSHandle, FLAG_SONAR_RIGHT_TIMEOUT);
            }

        }
#if PRINT_TASK
		static uint32_t cycle_count = 0;
		cycle_count++;

		if (cycle_count >= 100) {

		printSonar(&Board2_U.sonar);
		cycle_count = 0;
		}
#endif

#else
        Board2_U.remoteController = (BUS_RemoteController){ 0, 0, 0 };
        Board2_U.gyroscope = 32;
        Board2_U.sonar = (BUS_Sonar){ 380, 400, 380 };
		DWT_DelayUs(WCET_POLLING_SERVER);
#endif

#endif

        periodic_wait(&next, T, &MissPollingServer);

    }

    osThreadTerminate(osThreadGetId());

  /* USER CODE END StartPollingServer */
}

/* USER CODE BEGIN Header_StartSupervisorDeg */
/**
* @brief Function implementing the SupervisorDeg thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSupervisorDeg */
void StartSupervisorDeg(void *argument)
{
  /* USER CODE BEGIN StartSupervisorDeg */
  /* Infinite loop */
  for(;;)
  {
    break;
  }

  osThreadTerminate(osThreadGetId());
  /* USER CODE END StartSupervisorDeg */
}

/* SonarTimeout function */
void SonarTimeout(void *argument)
{
  /* USER CODE BEGIN SonarTimeout */
	// Check each sonar and set timeout flags if not done
	if (!hcsr04_is_done(&sonarLeft)) {
		osEventFlagsSet(flagsOSHandle, FLAG_SONAR_LEFT_TIMEOUT);
	}
	if (!hcsr04_is_done(&sonarFront)) {
		osEventFlagsSet(flagsOSHandle, FLAG_SONAR_FRONT_TIMEOUT);
	}
	if (!hcsr04_is_done(&sonarRight)) {
		osEventFlagsSet(flagsOSHandle, FLAG_SONAR_RIGHT_TIMEOUT);
	}
  /* USER CODE END SonarTimeout */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* SCHEDULING FUNCTIONS */

static uint32_t ms_to_ticks(uint32_t ms) {
	uint32_t hz = osKernelGetTickFreq();
	return (ms * hz + 999u) / 1000u;
}

static void periodic_wait(uint32_t *next_release, uint32_t period_ticks,
		volatile uint32_t *miss_counter) {
	uint32_t now = osKernelGetTickCount();

	/* Calcola il prossimo rilascio */
	*next_release += period_ticks;

	/* Controllo deadline miss (safe con wrap-around) */
	if ((int32_t) (now - *next_release) > 0) {
		if (miss_counter != NULL) {
			(*miss_counter)++;
		}
	}

	/* Sleep assoluta fino al prossimo periodo */
	osDelayUntil(*next_release);
}


/* ERROR DRIVER FUNCTIONS */
static inline void error_pad_receiver(void){
	Board2_U.remoteController = default_controller;
	pad_receiver_read_failed = 1;
}

static inline void error_gyroscope(void){
	// Board2_U.gyroscope; Preserve last valid data
	gyroscope_read_failed = 1;
}
static inline void error_sonar(void){
	sonar_read_failed = 1;
}

static inline void manage_fake_sonar_toggle(void) {
	/* FAKE SONAR */
	#include "controller_masks.h"

	// 0 = enabled, 1 = disabled
	static uint8_t disable_left = 0;
	static uint8_t disable_front = 0;
	static uint8_t disable_right = 0;

	uint32_t current = Board2_U.remoteController.buttons;
	uint32_t risingEdges = (~Board2_DW.previousButtons) & current;

	/* Toggle su fronte di salita */
	if (risingEdges & DISABLE_LEFT_SONAR)
		disable_left = !disable_left;

	if (risingEdges & DISABLE_FRONT_SONAR)
		disable_front = !disable_front;

	if (risingEdges & DISABLE_RIGHT_SONAR)
		disable_right = !disable_right;

	/* Applica disabilitazione */
	if (disable_left)
		Board2_U.sonar.left = 380;

	if (disable_front)
		Board2_U.sonar.front = 380;

	if (disable_right)
		Board2_U.sonar.right = 380;

	/* END FAKE SONAR */
}

/* USER CODE END Application */

