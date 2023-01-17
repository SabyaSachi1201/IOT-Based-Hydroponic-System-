#define BLYNK_TEMPLATE_ID "TMPLfentMQBJ"
#define BLYNK_DEVICE_NAME "DHT11TEMPHUMDITYMONITORING"
#define BLYNK_AUTH_TOKEN "fv-L-JG1GED7Sn8H_lJ0Iu_PZty_tplG"
#define level_sensor 36
#define pump_control 19
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
int value;
char auth[] = "fv-L-JG1GED7Sn8H_lJ0Iu_PZty_tplG";
char ssid[] = "NetworkSSID";
char pass[] = "PASSWORD";
#define DHTPIN 21          // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()

{

  float h = dht.readHumidity();

  float t = dht.readTemperature(); 
  value=analogRead(level_sensor);
  Serial.println(value);
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, value);
  if(value<2000)
  {
    digitalWrite(19,LOW);
  }
  else
  {
    digitalWrite(19,HIGH);
    delay(20000);
  }


  if (isnan(h) || isnan(t)) {

    Serial.println("Failed to read from DHT sensor!");

    return;

  }
}

void setup()

{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   pinMode(19,OUTPUT); //PIN 19 IS CONFIGURED AS AN OUTPUT FOR THE PUMP;
  pinMode(36,INPUT); //THE PIN 36 IS CONFIGURED AS AN INPUT PIN FOR THE ESP32  
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
void loop()

{
  Blynk.run();
  timer.run();
}
