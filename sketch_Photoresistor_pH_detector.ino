#include "TM1637Display.h"

// Define connections pins
#define CLK 2
#define DIO 3

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);

int sensorValue = 0;

void setup(){
  display.setBrightness(5);   // set brightness (0-7)
  display.clear();
  
  pinMode(A0, INPUT);
  Serial.begin(9600);

}

void loop(){
  // read the value from the sensor
  sensorValue = analogRead(A0);

  // print sensor reading to serial monitor
  Serial.println(sensorValue);
  
  // For pH levels 1-2
  if ((650 <= sensorValue) && (sensorValue <= 690)){
    // "1-2"
    uint8_t data[] = {
      SEG_B | SEG_C,                              // 1
      SEG_G,                                      // -
      SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,      // 2
      0x00                                        // blank
    };

    // Display characters on display
    display.setSegments(data);

    // Light up corresponding light 
    digitalWrite(8, LOW);  // Blue OFF
    digitalWrite(9, LOW);   // White OFF
    digitalWrite(13, HIGH); // Red ON


  // For pH levels 3-4
  }if ((sensorValue >= 736)&& (sensorValue <= 799)) {
    // "3-4"
    uint8_t data[] = {
      SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,           // 3
      SEG_G,                                           // -
      SEG_B | SEG_C | SEG_F | SEG_G,                   // 4
      0x00                                             // blank
    };

    // Display characters on display
    display.setSegments(data);

    // Light up corresponding light 
    digitalWrite(8, LOW);  // Blue OFF
    digitalWrite(9, LOW);   // White OFF
    digitalWrite(13, HIGH); // Red ON


  // For pH levels 5-6
  }if ((sensorValue >= 691)&& (sensorValue <= 735)){
    // "5-6"
    uint8_t data[] = {
      SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // 5
      SEG_G,                                           // -
      SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,   // 6
      0x00                                             // blank
    };
  
    // Display characters on display
    display.setSegments(data);

    // Light up corresponding light 
    digitalWrite(8, LOW);  // Blue OFF
    digitalWrite(9, LOW);   // White ON
    digitalWrite(13, HIGH); // Red OFF


  // For pH level 7
  }if ((sensorValue >= 530)&& (sensorValue <= 560)){
    // "7"
    display.showNumberDec(7);
    
    digitalWrite(8, LOW);  // Blue OFF
    digitalWrite(9, HIGH);   // White ON
    digitalWrite(13, LOW); // Red OFF


  // For pH levels 8-9
  }if ((sensorValue >= 561)&& (sensorValue <= 600)){
    // "8-9"
    uint8_t data[] = {
      SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,  // 8
      SEG_G,                                                  // -
      SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,          // 9
      0x00                                                    // blank
    };

    // Display characters on display
    display.setSegments(data);

    // Light up corresponding light 
    digitalWrite(8, HIGH);  // Blue OFF
    digitalWrite(9, LOW);   // White ON
    digitalWrite(13, LOW); // Red OFF


  // For pH levels 10+
  }if (sensorValue >= 820){
    // "10+"
    uint8_t data[] = {
      SEG_B | SEG_C,                                  // 1
      SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // 0
      SEG_G | SEG_D | SEG_A | SEG_F | SEG_E,          // + (approximation)
      0x00                                            // blank
    };

    // Display characters on display
    display.setSegments(data);

    // Light up corresponding light 
    digitalWrite(8, HIGH);  // Blue OFF
    digitalWrite(9, LOW);   // White ON
    digitalWrite(13, LOW); // Red OFF


  // If nothing is being tested 
  }if ((sensorValue >= 800)&& (sensorValue <= 819)){
    //
    uint8_t data[] = {
      SEG_G,   // -
      SEG_G,   // -
      SEG_G,   // -
      SEG_G    // -
    };

    // Display characters on display
    display.setSegments(data);

    // Light up corresponding light 
    digitalWrite(8, LOW);  // Blue OFF
    digitalWrite(9, LOW);   // White OFF
    digitalWrite(13, LOW); // Red OFF
    
  }


  delay(1000); // Wait for 100 ms
}
