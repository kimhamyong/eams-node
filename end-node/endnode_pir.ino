//PIR sensor
int val = 0;
int sen = 13;

void setup() {
  pinMode(sen, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sen);

  if(val==1){
    Serial.write(67); 
    Serial.println("\nPIR Sensor Detected!");
  }

  delay(3000);
}
