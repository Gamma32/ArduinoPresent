#include <Timer.h>
#include <Event.h>

 
const int buttonAPin = 2;     // the number of the pushbutton pin
const int buttonBPin = 4;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int timeLED1 = 5;      //Grün
const int timeLED2 = 10;
const int timeLED3 = 6;      //Rot

int time = 1; // Presentation Time in minutes
long timems =  60000;
long updateTime = 1000; //Update for 
boolean ledState = false;
Timer t;
int afterEvent = 0;
int updateEvent = 0;
int oscillateEvent = 0;
int doHalfTimer = 0;
int doAfterTimer = 0;
int doStopGruenLedBlink = 0;
int oscillateGreenEvent = 0;
int oscillateRedEvent = 0;
int doMinuteBeforeEndTimer = 0;

int value, value2;
long millisOld = 0;
int periode = 2000;
int displace = 500;

void setup() {
  // initialize the serial communication:
  Serial.begin(19200);
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  pinMode(timeLED1, OUTPUT); 
  pinMode(timeLED2, OUTPUT);
  pinMode(timeLED3, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonAPin, INPUT);
  attachInterrupt(0, buttonAPressed, RISING); 
  
  pinMode(buttonBPin, INPUT);
  attachInterrupt(1, buttonBPressed, RISING);
  
  digitalWrite(ledPin,HIGH);
  Serial.println("Presenter Start");
  restTimer(20);
}

void loop() {
  t.update();
  
  if (Serial.available() > 0) {
     // read the incoming byte:
     time = Serial.parseInt();
     restTimer(time);           
  }
}

void restTimer(int timeMinutes){
  
     timems = (long) timeMinutes * 60000;
     
     //Reset LEDs
     digitalWrite(timeLED1,LOW);
     digitalWrite(timeLED2,LOW);
     digitalWrite(timeLED3,LOW);
     t.stop(oscillateGreenEvent);
     t.stop(oscillateRedEvent);
     
     //Reset Timers
     t.stop(doHalfTimer);
     t.stop(doMinuteBeforeEndTimer);
     t.stop(doAfterTimer);
     
     
     //Set Timers
     doHalfTimer = t.after(timems / 2, doHalf);
     doMinuteBeforeEndTimer = t.after(timems - (60000) , doMinuteBeforeEnd);
     doAfterTimer = t.after(timems, doAfter);
     //Set Initial Blink
     gruenLedBlink();
     //Serial Output
     Serial.println("Time Resetted");
     Serial.print(time);
     Serial.println(" Minutes");
     Serial.print(timems);
     Serial.println(" MS");
}

void buttonAPressed(){
  Serial.println("Button A Pressed");
}

void buttonBPressed(){
  Serial.println("Button B Pressed");
}

void doHalf(){
  Serial.println("OMG Half Time is up"); 
  gelbLed();
}

void doMinuteBeforeEnd(){
  Serial.println("OMG in one minute is time up"); 
  rotLedBlink();
}

void doAfter(){
  Serial.println("OMG Time is up"); 
  rotLed();
}

void gruenLed(){
  t.stop(oscillateGreenEvent);
  analogWrite(timeLED1,HIGH);
  analogWrite(timeLED3,LOW);
  Serial.println("LED Gruen An");
}

void gruenLedBlink(){  
  Serial.println("LED Gruen blinken");
  oscillateGreenEvent = t.oscillate(timeLED1, 100, LOW,10);
}


void rotLed(){
  t.stop(oscillateRedEvent);
  analogWrite(timeLED1,0);
  analogWrite(timeLED3,255);
  Serial.println("LED Rot An");
}

void gelbLed(){
  analogWrite(timeLED1,128);
  analogWrite(timeLED3,60);
  Serial.println("LED Gelb An");
}


void rotLedBlink(){
  t.stop(oscillateGreenEvent);
  analogWrite(timeLED1,LOW);
  oscillateRedEvent = t.oscillate(timeLED3, 100, LOW,600);
  Serial.println("LED Rot blinken");
}



