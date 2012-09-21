/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin A0
 * LCD Enable pin to digital pin A1
 * LCD D4 pin to digital pin A2
 * LCD D5 pin to digital pin A3
 * LCD D6 pin to digital pin A4
 * LCD D7 pin to digital pin A5
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 20000009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 
 
 https://www.sparkfun.com/products/10862
 
 RGB are
 Arduino LCD
 6       16 
 5       17
 3       18
 
 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int ledR = 6;
int ledG = 5;
int ledB = 3;
int brightnessR = 1;
int brightnessG = 0;
int brightnessB = 0;
int fadeAmount = 5;

int fadeMode = 5;


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  lcd.clear();
  lcd.setCursor(0,0);
  // Print a message to the LCD.
  lcd.print("hello, world!");  
}

int setColor(int R, int G, int B)
{
  analogWrite(ledR, R);
  analogWrite(ledG, G);
  analogWrite(ledB, B);
}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
  
  lcd.setCursor(8, 1);
  lcd.print(fadeMode);

  analogWrite(ledR, brightnessR);
  analogWrite(ledG, brightnessG);
  analogWrite(ledB, brightnessB);
  
  if (fadeMode == 1)
  {
    if (brightnessR)
    {
      brightnessR += fadeAmount;
      if (brightnessR > 255)
      {
         brightnessR = 0;
         brightnessG = 1;
      }
    }
    if (brightnessG)
    {
      brightnessG += fadeAmount;
      if (brightnessG > 255)
      {
         brightnessG = 0;
         brightnessB = 1;
      }
    }
    if (brightnessB)
    {
      brightnessB += fadeAmount;
      if (brightnessB > 255)
      {
         brightnessB = 0;
         brightnessR = 1;
         fadeMode = 2;
         brightnessR = brightnessG = brightnessB = 0;
      }
    }
  }
  
  if (fadeMode == 2)
  {
    brightnessR = brightnessB = brightnessR = brightnessR+fadeAmount;
    if (brightnessR >= 255)
       fadeAmount = -fadeAmount;
    if (brightnessR <= 0)
     {
       fadeAmount = -fadeAmount;
       brightnessR = 0;
       brightnessG = brightnessB = 0;
       fadeMode = 3;
     }
  }
  
  if (fadeMode == 3)
  {
    if (brightnessR < 255)
      brightnessR += fadeAmount;
    else if (brightnessG < 255)
      brightnessG += fadeAmount;
    else if (brightnessB < 255)
      brightnessB += fadeAmount;
    else
    {
      brightnessR = 1;
      brightnessG = brightnessB = 0;
      fadeMode = 4;
    } 
  }
  
  if (fadeMode == 4)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    analogWrite(ledR, 0);
    analogWrite(ledG, 255);
    analogWrite(ledB, 0);
    lcd.print("ALL GOOD!");
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    analogWrite(ledR, 0);
    analogWrite(ledG, 0);
    analogWrite(ledB, 255);
    lcd.print("STANDBY ...");
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    analogWrite(ledR, 255);
    analogWrite(ledG, 0);
    analogWrite(ledB, 0);
    lcd.print("ALARM !!!");
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    analogWrite(ledR, 255);
    analogWrite(ledG, 255);
    analogWrite(ledB, 0);
    lcd.print("WARNING!");
    delay(2000);
    
    fadeMode = 5;
  }
  
  if (fadeMode == 5)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    // Print a message to the LCD.
    lcd.print("DorkBot !");

    setColor(0x00, 0x00, 0xff);
    delay(800);

    setColor(0x00, 0xff, 0x00);
    delay(200);

    setColor(0xff, 0xff, 0x00);
    delay(200);

    setColor(0xff, 0x00, 0x00);
    delay(200);

    setColor(0x44, 0x22, 0x00);
    delay(200);

    fadeMode = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    // Print a message to the LCD.
    lcd.print("hello, dorkbot!");

  }

  delay(30);
}

