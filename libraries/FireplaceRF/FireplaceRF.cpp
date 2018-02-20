/*
  FireplaceRF.cpp - Library for transmitting to a Hearth & Home compatible RF fireplace.
  Created by Matthew A. Nichols, January 15, 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "FireplaceRF.h"

FireplaceRF::FireplaceRF(int pin) 
{
  outPin = pin;
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin,LOW);
  //delayMicroseconds(13000);
}

void FireplaceRF::transmit(const unsigned long msg[], const unsigned int msgSize, const unsigned int msgByte, const unsigned int endDelay) 
{
  for (int y = 0; y < msgSize; y++){
    digitalWrite(outPin,pinState);
    unsigned long z = msg[y];
    delayMicroseconds(z);
    pinState = !pinState;
    digitalWrite(outPin,pinState);
    delayMicroseconds(msgByte);
    pinState = !pinState;
  }
  delayMicroseconds(endDelay);
}

void FireplaceRF::sendMsg(int msg, int val) 
{
  // msg: ON = 0, OFF = 1, FAN = 2, FLAME = 3
  pinState = 1;
  noInterrupts();
  for (int x = 1; x <= MSG_REPEAT; x++) {
    transmit(header, HEAD_SIZE, HEAD_BYTE, HEAD_BREAK);
    for (int y = 0; y < 3; y++) {
      transmit(start[y], BODY_SIZE, BODY_BYTE, BODY_BREAK);
    }      
    for (int z = 0; z < 3; z++) {
      switch(msg) {
        case 0 :
        transmit(onOff[z], FUNC_SIZE, BODY_BYTE, NO_BREAK);
        val = 1;
        break;
        case 1:
        transmit(onOff[z], FUNC_SIZE, BODY_BYTE, NO_BREAK);
        val = 2;
        break;
        case 2:
        transmit(fan[z], FUNC_SIZE, BODY_BYTE, NO_BREAK);
        break;
        case 3:
        transmit(flame[z], FUNC_SIZE, BODY_BYTE, NO_BREAK);
        break;
      }
      transmit(value[val][z], VAL_SIZE, BODY_BYTE, BODY_BREAK);
    }
    if (x < MSG_REPEAT) {
      unsigned long END_DELAY = MSG_BREAK;
      while (END_DELAY > MAX_DELAY) {
        delayMicroseconds(MAX_DELAY);
        END_DELAY = END_DELAY - MAX_DELAY;
      }
      delayMicroseconds(END_DELAY);
    }      
  }
  interrupts();
}

void FireplaceRF::start()
{
  sendMsg(0,1);
  delayMicroseconds(1000);
  sendMsg(2,0);
  delayMicroseconds(1000);
  sendMsg(3,1);
}

void FireplaceRF::stop()
{
  sendMsg(2,3);
  delayMicroseconds(1000);
  sendMsg(1,2);
}

void FireplaceRF::on() 
{
  sendMsg(0,1);
}

void FireplaceRF::off() 
{
  sendMsg(1,2);
}

void FireplaceRF::setFan(int speed) 
{
  sendMsg(2,speed);
}

void FireplaceRF::setFlame(int level) 
{
  sendMsg(3,level);
}