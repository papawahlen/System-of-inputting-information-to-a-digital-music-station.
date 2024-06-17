#include <LiquidCrystal_I2C.h>
#include <Control_Surface.h> 
#include <Wire.h>


USBMIDI_Interface midi;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPins[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);


NoteButton buttonMatrix[numButtons] = {
  {buttonPins[0], 0}, {buttonPins[1], 1}, {buttonPins[2], 2},
  {buttonPins[3], 3}, {buttonPins[4], 4}, {buttonPins[5], 5},
  {buttonPins[6], 6}, {buttonPins[7], 7}, {buttonPins[8], 8},
  {buttonPins[9], 9}, {buttonPins[10], 10}, {buttonPins[11], 11}
};


CCPotentiometer potentiometers[] = {
  {A0, 1}, 
  {A1, 2}, 
  {A2, 3}  
};


int lastButtonState[numButtons] = {0};
int lastPotValues[3] = {0};

void setup() {
  
  Control_Surface.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MIDI Controller");
  delay(1000);
  lcd.clear();
}

void loop() {
  Control_Surface.loop();


  for (int i = 0; i < numButtons; i++) {
    int currentState = digitalRead(buttonPins[i]);
    if (currentState != lastButtonState[i]) {
      lastButtonState[i] = currentState;
      if (currentState == HIGH) { 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button Pressed:");
        lcd.setCursor(0, 1);
        lcd.print("Note ");
        lcd.print(i);
        delay(100);
      }
    }
  }

  
  int potPins[] = {A0, A1, A2};
  for (int i = 0; i < 3; i++) {
    int potValue = analogRead(potPins[i]);
    potValue = map(potValue, 0, 1023, 0, 127); 
    if (potValue != lastPotValues[i]) {
      lastPotValues[i] = potValue;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Potentiometer ");
      lcd.print(i + 1);
      lcd.setCursor(0, 1);
      lcd.print("Value: ");
      lcd.print(potValue);
      delay(100);
    }
  }
}

