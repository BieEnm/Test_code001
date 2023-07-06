
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "ESPcenter";
const char* password = "esp-3214";

//variable char
char diplay_traf[10];
char OD[6], TN[6], MC[6];

//variable int
int LCD_ADDR;
int Mode_A = 1;
int Mode_B, check_modeB;
int next_mode = 1;
int Esp_Restart;
int Press_key;
int sec, count_min, count_Import, count_transfer, count_wifi, count_Backlight, count_Meter;
int count_key;
int Process_RecodeMeter;
int Process_RecodeEncoder;
int Process_Transfer;
int led_transfer;
int Check_ValueEn, Check_ValueMt;
int modbus_fail;

//variable String
String Mac_addr;
String OD_str, TN_str, MC_str;
String sec_str;
String rssi_str, user_str;
String kWh_str, TotalEnergy_str;
String Encoder_str, LongEn_str;
String Unit_str;

//variable float
float Data_Volt, Data_kWh, Data_TotalEnergy;
float Record_Volt, Record_kWh, Record_TotalEnergy;
float Encoder_float, Long_Encoder;


void setup() {
  Serial.begin(115200);
  setup_Modbus();
  //setCpuFrequencyMhz(160);
  setCpuFrequencyMhz(240);
  delay(1000);
  Serial.print("CPU Freq: ");
  Serial.println(getCpuFrequencyMhz());
  Serial.print("Setup running on core ");
  Serial.println(xPortGetCoreID());

  setup_Light();       //Calculate_tab.ino
  setup_Keypad();      //Keypad_tab.ino
  setup_ADDR();        //DisplayF_tab.ino
  setup_Macaddress();  //Transfer_tab.ino
  setup_Encoder();     //Encoder_tab.ino
  /*WiFi.disconnect();
  //WiFi.mode(WIFI_MODE_STA);
  WiFi.enableSTA(true);
  delay(1000);
  WiFi.begin(ssid, password);
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println("Wait for WiFi... ");
  if (WiFi.status() == WL_CONNECTED) {
    get_network_info();
  }*/
  xTaskCreatePinnedToCore(loop2, "loop2", 100000, NULL, 0, NULL, 0);
}
/*
void loop() {
  loop_Keypad();        //Keypad_tab.ino
  loop_Fillout();       //DisplayF_tab.ino
  calculate_Time();     //Calculate_tab.ino
  loop_info();          //DisplayM_tab.ino
  loop_infostr();       //DisplayM_tab.ino
  loop_diplay_modeB();  //DisplayM_tab.ino
  calculate_Dim();      //Calculate_tab.ino
  loop_Encoder();       //Encoder_tab.ino
  calculate_Values();   //Calculate_tab.ino
  setup_GoogleID();     //Transfer_tab.ino
  ESP_ReStart();        //DisplayM_tab.ino
  loop_Light();         //Calculate_tab.ino
  Lcd_noBackLight();    //DisplayM_tab.ino
}

void loop2(void* pvParameters) {
  Serial.print("loop2 running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    Wif_status();       //Wifi_tab.ino
    loop_ImportData();  //Transfer_tab.ino
    loop_GetMeter();    //Meter_tab.ino
    loop_ExportData();  //Transfer_tab.ino
    //delay(100);
  }
}
*/
void loop() {
  Wif_status();       //Wifi_tab.ino
  loop_ImportData();  //Transfer_tab.ino
  loop_GetMeter();    //Meter_tab.ino
  loop_ExportData();  //Transfer_tab.ino
}

void loop2(void* pvParameters) {
  Serial.print("loop2 running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    loop_Keypad();        //Keypad_tab.ino
    loop_Fillout();       //DisplayF_tab.ino
    calculate_Time();     //Calculate_tab.ino
    loop_info();          //DisplayM_tab.ino
    loop_infostr();       //DisplayM_tab.ino
    loop_diplay_modeB();  //DisplayM_tab.ino
    calculate_Dim();      //Calculate_tab.ino
    loop_Encoder();       //Encoder_tab.ino
    calculate_Values();   //Calculate_tab.ino
    setup_GoogleID();     //Transfer_tab.ino
    ESP_ReStart();        //DisplayM_tab.ino
    loop_Light();         //Calculate_tab.ino
    Lcd_noBackLight();    //DisplayM_tab.ino
  }
}
