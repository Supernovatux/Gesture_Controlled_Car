#include <MPU6050_tockn.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#define rxPin 13
#define txPin 12
SoftwareSerial BT_Serial(rxPin, txPin);
MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  BT_Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  if (mpu6050.getAngleY()>20) {
    Serial.println("F");
    BT_Serial.println("F");
  }
  else if (mpu6050.getAngleY()<-20){
    Serial.println("B");
    BT_Serial.println("B");
  }
  else if (mpu6050.getAngleX()>20) {
    Serial.println("R");
    BT_Serial.println("R");
  }
  else if (mpu6050.getAngleX()<-20) {
    Serial.println("L");
    BT_Serial.println("L");
  }
  else  {
    Serial.println("S");
    BT_Serial.println("S");
  }
}