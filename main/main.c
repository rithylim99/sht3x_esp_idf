/******************************************************************************
 *                                                                            *
 *  Author    : Lim Rithy                                                     *
 *  Project   : Sht3x Demo on ESP-IDF                                         *
 *  Date      : Aug 12, 2024                                                  *
 *                                                                            *
 *  Remark    :                                                               *
 *  Most components I got from UncleRus's Repo:                               *
 *  https://github.com/UncleRus/esp-idf-lib/tree/master/components            *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"
#include "sht3x.h"
#include "string.h"

#define I2C_SCL (GPIO_NUM_22)   // ESP32 SCL Pin
#define I2C_SDA (GPIO_NUM_21)   // ESP32 SDA Pin
#define SHT_ADD 0x44            // Sht3x Address (When AD-->GND)

static sht3x_t sensor;

float temp;
float humi;

void app_main(void)
{
    // Initial I2C Port
    i2cdev_init();
    memset(&sensor, 0, sizeof(sht3x_t));

    // Intial sensor param
    sht3x_init_desc(&sensor, SHT_ADD, 0, I2C_SDA, I2C_SCL);
    sht3x_init(&sensor);

    TickType_t last_wakeup = xTaskGetTickCount();

    for(;;){
        sht3x_measure(&sensor, &temp, &humi);
        printf("Sensor = %.2f C, %.2f %% \n", temp, humi);
        vTaskDelayUntil(&last_wakeup, pdMS_TO_TICKS(2000));
    }

}
