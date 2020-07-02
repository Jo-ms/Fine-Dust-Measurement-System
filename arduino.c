#include <HuemonelabKit.h>
#include <HuemonelabKit.h>

Bluetooth BT(2,3); // ������� TX,Rx �� ����
//RGBLed rgb(11,12,13); // RGB LED�� ����

int blue_pin = 13; // 13���ɿ� Blue
int green_pin = 12;// 12���ɿ� Green
int red_pin = 11;// 11���ɿ� Red

int inA = 9; // �Ҹ��� ��� iNA 9����  
int inB = 8;// �Ҹ��� ��� iNB 8����
int dustPin = A0; // �̼����� ���� �� ����
int ledPower = 10; // �̼����� ������ ���ܼ� ���� �� ����

int samplingTime = 280; // ���� LED�� ���� ��� ��ȣ �ð� ����
int deltaTime = 40;// LED�� �ٽ� ������ 40 ����ũ���� ���� �Ͻ�����
int sleepTime  = 9680; 
 

float voMeasured = 0; // �̼����������� �д� ��
float calcVoltage = 0;// �̼����������� �����ϴ� �����ȣ
float dustDensity =0;// �̼����� �������� ȯ��

double dust[] = {10.18, 54.22, 136.28, 221.99}; //�׽�Ʈ �ڵ�

void setup(){

Serial.begin(9600);
pinMode(ledPower,OUTPUT); //�̼����� ���� ���ܼ� LED�� ��� ����
BT.begin(9600); // ������� ����
pinMode(inB, OUTPUT); // �� ��� ��� ����
pinMode(inA, OUTPUT); // �� ��� ��� ����
  
}

 

void loop(){

  digitalWrite(ledPower,LOW); // �̼����� LED �ѱ�
  delayMicroseconds(samplingTime); // ���ø��ð����� ������
  voMeasured= analogRead(dustPin);// �̼��������� ����
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // �̼����� LED ����
  delayMicroseconds(sleepTime);
  
  calcVoltage= voMeasured *(5.0/1024.0); // �̼����� �е� ����
  dustDensity = abs((0.17*calcVoltage - 0.1)*1000); //ug/m^3 ������ ��� ����
  
  Serial.println(dustDensity);
  BT.println(dustDensity); 
  delay(3000);
   //�̼������� ���  
   if (dustDensity >151){
    setColor(255,0,0);
    digitalWrite(red_pin, HIGH); //�̼����� ���� 150�̻��� ��� 0.5�� ���� Red LED ����
    delay(100);
    
    digitalWrite(red_pin, LOW);
    delay(100);
    
    digitalWrite(inA, LOW); //���ʹ������� �� ���� ����
    digitalWrite(inB, HIGH);//�����ʹ��� OFF
    
   } else if (dustDensity >81){
    setColor(255,0,0); //�̼��������� 81�̻��ϰ�� Red LED ���
   digitalWrite(inA, HIGH); // ���ʹ������� �� ���� ���� 
  digitalWrite(inB, LOW); //������ ���� OFF
  
 
 }else if (dustDensity >31 && dustDensity < 80){ 
  setColor(0,255,0); // �̼��������� 31�̻� 80�̸��ϰ�� Green LED ���
  digitalWrite(green_pin, HIGH);
  delay(500); 
  digitalWrite(green_pin, LOW);
  delay(500);
  digitalWrite(inA, LOW);  
  digitalWrite(inB, LOW);
  

 }else if (dustDensity >0 && dustDensity < 30) {

  setColor(0,0,255); //�̼����� ���� 0�̻� 30�̸� �� ��� Blue LED ��� 
  digitalWrite(inA, LOW); 
  digitalWrite(inB, LOW);
 }
}

 

void setColor(int red, int green, int blue) {  //RGB LED ����� ���� �Ƴ��α� ��� ����

  analogWrite(red_pin, 255-red);
  analogWrite(green_pin, 255-green);
  analogWrite(blue_pin, 255-blue); 
}