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
#include "Board1.h"

/* Drivers */
#include "lights_init.h"     // #include "a4wd3_led.h"
#include "encoders_init.h"   // #include "encoders.h"
#include "motors_init.h"
/*
#include "motors_control.h"
#include "motor_constants.h"
#include "regulator.h"
*/
#include "battery_init.h"        // #include "batt_level.h"
#include "temperature_init.h"    //#include "temperature_adc.h"
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
volatile uint32_t MissPID = 0;
volatile uint32_t MissSupervisor = 0;
volatile uint32_t MissReadTemperature = 0;
volatile uint32_t MissReadBattery = 0;

/* STATUS FLAGS */
uint8_t encoder_read_failed = 0;
uint8_t temperature_read_failed = 0;
uint8_t battery_read_failed = 0;

/* TASK OUTPUT VARIABLES (written by tasks, read by Supervisor) */
volatile BUS_Speed task_speed = { 0.0f, 0.0f, 0.0f, 0.0f };
volatile Temperature task_temperature = 0.0f;
volatile BatteryLevel task_batteryLevel = 0;

/* Timer Handler from main.c */
extern timer_t timerSupervisor;

/* USER CODE END Variables */
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
/* Definitions for PID */
osThreadId_t PIDHandle;
uint32_t PIDBuffer[ 1024 ];
osStaticThreadDef_t PIDControlBlock;
const osThreadAttr_t PID_attributes = {
  .name = "PID",
  .stack_mem = &PIDBuffer[0],
  .stack_size = sizeof(PIDBuffer),
  .cb_mem = &PIDControlBlock,
  .cb_size = sizeof(PIDControlBlock),
  .priority = (osPriority_t) osPriorityHigh,
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
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for ReadTemperature */
osThreadId_t ReadTemperatureHandle;
uint32_t ReadTemperatureBuffer[ 1024 ];
osStaticThreadDef_t ReadTemperatureControlBlock;
const osThreadAttr_t ReadTemperature_attributes = {
  .name = "ReadTemperature",
  .stack_mem = &ReadTemperatureBuffer[0],
  .stack_size = sizeof(ReadTemperatureBuffer),
  .cb_mem = &ReadTemperatureControlBlock,
  .cb_size = sizeof(ReadTemperatureControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ReadBattery */
osThreadId_t ReadBatteryHandle;
uint32_t ReadBatteryBuffer[ 1024 ];
osStaticThreadDef_t ReadBatteryControlBlock;
const osThreadAttr_t ReadBattery_attributes = {
  .name = "ReadBattery",
  .stack_mem = &ReadBatteryBuffer[0],
  .stack_size = sizeof(ReadBatteryBuffer),
  .cb_mem = &ReadBatteryControlBlock,
  .cb_size = sizeof(ReadBatteryControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for toggleLeftRedLed */
osTimerId_t toggleLeftRedLedHandle;
osStaticTimerDef_t toggleLeftRedLedControlBlock;
const osTimerAttr_t toggleLeftRedLed_attributes = {
  .name = "toggleLeftRedLed",
  .cb_mem = &toggleLeftRedLedControlBlock,
  .cb_size = sizeof(toggleLeftRedLedControlBlock),
};
/* Definitions for toggleRightRedLed */
osTimerId_t toggleRightRedLedHandle;
osStaticTimerDef_t toggleRightRedLedControlBlock;
const osTimerAttr_t toggleRightRedLed_attributes = {
  .name = "toggleRightRedLed",
  .cb_mem = &toggleRightRedLedControlBlock,
  .cb_size = sizeof(toggleRightRedLedControlBlock),
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

/* DECISION FUNCTIONS */
static inline void compute_sensors_validity(uint8_t *out_validity);
static inline void compute_deadline_misses(uint8_t *out_deadline);
static inline void copy_sensor_inputs(BUS_Speed *out_speed,
		Temperature *out_temperature, BatteryLevel *out_batteryLevel);
static inline void actuate_white_leds(void);
static inline void change_set_point(void);
static inline void change_regulator(void);

/* USER CODE END FunctionPrototypes */

void StartSeggerTask(void *argument);
void StartSynchronization(void *argument);
void StartPID(void *argument);
void StartSupervisor(void *argument);
void StartReadTemperature(void *argument);
void StartReadBattery(void *argument);
void callbackToggleLeftRedLed(void *argument);
void callbackToggleRightRedLed(void *argument);

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
  /* creation of toggleLeftRedLed */
  toggleLeftRedLedHandle = osTimerNew(callbackToggleLeftRedLed, osTimerPeriodic, NULL, &toggleLeftRedLed_attributes);

  /* creation of toggleRightRedLed */
  toggleRightRedLedHandle = osTimerNew(callbackToggleRightRedLed, osTimerPeriodic, NULL, &toggleRightRedLed_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
	timer_set_period(&timerSupervisor, WCET_SUPERVISOR_MS);
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of StartSegger */
  StartSeggerHandle = osThreadNew(StartSeggerTask, NULL, &StartSegger_attributes);

  /* creation of Synchronization */
  SynchronizationHandle = osThreadNew(StartSynchronization, NULL, &Synchronization_attributes);

  /* creation of PID */
  PIDHandle = osThreadNew(StartPID, NULL, &PID_attributes);

  /* creation of Supervisor */
  SupervisorHandle = osThreadNew(StartSupervisor, NULL, &Supervisor_attributes);

  /* creation of ReadTemperature */
  ReadTemperatureHandle = osThreadNew(StartReadTemperature, NULL, &ReadTemperature_attributes);

  /* creation of ReadBattery */
  ReadBatteryHandle = osThreadNew(StartReadBattery, NULL, &ReadBattery_attributes);

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

	system_phase = SYNCHRONIZATION_START;

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

/* USER CODE BEGIN Header_StartPID */
/**
 * @brief  Function implementing the PID thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartPID */
void StartPID(void *argument)
{
  /* USER CODE BEGIN StartPID */
#if RUN_PID

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_PID);
	uint32_t next = start_tick;

	float current_speed[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	/* Infinite loop */
	for (;;) {

#if REAL_TASK

		/* READ ENCODERS AND UPDATE SPEEDS */
		for (int i = 0; i < 4; i++) {
			Encoder_Update(&encoders[i]);
			current_speed[i] = Encoder_GetSpeedRPM(&encoders[i]);
		}

		/* UPDATE TASK VARIABLE */
		task_speed = (BUS_Speed ) { current_speed[0], current_speed[1],
						current_speed[2], current_speed[3] };

		/* EXECUTE MOTOR CONTROL */
		for (int i = 0; i < 4; i++) {
			MotorControl_ClosedLoop(&motors[i], current_speed[i]);
			//MotorControl_OpenLoopActuate(&motors[i]);
		}

#if PRINT_TASK
        //printMotorSpeeds(&Board1_U.speed);
#endif

#else
		task_speed = (BUS_Speed ) { current_speed[0], current_speed[1],
						current_speed[2], current_speed[3] };
		DWT_DelayUs(WCET_PID);
#endif

		periodic_wait(&next, T, &MissPID);
	}
#endif

	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartPID */
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


		/* Copy task variables into Simulink model inputs */
		copy_sensor_inputs(&Board1_U.speed,
				&Board1_U.temperature, &Board1_U.batteryLevel);
		compute_sensors_validity(&Board1_U.areSensorsValid);
		compute_deadline_misses(&Board1_U.deadlineOccurred);

		Board1_U.areSensorsValid = 0;
		Board1_U.deadlineOccurred = 0;

#if ENTER_DEGRADED_MODE
		// In this way the boards will dedice together to enter in degraded mode
		Board1_U.areSensorsValid = 1;
#endif


#if PRINT_RESULT
		do {
			Board1_step();
		} while (Board1_Y.supervision_ended != 1);
#else
		/* START TIMER FOR MONITORING WCET */
		timer_start(&timerSupervisor);

		do {
			Board1_step();
			//Board1_U.timeoutOccurred++;

		} while (Board1_Y.supervision_ended != 1);

		/* STOP TIMER FOR MONITORING WCET */
		timer_reset(&timerSupervisor);
#endif

		/* FINALIZING DECISION */
		actuate_white_leds();
		change_set_point();
		change_regulator();


		/* BEGIN PRINT SECTION */
		static uint32_t cycle_count = 0;
		cycle_count++;

		//printMsg("Cycle Count B1: ");
		//printInt((int32_t)cycle_count);
		//printNewLine();

		//printMotorSpeeds(&Board1_U.speed);

		if (cycle_count >= 100) { // Approx 2 seconds (50ms * 40)
			cycle_count = 0;
#if PRINT_RESULT
			printGlobalState(&Board1_Y.board1GlobalState);
			printDecision(&Board1_Y.board1Decision);
#endif
		}


		/* END PRINT SECTION */

		if(Board1_Y.board1Decision.roverState == EMERGENCY ||
				Board1_Y.board1Decision.roverState == FAULTY_B1_DEGRADED_B2){
			break;
		}

		periodic_wait(&next, T, &MissSupervisor);


	}

#endif

	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartSupervisor */
}

/* USER CODE BEGIN Header_StartReadTemperature */
/**
 * @brief Function implementing the ReadTemperature thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReadTemperature */
void StartReadTemperature(void *argument)
{
  /* USER CODE BEGIN StartReadTemperature */
#if RUN_READ_TEMPERATURE

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_TEMPERATURE);
	uint32_t next = start_tick;

	/* Infinite loop */
	for (;;) {

#if REAL_TASK

		float temp_val = 0.0f;
		if (temp_internal_read_temperature(&temp_sensor, &temp_val) == 0) {
			task_temperature = (Temperature) temp_val;
			temperature_read_failed = 0;
		} else {
			task_temperature = -255.0f;
			temperature_read_failed = 1;
		}

#if PRINT_TASK
        printTemperature(task_temperature);
#endif

#else
        task_temperature = 32.3f;
		DWT_DelayUs(WCET_TEMPERATURE);
#endif

		periodic_wait(&next, T, &MissReadTemperature);
	}

#endif

	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartReadTemperature */
}

/* USER CODE BEGIN Header_StartReadBattery */
/**
 * @brief Function implementing the ReadBattery thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReadBattery */
void StartReadBattery(void *argument)
{
  /* USER CODE BEGIN StartReadBattery */
#if RUN_READ_BATTERY

	Sync_WaitStart();

	const uint32_t T = ms_to_ticks(T_BATTERY);
	uint32_t next = start_tick;

	/* Infinite loop */
	for (;;) {

#if REAL_TASK

		if (battery_get_percentage_linear(battery_read_voltage(&battery),
				MIN_VOLTAGE, MAX_VOLTAGE, (BatteryLevel *)&task_batteryLevel) == 0) {
			battery_read_failed = 0;
			// task_batteryLevel updated
		} else {
			task_batteryLevel = 255;
			battery_read_failed = 1;
		}

#if PRINT_TASK
        printBattery(task_batteryLevel);
#endif

#else
        task_batteryLevel = 32;
		DWT_DelayUs(WCET_BATTERY);
#endif


		periodic_wait(&next, T, &MissReadBattery);
	}

#endif

	osThreadTerminate(osThreadGetId());

  /* USER CODE END StartReadBattery */
}

/* callbackToggleLeftRedLed function */
void callbackToggleLeftRedLed(void *argument)
{
  /* USER CODE BEGIN callbackToggleLeftRedLed */
	A4WD3_Red_Toggle(&led_left);
  /* USER CODE END callbackToggleLeftRedLed */
}

/* callbackToggleRightRedLed function */
void callbackToggleRightRedLed(void *argument)
{
  /* USER CODE BEGIN callbackToggleRightRedLed */
	A4WD3_Red_Toggle(&led_right);
  /* USER CODE END callbackToggleRightRedLed */
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

	/* Controlla se il task ha sforato */
	if ((int32_t) (now - *next_release) > 0) {
		if (miss_counter != NULL) {
			(*miss_counter)++;
		}
	}

	/* Sleep assoluta fino al prossimo periodo */
	osDelayUntil(*next_release);
}


/* DECISION FUNCTIONS */

static inline void compute_sensors_validity(uint8_t *out_validity) {
	/* Convert singular errors into global flags for the Simulink model */
	uint8_t temp = 0;
	temp |= (encoder_read_failed      & 0x01) << 0;
	temp |= (temperature_read_failed  & 0x01) << 1;
	temp |= (battery_read_failed      & 0x01) << 2;
	*out_validity = temp;

	/* Clear previous error flags */
	encoder_read_failed = 0;
	temperature_read_failed = 0;
	battery_read_failed = 0;
}

static inline void compute_deadline_misses(uint8_t *out_deadline) {
	/* Convert non-zero miss counters into a bitmask for the Simulink model */
	uint8_t temp = 0;

	if (MissPID != 0) {
		temp |= (1u << 0);
		MissPID = 0;
	}
	if (MissSupervisor != 0) {
		temp |= (1u << 1);
		MissSupervisor = 0;
	}
	if (MissReadTemperature != 0) {
		temp |= (1u << 2);
		MissReadTemperature = 0;
	}
	if (MissReadBattery != 0) {
		temp |= (1u << 3);
		MissReadBattery = 0;
	}

	*out_deadline = temp;
}

static inline void copy_sensor_inputs(BUS_Speed *out_speed,
		Temperature *out_temperature, BatteryLevel *out_batteryLevel) {
	*out_speed = task_speed;
	*out_temperature = task_temperature;
	*out_batteryLevel = task_batteryLevel;
}

static inline void actuate_white_leds(void) {
	A4WD3_White_Set(&led_left, Board1_Y.board1Decision.leds.white.left);
	A4WD3_White_Set(&led_right, Board1_Y.board1Decision.leds.white.right);
}

static inline void change_set_point(void) {
	const float left = Board1_Y.board1Decision.setPoint.leftAxis;
	const float right = Board1_Y.board1Decision.setPoint.rightAxis;

	MotorControl_SetReferenceRPM(&motors[MOTOR_FRONT_LEFT], left);
	MotorControl_SetReferenceRPM(&motors[MOTOR_REAR_LEFT], left);

	MotorControl_SetReferenceRPM(&motors[MOTOR_FRONT_RIGHT], right);
	MotorControl_SetReferenceRPM(&motors[MOTOR_REAR_RIGHT], right);
}

static inline void change_regulator(void) {
	const uint8_t action = Board1_Y.board1Decision.roverAction;

	switch (action) {
	case RA_BRAKING_SMOOTH:
		for (int i = 0; i < N_MOTORS; i++) {
			MotorControl_SetRegulator(&motors[i], &pid_slow[i]);
		}
		break;

	case RA_BRAKING_MODERATE:
		for (int i = 0; i < N_MOTORS; i++) {
			MotorControl_SetRegulator(&motors[i], &pid_medium[i]);
		}
		break;

	default:
		for (int i = 0; i < N_MOTORS; i++) {
			MotorControl_SetRegulator(&motors[i], &pid_fast[i]);
		}
		break;
	}
}
/* USER CODE END Application */

