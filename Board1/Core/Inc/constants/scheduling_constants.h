#ifndef INC_CONSTANTS_SCHEDULING_CONSTANTS_H_
#define INC_CONSTANTS_SCHEDULING_CONSTANTS_H_

#include <stdint.h>

/*
 * Scheduling constants
 *
 * - All T_* are periods in milliseconds (ms)
 * - All WCET_* are execution times in microseconds (us)
 */

#define MS_TO_US(ms_) ((uint32_t)(ms_) * 1000u)

/* =========================
 *  Board1
 * ========================= */

/* PID Task */
#define T_PID           		20u    /* 20ms (50Hz) */
#define WCET_PID_US            1000u
#define WCET_PID               WCET_PID_US

/* Supervisor Task */
#define T_SUPERVISOR           	50u    /* 50ms (20Hz) */
#define WCET_SUPERVISOR_MS      15u
#define WCET_SUPERVISOR_US      MS_TO_US(WCET_SUPERVISOR_MS)
#define WCET_SUPERVISOR         WCET_SUPERVISOR_US

/* Battery Task */
#define T_BATTERY           	200u    /* 200ms (5Hz) */
#define WCET_BATTERY_US         1000u
#define WCET_BATTERY            WCET_BATTERY_US

/* Temperature Task */
#define T_TEMPERATURE           200u    /* 200ms (5Hz) */
#define WCET_TEMPERATURE_US     1000u
#define WCET_TEMPERATURE        WCET_TEMPERATURE_US


#endif /* INC_CONSTANTS_SCHEDULING_CONSTANTS_H_ */
