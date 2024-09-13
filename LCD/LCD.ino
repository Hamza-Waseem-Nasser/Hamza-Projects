#include <LiquidCrystal_I2C.h>

#include <LiquidCrystal.h>
///LiquidCrystal lcd(1,2,4,5,6,7);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
 lcd.init();                              // Start the LCD
    lcd.backlight();      
   
//Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //int ldrStatus = analogRead(ldrPin);
 //Serial.println(ldrStatus);
 //if(ldrStatus<=150){
//digitalWrite(ledPin,HIGH);
//Serial.println("LDR IS INTRUpted");

 //}
 //else{digitalWrite(ledPin,LOW);
//}
 lcd_print();

}
void lcd_print(){
lcd.print("HI");
lcd.setCursor(0,1);
lcd.print("lcd is working");
//lcd.blink();
delay(100000);
lcd.clear();

 
}

