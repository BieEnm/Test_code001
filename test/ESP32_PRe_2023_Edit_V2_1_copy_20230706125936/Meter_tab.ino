#include <ModbusMaster.h>
#define RXD2 16
#define TXD2 17

#define Meter_ADDR 125
#define Total_of_Reg 3

#define Reg_VoltPhaseA 4039
#define Reg_PowerTotal 4015         //0.001kW
#define Reg_ActiveEnergyTotal 4011  //0.1kWh

uint16_t const Reg_addr[3] = {
  Reg_VoltPhaseA,
  Reg_PowerTotal,
  Reg_ActiveEnergyTotal
};

float DATA_METER[Total_of_Reg];


ModbusMaster node;
uint32_t Read_Meter(char addr, uint16_t REG) {
  uint8_t j, result;
  uint32_t data[1];
  uint32_t value = 0;

  node.begin(addr, Serial2);
  result = node.readHoldingRegisters(REG, 1);
  delay(100);
  if (result == node.ku8MBSuccess) {
    for (j = 0; j < 1; j++) {
      data[j] = node.getResponseBuffer(j);
    }
    modbus_fail = 0;
    value = data[0];
    return value;
  } else {
    modbus_fail = 1;
    Serial.print("Connec modbus fail. REG>>> ");
    Serial.println(REG, HEX);
    return 0;
  }
}

void setup_Modbus() {
  Serial2.begin(4800, SERIAL_8E1, RXD2, TXD2);
}

void loop_GetMeter() {
  if (Process_RecodeMeter == 0 || Process_RecodeMeter == 1) {
    for (char i = 0; i < Total_of_Reg; i++) {
      DATA_METER[i] = Read_Meter(Meter_ADDR, Reg_addr[i]);
    }
    Data_Volt = (DATA_METER[0] / 100.0);
    Data_kWh = (DATA_METER[1] / 1000.0) * 60;
    Data_TotalEnergy = (DATA_METER[2] / 10.0) * 60;
    if (Data_kWh > 0) {
      Serial.println("---------------------------------");
      Serial.println(String("  Volt : ") + Data_Volt);
      Serial.println(String("   kWh : ") + Data_kWh);
      Serial.println(String("Energy : ") + Data_TotalEnergy);
      Serial.println("---------------------------------");
      kWh_str = String(Data_kWh);
      Record_kWh = Data_kWh;
      TotalEnergy_str = String(Data_TotalEnergy);
      Record_TotalEnergy = Data_TotalEnergy;

      Process_RecodeMeter = 2;
      Check_ValueMt = 1;
      count_Meter = 0;
      Serial.print("Meter running on core ");
      Serial.println(xPortGetCoreID());
    }
    if (count_Meter >= 10) {
      kWh_str = String(Record_kWh);
      TotalEnergy_str = String(Record_TotalEnergy);
      Process_RecodeMeter = 2;
      Check_ValueMt = 1;
      count_Meter = 0;
    }
  }
}