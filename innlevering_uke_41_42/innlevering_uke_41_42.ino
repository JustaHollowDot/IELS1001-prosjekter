const unsigned num_values = 5;
const unsigned SENSOR_PIN = 2;
const unsigned RED_PIN = 3;
const unsigned YELLOW_PIN = 4;
const unsigned GREEN_PIN = 5;
const unsigned BUTTON = 6;

int values[num_values] = {0};
int values_2[num_values] = {0};

int index = 0;
int sum_2 = 0;


unsigned interval = 850;
bool is_red = true;
bool blink = true;
bool is_on = false;
bool is_on_2 = false;
bool button_held = false;
unsigned button_held_timer;
unsigned prev_time;
unsigned prev_time_2;


void blink_leds() {
    if (millis() - prev_time > interval) {
        is_on = !is_on;
        digitalWrite(YELLOW_PIN, is_on);

        prev_time = millis();
    }

    if (blink && millis() - prev_time_2 > interval / 3) {
        is_on_2 = !is_on_2;

        if (is_red) {
            digitalWrite(RED_PIN, is_on_2);
        } else {
            digitalWrite(GREEN_PIN, is_on_2);
        }

        prev_time_2 = millis();
    }

    if (digitalRead(BUTTON)) {
        if (button_held) {
            if (millis() - button_held_timer > 2000) {
                blink = !blink;

                if (!blink) {
                    is_on_2 = true;
                }
            }
        } else {
            button_held_timer = millis();
            button_held = true;
        }
    } else {
        if (button_held && millis() - button_held_timer < 2000) {
            if (is_red) {
                digitalWrite(RED_PIN, LOW);
            } else {
                digitalWrite(GREEN_PIN, LOW);
            }

            is_red = !is_red;

            if (is_red) {
                digitalWrite(RED_PIN, is_on_2);
            } else {
                digitalWrite(GREEN_PIN, is_on_2);
            }
        }
        button_held = false;
    }
}


void setup() {
    prev_time = millis();
    prev_time_2 = millis();
}

void loop() {
    int sum = 0;
    for (int i = 0; i < num_values; i++) {
        values[i] = analogRead(SENSOR_PIN);
        sum += values[i];
    }

    Serial.println(sum / num_values);

    int new_value = analogRead(SENSOR_PIN);

    sum_2 += new_value;
    sum_2 -= values_2[index];

    values_2[index] = new_value;

    index++;
    index %= num_values;
}