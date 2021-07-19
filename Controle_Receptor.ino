//  Receptor de 4 canais
//  Saída PWM nos pinos D2, D3, D4, D5
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;

struct Signal {
  byte throttle;      
  byte pitch;
  byte roll;
  byte yaw;
};

Signal data;

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(9, 10); 

void ResetData(){
  // Defina o valor inicial de cada entrada de dados.
  // A posição do meio para Potenciômetros. (254/2 = 127)
  data.throttle = 127; // Motor Stop
  data.pitch = 127;  // Center
  data.roll = 127;   // Center
  data.yaw = 127;   // Center
}
void setup(){
  // Defina os pinos para cada sinal PWM
  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);
  // Configure o módulo NRF24
  ResetData();
  radio.begin();
  radio.openReadingPipe(1,pipeIn);
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.startListening(); // inicia a comunicação de rádio para o receptor
  Serial.begin(9600);
}

unsigned long lastRecvTime = 0;

void recvData(){
  Serial.println("Teste!");
  while (radio.available()){
    radio.read(&data, sizeof(Signal));
    lastRecvTime = millis();   // receba os dados
    Serial.println(lastRecvTime);
  }
}
void loop(){
  recvData();
  unsigned long now = millis();
  if(now - lastRecvTime > 1000){
    lastRecvTime = 0;
    ResetData(); // Sinal perdido .. Reinicializar dados
  }
  ch_width_1 = map(data.throttle, 0, 255, 1000, 2000);     // pino D2 (sinal PWM)
  Serial.print(data.throttle);
  Serial.print(" - ");
  ch_width_2 = map(data.pitch,    0, 255, 1000, 2000);     // pino D3 (sinal PWM)
  Serial.print(data.pitch);
  Serial.print(" - ");
  ch_width_3 = map(data.roll,     0, 255, 1000, 2000);     // pino D4 (sinal PWM)
  Serial.print(data.roll);
  Serial.print(" - ");
  ch_width_4 = map(data.yaw,      0, 255, 1000, 2000);     // pino D5 (sinal PWM)
  Serial.print(data.yaw);
  Serial.println("");
  // Escreva o sinal PWM
  ch1.writeMicroseconds(ch_width_1);
  ch2.writeMicroseconds(ch_width_2);
  ch3.writeMicroseconds(ch_width_3);
  ch4.writeMicroseconds(ch_width_4);
}
