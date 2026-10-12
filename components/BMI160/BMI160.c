#include <stdint.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "esp_log.h"
#include "esp_err.h"
#include "I2C.h"
#include "config/registers.h"


typedef uint8_t POWER_MODE;


static const char* TAG = "BMI160";

/*
 *  Static helper function that combines 
 *  two int8_t types into int16_t.
 *
 *  Mainly used for returning sensor values.
 */
static int16_t int8_t_to_in16_t(int8_t val1, int8_t val2)
{
    return (int16_t) (val1 << 8 | val2);
}


static esp_err_t is_correct_power_mode(uint8_t power_mode)
{
    uint8_t min = 0;
    uint8_t max = 2;

    bool is_valid_power_mode = (power_mode >= min && power_mode <= max);

    if(is_valid_power_mode) 
      return ESP_OK;
      
    ESP_LOGI(TAG, "%d is not a correct power mode option", power_mode);
    return ESP_FAIL;
     
}

/*
 * Applies a bit mask to the value received from the register.
 * 
 * NOTE:
 * 2.11.3 Register (0x03) PMU_STATUS:
 *    bit (5-4): acc_pmu_status
 *    bit (3-2): gy_pmu_status
 *    bit (1-0): mag_pmu_status (Unused atm)
 *   
 *TODO: Add struct for shift_by
 * */
static esp_err_t power_bit_to_uint8_t(uint8_t *value, uint8_t shift_by)
{
  uint8_t mask = 0b00000011;
  uint8_t masked_value = ((*value >> shift_by ) & mask );

  if(masked_value != 0x00 && masked_value != 0x01 && masked_value && 0x02)
  {
    ESP_LOGI(TAG, "Incorrect value for power mode: 0x%x", masked_value);
    return ESP_FAIL;
  }
  
  //Assign value to param so that it can be reused.
  *value = masked_value;

  return ESP_OK;
}


esp_err_t is_device_connected()
{
  uint8_t connectedStatus;
  esp_err_t isConnected = read_from_register(BMI160_CHIPID, &connectedStatus);

  if(isConnected != ESP_OK){
   ESP_LOGI(TAG, "BMI160 could not be connected"); 
   return ESP_FAIL;
  }


   ESP_LOGI(TAG, "[SUCCESS] BMI160 is connected"); 

  return ESP_OK;
}

//=========[POWER MODES]==============
esp_err_t get_gyroscope_power_mode()
{
  //Register  (3-2)
  uint8_t shift_by = 2;
  POWER_MODE pwr_mode = 0x00;
  
  ESP_ERROR_CHECK(read_from_register(BMI160_PMU_STATUS, &pwr_mode )); 
  ESP_ERROR_CHECK(power_bit_to_uint8_t(&pwr_mode, shift_by));
  
  ESP_LOGI(TAG, "[Gyroscope power mode: 0x%x", pwr_mode);

  return ESP_OK;
}

esp_err_t get_accelerometer_power_mode(uint8_t *power_mode)
{
  //Register  (5-4)
  uint8_t shift_by = 4;
  POWER_MODE pwr_mode = 0x00;
  
  ESP_ERROR_CHECK(read_from_register(BMI160_PMU_STATUS, &pwr_mode ));
  ESP_ERROR_CHECK(power_bit_to_uint8_t(&pwr_mode, shift_by));
  
  ESP_LOGI(TAG, "[Accelerometer power mode: 0x%x", pwr_mode);

  return ESP_OK;
}



esp_err_t set_gyroscope_power_mode(uint8_t power_mode)
{
  ESP_ERROR_CHECK(is_correct_power_mode(power_mode));

  return ESP_OK;
}

esp_err_t set_accelerometer_power_mode(uint8_t power_mode)
{
  ESP_ERROR_CHECK(is_correct_power_mode(power_mode));


  return ESP_OK;
}


int8_t get_gyroscope_value()
{
  return 0;
}

int8_t get_accelerometer_value()
{
  return 0;
}




