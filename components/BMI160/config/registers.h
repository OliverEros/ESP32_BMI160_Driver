#ifndef BMI160_REGISTERS
#define BMI160_REGISTERS

#define BMI160_CHIPID     0x00 //the chip identification code.
#define BMI160_ERR_REG    0x02 //Reports sensor error flags. Flags are reset when read.
#define BMI160_PMU_STATUS 0x03 //Shows the current power mode of the sensor.
#define BMI160_CMD        0x7E //

//Register (0x04-0x17) DATA 
//(Register for accelerometer, gyroscope and magnetometer data)
//[Magnetometer]
// #define  MAG_X_LSB        0x04
// #define  MAG_X_MSB        0x05
// #define  MAG_Y_LSB        0x06
// #define  MAG_Y_MSB        0x07
// #define  MAG_Z_LSB        0x08
// #define  MAG_Z_MSB        0x09
//

//[Gyroscope]
#define  GYR_X_LSB        0x0C
#define  GYR_X_MSB        0x0D
#define  GYR_Y_LSB        0x0E
#define  GYR_Y_MSB        0x0F
#define  GYR_Z_LSB        0x10
#define  GYR_Z_MSB        0x11


//[Accelerometer]
#define  ACC_X_LSB        0x12
#define  ACC_X_MSB        0x13
#define  ACC_Y_LSB        0x14
#define  ACC_Y_MSB        0x15
#define  ACC_Z_LSB        0x16
#define  ACC_Z_MSB        0x17







 




#endif
