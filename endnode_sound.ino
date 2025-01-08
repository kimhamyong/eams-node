//Sound sensor
int val = 0;
int threshold = 200;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);
  
  if(val>threshold){
    Serial.write(66); 
    Serial.println("\nSound Sensor Detected!");
  }

  delay(3000);
}
