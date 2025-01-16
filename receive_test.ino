void setup() {
  Serial.begin(9600);
  Serial.println("ZigBee Coordinator Initialized - Ready to Receive");
}

void loop() {
  if (Serial.available() > 0) {
    uint8_t frame[100];
    uint8_t index = 0;

    while (Serial.available() > 0) {
      frame[index++] = Serial.read();
      delay(10); 
    }

    if (index == 0) {
      Serial.println("No data received.");
      return;
    }

    Serial.print("Raw Frame: ");
    for (uint8_t i = 0; i < index; i++) {
      Serial.print(frame[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    processReceivedFrame(frame, index);
  } else {
    Serial.println("Waiting for data...");
    delay(1000); 
  }
}

void processReceivedFrame(uint8_t* frame, uint8_t length) {
  if (frame[0] != 0x7E) {
    Serial.println("Invalid Frame: Missing Start Delimiter");
    return;
    }

  uint16_t frameLength = (frame[1] << 8) | frame[2]; 
  if (frameLength != length - 3) { 
    Serial.println("Invalid Frame: Length Mismatch");
    return;
  }

  if (frame[3] == 0x91) {
    Serial.println("Valid API Frame Received");

    Serial.print("Sender MAC Address: ");
    for (int i = 4; i < 12; i++) {
      Serial.print(frame[i], HEX);
      if (i < 11) Serial.print(":");
    }
    Serial.println();

    Serial.print("Received Data: ");
    for (int i = 15; i < length - 1; i++) { 
      Serial.print((char)frame[i]); 
    }
    Serial.println();
  } else {
    Serial.println("Unsupported Frame Type");
  }
}