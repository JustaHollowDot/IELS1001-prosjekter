#include "Adafruit_NeoPixel.h"

#define PIN 2
#define NUMPIXELS 32
#define ENDZONE 5
#define WINS_NEEDED 10
#define LEFT_BUTTON 3
#define RIGHT_BUTTON 4

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long ball_color = pixels.Color(255, 0, 0);
unsigned long left_color = pixels.Color(0, 255, 0);
unsigned long right_color = pixels.Color(0, 0, 255);

bool button_delay = 100;
bool left_pressed = false;
bool right_pressed = false;
unsigned left_timer;
unsigned right_timer;
unsigned left_points = 0;
unsigned right_points = 0;
unsigned ball_pos;
int speed;

enum Direction {
    right = 1,
    left = -1,
};

enum Ball_state {
    out_left,
    out_right,
    left_endzone,
    right_endzone,
    neutral_zone,
};

enum Button_state {
    left_click,
    right_click,
    no_click,
};

void color_endzone() {
    for (int i = 0; i < ENDZONE; i++) {
        pixels.setPixelColor(i, left_color);
        pixels.setPixelColor(NUMPIXELS - i - 1, right_color);
    }
}

unsigned update_ball() {
    ball_pos += speed;

    pixels.setPixelColor(ball_pos, ball_color);

    if (ball_pos < 0) {
        return Ball_state::out_left;
    } else if (ball_pos >= NUMPIXELS) {
        return Ball_state::out_right;
    } else if (ball_pos < ENDZONE) {
        return Ball_state::left_endzone;
    } else if (ball_pos > NUMPIXELS - ENDZONE - 1) {
        return Ball_state::right_endzone;
    } else {
        return Ball_state::neutral_zone;
    }

}

void reverse_ball() {
    if (speed == right) {
        speed = Direction::left;
    } else {
        speed = Direction::right;
    }
}

unsigned get_button_press() {
    if (left_pressed && left_timer < millis() - 200) {
        left_pressed = false;
    }

    if (digitalRead(LEFT_BUTTON) && !left_pressed) {
        left_pressed = true;
        left_timer = millis();
        return Button_state::left_click;
    }

    if (right_pressed && right_timer < millis() - 200) {
        right_pressed = false;
    }

    if (digitalRead(RIGHT_BUTTON) && !right_pressed) {
        right_pressed = true;
        right_timer = millis();
        return Button_state::right_click;
    }

    return Button_state::no_click;
}

void play_round() {
    unsigned interval_micro = 1000000;
    unsigned initial_interval = interval_micro;
    unsigned long prev_time = micros();

    while (true) {
        if (prev_time < micros() - interval_micro) {
            pixels.clear();
            color_endzone();

            unsigned ball_result = update_ball();
            unsigned button_result = get_button_press();

            if (ball_result == Ball_state::out_left) {
                right_points++;
                return;
            } else if (ball_result == Ball_state::out_right) {
                left_points++;
                return;
            }

            if (button_result == Button_state::left_click) {
                if (ball_result == Ball_state::left_endzone) {
                    reverse_ball();

                    interval_micro -= interval_micro / initial_interval;
                } else {
                    right_points++;
                    return;
                }
            }

            if (button_result == Button_state::right_click) {
                if (ball_result == Ball_state::right_endzone) {
                    reverse_ball();

                    interval_micro -= interval_micro / initial_interval;
                } else {
                    left_points++;
                    return;
                }
            }
        }
    }
}

void display_points() {
    unsigned middle = NUMPIXELS / 2;

    for (int i = 0; i < left_points; i++) {
        pixels.setPixelColor(middle - i, left_color);
        delay(100);
    }

    for (int i = 0; i < right_points; i++) {
        pixels.setPixelColor(middle + 1 + i, right_color);
        delay(100);
    }

    delay(3000);
}

void setup() {
    Serial.begin(9600);
    pixels.begin();

    ball_pos = ENDZONE;
    speed = Direction::right;

    pinMode(LEFT_BUTTON, INPUT);
    pinMode(RIGHT_BUTTON, INPUT);
}



void loop() {
    while (left_points < WINS_NEEDED && right_points < WINS_NEEDED) {
        play_round();

        display_points();
    }
}