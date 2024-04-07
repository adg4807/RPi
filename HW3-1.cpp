#include <iostream>
#include <wiringPi.h>

using namespace std;

#define PIN_TRIG 23
#define PIN_ECHO 24
#define RANGE_MAX 200
#define RANGE_MIN 0 
#define RED_PIN 17
#define GREEN_PIN 18
#define BLUE_PIN 27

void setup() {
    wiringPiSetupGpio();
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

float measure_distance() {
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(PIN_TRIG, LOW);

    while (digitalRead(PIN_ECHO) == LOW);
    unsigned int startTime = micros();
    while (digitalRead(PIN_ECHO) == HIGH);
    unsigned int travelTime = micros() - startTime;

    float distance = travelTime / 58.0;
    return distance;
}

void set_led_color(float distance) {
    if (distance >= 0 && distance < 10) {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
    } else if (distance >= 10 && distance < 15) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
    } else if (distance >= 15 && distance < 30) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
    } else {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
    }
}

int main() {
    setup();

    while (1) {
        float distance = measure_distance();
        cout << "Distance is " << distance << " cm" << endl;
        set_led_color(distance);
        delay(500);
    }

    return 0;
}
