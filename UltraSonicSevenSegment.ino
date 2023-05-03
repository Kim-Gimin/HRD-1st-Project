#include <SoftwareSerial.h>
#include <MsTimer2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_arduino_lib.h"
#include "my_fnd_lib.h"
#include "my_key_lib.h"


#define trigPin A0
#define echoPin A1

SoftwareSerial MTX(16, 17);  //17TX
SoftwareSerial STX(18, 19); //19TX

int cnt;
long distance = 0;

void time2_irq(){
   fnd_dis(distance);
}

void setup() {
  DDRD = 0xff;
  DDRB = 0xff;
  pinMode(trigPin, OUTPUT);  // 초음파 핀코드
  pinMode(echoPin, INPUT);  // 초음파 핀코드
  MsTimer2::set(4, time2_irq);
  MsTimer2::start();
  pinMode(17, OUTPUT); // 보드2 송신 핀코드
  pinMode(19, OUTPUT); // 보드3 송신 핀코드
  MTX.begin(9600); // 보드 2로 블루투스 통신 초기화(SoftwareSerial 통신 초기화)
  STX.begin(9600); // 보드 3로 블루투스 통신 초기화(SoftwareSerial 통신 초기화)
}

void loop() {
   digitalWrite(trigPin, HIGH);  //초음파 체크
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   distance = pulseIn(echoPin, HIGH) / 58;
  MTX.write(distance); // 보드 2로 distance 값 송신
  delay(500);
  STX.write(distance);  // 보드 3으로 distance 값 송신
  delay(500);
}