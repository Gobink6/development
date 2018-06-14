#include<ESP8266WiFi.h>
#include <Adafruit_MQTT_Client.h>
#include<ESP8266WebServer.h>
#include <EEPROM.h>
ESP8266WebServer warsaw;
const char username1[]="HIII";
const char password1[]="123456789";

#define wifi "HWjunction"
#define password "knogbuf5$"
#define server "io.adafruit.com"
#define port 1883
#define username "ij"
#define key "e0d6b6366e8a49f29015590ad4bac7f8"
WiFiClient Robot;
Adafruit_MQTT_Client mqtt1(&Robot,server,port,username,key);
Adafruit_MQTT_Subscribe feed = Adafruit_MQTT_Subscribe(&mqtt1,"ij/feeds/please");
int total_A=0;
int total_B=0;
int total_C=0;
int current_A=0;
int current_B=0;
int current_C=0;
int final_piece=0;
int flag_A,flag_B,flag_C,flag1_A,flag2_B,flag3_C;
int eeAddress=0;
int checkpoint1=0;
int checkpoint;
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT");
  Serial.print("Connecting to ");
  Serial.println(wifi);
  WiFi.begin(wifi,password);
  WiFi.softAP(username1,password1);
   IPAddress IPname=WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(IPname);
  warsaw.begin();
  warsaw.on("/display",display);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
Serial.println("WiFi connected");
Serial.println("IP Address:");
Serial.println(WiFi.localIP());
mqtt1.subscribe(&feed);
Serial.println("Connecting to MQTT");

  EEPROM.begin(512);
while(mqtt1.connect())
{
  delay(500);
  Serial.print(".");
}


}
void loop()
{
  

 
    while(mqtt1.readSubscription(5000))
  {
     while (!Serial) {
    ; 
  }int eeAddress=0;
  EEPROM.get(eeAddress, checkpoint);
  Serial.println("checkpoint ");
  Serial.print(checkpoint);
 if(checkpoint==30)
 {
    while (!Serial) {
    ; 
  } eeAddress =4;
  EEPROM.get(eeAddress, total_A);
  eeAddress +=sizeof(int);
  while (!Serial) {
    ; 
  }
  EEPROM.get(eeAddress, current_A);
  eeAddress +=sizeof(int);
  while (!Serial) {
    ; 
  }
  EEPROM.get(eeAddress, total_B);
  eeAddress +=sizeof(int);
  while (!Serial) {
    ; 
  }
  EEPROM.get(eeAddress, current_B);
  eeAddress +=sizeof(int);
  while (!Serial) {
    ; 
  }
  EEPROM.get(eeAddress, total_C);
  eeAddress +=sizeof(int);
  while (!Serial) {
    ; 
  }
  EEPROM.get(eeAddress, current_C);
 Serial.println("EEPROM");
  Serial.println(total_A);
 }
      int A=0,B=0,C=0,desginer=0,data=0;flag_A=0;flag_B=0;flag_C=0,flag1_A=0;flag2_B=0;flag3_C=0;
    Serial.print("recieving data : ");
    Serial.print((char *)feed.lastread);
     data=atoi((char *)feed.lastread);
    Serial.print(" ");
    Serial.println(data);
    if(data>=300)
      {C=data-300;
      Serial.print("tailor C:");Serial.println(C);}
    else if(data>=200)
      {B=data-200;
      Serial.print("tailor B:");Serial.println(B);}
    else if(data>=100)
    {A=data-100;
    Serial.print("tailor A:");Serial.println(A);}
    else
    {desginer=data;
    Serial.print("Marker :");Serial.println(desginer);}
 current_A=current_A+desginer;
 if(current_A>=A)
 {
 total_A=total_A+A;
 current_A=current_A-A;
 current_B=current_B+A;
 }
  else if(current_A<A)
  {
     total_A=total_A+current_A;
    current_B=current_B+current_A;
  current_A=0;
 }
  if(current_A==0)
  flag_A=1;
  if(current_B>=B)
  {
  total_B=total_B+B;
 current_B=current_B-B;
 current_C=current_C+B;
 }
 else if(current_B<B)
 {
  total_B=total_B+current_B;
 current_C=current_C+current_B;
  current_B=0;
 }
  if(current_B==0)
  flag_B=1;
 if(current_C>=C)
 {
  total_C=total_C+C;
 current_C=current_C-C;
 final_piece=total_C;
 }
  else if(current_C<C)
  {  total_C=total_C+current_C;
 final_piece=total_C;
  current_C=0;
}
  if(current_C==0)
  flag_C=1;
  if(current_A>=10)
  
  if(current_A>=10)
  flag1_A=1;
  if(current_B>=10)
   flag2_B=1;
  if(current_C>=10)
   flag3_C=1;
  
 Serial.print("Total piece in Tailor A:");
 Serial.println(total_A);
   Serial.print("Current piece in Tailor A:");
   Serial.println(current_A);  
  Serial.print("Total piece in Tailor B:");
  Serial.println(total_B);
   Serial.print("Current piece in Tailor B:");
   Serial.println(current_B);
    Serial.print("Total piece in Tailor C:");
    Serial.println(total_C);
   Serial.print("Current piece in Tailor C:");
   Serial.println(current_C);
   Serial.print("Final no.of clothes");
   Serial.println(final_piece);
   
checkpoint1++;
if(checkpoint1==30)
{
  Serial.println("\n/n\n/n");
  Serial.println("EEPROM writting");
     int eeAdress=0;
     EEPROM.put(eeAddress,checkpoint1 );
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, checkpoint1);
  EEPROM.commit();
  
    EEPROM.put(eeAddress,total_A );
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, total_A);
  EEPROM.commit();
    EEPROM.put(eeAddress, current_A);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, current_A);
  EEPROM.commit();

    EEPROM.put(eeAddress, total_B);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, total_B);
  EEPROM.commit();
    EEPROM.put(eeAddress, current_B);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, current_B);
  EEPROM.commit();

    EEPROM.put(eeAddress, total_C);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, total_C);
  EEPROM.commit();
    EEPROM.put(eeAddress, current_C);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, current_C);
  EEPROM.commit();
  ESP.restart();
}
  
  warsaw.handleClient();
  }
  }
  void display()
  {
    String myhtml="<html><head><style>table, th, td {border: 1px solid black;border-collapse: collapse;th, td {padding: 5px;text-align: left;    }</style></head><body><h2><center>Warshaw_Report</center></h2><h3>Final no.of Pieces : "+String(final_piece)+"</h3><table style=\"width:100%\"><tr><th>Process_details</th><th>worker1</th><th>worker2</th><th>worker3</th></tr><tr><td>Total Work</td><td>"+String(total_A)+"</td><td>"+String(total_B)+"</td><td>"+String(total_C)+"</td></tr><tr><td>Current Piece</td><td>"+String(current_A)+"</td><td>"+String(current_B)+"</td><td>"+String(current_C)+"</td></tr><tr><td>Worker have less clothes</td><td>"+String(flag_A)+"</td><td>"+String(flag_B)+"</td><td>"+String(flag_C)+"</td></tr><tr><td>Worker have more clothes</td><td>"+String(flag1_A)+"</td><td>"+String(flag2_B)+"</td><td>"+String(flag3_C)+"</td></tr></table></body></html>";
warsaw.send(200,"text/html",myhtml);

  }




