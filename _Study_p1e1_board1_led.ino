/*
  Autonomous Vehicles and Pedestrian Interaction with Visual Signals Study - Phase 1

  Experiment 1. Empirical Assessment of light signals for peripheral perception

  This code is used for LEDs control. It runs on its own Ardiuno Uno.
  
  The circuit: 
  5x WS2815B led strips, powered independently by 12 VDC power supply;
  each data line is connected to arduino LED_PIN through a 330ohm resistor

  Lights are controlled via serial commands from another Ardiuno, listening on serial RX pin 11
  The GND pins on both boards are common
   
  The following commands are accepted:
  0 -> Turn off the leds
  1 - 8 -> Select test mode
  
  Programmer: 
    Henry Chen (Uwaterloo)
    May 2019

  
  This example code is based on 
  https://howtomechatronics.com/tutorials/arduino/arduino-and-hc-05-bluetooth-module-tutorial/
  https://www.teachmemicro.com/arduino-bluetooth/
  
  */

#include <FastLED.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial_LED(11, 12); // RX, TX

#define LED_PIN_GRP_1     3
#define LED_PIN_GRP_2     4
#define LED_PIN_GRP_3     5
#define LED_PIN_GRP_4     6
#define LED_PIN_GRP_5     7

#define NUM_LEDS_GRP_1    12
#define NUM_LEDS_GRP_2    32
#define NUM_LEDS_GRP_3    32
#define NUM_LEDS_GRP_4    32
#define NUM_LEDS_GRP_5    32

#define OFF         CRGB ( 0, 0, 0) 
#define TURQUOISE   CRGB ( 0, 255, 239) 
#define AMBER       CRGB ( 255, 191, 0) 


CRGB leds_grp_1[NUM_LEDS_GRP_1];
CRGB leds_grp_2[NUM_LEDS_GRP_2];
CRGB leds_grp_3[NUM_LEDS_GRP_3];
CRGB leds_grp_4[NUM_LEDS_GRP_4];
CRGB leds_grp_5[NUM_LEDS_GRP_5];

int serial_rx_data;  // serial control data


void setup() {
  pinMode(LED_PIN_GRP_1, OUTPUT);
  pinMode(LED_PIN_GRP_2, OUTPUT);
  pinMode(LED_PIN_GRP_3, OUTPUT);
  pinMode(LED_PIN_GRP_4, OUTPUT);
  pinMode(LED_PIN_GRP_5, OUTPUT);
    
  FastLED.addLeds<WS2813, LED_PIN_GRP_1, GRB>(leds_grp_1, NUM_LEDS_GRP_1);
  FastLED.addLeds<WS2813, LED_PIN_GRP_2, GRB>(leds_grp_2, NUM_LEDS_GRP_2);
  FastLED.addLeds<WS2813, LED_PIN_GRP_3, GRB>(leds_grp_3, NUM_LEDS_GRP_3);
  FastLED.addLeds<WS2813, LED_PIN_GRP_4, GRB>(leds_grp_4, NUM_LEDS_GRP_4);
  FastLED.addLeds<WS2813, LED_PIN_GRP_5, GRB>(leds_grp_5, NUM_LEDS_GRP_5); 

  Serial_LED.begin(9600);      // Serial communication line for control data

  Serial.begin(9600);              // Serial Monitor for debugging
  Serial.println("LEDs ready for control...");
}


/*
 * Function turns off all led strips 
 */
void lights_out() {
  for (int i = 0; i < 32; i++) {
    if (i<NUM_LEDS_GRP_1) {
      leds_grp_1[i] = OFF;
    }
    leds_grp_2[i] = OFF;
    leds_grp_3[i] = OFF;
    leds_grp_4[i] = OFF;
    leds_grp_5[i] = OFF;
  }
  FastLED.show();
}


void loop() {

  /*
  // receiving serial monitor input
  if (Serial.available () > 0){
    serial_rx_data = Serial.read();
    
    Serial.print("Serial Monitor Data Received: ");
    Serial.println(serial_rx_data);
    
    if ((serial_rx_data >= 48) && (serial_rx_data <= 56)) {
      lights_out();
      Serial.print("Activate Mode: ");
      Serial.println(serial_rx_data);

      delay(100);
    }
  }
  */ 

  
  // receiving serial control data
  if (Serial_LED.available () > 0){
    serial_rx_data = Serial_LED.read();
    Serial.print("Serial Data Received: ");
    Serial.println(serial_rx_data);
    
    if ((serial_rx_data >= 48) && (serial_rx_data <= 60)) {
      lights_out();
      Serial.print("Activate Mode: ");
      Serial.println(serial_rx_data);

      delay(500);
    }
  }
  
    
  // Test 1 - Baseline (OFF)
  if (serial_rx_data == 48) {          // ASCII '0'  
    lights_out();
    delay(500);
  }
  
  //------
  
  // Test 2a - Top Turquoise
  else if (serial_rx_data == 49) {     // ASCII '1'       
    //Serial.println("Test 2a - Top Turquoise");
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
      leds_grp_2[i] = TURQUOISE;
      leds_grp_3[i] = TURQUOISE;
    }
    FastLED.show();
    delay(500);
  }

  // Test 2b - Top Amber
  else if (serial_rx_data == 50) {      // ASCII '2'           
    //Serial.println("Test 2b - Top Amber");
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
      leds_grp_2[i] = AMBER;
      leds_grp_3[i] = AMBER;
    }
    FastLED.show();
    delay(500);
  }
  
  //------
  
  // Test 3a - Front Turquoise
  else if (serial_rx_data == 51) {      // ASCII '3'           
    //Serial.println("Test 3a - Front Turquoise");
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
      leds_grp_4[i] = TURQUOISE;
      leds_grp_5[i] = TURQUOISE;
    }
    FastLED.show();
    delay(500);
  }

  // Test 3b - Front Amber
  else if (serial_rx_data == 52) {      // ASCII '4'           
    //Serial.println("Test 3b - Front Amber");
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
      leds_grp_4[i] = AMBER;
      leds_grp_5[i] = AMBER;
    }
    FastLED.show();
    delay(500);
  }

  //------
  
  // Test 4a - Top Blinking Turquoise
  else if (serial_rx_data == 53) {      // ASCII '5'           
    //Serial.println("Test 4a - Top Blinking Turquoise");
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = TURQUOISE;
        leds_grp_3[i] = TURQUOISE;
    }
    FastLED.show(); 
    delay(250);
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = OFF;
        leds_grp_3[i] = OFF;
    }
    FastLED.show(); 
    delay(250);
  }

  // Test 4b - Top Blinking Amber
  else if (serial_rx_data == 54) {      // ASCII '6'           
    //Serial.println("Test 4b - Top Blinking Amber");
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = AMBER;
        leds_grp_3[i] = AMBER;
    }
    FastLED.show(); 
    delay(250);
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = OFF;
        leds_grp_3[i] = OFF;
    }
    FastLED.show(); 
    delay(250);
  }

  //------
   
  // Test 5a - Front Blinking Turquoise
  else if (serial_rx_data == 55) {      // ASCII '7'           
    //Serial.println("Test 5a - Front Blinking Turquoise");
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[i] = TURQUOISE;
        leds_grp_5[i] = TURQUOISE;
    }
    FastLED.show(); 
    delay(250);
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[i] = OFF;
        leds_grp_5[i] = OFF;
    }
    FastLED.show(); 
    delay(250);
  }

  // Test 5b - Front Blinking Amber
  else if (serial_rx_data == 56) {      // ASCII '8'           
    //Serial.println("Test 5b - Front Blinking Amber");
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[i] = AMBER;
        leds_grp_5[i] = AMBER;
    }
    FastLED.show(); 
    delay(250);
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[i] = OFF;
        leds_grp_5[i] = OFF;
    }
    FastLED.show(); 
    delay(250);
  }

  //------

  // Test 6a - Top Chase Turquoise
  else if (serial_rx_data == 57) {      // ASCII '9'           
    //Serial.println("Test 6a - Top Chase Turquoise");
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = TURQUOISE;
        leds_grp_3[i] = TURQUOISE;
        FastLED.show(); 
        delay(250/NUM_LEDS_GRP_2);    
    }
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = OFF;
        leds_grp_3[i] = OFF;
    }
    FastLED.show(); 
  }

  // Test 6b - Top Chase Amber
  else if (serial_rx_data == 58) {      // ASCII ':'           
    //Serial.println("Test 6b - Top Chase Amber");
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = AMBER;
        leds_grp_3[i] = AMBER;
        FastLED.show(); 
        delay(250/NUM_LEDS_GRP_2);    
    }
    for (int i = 0; i < NUM_LEDS_GRP_2; i++) {
        leds_grp_2[i] = OFF;
        leds_grp_3[i] = OFF;
    }
    FastLED.show(); 
  }

  //------

  // Test 7a - Front Chase Turquoise
  else if (serial_rx_data == 59) {      // ASCII ';'           
    //Serial.println("Test 7a - Front Chase Turquoise");
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[NUM_LEDS_GRP_4-1-i] = TURQUOISE;
        leds_grp_5[NUM_LEDS_GRP_5-1-i] = TURQUOISE;
        FastLED.show(); 
        delay(250/NUM_LEDS_GRP_4);    
    }
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[i] = OFF;
        leds_grp_5[i] = OFF;
    }
    FastLED.show(); 
  }

  // Test 7b - Front Chase Amber
  else if (serial_rx_data == 60) {      // ASCII '<'           
    //Serial.println("Test 7b - Front Chase Amber");
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[NUM_LEDS_GRP_4-1-i] = AMBER;
        leds_grp_5[NUM_LEDS_GRP_5-1-i] = AMBER;
        FastLED.show(); 
        delay(250/NUM_LEDS_GRP_4);    
    }
    for (int i = 0; i < NUM_LEDS_GRP_4; i++) {
        leds_grp_4[i] = OFF;
        leds_grp_5[i] = OFF;
    }
    FastLED.show(); 
  }

}
