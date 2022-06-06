
#include <Servo.h>
int mid = 90;

int LETmax = 120;
int LETmin = 70;
int LEBmax = 135;
int LEBmin = 70;

int RETmax = 120;
int RETmin = 60;
int REBmax = 135;
int REBmin = 75;

int LRmin = 50;
int LRmax = 135;
int LRmid = 85;

int UDmin = 40;
int UDmax = 100;
int UDmid = 90;

unsigned long previousMillis = 0;
const long lang = 10000;
const long kort = 90;
int blinkState = LOW;

Servo leftEyelidTop; //PIN2
Servo leftEyelidButtom; //PIN3
Servo rightEyelidTop; //PIN4
Servo rightEyelidButtom; //PIN5
Servo lefRight; //PIN6
Servo upDown; //PIN7

// ---------------------------------------
// ---------------- SETUP ----------------
// ---------------------------------------

void setup() {
  leftEyelidTop.attach(2);
  leftEyelidButtom.attach(3);
  rightEyelidTop.attach(4);
  rightEyelidButtom.attach(5);
  lefRight.attach(6);
  upDown.attach(7);

  //Åben begge øjne 
  leftEyelidTop.write(LETmax);
  leftEyelidButtom.write(LEBmin);
  rightEyelidTop.write(RETmin);
  rightEyelidButtom.write(REBmax);
  
  //Øjne i midsten
  lefRight.write(LRmid);
  upDown.write(UDmid);
  
  }


// --------------------------------------
// ---------------- LOOP ----------------
// --------------------------------------

void loop() {
  blinkHV();
  
}


// ---------------------------------------
// ---------------- BLINK ----------------
// ---------------------------------------

void blinkHV() {
  //Åben begge øjne
  leftEyelidTop.write(LETmax);
  leftEyelidButtom.write(LEBmin);
  rightEyelidTop.write(RETmin);
  rightEyelidButtom.write(REBmax);
  
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= lang) {
    previousMillis = currentMillis;
    
    //Luk begge øjen
    leftEyelidTop.write(LETmin);
    leftEyelidButtom.write(LEBmax);
    rightEyelidTop.write(RETmax);
    rightEyelidButtom.write(REBmin);
    delay(200);
  }
}




void blinkV() {
  leftEyelidTop.write(LETmax);
  leftEyelidButtom.write(LEBmin);
  delay(3000);
  leftEyelidTop.write(LETmin);
  leftEyelidButtom.write(LEBmax);
  delay(90);
}

void blinkH() {
  rightEyelidTop.write(RETmin);
  rightEyelidButtom.write(REBmax);
  delay(3000);
  rightEyelidTop.write(RETmax);
  rightEyelidButtom.write(REBmin);
  delay(90);
}


void HVscan() {
  lefRight.write(LRmin); //(Kig til Højre)
  delay(1000);
  lefRight.write(LRmax); //(Kig til Venstre)
  delay(1000);
}
