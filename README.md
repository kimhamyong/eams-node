## Code Description
The Arduino UNO boards are connected with various sensors to detect pressure, sound, and human movement. Each Arduino UNO is connected to a ZigBee module and shield, allowing the collected sensor data to be transmitted to the home gateway using the ZigBee protocol.  

## ZigBee Settings
```
<Coordinator>
- ID: Set the same ID for all nodes to communicate.
- JV: Disabled
- CE: Enabled
- DH: 0
- DL: FFFF
- APL: API enabled with escape
- BD: 9600

<Router>
- ID: Set the same ID for all nodes to communicate.
- JV: Enabled
- DH, DL: Set to the coordinator's MAC address.
```

## End-Node Settings
```
- Arduino IDE Version: 2.2.1
- XCTU Version: 6.5.13.2
```

## End-Node Components
```
- Arduino UNO
- Pressure Sensor(FSR 402 Solder Tabs [30-81794])
- Sound Sens9or(SZH-EK033)
- PIR Sensor(HC-SR501)
- ZigBee Module(XBee ZigBee TH(S2C) - XB24CZ7WIT-004)
- XBee Shield(XBee Shield 3.0)
```
  
## Circuit Description
```
The connections between each sensor and the Arduino UNO board are as follows:

1. Pressure Sensor:
   - VCC: Connected to 5V on the Arduino
   - GND: Connected to GND on the Arduino
   - OUT: Connected to an analog pin on the Arduino(A0)

2. Sound Sensor:
   - VCC: Connected to 5V on the Arduino
   - GND: Connected to GND on the Arduino
   - OUT: Connected to an analog pin on the Arduino(A0)

3. PIR Sensor:
   - VCC: Connected to 5V on the Arduino
   - GND: Connected to GND on the Arduino
   - OUT: Connected to a digital pin on the Arduino(pin 13)

4. XBee Shield:
   - Mounted directly on top of the Arduino UNO board
   - The XBee module is inserted into the socket on the Shield
```   
