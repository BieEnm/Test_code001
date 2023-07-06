#include <ESP32Encoder.h>
ESP32Encoder encoder;
int Encoder_first;

void setup_Encoder() {
  ESP32Encoder::useInternalWeakPullResistors = UP;
  encoder.attachHalfQuad(25, 26);
  encoder.clearCount();
}

void loop_Encoder() {
  if (check_modeB > 0) {
    if (Encoder_first == 0) {
      encoder.clearCount();
      Encoder_first = 1;
    }
    Encoder_str = encoder.getCount() / 2;
    if (Encoder_str.toFloat() != Encoder_float) {
      Encoder_float = Encoder_str.toFloat();
      if (Encoder_float < 0) {
        Encoder_float = Encoder_float - (Encoder_float + Encoder_float);
      }
      Long_Encoder = (Encoder_float * 14.9935) / 1000;
    }
    if (Process_RecodeEncoder == 1) {
      if (Long_Encoder < 0.10) {
        LongEn_str = String("0");
      } else {
        LongEn_str = String(Long_Encoder);
      }
      Process_RecodeEncoder = 2;
      encoder.clearCount();
      Check_ValueEn = 1;
    }
  }
}