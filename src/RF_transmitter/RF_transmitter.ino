//Expected Protocol Timings
const long msg[] = {875, 425, 375, 425};

const int outPin = 3;
int go = 1;
int msgSize = sizeof(msg);

void setup() {   
  pinMode(outPin,OUTPUT);
  digitalWrite(outPin,LOW);
  delayMicroseconds(13000);
}

void loop() {
  byte pinState = 1;
  noInterrupts();
  if (go == 1) {
    for (int y = 0; y < msgSize; y++){
      digitalWrite(outPin,pinState);
      long z = msg[y];
      while (z > 16383) {
        delayMicroseconds(16383);
        z = z - 16383;
      }      
      delayMicroseconds(z);
      pinState = !pinState;
    }
  }
  go = 0;
  interrupts();
}
