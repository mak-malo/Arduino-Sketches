const int analogPin = A0;       // Аналоговый пин для потенциометра
//const int pwmLedPin = 9;        // Цифровой пин с ШИМ для светодиода
const int buttonSlave = 7;

bool isSender = false;          // По умолчанию каждый МК сначала Приемник
int previousValue = -1;
//int receivedValue = 0;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(buttonSlave, INPUT);
//  pinMode(pwmLedPin, OUTPUT);
//  analogWrite(pwmLedPin, 0);
//  strip.show();

  Serial.begin(960000);
  delay(1000); // Ожидание стабильности UART
}

void loop() {
  int analogValue = analogRead(analogPin);      // Считывание аналогового сигнала
  int valueToSend = analogValue / 4;            // Преобразуем 0–1023 в 0–255
  Serial.println(valueToSend);
  delayMicroseconds(100);
}

