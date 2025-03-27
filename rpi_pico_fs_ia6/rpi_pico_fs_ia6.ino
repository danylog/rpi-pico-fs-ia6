#include <Joystick.h>

#define NUM_CHANNELS 6
uint32_t lastTimes;
// Define the PWM pins for the FS-IA6 receiver
int pwmPins[NUM_CHANNELS] = { 2, 3, 4, 5, 6, 7 };

// Array to store PWM values
volatile uint16_t pwmValues[NUM_CHANNELS];



void pwmISR0() {
  handlePWM(0);
}
void pwmISR1() {
  handlePWM(1);
}
void pwmISR2() {
  handlePWM(2);
}
void pwmISR3() {
  handlePWM(3);
}
void pwmISR4() {
  handlePWM(4);
}
void pwmISR5() {
  handlePWM(5);
}

void handlePWM(int channel) {
  static uint32_t lastTime[NUM_CHANNELS] = { 0 };
  uint32_t currentTime = micros();
  pwmValues[channel] = currentTime - lastTime[channel];
  lastTime[channel] = currentTime;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting FlySky to Joystick Converter");

  // Initialize PWM pins and attach interrupts
  pinMode(pwmPins[0], INPUT);
  pinMode(pwmPins[1], INPUT);
  pinMode(pwmPins[2], INPUT);
  pinMode(pwmPins[3], INPUT);
  pinMode(pwmPins[4], INPUT);
  pinMode(pwmPins[5], INPUT);

  attachInterrupt(digitalPinToInterrupt(pwmPins[0]), pwmISR0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pwmPins[1]), pwmISR1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pwmPins[2]), pwmISR2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pwmPins[3]), pwmISR3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pwmPins[4]), pwmISR4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pwmPins[5]), pwmISR5, CHANGE);

  // Initialize Joystick library
  Joystick.begin();
}

void loop() {
  
  if (millis() - lastTimes >= 100) {
    lastTimes = millis();
    int16_t joystickValues[NUM_CHANNELS];
    for (int i = 0; i < NUM_CHANNELS; i++) {
      joystickValues[i] = map(pwmValues[i], 995, 2000, 0, 1023);
      Serial.print("Channel ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(pwmValues[i]);
    }

    // Update joystick values
    Joystick.use10bit();
    Joystick.X(joystickValues[0]);
    Joystick.Y(joystickValues[1]);
    Joystick.Z(joystickValues[2]);
    Joystick.Zrotate(joystickValues[3]);
    for (int i = 1; i <= 2; i++) {
      if (pwmValues[3 + i] > 1100) {
        Joystick.button(i, true);
      } else {
        Joystick.button(i, false);
      }
    }
  }
}