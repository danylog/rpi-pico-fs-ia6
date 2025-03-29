//Settings :
#define BUTTONS 1  //enables the last two channels to work as gamepad buttons (the levers on the top part of the controller). If disabled (put 0), the channels can be used for VRA and VRB sliders.
#define NUM_CHANNELS 6
#define DIAGNOSTICS 1

#include <Joystick.h>

uint32_t lastTimes;

// Define the PWM pins for the FS-IA6 receiver
int pwmPins[NUM_CHANNELS] = { 2, 3, 4, 5, 6, 7 };

int16_t joystickValues[NUM_CHANNELS];

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



    //map the joystick values to 10-bit
    for (int i = 0; i < NUM_CHANNELS; i++) {
      joystickValues[i] = map(pwmValues[i], 995, 2000, 0, 1023);
      if (DIAGNOSTICS) {

        diagnostics(i);
      }
    }
        Serial.println(" ");

    // Update joystick values
    Joystick.use10bit();
    Joystick.X(joystickValues[0]);
    Joystick.Y(joystickValues[1]);
    Joystick.Z(joystickValues[2]);
    Joystick.Zrotate(joystickValues[3]);

    //Buttons routine
    if (BUTTONS) {

      for (int i = 1; i <= 2; i++) {
        if (joystickValues[3 + i] > 900) {
          Joystick.button(i, true);

        } else {
          Joystick.button(i, false);
        }
      }

    } else {
      Joystick.sliderLeft(joystickValues[4]);
      Joystick.sliderRight(joystickValues[5]);
    }
  }
}