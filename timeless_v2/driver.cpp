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
      // 95 -> (95 + implicit 1) -> count of 96 -> 8MHz / 1024 prescaler / 96 counts = 81.4Hz
      uint8_t period = BASE_MAG_PERIOD;
      OCR0A = period; // Period
      OCR0B = ((period+1) >> 1);
      break;
    case ADA_TRINK_OC1B: // PWM LED Pin -> Timer 1 Output Compare B
      // Set Compare Output Mode - Fast PWM Mode -> 2 (Non Inverting Compare Match)
      GTCCR = 0x20;// Set PWM1B = PWM B Enable

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

int make_linear(int pot_val)
{
  int out;
  int frac = ANA_MAX_3V3_READ / 4;
  if (pot_val < 0)
  {
    out = 0;
  }
  else if (pot_val < 50)
  {
    out = map(pot_val, 0, 50, 0, frac);
  }
  else if (pot_val < 117)
  {
    out = map(pot_val, 50, 117, frac, 2*frac);
  }
  else if (pot_val < 340)
  {
    out = map(pot_val, 117, 340, 2*frac, 3*frac);
  }
  else
  {
    out = map(pot_val, 340, ANA_MAX_3V3_READ, 3*frac, 4*frac);
  }
  return out;
}
