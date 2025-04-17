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
#define MOTOR_ADDRESS 1

    // MARK:setup
    void user_setup(void)
    {
        setbuf(stdout, NULL);
        printf("Hello World!!\n");

        HAL_CAN_Start(&hcan1);
    }

    // MARK:loop
    void user_loop(void)
    {
        const uint32_t now = HAL_GetTick();
        static uint32_t pre = now;

        if (now - pre >= 10)
        {
            DitelMotor(&hcan1, MOTOR_ADDRESS, 50);
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
