#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <SharpIR.h>
#include <tcs3200.h>
byte count = 0;


byte standby = 1;
byte Start = 2;
byte Corner0 = 3;
byte Corner1 = 4;
byte Forward = 5;
unsigned long previousMillis = 0;
const unsigned long interval = 500;
byte state = standby;
// byte stop = 1;
// byte wait = 2;
// byte search = 3;
// byte drattack = 4;
// byte l = 5;
// ...
// byte state = stop;

// // SoftwareSerial mySerial1(, );  // RX, TX
HUSKYLENS huskylens;
const float REAL_WIDTH_CM = 5.0;
const float FOCAL_LENGTH = 410;  //for the distance of the camera

//right motor
#define O1R 3
#define O2R 5

//steer motor
#define sdsz 6
#define O2L 9

#define PB A0

// Right sensor
#define TRIG1 2
#define ECHO1 4
// Middle Sensor
#define TRIG2 48
#define ECHO2 46
// Left sensor
#define TRIG3 11
#define ECHO3 10

#define OUT 44
#define S3 43
#define S2 42
#define S1 41
#define S0 40
tcs3200 tcs(S0, S1, S2, S3, OUT);

int count = 0;


void setup() {
  // Serial1.begin(9600);
  // Serial.begin(9600);

  pinMode(sdsz, OUTPUT);
  pinMode(O2L, OUTPUT);
  pinMode(O1R, OUTPUT);
  pinMode(O2R, OUTPUT);

  pinMode(PB, INPUT_PULLUP)

    pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
  // if (!huskylens.begin(Serial1)) {
  //   Serial.println("HUSKYLENS not connected!");
  //   while (1)
  //     ;

  //   Serial.println("HUSKYLENS connected. Estimating distance...");
  // }
}

void loop() {
  float distance1 = getDistance(TRIG1, ECHO1);
  float distance2 = getDistance(TRIG2, ECHO2);
  float distance3 = getDistance(TRIG3, ECHO3);
  int red, green, blue, white;
  // if(state == stop){
  //   stop
  //   state = wait;
  // }
  // if(state == wait){
  //   del 5000
  //   state = search;
  // }
  // if(state == search){
  //   if(L == low && high){
  //     state = L;
  //   }
  // }
  // if(state == L){
  //   turn left
  //   if(f ==LOW){
  //     state = F;
  //   }
  // }
  // if(red > 15 && red < 30 && green > 5 && green < 15 && blue > 5 && blue < 15){
  //   count+=1;
  // }
  if (count < 12) {
    if (state == standby) {
      //action
      DriveSpeed(0);
      //transition
      if (digitalRead(PB) == LOW) {
        state = Start
      }
    }
    if (state == Start) {
      //action
      DriveSpeed(100);

      //Transition
      if (red > 5 && red < 15 && green > 8 && green < 15 && blue > 13 && blue < 25) {
        count +=1
        state = Corner0
      }
      if (red > 15 && red < 45 && green > 8 && green < 20 && blue > 5 && blue < 17){
        count +=1
        state = Corner1
      }
    }
    if (state == Corner0) {
      //action
      Stear(50);
      delay(500);
      Stear(-50);
       millis();
      //transition
      state = Forward
      
    }
    if (state == Corner1){
      //action
      Stear(-50);
      delay(500);
      Stear(50);
       millis();
      //transition
      state = Forward
    }
    if (state == Forward){
      //action
      DriveSpeed(100);

      if (millis() - previousMillis >= interval){
        state = Start
      }
    }
    if (count = 12){
      state = Forward
    }




    // put your main code here, to run repeatedly:


    // Serial.print("Sensor 1: ");
    // Serial.print(distance1);
    // Serial.print(" cm\t");

    // Serial.print("Sensor 2: ");
    // Serial.print(distance2);
    // Serial.print(" cm\t");

    // Serial.print("Sensor 3: ");
    // Serial.print(distance3);
    // Serial.println(" cm");


    // if (huskylens.request()) {
    //   while (huskylens.available()) {
    //     HUSKYLENSResult result = huskylens.read();
    //     int width_px = result.width;

    //     if (width_px > 0) {
    //       float distance_cm = (REAL_WIDTH_CM * FOCAL_LENGTH) / width_px;

    //       Serial.print("Width (px): ");
    //       Serial.print(width_px);
    //       Serial.print(" | Distance (cm): ");
    //       Serial.println(distance_cm);
    //     } else {
    //       Serial.println("Object width = 0. Can't calculate distance.");
    //     }
    //   }
    // } else {
    //   Serial.println("No object detected.");
    // }

    // red = tcs.colorRead('r');   //reads color value for red
    // Serial.print("R= ");
    // Serial.print(red);
    // Serial.print("    ");

    // green = tcs.colorRead('g');   //reads color value for green
    // Serial.print("G= ");
    // Serial.print(green);
    // Serial.print("    ");

    // blue = tcs.colorRead('b');    //reads color value for blue
    // Serial.print("B= ");
    // Serial.print(blue);
    // Serial.print("    ");

    // white = tcs.colorRead('c');    //reads color value for white(clear)
    // Serial.print("W(clear)= ");
    // Serial.print(white);
    // Serial.print("    ");

    // Serial.println();


    // if(red > 30 && green > 30 && blue > 30){
    // // digitalWrite(13, HIGH);
    // Serial.println("White");
    // }
    // else if(red > 5 && red < 15 && green > 8 && green < 15 && blue > 13 && blue < 25){
    //   // digitalWrite(13, HIGH);
    //   // delay(100);
    //   // digitalWrite(13, LOW);
    //   // delay(100);
    //   Serial.println("Blue")
    // };
    // else if(red > 15 && red < 45 && green > 8 && green < 20 && blue > 5 && blue < 17){
    //   // digitalWrite(13, HIGH);
    //   // delay(1000);
    //   // digitalWrite(13, LOW);
    //   // delay(1000);
    //   Serial.println("Orange");
    // }
    // else{
    //   // digitalWrite(13, LOW);
    //   Serial.println("Floating");
    // }
    // DriveSpeed(100);
    // delay(500);
    // DriveSpeed(100);
    // Stear(50);
    // //DriveSpeed(100);
    // delay(500);
    // DriveSpeed(100);
    // Stear(-50);
    // delay(500);
    //DriveSpeed(-100);
    // delay(500);
  }



  void Stear(int speed) {

    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;


    if (speed > 0) {
      analogWrite(sdsz, int(abs(speed) * 2));
      digitalWrite(O2L, LOW);

    } else {

      digitalWrite(sdsz, LOW);
      analogWrite(O2L, int(abs(speed) * 2));
    }
  }

  void DriveSpeed(int speed) {

    if (speed > 100) speed = 100;
    if (speed < -100) speed = -100;


    if (speed > 0) {
      analogWrite(O1R, int(abs(speed) * 2));
      digitalWrite(O2R, LOW);

    } else {

      digitalWrite(O1R, LOW);
      analogWrite(O2R, int(abs(speed) * 2));
    }
  }
  void TurnLeft() {
  }

  // float getDistance(int trigPin, int echoPin) {
  //   digitalWrite(trigPin, LOW);
  //   delayMicroseconds(2);
  //   digitalWrite(trigPin, HIGH);
  //   delayMicroseconds(10);
  //   digitalWrite(trigPin, LOW);

  //   long duration = pulseIn(echoPin, HIGH);
  //   float distance = duration * 0.034 / 2;  // Convert to cm
  //   return distance;
