#include "config/pins.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include <stdio.h>
#include <stdint.h>
#include "esp_log.h"  

//esp_log
static const char* TAG = "I2C";

//[I2C master config]
static i2c_master_bus_config_t i2c_master_config = {
  .clk_source = I2C_CLK_SRC_DEFAULT,
  .i2c_port   = I2C_NUM_0,
  .scl_io_num = I2C_PIN_SCL,
  .sda_io_num = I2C_PIN_SDA
};

//[Master device (esp32)]
static i2c_master_bus_handle_t master_bus_handle;


//[Slave device configuration]
 static i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address  = 0x69,
    .scl_speed_hz    = 100000
 };

static i2c_master_dev_handle_t slave_handle;
/*
    Used for initialising I2C
*/



/*
 *  
 * */
void init_i2c(void)
{
  ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_config,&master_bus_handle));
}

/* Registers the I2C slave device.
 * */
void register_slave_device(void)
{
  esp_err_t error;
  error = i2c_master_bus_add_device(master_bus_handle, &dev_cfg, &slave_handle);

  if(error == ESP_OK){
    ESP_LOGI(TAG, "[OK] I2C slave has been added");
  } else {
    ESP_LOGI(TAG, "[ERROR] There was a problem adding slave.");
  }  
}


/*
 * TODO: 
 **/
esp_err_t read_from_register(uint8_t reg, uint8_t *value)
{
    esp_err_t ret = i2c_master_transmit_receive(slave_handle, &reg, 1, value, 1, 1000);

    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Reg 0x%02X = 0x%02X", reg, *value);
    } else {
        ESP_LOGI(TAG, "Read reg 0x%02X failed: %s", reg, esp_err_to_name(ret));
    }
    return ret;
}

/*
 * Function used to write data to a register
 * reg + data is combined => uint8_t data[2] = {reg, data}
 */
esp_err_t write_to_register(uint8_t reg, uint8_t data)
{
    uint8_t toSend[2] = {reg, data};
    esp_err_t isSuccess;

    isSuccess = i2c_master_transmit(slave_handle, toSend, sizeof(toSend), 1000);

    if(isSuccess == ESP_OK){
      ESP_LOGI(TAG, "[OK] Data write to register 0x%02X", reg);
    } else {
      ESP_LOGI(TAG, "[ERROR] Data write to register 0x%02X resulted in error", reg);
    }

    return isSuccess;
}
