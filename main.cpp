#include <M5StickCPlus.h>
#include <WiFiMulti.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <ArduinoJson.h>


//library doc: https://platformio.org/lib/show/6758/ESPAsyncWebServer-esphome


// Set the name and password of the wifi to be connected.  配置所连接wifi的名称和密码

const char *ssid = "LF";
const char *password = "hesloksiti";

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
//String localIP;

String barva;



// the setup routine runs once when M5StickC starts up
void setup(){ 
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Initialize the M5StickC object
  M5.begin();
  
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Rover\n");

  int sum=0;
  WiFiMulti.addAP(ssid, password);  //Add wifi configuration information.  添加wifi配置信息
  M5.lcd.printf("Waiting connect to WiFi: %s \n",ssid); //Serial port output format string.  串口输出格式化字符串
  while(WiFiMulti.run() != WL_CONNECTED) {  //If the connection to wifi is not established successfully.  如果没有与wifi成功建立连接
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


  Serial.print("IP Address: ");
  Serial.println(localIP);
  M5.lcd.print("IP address:\n");
  M5.lcd.println(localIP); //The serial port outputs the IP address of the M5StickC.  串口输出M5StickC的IP地址
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
            request->redirect("/");
        } else {
            message = "No message sent";
        }
        request->send(200, "text/html", "Welcome:): " + message + "<br>" + \
         "<a href=/set?message=r>RED</a><br><br>" + \
         "<a href=/set?message=o>ORANGE</a><br><br>" + \
         "<a href=/set?message=y>YELLOW</a><br><br>" + \
         "<a href=/set?message=g>GREEN</a><br><br>" + \
         "<a href=/set?message=b>BLUE</a><br><br>" + \
         "<a href=/set?message=p>PURPLE</a><br><br>" + \
         "<a href=/set?message=c>RAINBOW</a><br><br>" + \
         "<a href=/set?message=f>SEMAFOR</a><br><br>" + \
         "<a href=/set?message=w>WHITE</a><br><br>" + \
         "<a href=/set?message=t>TURN OFF</a>" 
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
        
        request->send(200, "application/json", odpoved);
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

 if(message=="r")
  {
  leds[2] = CRGB::Red;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "red";
  message="";

  } else if(message=="y")
  {
  leds[2] = CRGB::Yellow;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "yellow";
  message="";

  } else if(message=="g")
  {
  leds[2] = CRGB::Green;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "green";
  message="";

   message="";
  } else if(message=="o")
  {
   leds[2] = CRGB::Orange;
   FastLED.setBrightness(30);
   FastLED.show();
   barva = "orange";
   message="";

  } else if(message=="b")
  {
  leds[2] = CRGB::Blue;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "blue";
  message="";

  } else if(message=="p")
  {
  leds[2] = CRGB::Purple;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "purple";
  message="";

  } else if(message=="t")
  {
  leds[2] = CRGB::Black;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "off";
  message="";
 
  } else if(message=="w")
  {
  leds[2] = CRGB::White;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "white";
  message="";

  } else if(message=="c")
  {
  leds[2] = CRGB::Red;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "rainbow";
  delay(1000);

  leds[2] = CRGB::Orange;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(1000);

  leds[2] = CRGB::Yellow;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(1000);

  leds[2] = CRGB::Green;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(1000);

  leds[2] = CRGB::Blue;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(1000);

  leds[2] = CRGB::Purple;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(1000);

  leds[2] = CRGB::Black;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(10);
  

  } else if(message=="f")
  {
  leds[2] = CRGB::Red;
  FastLED.setBrightness(30);
  FastLED.show();
  barva = "semafor";
  delay(1000);
  leds[2] = CRGB::Black;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(10);

  leds[1] = CRGB::Orange;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(500);
  leds[1] = CRGB::Black;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(10);

  leds[0] = CRGB::Green;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Black;
  FastLED.setBrightness(30);
  FastLED.show();
  delay(10);



  } else if(message=="p")
  {
   message="";
  }
  
  delay(100);
  
  }

