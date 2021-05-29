
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "##################";
char ssid[] = "###########";
char pass[] = "############";
const float airval = 3450.0;
const float waterval = 1540.0;

int moistureSensor1 = 32;
int moistureSensor2 = 35;
int rawSval1; //idk
int rawSval2;
float moistureSval1;
float moistureSval2;
float moistureavg;
BlynkTimer timer;

void readdata()
{
  rawSval1 = analogRead(moistureSensor1);   // edit it here
  rawSval2 = analogRead(moistureSensor2);
  moistureSval1=map(rawSval1, airval, waterval, 0, 100);
  moistureSval2=map(rawSval2, airval, waterval, 0, 100);
  moistureavg = map(moistureSval1 + moistureSval2 )/2;

  Serial.println(rawSval1);
  Serial.println(rawSval2);
  Serial.println(moistureSval1);
  Serial.println(moistureSval2);
  Serial.println(moistureavg);
  Blynk.virtualWrite(V1, moistureSval1);
  Blynk.virtualWrite(V2, moistureSval2);
  Blynk.virtualWrite(V2, moistureavg);
}

void setup()
{

  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass, "vxjblynk.duckdns.org", 8081);   //change the server if you want
  timer.setInterval(1000L, readdata); //push data every 1 sec
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
