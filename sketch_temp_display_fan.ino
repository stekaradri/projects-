#include <dht.h>
#include <LiquidCrystal.h>

// L293D for fan 
#define ENA 9
#define DIRF 8
#define DIRB 6

// Temp & humitity sensor 
#define DHT22_PIN 7
dht DHT;

// Display panel 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(ENA, OUTPUT); // Speed control pin
  pinMode(DIRF, OUTPUT); // Direction control pin (forwards if high)
  pinMode(DIRB, OUTPUT); // Direction control pin (Backwards if high)

  // Set motor to off initially 
  analogWrite(ENA, 0);
  digitalWrite(DIRF, LOW);
  digitalWrite(DIRB, LOW);
}


void loop() {
  int chk = DHT.read22(DHT22_PIN);
  float temp = DHT.temperature; // Variable for temperature
  float humid = DHT.humidity; // Variable for humidity

  // Display on LCD
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); 
  lcd.print("C   "); 
   
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humid);
  lcd.print("%   ");

  // Fan control logic
  if (temp >= 21.0 && temp <= 21.9) {
    Serial.println("Fan LOW");
    digitalWrite(DIRF, HIGH);   
    digitalWrite(DIRB, LOW);
    analogWrite(ENA, 150);   // Low speed
  } else if (temp >= 22.0 && temp <= 22.9) {
    Serial.println("Fan MEDIUM");
    digitalWrite(DIRF, HIGH);   
    digitalWrite(DIRB, LOW);
    analogWrite(ENA, 200);   // Medium speed
   
  } else if (temp >= 23) {
    Serial.println("Fan HIGH");
    digitalWrite(DIRF, HIGH);  
    digitalWrite(DIRB, LOW);
    analogWrite(ENA, 250);   // High speed
    
  } else {
    Serial.println("Fan OFF");
    analogWrite(ENA, 0);     // Fan off
    digitalWrite(DIRF, LOW);
    digitalWrite(DIRB, LOW);
  }

  delay(1000); // Wait 1 second
}
