
int Wifi_order = 2;

void Wif_status() {
  if (WiFi.status() != WL_CONNECTED && Wifi_order == 2) {
    Wifi_order = 0;
  }
  if (WiFi.status() == WL_CONNECTED && Wifi_order < 2) {
    Serial.println("Connected to successfully.");
    Serial.print("Wifi running on core ");
    Serial.println(xPortGetCoreID());
    get_network_info();
    Wifi_order = 2;
  }
  if (Wifi_order == 0) {
    WiFi.disconnect();
    WiFi.enableSTA(true);
    Serial.println("WiFi Disconnected!");
    Wifi_order = 1;
  }
  if (Wifi_order == 1) {
    if (count_wifi < 6) {

    } else {
      WiFi.disconnect();
      WiFi.mode(WIFI_MODE_STA);
      WiFi.enableSTA(true);
      WiFi.begin(ssid, password);
      Serial.println("WiFi Connecting...");
      Serial.print("WiFi running on core ");
      Serial.println(xPortGetCoreID());
      count_wifi = 0;
    }
  }
}

void get_network_info() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("[*] Network information for ");
    Serial.println(ssid);
    Serial.println("[+] BSSID : " + WiFi.BSSIDstr());
    Serial.print("[+] Gateway IP : ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("[+] Subnet Mask : ");
    Serial.println(WiFi.subnetMask());
    Serial.println((String) "[+] RSSI : " + WiFi.RSSI() + " dB");
    Serial.print("[+] ESP32 IP : ");
    Serial.println(WiFi.localIP());
    user_str = String(ssid);
    rssi_str = String(WiFi.RSSI() + String(" dB"));
  }
}