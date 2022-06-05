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

int sensePin= 0;

void setup() {

Serial.begin(9600);

lcd.begin (16,2); // or (20,4)

lcd.createChar(0, seismic);


}

void loop() {

int reading= analogRead(sensePin);

Serial.println(reading);

reading = constrain(reading, minimum, maximum);

Serial.println(reading);

reading = map(reading, minimum, maximum, 0, 15);

Serial.println(reading); lcd.clear();

for (int i=0; i <= reading; i++){

lcd.write(byte(0));

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

delay(500);

}

delay(maxdelay);

lcd.clear();

}


