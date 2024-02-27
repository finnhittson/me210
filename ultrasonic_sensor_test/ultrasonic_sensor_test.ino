const int triggerPin = 9;
const int echoPin = 10;

unsigned long duration;
float distance;
unsigned long lastTime;
unsigned long trigDur = 10;        // [micros] trigger on for 10 microseconds
unsigned long pulseDur = 200;      // [micros] wait to read after 8 cycles ot 40kHz sonic burst
unsigned long cycleDur = 60000;    // [micros] sensing cycle >60ms
bool needTrig = true;
bool needPulse = false;
bool needRead = false;
bool needCycle = false;

void setup() {
	Serial.begin(9600);
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);

  lastTime = micros();
  digitalWrite(triggerPin, LOW);  // no trigger signal
}

void loop() {
  if (needTrig) {
    if (micros() - lastTime < trigDur) {    // trigger hasn't been on long enough
      digitalWrite(triggerPin, HIGH); 
    }
    else {  // do pulse next
      needTrig = false;
      needPulse = true;
      lastTime = micros();
    }
  }
  
  if (needPulse) {
    if (micros() - lastTime < pulseDur) {    // hasn't waited long enough for pulse to send
      digitalWrite(triggerPin, LOW);    // trigger off
    }
    else {  // read signal next
      needPulse = false;
      needRead = true;
      lastTime = micros();
    }
  }

  if (needRead) {   // read the signal
    duration = pulseIn(echoPin, HIGH);
    distance =  duration * (1125.33*12/1000000) / 2;   // duration * 0.0343 / 2; for cm
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" in");
    needRead = false;
    needCycle = true;
    lastTime = micros();
  }

  if (needCycle) {
    if (micros() - lastTime < cycleDur) {  // wait for recommended measurement cycle
    }
    else {  // send trigger next
      needCycle = false;
      needTrig = true;
      lastTime = micros();
    }
  }

}

void BlockingExample() {
  // basic example using blocking code
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
