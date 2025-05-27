const int analogPin = A0;       // Аналоговый пин для потенциометра
const int pwmLedPin = 6;        // Цифровой пин с ШИМ для светодиода

bool isSender = false;          // По умолчанию каждый МК сначала Приемник
int previousValue = -1;
int receivedValue = 0;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(pwmLedPin, OUTPUT);
  analogWrite(pwmLedPin, 0);

  Serial.begin(9600);
  delay(1000); // Ожидание стабильности UART

  // Определение роли: если сигнал на A0 > 10, значит подключён потенциометр, а МК выполняет роль Отправителя
  if (analogRead(analogPin) > 10) {
    isSender = true;
  }
}

void loop() {
  if (isSender) {                                 // Если МК Отправитель
    int analogValue = analogRead(analogPin);      // Считывание аналогового сигнала
    int valueToSend = analogValue / 4;            // Преобразуем 0–1023 в 0–255
    if (valueToSend != previousValue) {
      Serial.println(valueToSend);
      previousValue = valueToSend;
      delayMicroseconds(100);                     // Задержка 10 мс необходима для сглаживания колебаний яркости светодиода
    }
  } else {                                        // Если МК Приемник
    if (Serial.available()) {
      receivedValue = Serial.parseInt();
      analogWrite(pwmLedPin, constrain(receivedValue, 0, 255));
    }
  }
}