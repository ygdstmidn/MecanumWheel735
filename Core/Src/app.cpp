// main code here!!

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "can.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

#include <DitelMotorDriverController/DitelMotorDriverController.h>
#define MOTOR_ADDRESS1 1
#define MOTOR_ADDRESS2 2
#define MOTOR_ADDRESS3 7
#define MOTOR_ADDRESS4 4

    // MARK:setup
    void user_setup(void)
    {
        setbuf(stdout, NULL);
        printf("Hello World!!\n");

        HAL_CAN_Start(&hcan1);
        HAL_Delay(1);
        DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS1, 10, 100, 0, -1);
        DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS1, DITEL_MOTOR_PID_ENABLE);
        HAL_Delay(1);
        DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS2, 10, 100, 0, -1);
        DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS2, DITEL_MOTOR_PID_ENABLE);
        HAL_Delay(1);
        DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS3, 7, 60, 0, -1);
        DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS3, DITEL_MOTOR_PID_ENABLE);
        HAL_Delay(1);
        DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS4, 10, 100, 0, -1);
        DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS4, DITEL_MOTOR_PID_ENABLE);
        HAL_Delay(1);
    }

    // MARK:loop
    void user_loop(void)
    {
        const uint32_t now = HAL_GetTick();
        static uint32_t pre = now;

        if (now - pre >= 10)
        {
            static int speed = 800;
            DitelMotorPID(&hcan1, MOTOR_ADDRESS1, speed);
            DitelMotorPID(&hcan1, MOTOR_ADDRESS2, -1 * speed);
            HAL_Delay(1);
            DitelMotorPID(&hcan1, MOTOR_ADDRESS3, -4 * speed);
            DitelMotorPID(&hcan1, MOTOR_ADDRESS4, speed);

            // static int count = 0;
            // count++;
            // if (count >= 1000)
            // {
            //     if (speed == 0)
            //     {
            //         speed = 800;
            //     }
            //     else
            //     {
            //         speed = 0;
            //     }
            //     count = 0;
            // }
            pre = now;
        }
    }

    // MARK:_write (for printf)
    int _write(int file, char *ptr, int len)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, 10);
        return len;
    }

#ifdef __cplusplus
}
#endif
