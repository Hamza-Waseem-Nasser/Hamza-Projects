const int infrared1 = A0;  // Connect the IR sensor to digital pin 22626


void setup() {
  Serial.begin(9600);
    pinMode(infrared1, INPUT);

}

void loop() {
 
  
  int x =analogRead(infrared1);
  int y = digitalRead(infrared1);
  Serial.println(x);
  /*
if(digitalRead(infrared1)==HIGH)
  Serial.println("yes yes");
  else Serial.println("no no ");

  //int x = analogRead(infrared1);
  */
}
