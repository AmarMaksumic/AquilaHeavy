#include <Arduino.h>
#include <sd.hpp>
#include <cam.hpp>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

const int bme_pin = 8;
const int card_pin = 9;
const int cam_pin = 10;
const int led_pin = 13;
Adafruit_BME280 bme(8);
int i = 0;

void blink(int num) {
  for (int i = 0; i < num; i++) {
    digitalWrite(led_pin, HIGH);
    delay(200);
    digitalWrite(led_pin, LOW);
    delay(200);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  blink(3);
  bool card_stat = initialize_card(card_pin);
  if(card_stat) {
    Serial.println("SD Card is mounted!");
    digitalWrite(led_pin, HIGH);
    delay(1000);
  } else {
    Serial.println("SD Card is not mounted...");
  }
  Serial.println(card_type());
  Serial.println(write_file(card_pin, "test.txt", "test message!"));
  Serial.println(read_file(card_pin, "test.txt"));
  int cam_stat = initialize_cam();
  bool sensor_stat = bme.begin();
  Serial.println(cam_stat);
  Serial.println(sensor_stat);
  blink(3);
  if(sensor_stat == 1) {
    digitalWrite(led_pin, HIGH);
  }
}

void loop() {  
  myCAMSaveToSDFile();  
  
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure();
  float humidity = bme.readHumidity();
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  digitalWrite(bme_pin, LOW);  

  Serial.print("temperature:");
  Serial.print(temperature);
  Serial.print("*C   ");

  Serial.print("pressure:");
  Serial.print(pressure);
  Serial.print("hPa   ");

  Serial.print("humidity:");
  Serial.print(humidity);
  Serial.print("%   ");

  Serial.print("altitude:");
  Serial.print(altitude);
  Serial.println("m");

  String results = "Temperature: " + String(temperature) + "*C\n" + 
                    "Pressure: " + String(pressure) + "hPa\n" + 
                    "Humidity: " + String(humidity) + "%\n" + 
                    "Altitude: " + String(altitude) + "m";

  Serial.println(results);

  digitalWrite(card_pin, HIGH); 
  Serial.println(write_file(card_pin, "sensor_dat.txt", results));
  digitalWrite(card_pin, LOW); 

  i++;
}