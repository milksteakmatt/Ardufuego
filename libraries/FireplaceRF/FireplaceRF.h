/*
  FireplaceRF - Library for transmitting to a Hearth & Home compatible RF fireplace.
  Created by Matthew A. Nichols, January 15, 2018.
  Released into the public domain.
*/

#ifndef FireplaceRF_h
  #define FireplaceRF_h

  #include "Arduino.h"

  class FireplaceRF 
  {
    public:
      FireplaceRF(int pin);
      void start();
      void stop();
      void on();
      void off();
      void setFan(int speed);
      void setFlame(int level);
    private:
      // Data is represented by pairs of bits.  The first bit is either high or low and the second is a fixed value.
      //      Note: In the header, the fixed value bit is different than the fixed value bit in the body.
      // Each button press sends the same message 10 times
      //      [Msg] [Msg] [Msg] [Msg] [Msg] [Msg] [Msg] [Msg] [Msg] [Msg] 
      // Each message is made up of a header and 6 message segments
      //      [Header] [Msg] [Msg] [Msg] [Msg] [Msg] [Msg]
      // The header is a high and 3 low values followed by a 1250ms pause
      //      [XX][OO][OO][OO] [pause]
      // The message segments are 8 hi and low values followed by a 1520ms pause
      //      [XX/OO] [XX/OO] [XX/OO] [XX/OO] [XX/OO] [XX/OO] [XX/OO] [XX/OO] [pause]
      // The first 3 body segments do not change and are referenced as "start" segments
      //      [Header] [Start] [Start] [Start] [Msg] [Msg] [Msg]     
      // The second 3 body segments carry the button function and value data and are referenced as "body" segments
      //      [Header] [Start] [Start] [Start] [Body] [Body] [Body] 
      // Each of the 3 body segments repeats the same data in different formats
      //      [Body1] [Body2] [Body3]
      // The first 5 bit pairs of each body segment represent the button function
      //      [Func] [Func] [Func] [Func] [Func] [XX/OO] [XX/OO] [XX/OO] [pause]
      // The last 3 bit pairs of each body segment represent values 0 to 5
      //      [Func] [Func] [Func] [Func] [Func] [Val] [Val] [Val] [pause]
      // Values are used for fan speed and flame height and fixed at 1 for on and 2 for off

      // High and Low delay values.  Represented by XX and OO for visibility 
      const unsigned int XX = 880;
      const unsigned int OO = 380;

      // Fixed bit delay as the second value in each header pair
      const unsigned int HEAD_BYTE = 420;

      // Combined with the HEAD_BYTE, the delay after each header segment
      const unsigned int HEAD_BREAK = 830;

      // Number of 2 bit pairs in the header segment
      const unsigned int HEAD_SIZE = 4;

      // Fixed bit delay for the second value in each body pair
      const unsigned int BODY_BYTE = 700;

      // Combined with the BODY_BYTE, the delay after each body segment
      const unsigned int BODY_BREAK = 820;

      // Number of 2 bit pairs in the function segment of the body
      const unsigned int FUNC_SIZE = 5;

      // Number of 2 bit pairs in the value segment of the body used to represent values 0 to 5
      const unsigned int VAL_SIZE = 3;

      // Combined with the BODY_BYTE, the delay after each message
      const unsigned long MSG_BREAK = 90900;

      // Message is repeated multiple times
      const unsigned int MSG_REPEAT = 5;

      // Number of 2 bit pairs in the body segment of the message
      const unsigned long BODY_SIZE = 8;

      // Body is the last 3 segments that change each message
      const unsigned int BODY_REPEAT = 3;

      // Convenience value to use the same transmit and separate function from value
      const unsigned int NO_BREAK = 0;

      // Max reliable delay for Arduino delayMicroseconds
      const unsigned long MAX_DELAY = 16383;

      const unsigned long header[4] = {860, 380, 880, 380};

      const unsigned long start[3][8] = {
        {OO, XX, XX, OO, OO, OO, OO, XX},
        {OO, XX, OO, OO, XX, XX, XX, OO},
        {OO, OO, XX, XX, OO, OO, XX, XX}
      };

      const unsigned long onOff[3][5] = {
        {OO, OO, OO, OO, OO},
        {OO, OO, XX, XX, XX},
        {XX, XX, OO, OO, OO}
      };

      const unsigned long flame[3][5] = {
        {OO, OO, XX, XX, OO},
        {OO, XX, XX, OO, XX},
        {XX, OO, OO, XX, OO}
      };

      const unsigned long fan[3][5] = {
        {OO, XX, OO, OO, OO},
        {OO, XX, XX, XX, OO},
        {XX, OO, OO, OO, XX}
      };

      const unsigned long value[6][3][3] = {
        { {OO, OO, OO},
          {XX, XX, XX},
          {OO, OO, OO}
        },
        { {OO, OO, XX},
          {OO, OO, OO},
          {XX, XX, XX}
        },
        { {OO, XX, OO},
          {OO, OO, XX},
          {XX, XX, OO}
        },
        { {OO, XX, XX},
          {OO, XX, OO},
          {XX, OO, XX}
        },
        { {XX, OO, OO},
          {OO, XX, XX},
          {XX, OO, OO}
        },
        { {XX, OO, XX},
          {XX, OO, OO},
          {OO, XX, XX}
        }
        
      };

      int outPin;
      byte pinState;

      void transmit(const unsigned long msg[], const unsigned int msgSize, const unsigned int msgByte, const unsigned int endDelay);
      void sendMsg(int msg, int val);
  };

#endif