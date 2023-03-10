#include <M5StickCPlus.h>
#include <WiFiMulti.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <ArduinoJson.h>
#include <string.h>
#include <pixeltypes.h>




//library doc: https://platformio.org/lib/show/6758/ESPAsyncWebServer-esphome


// Set the name and password of the wifi to be connected.  
const char *ssid = " ";
const char *password = " ";

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

  unsigned long startTime;
  const unsigned long TIME = 10000; // in milliseconds

  startTime = millis(); // start the timer
  

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
        }
        request->send(200, "text/html", "Select colour: " + message + "<br>" + \
         "<a href=/set?message=Red>Red</a><br><br>" + \
         "<a href=/set?message=Green>Green</a><br><br>" + \
         "<a href=/set?message=Blue>Blue</a><br><br>" + \
         "<a href=/set?message=Amethyst>Amethyst</a><br><br>" + \
         "<a href=/set?message=Cyan>Cyan</a><br><br>" + \      
         "<a href=/set?message=FairyLight>Fairy Light</a><br><br>" + \
         "<a href=/set?message=ForestGreen>Forest Green</a><br><br>" + \ 
         "<a href=/set?message=Gold>Gold</a><br><br>" +  \                  
         "<a href=/set?message=Magenta>Magenta</a><br><br>" + \                                           
         "<a href=/set?message=Orange>Orange</a><br><br>" + \
         "<a href=/set?message=Purple>Purple</a><br><br>" + \                  
         "<a href=/set?message=RoyalBlue>Royal Blue</a><br><br>" + \         
         "<a href=/set?message=Violet>Violet</a><br><br>" + \          
         "<a href=/set?message=White>White</a><br><br>" + \ 
         "<a href=/set?message=Yellow>Yellow</a><br><br>" + \
         "<a href=/set?message=Off>Off</a>" 
         
        );
        
        
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


  // Příjem hodnoty jasu přes sériovou komunikaci
  if (Serial.available() > 0) {
    int brightness = Serial.parseInt();

    // Aktualizace hodnoty jasu LED pásky
    FastLED.setBrightness(brightness);
    FastLED.show();

  }
}



void loop() {

  unsigned long elapsedTime = millis();
  const unsigned long ON_TIME = 300000; // in milliseconds

  
  if (elapsedTime < ON_TIME) {
    // turn on the LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = (0, 255, 0);  
    }

    FastLED.show();
  }
  else {
    // turn off the LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

    
 int step=50;



 if(message=="Amethyst")
  {
  setColourAll(0xCE55E0);
  FastLED.setBrightness(10);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Amethyst";
  message="";
 
  } else if(message=="Blue")
  {
  setColourAll(0x0000FF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Blue";
  message="";


  } else if(message=="Cyan")
  {
  setColourAll(0x00FFFF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Cyan";
  message="";

  } else if(message=="FairyLight")
  {
  setColourAll(0xFFE42D);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Fairy Light";
  message="";
 
  } else if(message=="ForestGreen")
  {
  setColourAll(0x113811);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Forest Green";
  message="";

  } else if(message=="Gold")
  {
  setColourAll(0xFFC108);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Gold";
  message="";

  } else if(message=="Green")
  {
  setColourAll(0x00FF00);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Green";
  message="";

  } else if(message=="Magenta")
  {
  setColourAll(0xFF00FF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Magenta";
  message="";

  } else if(message=="Orange")
  {
  setColourAll(0xFF8708);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Orange";
  message="";

  } else if(message=="Purple")
  {
  setColourAll(0x490b54);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Purple";
  message="";

  } else if(message=="Red")
  {
  setColourAll(0xFF0000);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Red";
  message="";

  } else if(message=="RoyalBlue")
  {
  setColourAll(0x4169E1);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Royal Blue";
  message="";

  } else if(message=="Violet")
  {
  setColourAll(0xEE82EE);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Violet";
  message="";

  } else if(message=="White")
  {
  setColourAll(0xFFFFFF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "White";
  message="";

  } else if(message=="Yellow")
  {
  setColourAll(0xFFFF00);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Yellow";
  message="";

  } else if(message=="Off")
  {
  setColourAll(0x000000);
  FastLED.show();
  barva = "Off";
  message="";

  } else if(message=="p")
  {
   message="";
  }
  
 
 delay(100);
  
}

