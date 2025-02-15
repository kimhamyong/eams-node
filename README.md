# Elderly Activity Monitoring System
This project aims to prevent lonely deaths among elderly individuals living alone by providing a privacy-friendly home monitoring solution. Unlike traditional monitoring systems, this approach does not use cameras or wearable devices, ensuring a non-intrusive and respectful solution for elderly care.
The system utilizes various sensors to track motion and activity patterns, transmitting data via a home gateway. If prolonged inactivity is detected, a warning message is sent to caregivers via the user interface.

**This project is divided into multiple repositories:**  
[Click Details] -> **[End-Node](https://github.com/kimhamyong/eams-node)**, **[Home-Gateway](https://github.com/kimhamyong/eams-gateway)**, **[Server](https://github.com/kimhamyong/eams-server)**

```   
 ┌──────────────┐           ┌──────────────────┐           ┌────────────┐           ┌────────┐
 │   End Node   │     →     │   Home Gateway   │     →     │   Server   │     →     │   UI   │
 └──────────────┘           │         │        │           └────────────┘           └────────┘
                   (ZigBee) │         │        │   (MQTT)                (WebSocket)
                            │    MQTT Broker   │
                            └──────────────────┘  
```

## Overview
The Arduino UNO boards are connected with various sensors to detect pressure, sound, and human movement. Each Arduino UNO is connected to a ZigBee module and shield, allowing the collected sensor data to be transmitted to the home gateway using the ZigBee protocol.  

## Setup & Install

1. **Initialize Arduino Board** (Without XBee Shield)  
- Connect the board to your computer, install [Arduino IDE](https://www.arduino.cc/en/software), and select the correct **Board** and **Port** in **Tools**.  
 - Upload an empty sketch to reset the board:  
     ```cpp
     void setup() {}  
     void loop() {}
     ```  

2. **Install XCTU & Configure XBee**  
- [Download XCTU](https://www.digi.com/resources/documentation/digidocs/90001526/tasks/t_download_and_install_xctu.htm) and install it.  
- Attach the XBee shield, set it to **USB mode**, and configure the module in XCTU using [ZigBee Settings](#zigbee-settings).

3. **Upload Code & Enable XBee Communication**  
- Keep the XBee shield in **USB mode** and use Arduino IDE to upload the required code.  
- After uploading, switch the XBee shield to **XBee mode** and start communication.  



## ZigBee Settings
```
<Coordinator>
- ID: Set the same ID for all nodes to communicate.
- JV: Disabled
- CE: Enabled
- DH: 0
- DL: FFFF
- API: API enabled with escaping
- BD: 9600

<Router>
- ID: Set the same ID for all nodes to communicate.
- JV: Enabled
- DH, DL: Set to the coordinator's MAC address.
- API: API enabled with escaping
```

## API 2 Mode Data Explanation

### ZigBee API 2 Mode Overview

- Ensures reliable transmission by escaping specific control bytes (`0x7E`, `0x7D`, `0x11`, `0x13`).  
- Escaped bytes are prefixed with `0x7D` and XOR-ed with `0x20`, requiring decoding. 
- **Decoding rule:** Any byte after `0x7D` must be XOR-ed with `0x20` to restore its original value.  
- Example: `7D 33` → `33 ^ 20 = 13` → Restored to `0x13`. 

### Example of Received API 2 Frame
When using sensor data transmission via XBee in API 2 Mode, a received frame may look like this: 
```
7E 00 0D 90 00 7D 33 A2 00 41 FC B7 A4 12 9A 01 34 41
```


### Breakdown of the Frame

| Byte(s)                      | Description                | Value                 | Explanation                                   |
| ---------------------------- | -------------------------- | --------------------- | --------------------------------------------- |
| `7E`                         | Start Delimiter            | `0x7E`                | Indicates the beginning of an API frame.      |
| `00 0D`                      | Length                     | `0x000D` (13 bytes)   | Length of the remaining bytes in the frame.   |
| `90`                         | Frame Type                 | `0x90` (RX Indicator) | Received data frame from another XBee device. |
| `00 7D 33 A2 00 41 FC B7 A4` | Source Address             | `0x0013A20041FCB7A4`  | MAC address of the sender (escaped).          |
| `12 9A`                      | **16-bit Network Address** | `0x129A`              | Network address of the sender.                |
| `01`                         | **Receive Options**        | `0x01`                | Acknowledgment received.                      |
| `34`                         | **RF Data**                | `0x34`                | Actual data payload received.                 |
| `41`                         | **Checksum**               | `0x41`                | Validates data integrity.                     |


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
