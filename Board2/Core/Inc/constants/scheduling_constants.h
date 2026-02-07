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
 *  Board2
 * ========================= */

/* Controller Task */
#define T_REMOTE_CONTROLLER           20u   /* 20ms (50Hz) */
#define WCET_CONTROLLER_US           200u
#define WCET_CONTROLLER              WCET_CONTROLLER_US

/* Gyroscope Task */
#define T_GYROSCOPE                   40u   /* 40ms (25Hz) */
#define WCET_GYROSCOPE_US            200u
#define WCET_GYROSCOPE               WCET_GYROSCOPE_US

/* Supervisor Task */
#define T_SUPERVISOR             	 50u   /* 50ms (20Hz) */
#define WCET_SUPERVISOR_MS           15u
#define WCET_SUPERVISOR_US           MS_TO_US(WCET_SUPERVISOR_MS)
#define WCET_SUPERVISOR              WCET_SUPERVISOR_US

/* Sonar Task */
#define T_SONAR          			 100u   /* 100ms (10Hz) */
#define WCET_SONAR_US               2000u
#define WCET_SONAR                  WCET_SONAR_US

/* Polling Server */
#define T_POLLING_SERVER 	  		 10u   /* 10ms (100Hz) */
#define WCET_POLLING_SERVER_US      1000u
#define WCET_POLLING_SERVER         WCET_POLLING_SERVER_US

#endif /* INC_CONSTANTS_SCHEDULING_CONSTANTS_H_ */
