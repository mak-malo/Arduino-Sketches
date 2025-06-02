const int analogPin = A0;       // Аналоговый пин для потенциометра
const int pwmLedPin = 9;        // Цифровой пин с ШИМ для светодиода

bool isSender = true;          // По умолчанию каждый МК сначала Приемник
int previousValue = -1;
int receivedValue = 0;
const int buttonSlave = 7;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(pwmLedPin, OUTPUT);
  analogWrite(pwmLedPin, 0);

  Serial.begin(9600);
  delay(1000); // Ожидание стабильности UART
}

void loop() {

  if (digitalRead(buttonSlave) == LOW) {
    delay(30);
    if (digitalRead(buttonSlave) == LOW) {
      isSender = false;
    }
  }

  if (isSender) {                                 // Если МК Отправитель
    int analogValue = analogRead(analogPin);      // Считывание аналогового сигнала
    int valueToSend = analogValue / 4;            // Преобразуем 0–1023 в 0–255
    if (valueToSend != previousValue) {
      Serial.println(valueToSend);
      previousValue = valueToSend;
      delayMicroseconds(100);                     // Задержка 10 мс необходима для сглаживания колебаний яркости светодиода
    }
  }
   else {                                        // Если МК Приемник
    if (Serial.available()) {
      receivedValue = Serial.parseInt();
      analogWrite(pwmLedPin, receivedValue / 4);

    }
  }
}
