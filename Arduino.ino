#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const int pingPin = A0;
const int echoPin = A1;
long duration, inches, cm;
#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 
 // NewPing setup of pins and maximum distance.

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(11,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("DAM IS FULL");
  lcd.setCursor(2,1);
  lcd.print("  NORMAL");
  delay(50);  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  if(cm>40)
  {
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(10,HIGH);
  }
  if(cm>30&&cm<40)
  {
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(8,HIGH);
  }
  if(cm<20&cm>0)
  {
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    Serial.println("DAM IS FULL");
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("DAM IS FULL");
    lcd.setCursor(2,1);
    lcd.print("  ALERT!!!");
    digitalWrite(11,HIGH);
    digitalWrite(A2,HIGH);
    delay(1000);    
    digitalWrite(A2,LOW);
    digitalWrite(11,LOW);
  }
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}