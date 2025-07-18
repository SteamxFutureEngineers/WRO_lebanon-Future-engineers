#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

SoftwareSerial mySerial(10, 11); // RX, TX
HUSKYLENS huskylens;

// Your calibrated focal length
const float FOCAL_LENGTH = 410;

// Real-world width of the object in centimeters
const float REAL_WIDTH_CM = 5.0; // <-- Change to your actual object's width if needed

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  if (!huskylens.begin(mySerial)) {
    Serial.println("HUSKYLENS not connected!");
    while (1);
  }

  Serial.println("HUSKYLENS connected. Estimating distance...");
}

void loop() {
  if (huskylens.request()) {
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int width_px = result.width;

      if (width_px > 0) {
        float distance_cm = (REAL_WIDTH_CM * FOCAL_LENGTH) / width_px;

        Serial.print("Width (px): "); Serial.print(width_px);
        Serial.print(" | Distance (cm): "); Serial.println(distance_cm);
      } else {
        Serial.println("Object width = 0. Can't calculate distance.");
      }
    }
  } else {
    Serial.println("No object detected.");
  }

  delay(200);
}
