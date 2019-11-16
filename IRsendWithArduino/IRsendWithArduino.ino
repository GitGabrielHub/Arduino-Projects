#include <IRremote.h>

IRsend irsend;

byte PIN_ECHO = 6;
byte PIN_TRIG = 5;

unsigned long time;
double dist;

boolean condictionOn  = false;
boolean condictionOff = true;

void setup(){
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
  
  Serial.begin(9600);

  digitalWrite(PIN_TRIG,LOW);
}

void loop() {

  digitalWrite(PIN_TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG,LOW);

  time = pulseIn(PIN_ECHO,HIGH);

  dist = time/58;

  if(dist < 20 && condictionOff){
    irsend.sendNEC(0xE0E040BF,32);
    condictionOn = true;
    condictionOff = false;
    delay(5000);
  }

  else if(dist > 100 && condictionOn){
    irsend.sendNEC(0xE0E040BF, 32);
    condictionOn = false;
    condictionOff = true;
    delay(7000);
  }

  delay(500);
}
