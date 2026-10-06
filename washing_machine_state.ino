#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

//connection
//LCD 12c, touch sensor (8), motor 

//variable button debounces
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1;
int touchSensorPin = 8;

//record the hold duration when button is high 
unsigned long StartTime = 0;
int TargetHoldTime = 500;
const unsigned long intervalSecond = 1000;

int machineState = 1;
//  1= welcome (Welcome screen)
//  2= main screen 
//  3= mode seletion 
//  4= fast wash
//  5= slow wash 

// function for pointer positions
const int column = 16;
const int row = 2;
LiquidCrystal_I2C lcd(0x27, column, row);
int pointerPositionnRow = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

}

void loop() {


  if (machineState = 1) {
    welcomeScreen();

  }
else if (machineState = 2) {
  menuSelection();
}
}


void welcomeScreen() {
  while(machineState = 1) {
  lcd.setCursor(0, 0);
  lcd.print("HELLO! WELCOME!");
delay(3000);
  lcd.clear();
  machineState = 2;
  menuSelection();
  }
}

void menuSelection() {
  
  int changeScreenTab = 0;

  while (machineState = 2) {
  lcd.setCursor(0, 0);
  lcd.print("SELECTION MODE");
  delay(2000);
  lcd.clear();
  int changeScreenTab = 1;


while (changeScreenTab = 1) {
    lcd.setCursor(0, pointerPositionnRow);
    lcd.print("> ");
    lcd.setCursor(2, 0);
    lcd.print("FAST wash");
    lcd.setCursor(2, 1);
    lcd.print("SLOW wash");

 int reading = digitalRead(touchSensorPin);

 Serial.println(debounceDelay);


 if (reading != lastButtonState) {

  lastDebounceTime = millis();
 }

 if((millis() - lastDebounceTime) > debounceDelay) {

  if (reading != buttonState) {
    buttonState = reading;

    if (buttonState == HIGH) {
   pointerPositionnRow++;
    lcd.clear();
    }
   }  
  }
   lastButtonState = reading;
   
   if(pointerPositionnRow >= 2) {
   pointerPositionnRow = 0;
   lcd.clear(); //jika posisi lebih dari 2 atau lebih dari jumlah kolumn, maka posisi akan balek jadi 0 lagi
    }
  }
}

}


void fastWash() {
  lcd.clear();
  lcd.print("entered fast wash");
}
