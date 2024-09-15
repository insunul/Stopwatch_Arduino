#include <LiquidCrystal.h>  // Include the library for the LCD display

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // Define the pins for the LCD

const int buttonStartStop = 2;  // Button for start/stop
const int buttonReset = 3;      // Button for reset

bool isRunning = false;  // Flag for stopwatch running state
unsigned long startTime = 0;
unsigned long elapsedTime = 0;

void setup() {
  pinMode(buttonStartStop, INPUT_PULLUP);  // Button for start/stop (with internal pullup resistor)
  pinMode(buttonReset, INPUT_PULLUP);      // Button for reset (with internal pullup resistor)
  
  lcd.begin(16, 2);  // Initialize the 16x2 LCD
  lcd.print("00:00:00");
}

void loop() {
  static bool lastButtonStartStopState = HIGH;  // Track last state of start/stop button
  static bool lastButtonResetState = HIGH;      // Track last state of reset button
  
  // Read button states
  bool currentButtonStartStopState = digitalRead(buttonStartStop);
  bool currentButtonResetState = digitalRead(buttonReset);
  
  // Handle start/stop button press
  if (currentButtonStartStopState == LOW && lastButtonStartStopState == HIGH) {
    isRunning = !isRunning;
    
    if (isRunning) {
      startTime = millis() - elapsedTime;  // Resume the stopwatch
    }
  }
  lastButtonStartStopState = currentButtonStartStopState;

  // Handle reset button press
  if (currentButtonResetState == LOW && lastButtonResetState == HIGH) {
    isRunning = false;
    elapsedTime = 0;
    lcd.setCursor(0, 0);
    lcd.print("00:00:00");
  }
  lastButtonResetState = currentButtonResetState;
  
  // Update the display if the stopwatch is running
  if (isRunning) {
    elapsedTime = millis() - startTime;
    
    unsigned long seconds = (elapsedTime / 1000) % 60;
    unsigned long minutes = (elapsedTime / 60000) % 60;
    unsigned long hours = (elapsedTime / 3600000);
    
    lcd.setCursor(0, 0);  // Set cursor to the beginning
    lcd.print((hours < 10 ? "0" : "") + String(hours) + ":");
    lcd.print((minutes < 10 ? "0" : "") + String(minutes) + ":");
    lcd.print((seconds < 10 ? "0" : "") + String(seconds));
  }
}
