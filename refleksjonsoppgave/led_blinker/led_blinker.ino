const unsigned LED = 9;
const unsigned INTERVAL = 1000;

unsigned long prev_time = 0;
bool is_on = false;


void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    if (millis() - prev_time > INTERVAL) {
        prev_time = millis();

        is_on = !is_on;
    }

    digitalWrite(LED, is_on);
}