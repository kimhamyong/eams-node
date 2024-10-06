//Pressure sensor
int val = 0;
int threshold = 700;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);

  if(val>threshold){
    Serial.write(65); 
    Serial.println("\nPressure Sensor Detected!");
  }

  delay(3000);
}
