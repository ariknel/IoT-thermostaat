///blynk user 13

#define BLYNK_TEMPLATE_ID   "---"
#define BLYNK_TEMPLATE_NAME "---"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
unsigned long previousMillis = 0;
const long interval = 1000; //interval voor updates van analog input
char auth[] = "---";
char ssid[] = "---";
char pass[] = "---";
int pin = 33; // led pin -> in circuit, could change to relay or mosfet to turn on heating element
float sensorValue;
float mappedLM35;
float voltageOut;
int ingestelde_temp_ketel = 0;
void setup() {
  pinMode(pin, INPUT);
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Blynk.begin(auth, ssid, pass, "---t", ---);

#define BLYNK_TEMPLATE_ID   "---"
#define BLYNK_TEMPLATE_NAME "---"
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  
    sensorValue = analogRead(pin);
    voltageOut = (sensorValue * 5000) / 1024;
    mappedLM35 = voltageOut / 10;
    Serial.print(mappedLM35);
  }
  Blynk.run();
  ///
  Blynk.virtualWrite(V19, mappedLM35); 
}

/////ontvangen parameters van blynk (slider - genoemd naar range)

BLYNK_WRITE(V0) //v0 -> range -> gestuurd naar gauge in blynk
{   
  int ingestelde_temp_ketel = param.asInt(); // Get value as integer
  Serial.println(ingestelde_temp_ketel);
}
