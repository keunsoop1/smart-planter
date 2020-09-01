#include <dht.h>    // dht lib

dht DHT;    // initialise dht sensor

#define DHT11_PIN 7

int soilValue = 0;    // 토양 수분값 0으로 설정
int soilPin = A0;        // 토양 센서를 A0 핀으로 설정 
int chk;
float temp;
float hum;
int ldrValue;
int redLEDPin = 13;     // 물에 빨간색 led 13번 핀으로 설정 (water)
int yellowLEDPin = 12;  // ldr 에 빨간색 led 12번 핀으로 설정 (ldr)
int ldrPin = A1;        // ldr 을 A1 핀으로 설정
int motorPin = 3;       // 모터 핀을 3번 핀으로 설정
/* 'A': auto
   'M': manual
   'O': on
   'F': off
*/
char status;
int lightLevel;

void setup() {
  Serial.begin(9600);
  //Serial.println("토양 수분 센서 읽기 시작");
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(motorPin, OUTPUT);
  
  delay (2000);
  }

void loop() {
  // 서버로 부터 데이터 수신
  if (Serial.available() ) {
    status = Serial.read();
  }
  
  chk = DHT.read11(DHT11_PIN);
  temp = DHT.temperature;
  hum = DHT.humidity;  
  soilValue = analogRead(soilPin);
  ldrValue = analogRead(ldrPin);
  
  Serial.println(temp);
  Serial.println(hum);
  Serial.println(soilValue);
  Serial.println(ldrValue);
  
  if (status == 'A') {
    if (soilValue> 500) {
      analogWrite (motorPin, 200);
      digitalWrite (redLEDPin, HIGH);
    } else {
      digitalWrite (redLEDPin, LOW);
      analogWrite (motorPin, LOW);
    }
 } else if (status == 'M'|| status == 'F') {
    if (soilValue> 500) {
      analogWrite (motorPin, LOW);
      digitalWrite (redLEDPin, HIGH);
    } else {
      digitalWrite (redLEDPin, LOW);
      analogWrite (motorPin, LOW);
    }
  } else if (status == 'O') {
    if (soilValue> 500) {
      digitalWrite (redLEDPin, HIGH);
    } else {
      digitalWrite (redLEDPin, LOW);
    }
    analogWrite (motorPin, 200);
  } else {
    if (soilValue> 500) {
      digitalWrite (redLEDPin, HIGH);
    } else {
      digitalWrite (redLEDPin, LOW);
    }
    analogWrite (motorPin, LOW);
  }
  
  if (ldrValue> = 300) {
    digitalWrite (yellowLEDPin, HIGH);
  } else {
    digitalWrite (yellowLEDPin, LOW);
  }
  지연 (4000);
}

