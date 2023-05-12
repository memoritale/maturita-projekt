#include <M5StickCPlus.h>
#include <WiFiMulti.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <ArduinoJson.h>
#include <string.h>
#include <pixeltypes.h>




//library doc: https://platformio.org/lib/show/6758/ESPAsyncWebServer-esphome


// Set the name and password of the wifi to be connected.  
const char *ssid = "ssid";
const char *password = "password";

#define NUM_LEDS 35
#define LED_PIN  6 



// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 26
#define CLOCK_PIN 13


// Define the array of leds
CRGB leds[NUM_LEDS];


unsigned long ledStartTime = 0;

void setColourAll(int colour){  
  for(int ledky = NUM_LEDS - 1; ledky >= 0; ledky--){
    leds[ledky] = colour;
  }
}





WiFiMulti WiFiMulti;


AsyncWebServer server(80);
const char* PARAM_MESSAGE = "message";
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


String message;
String localIP;
String barva;





// the setup routine runs once when M5StickC starts up
void setup(){ 
   
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  ledStartTime = millis();




  // Initialize the M5StickC object
  M5.begin();
  
    M5.Lcd.setRotation(1);
    M5.Lcd.printf("\n");


   int sum=0;
  WiFiMulti.addAP(ssid, password);  
  M5.lcd.printf("Waiting connect to WiFi: %s \n",ssid); 
  while(WiFiMulti.run() != WL_CONNECTED) { 
    M5.lcd.print(".");
    delay(1000);
    sum+=1;
    if(sum==10) M5.lcd.print("Conncet failed!");
  }
  M5.lcd.println("\nWiFi connected");

    
    
        IPAddress ipAddress = WiFi.localIP();
        String localIP = String(ipAddress[0]) + String(".") +\
        String(ipAddress[1]) + String(".") +\
        String(ipAddress[2]) + String(".") +\
        String(ipAddress[3]); 

            //převod string na char
            int str_len = localIP.length() + 1;
            char char_localIP[str_len];
            localIP.toCharArray(char_localIP, str_len);

            char destination[] = "http://";
            //char source[] = char_localIP;
            printf("Concatenated String: %s\n",  strcat(destination,char_localIP));

        Serial.print("IP Address: ");
        Serial.println(localIP);
        M5.lcd.qrcode(destination,70,30,110,7);
        M5.lcd.println(localIP);
        delay(500);

  
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<a href=/set>Click to set colours</a><br><br>");

    });

    // Send a SET request to <IP>/set?message=<message>
    server.on("/set", HTTP_GET, [] (AsyncWebServerRequest *request) {
        Serial.println("SET:");
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
            Serial.println(message);
        } else {
            message = "No message sent";

             int r = 0, g = 0, b = 0, brightness = 0;
        if (request->hasParam("red")) {
          r = request->getParam("red")->value().toInt();
          // Set red value
        }

        if (request->hasParam("green")) {
          g = request->getParam("green")->value().toInt();
          // Set green value
        }

        if (request->hasParam("blue")) {
          b = request->getParam("blue")->value().toInt();
          // Set blue value
        }

        if (request->hasParam("brightness")) {
          brightness = request->getParam("brightness")->value().toInt();
          // Set brightness value
        }

  // Set color and brightness
  FastLED.setBrightness(brightness);
  fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
  FastLED.show();


        }
        request->send(200, 
        "text/html",

         "Select colour: " + message + "<br>" + \
         "<!DOCTYPE html>" + \
          "<html>" + \
          "<head>" + \
          "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" + \
          "<style>" + \

          "</style>" + \
          "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD\" crossorigin=\"anonymous\">" + \
          "</head>" + \
          "<body>" + \
            "<div class=\"container-fluid\">" + \
              "<form>" + \
                "<label for=\"RED\" class=\"form-label\">Red</label>" + \
                "<input type=\"range\" class=\"form-range\" min=\"0\" max=\"255\" id=\"RED\" name=\"red\">" + \

                "<label for=\"GREEN\" class=\"form-label\">Green</label>" + \
                "<input type=\"range\" class=\"form-range\" min=\"0\" max=\"255\" id=\"GREEN\" name=\"green\">" + \

                "<label for=\"BLUE\" class=\"form-label\">Blue</label>" + \
                "<input type=\"range\" class=\"form-range\" min=\"0\" max=\"255\" id=\"BLUE\" name=\"blue\">" + \

                "<label for=\"BRIGHTNESS\" class=\"form-label\">Brightness</label>" + \
                "<input type=\"range\" class=\"form-range\" min=\"0\" max=\"255\" id=\"BRIGHTNESS\" name=\"brightness\">" +\

                "<button type=\"submit\" class=\"btn btn-primary\">Submit</button>" + \
              "</form>" + \
            "</div>" + \
          "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN\" crossorigin=\"anonymous\"></script>" + \
          "</body>" + \
          "</html>"
         
        );
        
      if (request->hasParam("red")) {
        int r = request->getParam("red")->value().toInt();
        // Set red value
      }

      if (request->hasParam("green")) {
        int g = request->getParam("green")->value().toInt();
        // Set green value
      }

      if (request->hasParam("blue")) {
        int b = request->getParam("blue")->value().toInt();
        // Set blue value
      }

      if (request->hasParam("brightness")) {
        int brightness = request->getParam("brightness")->value().toInt();
        // Set brightness value
      }
                
            });
        
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(1024);
        doc["brightness"] = FastLED.getBrightness();
        doc["colour"] = barva;
        //doc["timer"] = timer;

        String odpoved;
        serializeJson(doc, odpoved);

        Serial.println(odpoved);
        
        request->send(200, "serializeJson", odpoved);

    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();


    

}




void loop(){
 int step=50;
 //...
  unsigned long elapsedTime = millis() - ledStartTime;
  if (elapsedTime >= 60000) { // 5 seconds have elapsed
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Turn off LED stripe
    FastLED.show();
  }
  //...



 delay(100);
}


