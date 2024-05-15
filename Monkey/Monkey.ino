#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run
`make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
#define motorpin 13
int recmov=0;
int settime=250;
int runtime=0;

char bt_data; // variable for storing bluetooth data 

void setup() {
  btStart(); 
  SerialBT.begin("Monkey1"); //Bluetooth device name
  delay(200);
  recmov=0;
  pinMode(motorpin, OUTPUT);
  digitalWrite(motorpin, LOW); 
  runtime=0;
}
void loop() {
 if (SerialBT.available()){
   bt_data = SerialBT.read();
    if (bt_data=='1')
    {
      recmov=recmov+1;
    }
 }
 if (recmov>0)
 {
  digitalWrite(motorpin, HIGH);
  runtime=runtime+1;
  delay(10);
  if(runtime>=settime)
  {
    recmov=recmov-1;
    runtime=0;
  }
 }else{
   runtime=0;
   digitalWrite(motorpin, LOW);
 }
}
