//variable int
int count_byte;

//variable String
String Char_str[5];

unsigned long delay_Millis = 0;


#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup_ADDR() {
  byte address;
  for (address = 0x27; address <= 0x3F; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    if (error == 0) {
      lcd = LiquidCrystal_I2C(address, 20, 4);  // กำหนด I2C address ที่ค้นหาได้
      break;
    }
  }
  Serial.println(String("Address LCD is: ") + address);
  lcd.init();
  lcd.backlight();
}

void loop_Fillout() {
  if (Esp_Restart == 0) {
    if (Mode_A < 4) {
      lcd.setCursor(0, 0);
      lcd.print("      Fill out");
      if (MC_str.toInt() > 0 && count_min >= next_mode) {
        lcd.setCursor(0, 1);
        lcd.print(String("   OD : ") + OD_str);
        lcd.setCursor(0, 2);
        lcd.print(String("   TN : ") + TN_str);
        lcd.setCursor(0, 3);
        lcd.print(String("  AEI : ") + MC_str);
        if (sec >= 10) {
          Mode_A = 4;
        }
      } else {
        if (Mode_A == 1) {                                   //กรอกข้อมูลความกว้างท่อ
          OD[count_key] = '\0';                              //ลบตัวแปร"OD"ตำแหน่ง"count_key"ให้ว่าง
          lcd.setCursor(0, 1);                               //
          lcd.print(String(">  OD : ") + OD);                //
          lcd.setCursor(0, 2);                               //
          lcd.print("   TN : ");                             //
          lcd.setCursor(0, 3);                               //
          lcd.print("  AEI : ");                             //
          lcd.setCursor(9 + count_key, 1);                   //ระบุตำแหน่งหลังcursor (เพื่อลบcursorที่ข้างบนหน้าจอ)
          lcd.print(" ");                                    //ลบcursorที่ข้างบนหน้าจอ
        }                                                    //
        if (Mode_A == 2) {                                   //กรอกข้อมูลความหนาท่อ
          TN[count_key] = '\0';                              //ลบตัวแปร"OD"ตำแหน่ง"count_key"ให้ว่าง
          lcd.setCursor(0, 1);                               //
          lcd.print(String("   OD : ") + OD + String(" "));  //
          lcd.setCursor(0, 2);                               //
          lcd.print(String(">  TN : ") + TN);                //
          lcd.setCursor(0, 3);                               //
          lcd.print("  AEI : ");                             //
          lcd.setCursor(9 + count_key, 2);                   //ระบุตำแหน่งหลังcursor (เพื่อลบcursorที่ข้างบนหน้าจอ)
          lcd.print(" ");                                    //ลบcursorที่ข้างบนหน้าจอ
        }
        if (Mode_A == 3) {                                   //กรอกข้อมูลเครื่อง
          MC[count_key] = '\0';                              //ลบตัวแปร"MC"ตำแหน่ง"count_key"ให้ว่าง
          lcd.setCursor(0, 1);                               //
          lcd.print(String("   OD : ") + OD + String(" "));  //
          lcd.setCursor(0, 2);                               //
          lcd.print(String("   TN : ") + TN + String(" "));  //
          lcd.setCursor(0, 3);                               //
          lcd.print(String("> AEI : ") + MC);                //
          lcd.setCursor(9 + count_key, 3);                   //ระบุตำแหน่งหลังcursor (เพื่อลบcursorที่ข้างบนหน้าจอ)
          lcd.print(" ");                                    //ลบcursorที่ข้างบนหน้าจอ
        }                                                    //
        lcd.setCursor(8 + count_key, Mode_A);                //ระบุตำแหน่งcursor (ห่างจากด้านหน้า8ช่องของLCD)
        if (led_millis == 0) {                               //กำหนดให้cursorกระพริบ
          lcd.print(" ");                                    //
        } else {                                             //
          lcd.print("I");                                    //ใช้"I"แทนcursor
        }
      }
    }
  }
}