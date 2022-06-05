int vibrationPin=7;
int Buzzer=13;
void setup() {
  pinMode(vibrationPin,INPUT);
  pinMode(Buzzer,OUTPUT);
}

void loop() {
  int val;
  val=digitalRead(vibrationPin);
  if(val==1)
  {
    digitalWrite(Buzzer,HIGH);
    delay(1000);
    digitalWrite(Buzzer,LOW);
    delay(1000);
   }
   else
   digitalWrite(Buzzer,LOW);
}
