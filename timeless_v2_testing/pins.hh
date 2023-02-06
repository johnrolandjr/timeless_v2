//
// Filename: pins.hh
// Author: Beau Roland
// Details: Pinout Header file for Adafruit Trinket v5
// Date: 2/5/23
//

#ifndef PINS_H
#define PINS_H

//---------
// Board pins for Adafruit Trinket V5
// GPIO Port B
#define ADA_TRINK_PB0 0
#define ADA_TRINK_PB1 1
#define ADA_TRINK_PB2 2
#define ADA_TRINK_PB3 3
#define ADA_TRINK_PB4 4 
#define ADA_TRINK_PB5 5 // Reset

// PWM (Pins capable of automatic pwm)
#define ADA_TRINK_OC0A ADA_TRINK_PB0
#define ADA_TRINK_nOC1A ADA_TRINK_PB0
#define ADA_TRINK_OC1A ADA_TRINK_PB1
#define ADA_TRINK_OC0B ADA_TRINK_PB1
#define ADA_TRINK_nOC1B ADA_TRINK_PB3
#define ADA_TRINK_OC1B ADA_TRINK_PB4

// ADC
#define ADA_TRINK_A0 0 // RESET pin 1
#define ADA_TRINK_A1 1 // PB2 pin 7
#define ADA_TRINK_A2 2 // PB4 pin 3
#define ADA_TRINK_A3 3 // PB3 pin 2

// LED
#define ADA_TRINK_LED ADA_TRINK_PB1

//---------
// Application DEFINES, CONSTANTS, LITERALS

#ifndef LED_BUILTIN
  #define LED_BUILTIN	ADA_TRINK_LED
#endif
#define BRD_LED_PIN LED_BUILTIN

#define PWM_MAG_PIN     ADA_TRINK_OC0B   // Output Compare B Timer 0
#define PWM_LED_PIN     ADA_TRINK_OC1B   // Output Compare B Timer 1

// Potentiometer read to change different settings on the fly
#define BRIGHTNESS_POT_PIN  (ADA_TRINK_A1)
#define DELTA_POT_PIN       (ADA_TRINK_A3)

#endif // PINS_H
