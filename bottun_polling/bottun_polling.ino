#define PIN_BTN  15


void setup() {
  Serial.begin(115200);
  pinMode(PIN_BTN, INPUT);
}

void loop() {

  int btn_on_check;
  btn_on_check = digitalRead(PIN_BTN);
  Serial.print(btn_on_check);
  delay(1);
  
}
