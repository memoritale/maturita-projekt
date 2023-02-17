#include <M5StickCPlus.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

uint8_t i = 7;
int b_cData=0;
int b_cDataCharge=0;
int b_cDataDischarge=0;
int b_ICharge=0;
int b_IDischarge=0;
int b_IinData=0;
int b_IusbInData=0;
int b_PowerBatData=0;
int b_TempData=0;
int b_TempIn=0;
int b_Vaps=0;
int b_Vbat=0;

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

   void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void setup() {
  M5.begin();
  M5.Lcd.fillScreen(WHITE);
  M5.Axp.ScreenBreath(16);
}

void loop() {
  //M5.Axp.ScreenBreath(i++);
b_cData=M5.Axp.GetCoulombchargeData();
b_cDataCharge=M5.Axp.GetCoulombData();
b_cDataDischarge=M5.Axp.GetCoulombdischargeData();
//#b_ICharge=M5.Axp.GetIchargeData();
b_IDischarge=M5.Axp.GetIdischargeData();
b_IinData=M5.Axp.GetIinData();
b_IusbInData=M5.Axp.GetIusbinData();
b_PowerBatData=M5.Axp.GetPowerbatData();
b_TempData=M5.Axp.GetTempData();
b_TempIn=M5.Axp.GetTempInAXP192();
b_Vaps=M5.Axp.GetVapsData();
b_Vbat=M5.Axp.GetVbatData();

  
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setCursor(10,1);
  M5.Lcd.println("b_cData");
  M5.Lcd.println(b_cData);
  M5.Lcd.println("b_cDataCharge");
  M5.Lcd.println(b_cDataCharge);
  M5.Lcd.println("b_cDataDischarge");
  M5.Lcd.println(b_cDataDischarge);
  M5.Lcd.println("b_ICharge");
  M5.Lcd.println(b_ICharge);
  M5.Lcd.println("b_IDischarge");
  M5.Lcd.println(b_IDischarge);
  M5.Lcd.println("b_IinData");
  M5.Lcd.println(b_IinData);
  M5.Lcd.println("b_PowerBatData");
  M5.Lcd.println(b_PowerBatData);
  M5.Lcd.println("b_TempData");
  M5.Lcd.println(b_TempData);
  M5.Lcd.println("b_TempIn");
  M5.Lcd.println(b_TempIn);
  M5.Lcd.println("b_Vaps");
  M5.Lcd.println(b_Vaps);
  M5.Lcd.println("b_Vbat");
  M5.Lcd.println(b_Vbat);
  if (i > 15) i = 0;
  i++;
  delay(2000);
}
