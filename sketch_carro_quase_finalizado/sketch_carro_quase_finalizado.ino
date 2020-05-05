#include <RF24.h>

//*************** Definição dos Pinos ***********************
#define pinCE  7
#define pinCSN 8
#define pinIN1 10
#define pinIN2 9
#define pinIN3 6
#define pinIN4 5

/* Controle do servo (Direção)  */
#include <Servo.h>
Servo Servo1;

struct tipoDadosRF {
   int pot1 = 512;
   int pot2 = 512;
   boolean botao = false;
   int angle;
};
tipoDadosRF dadosRF;

RF24 radio(pinCE,pinCSN);

const uint64_t pipeOut = 0xA5E8F0F0E1LL;


//*************** Controle do Carro ************
int pDireita  = 100;
int pEsquerda = 100;


void setup() {
  //*************** Controle do RF ***********************
  radio.begin();
  radio.setPALevel( RF24_PA_LOW );     //RF24_PA_MIN  / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS );   //RF24_250KBPS / RF24_1MBPS  / RF24_2MBPS
  radio.openReadingPipe(1, pipeOut);
  radio.startListening();  

  Serial.begin(9600);
  Servo1.attach(4); //controle do servo

  //*************** Controle do Carro ************
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
}


void loop() {
  //*************** Controle do RF ***********************
  if (radio.available()) {                                   
     radio.read( &dadosRF, sizeof(tipoDadosRF) ); 
  }   

  //*************** Controle do Carro ************
  if (dadosRF.botao) {
     //Aciona o freio
     digitalWrite(pinIN1, HIGH);
     digitalWrite(pinIN2, HIGH);
     digitalWrite(pinIN3, HIGH);
     digitalWrite(pinIN4, HIGH);
  } else {

    //controle do servo para controlar a direção do carro
    //dadosRF.pot2=analogWrite(dadosRF.pinPot2);
    //dadosRF.angle=map(dadosRF.pot2,0,1023,40,160);
    Serial.print (" angle= ");
    Serial.println (dadosRF.angle);
    Servo1.write(dadosRF.angle);
    delay (50);
    
/** código do carinha do canal
     //Controle da direção 
     if (dadosRF.pot2 < 512) {
        //Esquerda 
        pDireita  = 100;
        pEsquerda = map(dadosRF.pot2, 511, 0, 100, 0); 
     } else {
        //Direita
        pDireita  = map(dadosRF.pot2, 512, 1023, 100, 0);
        pEsquerda = 100;       
     }  **/


     if (dadosRF.pot1 < 512) {
        //Reverso
        int velocidade = map(dadosRF.pot1, 511, 0, 0, 255);

        analogWrite(pinIN1, 0);
        analogWrite(pinIN2, velocidade * pDireita / 100);
     
        analogWrite(pinIN3, 0);
        analogWrite(pinIN4, velocidade * pEsquerda / 100); 
     } else {
        //Para frente
        int velocidade = map(dadosRF.pot1, 512, 1023, 0, 255);

        analogWrite(pinIN1, velocidade * pDireita / 100);
        analogWrite(pinIN2, 0);
     
        analogWrite(pinIN3, velocidade * pEsquerda / 100);
        analogWrite(pinIN4, 0);                         
     }
  }  
}
