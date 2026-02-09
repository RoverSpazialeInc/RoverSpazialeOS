#ifndef INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_
#define INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_

/* Event Flags (CMSIS-RTOS v2 / FreeRTOS)
 * Bitmask definitions
 */

#define FLAG_START                  (1U << 0) // 2^0 = 1
#define FLAG_SYNC                   (1U << 1) // 2^1 = 2
#define FLAG_ACK                    (1U << 2) // 2^2 = 4

/* Controller / Pad */
#define FLAG_PAD_OK                 (1U << 3)  // 2^3 = 8
#define FLAG_PAD_ERROR              (1U << 4)	// 2^4 = 16

/* Gyroscope */
#define FLAG_GYRO_OK                (1U << 5) // 2^5 = 32
#define FLAG_GYRO_ERROR             (1U << 6)	// 2^6 = 64

/* Sonar Left */
#define FLAG_SONAR_LEFT_OK          (1U << 7) // 2^7 = 128
#define FLAG_SONAR_LEFT_TIMEOUT     (1U << 8) // 2^8 = 256

/* Sonar Front */
#define FLAG_SONAR_FRONT_OK         (1U << 9) // 2^9 = 512
#define FLAG_SONAR_FRONT_TIMEOUT    (1U << 10) // 2^10 = 1024

/* Sonar Right */
#define FLAG_SONAR_RIGHT_OK         (1U << 11) 	// 2^11 = 2048
#define FLAG_SONAR_RIGHT_TIMEOUT    (1U << 12) // 2^12 = 4096

/* Degraded mode */
#define FLAG_DEGRADED               (1U << 13) // 2^13 = 8192

/* Mask for all events the Polling Server waits for (everything except START and SYNC) */
#define FLAGS_POLLING_SERVER_WAIT   (FLAG_PAD_OK | FLAG_PAD_ERROR | \
                                     FLAG_GYRO_OK | FLAG_GYRO_ERROR | \
                                     FLAG_SONAR_LEFT_OK | FLAG_SONAR_LEFT_TIMEOUT | \
                                     FLAG_SONAR_FRONT_OK | FLAG_SONAR_FRONT_TIMEOUT | \
                                     FLAG_SONAR_RIGHT_OK | FLAG_SONAR_RIGHT_TIMEOUT)

#endif /* INC_CONSTANTS_EVENT_FLAGS_CONSTANT_H_ */
