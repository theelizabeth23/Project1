#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTTYPE DHT22   // DHT 22 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const int DHTPin = 2;
DHT dht(DHTPin, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

}

void loop() {
  dht.begin();
  delay(500);
    float h = dht.readHumidity();
  float t = dht.readTemperature();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  delay(1000);
  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);
  display.setCursor(0,10); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  display.print("Humidity: ");
  display.print(h);
  display.println("%");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("Temperature: ");
  display.print(t);
  display.println((" C "));
  display.display();

  if (isnan(h) || isnan(t)) {
    display.println(F("Failed to read from DHT sensor!"));
    return;
  }
}
