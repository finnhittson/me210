const int triggerPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() {
	Serial.begin(9600);
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

void loop() {
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration * 0.034 / 2;
	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" cm");
	delay(1000);
}
