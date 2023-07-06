//Display Manu tab.

//variable int

//variable String
String info_str[20];

void loop_info() {
  if (Mode_A == 4) {  //
    Mode_A = 5;       //
    Mode_B = 1;       //
    sec = 0;          //set sec = 0;
    if (String(MC).toInt() > 0) {
      MC_str = String(MC);
      OD_str = String(OD);
      TN_str = String(TN);
    }
  }
  if (Mode_A >= 5) {
    if (check_modeB != Mode_B) {
      lcd.clear();
      check_modeB = Mode_B;
      Serial.println(String("Print check Mode B : ") + check_modeB);
    }
  }
}

void loop_infostr() {
  info_str[1] = "    Information.";
  if (MC_str.toInt() < 10) {
    info_str[2] = String(String("Name: AEI-0") + MC_str + String("M"));
  } else {
    info_str[2] = String(String("Name: AEI-") + MC_str + String("M"));
  }
  info_str[3] = String(String("size: ") + OD_str + String("x") + TN_str);
  info_str[4] = String(String("Time: ") + sec_str);
  info_str[5] = "    Information.";
  info_str[6] = String(String("Power : ") + kWh_str);
  info_str[7] = String(String("Value : ") + Unit_str);
  info_str[8] = String(String("Speed : ") + LongEn_str);
  info_str[9] = "       SET UP";
  info_str[10] = "    ENCODER RUN.";
  info_str[11] = String(String("Length : ") + String(Long_Encoder) + String(" M."));
  info_str[12] = "";
  info_str[13] = "     Info Wi-Fi";
  info_str[14] = String(String("User : ") + user_str);
  info_str[15] = String(String("RSSI : ") + rssi_str);
  info_str[16] = String(String(": ") + Mac_addr);
}

void loop_diplay_modeB() {
  if (Esp_Restart == 0) {
    if (check_modeB > 0) {  //ถ้าLCD คือ Address 1 เริ่มทำงานเมื่อ check_modeB มากกว่า 0
      lcd.setCursor(0, 0);
      lcd.print(info_str[(check_modeB * 4) - 3]);
      lcd.setCursor(0, 1);
      lcd.print(info_str[(check_modeB * 4) - 2]);
      lcd.setCursor(0, 2);
      lcd.print(info_str[(check_modeB * 4) - 1]);
      lcd.setCursor(0, 3);
      lcd.print(info_str[check_modeB * 4]);
    }
  }
}

void ESP_ReStart() {
  if (Esp_Restart == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("    Restarting...");
    delay(9000);
    ESP.restart();
  }
}

void Lcd_noBackLight() {
  if (count_Backlight >= 3) {
    lcd.noBacklight();
  } else {
    lcd.backlight();
  }
}