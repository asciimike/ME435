#include <LiquidCrystal.h>

/***  Pin I/O   ***/ 
#define PIN_LED_1 64
#define PIN_LED_2 65
#define PIN_LED_3 66
#define PIN_LED_4 67
#define PIN_LED_5 68
#define PIN_LED_6 69
#define PIN_RIGHT_BUTTON 2
#define PIN_LEFT_BUTTON 3
#define PIN_SELECT_BUTTON 21
#define PIN_CONTRAST_ANALOG 8
#define PIN_HORZ_ANALOG 0
#define PIN_VERT_ANALOG 1

#define FLAG_INTERRUPT_0 1<<0
#define FLAG_INTERRUPT_1 1<<1
#define FLAG_INTERRUPT_2 1<<2

#define MAX_SELECTED 5
#define MIN_SELECTED 0

#define MAX_ANGLE 180
#define MIN_ANGLE 0

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(14,15,16,17,18,19,20);

volatile int mainEventFlags = 0;

int currentSelected = 0;
int jointAngles[6] = {90,90,90,90,90,90};

void setup() { 
  pinMode(PIN_CONTRAST_ANALOG, INPUT);
  
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);
  pinMode(PIN_LED_6, OUTPUT);
  pinMode(PIN_RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LEFT_BUTTON, INPUT_PULLUP);
  pinMode(PIN_SELECT_BUTTON, INPUT_PULLUP);
  attachInterrupt(0, int0_isr, FALLING);
  attachInterrupt(1, int1_isr, FALLING);
  attachInterrupt(2, int2_isr, FALLING);
  pinMode(PIN_HORZ_ANALOG,INPUT);
  pinMode(PIN_VERT_ANALOG,INPUT);
  
  digitalWrite(PIN_LED_2, LOW);
  digitalWrite(PIN_LED_4, LOW);
  digitalWrite(PIN_LED_6, LOW);
        
  lcd.begin(16, 2);
  setLEDn(currentSelected);
//  analogReference(INTERNAL2V56);
}

void loop() {
    if (mainEventFlags & FLAG_INTERRUPT_0) {
      delay(20);
      mainEventFlags &= ~FLAG_INTERRUPT_0;
      if (!digitalRead(PIN_RIGHT_BUTTON)) {
        currentSelected++;
        if(currentSelected > MAX_SELECTED) {
          currentSelected = MIN_SELECTED;
        }
        setLEDn(currentSelected);
      }
    }
    
    
  if (mainEventFlags & FLAG_INTERRUPT_1) {
      delay(20);
      mainEventFlags &= ~FLAG_INTERRUPT_1;
      if (!digitalRead(PIN_LEFT_BUTTON)) {
        currentSelected--;
        if(currentSelected < MIN_SELECTED) {
          currentSelected = MAX_SELECTED;
        }
        setLEDn(currentSelected);
      }
  }
  
  if (mainEventFlags & FLAG_INTERRUPT_2) {
      delay(20);
      mainEventFlags &= ~FLAG_INTERRUPT_2;
      if (!digitalRead(PIN_SELECT_BUTTON)) {
          jointAngles[currentSelected] = 90;
      }
  }
  
  updateJointValue(currentSelected);
  updateLCD();
}

void int0_isr() {
    mainEventFlags |= FLAG_INTERRUPT_0;
}

void int1_isr() {
    mainEventFlags |= FLAG_INTERRUPT_1;
}

void int2_isr() {
    mainEventFlags |= FLAG_INTERRUPT_2;
}

void setLEDn(int n) {
  switch (n) {
    case 0:
      digitalWrite(PIN_LED_1, HIGH);
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, LOW);
      digitalWrite(PIN_LED_5, LOW);
      digitalWrite(PIN_LED_6, LOW);
      break;
    
    case 1:
      digitalWrite(PIN_LED_1, LOW);
      digitalWrite(PIN_LED_2, HIGH);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, LOW);
      digitalWrite(PIN_LED_5, LOW);
      digitalWrite(PIN_LED_6, LOW);
      break;
    
    case 2:
      digitalWrite(PIN_LED_1, LOW);
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, HIGH);
      digitalWrite(PIN_LED_4, LOW);
      digitalWrite(PIN_LED_5, LOW);
      digitalWrite(PIN_LED_6, LOW);
      break;
    
    case 3:
      digitalWrite(PIN_LED_1, LOW);
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, HIGH);
      digitalWrite(PIN_LED_5, LOW);
      digitalWrite(PIN_LED_6, LOW);
      break;
    
    case 4:
      digitalWrite(PIN_LED_1, LOW);
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, LOW);
      digitalWrite(PIN_LED_5, HIGH);
      digitalWrite(PIN_LED_6, LOW);
      break;
    
    case 5:
      digitalWrite(PIN_LED_1, LOW);
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, LOW);
      digitalWrite(PIN_LED_5, LOW);
      digitalWrite(PIN_LED_6, HIGH);
      break;
    
    default:
      digitalWrite(PIN_LED_1, LOW);
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, LOW);
      digitalWrite(PIN_LED_5, LOW);
      digitalWrite(PIN_LED_6, LOW);
      break;
  }
}

void updateJointValue(int j)
{
  int hReading = analogRead(PIN_HORZ_ANALOG);
  int vReading = analogRead(PIN_VERT_ANALOG);
  if (hReading > 900) {
    jointAngles[j] += 1;
    if(jointAngles[j] > MAX_ANGLE) {
      jointAngles[j] = MAX_ANGLE;
    }
  } else if (hReading < 100) {
    jointAngles[j] -= 1;
    if(jointAngles[j] < MIN_ANGLE) {
      jointAngles[j] = MIN_ANGLE;
    }
  }
  
  if (vReading > 900) {
    jointAngles[j] += 4;
    if(jointAngles[j] > MAX_ANGLE) {
      jointAngles[j] = MAX_ANGLE;
    }
  } else if (vReading < 100) {
    jointAngles[j] -= 4;
    if(jointAngles[j] < MIN_ANGLE) {
      jointAngles[j] = MIN_ANGLE;
    }
  }
  delay(100);
}

void updateLCD() {
  char buf[5];
  lcd.setCursor(0, 0);
  snprintf(buf, 6, "%d   ", jointAngles[0]);
  lcd.print(buf);
  snprintf(buf, 6, "%d   ", jointAngles[1]);
  lcd.print(buf);
  snprintf(buf, 6, "%d   ", jointAngles[2]);
  lcd.print(buf);
  lcd.setCursor(0, 1);
  snprintf(buf, 6, "%d   ", jointAngles[3]);
  lcd.print(buf);
  snprintf(buf, 6, "%d   ", jointAngles[4]);
  lcd.print(buf);
  snprintf(buf, 6, "%d   ", jointAngles[5]);
  lcd.print(buf);
}

