# Components
In this DIY version, only commonly available breakout boards and easily solderable parts are used. No SMD's are used.

## Arduino
An Arduino MEGA 2560 is the basis for this project.<br>
The length of the code, the amount of RAM, and the number of I/O pins required for this project only allows an Arduino MEGA 2560 to be used.<br>
- Arduino MEGA 2560

## Power supply
To conserve power, the Arduino can be fed by a 12V-5V DC/DC-converter instead of directly from the 12V bus. This is optional of course.
- 1 x 12V to 5V DC/DC converter.

## Lithium battery
This BMS is only intended to be used for LiFePO4 batteries.<br>
Although this BMS can probably be used for any size Lithium battery, the BMS is designed primarily for quite large capacity batteries; I use 8 cells of 180Ah, 2 in parallel, 4 in series, so it is effectively a 12V 360Ah battery.

## Sensors
### Cell voltage probes
- 1 x Adafruit ADS1115 4-channel 16bit ADC breakout board
- 4 x 1:3 resistor dividers for voltage sensor probes. Precision is not very important, during commission the sensor probes will be automatically calibrated.

### Bus voltage, Lithium battery current, Lead-acid battery current
- 2 x Adafruit INA219 High Side DC current sensor breakout boards, the shunt resistor has to be removed
- 2 x external high power shunt resistors

### Temperature
These temperature sensors can all be wired together
- 1 x DS18B temperature sensor per Lithium Cell, plus one sensor for ambient temperature and one for outside temperature.

## Control
Although the BMS has an output for a monostable relay, it is highly recommended to use a bistable relay.
- 1 x 300 Amp bistable relais (I used one from www.kissling.de)
- 2 x Logic level FET's (like NDP6020P) to control relais coils

For testing purposes one can use a monostable relay, in that case:
- 1 x 300 Amp monostable relais (startrelais?)
- 1 x Logic level FET (like NDP6020P) on a cooling block

## User interface
- 1 x 1602 display unit with I2C interface
- 2 x push buttons
- 2 x LED's (with resistor)

## Communication
Important note: Although it is tempting to connect the Ethernet module to the 3.3V of the Arduino, it works unreliable due to the high current pulses required.
To prevent erroneous behaviour, the Ethernet module needs to have its own power supply. A 3.3V DC/DC converter fed from the 12V bus is used to conserve power.<br>
Optionally, a DC/DC converter with an enable input can be used, so the BMS can shut down the ethernet module when it senses that it is not being used.
- 1 x ENC28J60 Ethernet board
- 1 x 12V to 3.3 Volt DC/DC converter (with optional logic enable input)

## Optional
- 1 x RS485 interface for remote display and Open-NMEA interface
- Interface (Logic level FET's?) to control environment (Fan and/or Heater).
- Interface (Logic level FET's, buffers, level converters) to use the signal ports to control external devices
