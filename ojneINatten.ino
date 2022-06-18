#include <Arduino.h>
#include <Servo.h>
#include "ServoEasing.hpp"
#include "PinDefinitionsAndMore.h"

int potXpin = A0; //GRØN (OP/NED)
int potYpin = A1; //BLÅ (HØJRE/VENSTRE)
int valHV;
int valON;

int mid = 90;

int LETmax = 120;
int LETmin = 70;
int LEBmax = 135;
int LEBmin = 70;

int RETmax = 120;
int RETmin = 60;
int REBmax = 135;
int REBmin = 75;

int LRmin = 40; //Kigger til højre
int LRmax = 120; //Kigger til venstre
int LRmid = 85;

int UDmin = 50; //Kigger ned
int UDmax = 111; //Kigger op
int UDmid = 90; 

unsigned long previousBlinkMillis = 0;
unsigned long previousScanMillis = 0;

const long lang = 10000;
const long scanInterval = 1000;
int scanState = LOW;

ServoEasing leftEyelidTop; //PIN2
ServoEasing leftEyelidButtom; //PIN3
ServoEasing rightEyelidTop; //PIN4
ServoEasing rightEyelidButtom; //PIN5
ServoEasing lefRight; //PIN6
ServoEasing upDown; //PIN7

/*
Servo leftEyelidTop; //PIN2
Servo leftEyelidButtom; //PIN3
Servo rightEyelidTop; //PIN4
Servo rightEyelidButtom; //PIN5
Servo lefRight; //PIN6
Servo upDown; //PIN7
*/

// ---------------------------------------
// ---------------- SETUP ----------------
// ---------------------------------------

void setup() {
  //ÅBNER BEGGE ØJNE OG SÆTTER DEM I MIDTER POSITION
  
  leftEyelidTop.setEasingType(EASE_QUARTIC_OUT);
  leftEyelidTop.attach(2, LETmax);
  //leftEyelidTop.attach(2);

  leftEyelidButtom.setEasingType(EASE_QUARTIC_OUT);
  leftEyelidButtom.attach(3, LEBmin);  
  //leftEyelidButtom.attach(3);
  
  rightEyelidTop.setEasingType(EASE_QUARTIC_OUT);
  rightEyelidTop.attach(4, RETmin);
  //rightEyelidTop.attach(4);
  
  rightEyelidButtom.setEasingType(EASE_QUARTIC_OUT);
  rightEyelidButtom.attach(5, REBmax);
  //rightEyelidButtom.attach(5);
  
  lefRight.setEasingType(EASE_QUARTIC_OUT);
  lefRight.attach(6, LRmid);
  //lefRight.attach(6);
  
  upDown.setEasingType(EASE_QUARTIC_OUT);
  upDown.attach(7, UDmid);
  //upDown.attach(7);

  //Åben begge øjne 
  //leftEyelidTop.write(LETmax);
  //leftEyelidButtom.write(LEBmin);
  //rightEyelidTop.write(RETmin);
  //rightEyelidButtom.write(REBmax);
  
  //Øjne i midsten
  //lefRight.write(LRmid);
  //upDown.write(UDmid);

  Serial.begin(115200);
  
  }


// --------------------------------------
// ---------------- LOOP ----------------
// --------------------------------------

void loop() {
blinkHV();
joystick();
}

// ------------------------------------------
// ---------------- JOYSTICK ----------------
// ------------------------------------------
void joystick() {
  valHV = analogRead(potYpin);
  valHV = map(valHV, 0, 909, LRmin, LRmax);
  Serial.println(valHV);
  valON = analogRead(potXpin);
  valON = map(valON, 909, 0, UDmin, UDmax);
  //Serial.println(valON);
  
  lefRight.easeTo(valHV, 100);
  upDown.easeTo(valON, 100);
  
  delay(15);  
}

// ------------------------------------------
// ---------------- BLINK HW ----------------
// ------------------------------------------

void blinkHV() {
  //Åben begge øjne
leftEyelidTop.write(LETmax);
leftEyelidButtom.write(LEBmin);
rightEyelidTop.write(RETmin);
rightEyelidButtom.write(REBmax);
  
  unsigned long currentBlinkMillis = millis();
  
  if (currentBlinkMillis - previousBlinkMillis >= lang) {
    previousBlinkMillis = currentBlinkMillis;
    
    //Luk begge øjen
    leftEyelidTop.write(LETmin);
    leftEyelidButtom.write(LEBmax);
    rightEyelidTop.write(RETmax);
    rightEyelidButtom.write(REBmin);
    
    delay(100);
  }
}

void luk() {
    leftEyelidTop.easeTo(LETmin, 200);
    leftEyelidButtom.easeTo(LEBmax, 200);
    rightEyelidTop.easeTo(RETmax, 200);
    rightEyelidButtom.easeTo(REBmin, 200);
}

void aaben() {
    leftEyelidTop.easeTo(LETmax, 200);
    leftEyelidButtom.easeTo(LEBmin, 200);
    rightEyelidTop.easeTo(RETmin, 200);
    rightEyelidButtom.easeTo(REBmax, 200);
}

// ---------------------------------------
// ---------------- SCAN -----------------
// ---------------------------------------

void HVscan() {
  unsigned long currentScanMillis = millis();
  if (currentScanMillis - previousScanMillis >= scanInterval) {
    previousScanMillis = currentScanMillis;

    if (scanState == LOW) {
      scanState = HIGH;
      } else {
        scanState = LOW;
    }
  }

  if (scanState == LOW) {
    lefRight.easeTo(LRmin, 100); //(Kig til Højre)
    //lefRight.write(LRmin); //(Kig til Højre)
  }

  if (scanState == HIGH) {
    lefRight.easeTo(LRmax, 100); //(Kig til Venstre)
    //lefRight.write(LRmax); //(Kig til Venstre)
  }

}


// ----------------------------------------
// ---------------- ANDET -----------------
// ----------------------------------------

void blinkV() {
  leftEyelidTop.easeTo(LETmax, 100);
  leftEyelidButtom.easeTo(LEBmin, 100);
  delay(3000);
  leftEyelidTop.easeTo(LETmin, 100);
  leftEyelidButtom.easeTo(LEBmax, 100);
  delay(90);

  //leftEyelidTop.write(LETmax);
  //leftEyelidButtom.write(LEBmin);
  //delay(3000);
  //leftEyelidTop.write(LETmin);
  //leftEyelidButtom.write(LEBmax);
  //delay(90);
}

void blinkH() {
  rightEyelidTop.easeTo(RETmin, 100);
  rightEyelidButtom.easeTo(REBmax, 100);
  delay(3000);
  rightEyelidTop.easeTo(RETmax, 100);
  rightEyelidButtom.easeTo(REBmin, 100);
  delay(90);

  //rightEyelidTop.write(RETmin);
  //rightEyelidButtom.write(REBmax);
  //delay(3000);
  //rightEyelidTop.write(RETmax);
  //rightEyelidButtom.write(REBmin);
  //delay(90);
}
