#ifndef Car_h
#define Car_h

#include "TurnSensor.h"
#include "Positional_data.h"

enum class Action {
    MOVE_TIME,
    MOVE_DISTANCE,
    TURN_DEGREES,
    TURN_WITH_RADIUS,
    FOLLOW_LINE,
    NO_ACTION
};

struct Movement {
    Action action;
    uint32_t time_initialized;
    bool move_forward;
    int16_t move_time;
    int16_t move_distance;
    int16_t move_degrees;
    int16_t move_radius;
};

class Car {
    public:

    Movement current_movement;
    bool turn_sensor_setup = false;
    bool follow_line_setup = false;
    int16_t max_speed = 100;
    int16_t turn_speed = 100;
    int16_t current_speed_left = 0;
    int16_t current_speed_right = 0;

    int16_t correct_speed_left = 0;
    int16_t correct_speed_right = 0;

    TurnSensor turn_sensor;


    Car() = default;
    bool update();
    void stop_movement();
    void move(int16_t left_speed, int16_t right_speed);
    void move_time();
    void move_distance();
    void turn_degrees();
    void turn_with_radius();
    void follow_line();
    void calibrate_line(bool line_is_black);
    void set_move(int16_t distance = 0, int32_t time = 0, bool drive_forward = true);
    void set_turn_degrees(int16_t degrees);
    void set_turn_with_radius(int16_t radius, int16_t degrees);
    void set_follow_line(bool line_is_black);
};



#endif