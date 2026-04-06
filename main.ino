// Smart Parking System - Main Code

#define IR_SENSOR 2
#define TRIG_PIN 3
#define ECHO_PIN 4
#define LED_OCCUPIED 5
#define LED_FREE 6

long duration;
int distance;
bool isOccupied = false;

void setup() {
  Serial.begin(9600);

  pinMode(IR_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_OCCUPIED, OUTPUT);
  pinMode(LED_FREE, OUTPUT);
}

void loop() {
  int irStatus = digitalRead(IR_SENSOR);
  distance = getDistance();

  // Sensor Fusion Logic
  if (irStatus == LOW && distance < 10) {
    isOccupied = true;
  } else {
    isOccupied = false;
  }

  // Output Control
  if (isOccupied) {
    digitalWrite(LED_OCCUPIED, HIGH);
    digitalWrite(LED_FREE, LOW);
    Serial.println("Slot: OCCUPIED");
  } else {
    digitalWrite(LED_OCCUPIED, LOW);
    digitalWrite(LED_FREE, HIGH);
    Serial.println("Slot: FREE");
  }

  delay(1000);
}

// Ultrasonic Distance Function
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}
