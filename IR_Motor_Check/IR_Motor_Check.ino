#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

const int infrared0 = 11;   
const int infrared1 = 10;   
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin
unsigned long startTime = 0;

HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
unsigned long t = 0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
 pinMode(infrared0, INPUT);
    pinMode(infrared1, INPUT);
     LoadCell.begin();
     float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
  #if defined(ESP8266)|| defined(ESP32)
  EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom
   unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

    bool Check = false;
    while(!Check){
    if (digitalRead(infrared0) == LOW ) {
    startCounter();
    
 while(true){
  if (digitalRead(infrared1) == LOW) {
 stopCounter();
Check = true;

    break;

    }

    
  }
  }
  }
  

  for ( unsigned long count = 0; count <= 500000; count++) {
    static boolean newDataReady = 0;
    const int serialPrintInterval = 0; // increase value to slow down serial print activity

    // check for new data/start the next conversion:
    if (LoadCell.update()) newDataReady = true;

    // get smoothed value from the dataset:
    if (newDataReady) {
      if (millis() > t + serialPrintInterval) {
        float i = LoadCell.getData();
        Serial.print("Load_cell output val: ");
        Serial.println(i);
        newDataReady = 0;
        t = millis();
      }
    }

    // receive command from the serial terminal, send 't' to initiate the tare operation:
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 't') LoadCell.tareNoDelay();
    }

    // check if the last tare operation is complete:
    if (LoadCell.getTareStatus() == true) {
      Serial.println("Tare complete");
    }
  }
    
  float i = LoadCell.getData(); // Assuming you want to get the data after the loop

  
}

void startCounter() {
  startTime = millis();
  Serial.println("Counter started!");
}

void stopCounter() {
  unsigned long elapsedTime = millis() - startTime;
  Serial.print("Counter stopped. Elapsed time: ");
  Serial.print(elapsedTime );  // Convert milliseconds to seconds
  Serial.println(" milisecond");
}
