#include <LiquidCrystal.h>
#define RIGHT_BUTTON 2
#define LEFT_BUTTON 3
#define FLAG_INTERRUPT_0 1<<0
#define FLAG_INTERRUPT_1 1<<1
#define FLAG_INTERRUPT_2 1<<2

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(14,15,16,17,18,19,20);

volatile int age = 0;
volatile int mainEventFlags = 0;

void setup() {
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  
  attachInterrupt(0, int0_isr, FALLING);
  attachInterrupt(1, int1_isr, FALLING);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Mike McDonald is");
}

void loop() {
  if (mainEventFlags & FLAG_INTERRUPT_0) {
      delay(20);
      mainEventFlags &= ~FLAG_INTERRUPT_0;
      if (!digitalRead(RIGHT_BUTTON)) {
        age++;
      }
    }
  if (mainEventFlags & FLAG_INTERRUPT_1) {
      delay(20);
      mainEventFlags &= ~FLAG_INTERRUPT_1;
      if (!digitalRead(LEFT_BUTTON)) {
        age--;
      }
  }
  lcd.setCursor(0, 1);
  lcd.print(age);
  lcd.print(" years old");
  delay(10);
  lcd.setCursor(0, 1);
  lcd.print("                  ");
}

void int0_isr() {
  mainEventFlags |= FLAG_INTERRUPT_0;
}

void int1_isr() {
  mainEventFlags |= FLAG_INTERRUPT_1;
}
