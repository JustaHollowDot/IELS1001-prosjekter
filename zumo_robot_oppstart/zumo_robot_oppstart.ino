#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4Motors motors;
Zumo32U4Encoders encoders;
Zumo32U4IMU imu;
Zumo32U4ButtonA button_a;

const float radius = 39 / 2;
const float counts_per_rev = 909.7;
const float circumference = 2*3.1415*radius;

enum class Action {
  MOVE_TIME,
  MOVE_DISTANCE,
  MOVE_DEGREES
};

struct Movement {
  int time_initialized;
  int move_time;
  int move_distance;
  int move_degrees;
};

class Car {
  public:

  Car() {
    encoders.init();
  }

  void update() {

  }

  void move(int left_speed, int right_speed /*, int distance, int time*/) {
    motors.setSpeeds(left_speed, right_speed);
  }

  void turn(int degrees) {
  if (degrees > 0) {
    motors.setLeftSpeed(-50);
    motors.setRightSpeed(50);
  } else {
    motors.setLeftSpeed(50);
    motors.setRightSpeed(-50);
  }

  for ( ; ; ) {
    turn_sensor.update();

    if (degrees > 0) {
      if (turn_sensor.turn_angle >= degrees) {
        motors.setSpeeds(0, 0);
        return;
      }
    } else {
      if (turn_sensor.turn_angle <= degrees) {
        motors.setSpeeds(0, 0);
        return;
      }
    }

    delay(10);
  }
  }
};

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

class TurnSensor {
  public:
  long turn_45 = 0x20000000;
  long turn_90 = 0x40000000;
  long turn_1 = (0x20000000 + 22) / 45;

  int turn_angle = 0;
  int turn_rate;
  int gyro_offset;
  unsigned long last_update = 0;

  TurnSensor() = default;

  void reset()  {
    last_update = micros();
    turn_angle = 0;
  }

  void update() {
    imu.readGyro();

    turn_rate = imu.g.z - gyro_offset;

    unsigned long m = micros();
    unsigned long dt = m - last_update;
    last_update = m;

    long int  d = turn_rate * dt;

    turn_angle += d * 14680064 / 17578125;
  }

  void setup() {
    imu.init();
    imu.enableDefault();
    imu.configureForTurnSensing();

    int total = 0;
    for (int i = 0; i < 1024; i++) {
      while (!imu.gyroDataReady()) {}
      imu.readGyro();

      total += imu.g.z;
    }

    gyro_offset = total / 1024;

    reset();
  }
};

TurnSensor turn_sensor;

void setup() {
  Serial.begin(9600);



  /*
  encoders.init();

  Serial.println("test3");
  button_a.waitForButton();
  Serial.println("waited");


  Serial.println("test2");
  turn_sensor.setup();
  delay(500);
  Serial.println("test2");
  turn_sensor.reset();
  Serial.println("test2");
*/
}

Car car;
  
void loop() {

  /*
  Serial.println("test");
  turn(90);
  delay(100);
  turn(-90);
  delay(100);
*/
}

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
