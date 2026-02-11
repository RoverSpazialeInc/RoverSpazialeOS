/*
 * mpu6050.c
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 *
 *  Contact information
 *  -------------------
 *
 * e-mail   :  leech001@gmail.com
 */

/*
 * |---------------------------------------------------------------------------------
 * | Copyright (C) Bulanov Konstantin,2021
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |
 * | Kalman filter algorithm used from https://github.com/TKJElectronics/KalmanFilter
 * |---------------------------------------------------------------------------------
 */

/**
 * @file mpu6050.c
 * @brief MPU6050 driver implementation for STM32
 * 
 * This file contains the implementation of the MPU6050 driver using I2C communication.
 * It includes initialization, reading accelerometer and gyroscope data, and Kalman filter implementation.
 */

#include <math.h>
#include "mpu6050.h"

#define RAD_TO_DEG 57.295779513082320876798154814105

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43
// Ensure Z register is defined
#ifndef GYRO_ZOUT_H_REG
#define GYRO_ZOUT_H_REG 0x47
#endif

// Setup MPU6050
#define MPU6050_ADDR 0xD0
const uint16_t i2c_timeout = 100;
const double Accel_Z_corrector = 14418.0;

uint32_t last_tick;
static double gyroZ_bias = 0.0; // bias in dps (degrees/sec)

Kalman_t KalmanX = {
    .Q_angle = 0.001f,
    .Q_bias = 0.003f,
    .R_measure = 0.03f};

Kalman_t KalmanY = {
    .Q_angle = 0.001f,
    .Q_bias = 0.003f,
    .R_measure = 0.03f,
};

// Kalman filter definition for Z axis
Kalman_t KalmanZ = {
    .Q_angle = 0.001f,
    .Q_bias = 0.003f,
    .R_measure = 0.03f,
};

/**
 * @brief  Initializes the MPU6050 sensor
 * @param  I2Cx Pointer to I2C handle
 * @return 0 if successful, 1 if device not found
 */
uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx)
{
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);

    if (check == 104 || check == 112) // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);

        // --- GYRO Z BIAS CALIBRATION (blocking, a few hundred samples) ---
        {
            const int samples = 500;
            int32_t sum_gz = 0;
            uint8_t buf[6];
            for (int i = 0; i < samples; ++i)
            {
                HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, buf, 6, i2c_timeout);
                int16_t gz_raw = (int16_t)(buf[4] << 8 | buf[5]);
                sum_gz += gz_raw;
                HAL_Delay(2); // ~2 ms between reads -> ~1s total for 500 samples
            }
            gyroZ_bias = (double)sum_gz / (double)samples / 131.0; // convert to dps
        }

        last_tick = HAL_GetTick(); // initialize last_tick to avoid huge first dt

        return 0;
    }
    return 1;
}

/**
 * @brief  Reads accelerometer data from MPU6050
 * @param  I2Cx Pointer to I2C handle
 * @param  DataStruct Pointer to MPU6050 data structure
 */
void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);

    DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into acceleration in 'g'
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 16384.0
         for more details check ACCEL_CONFIG Register              ****/

    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
}

/**
 * @brief  Reads gyroscope data from MPU6050
 * @param  I2Cx Pointer to I2C handle
 * @param  DataStruct Pointer to MPU6050 data structure
 */
void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);

    DataStruct->Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;
}

/**
 * @brief  Reads temperature data from MPU6050
 * @param  I2Cx Pointer to I2C handle
 * @param  DataStruct Pointer to MPU6050 data structure
 */
void MPU6050_Read_Temp(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct)
{
    uint8_t Rec_Data[2];
    int16_t temp;

    // Read 2 BYTES of data starting from TEMP_OUT_H_REG register

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, TEMP_OUT_H_REG, 1, Rec_Data, 2, i2c_timeout);

    temp = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);
}

/**
 * @brief  Reads all data (Accel, Gyro, Temp) from MPU6050 and calculates angles using Kalman filter
 * @param  I2Cx Pointer to I2C handle
 * @param  DataStruct Pointer to MPU6050 data structure
 */
void MPU6050_Read_All(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct)
{
    uint8_t Rec_Data[14];
    int16_t temp;

    // Read 14 BYTES of data starting from ACCEL_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 14, i2c_timeout);

    DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
    temp = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);
    DataStruct->Gyro_X_RAW = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    DataStruct->Gyro_Y_RAW = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    DataStruct->Gyro_Z_RAW = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);

    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
    DataStruct->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);
    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0 - gyroZ_bias; // subtract calibrated bias

    // Kalman angle solve
    double dt = (double)(HAL_GetTick() - last_tick) / 1000;
    last_tick = HAL_GetTick();

    double roll;
    double roll_sqrt = sqrt(
        DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
    if (roll_sqrt != 0.0)
    {
        roll = atan(DataStruct->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
    }
    else
    {
        roll = 0.0;
    }
    double pitch = atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW) * RAD_TO_DEG;
    if ((pitch < -90 && DataStruct->KalmanAngleY > 90) || (pitch > 90 && DataStruct->KalmanAngleY < -90))
    {
        KalmanY.angle = pitch;
        DataStruct->KalmanAngleY = pitch;
    }
    else
    {
        DataStruct->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
    }
    if (fabs(DataStruct->KalmanAngleY) > 90)
        DataStruct->Gx = -DataStruct->Gx;
    DataStruct->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, DataStruct->Gx, dt);

    // Calculate Z axis (Yaw)
    DataStruct->KalmanAngleZ += DataStruct->Gz * dt;

    // Implementing circularity: reset to 0 if it exceeds +/- 360
    if (DataStruct->KalmanAngleZ >= 360.0) {
        DataStruct->KalmanAngleZ -= 360.0;
    } else if (DataStruct->KalmanAngleZ <= -360.0) {
        DataStruct->KalmanAngleZ += 360.0;
    }
}

/**
 * @brief  Calculates angle using Kalman filter
 * @param  Kalman Pointer to Kalman filter structure
 * @param  newAngle New angle measurement
 * @param  newRate New angular rate measurement
 * @param  dt Time delta
 * @return Calculated angle
 */
double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt)
{
    double rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    double S = Kalman->P[0][0] + Kalman->R_measure;
    double K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    double y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    double P00_temp = Kalman->P[0][0];
    double P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
};

// --- Static variables for Interrupt management ---
static uint8_t yaw_buffer[2];            // Buffer for raw I2C data
static MPU6050_Yaw_t *pYawStruct = NULL; // Pointer to the currently used struct
static volatile MPU_RxStatus_t mpu_rx_status = MPU_RX_NOT_RECEIVED;

// ---------------------------------------------------------
// INTERRUPT READING IMPLEMENTATION 
// ---------------------------------------------------------

/**
 * @brief  Starts Yaw reading in Interrupt mode.
 * @param  I2Cx Pointer to I2C handle
 * @param  DataStruct Pointer to MPU6050 Yaw data structure
 * @return MPU_OK if the request started successfully, MPU_ERR otherwise
 */
int8_t MPU6050_Read_Yaw_IT(I2C_HandleTypeDef *I2Cx, MPU6050_Yaw_t *DataStruct)
{
    if (HAL_I2C_GetState(I2Cx) == HAL_I2C_STATE_READY) {
        
        mpu_rx_status = MPU_RX_IN_PROGRESS; // Reset flag: operation start (Busy)
        pYawStruct = DataStruct;

        // Start memory reading via interrupt (GYRO_ZOUT_H_REG register, 2 bytes)
        if(HAL_I2C_Mem_Read_IT(I2Cx, MPU6050_ADDR, GYRO_ZOUT_H_REG, 1, yaw_buffer, 2) != HAL_OK) {
             mpu_rx_status = MPU_RX_NOT_RECEIVED; // Start error
             return MPU_ERR;        // Start failed
        }
        return MPU_OK; // Successfully started
    } else {
        return MPU_ERR; // Busy or HAL Not Ready
    }
}

/**
 * @brief  Gets the current status of the MPU6050 interrupt operation
 * @return Current status of the operation
 */
MPU_RxStatus_t MPU6050_GetStatus(void) {
    return mpu_rx_status;
}

/**
 * @brief  I2C Receive Complete Callback
 */
void MPU6050_RxCpltCallback(void) {
    if (pYawStruct != NULL) {
        pYawStruct->isr_tick = HAL_GetTick(); // Capture timestamp right when data arrives
    }
    mpu_rx_status = MPU_RX_SUCCESS; // Signal operation successfully received
}

/**
 * @brief  Data processing function called by Task after completion.
 *         Reconstructs raw data, converts to dps, integrates and normalizes Yaw
 */
void MPU6050_Process_Yaw_IT_Data(void)
{
    if (pYawStruct != NULL)
    {
        // 1. Reconstruct RAW data from buffer
        pYawStruct->Gyro_Z_RAW = (int16_t)(yaw_buffer[0] << 8 | yaw_buffer[1]);

        // 2. Convert to dps
        pYawStruct->Gz = pYawStruct->Gyro_Z_RAW / 131.0 - gyroZ_bias;

        // 3. Calculate DT using tick captured in ISR (not current time)
        double dt = (double)(pYawStruct->isr_tick - last_tick) / 1000;
        last_tick = pYawStruct->isr_tick;

        // 4. Integration
        pYawStruct->_YawAcc += pYawStruct->Gz * dt;

        // 5. Normalization
        if (pYawStruct->_YawAcc >= 360.0) {
            pYawStruct->_YawAcc -= 360.0;
        } else if (pYawStruct->_YawAcc < 0.0) {
            pYawStruct->_YawAcc += 360.0;
        }

        // 6. Output
        pYawStruct->KalmanAngleZ = (uint16_t)(pYawStruct->_YawAcc);
    }
}

/**
 * @brief  Error callback to unlock flag in case of I2C problems
 */
void MPU6050_Error_Callback(void) {
    mpu_rx_status = MPU_RX_ERROR; // Signal error
}

/**
 * @brief  Aborts any ongoing I2C transfer for the MPU6050.
 *         Sends a STOP condition on the bus to release it.
 * @param  I2Cx Pointer to the I2C handle used by the MPU6050
 * @note   Should be called from the I2C error callback to recover
 *         from bus errors (NACK, arbitration lost, etc.).
 */
void MPU6050_Abort(I2C_HandleTypeDef *I2Cx) {
    HAL_I2C_Master_Abort_IT(I2Cx, MPU6050_ADDR);
}
