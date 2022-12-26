#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10, 1000000U);
const byte address[6] = "01101";
uint16_t angle = 90;
Servo pointServo;

void setup() 
{
  pointServo.attach(5);
  pointServo.write(angle);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}


void loop()
{
  if (radio.available())            
  {
    radio.read(&angle, sizeof(angle));
    pointServo.write(angle);
  }
  delay(5);
}
