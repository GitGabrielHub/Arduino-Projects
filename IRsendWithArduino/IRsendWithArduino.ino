//Utilização do sensor ultrassônico do Arduino para ligar/desligar TV

#include <IRremote.h> //Biblioteca usada para que o led infravermelho (de um controle remoto IR qualquer) possa emitir pulsos 
                      //correspondete a algum código binário específico que por conseguinte o receptor 
                      //da TV vai decodificar e processar a tarefa exigida.

IRsend irsend; //Por padrão da biblioteca, o led infravermelho deve estar no pino 3, ou seja, não precisa especificar
               //o pinMode() no setup, a biblioteca faz por si só.

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

  dist = time/58; //Distância em centímetros.

  if(dist < 20 && condictionOff){   //
    irsend.sendNEC(0xE0E040BF,32);  //Chamada de função passada como primeiro parâmetro o 0x juntamente com o código hexadecimal que corresponde ao valor da tarefa
                                    //ligar/desligar TV SAMSUNG, e como segundo parâmetro valor em bits correspondente a resolução.
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
