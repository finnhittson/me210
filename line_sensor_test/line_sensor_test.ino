const int lineSensor = A0;
const int threshold = 30;


void setup() {
  Serial.begin(9600);
  pinMode(lineSensor, INPUT);
}

void loop() {
  delay(1000);
  // Serial.println(analogRead(lineSensor));
  int sensor = analogRead(lineSensor);
  if (sensor > threshold) {
    Serial.println("off line");
  } else {
    Serial.println("on line");
  }
}
