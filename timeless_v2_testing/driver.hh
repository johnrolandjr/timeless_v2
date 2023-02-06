//
// Filename: driver.hh
// Author: Beau Roland
// Details: Driver C++ Header file
//   Contains all the needed defines, externs, and function prototypes for the application
// Date: 2/5/23
//

#ifndef EX_CPP_H
#define EX_CPP_H

//---------
//DEFINES, CONSTANTS, LITERALS
#define ANA_MAX_3V3_READ (755)

#define BASE_MAG_PERIOD (98)
#define BASE_LED_PERIOD (BASE_MAG_PERIOD)

//---------
// Variables

//---------
// Function Prototypes 
void init_pwm_pin(uint32_t pwm_pin);
void start_pwms(void);
void update_led(void);
void calculate_led_pwm(uint8_t * p_period, uint8_t * p_on_period);
uint8_t get_delta(int pot_val);
int make_linear(int pot_val);
#endif // EX_CPP_H
