#include <Wire.h>
#include "Adafruit_VL6180X.h"

#define TCAADDR 0x70 // บ้านเลขที่พื้นฐานของบอร์ด Multiplexer

// สร้างตัวแปรเซนเซอร์แค่ "ตัวเดียว" พอครับ
Adafruit_VL6180X vl = Adafruit_VL6180X();

// ฟังก์ชันสับรางรถไฟ (เลือกช่อง 0-7)
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); }
  Wire.begin();

  Serial.println("\n--- เริ่มต้นระบบ TCA9548A Multiplexer ---");

  // เช็ก Sensor 1 (ช่อง 0)
  tcaselect(0); // สับรางไปช่อง 0
  if (!vl.begin()) {
    Serial.println("X ไม่พบ Sensor 1 (เช็กสาย SD0/SC0)");
  } else {
    Serial.println("O พบ Sensor 1 พร้อมใช้งาน!");
  }

  // เช็ก Sensor 2 (ช่อง 1)
  tcaselect(1); // สับรางไปช่อง 1
  if (!vl.begin()) {
    Serial.println("X ไม่พบ Sensor 2 (เช็กสาย SD1/SC1)");
  } else {
    Serial.println("O พบ Sensor 2 พร้อมใช้งาน!");
  }
  
  Serial.println("----------------------------------------");
}

void loop() {
  // สับรางไปช่อง 0 เพื่ออ่าน Sensor 1
  tcaselect(0);
  uint8_t d1 = vl.readRange();

  // สับรางไปช่อง 1 เพื่ออ่าน Sensor 2
  tcaselect(1);
  uint8_t d2 = vl.readRange();

  // พิมพ์ผลลัพธ์
  Serial.print("S1: "); 
  Serial.print(d1); 
  Serial.print(" mm \t|\t S2: "); 
  Serial.print(d2); 
  Serial.println(" mm");

  delay(100);
}
