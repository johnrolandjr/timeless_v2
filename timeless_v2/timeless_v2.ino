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
  // Setup System Prescaler
  //CLKPR = _BV(CLKPCE);  // enable change of the clock prescaler
  //CLKPR = 4;  // divide frequency by 16(=4)
  
  // WGM set to FastPWM
  //TCCR2A = 0x3;
  //TCCR2B = 0x08;

  // Init Led PWM pin as digital output and PWM that is turned off
  //init_pwm_pin(PWM_LED_PIN);

  // Init Mag PWM pin as digital output and PWM that is turned off
  init_pwm_pin(PWM_MAG_PIN);

  // Initialize mag pwm pin as digital output
  //pinMode(PWM_MAG_PIN, OUTPUT);

  // Initialize magnet pin as digital input
  //pinMode(MAG_DETECT_PIN, INPUT);

  // Initialize backup switch as digital input
  //pinMode(BK_UP_PIN, INPUT);
}

// Arduino Main Loop
void loop() {
  start_pwms();
}
