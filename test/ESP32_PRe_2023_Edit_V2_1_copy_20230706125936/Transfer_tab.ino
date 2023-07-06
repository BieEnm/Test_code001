
String GOOGLE_SCRIPT_ID;
String Send_Machine, Send_Size, Send_Unit, Send_kWh, Send_Speed, Send_Energy;
int check_export;
String AEI[20];
String GOOGLE_SCRIPT_ID_I = "AKfycbwy2USqjN2aGlA2H8ut4nKCytmegFzgzhTKlbLyVxynkDIyHBzfqzdW2b5nCFO3ZsBUlg";
String Send_name;
int j, t, count_j;
String payload_str[3];


void setup_Macaddress() {
  Mac_addr = String(WiFi.macAddress());
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(Mac_addr);
  Send_name = String(String("name=") + Mac_addr + String("&read"));

  AEI[1] = "AKfycby-_7of4e2OX-kY8WCLNlRNBzsFvcczFdYKFu-be0lB6KXLBpKik-2EAcmyNg-b1iIFdw";
  AEI[2] = "AKfycbzNLyOWoiEcdVv82hgF_YWo_YPSdA9C7dXDhvdYvlCJ9GWABcosQo2OZeRlHukVgSKK";
  AEI[3] = "AKfycbzcLdlVjssxQCeiaGDgyy87_tQpHhp3AFxg3qi29JOf1hPfy6igXS1bV-JGWjYEi37aMQ";
  AEI[4] = "AKfycbyyQeYph4PQ1rFJ3oQvwUyBhfVKwmto9gVx5b7wxEMqfZRL21e-L9-wFpiPaC6oQvYo-w";
  AEI[5] = "AKfycbz5vtMypVHA0S6g0xgU9VKLQcwsnWZ4lwLJNmNPFvAJ1CzYB6JCOSgEVw7HS7NEVMORww";
  AEI[6] = "AKfycbwSHHJCjA8MewaGRf4lp2y_CNNNtv6fyfGUeI0h2Wc5iIrOHBRTA0VOS8cJ7EgdbYI4_A";
  AEI[7] = "AKfycby5s95qRsBQU_SoQ8AZWU2FxL1Syp6A2KyBeBq1tqaPBZTGvHPppBIXgQWqRzdshBhF6w";
  AEI[8] = "AKfycbwBbqFDOIxc76D3v1UVzCcYP5pKEcBpnjNkuojB537KZi2OqWe4z3JtBG_eS1gzVxPr_w";
  AEI[9] = "AKfycbxaGPP_0nIdQZwgyPtxvtDPnqhY6AyVvSPk9nDuTYiXApNb8BpCbzsMjuX4rowk3aWpow";
  AEI[10] = "AKfycbzFSctCTEajhhV7BMpVVe7OprD4urExe2Y9tqDh0tv3L-LG04CEI6Qw8O9SKbJ3eu1PYw";
  AEI[11] = "AKfycbxeWkktTZPz-3HcIJIMJPKkq3esWPyLOCKDxeEzLtEURPgZYm5fqk2qxQV-3-FZ68HZ";
  AEI[12] = "AKfycbzvUTvpf5vMze3SiLYRawjusT5q5OS5OAaRuIgztZP9b_KQcMSELDN4r8WliPynxp6x";
  AEI[13] = "AKfycbz8jATVH0TgD4aMK_pIECXjFkGCFW9AE09Pu92OrAfsoq4Ge0yFs_GeA6l6w6JhJ3-SMw";
  AEI[14] = "AKfycbzsZtNerABKlzHoNoMMsm0f4s5KMzcuM_mYVpm5np94d477_aPR-54cZ8cLlO_dzgTm";
  AEI[15] = "AKfycbyZ2xd8su5p36lRVoYw-2XsfxNRZQRde1ESRMC2aMd5CsZZCSZRuh3cfn4NHMnNyCAsbQ";
  AEI[16] = "AKfycbwjSxXZ6j1HubdspJpX-GTPO3SGVxJI6PUl1m6mobllDjO26iIxndodzysWXWw6Nlnu";
  AEI[17] = "AKfycbz-Z1MZPX-lCFJBNo9n2z_D1uJy-A-18ZUdmlpxbhejQ36vCLp8oXAEepCsQkZVC-4n";
}


void loop_ImportData() {
  if (MC_str.toInt() <= 0 && Press_key == 0 && sec >= 10) {  // ถ้าไม่กดภายใน 1นาที ให้ดึงข้อมูลจาก Google sheet
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(String("Check Import : ") + Send_name);
      HTTPClient http;
      String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID_I + "/exec?" + Send_name;  //
      http.begin(urlFinal.c_str());                                                                         //กำหนด url เพื่อเซฟข้อมูลลง google sheets
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);                                               //
      int httpCode = http.GET();                                                                            //ส่งค่า url
      if (httpCode > 0) {                                                                                   //ถ้าส่งสำเร็จ
        String payload = http.getString();                                                                  // อ่านค่าผลลัพธ์
        Serial.println(payload);
        while (j < payload.length()) {
          if (payload.substring(j, j + 1) == ",") {
            if (count_j <= 0) {
              payload_str[count_j] = payload.substring(t, j);
              t = j;
              count_j++;
            } else {
              payload_str[count_j] = payload.substring(t + 1, j);
              t = j;
              count_j++;
            }
          }
          j++;
          if (j == payload.length()) {
            payload_str[count_j] = payload.substring(t + 1, payload.length());
          }
        }
        Serial.println("---------------------------------");
        Serial.println(String("Machine          : ") + payload_str[0]);
        Serial.println(String("Outside Diameter : ") + payload_str[1] + String(" mm."));
        Serial.println(String("Thickness        : ") + payload_str[2] + String(" mm."));
        Serial.println("---------------------------------");
        if (payload_str[0].toFloat() > 0 && payload_str[1].toFloat() > 0 && payload_str[2].toFloat()) {
          MC_str = payload_str[0];
          OD_str = payload_str[1];
          TN_str = payload_str[2];
        }
        //check_import = 0;
      }
      http.end();
    }
  }
}

void loop_ExportData() {
  if (Process_Transfer == 1) {
    Send_Unit = Unit_str;
    Send_kWh = kWh_str;
    Send_Speed = LongEn_str;
    Send_Energy = TotalEnergy_str;
    String Send_Data = "name=" + Send_Machine + "&size=" + Send_Size + "&unit=" + Send_Unit + "&kWh=" + Send_kWh + "&speed=" + Send_Speed + "&energy=" + Send_Energy;
    String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + Send_Data;
    HTTPClient http;
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Transferring...");
      http.begin(urlFinal.c_str());         //กำหนด url เพื่อเซฟข้อมูลลง google sheets
      int httpCode = http.GET();            //ส่งค่า url
      if (httpCode > 0) {                   //ถ้าส่งสำเร็จ
        String payload = http.getString();  // อ่านค่าผลลัพธ์
        Serial.println(payload);
        Process_Transfer = 0;
        led_transfer = 1;
        led_count = 0;
        Serial.println("Transfer Successful.");
        Serial.print("Export running on core ");
        Serial.println(xPortGetCoreID());
        http.end();
      }
    }
    if (count_transfer >= 15) {
      http.end();
      Serial.println("Transfer Canceled!");
      Process_Transfer = 0;
    }
  }
}

void setup_GoogleID() {
  if (check_modeB > 0) {
    if (GOOGLE_SCRIPT_ID.length() <= 0) {
      GOOGLE_SCRIPT_ID = AEI[MC_str.toInt()];
      Serial.println(GOOGLE_SCRIPT_ID);
      if (MC_str.toInt() < 10) {
        Send_Machine = String("AEI-0") + MC_str + String("M");
      } else {
        Send_Machine = String("AEI-") + MC_str + String("M");
      }
      Send_Size = String(OD_str + String("X") + TN_str);
    }
  }
}
