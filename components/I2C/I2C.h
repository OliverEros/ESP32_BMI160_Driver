#ifndef I2C_COMPONENT
#define I2C_COMPONENT

void init_i2c(void);
void register_slave_device(void);
uint8_t read_from_register(uint8_t reg, uint8_t *value);

uint8_t write_to_register(uint8_t reg, uint8_t data);

#endif
