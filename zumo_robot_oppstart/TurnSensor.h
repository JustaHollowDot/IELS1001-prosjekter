#ifndef TurnSensor_h
#define TurnSensor_h

class TurnSensor {
    public:
    const long turn_45 = 0x20000000;
    const long turn_90 = 0x40000000;
    const long turn_1 = (0x20000000 + 22) / 45;

    int turn_angle = 0;
    int turn_rate;
    int gyro_offset;
    unsigned long last_update = 0;

    TurnSensor() = default;

    void reset();
    void update();
    void setup();
};

#endif