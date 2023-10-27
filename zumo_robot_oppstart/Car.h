#ifndef Car_h
#define Car_h

#include "TurnSensor.h"

enum class Action {
    MOVE_TIME,
    MOVE_DISTANCE,
    MOVE_TURN_DEGREES,
    MOVE_TURN_WITH_RADIUS,
    MOVE_FOLLOW_LINE,
    NO_ACTION
};

struct Movement {
    Action action;
    unsigned long time_initialized;
    bool move_forward;
    bool is_left;
    int move_time;
    int move_distance;
    int move_degrees;
    unsigned move_radius;
};

class Car {
    public:
    Movement current_movement;
    unsigned max_speed = 100;
    int turn_speed = 50;
    TurnSensor turn_sensor;
    bool turn_sensor_setup = false;
    bool follow_line_setup = false;

    Car() = default;
    bool update();
    void stop_movement();
    void move(int left_speed, int right_speed);
    void turn_degrees();
    void turn_with_radius();
    void follow_line();
    void calibrate_line(bool line_is_black);
    void set_move(int distance = 0, int time = 0, bool drive_forward = true);
    void set_turn_degrees(int degrees);
    void set_turn_with_radius(unsigned radius, int degrees, bool is_left);
    void set_follow_line(bool line_is_black);
};



#endif