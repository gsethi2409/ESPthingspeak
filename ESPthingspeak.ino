#include <ESP8266WiFi.h>
const char* server = "api.thingspeak.com";
String apiKey ="5G3QSIJP3HTCSH25";
const char* MY_SSID = "Paradise"; 
const char* MY_PWD = "mukesh9980813506";
int sent = 0;
void setup() 
{
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  double llat,llong;
//Recieve latitude and longitude values through GPS code
  //sendLocation(llat, llong);
  sendLocation(13.113982, 77.634618); //Reva University
  sendLocation(13.124995, 77.620379); //Brindavan College
  sendLocation(13.122134, 77.610543); //Bagalur Cross
  delay(1000);
}

void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

void sendLocation(double llat, double llong)
{  
   WiFiClient client;
   if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
   Serial.println("WiFi Client connected ");
   
   String postStr = apiKey;
   postStr += "&field1=";
   postStr += String(llat);
   postStr += "&field2=";
   postStr += String(llong);
   //postStr += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(1000);
   
   }//end if
   sent++;
 client.stop();
}//end send
