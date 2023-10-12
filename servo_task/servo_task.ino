#include <Servo.h>

const int servoPinH = 9;
const int servoPinV = 10;
const int t = 1000;

Servo servo_h;
Servo servo_v;

int scale = 20;

float test[4] = {0.5757789167546983, 0.7658098256321973, 1.0, 0.9286357056222857};
int ph_values[4];
int highest_ph_index[2];
int max_ph_average = 0;

float light_vec[2] = {360,90};

void setup() {
    Serial.begin(9600);
    servo_h.attach(servoPinH);
    servo_v.attach(servoPinV);
}

void loop() {
    rotate_vector();
    Serial.print(light_vec[0]);
    Serial.print(" ");
    Serial.println(light_vec[1]);
    delay(10);
    /*
    for (int i = 0; i < 180; i += 20) {
        servo_v.write(i);

        for (int j = 0; j < 180; j += 20) {
            servo_h.write(j);

            int average = get_data_with_sum_ph();

            if (average > max_ph_average) {
                max_ph_average = average;

                highest_ph_index[0] = i;
                highest_ph_index[1] = j;
            }

            delay(100);
        }

        i += 20;
        servo_v.write(i);

        for (int j = 180; j > 0; j -= 20) {
            servo_h.write(j);

            int average = get_data_with_sum_ph();
            
            if (average > max_ph_average) {
                max_ph_average = average;

                highest_ph_index[0] = i;
                highest_ph_index[1] = j;
            }

            delay(100);
        }
    }

    Serial.println(highest_ph_index[0]);
    Serial.println(highest_ph_index[1]);

    servo_v.write(highest_ph_index[0]);
    servo_h.write(highest_ph_index[1]);

    for (int i = 0; i < 1000; i++){
        get_data_with_sum_ph();
        Serial.print(ph_values[0]);
        Serial.print(" ");
        Serial.print(ph_values[1]);
        Serial.print(" ");
        Serial.print(ph_values[2]);
        Serial.print(" ");
        Serial.print(ph_values[3]);
        Serial.println();

        delay(100);

    }
    delay(-1);*/
}


int get_data_with_sum_ph() {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        ph_values[i] = analogRead(i + 2) / test[i];
        sum += ph_values[i];
    }

    return sum;
}

void rotate_motors(){
    int direction = 0;
    if (light_vec[0] > 180){
        direction = 1;
    }

    if (direction == 0){
        servo_h.write(light_vec[0]);
        servo_v.write(light_vec[1]);

        while (servo_h.read() != light_vec[0] && servo_v.read() != light_vec[1]) {
            delay(1);
        }
    } else {
        servo_h.write(180-light_vec[0]);
        servo_v.write(180-light_vec[1]);

        while (servo_h.read() != 180 - light_vec[0] && servo_v.read() != 180 - light_vec[1]) {
            delay(1);
        }
    }
}

void rotate_vector(){
    get_data_with_sum_ph();
    rotate_motors();//align the senors to the current vector
    //light_vec er motorens vinkel, x aksen er 360, y aksen er maks 90
    int direction = 0;
    if (light_vec[0] > 180){
        direction = 1;
    }

    //y aksen 0 er ned opp er 90
    if (direction == 0){
        light_vec[1] += ((ph_values[1] + ph_values[2]) - (ph_values[0] + ph_values[3]))/scale;

        light_vec[0] += ((ph_values[3] + ph_values[2]) - (ph_values[0] + ph_values[1]))/scale;

    }else{
        //opp ned
        light_vec[1] += ((ph_values[0] + ph_values[3]) - (ph_values[1] + ph_values[2]))/scale;

        light_vec[0] += ((ph_values[0] + ph_values[1]) - (ph_values[3] + ph_values[2]))/scale;

    }

    light_vec[0] = fmod(light_vec[0], 360);
    light_vec[1] = fmod(max(light_vec[1],0), 180);
    //light_vec[0] %= 360; 
    //auto temp = light_vec[0];
    //light_vec[0] = temp%360;

    



}