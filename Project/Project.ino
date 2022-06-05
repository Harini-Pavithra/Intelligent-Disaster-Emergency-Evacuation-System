
int sensorPin = A0;
int sensorValue = 0;
int Buzzer1 = 2;

int Buzzer2 = 3;
int smokeA0 = A1;
// Your threshold value
int sensorThres = 400;

#include <LiquidCrystal.h>
//I'm including the code here for the parallel LCD. Contact me if you want the I2C code. It requires special libraries, but only uses two data pins instead of 6.
//sensitivity variables
int minimum = 200;
int maximum= 1023;
int maxdelay = 400;
// include the library code:
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Custom Character
byte seismic[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111, };
//defines the pin connections
int sensePin= A2;
int Buzzer3= 4;

void setup() {
pinMode(Buzzer1,OUTPUT);
pinMode(Buzzer2, OUTPUT);
pinMode(smokeA0, INPUT);
Serial.begin(9600);

lcd.begin (16,2); // or (20,4)
lcd.createChar(0, seismic);

}
void loop()
{ 
  
int reading= analogRead(sensePin);
Serial.println(reading);
reading = constrain(reading, minimum, maximum);
Serial.println(reading);
reading = map(reading, minimum, maximum, 0, 15);
Serial.println(reading); lcd.clear();
for (int i=0; i <= reading; i++){
lcd.write(byte(0));
}

int analogSensor = analogRead(smokeA0);
Serial.print("Pin A0: ");
Serial.println(analogSensor);
Serial.println("NO Fire Detected");

sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);

if (sensorValue < 100)
{
Serial.println("Fire Detected");
digitalWrite(Buzzer1,HIGH);
delay(1000);

if (analogSensor > sensorThres)
  {
    tone(Buzzer1, 1000, 200);
  }
  
  if (4<=reading && 8>reading){
lcd.setCursor(0, 1);
lcd.print(" ");
lcd.print("Seismic Activity");
delay(500);
}
if (8<=reading){
lcd.setCursor(0, 1);
lcd.print(" ");
lcd.print("Earthquake");
digitalWrite(Buzzer3,HIGH);
delay(500);
}
delay(maxdelay);
lcd.clear();

}
digitalWrite(Buzzer1,LOW);
noTone(Buzzer2);
digitalWrite(Buzzer3,LOW);
delay(sensorValue);
}
