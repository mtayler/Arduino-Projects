/*
  Thermometer
 
 Monitors temperature, and prints to LCD. Lights LCDs based on human comfort
 in the current temperature
 
  The circuit:
 * TMP 36GZ to A0
 *
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K pot:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 * pin 8 to red LED
 * pin 9 to green LED
 * pin 10 to blue LED
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

#define DELAY (2000)

#define RED (8)
#define GREEN (9)
#define BLUE (10)

void lights(int temp);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int prev;
long sum;
int iterations;

void setup() {
  pinMode(A0, INPUT);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temperature:");
  
  prev = millis() + DELAY;
  sum = 0;
  
  Serial.begin(9600);
}

void loop() {
  int temp;
  float tmpOutput;
  
  tmpOutput = analogRead(A0);
  temp = ((tmpOutput * 5000/1024) - 500) / 10;
  
  if (millis() - prev > DELAY) {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(temp);
    lcd.setCursor(2, 1);
    lcd.print(" degrees C");
    
    lights(temp);
    
    iterations = 0;
    sum = 0;
    prev = millis();
    
    delay(100);
  }
  else {
    sum += temp;
    ++iterations;
    delay(50);
  }
}

void lights(int T) {
  int red = 85*(T-24);
  int green = 85*(-abs(T-21)+3);
  int blue = 85*(T-18);
  
  Serial.print("R: ");
  Serial.print(red);
  Serial.print("; G: ");
  Serial.print(green);
  Serial.print("; B: ");
  Serial.println(blue);
  
  digitalWrite(RED, red);
  digitalWrite(GREEN, green);
  digitalWrite(BLUE, blue);
}
