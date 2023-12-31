#include <Wire.h>
#include <Zumo32U4.h>
#include "Car.h"
  
Zumo32U4ButtonA button_a;
Zumo32U4Encoders encoders;

/*
*/

Car car;

void setup() {
  Serial.begin(9600);
}
 
void loop() {
  for (int i = 0; i < 4; i++) {
    car.set_turn_with_radius(100, 90);

    while (!car.update()) {}
  }

  for (int i = 0; i < 4; i++) {
    car.set_turn_with_radius(100, -90);

    while (!car.update()) {
    }
  }

  delay(500);

  car.set_turn_degrees(180);

  while (!car.update()) {
  }

  delay(500);
}

/*
void turn(int angle) {
  if (angle > 0) {
    motors.setLeftSpeed(-50);
    motors.setRightSpeed(50);
  } else {
    motors.setLeftSpeed(50);
    motors.setRightSpeed(-50);
  }

  for ( ; ; ) {
    turn_sensor.update();

    if (angle > 0) {
      if (turn_sensor.turn_angle >= angle) {
        motors.setSpeeds(0, 0);
        return;
      }
    } else {
      if (turn_sensor.turn_angle <= angle) {
        motors.setSpeeds(0, 0);
        return;
      }
    }

    delay(10);
  }

}

void drive_forward() {
  float distance_left = 0;
  float distance_right = 0;

  motors.setRightSpeed(100);
  motors.setLeftSpeed(100);

  for ( ; ; ) {
    int encoders_amount_right = encoders.getCountsAndResetRight();
    distance_right += encoders_amount_right / counts_per_rev * circumference;

    int encoder_amount_left = encoders.getCountsAndResetLeft();
    distance_left += encoder_amount_left / counts_per_rev * circumference;

    Serial.println(distance_right);
    Serial.println(distance_left);

    if (distance_left > 500) {
      break;
    }

    delay(10);
  }
}
*/