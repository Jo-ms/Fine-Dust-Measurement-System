#include <HuemonelabKit.h>
#include <HuemonelabKit.h>

Bluetooth BT(2,3); // 블루투스 TX,Rx 핀 설정
//RGBLed rgb(11,12,13); // RGB LED핀 설정

int blue_pin = 13; // 13번핀에 Blue
int green_pin = 12;// 12번핀에 Green
int red_pin = 11;// 11번핀에 Red

int inA = 9; // 팬모터 모듈 iNA 9번핀  
int inB = 8;// 팬모터 모듈 iNB 8번핀
int dustPin = A0; // 미세먼지 센서 핀 설정
int ledPower = 10; // 미세먼지 센서의 적외선 감지 핀 설정

int samplingTime = 280; // 내부 LED를 켠후 출력 신호 시간 설정
int deltaTime = 40;// LED를 다시 끄기전 40 마이크로초 동안 일시정지
int sleepTime  = 9680; 
 

float voMeasured = 0; // 미세먼지센서가 읽는 값
float calcVoltage = 0;// 미세먼지센서가 측정하는 전기신호
float dustDensity =0;// 미세먼지 계산식으로 환산

double dust[] = {10.18, 54.22, 136.28, 221.99}; //테스트 코드

void setup(){

Serial.begin(9600);
pinMode(ledPower,OUTPUT); //미세먼지 센서 적외선 LED핀 모드 설정
BT.begin(9600); // 블루투스 설정
pinMode(inB, OUTPUT); // 팬 모듈 모드 설정
pinMode(inA, OUTPUT); // 팬 모듈 모드 설정
  
}

 

void loop(){

  digitalWrite(ledPower,LOW); // 미세먼지 LED 켜기
  delayMicroseconds(samplingTime); // 샘플링시간동안 딜레이
  voMeasured= analogRead(dustPin);// 미세먼지값을 읽음
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // 미세먼지 LED 끄기
  delayMicroseconds(sleepTime);
  
  calcVoltage= voMeasured *(5.0/1024.0); // 미세먼지 밀도 계산식
  dustDensity = abs((0.17*calcVoltage - 0.1)*1000); //ug/m^3 단위로 출력 설정
  
  Serial.println(dustDensity);
  BT.println(dustDensity); 
  delay(3000);
   //미세먼지값 출력  
   if (dustDensity >151){
    setColor(255,0,0);
    digitalWrite(red_pin, HIGH); //미세먼지 값이 150이상일 경우 0.5초 마다 Red LED 점멸
    delay(100);
    
    digitalWrite(red_pin, LOW);
    delay(100);
    
    digitalWrite(inA, LOW); //왼쪽방향으로 팬 모터 동작
    digitalWrite(inB, HIGH);//오른쪽방향 OFF
    
   } else if (dustDensity >81){
    setColor(255,0,0); //미세먼지값이 81이상일경우 Red LED 출력
   digitalWrite(inA, HIGH); // 왼쪽방향으로 팬 모터 동작 
  digitalWrite(inB, LOW); //오른쪽 방향 OFF
  
 
 }else if (dustDensity >31 && dustDensity < 80){ 
  setColor(0,255,0); // 미세먼지값이 31이상 80미만일경우 Green LED 출력
  digitalWrite(green_pin, HIGH);
  delay(500); 
  digitalWrite(green_pin, LOW);
  delay(500);
  digitalWrite(inA, LOW);  
  digitalWrite(inB, LOW);
  

 }else if (dustDensity >0 && dustDensity < 30) {

  setColor(0,0,255); //미세먼지 값이 0이상 30미만 일 경우 Blue LED 출력 
  digitalWrite(inA, LOW); 
  digitalWrite(inB, LOW);
 }
}

 

void setColor(int red, int green, int blue) {  //RGB LED 출력을 위한 아날로그 출력 세팅

  analogWrite(red_pin, 255-red);
  analogWrite(green_pin, 255-green);
  analogWrite(blue_pin, 255-blue); 
}