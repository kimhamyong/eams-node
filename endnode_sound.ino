// Sound sensor setup
int val = 0;
int threshold = 200;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  val = analogRead(A0);  // Read pressure sensor value

  if (val > threshold) {
    sendXBeeAPIFrame("3");  // Send XBee API frame
    Serial.println("\nSound Sensor Detected!");
  }

  delay(3000);  // Wait 3 seconds before checking again
}

// Function to send XBee API frame (API Mode 2)
void sendXBeeAPIFrame(const char* message) {
  uint8_t frame[100];
  uint8_t index = 0;

  // Start delimiter
  frame[index++] = 0x7E;

  // Length calculation
  uint16_t length = 14 + strlen(message);
  frame[index++] = (length >> 8) & 0xFF;  // Length MSB
  frame[index++] = length & 0xFF;         // Length LSB

  // Frame Type: Transmit Request
  frame[index++] = 0x10;

  // Frame ID
  frame[index++] = 0x01;

  // Destination Address (64-bit MAC)
  frame[index++] = 0x00;
  frame[index++] = 0x13;
  frame[index++] = 0xA2;
  frame[index++] = 0x00;
  frame[index++] = 0x41;
  frame[index++] = 0xFC;
  frame[index++] = 0xB7;
  frame[index++] = 0xC4;

  // Network Address (Broadcast)
  frame[index++] = 0xFF;
  frame[index++] = 0xFE;

  // Broadcast Radius
  frame[index++] = 0x00;

  // Options
  frame[index++] = 0x00;

  // RF Data (Payload)
  for (size_t i = 0; i < strlen(message); i++) {
    frame[index++] = message[i];
  }

  // Checksum calculation
  uint8_t checksum = 0;
  for (uint8_t i = 3; i < index; i++) {
    checksum += frame[i];
  }
  checksum = 0xFF - checksum;
  frame[index++] = checksum;

  // Send frame via serial to XBee
  Serial.write(frame, index);
}
