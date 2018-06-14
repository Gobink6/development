#include<Servo.h> 
Servo myservo1; 
Servo myservo2;
int lm11 = 2;
int lm12 = 3;
int rm11 = 4;
int rm12 = 5;
int sensor_pin =8; 
int pos1 = 0;
int pos2 = 0;
 
void setup()
{
Serial.begin(9600);

pinMode(sensor_pin,INPUT);
pinMode(lm11,OUTPUT);
pinMode(lm12,OUTPUT);
pinMode(rm11,OUTPUT);
pinMode(rm12,OUTPUT); 
myservo1.attach(6);
myservo2.attach(7);
}

void loop()
{
 if(Serial.available() > 0)
 {
  char val = Serial.read() ;
  Serial.print(val);
 if (val == 'F')
  {
    Serial.println("FORWARD");
    digitalWrite(lm11,LOW); digitalWrite(lm12,HIGH);
    digitalWrite(rm11,LOW);digitalWrite(rm12,HIGH);
    }
  else if(val == 'B')
  {
  Serial.println("BACK");
    digitalWrite(lm11,HIGH);    digitalWrite(lm12,LOW);
    digitalWrite(rm11,HIGH);digitalWrite(rm12,LOW);
  
  }
   
  else if(val == 'R')
  {
  Serial.println("RIGHT");
    digitalWrite(lm11,LOW);  digitalWrite(lm12,HIGH); 
     digitalWrite(rm11,HIGH);   digitalWrite(rm12,LOW);
  }
   
  else if(val == 'L')
  {
   Serial.println("LEFT");
      digitalWrite(rm11,LOW); digitalWrite(rm12,HIGH);
    digitalWrite(lm11,HIGH);  digitalWrite(lm12,LOW);
  
  }
  else if(val == 'W')
  {
    
  for(pos1 = 0; pos1 <= 90; pos1 += 1)
  {                                  
    myservo1.write(pos1);            
    delay(15);                       
  } 
    if(digitalRead(sensor_pin) == HIGH)
    {
  for(pos2 = 0; pos2 <= 90; pos2 += 1)
  {                                  
    myservo2.write(pos2);            
    delay(15);                       
  }   for(pos2 = 90; pos2 >=0; pos2 -=1) 
  {                                  
    myservo2.write(pos2);              
    delay(15);                       
  } 
   } delay(2000);
  for(pos1=90; pos1>=0; pos1--)     
  {                                
    myservo1.write(pos1);              
    delay(15);                        
  } 
  } 
   else
  {
  Serial.println("Invalid!!!");
     digitalWrite(lm11,LOW);   digitalWrite(lm12,LOW); 
     digitalWrite(rm11,LOW);digitalWrite(rm12,LOW);
    

  }}}
  

