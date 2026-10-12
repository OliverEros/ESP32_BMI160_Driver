#include <stdio.h>
#include "esp_err.h"
#include <stdint.h>
#include "I2C.h"
#include "esp_log.h"
#include "BMI160.h"

static const char* TAG = "main";

void app_main()
{
    init_i2c();
    register_slave_device();
   
    is_device_connected();
    get_gyroscope_power_mode();


}
