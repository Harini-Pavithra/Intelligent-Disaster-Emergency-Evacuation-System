
int sensorPin = A0; // select the input pin for the LDR

int sensorValue = 0; // variable to store the value coming from the sensor

int led = 9; // Output pin for LED

int buzzer = 12; // Output pin for Buzzer

void setup() {

// declare the ledPin and buzzer as an OUTPUT:

pinMode(led, OUTPUT);

pinMode(buzzer,OUTPUT);

Serial.begin(9600);

}

void loop()

{

Serial.println("NO Fire Detected");

sensorValue = analogRead(sensorPin);

Serial.println(sensorValue);

if (sensorValue < 100)

{

Serial.println("Fire Detected");

Serial.println("LED on");

digitalWrite(led,HIGH);

digitalWrite(buzzer,HIGH);

delay(1000);

}

digitalWrite(led,LOW);

digitalWrite(buzzer,LOW);

delay(sensorValue);

}
