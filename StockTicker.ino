#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID = "********"
#define STAPSK  "********"
#endif

//Blake Stewart. November 7 2020. Code inspired from various working examples made in previous years.

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "finnhub.io"; //Finnhub API
const int httpsPort = 443; //HTTPS

const char fingerprint[] PROGMEM = "2b34ad3f518da85ad553a35d481385c4a1a26043"; //Works November 7, 2020

String bitsToShift[] = {"11111111", "11111111", "11111111", "11111111"}; //clear

String key = "abcdefghijklmnopqrstuvwxyz0123456789";
String bits[] = {"00000101", "00110001", "10010011", "01100001", "00010011", "00010111", "00001001", "00100101", "11110111", "11101001", "00010101"
                 , "10110011", "01010101", "10000101", "10000001", "00000111", "00001101", "10000111", "00011001", "00110011", "10100001", "00101111", "10101011"
                 , "00111101", "00101001", "01000011", "10000001", "11101101", "01000011", "01001001", "00101101", "00011001", "00010001", "11001101", "00000001", "00001101"
                };

String response;
String price = "";

long lastupdatems;
boolean justUpdated = false;

void setup()
{

  Serial.begin(115200);


  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(12, HIGH);

  for (int i = 0; i < 8; i++) {
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    delay(1);
    digitalWrite(2, HIGH);
    delay(1);
    digitalWrite(0, LOW); digitalWrite(1, LOW); digitalWrite(2, LOW);
    delayMicroseconds(100);
  }

  display("LOAD");
  ledDisplay();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Connecting....");
  }

  Serial.println("Connected");
  lastupdatems = -1;
}



void updatePrices() {
  DynamicJsonDocument doc(1024);
  String input = response;
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();
  price = obj["c"].as<String>();
  display("TSLA");
  justUpdated = true;
  //Serial.println("updated");
}

void loop()
{
  ledDisplay();
  if(millis() - lastupdatems > 3000 && justUpdated){
    
    justUpdated = false;
    display(price);
    //Serial.println("dispaly price"+price);
  }

  if (millis() - lastupdatems > 60 * 1000 || lastupdatems == -1) {
    lastupdatems = millis();
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
                                                                                                   

      WiFiClientSecure client;
 // Serial.print("connecting to ");
 // Serial.println(host);

 // Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) { 
                                                                                                  
    return;
  }

  String url = "/api/v1/quote?symbol=TSLA&token=[TOKEN]"; // [TOKEN] you can get from Finnhub.io 
  Serial.print("requesting URL: ");
  //Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
                                                                                                      
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      //Serial.println("headers received");
      break;
    }
  }
  //Serial.println("NA");
  client.setTimeout(100);
  while(client.available() > 0){Serial.println("A!");
  String line = client.readStringUntil('\n');
  /*Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");*/
  response=line;
  updatePrices();
  }
    
      display("TSLA");
    }
  }
}


void display(String text) {
  for (int i = 0; i < 4; i++) {
    bitsToShift[i] = "11111111";
  }
  int leds = 0;
  for (int index = 0; index <= text.length(); index++) {
    //for .
    //Serial.println(text[index]);

    if (text[index] == '.') {
      //Serial.println("Found . index: " + String(index));
      if (index == 0) {
        bitsToShift[leds] = "11111110";
        leds++;
        continue;
      } else {
        bitsToShift[leds - 1][7] = '0';
        continue;
      }
    }
    if (leds > 3) {
      break;
    }
    bitsToShift[leds] = bits[key.indexOf(tolower(text[index]))];
    leds++;
  }
}

void ledDisplay() {
  for (int i = 0; i < 5; i++) {
    if (i < 4) {
      digitalWrite(13, LOW);
      digitalWrite(14, LOW);
      digitalWrite(15, LOW);
      digitalWrite(16, LOW);
      shiftRegister(bitsToShift[i]);
      digitalWrite(i + 13, HIGH);

      //Serial.println(bitsToShift[i]);
      delayMicroseconds(100);
    } else {
      digitalWrite(16, LOW);
    }
  }
  //Serial.println(" ");
}

void shiftRegister(String bitsshift) {
  digitalWrite(4, LOW);
  for (int i = 0; i < 8; i++) {
    if (bitsshift.charAt(7 - i) == '0') {
      digitalWrite(0, LOW);
    } else {
      digitalWrite(0, HIGH);
    }
    digitalWrite(2, HIGH);

    digitalWrite(2, LOW);
  }
  digitalWrite(4, HIGH);
}
