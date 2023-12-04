# ESP32 Encoder Reader

The ESP32 Encoder Reader is a code snippet that reads the RPM (Rotations Per Minute) from an encoder connected to an ESP32 microcontroller. It utilizes the ESP-IDF framework and the PCNT (Pulse Counter) peripheral to accurately measure the RPM of the encoder.

## Prerequisites

- ESP-IDF development framework installed

## Installation

1. Clone or download the repository.
2. Open the project in your preferred IDE (e.g., Visual Studio Code with PlatformIO).
3. Configure the necessary GPIO pins for the encoder by modifying the following lines:

```cpp
const gpio_num_t ENCODER_PIN_PHASE_A = GPIO_NUM_27;
const gpio_num_t ENCODER_PIN_PHASE_B = GPIO_NUM_32;
