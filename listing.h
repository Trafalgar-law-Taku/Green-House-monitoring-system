#include <Servo.h>
Servo servo;
int level=0;
float temperature=0;
int  valhumidity=0;
int detection=0;

int pir=2;
int buzzerPin=3;
int  relay1=4;
int relay2=5;
int green=9;
int red=10;

int ldr1;
int  ldr2;
int temp;
int waterlevel;
int humidity1;
int humidity2;


void  setup(){
Serial.begin(9600);
servo.attach(11);
pinMode(green, OUTPUT);
pinMode(red,  OUTPUT);
pinMode(pir, INPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(relay1,  OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(waterlevel, INPUT);
pinMode(humidity1,  INPUT);
pinMode(humidity2, INPUT);
pinMode(temp, INPUT);
pinMode(ldr1,  INPUT);
pinMode(ldr2, INPUT);
}
void loop()
{
  temp=analogRead(A2);
  temperature =((temp * 0.00488) - 0.5) / 0.01;
  detection=digitalRead(pir);
  waterlevel=analogRead(A3);
  
  ldr1 = analogRead(A0);
  ldr2 = analogRead(A1);
  Serial.print("ldr1 is:");
  Serial.print(ldr1);
  Serial.print("  |   ");
  Serial.print("ldr2 is:");
  Serial.print(ldr2);
  Serial.print("  |   ");
  Serial.print("water level is:");
  Serial.println(waterlevel);
  Serial.print("  |   ");
  Serial.print("temperature is:");
  Serial.println(temperature);
  
  if((ldr1-ldr2)>=250 || (ldr2-ldr1)>=250) {// vero se una delle due espressioni  è vera
   if(detection==HIGH)
   servo.write(0);
    digitalWrite(relay1,HIGH);{
    for(int i=1; i<6; i++) {
  tone(buzzerPin, 1000, 500);
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  delay(500);    
  digitalWrite(red,LOW);
  delay(500);}
  delay(5000);}}
    
  else{
    if(((ldr1+ldr2)/2)>700  && temperature>15  ){
    servo.write(90);
    digitalWrite(relay1,LOW);
    delay(1000);}
    
    if(((ldr1+ldr2)/2)<700 || temperature>15  ){
    servo.write(0);
    digitalWrite(relay1,HIGH);
    delay(1000);}
    
    
  if(waterlevel<180){
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);  
  digitalWrite(relay2,LOW);
    if(detection==HIGH){
    for(int i=1;  i<5; i++) {
  tone(buzzerPin, 1000, 500);
  delay(1000);}
  delay(5000);}}
    
  else{
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
  digitalWrite(relay2,  LOW);
  do{
  digitalWrite(relay2, HIGH);
  humidity1=analogRead(A4);
  humidity2=analogRead(A5);}
  while (((humidity1+humidity2)/2)> 500);
  digitalWrite(relay2,  LOW);
  delay(1000);
  }}}