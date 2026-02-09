#include "freeRTOS_functions.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "i2c.h"
#include "uart_functions.h"
#include "print.h"

// Extern thread handles
extern osThreadId_t ReadControllerHandle;
extern osThreadId_t ReadGyroscopeHandle;
extern osThreadId_t SupervisorHandle;
extern osThreadId_t ReadSonarsHandle;
extern osThreadId_t StartSeggerHandle;
extern osThreadId_t SynchronizationHandle;
extern osThreadId_t PollingServerHandle;

// Extern peripheral handles
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;

static inline void terminateThreadIfAlive(osThreadId_t thread, osThreadId_t current)
{
    if ((thread != NULL) && (thread != current)) {
        (void)osThreadTerminate(thread);
    }
}

static inline void killTasks(void)
{
    osThreadId_t current = osThreadGetId();

    terminateThreadIfAlive(ReadControllerHandle, current);
    terminateThreadIfAlive(ReadGyroscopeHandle, current);
    terminateThreadIfAlive(ReadSonarsHandle, current);
    terminateThreadIfAlive(PollingServerHandle, current);
}

static inline void abortUartLinks(void)
{
    UART_HandleTypeDef *comm_uart = getComunicationHandler();
    UART_HandleTypeDef *print_uart = getPrinterHandler();

    if (comm_uart != NULL) {
        (void)HAL_UART_Abort(comm_uart);
        (void)HAL_UART_Abort_IT(comm_uart);
    }

    if (print_uart != NULL) {
        (void)HAL_UART_Abort(print_uart);
        (void)HAL_UART_Abort_IT(print_uart);
    }
}

static inline void stopTimers(void)
{
    (void)HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_ALL);
    (void)HAL_TIM_Base_Stop_IT(&htim1);

    (void)HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_ALL);
    (void)HAL_TIM_Base_Stop_IT(&htim2);
}

static inline void stopI2cBuses(void)
{
    (void)HAL_I2C_DeInit(&hi2c1);
    (void)HAL_I2C_DeInit(&hi2c3);
}

static inline void resetOutputs(void)
{
    (void)HAL_GPIO_WritePin(SonarLeftTrig_GPIO_Port, SonarLeftTrig_Pin, GPIO_PIN_RESET);
    (void)HAL_GPIO_WritePin(SonarRightTrig_GPIO_Port, SonarRightTrig_Pin, GPIO_PIN_RESET);
    (void)HAL_GPIO_WritePin(SonarFrontTrig_GPIO_Port, SonarFrontTrig_Pin, GPIO_PIN_RESET);

#if LED_DEBUG
    (void)HAL_GPIO_WritePin(LedDebug_GPIO_Port, LedDebug_Pin, GPIO_PIN_RESET);
#endif

    (void)HAL_GPIO_WritePin(RTR_OUT_GPIO_Port, RTR_OUT_Pin, GPIO_PIN_RESET);
}

static inline void killPeripherals(void)
{
    abortUartLinks();
    stopTimers();
    stopI2cBuses();
    resetOutputs();
}

extern osEventFlagsId_t flagsOSHandle;
#include "event_flags_constant.h"

void enterDegraded(){
	osEventFlagsSet(flagsOSHandle, FLAG_DEGRADED);
    (void)osThreadTerminate(osThreadGetId());
}


void enterEmergency(){
    killTasks();
    killPeripherals();
}

void enterFaulty(){
    killTasks();
    killPeripherals();
}
