#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Android";
const char* psk  = "vismaya123";
String IPV4 = "192.168.43.183";

#define LDRPIN1 32 // Pin for the first LDR sensor
#define LDRPIN2 33 // Pin for the second LDR sensor
#define LDRPIN3 34 // Pin for the second LDR sensor


const int numLeds = 5;  // Number of LEDs
int ledPins[numLeds] = {15, 4, 5, 19, 23};  // Pin numbers where the LEDs are connected
int delayTime = 300;  // Delay time in milliseconds
int val1, val2, val3;
int s,r,t;

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 bps

  // Set the LED pins as outputs
  for (int i = 0; i < numLeds; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }

 /*WiFi.begin(ssid, psk);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print (".");
    delay(100);
  }
  delay(5000);*/
}

void loop() { 
  char receivedChar = Serial.read();  // Read the incoming character from serial
    s=0;
    r=0;
    val3 = analogRead(LDRPIN3);
    Serial.println("sunlight status: ");
    Serial.print(val3);
    
    if(val3<2000)
  {
    if (Serial.available() > 0) {
      {
    
        if (receivedChar == 'A') {
          for (int i = 0; i < numLeds; ++i) {
            digitalWrite(ledPins[i], HIGH); // Turn on the LED
           // delay(delayTime);

            // Read LDR values for both sensors
            val1 = analogRead(LDRPIN1);
            val2 = analogRead(LDRPIN2);
          

            
            
          }

          // Print LDR values for debugging
            
          
            Serial.print("LDR1: ");
            Serial.print(val1);
            Serial.print(" LDR2: ");
            Serial.println(val2);
            
            // Check if any of the LDR readings indicate failure
            if (val1 > 800) {
              Serial.println("LED 1 is failed");
              s=1;
            }
            if(val2 > 1500) {
              Serial.println("LED 2 is failed");
              r=1;
            }
          
          /*WiFiClient client;
          HTTPClient http;

          String url = "http://" + IPV4 + ":80/project/streetlight.php/?s1=" + String (s) + "&s2=" + String (r);
          Serial.print("Sending data: ");
          Serial.println(url);

          http.begin(client, url);
          int httpCode = http.GET();
          if (httpCode == HTTP_CODE_OK) {
            String response = http.getString();
            Serial.println("Server response: " + response);
          } 
          else {
            Serial.print("HTTP GET request failed with error code: ");
            Serial.println(httpCode);
            if (httpCode == HTTPC_ERROR_CONNECTION_REFUSED) {
              Serial.println("Connection refused by the server.");
            }
            else if (httpCode == HTTP_CODE_NOT_FOUND) {
              Serial.println("Server resource not found.");
            }
            else {
              Serial.println("Unknown error occurred.");
            }
          }
          http.end();*/

          delay (2000);



              Serial.println("All LEDs ON");
        }  
     
      
    
     else if (receivedChar == 'B') {
      // Turn all LEDs off
      for (int i = 0; i < numLeds; ++i) {
        digitalWrite(ledPins[i], LOW);
       // delay(delayTime);
      }
      Serial.println("All LEDs OFF");
    }

    }
  }

 }
 else if (receivedChar == 'B') {
      // Turn all LEDs off
      for (int i = 0; i < numLeds; ++i) {
        digitalWrite(ledPins[i], LOW);
       // delay(delayTime);
      }
      Serial.println("All LEDs OFF");
 
 }
}


