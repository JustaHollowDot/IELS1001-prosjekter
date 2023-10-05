const unsigned LED_RED = 9;
const unsigned LED_GREEN = 10;
const unsigned LED_BLUE = 11;
const unsigned BUTTON = 3;

const unsigned SENSOR = 0;

const unsigned INTERVAL = 1000;

unsigned long button_held_timer;
bool button_held = false;

unsigned mode = 0;

void setup() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
    unsigned sensor_value = analogRead(SENSOR);

    unsigned long output_value = map(sensor_value, 0, 1023, 0, 256 * 3 - 1);

    if (output_value > 511) {
        analogWrite(LED_BLUE, output_value - 511);
    } else if (output_value > 255) {
        analogWrite(LED_GREEN, output_value - 255);
    } else {
        analogWrite(LED_RED, output_value);
    }

    if (digitalRead(BUTTON) && !button_held) {
        button_held_timer = millis();
        button_held = true;
    } else if (button_held) {
        if (millis() - button_held_timer > 200) {
            mode++;
        }
    }
}