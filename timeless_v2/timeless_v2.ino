//
// Filename: timeless_v2.cpp
// Author: Beau Roland
// Details: Application Source File
//   Contains all the application source code.
// Date: 2/5/23
//

#include "driver.hh"
#include "pins.hh"

// ---------------------------------------------------------------------------------------------------------------
// Application prototypes
// (none)

// ---------------------------------------------------------------------------------------------------------------
// Application functions
// (none)

// ---------------------------------------------------------------------------------------------------------------
// Arduino Setup
void setup() {
  // Init Led PWM pin as digital output and PWM that is turned off
  init_pwm_pin(PWM_LED_PIN);

  // Init Mag PWM pin as digital output and PWM that is turned off
  init_pwm_pin(PWM_MAG_PIN);
}

// Arduino Main Loop
void loop() {
  // Turn on PWMs (if not already on already)
  // Update the LED PWM duty and period according to the voltages read from the potentiometers.
  start_pwms();
}
