#ifndef INC_BUS_FRAME_SIZE_H_
#define INC_BUS_FRAME_SIZE_H_

/* --- Dimensioni dei tipi elementari --- */

#define FLOAT_FRAME_SIZE                (4)
#define ENUM_FRAME_SIZE                 (1)
#define SENSOR_READINGS_FRAME_SIZE      (1)
#define DEADLINE_OCCURRED_FRAME_SIZE    (1)

/* 
   Per gli altri tipi, ci sono solo interi dove è specificato il numero di byte
   e mai ad esempio solo int quindi dovrebbero bastare questi due
*/

/* --- Dimensioni dei tipi base dei sensori --- */

#define SPEED_FRAME_SIZE             (FLOAT_FRAME_SIZE)
#define BUS_SPEED_FRAME_SIZE         (SPEED_FRAME_SIZE * 4)         // 16

#define TEMPERATURE_FRAME_SIZE       (FLOAT_FRAME_SIZE)             // 4

#define BATTERY_LEVEL_FRAME_SIZE     (1)                            /* uint8 */

#define SONAR_FRAME_SIZE             (2)                            /* uint16 */
#define BUS_SONAR_FRAME_SIZE         (SONAR_FRAME_SIZE * 3)         // 6  

#define GYROSCOPE_FRAME_SIZE         (2)                            /* uint16 */

#define REMOTE_CONTROLLER_FRAME_SIZE (2 * 3)                        /* 2 int16 + uint16 */ // 6

/* --- Stati --- */

#define LOCAL_STATE_B1_FRAME_SIZE ( \
    BUS_SPEED_FRAME_SIZE + TEMPERATURE_FRAME_SIZE + \
    BATTERY_LEVEL_FRAME_SIZE + SENSOR_READINGS_FRAME_SIZE +\
    DEADLINE_OCCURRED_FRAME_SIZE)                // 23

#define LOCAL_STATE_B2_FRAME_SIZE ( \
    BUS_SONAR_FRAME_SIZE + GYROSCOPE_FRAME_SIZE + \
    REMOTE_CONTROLLER_FRAME_SIZE +SENSOR_READINGS_FRAME_SIZE +\
    DEADLINE_OCCURRED_FRAME_SIZE)               // 16

#define GLOBAL_STATE_FRAME_SIZE (LOCAL_STATE_B1_FRAME_SIZE + \
    LOCAL_STATE_B2_FRAME_SIZE)                // 39

/* --- Decisione / Controllo --- */

#define SET_POINT_FRAME_SIZE             (FLOAT_FRAME_SIZE)
#define BUS_SET_POINT_FRAME_SIZE         (SET_POINT_FRAME_SIZE * 2)  // 8

#define DECISION_FRAME_SIZE              ((5 * ENUM_FRAME_SIZE) + \
                                         BUS_SET_POINT_FRAME_SIZE + 1) // 14

#endif /* INC_BUS_FRAME_SIZE_H_ */
    