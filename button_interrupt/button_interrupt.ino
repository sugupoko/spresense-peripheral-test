#define PIN_BTN  15

void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN), interruptsw, FALLING ); 
}

void loop() {
  delay(100);
}

void interruptsw(void)
{
  Serial.println("interrupt!!");  
}
