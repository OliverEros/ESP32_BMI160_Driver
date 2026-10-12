# BMI160 on ESP32

Reading a Bosch BMI160 6-axis IMU (accelerometer and gyroscope) over I2C from an ESP32, written in C with ESP-IDF.

> **Status: work in progress.** 
## Goals

- Talk to the BMI160 over I2C using the ESP-IDF `i2c_master` driver
- Read raw accelerometer and gyroscope data
- Convert raw readings into physical units (g and °/s)
- Build a small, reusable driver component for future projects.

## Progress ()

- [x] I2C bus and device set up
- [x] Read the chip ID (register `0x00`, expected value `0xD1`)
- [ ] Soft reset and power-up sequence
- [ ] Configure accelerometer and gyroscope (range and output data rate)
- [ ] Read raw accelerometer and gyroscope data
- [ ] Scale readings to physical units
- [ ] Package as a reusable component

## Hardware

- ESP32 DEVKIT V1 
- BMI160 breakout board

## Wiring

Default I2C connection (change the pins in the code or `menuconfig` if you use different ones):

| BMI160 | ESP32 | Notes |
| --- | --- | --- |
| VIN / VCC | 3V3 | Use 3.3 V, not 5 V, unless your breakout has a regulator |
| GND | GND | |
| SDA / SDI | GPIO [21] | I2C data |
| SCL / SCK | GPIO [22] | I2C clock |
| CS / CSB | 3V3 | Pulled high to select I2C mode |
| SDO | GND or 3V3 | Selects the I2C address (see below) |

### I2C address

| SDO pin | 7-bit address |
| --- | --- |
| GND | `0x68` |
| 3V3 | `0x69` |


## Requirements

- ESP32 (other ESP32 variants may work but are untested)
- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) [version, e.g. v5.x]

## Build and flash

```bash
git clone https://github.com/OliverEros/<repo-name>.git
cd <repo-name>

idf.py set-target esp32
idf.py build
idf.py -p <PORT> flash monitor
```

Replace `<PORT>` with your serial port (for example `/dev/ttyUSB0` or `COM3`). Press `Ctrl+]` to exit the monitor.

## Expected output

Once the chip ID read works, the serial monitor should show something like:

```text
[value] BMI160 chip ID: 0xD1
```

## Project structure

```text
.
├── CMakeLists.txt
├── main/          # Application code
├── components/    # Driver and helper components
└── sdkconfig      # Generated locally (not committed)
```

## Roadmap

- Interrupt-driven reads using the BMI160 data-ready pin
- FIFO support
- Basic orientation estimation from the sensor data

## Resources

- [BMI160 datasheet (Bosch Sensortec)](https://www.bosch-sensortec.com/products/motion-sensors/imus/bmi160/)
- [ESP-IDF I2C driver documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html)

## License
Released under the [MIT License](LICENSE).

