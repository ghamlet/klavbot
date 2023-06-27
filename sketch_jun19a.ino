//правое переднее   f11    r10
//правое заднее   f12    r9
//левое переднее   f4    r7
//левое заднее   f6    r5
#define PIN_IN3 23
#define PIN_IN4 25

#define rff 11
#define rfr 10
#define rrf 12
#define rrr 9
#define lff 7
#define lfr 4
#define lrf 6
#define lrr 5
#include "FlySkyIBus.h"

#include <Servo.h> // подключаем библиотеку для работы с сервоприводом
Servo servo; // объявляем переменную servo типа "servo1"


int x = 0;
int y = 0;
int camera = 0;
int c = 0;
int r = 0;
int l = 0;

int manip = 0;
bool flag = false;
void setup()
{
  Serial.begin(115200);
  IBus.begin(Serial2);
  for (int i = 4; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  servo.attach(2); 
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(28,OUTPUT);
  digitalWrite(22,0);
  digitalWrite(24,0);
  digitalWrite(26,0);
  digitalWrite(28,0);

  pinMode(PIN_IN3,OUTPUT);
  pinMode(PIN_IN4,OUTPUT);
  
  delay(2000);
}

void loop()
{
  IBus.loop();
  x = IBus.readChannel(0);
  y = IBus.readChannel(1);
  camera = IBus.readChannel(2);
  manip = IBus.readChannel(6);
   
  x = map(x, 1000, 2000, -255, 255);
  y = map(y, 1000, 2000, -255, 255);
  camera = map(camera, 1000, 2000, 0, 180);
  
  manip = map(manip, 1000, 2000, -1, 1);
  //Serial.print(manip);


 ///MANIPULYTOR///
  if (manip == 0){
    
    digitalWrite(PIN_IN3,0);
    digitalWrite(PIN_IN4,0);
    flag = true;
    
  }else if ((manip == -1) && (flag == true)){ //stick up  close
    
   digitalWrite(PIN_IN3,1);
    digitalWrite(PIN_IN4,0); 
    
  } else if (manip == 1){
    
    digitalWrite(PIN_IN3,0);
    digitalWrite(PIN_IN4,1);
  }


  if ((x < 50) && (x > -50)) {
    x = 0;
  }
  if (x > 150) {
    x = 255;
  }
  if (x < -150) {
    x = -255;
  }


  if ((y < 50) && (y > -50)) {
    y = 0; 
  }
  if (y > 150) {
    y = 255;
  }
  if (y < -150) {
    y = -255;
  }

  if ((camera < 95) && (camera > 85)) {
    camera = 0;
  }
  servo.write(camera);
  l = x + y;
  r = y - x;


  if ((r < 50) && (r > -50)) {
    r = 0;
  }
  if (r > 150) {
    r = 255;
  }
  if (r < -150) {
    r = -255;
  }
  if ((l < 50) && (l > -50)) {
    l = 0;
  }
  if (l > 150) {
    l = 255;
  }
  if (l < -150) {
    l = -255;
  }
  if(l>0){
    digitalWrite(lfr,0);
    digitalWrite(lrr,0);
    analogWrite(lff,l);
    analogWrite(lrf,l);
  } else{
    digitalWrite(lff,0);
    digitalWrite(lrf,0);
    analogWrite(lfr,-l);
    analogWrite(lrr,-l);
  }
  if(l==0){
    digitalWrite(lff,0);
    digitalWrite(lrf,0);
    digitalWrite(lfr,0);
    digitalWrite(lrr,0);
  }

    if(r>0){
    digitalWrite(rfr,0);
    digitalWrite(rrr,0);
    analogWrite(rff,r);
    analogWrite(rrf,r);
  } else{
    digitalWrite(rff,0);
    digitalWrite(rrf,0);
    analogWrite(rfr,-r);
    analogWrite(rrr,-r);
  }
  if(r==0){
    digitalWrite(rff,0);
    digitalWrite(rrf,0);
    digitalWrite(rfr,0);
    digitalWrite(rrr,0);
  }
  
  
//  Serial.print("  x=");
//  Serial.print(x);
//  Serial.print("  y=");
//  Serial.print(y);
//  Serial.print("  b=");
//  Serial.print(b);
//  Serial.println();
//  delay(300);

}
