//
// Filename: pins.hh
// Author: Beau Roland
// Details: Pinout Header file
// Date: 10/12/22
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

// PWM
#define ADA_TRINK_OC0A ADA_TRINK_PB0
#define ADA_TRINK_nOC1A ADA_TRINK_PB0
#define ADA_TRINK_OC1A ADA_TRINK_PB1
#define ADA_TRINK_OC0B ADA_TRINK_PB1
#define ADA_TRINK_nOC1B ADA_TRINK_PB3
#define ADA_TRINK_OC1B ADA_TRINK_PB4


// ADC
#define ADA_TRINK_A1 ADA_TRINK_PB2
#define ADA_TRINK_A2 ADA_TRINK_PB4
#define ADA_TRINK_A3 ADA_TRINK_PB3

// LED
#define ADA_TRINK_LED ADA_TRINK_PB1

//---------
// Application DEFINES, CONSTANTS, LITERALS

#ifndef LED_BUILTIN
  #define LED_BUILTIN	ADA_TRINK_LED
#endif
#define BRD_LED_PIN LED_BUILTIN

#define PWM_MAG_PIN     ADA_TRINK_OC0B   // Timer 0 Compare B
#define PWM_LED_PIN     ADA_TRINK_OC1B   // Timer 1 Compare B

// Potentiometer read to change different settings on the fly
#define BRIGHTNESS_POT_PIN  (ADA_TRINK_A1)
#define DELTA_POT_PIN       (ADA_TRINK_A3)

#endif // PINS_H
