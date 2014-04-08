#include <LiquidCrystal.h>
#define PIN_CONTRAST_ANALOG 8

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(14,15,16,17,18,19,20);


void setup() { 
  pinMode(PIN_CONTRAST_ANALOG, INPUT);
  lcd.begin(16, 2);
  analogReference(INTERNAL2V56);
}

void loop() {
  int analogReading = analogRead(PIN_CONTRAST_ANALOG);
  lcd.setCursor(0, 0);
  lcd.print("Reading = ");
  lcd.print(analogReading);
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print("Voltage = ");
  lcd.print( (float) analogReading / 1023.0 * 2.56);
  lcd.print("  ");
}
