const int infrared0 = 3;  // Connect the IR sensor to digital pin 2
const int infrared1 = 2;  // Connect the IR sensor to digital pin 2

unsigned long startTime = 0;
 

void setup() {
  Serial.begin(9600);
  pinMode(infrared0, INPUT);
    pinMode(infrared1, INPUT);

}

void loop() {
 
  
  
  if (digitalRead(infrared0) == LOW ) {
    startCounter();
    
 while(true){
  if (digitalRead(infrared1) == LOW) {
 stopCounter();
    break;

    }

    
  }
  }
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

