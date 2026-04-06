#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Example display (can be linked with main logic later)
  lcd.setCursor(0, 0);
  lcd.print("Slot Status:");

  lcd.setCursor(0, 1);
  lcd.print("Checking...");
  
  delay(1000);
}
