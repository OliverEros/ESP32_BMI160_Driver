idf_component_register(
    SRCS "I2C.c"
    INCLUDE_DIRS "."
    REQUIRES driver
    PRIV_REQUIRES BMI160
)

