#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4Encoders encoders;

/*
void Car::update() {
    switch (current_movement.action) {
        case Action::MOVE_TIME:
            move(max_speed, max_speed);

            if (current_movement.time_initialized > millis() - 1000) {
                current_movement.action = Action::NO_ACTION;
            }
            break;

        case Action::MOVE_DISTANCE:
            break;

        case Action::MOVE_TURN_DEGREES:
            if (!turn_sensor_setup) {
                turn_sensor.setup();
                turn_sensor_setup = true;
            }

            turn_degrees();

            turn_sensor.update();

            if (current_movement.move_degrees > 0) {
                if (turn_sensor.turn_angle >= current_movement.move_degrees) {
                    current_movement.action = Action::NO_ACTION;
                }
            } else {
                if (turn_sensor.turn_angle <= current_movement.move_degrees) {
                    current_movement.action = Action::NO_ACTION;
                }
            }
            break;

        case Action::MOVE_TURN_WITH_RADIUS:
            if (!turn_sensor_setup) {
                turn_sensor.setup();
                turn_sensor_setup = true;
            }
            
            turn_with_radius();

            turn_sensor.update();

            if (current_movement.move_degrees > 0) {
                if (turn_sensor.turn_angle >= current_movement.move_degrees) {
                    current_movement.action = Action::NO_ACTION;
                }
            } else {
                if (turn_sensor.turn_angle <= current_movement.move_degrees) {
                    current_movement.action = Action::NO_ACTION;
                }
            }

        case Action::MOVE_FOLLOW_LINE:
            break;

        default:
            stop_movement();
            break;
    }
}


void Car::stop_movement() {
    motors.setSpeeds(0, 0);
}

void Car::move(int left_speed, int right_speed) {
    motors.setSpeeds(max_speed, max_speed);
}

void Car::turn_degrees() {
    if (current_movement.move_degrees > 0) {
        motors.setLeftSpeed(-turn_speed);
        motors.setRightSpeed(turn_speed);
    } else {
        motors.setLeftSpeed(turn_speed);
        motors.setRightSpeed(-turn_speed);
    }
}

void Car::turn_with_radius() {
    float circumference = 2 * PI * current_movement.move_radius;

    float circ_1 = 2 * PI * (current_movement.move_radius - 49);
    float circ_2 = 2 * PI * (current_movement.move_radius + 49);
    float diff_c = circ_2 / circ_1;

    if (current_movement.is_left) {
        move((int)(max_speed*diff_c), max_speed);
    } else {
        move(max_speed, (int)(max_speed*diff_c));
    }
}

void Car::follow_line() {
}

void Car::calibrate_line(bool line_is_black) {
}

void Car::set_move(int distance = 0, int time = 0, bool drive_forward = true) {
    if (distance) {
        current_movement = {
        .action = Action::MOVE_DISTANCE, 
        .time_initialized = millis(), 
        .move_forward = drive_forward,
        .move_distance = distance, 
        };
    } else {
        current_movement = {
        .action = Action::MOVE_TIME,
        .time_initialized = millis(), 
        .move_forward = drive_forward,
        .move_time = time, 
        };
    }
}

void Car::set_turn_degrees(int degrees) {
    current_movement = {
        .action = Action::MOVE_TURN_DEGREES,
        .time_initialized = millis(),
        .move_degrees = degrees,
    };

    turn_sensor.reset();
}

void Car::set_turn_with_radius(unsigned radius, int degrees, bool is_left) {
    current_movement = {
        .action = Action::MOVE_TURN_WITH_RADIUS,
        .time_initialized = millis(),
        .is_left = is_left,
        .move_degrees = degrees,
        .move_radius = radius,
    };

    turn_sensor.reset();
}

void Car::set_follow_line(bool line_is_black) {
}
*/
