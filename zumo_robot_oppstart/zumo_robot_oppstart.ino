#include <Wire.h>
#include <Zumo32U4.h>
#include "Car.h"
  
Zumo32U4ButtonA button_a;

/*
class SimpleMovingAverage {
    int dataset[10] = {0};
    int idx;
    double sum;
    
    public:

    SimpleMovingAverage() = default;
    
    void addData(double num)
    {
        sum += num;
        sum -= dataset[idx];

        idx++;
        idx %= 10;
    }
    
    double getMean() const { return sum / 10; }
};
*/

Car car;

void setup() {
  Serial.begin(9600);
}

  
void loop() {
  car.set_move(0, 500, true);

  while (!car.update());

  delay(500);

  car.set_move(0, 500, false);

  while (!car.update());

  delay(500);
  

  /*
  car.set_turn_degrees(-90);

  while (car.current_movement.action != Action::NO_ACTION) {
    car.update();
  }
*/
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