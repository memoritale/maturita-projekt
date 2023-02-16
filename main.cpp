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
         "<a href=/set?message=AliceBlue>AliceBlue</a><br><br>" + \
         "<a href=/set?message=Amethyst>Amethyst</a><br><br>" + \
         "<a href=/set?message=AntiqueWhite>AntiqueWhite</a><br><br>" + \
         "<a href=/set?message=Aqua>Aqua</a><br><br>" + \
         "<a href=/set?message=Aquamarine>Aquamarine</a><br><br>" + \
         "<a href=/set?message=Azure>Azure</a><br><br>" + \
         "<a href=/set?message=Beige>Beige</a><br><br>" + \
         "<a href=/set?message=Bisque>Bisque</a><br><br>" + \
         "<a href=/set?message=BlanchedAlmond>BlanchedAlmond</a><br><br>" + \
         "<a href=/set?message=Blue>Blue</a><br><br>" + \
         "<a href=/set?message=BlueViolet>BlueViolet</a><br><br>" + \
         "<a href=/set?message=Brown>Brown</a><br><br>" + \
         "<a href=/set?message=BurlyWood>BurlyWood</a><br><br>" + \
         "<a href=/set?message=CadetBlue>CadetBlue</a><br><br>" + \
         "<a href=/set?message=Chartreuse>Chartreuse</a><br><br>" + \
         "<a href=/set?message=Chocolate>Chocolate</a><br><br>" + \
         "<a href=/set?message=Coral>Coral</a><br><br>" + \
         "<a href=/set?message=CornflowerBlue>CornflowerBlue</a><br><br>" + \
         "<a href=/set?message=Cornsilk>Cornsilk</a><br><br>" + \
         "<a href=/set?message=Crimson>Crimson</a><br><br>" + \
         "<a href=/set?message=Cyan>Cyan</a><br><br>" + \
         "<a href=/set?message=DarkBlue>DarkBlue</a><br><br>" + \
         "<a href=/set?message=DarkCyan>DarkCyan</a><br><br>" + \
         "<a href=/set?message=DarkGoldenrod>DarkGoldenrod</a><br><br>" + \
         "<a href=/set?message=DarkGray>DarkGray</a><br><br>" + \
         "<a href=/set?message=DarkGreen>DarkGreen</a><br><br>" + \
         "<a href=/set?message=DarkKhaki>DarkKhaki</a><br><br>" + \
         "<a href=/set?message=DarkMagenta>DarkMagenta</a><br><br>" + \
         "<a href=/set?message=DarkOliveGreen>DarkOliveGreen</a><br><br>" + \
         "<a href=/set?message=DarkOrange>DarkOrange</a><br><br>" + \
         "<a href=/set?message=DarkOrchid>DarkOrchid</a><br><br>" + \
         "<a href=/set?message=DarkRed>DarkRed</a><br><br>" + \
         "<a href=/set?message=DarkSalmon>DarkSalmon</a><br><br>" + \
         "<a href=/set?message=DarkSeaGreen>DarkSeaGreen</a><br><br>" + \
         "<a href=/set?message=DarkSlateBlue>DarkSlateBlue</a><br><br>" + \
         "<a href=/set?message=DarkSlateGrey>DarkSlateGrey</a><br><br>" + \ 
         "<a href=/set?message=DarkTurquoise>DarkTurquoise</a><br><br>" + \
         "<a href=/set?message=DarkViolet>DarkViolet</a><br><br>" + \
         "<a href=/set?message=DeepPink>DeepPink</a><br><br>" + \
         "<a href=/set?message=DeepSkyBlue>DeepSkyBlue</a><br><br>" + \
         "<a href=/set?message=DimGrey>DimGrey</a><br><br>" + \
         "<a href=/set?message=DodgerBlue>DodgerBlue</a><br><br>" + \
         "<a href=/set?message=FairyLight>FairyLight</a><br><br>" + \
         "<a href=/set?message=FireBrick>FireBrick</a><br><br>" + \
         "<a href=/set?message=FloralWhite>FloralWhite</a><br><br>" + \
         "<a href=/set?message=ForestGreen>ForestGreen</a><br><br>" + \
         "<a href=/set?message=Fuchsia>Fuchsia</a><br><br>" + \
         "<a href=/set?message=Gainsboro>Gainsboro</a><br><br>" + \ 
         "<a href=/set?message=GhostWhite>GhostWhite</a><br><br>" + \
         "<a href=/set?message=Gold>Gold</a><br><br>" + \
         "<a href=/set?message=Goldenrod>Goldenrod</a><br><br>" + \
         "<a href=/set?message=Grey>Grey</a><br><br>" + \
         "<a href=/set?message=Green>Green</a><br><br>" + \
         "<a href=/set?message=GreenYellow>GreenYellow</a><br><br>" + \  
         "<a href=/set?message=Honeydew>Honeydew</a><br><br>" + \
         "<a href=/set?message=HotPink>HotPink</a><br><br>" + \ 
         "<a href=/set?message=IndianRed>IndianRed</a><br><br>" + \
         "<a href=/set?message=Indigo>Indigo</a><br><br>" + \
         "<a href=/set?message=Ivory>Ivory</a><br><br>" + \
         "<a href=/set?message=Khaki>Khaki</a><br><br>" + \
         "<a href=/set?message=Lavender>Lavender</a><br><br>" + \
         "<a href=/set?message=LavenderBlush>LavenderBlush</a><br><br>" + \ 
         "<a href=/set?message=LawnGreen>LawnGreen</a><br><br>" + \
         "<a href=/set?message=LemonChiffon>LemonChiffon</a><br><br>" + \
         "<a href=/set?message=LightBlue>LightBlue</a><br><br>" + \
         "<a href=/set?message=LightCoral>LightCoral</a><br><br>" + \
         "<a href=/set?message=LightCyan>LightCyan</a><br><br>" + \
         "<a href=/set?message=LightGoldenrodYellow>LightGoldenrodYellow</a><br><br>" + \ 
         "<a href=/set?message=LightGreen>LightGreen</a><br><br>" + \
         "<a href=/set?message=LightGrey>LightGrey</a><br><br>" + \ 
         "<a href=/set?message=LightPink>LightPink</a><br><br>" + \
         "<a href=/set?message=LightSalmon>LightSalmon</a><br><br>" + \
         "<a href=/set?message=LightSeaGreen>LightSeaGreen</a><br><br>" + \
         "<a href=/set?message=LightSkyBlue>LightSkyBlue</a><br><br>" + \
         "<a href=/set?message=LightSlateGrey>LightSlateGrey</a><br><br>" + \
         "<a href=/set?message=LightSteelBlue>LightSteelBlue</a><br><br>" + \ 
         "<a href=/set?message=LightYellow>LightYellow</a><br><br>" + \
         "<a href=/set?message=Lime>Lime</a><br><br>" + \
         "<a href=/set?message=LimeGreen>LimeGreen</a><br><br>" + \
         "<a href=/set?message=Linen>Linen</a><br><br>" + \
         "<a href=/set?message=Magenta>Magenta</a><br><br>" + \
         "<a href=/set?message=Maroon>Maroon</a><br><br>" + \ 
         "<a href=/set?message=MediumAquamarine>MediumAquamarine</a><br><br>" + \
         "<a href=/set?message=MediumBlue>MediumBlue</a><br><br>" + \
         "<a href=/set?message=MediumOrchid>MediumOrchid</a><br><br>" + \
         "<a href=/set?message=MediumSeaGreen>MediumSeaGreen</a><br><br>" + \
         "<a href=/set?message=MediumSlateBlue>MediumSlateBlue</a><br><br>" + \
         "<a href=/set?message=MediumSpringGreen>MediumSpringGreen</a><br><br>" + \ 
         "<a href=/set?message=MediumTurquoise>MediumTurquoise</a><br><br>" + \
         "<a href=/set?message=MediumVioletRed>MediumVioletRed</a><br><br>" + \ 
         "<a href=/set?message=MidnightBlue>MidnightBlue</a><br><br>" + \
         "<a href=/set?message=MintCream>MintCream</a><br><br>" + \
         "<a href=/set?message=MistyRose>MistyRose</a><br><br>" + \
         "<a href=/set?message=Moccasin>Moccasin</a><br><br>" + \
         "<a href=/set?message=NavajoWhite>NavajoWhite</a><br><br>" + \
         "<a href=/set?message=Navy>Navy</a><br><br>" + \ 
         "<a href=/set?message=OldLace>OldLace</a><br><br>" + \
         "<a href=/set?message=Olive>Olive</a><br><br>" + \
         "<a href=/set?message=OliveDrab>OliveDrab</a><br><br>" + \
         "<a href=/set?message=Orange>Orange</a><br><br>" + \
         "<a href=/set?message=OrangeRed>OrangeRed</a><br><br>" + \
         "<a href=/set?message=Orchid>Orchid</a><br><br>" + \ 
         "<a href=/set?message=PaleGoldenrod>PaleGoldenrod</a><br><br>" + \
         "<a href=/set?message=PaleGreen>PaleGreen</a><br><br>" + \
         "<a href=/set?message=PaleTurquoise>PaleTurquoise</a><br><br>" + \
         "<a href=/set?message=PaleVioletRed>PaleVioletRed</a><br><br>" + \ 
         "<a href=/set?message=Plaid>Plaid</a><br><br>" + \
         "<a href=/set?message=Plum>Plum</a><br><br>" + \
         "<a href=/set?message=PowderBlue>PowderBlue</a><br><br>" + \
         "<a href=/set?message=Purple>Purple</a><br><br>" + \
         "<a href=/set?message=Red>Red</a><br><br>" + \
         "<a href=/set?message=RosyBrown>RosyBrown</a><br><br>" + \ 
         "<a href=/set?message=RoyalBlue>RoyalBlue</a><br><br>" + \
         "<a href=/set?message=SaddleBrown>SaddleBrown</a><br><br>" + \
         "<a href=/set?message=Salmon>Salmon</a><br><br>" + \
         "<a href=/set?message=SandyBrown>SandyBrown</a><br><br>" + \
         "<a href=/set?message=SeaGreen>SeaGreen</a><br><br>" + \
         "<a href=/set?message=Seashell>Seashell</a><br><br>" + \ 
         "<a href=/set?message=Sienna>Sienna</a><br><br>" + \
         "<a href=/set?message=Silver>Silver</a><br><br>" + \ 
         "<a href=/set?message=SkyBlue>SkyBlue</a><br><br>" + \
         "<a href=/set?message=SlateBlue>SlateBlue</a><br><br>" + \
         "<a href=/set?message=SlateGrey>SlateGrey</a><br><br>" + \
         "<a href=/set?message=Snow>Snow</a><br><br>" + \
         "<a href=/set?message=SpringGreen>SpringGreen</a><br><br>" + \
         "<a href=/set?message=SteelBlue>SteelBlue</a><br><br>" + \ 
         "<a href=/set?message=Tan>Tan</a><br><br>" + \
         "<a href=/set?message=Teal>Teal</a><br><br>" + \
         "<a href=/set?message=Thistle>Thistle</a><br><br>" + \
         "<a href=/set?message=Tomato>Tomato</a><br><br>" + \
         "<a href=/set?message=Turquoise>Turquoise</a><br><br>" + \
         "<a href=/set?message=Violet>Violet</a><br><br>" + \ 
         "<a href=/set?message=Wheat>Wheat</a><br><br>" + \
         "<a href=/set?message=White>White</a><br><br>" + \ 
         "<a href=/set?message=WhiteSmoke>WhiteSmoke</a><br><br>" + \
         "<a href=/set?message=Yellow>Yellow</a><br><br>" + \
         "<a href=/set?message=YellowGreen>YellowGreen</a><br><br>" + \                               
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
        
        //request->send(200, "", odpoved);
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

 if(message=="AliceBlue")
  {
  leds[2]  = 0xF0F8FF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "AliceBlue";
  message="";


  } else if(message=="Amethyst")
  {
  leds[2] = 0x9966CC;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Amethyst";
  message="";

  } else if(message=="AntiqueWhite")
  {
  leds[2] = 0xFAEBD7;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "AntiqueWhite";
  message="";

   message="";

  } else if(message=="Aqua")
  {
  leds[2] = 0x00FFFF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Aqua";
  message="";

  } else if(message=="Aquamarine")
  {
  leds[2] = 0x7FFFD4;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Aquamarine";
  message="";

  } else if(message=="Azure")
  {
  leds[2] = 0xF0FFFF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Azure";
  message="";

  } else if(message=="Beige")
  {
  leds[2] = 0xF5F5DC;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Beige";
  message="";
 
  } else if(message=="Bisque")
  {
  leds[2] = 0xFFE4C4;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Bisque";
  message="";

  } else if(message=="BlanchedAlmond")
  {
  leds[2] = 0xFFEBCD;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "BlanchedAlmond";
  message="";

  } else if(message=="Blue")
  {
  leds[2] = 0x0000FF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Blue";
  message="";

  } else if(message=="BlueViolet")
  {
  leds[2] = 0x8A2BE2;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "BlueViolet";
  message="";

  } else if(message=="Brown")
  {
  leds[2] = 0xA52A2A;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Brown";
  message="";

  } else if(message=="BurlyWood")
  {
  leds[2] = 0xDEB887;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "BurlyWood";
  message="";

  } else if(message=="CadetBlue")
  {
  leds[2] = 0x5F9EA0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "CadetBlue";
  message="";

  } else if(message=="Chartreuse")
  {
  leds[2] = 0x7FFF00;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Chartreuse";
  message="";

  } else if(message=="Chocolate")
  {
  leds[2] = 0xD2691E;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Chocolate";
  message="";

  } else if(message=="Coral")
  {
  leds[2] = 0xFF7F50;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Coral";
  message="";

  } else if(message=="CornflowerBlue")
  {
  leds[2] = 0x6495ED;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "CornflowerBlue";
  message="";

  } else if(message=="Cornsilk")
  {
  leds[2] = 0xFFF8DC;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Cornsilk";
  message="";

  } else if(message=="Crimson")
  {
  leds[2] = 0xDC143C;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Crimson";
  message="";

  } else if(message=="Cyan")
  {
  leds[2] = 0x00FFFF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Cyan";
  message="";

  } else if(message=="DarkBlue")
  {
  leds[2] = 0x00008B;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkBlue";
  message="";

  } else if(message=="DarkCyan")
  {
  leds[2] = 0x008B8B;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkCyan";
  message="";

  } else if(message=="DarkGoldenrod")
  {
  leds[2] = 0xB8860B;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkGoldenrod";
  message="";

  } else if(message=="DarkGray")
  {
  leds[2] = 0xA9A9A9;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkGray";
  message="";

  } else if(message=="DarkGreen")
  {
  leds[2] = 0x006400;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkGreen";
  message="";

  } else if(message=="DarkKhaki")
  {
  leds[2] = 0xBDB76B;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkKhaki";
  message="";

  } else if(message=="DarkMagenta")
  {
  leds[2] = 0x8B008B;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkMagenta";
  message="";
  
  } else if(message=="DarkOliveGreen")
  {
  leds[2] = 0x556B2F;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkOliveGreen";
  message="";

  } else if(message=="DarkOrange")
  {
  leds[2] = 0xFF8C00;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkOrange";
  message="";
  
  } else if(message=="DarkOrchid")
  {
  leds[2] = 0x9932CC;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkOrchid";
  message="";

  } else if(message=="DarkRed")
  {
  leds[2] = 0x8B0000;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkRed";
  message="";
  
  } else if(message=="DarkSalmon")
  {
  leds[2] = 0xE9967A;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkSalmon";
  message="";

  } else if(message=="DarkSeaGreen")
  {
  leds[2] = 0x8FBC8F;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkSeaGreen";
  message="";
  
  } else if(message=="DarkSlateBlue")
  {
  leds[2] = 0x483D8B;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkSlateBlue";
  message="";

  } else if(message=="DarkSlateGrey")
  {
  leds[2] = 0x2F4F4F;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkSlateGrey";
  message="";
  
  } else if(message=="DarkTurquoise")
  {
  leds[2] = 0x00CED1;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkTurquoise";
  message="";

  } else if(message=="DarkViolet")
  {
  leds[2] = 0x9400D3;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DarkViolet";
  message="";

  } else if(message=="DeepSkyBlue")
  {
  leds[2] = 0xFF1493;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DeepSkyBlue";
  message="";

  } else if(message=="DeepSkyBlue")
  {
  leds[2] = 0x00BFFF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DeepSkyBlue";
  message="";

  } else if(message=="DimGrey")
  {
  leds[2] = 0x696969;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DimGrey";
  message="";

  } else if(message=="DodgerBlue")
  {
  leds[2] = 0x1E90FF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "DodgerBlue";
  message="";

  } else if(message=="FairyLight")
  {
  leds[2] = 0xFFE42D;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "FairyLight";
  message="";

  } else if(message=="FireBrick")
  {
  leds[2] = 0xB22222;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "FireBrick";
  message="";

  } else if(message=="FloralWhite")
  {
  leds[2] = 0xFFFAF0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "FloralWhite";
  message="";

  } else if(message=="ForestGreen")
  {
  leds[2] = 0x228B22;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "ForestGreen";
  message="";

  } else if(message=="Fuchsia")
  {
  leds[2] = 0xFF00FF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Fuchsia";
  message="";

  } else if(message=="Gainsboro")
  {
  leds[2] = 0xDCDCDC;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Gainsboro";
  message="";

    } else if(message=="GhostWhite")
  {
  leds[2] = 0xF8F8FF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "GhostWhite";
  message="";

  } else if(message=="Gold")
  {
  leds[2] = 0xFFD700;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Gold";
  message="";

  } else if(message=="Goldenrod")
  {
  leds[2] = 0xDAA520;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Goldenrod";
  message="";

    } else if(message=="Grey")
  {
  leds[2] = 0x808080;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Grey";
  message="";

  } else if(message=="Green")
  {
  leds[2] = 0x008000;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Green";
  message="";

  } else if(message=="GreenYellow")
  {
  leds[2] = 0xADFF2F;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "GreenYellow";
  message="";

    } else if(message=="Honeydew")
  {
  leds[2] = 0xF0FFF0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Honeydew";
  message="";

  } else if(message=="HotPink")
  {
  leds[2] = 0xFF69B4;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "HotPink";
  message="";

  } else if(message=="IndianRed")
  {
  leds[2] = 0xCD5C5C;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "IndianRed";
  message="";

    } else if(message=="Indigo")
  {
  leds[2] = 0x4B0082;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Indigo";
  message="";

  } else if(message=="Ivory")
  {
  leds[2] = 0xFFFFF0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Ivory";
  message="";

  } else if(message=="Khaki")
  {
  leds[2] = 0xF0E68C;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Khaki";
  message="";

    } else if(message=="Lavender")
  {
  leds[2] = 0xE6E6FA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Lavender";
  message="";

  } else if(message=="LavenderBlush")
  {
  leds[2] = 0xFFF0F5;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LavenderBlush";
  message="";

  } else if(message=="LawnGreen")
  {
  leds[2] = 0x7CFC00;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LawnGreen";
  message="";

    } else if(message=="LemonChiffon")
  {
  leds[2] = 0xFFFACD;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LemonChiffon";
  message="";

  } else if(message=="LightBlue")
  {
  leds[2] = 0xADD8E6;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightBlue";
  message="";


  } else if(message=="LightCoral")
  {
  leds[2] = 0xF08080;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightCoral";
  message="";

  } else if(message=="LightCyan")
  {
  leds[2] = 0xE0FFFF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Brown";
  message="";


  } else if(message=="LightGoldenrodYellow")
  {
  leds[2] = 0xFAFAD2;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightGoldenrodYellow";
  message="";

  } else if(message=="LightGreen")
  {
  leds[2] = 0x90EE90;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightGreen";
  message="";


  } else if(message=="LightGrey")
  {
  leds[2] = 0xD3D3D3;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightGrey";
  message="";

  } else if(message=="LightPink")
  {
  leds[2] = 0xFFB6C1;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightPink";
  message="";

    } else if(message=="LightSalmon")
  {
  leds[2] = 0xFFA07A;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightSalmon";
  message="";

  } else if(message=="LightSeaGreen")
  {
  leds[2] = 0x20B2AA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightSeaGreen";
  message="";

  } else if(message=="LightSkyBlue")
  {
  leds[2] = 0x87CEFA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightSkyBlue";
  message="";

  } else if(message=="LightSlateGrey")
  {
  leds[2] = 0x778899;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightSlateGrey";
  message="";

  } else if(message=="LightSteelBlue")
  {
  leds[2] = 0xB0C4DE;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightSteelBlue";
  message="";

  } else if(message=="LightYellow")
  {
  leds[2] = 0xFFFFE0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LightYellow";
  message="";

  } else if(message=="Lime")
  {
  leds[2] = 0x00FF00;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Lime";
  message="";

  } else if(message=="LimeGreen")
  {
  leds[2] = 0x32CD32;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "LimeGreen";
  message="";

  } else if(message=="Linen")
  {
  leds[2] = 0xFAF0E6;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Linen";
  message="";

  } else if(message=="Magenta")
  {
  leds[2] = 0xFF00FF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Magenta";
  message="";

  } else if(message=="Maroon")
  {
  leds[2] = 0x800000;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Maroon";
  message="";

  } else if(message=="MediumAquamarine")
  {
  leds[2] = 0x66CDAA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumAquamarine";
  message="";

  } else if(message=="MediumBlue")
  {
  leds[2] = 0x0000CD;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumBlue";
  message="";

  } else if(message=="MediumOrchid")
  {
  leds[2] = 0xBA55D3;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumOrchid";
  message="";

    } else if(message=="MediumPurple")
  {
  leds[2] = 0x9370DB;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumPurple";
  message="";

  } else if(message=="MediumSeaGreen")
  {
  leds[2] = 0x3CB371;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumSeaGreen";
  message="";


  } else if(message=="MediumSlateBlue")
  {
  leds[2] = 0x7B68EE;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumSlateBlue";
  message="";

  } else if(message=="MediumSpringGreen")
  {
  leds[2] = 0x00FA9A;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumSpringGreen";
  message="";

  } else if(message=="MediumTurquoise")
  {
  leds[2] = 0x48D1CC;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumTurquoise";
  message="";

  } else if(message=="MediumVioletRed")
  {
  leds[2] = 0xC71585;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MediumVioletRed";
  message="";

  } else if(message=="MidnightBlue")
  {
  leds[2] = 0x191970;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MidnightBlue";
  message="";

  } else if(message=="MintCream")
  {
  leds[2] = 0xF5FFFA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MintCream";
  message="";

  } else if(message=="MistyRose")
  {
  leds[2] = 0xFFE4E1;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "MistyRose";
  message="";

  } else if(message=="Moccasin")
  {
  leds[2] = 0xFFE4B5;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Moccasin";
  message="";

  } else if(message=="NavajoWhite")
  {
  leds[2] = 0xFFDEAD;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "NavajoWhite";
  message="";

  } else if(message=="Navy")
  {
  leds[2] = 0x000080;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Navy";
  message="";

  } else if(message=="OldLace")
  {
  leds[2] = 0xFDF5E6;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "OldLace";
  message="";

  } else if(message=="Olive")
  {
  leds[2] = 0x808000;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Olive";
  message="";

    } else if(message=="OliveDrab")
  {
  leds[2] = 0x6B8E23;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "OliveDrab";
  message="";

  } else if(message=="Orange")
  {
  leds[2] = 0xFFA500;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Orange";
  message="";

  } else if(message=="OrangeRed")
  {
  leds[2] = 0xFF4500;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "OrangeRed";
  message="";

  } else if(message=="Orchid")
  {
  leds[2] = 0xDA70D6;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Orchid";
  message="";

  } else if(message=="PaleGoldenrod")
  {
  leds[2] = 0xEEE8AA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "PaleGoldenrod";
  message="";

  } else if(message=="PaleGreen")
  {
  leds[2] = 0x98FB98;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "PaleGreen";
  message="";

  } else if(message=="PaleTurquoise")
  {
  leds[2] = 0xAFEEEE;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "PaleTurquoise";
  message="";

  } else if(message=="PaleVioletRed")
  {
  leds[2] = 0xDB7093;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "PaleVioletRed";
  message="";

  } else if(message=="Plaid")
  {
  leds[2] = 0xCC5533;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Plaid";
  message="";

  } else if(message=="Plum")
  {
  leds[2] = 0xDDA0DD;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Plum";
  message="";

  } else if(message=="PowderBlue")
  {
  leds[2] = 0xB0E0E6;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "PowderBlue";
  message="";

  } else if(message=="Purple")
  {
  leds[2] = 0x800080;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Purple";
  message="";

  } else if(message=="Red")
  {
  leds[2] = 0xFF0000;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Red";
  message="";

  } else if(message=="RosyBrown")
  {
  leds[2] = 0xBC8F8F;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "RosyBrown";
  message="";

  } else if(message=="RoyalBlue")
  {
  leds[2] = 0x4169E1;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "RoyalBlue";
  message="";

  } else if(message=="SaddleBrown")
  {
  leds[2] = 0x8B4513;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SaddleBrown";
  message="";

  } else if(message=="Salmon")
  {
  leds[2] = 0xFA8072;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Salmon";
  message="";

  } else if(message=="SandyBrown")
  {
  leds[2] = 0xF4A460;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SandyBrown";
  message="";

  } else if(message=="SeaGreen")
  {
  leds[2] = 0x2E8B57;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SeaGreen";
  message="";

  } else if(message=="Seashell")
  {
  leds[2] = 0xFFF5EE;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Seashell";
  message="";

    } else if(message=="Sienna")
  {
  leds[2] = 0xA0522D;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Sienna";
  message="";

  } else if(message=="Silver")
  {
  leds[2] = 0xC0C0C0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Silver";
  message="";

  } else if(message=="SkyBlue")
  {
  leds[2] = 0x87CEEB;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SkyBlue";
  message="";

    } else if(message=="SlateBlue")
  {
  leds[2] = 0x6A5ACD;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SlateBlue";
  message="";

  } else if(message=="SlateGrey")
  {
  leds[2] = 0x708090;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SlateGrey";
  message="";

  } else if(message=="Snow")
  {
  leds[2] = 0xFFFAFA;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Snow";
  message="";

    } else if(message=="SpringGreen")
  {
  leds[2] = 0x00FF7F;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SpringGreen";
  message="";

  } else if(message=="SteelBlue")
  {
  leds[2] = 0x4682B4;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "SteelBlue";
  message="";

  } else if(message=="Tan")
  {
  leds[2] = 0xD2B48C;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Tan";
  message="";

    } else if(message=="Teal")
  {
  leds[2] = 0x008080;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Teal";
  message="";

  } else if(message=="Thistle")
  {
  leds[2] = 0xD8BFD8;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Thistle";
  message="";

    } else if(message=="Tomato")
  {
  leds[2] = 0xFF6347;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Tomato";
  message="";

  } else if(message=="Turquoise")
  {
  leds[2] = 0x40E0D0;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Turquoise";
  message="";


    } else if(message=="Violet")
  {
  leds[2] = 0xEE82EE;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Violet";
  message="";

  } else if(message=="Wheat")
  {
  leds[2] = 0xF5DEB3;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Wheat";
  message="";

    } else if(message=="White")
  {
  leds[2] = 0xFFFFFF;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "White";
  message="";


    } else if(message=="WhiteSmoke")
  {
  leds[2] = 0xF5F5F5;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "WhiteSmoke";
  message="";

  } else if(message=="Yellow")
  {
  leds[2] = 0xFFFF00;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "Yellow";
  message="";

    } else if(message=="YellowGreen")
  {
  leds[2] = 0x9ACD32;
  FastLED.setBrightness(50);
  FastLED.show();
  barva = "YellowGreen";
  message="";

  } else if(message=="Off")
  {
  leds[2] = 0x000000;
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




