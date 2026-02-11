/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file mpu6050.h
 * @brief Header file for MPU6050/GY521 accelerometer and gyroscope driver.
 * @author Bulanov Konstantin
 */

#ifndef INC_GY521_H_
#define INC_GY521_H_

#include <stdint.h>
#include "i2c.h"

/**
 * @brief MPU6050 Data structure
 */
typedef struct
{

    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;
    double Ax;
    double Ay;
    double Az;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;
    double Gx;
    double Gy;
    double Gz;

    float Temperature;

    double KalmanAngleX;
    double KalmanAngleY;
    double KalmanAngleZ;
} MPU6050_t;

/**
 * @brief Structure for exclusive Yaw (Z-axis) reading
 */
typedef struct
{
    int16_t Gyro_Z_RAW;
    double Gz;
    
    /** @brief Internal 'double' accumulator to avoid precision loss during integration */
    double _YawAcc; 
    
    /** @brief Final output in uint16_t (0-360 degrees) */
    uint16_t KalmanAngleZ;

    /** @brief Tick captured in ISR at the moment data is received */
    uint32_t isr_tick;
} MPU6050_Yaw_t;

/**
 * @brief Kalman Filter structure
 */
typedef struct
{
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} Kalman_t;

// --- Function Prototypes ---

uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx);

void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);
void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);
void MPU6050_Read_Temp(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);
void MPU6050_Read_All(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);
void MPU6050_Read_Yaw(I2C_HandleTypeDef *I2Cx, MPU6050_Yaw_t *DataStruct);

double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);

// Define per return status
/** @brief MPU Operation OK */
#define MPU_OK      (0)
/** @brief MPU Operation Error */
#define MPU_ERR     (-1)

/**
 * @brief Enum for asynchronous reception status
 */
typedef enum {
    MPU_RX_NOT_RECEIVED = 0, /**< Idle */
    MPU_RX_IN_PROGRESS,      /**< Busy */
    MPU_RX_SUCCESS,          /**< Done OK */
    MPU_RX_ERROR             /**< Done Error */
} MPU_RxStatus_t;

// *** ASYNCHRONOUS / INTERRUPT HANDLING (PadReceiver Logic) ***
/**
 * @brief Starts Yaw reading in Interrupt mode (Non-Blocking).
 * @param I2Cx Pointer to the I2C handle.
 * @param DataStruct Pointer to the MPU6050 Yaw data structure.
 * @return MPU_OK if started successfully, MPU_ERR if busy or error.
 */
int8_t MPU6050_Read_Yaw_IT(I2C_HandleTypeDef *I2Cx, MPU6050_Yaw_t *DataStruct);

/**
 * @brief Returns the operation status.
 * @return Current reception status.
 */
MPU_RxStatus_t MPU6050_GetStatus(void);

/**
 * @brief To be called inside HAL_I2C_MemRxCpltCallback (or RxCpltCallback) in main.c 
 *        to signal RX completion.
 */
void MPU6050_RxCpltCallback(void);

/**
 * @brief Processes received data (to be called in the task after SUCCESS).
 */
void MPU6050_Process_Yaw_IT_Data(void);

/**
 * @brief To be called in HAL_I2C_ErrorCallback to handle errors and unlock the bus.
 */
void MPU6050_Error_Callback(void);

#endif /* INC_GY521_H_ */
