#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial wifi_module(2,3); // Connect TX pin of esp to the pin 2 of Arduino and RX pin of esp to the pin 3 of Arduino




int red_led_pin = 9;

int green_led_pin = 8;

int buzzer_pin = 10;

int smoke_sensor_pin = A0;




void setup()

{

  Serial.begin(9600);

  wifi_module.begin(9600); // Set the baudrate according to your esp8266

  pinMode(red_led_pin, OUTPUT);

  pinMode(green_led_pin, OUTPUT);

  pinMode(buzzer_pin, OUTPUT);

  pinMode(smoke_sensor_pin, INPUT);

  esp8266_command("AT+RST\r\n",2000,DEBUG); // reset module

  esp8266_command("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point

  esp8266_command("AT+CIFSR\r\n",1000,DEBUG); // get ip address

  esp8266_command("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections

  esp8266_command("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80

}

void loop()

{

  int analogSensor = analogRead(smoke_sensor_pin);

  if (analogSensor > 400)

  {

    digitalWrite(red_led_pin, HIGH);

    digitalWrite(green_led_pin, LOW);

    tone(buzzer_pin, 1000, 200);

  }

  else

  {

    digitalWrite(red_led_pin, LOW);

    digitalWrite(green_led_pin, HIGH);

    noTone(buzzer_pin);

  }




  if(wifi_module.available()) 

  {

    if(wifi_module.find("+IPD,"))

    {

     delay(1000);

     int connectionId = wifi_module.read()-48;     

     String webpage = "<h1>IOT Smoke Detection System</h1>";

      webpage +="<p>Smoke Value is ";

      webpage += analogSensor;

      webpage +="</p>";

      if (analogSensor > 400)

  {

    webpage +="<h5>DANGER! Move Somewhere Else</h5>";

  }

  else

  {

    webpage +="<h4>Everything Normal</h4>";

  }

     String cipSend = "AT+CIPSEND=";

     cipSend += connectionId;

     cipSend += ",";

     cipSend +=webpage.length();

     cipSend +="\r\n";

     

     esp8266_command(cipSend,1000,DEBUG);

     esp8266_command(webpage,1000,DEBUG);

     

     String closeCommand = "AT+CIPCLOSE="; 

     closeCommand+=connectionId; // append connection id

     closeCommand+="\r\n";

     

     esp8266_command(closeCommand,3000,DEBUG);

    }

  }

}

String esp8266_command(String command, const int timeout, boolean debug)

{

    String response = "";

    wifi_module.print(command); 

    long int time = millis();

    while( (time+timeout) > millis())

    {

      while(wifi_module.available())

      {

        

        char c = wifi_module.read(); 

        response+=c;

      }  

    }

    

    if(debug)

    {

      Serial.print(response);

    }

    return response;

}
