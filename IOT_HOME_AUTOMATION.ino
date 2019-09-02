
               /*
Project : Home Automation 

Faculty Name : Souvik Sarkar

Group Members : 
1.Ritwick Das
2.Gourav Ranjan Dutta
3.Aishik Sett
4.Baisakhi Mukherjee
5.Sourav Das Adhikary
6.Suprakash Maity

Code Written By:
*Ritwick Das 
*Gourav Ranjan Dutta

Component Used : 
1. Node MCU
2. Servo Motor
3. Ultrasonic Sensor
4. Relay
5. Flame Sensor
6. PIR Sensor
7. LDR
8. Resistance of 330ohm and 100k ohm
9. LED
10. Smoke Sensor
11. Wires and Jumpers
12. Bread Board 

*/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#include <Servo.h>
Servo servo;
#include <LiquidCrystal.h>                              
int a;
int state = LOW, val;
long duration;
long cm;
const int trigpin = D7; //Ultrasonic
const int echopin = D8;
const int flmpin = D0;
const int smkepin = D1;
const int pirpin = D5;
const int ledpin = D6;

WidgetLCD lcd(V0);
char auth[] = "d74a8093e57f45e28170b126156cc518";

char ssid[] = "Burbaklaal";
char pass[] = "8420825204";

void setup() {
   pinMode(flmpin,INPUT);    //Flame sensor
  pinMode(smkepin,INPUT);     //Smoke sensor
  pinMode(trigpin,OUTPUT);     // Ultra
  pinMode(echopin,INPUT);     // Ultra
  pinMode(pirpin,INPUT);  //PIR
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  servo.attach(D4);
  

}


void loop() {
  ultrasonic();
  delay(500);
   Blynk.run();
  if(digitalRead(flmpin)==LOW)
  {
Blynk.notify("ALERT! : There's FIRE in your House");
  }
  
  if(digitalRead(smkepin)==LOW)
  {
Blynk.notify("ALERT! : There's Gas leaking in your House");
  }

//PIR
  val = digitalRead(pirpin);   
  if (val == HIGH) 
  {           
    if (state == LOW) 
    {
      Serial.println("Motion detected!"); 
      Blynk.notify("ALERT! : There's some sort of activity in your house");
      state = HIGH; 
    }
  } 
  else 
  {
      if (state == HIGH)
      {
        Serial.println("No Motion Detected !!");
        state = LOW;
      }
  }
  delay(1000);

  //LDR 
a=analogRead(A0);
Serial.print(a);
if(a<=300)
{
  digitalWrite(ledpin,HIGH);
}
else
{
  digitalWrite(ledpin,LOW);
}

//LCD
 if(digitalRead(flmpin)==HIGH && digitalRead(smkepin)==HIGH && digitalRead(pirpin)==LOW)
  {
lcd.clear();  //  Clear the LCD Widget screen
lcd.print(4, 0, "All Ok");  

  }
  else
  {
    lcd.clear();
    lcd.print(0, 1, "ALERT!!");
  }



}
  
// SERVOS
BLYNK_WRITE(V4)
{
  servo.write(0);
  
}
BLYNK_WRITE(V5)
{
  servo.write(90);
  
}


// MAIN SWITCH
BLYNK_WRITE(V2)
{
  digitalWrite(D4,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D6,LOW);
}

void ultrasonic()
{
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  cm = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(cm);
  if(cm<20)
  { 
// BLYNK_WRITE(V4);
    servo.write(0);
      delay(1000);
  }
  else
  {
 //BLYNK_WRITE(V5);
    servo.write(90);
      delay(1000);
  } 
}
 
