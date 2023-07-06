//==============KeyPad===============
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#define I2CADDR 0x24
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '.', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 0, 1, 2, 3 };
byte colPins[COLS] = { 4, 5, 6, 7 };
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

void setup_Keypad() {
  Wire.begin();
  keypad.begin(makeKeymap(keys));
}

void loop_Keypad() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    //===============Number===================
    if (count_key <= 6) {
      if ((key != 'A') && (key != 'B') && (key != 'C') && (key != 'D') && (key != '#')) {
        if (Press_key == 0) {
          Press_key = 1;
        }
        if (Mode_A == 1) {
          OD[count_key] = key;
        }
        if (Mode_A == 2) {
          TN[count_key] = key;
        }
        if (Mode_A == 3) {
          MC[count_key] = key;
        }
        count_key++;
      }
    }
    //===============Enter====================
    if (key == 'A') {
      if (Mode_A < 4) {
        count_key = 0;
        Mode_A++;
      }
    }
    //===============Delete===================
    if (key == 'B') {
      if (Mode_A < 4) {
        if (count_key > 0) {
          count_key = count_key - 1;
        }
        if (Mode_A == 1) {
          OD[count_key] = ' ';
        }
        if (Mode_A == 2) {
          TN[count_key] = ' ';
        }
        if (Mode_A == 3) {
          MC[count_key] = ' ';
        }
      }
    }
    //==============Restrat===================
    if (key == 'C') {
      Esp_Restart = 1;
    }
    //===============Select===================
    if (key == 'D') {
      Mode_B++;
      if (Mode_B > 4) {  //มีข้อมูลทั้งหมด 4 หน้า
        Mode_B = 1;
      }
    }
    if (key == '#') {
      if (count_Backlight >= 3) {
        count_Backlight = 0;
      } else {
        count_Backlight = 3;
      }
    }
  }
}
