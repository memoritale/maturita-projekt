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

#define NUM_LEDS 3 



// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 26
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setColorAll(int color){  
  for(int ledky = NUM_LEDS - 1; ledky >= 0; ledky--){
    leds[ledky] = color;
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
        request->send(200, "text/html", "Hello, world <a href=/set>Click to set colours</a><br><br>");

    });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/set", HTTP_GET, [] (AsyncWebServerRequest *request) {
        Serial.println("SET:");
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
            Serial.println(message);
        } else {
            message = "No message sent";
        }
        request->send(200, "text/html", "Select required color: " + message + "<br>" + \
         "<a href=/set?message=Red>Red</a><br><br>" + \
         "<a href=/set?message=Green>Green</a><br><br>" + \  
         "<a href=/set?message=Blue>Blue</a><br><br>" + \
         "<a href=/set?message=Amethyst>Amethyst</a><br><br>" + \
         "<a href=/set?message=Aqua>Aqua</a><br><br>" + \
         "<a href=/set?message=Cyan>Cyan</a><br><br>" + \
         "<a href=/set?message=FairyLight>Fairy Light</a><br><br>" + \
         "<a href=/set?message=ForestGreen>Forest Green</a><br><br>" + \
         "<a href=/set?message=Gold>Gold</a><br><br>" + \
         "<a href=/set?message=LawnGreen>Lawn Green</a><br><br>" + \
         "<a href=/set?message=Magenta>Magenta</a><br><br>" + \
         "<a href=/set?message=MidnightBlue>Midnight Blue</a><br><br>" + \
         "<a href=/set?message=Orange>Orange</a><br><br>" + \
         "<a href=/set?message=Purple>Purple</a><br><br>" + \
         "<a href=/set?message=RoyalBlue>Royal Blue</a><br><br>" + \
         "<a href=/set?message=SeaGreen>Sea Green</a><br><br>" + \
         "<a href=/set?message=Violet>Violet</a><br><br>" + \ 
         "<a href=/set?message=White>White</a><br><br>" + \ 
         "<a href=/set?message=Yellow>Yellow</a><br><br>" + \                            
         "<a href=/set?message=Off>Off</a>" 
         );
        
        //http://192.168.0.172

    });

    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(1024);
        doc["brightnes"] = FastLED.getBrightness();
        doc["color"] = barva;

        String odpoved;
        serializeJson(doc, odpoved);

        Serial.println(odpoved);
        
        //request->send(200, "/get", odpoved);
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

// the loop routine runs over and over again forever
void loop() {
 int step=50;

  if(message=="Amethyst")
  {
  setColorAll(0xCE55E0);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Amethyst";
  message="";


  } else if(message=="Aqua")
  {
  setColorAll(0x00FFFF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Aqua";
  message="";

  } else if(message=="Blue")
  {
  setColorAll(0x0000FF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Blue";
  message="";


  } else if(message=="Cyan")
  {
  setColorAll(0x00FFFF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Cyan";
  message="";

  } else if(message=="FairyLight")
  {
  setColorAll(0xFFE42D);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Fairy Light";
  message="";

  } else if(message=="ForestGreen")
  {
  setColorAll(0x113811);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Forest Green";
  message="";

  } else if(message=="Gold")
  {
  setColorAll(0xFFD700);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Gold";
  message="";

  } else if(message=="Green")
  {
  setColorAll(0x00FF00);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Green";
  message="";

  } else if(message=="LawnGreen")
  {
  setColorAll(0x7CFC00);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Lawn Green";
  message="";


  } else if(message=="Magenta")
  {
  setColorAll(0xFF00FF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Magenta";
  message="";

  } else if(message=="MidnightBlue")
  {
  setColorAll(0x191970);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Midnight Blue";
  message="";

  } else if(message=="Orange")
  {
  setColorAll(0xFFA500);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Orange";
  message="";

  } else if(message=="Purple")
  {
  setColorAll(0x490b54);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Purple";
  message="";

  } else if(message=="Red")
  {
  setColorAll(0xFF0000);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Red";
  message="";

  } else if(message=="RoyalBlue")
  {
  setColorAll(0x4169E1);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Royal Blue";
  message="";

  } else if(message=="SeaGreen")
  {
  setColorAll(0x2E8B57);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Sea Green";
  message="";

  } else if(message=="Violet")
  {
  setColorAll(0xEE82EE);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Violet";
  message="";

  } else if(message=="White")
  {
  setColorAll(0xFFFFFF);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "White";
  message="";

  } else if(message=="Yellow")
  {
  setColorAll(0xFFFF00);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Yellow";
  message="";

  } else if(message=="Off")
  {
  setColorAll(0x000000);
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Off";
  message="";

  } else if(message=="p")
  {
   message="";
  }
  
  delay(100);
  
  }




