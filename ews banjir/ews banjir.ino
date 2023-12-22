// Flood Early Warning System using Ultrasonic Sensor and Arduino with Tone Alert

const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = A5;
const int ledPins[8] = {9, 8, 7, 6, 5, 4, 3, 2};

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {

  // Measure water level with ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2) * 0.0343;
  float waterLevel = 500 - distance;

  // Calculate percentage
  int percentage = (waterLevel / 500) * 100;

  // Display data on serial monitor
  Serial.print("Sensor Height: ");
  Serial.print(distance);
  Serial.print(" cm, Water Level: ");
  Serial.print(waterLevel);
  Serial.print(" cm, Percentage: ");
  Serial.print(percentage);
  Serial.println("%");

  // Check for danger and activate tone alert
  if (percentage >= 75) {
    tone(buzzerPin, 1000); // Activate tone alert
    Serial.println("Danger! Flood Warning!");
  } else {
    noTone(buzzerPin); // Deactivate tone alert
    Serial.println("Safe");
  }

  // Display percentage on LEDs
  int ledCount = (percentage * 8) / 99;
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], i < ledCount);
  }

  delay(1000); // Delay for stability
}
