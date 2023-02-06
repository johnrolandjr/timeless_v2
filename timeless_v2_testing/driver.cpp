//
// Filename: driver.cpp
// Author: Beau Roland
// Details: Driver C++ Source file
//   Contains all the source code for the different functional blocks used in the application.
// Date: 7/31/22
//

#include <Arduino.h>
#include "driver.hh"
#include "pins.hh"

void init_pwm_pin(uint32_t pwm_pin)
{
  switch (pwm_pin)
  {
    case ADA_TRINK_OC0B: // PWM Magnet Pin -> Timer 0 Output Compare B
      // Set Compare Output Mode - Fast PWM Mode -> 2 (Non Inverting Compare Match)
      TCCR0A = (0x02 << 4);
      
      // WGM set to FastPWM(=7) (updated at OCRA)
      TCCR0A |= (0x03); // bits[1:0] of wgm
      TCCR0B  = (0x08); // bit[2] of wgm

      // MAG PWM Duty 50% with Period set to 80Hz
      // MAG PWM frequency/period will not change, setting here.
      // 98 -> 8MHz clock / 1024 prescaler / 98 tick periods = 80Hz
      uint8_t period = BASE_MAG_PERIOD;
      OCR0A = period;
      OCR0B = ((period) >> 1); // Setting to 50% duty (magnet will always be at 50% for max pu)
      break;
    case ADA_TRINK_OC1B: // PWM LED Pin -> Timer 1 Output Compare B
      // Set Compare Output Mode - Fast PWM Mode -> 2 (Non Inverting Compare Match)
      GTCCR = 0x40 | 0x20; // Set PWM1B (PWM B Enable) + COM1B set to 10, non inverting of OC1B PWM

      // PWM mode is different on Timer 1. Match Event OCR1B and Counter Reset when matched with OCR1C
      // Not setting the period or duty as it will change
      break;
    default:
      // Invalid/Unexpected Pin initialized!
      return;
  }

  // Initialize pwm pin as digital output
  pinMode(pwm_pin, OUTPUT);
}

void start_pwms(void)
{
  //Update led pwm and duty
  update_led();

  // Start PWMs by setting the clock
  // Set Clock Prescaler for Timer0 (CLKio / 1024 =5)
  TCCR0B |= 0x05;
  // Set Clock Prescaler for Timer1 (CLKio / 1024 =0xB)
  // Set Clock Prescaler for Timer1 (CLKio / 1024 =0xB)
  TCCR1 = _BV(CS13) | _BV(CS11) | _BV(CS10);
  GTCCR = _BV(COM1B1) | _BV(PWM1B);  //  Noninverting + Enable PWM on OCR1B
}

void update_led(void)
{
  uint8_t led_period;
  uint8_t led_on_period;

  calculate_led_pwm(&led_period, &led_on_period);
  
  // Update Led Period and Duty
  OCR1C = led_period;
  OCR1B = led_on_period;
}

void calculate_led_pwm(uint8_t * p_period, uint8_t * p_on_period)
{
  uint8_t period;
  uint8_t period_delta;
  uint8_t period_shift_duty;
  
  // CLKsys (8Mhz) prescaled(1024) = 7812 Hz --> Range of (31Hz - 7812Hz) (~0.3Hz / tick)
  period = BASE_LED_PERIOD;

  // Calculate both duty values (0x00 - 0xFF)
  int delta_pot_val = analogRead(DELTA_POT_PIN);
  period_shift_duty = get_delta(delta_pot_val); // (~0.3Hz / tick)
  int brightness_pot_val = analogRead(BRIGHTNESS_POT_PIN);
  uint8_t led_duty = get_delta(brightness_pot_val);

  // Update the frequencies prior to turning them on
  period_delta = map(period_shift_duty, 0, 0xFF, 0, 60);
  *p_period = (period + period_delta);
  *p_on_period = map(led_duty, 0, 255, 5, *p_period);
}

uint8_t get_delta(int pot_val)
{
  uint32_t delta = 0;
  uint8_t ret = 0;

  // Before we do anything, make the pot value more linear
  pot_val = make_linear(pot_val);
  
  if (pot_val < 0)
  {
    pot_val = 0;
  }

  if (pot_val >= ANA_MAX_3V3_READ)
  {
    ret = 0xFF;
  }
  else
  {
    delta = (uint32_t) pot_val;
    delta = ((delta << 8) / ANA_MAX_3V3_READ);
    ret = (uint8_t) delta;
  }
  
  // get_delta should never return 0 or 255 as we always want some sort of PWM
  if (ret == 0)
  {
    ret = 1;
  }
  else if (ret >= 0xFF)
  {
    ret = 0xFE;
  }
  return ret;
}

// Examined extrapolation (nonlinear) for steps
#define ACT_MIN 0
#define ACT_25P 240
#define ACT_50P 523
#define ACT_75P 800
#define ACT_MAX 1023
// Linear steps from 0 to 255
// Translating to range of 0-255 for pwm control
#define FRAC_MIN 0
#define FRAC_25P 64
#define FRAC_50P 128
#define FRAC_75P 192
#define FRAC_MAX 255
int make_linear(int pot_val)
{
  int out;
  if (pot_val < 0)
  {
    out = 0;
  }
  else if (pot_val < ACT_25P)
  {
    out = map(pot_val, ACT_MIN, ACT_25P, FRAC_MIN, FRAC_25P);
  }
  else if (pot_val < ACT_50P)
  {
    out = map(pot_val, ACT_25P, ACT_50P, FRAC_25P, FRAC_50P);
  }
  else if (pot_val < ACT_75P)
  {
    out = map(pot_val, ACT_50P, ACT_75P, FRAC_50P, FRAC_75P);
  }
  else
  {
    out = map(pot_val, ACT_75P, ACT_MAX, FRAC_75P, FRAC_MAX);
  }
  return out;
}
