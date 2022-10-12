//
// Filename: pins.hh
// Author: Beau Roland
// Details: Pinout Header file
// Date: 7/31/22
//

#ifndef PINS_H
#define PINS_H

//---------
// DEFINES, CONSTANTS, LITERALS

#ifndef LED_BUILTIN
  #define LED_BUILTIN	5
#endif
#define BRD_LED_PIN LED_BUILTIN

                            // Timer 1 should be used for event timing
#define PWM_LED_PIN     5   // Timer 0 Compare B
#define PWM_MAG_PIN     3   // Timer 2 Compare B

#define MAG_DETECT_PIN  2
#define BK_UP_PIN       11

// Potentiometer read to change different settings on the fly
#define BRIGHTNESS_POT_PIN  (A2)
#define DELTA_POT_PIN       (A1)

#endif // PINS_H
