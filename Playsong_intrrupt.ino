#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4,8,8,4,4,4,4,4
};
int button_pin = 2;
int led_pin = A1;
int buttonState = 0;
int state = 0;  
int tone_pin = 3; 
String a;

void switchPressed(){
  if (digitalRead (button_pin) == HIGH) {
    buttonState = 1;
    digitalWrite(led_pin, HIGH);
    delay(1000);
  }
  else{
    buttonState = 0;
    digitalWrite(led_pin, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), switchPressed, HIGH);
}

void loop() {
  Serial.print("buttonState:");
  Serial.println(buttonState);
  if (Serial.available()){
    a = Serial.readString();
    a.trim();
    if (a == "1"){    
       for (int thisNote = 0; thisNote <8; thisNote++){
         if (buttonState == 1)
           break;
         int noteDuration = 1000/ noteDurations[thisNote];
         tone(tone_pin, melody[thisNote], noteDuration);
         int pauseBetweenNotes = noteDuration * 1.30;
         delay(pauseBetweenNotes);
         noTone(tone_pin);
         }
    } else {
      Serial.println("not 1");
    }
  }
}


