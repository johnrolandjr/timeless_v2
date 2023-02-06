//
// Filename: timeless_v2_testing.cpp
// Author: Beau Roland
// Details: Timeless v2 Testing
//   Contains all the integration tests prior to using main code.
// Date: 2/5/23
//
// #include "TrinketFakeUsbSerial.h"

#include "driver.hh"
#include "pins.hh"

// //---------------------------------------------------------------------------------------------------------------
// // Arduino Testing : Analog ports
// // Analog Read
// void setup() {
//   TFUSerial.begin();
// }

// // Arduino Main Loop
// void loop() {
//   TFUSerial.task(); // this should be called at least once every 10 ms

//   if (TFUSerial.available()) {
//     int sensorValue = analogRead(ADA_TRINK_A1);
//     // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//     //float voltage = sensorValue * (5.0 / 1023.0);
//     // print out the value you read:
//     TFUSerial.println(sensorValue);
//   }
// }

// // ---------------------------------------------------------------------------------------------------------------
// // Arduino Testing : Analog ports
// // Make nonlinear pot having a psuedo linear readout
// #define POT_PIN ADA_TRINK_A1
// void setup() {
//   TFUSerial.begin();
// }

// // Arduino Main Loop
// void loop() {
//   TFUSerial.task(); // this should be called at least once every 10 ms

//   if (TFUSerial.available()) {
//     int rawValue = analogRead(POT_PIN);
//     int linValue = make_linear(rawValue);

//     float calcPercent = (linValue * 100) / 255;
//     TFUSerial.print("R:");
//     TFUSerial.print(rawValue);
//     TFUSerial.print("  L:");
//     TFUSerial.println(calcPercent);
//   }
// }

// // ----------------------------------------------------------------------------------
// // Arduinot Testing : GPO ports
// // Direct Control Test
// #define GPO_PIN ADA_TRINK_PB2
// void setup() {
//   pinMode(GPO_PIN, OUTPUT);
// }

// void loop() {
//   digitalWrite(GPO_PIN, HIGH);
//   delay(1000);
//   digitalWrite(GPO_PIN, LOW);
//   delay(1000);
// }

// // ----------------------------------------------------------------------------------
// // Arduinot Testing : GPO ports
// // PWM Control Test
// int brightness = 0;
// int fadeAmount = 5;

// #define GPO_PIN ADA_TRINK_OC1A
// void setup() {
//   pinMode(GPO_PIN, OUTPUT);
// }

// void loop() {
//   analogWrite(GPO_PIN, brightness);

//   brightness = brightness + fadeAmount;

//   // reverse the direction of the fading at the ends of the fade
//   if (brightness <= 0 || brightness >= 255) {
//     fadeAmount = -fadeAmount;
//   }
//   delay(30);
// }

// // ----------------------------------------------------------------------------------
// // Arduinot Testing : GPO ports
// // PWM Finer Control Test
// void setup() {
//   // Init Led PWM pin as digital output and PWM that is turned off
//   init_pwm_pin(PWM_LED_PIN);

//   // Init Mag PWM pin as digital output and PWM that is turned off
//   init_pwm_pin(PWM_MAG_PIN);
// }

// void loop() {
//   //Update led pwm and duty
//   uint8_t led_period = BASE_LED_PERIOD;
//   uint8_t led_on_period = led_period>>1;
  
//   // Update Led Period and Duty
//   OCR1C = led_period;
//   OCR1B = led_on_period;

//   // Start PWMs by setting the clock
//   // Set Clock Prescaler for Timer0 (CLKio / 1024 =5)
//   TCCR0B |= 0x05;
//   // Set Clock Prescaler for Timer1 (CLKio / 1024 =0xB)
//   // Set Clock Prescaler for Timer1 (CLKio / 1024 =0xB)
//   TCCR1 = _BV(CS13) | _BV(CS11) | _BV(CS10);
//   GTCCR = _BV(COM1B1) | _BV(PWM1B);  //  Noninverting + Enable PWM on OCR1B
// }