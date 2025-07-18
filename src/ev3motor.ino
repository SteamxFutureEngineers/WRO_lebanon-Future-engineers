//left
#define O1L 10
#define O2L 9

//right
#define O1R 5
#define O2R 3

void setup() {
  pinMode(O1L, OUTPUT);
  pinMode(O2L, OUTPUT);

  pinMode(O1R, OUTPUT);
  pinMode(O2R, OUTPUT);
}

void loop() {
  lMotorSpeed(100);
  RMotorSpeed(60);
}

void lMotorSpeed(int speed) {

  if (speed > 100) speed = 100;
  if (speed < -100) speed = -100;


  if (speed > 0) {
    analogWrite(O1L, int(abs(speed) * 2));
    digitalWrite(O2L, LOW);

  } else {

    digitalWrite(O1L, LOW);
    analogWrite(O2L, int(abs(speed)*2));
  }
}

void RMotorSpeed(int speed) {

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



