#include "freeRTOS_functions.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "adc.h"
#include "uart_functions.h"
#include "print.h"

// Extern thread handles
extern osThreadId_t PIDHandle;
extern osThreadId_t SupervisorHandle;
extern osThreadId_t ReadTemperatureHandle;
extern osThreadId_t ReadBatteryHandle;
extern osThreadId_t StartSeggerHandle;
extern osThreadId_t SynchronizationHandle;

// Extern peripheral handles
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

static inline void terminateThreadIfAlive(osThreadId_t thread, osThreadId_t current)
{
    if ((thread != NULL) && (thread != current)) {
        (void)osThreadTerminate(thread);
    }
}

static inline void killTasks(void)
{
    osThreadId_t current = osThreadGetId();

    terminateThreadIfAlive(PIDHandle, current);
    terminateThreadIfAlive(ReadTemperatureHandle, current);
    terminateThreadIfAlive(ReadBatteryHandle, current);
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

    (void)HAL_TIM_Encoder_Stop(&htim2, TIM_CHANNEL_ALL);
    (void)HAL_TIM_Base_Stop_IT(&htim2);

    (void)HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_ALL);
    (void)HAL_TIM_Base_Stop_IT(&htim3);

    (void)HAL_TIM_Encoder_Stop(&htim4, TIM_CHANNEL_ALL);
    (void)HAL_TIM_Base_Stop_IT(&htim4);

    (void)HAL_TIM_Encoder_Stop(&htim8, TIM_CHANNEL_ALL);
    (void)HAL_TIM_Base_Stop_IT(&htim8);
}

static inline void stopAdcs(void)
{
    (void)HAL_ADC_Stop_IT(&hadc1);
    (void)HAL_ADC_Stop_IT(&hadc2);
}

static inline void resetOutputs(void)
{
    (void)HAL_GPIO_WritePin(WhiteLedRight_GPIO_Port, WhiteLedRight_Pin, GPIO_PIN_RESET);
    (void)HAL_GPIO_WritePin(RedLedRight_GPIO_Port, RedLedRight_Pin, GPIO_PIN_RESET);

    (void)HAL_GPIO_WritePin(WhiteLedLeft_GPIO_Port, WhiteLedLeft_Pin, GPIO_PIN_RESET);
    (void)HAL_GPIO_WritePin(RedLedLeft_GPIO_Port, RedLedLeft_Pin, GPIO_PIN_RESET);

#if LED_DEBUG
    (void)HAL_GPIO_WritePin(LedDebug_GPIO_Port, LedDebug_Pin, GPIO_PIN_RESET);
#endif

    (void)HAL_GPIO_WritePin(Actuator_GPIO_Port, Actuator_Pin, GPIO_PIN_RESET);
}

static inline void killPeripherals(void)
{
    abortUartLinks();
    stopTimers();
    stopAdcs();
    resetOutputs();
}


void enterDegraded(){
    killTasks();
    killPeripherals();
    (void)osThreadTerminate(osThreadGetId());
}


void enterEmergency(){
    killTasks();
    killPeripherals();
    (void)osThreadTerminate(osThreadGetId());
}

void enterFaulty(){
    killTasks();
    killPeripherals();
    (void)osThreadTerminate(osThreadGetId());
}

