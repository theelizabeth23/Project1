/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLMGnhn9TB"
#define BLYNK_DEVICE_NAME "SmartFarm"
#define BLYNK_AUTH_TOKEN "psUPx4sWrWBUKFOMAmKnNxBzP6qYAMma"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <DHT.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Smjnk2u_0.13";
char pass[] = "19082560";
#define DHTPIN 2 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Blynk.virtualWrite(V1, value);
}
BLYNK_CONNECTED()
{
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V4, h); // เรียกให้  V5 แสดงค่าจากตัวแปร h บน Blynk
  Blynk.virtualWrite(V5, t); // เรียกให้  V6 แสดงค่าจากตัวแปร t บน Blynk
}
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
    dht.begin();
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

}
