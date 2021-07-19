// Transmissor de 4 canais
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE9E8F0F0E1LL;   // IMPORTANTE: O mesmo que no receptor 0xE9E8F0F0E1LL
RF24 radio(9, 10); // selecione o pino CE, CSN

struct Signal{
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
};

Signal data;

void ResetData(){
  data.throttle = 127; // Parada do motor (254/2 = 127) (posição perdida de sinal)
  data.pitch = 127; // Center | Merkez (posição perdida de sinal)
  data.roll = 127; // Center | merkez (posição perdida de sinal)
  data.yaw = 127; // Center | merkez (posição perdida de sinal)
}

void setup(){
  // Comece tudo
  radio.begin();
  radio.openWritingPipe(pipeOut);
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.stopListening(); //inicia a comunicação de rádio para o Transmissor
  ResetData();
  Serial.begin(9600);
}

// Centro do joystick e suas bordas
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse){
  val = constrain(val, lower, upper);
  if ( val < middle )
  val = map(val, lower, middle, 0, 128);
  else
  val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}

void loop(){
  // Calibração da alavanca de controle
  // A configuração pode ser necessária para os valores corretos das alavancas de controle.
  data.throttle = mapJoystickValues( analogRead(A0), 12, 510, 1020, true); //(Aileron)
  Serial.print(data.throttle);
  Serial.print(" - ");
  data.roll = mapJoystickValues( analogRead(A1), 0, 128, 255, true);      //(Throttle) "verdadeiro" ou "falso" para a direção do servo
  Serial.print(data.roll);
  Serial.print(" - ");
  data.pitch = mapJoystickValues( analogRead(A2), 0, 500, 1020, false);     // "verdadeiro" ou "falso" para a direção do servo
  Serial.print(data.pitch);
  Serial.print(" - ");
  data.yaw = mapJoystickValues( analogRead(A3), 24, 524, 1020, false);       // "verdadeiro" ou "falso" para a direção do servo
  Serial.print(data.yaw);
  Serial.println("");
  radio.write(&data, sizeof(Signal));
}
