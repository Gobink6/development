#include<ESP8266WiFi.h>
#include <Adafruit_MQTT_Client.h>
#define wifi "HWjunction"
#define password "knogbuf5$"
#define server "io.adafruit.com"
#define port 1883
#define username "ij"
#define key "e0d6b6366e8a49f29015590ad4bac7f8"
WiFiClient Robot;
Adafruit_MQTT_Client mqtt(&Robot,server,port,username,key);
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish (&mqtt,"ij/feeds/please");
int buttonPushCounter = 100;   
int buttonState = 0;  
int lastButtonState =1000;
int reset1=0;
void setup()
{
  Serial.begin(115200);
  delay(10);
 
  Serial.println("Adafruit MQTT demo");
  Serial.print("Connecting to ");
  Serial.println(wifi);
  WiFi.begin(wifi,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
Serial.println("WiFi connected");
Serial.println("IP Address:");
Serial.println(WiFi.localIP());
Serial.print("Connecting to MQTT");
while(mqtt.connect())
{
  Serial.print(".");
}
}

void loop()
{
  int i;
 
 if(feed.publish(buttonPushCounter))
    {
      Serial.println("Success");
       Serial.println(buttonPushCounter);
       buttonPushCounter=100;
 for(i=0;i<2000;i++)
  {
  if(mqtt.connected())
  { 
        buttonState = analogRead(A0);
 if (buttonState > lastButtonState) {
if (buttonState>1000) {
  buttonPushCounter++;
  Serial.println(buttonPushCounter);}
  } lastButtonState = buttonState;
delay(10);
}
    }   reset1++;
if(reset1==10)
{
  ESP.restart();
}}
    else
    {
      Serial.println("Fail!");
    }
 
  } 
