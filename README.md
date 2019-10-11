# DroidController

Arduino software to control a droid with 2 motors connected to an RF24 mesh network

## Usage

Upload code with `NODE_ID` set to 0 for the master base station, then upload to droid nodes with approriate numbers

Droids will report their status every `UPDATE_INTERVAL` milliseconds, and the master node will output all data to Serial as JSON

## License
[GNU GPL V3](https://github.com/daveflanagan-fi/DroidController/blob/master/LICENSE)

## Board

All the board gerber files can be found in the `Board` directory

![Top](https://raw.githubusercontent.com/daveflanagan-fi/DroidController/master/Board/top.png)![Bottom](https://raw.githubusercontent.com/daveflanagan-fi/DroidController/master/Board/bottom.png)

## Bill of Materials

### Capacitors
- C1 10µF Capacitor
- C2 10µF Capacitor
- C3 10µF Capacitor
- C4 10µF Capacitor
- C5 100nF Capacitor
- C6 100nF Capacitor
- C7 100nF Capacitor
- C8 100nF Capacitor

### ICs
- IC1 Voltage Regulator 5V 78005
- IC2 L293D
- U1 Atmega328 dip28

### Connectors
- J1 2 pins screw terminal 0.137in spacing
- J2 2 pins screw terminal 0.137in spacing
- J3 4 pins male header 0.1in spacing
- J4 4 pins male header 0.1in spacing
- J5 4 pins male header 0.1in spacing
- J6 4 pins male header 0.1in spacing
- J8 3 pins male header 0.1in spacing
- J9 3 pins male header 0.1in spacing

### LEDs
- LED1 Red 5mm

### Resistors
- R1 220Ω Resistor
- R2 10kΩ Resistor
- R3 1MΩ Resistor
- R4 100kΩ Resistor
- R5 10kΩ Resistor
- R6 10kΩ Resistor

### Misc
- Radio NRF24L01+
- S1 Push button
- XTAL2 16Mhz Crystal
- Program FTDI Programmer
