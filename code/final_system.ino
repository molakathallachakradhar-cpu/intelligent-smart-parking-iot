// FINAL INTEGRATED SMART PARKING SYSTEM

#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// LCD Setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensor Pins
#define IR_SENSOR 2
#define TRIG_PIN 3
#define ECHO_PIN 4
#define LED_OCCUPIED 6
#define LED_FREE 7

WiFiServer server(80);

long duration;
int distance;
bool isOccupied = false;

void setup() {
  Serial.begin(9600);

  // Pin Modes
  pinMode(IR_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_OCCUPIED, OUTPUT);
  pinMode(LED_FREE, OUTPUT);

  // LCD Init
  lcd.begin(16, 2);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();

  // WiFi Init
  WiFi.begin(ssid, password);
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("WiFi Connected");

  server.begin();
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

  // LED Output
  if (isOccupied) {
    digitalWrite(LED_OCCUPIED, HIGH);
    digitalWrite(LED_FREE, LOW);
  } else {
    digitalWrite(LED_OCCUPIED, LOW);
    digitalWrite(LED_FREE, HIGH);
  }

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Slot Status:");

  lcd.setCursor(0, 1);
  if (isOccupied) {
    lcd.print("OCCUPIED");
  } else {
    lcd.print("FREE");
  }

  // WiFi Server
  WiFiClient client = server.available();
  if (client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<html><body>");
    client.println("<h1>Smart Parking</h1>");
    if (isOccupied) {
      client.println("<p>Status: OCCUPIED</p>");
    } else {
      client.println("<p>Status: FREE</p>");
    }
    client.println("</body></html>");

    client.stop();
  }

  delay(1000);
}

// Ultrasonic Function
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
