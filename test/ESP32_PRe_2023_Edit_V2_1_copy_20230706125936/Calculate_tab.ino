
int led_count;
int led_millis;

float Cal_Weight, Data_Weight, Data_Unit;


unsigned long previousMillis = 0;
unsigned long preledMillis = 0;


#define light_Key 5   //Status Detail
#define light_Send 4  //Status Sent Data
#define light_Wifi 2  //Status wifi

void setup_Light() {
  pinMode(light_Key, OUTPUT);
  pinMode(light_Send, OUTPUT);
  pinMode(light_Wifi, OUTPUT);
}

void loop_Light() {
  if (WiFi.status() != WL_CONNECTED) {
    if (led_millis == 1) {
      digitalWrite(light_Wifi, HIGH);
    } else {
      digitalWrite(light_Wifi, LOW);
    }
  } else {
    digitalWrite(light_Wifi, LOW);
  }

  if (MC_str.toInt() <= 0) {
    if (led_millis == 1) {
      digitalWrite(light_Key, HIGH);
    } else {
      digitalWrite(light_Key, LOW);
    }
  } else {
    digitalWrite(light_Key, LOW);
  }

  if (led_transfer == 1) {
    if (led_count <= 5) {
      if (led_millis == 1) {
        digitalWrite(light_Send, HIGH);
      } else {
        digitalWrite(light_Send, LOW);
      }
    } else {
      led_transfer = 0;
    }
  } else {
    digitalWrite(light_Send, LOW);
  }
}

void calculate_Time() {
  if (Esp_Restart == 0) {
    unsigned long currentMillis = millis();
    unsigned long ledMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      if (modbus_fail == 1 && count_Meter < 15 && Process_RecodeMeter != 2) {
        count_Meter++;
        Serial.println(String("Count Meter : ") + count_Meter);
      }
      //---------------------------------------------------------------------------
      if (WiFi.status() != WL_CONNECTED) {
        count_wifi++;
      }
      //---------------------------------------------------------------------------
      if (count_transfer <= 15 && Process_Transfer == 1) {  //ส่วนของดึงข้อมูล loop_ExportData();
        count_transfer++;
        Serial.println(String("Count transfer is ") + count_transfer);
      }
      //---------------------------------------------------------------------------
      if (led_count <= 5) {
        led_count++;
      }
      //---------------------------------------------------------------------------
      if (sec < 59) {
        sec++;
      } else {
        sec = 0;
        Serial.print("Time running on core ");
        Serial.println(xPortGetCoreID());
        if (count_min <= 9) {  //10นาที
          count_min++;
        } else {
          if (MC_str.toInt() <= 0) {
            Esp_Restart = 1;
          }
        }
        if (MC_str.toInt() > 0 && count_min >= next_mode && Mode_A < 4) {
          sec = 0;
        }
        Serial.println(String("Min is ") + count_min);
        if (check_modeB > 0) {
          Process_RecodeMeter = 1;
          Process_RecodeEncoder = 1;
        }
        if (check_modeB > 0) {
          if (count_Backlight < 3) {
            count_Backlight++;
          }
          Serial.println(String("count_Backlight is ") + count_Backlight);
        }
      }
      previousMillis = currentMillis;
    }
    //---------------------------------------------------------------------------
    if (sec < 10) {
      sec_str = String(String("0") + sec);
    } else {
      sec_str = sec;
    }
    if (WiFi.status() != WL_CONNECTED || MC_str.toInt() <= 0 || led_transfer == 1 || count_min <= next_mode) {
      if (ledMillis - preledMillis >= 500) {
        if (led_millis < 1) {
          led_millis++;
        } else {
          led_millis = 0;
        }
        preledMillis = ledMillis;
      }
    }
  }
}

void calculate_Dim() {
  if (String(MC).toInt() > 0) {
    MC_str = String(MC);
    OD_str = String(OD);
    TN_str = String(TN);
  }
}

void calculate_Values() {
  if (Check_ValueEn == 1 && Check_ValueMt == 1) {
    Cal_Weight = (OD_str.toFloat() - TN_str.toFloat()) * (TN_str.toFloat() * 0.02491) * LongEn_str.toFloat();  //kg.
    Data_Weight = (Cal_Weight / 1000) * 60;                                                                    // คูณ 60 เพื่อทำให้เป็นชั่วโมง, หาร 1000 แปลงจากkgเป็นตัน
    Data_Unit = kWh_str.toFloat() / Data_Weight;
    Serial.println(String("LongEn_str is ") + LongEn_str);
    Serial.println(String("Cal_Weight is ") + Cal_Weight);
    Serial.println(String("Data_Weight is ") + Data_Weight);
    Serial.println(String("kWh_str is ") + kWh_str);
    Serial.println(String("Data_Unit is ") + Data_Unit);
    if (LongEn_str.toFloat() > 0) {
      Unit_str = String(Data_Unit);
    } else {
      Unit_str = String("0");
    }
    Check_ValueEn = 0;
    Check_ValueMt = 0;
    count_transfer = 0;
    Process_Transfer = 1;
  }
}
