#include <FireplaceRF.h>

const int PIN_FIRE_TX = 3;
FireplaceRF fireplace(PIN_FIRE_TX);

const bool debug = true;
bool done = false;

void setup() {
  if (debug) {
    Serial.begin(9600);
    Serial.println("setup");    
  }
}

void loop() { 
  if (!done) {
    fireplace.on();
    delay(2000);
    fireplace.setFan(0);
    delay(2000);
    fireplace.setFlame(1);
    done = true;
  }
}
