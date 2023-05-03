#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 =6, d7 =7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "my_arduino_lib.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//모터
#define M1_pin  10
#define M2_pin  11
#define EN_pin  12

// 송신부 trig를 3번 수신부 echo를 2번으로 변수 선언합니다.


unsigned char S_distance = 0;
char back_distance = 0;
char d_buf[20];

SoftwareSerial MTX(18, 19);

//모터 cw방향
void m_cw()
{
  d_out(EN_pin, ON);

  d_out(M1_pin, ON); // d_out(M1_pin, ON);
  d_out(M2_pin, 0);       // bit_clr(PORTB, OFF);
}
//모터 ccw방향
void m_ccw()
{
  d_out(EN_pin, ON);

  d_out(M1_pin, OFF); // 0
  d_out(M2_pin, ON);  // 1
}

//모터 멈춤
void m_stop()
{
  bit_clr(PORTB, M1_pin);
  bit_clr(PORTB, M2_pin);
  d_out(EN_pin, OFF);
}

void setup() {
  // put your setup code here, to run once:



  Serial.begin(9600);

  DDRD = 0xf8;
  DDRB = 0xff;
  pinMode(18, INPUT);
  MTX.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  //실습5
  //트리거를 통해 초음파 전송 신호를 100MS 동안 보냅니다
 
  //에코를 통해 반사된 초음파를 측정합니다.
  //측정된 값은 55로 나누어서 디스탠스 변수에 저장합니다
  S_distance = MTX.read(); 

  if(S_distance != 255){
    back_distance = S_distance;
    Serial.println(S_distance, DEC);
  sprintf(d_buf,"!!! WARNING !!!");
  lcd.setCursor(0, 0);
  lcd.print(d_buf);

  //디스탠스 함수를 시리얼 모니터에 출력합니다.
 


  if(S_distance <= 10)
  {
  sprintf(d_buf,"    VERY CLOSE     ");
  lcd.setCursor(0, 1);
  lcd.print(d_buf);
  //모터 멈춤
  m_stop();
  }
  else if(S_distance > 10 && S_distance<= 20)
  {
  sprintf(d_buf,"     CLOSE     ");
  lcd.setCursor(0, 1);
  lcd.print(d_buf);
  //모터 돌아감
  m_cw();
  }
  else if(S_distance > 20 && S_distance <= 30)
  {
  sprintf(d_buf,"      FAR     ");
  lcd.setCursor(0, 1);
  lcd.print(d_buf);
  //모터 돌아감
  m_cw();
  }
  else 
  {
  sprintf(d_buf,"     VERY FAR     ");
  lcd.setCursor(0, 1);
  lcd.print(d_buf);
  //모터 돌아감
  m_cw();
  }
  }
  else S_distance = back_distance;

  delay(500);
  }