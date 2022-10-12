#include "ex_cpp.hh"
#include "pins.hh"

// ---------------------------------------------------------------------------------------------------------------
// Application prototypes
bool magnet_detected(void);
uint32_t duration_sw_held(void);
bool showtime_expired(void);
void start_animation(void);
void stop_animation(void);

// ---------------------------------------------------------------------------------------------------------------
// Application functions

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
  start_pwms();
}
