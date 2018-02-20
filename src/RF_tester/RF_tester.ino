int receive_pin = 2;

// Change MAX to 800 for Mega to see entire message
#define MAX 200
int value[MAX];
unsigned long time[MAX];
int changes;
int printed;

void setup() {                
  Serial.begin(9600);
  pinMode(receive_pin, INPUT);

  changes = 0;
  printed = 0;
  attachInterrupt(4, change_handler, CHANGE);
  Serial.println("Receiver 433MHz setup");
}

void change_handler()
{
  if (changes >= MAX) return;
  value[changes] = digitalRead(receive_pin);
  time[changes] = micros();
  changes++;
}

void loop() {
  if (printed + 1 < changes) {
    Serial.print(printed);
    Serial.print(" ");
    Serial.print(value[printed]);
    Serial.print(" ");
    Serial.println(time[printed+1] - time[printed]);
    printed++;
  }
}

