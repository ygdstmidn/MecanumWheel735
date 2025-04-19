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
        // DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS1, 0, 1, 0);
        // DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS1, DITEL_MOTOR_PID_ENABLE);
        // HAL_Delay(1);
        // DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS2, 0, 1, 0);
        // DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS2, DITEL_MOTOR_PID_ENABLE);
        // HAL_Delay(1);
        // DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS3, 1, 20, 0);
        // DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS3, DITEL_MOTOR_PID_ENABLE);
        // HAL_Delay(1);
        // DitelMotorDriverSetPIDGain(&hcan1, MOTOR_ADDRESS4, 0, 1, 0);
        // DitelMotorDriverPIDCondition(&hcan1, MOTOR_ADDRESS4, DITEL_MOTOR_PID_ENABLE);
        // HAL_Delay(1);
    }

    // MARK:loop
    void user_loop(void)
    {
        const uint32_t now = HAL_GetTick();
        static uint32_t pre = now;

        if (now - pre >= 10)
        {
            static int speed = 40;
            DitelMotor(&hcan1, MOTOR_ADDRESS1, speed);
            DitelMotor(&hcan1, MOTOR_ADDRESS2, -1 * speed);
            HAL_Delay(1);
            DitelMotor(&hcan1, MOTOR_ADDRESS3, -1.5 * speed);
            DitelMotor(&hcan1, MOTOR_ADDRESS4, speed);

            // static int count = 0;
            // count++;
            // if (count >= 500)
            // {
            //     if (speed == 0)
            //     {
            //         speed = 4000;
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
