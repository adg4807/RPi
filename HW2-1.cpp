#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;

#define RLED_GPIO 17
#define GLED_GPIO 18
#define YLED_GPIO 27

#define RBUTTON_GPIO 13
#define GBUTTON_GPIO 19
#define YBUTTON_GPIO 26

#define DEBOUNCE_TIME 200

volatile bool rLED_state = false;
volatile bool gLED_state = false;
volatile bool yLED_state = false;

static unsigned long lastISRTime1 = 0;
static unsigned long lastISRTime2 = 0;
static unsigned long lastISRTime3 = 0;

void toggleLEDRed(void) {
    unsigned long currentISRTime1 = millis();
    if (currentISRTime1 - lastISRTime1 > DEBOUNCE_TIME) {
        rLED_state = !rLED_state;
        digitalWrite(RLED_GPIO, rLED_state ? HIGH : LOW);
    }
    lastISRTime1 = currentISRTime1;
}

void toggleLEDGreen(void) {
    unsigned long currentISRTime2 = millis();
    if (currentISRTime2 - lastISRTime2 > DEBOUNCE_TIME) {
        gLED_state = !gLED_state;
        digitalWrite(GLED_GPIO, gLED_state ? HIGH : LOW);
    }
    lastISRTime2 = currentISRTime2;
}

void toggleLEDYellow(void) {
    unsigned long currentISRTime3 = millis();
    if (currentISRTime3 - lastISRTime3 > DEBOUNCE_TIME) {
        yLED_state = !yLED_state;
        digitalWrite(YLED_GPIO, yLED_state ? HIGH : LOW);
    }
    lastISRTime3 = currentISRTime3;
}

int main() {
    wiringPiSetupGpio();
    pinMode(RLED_GPIO, OUTPUT);
    pinMode(GLED_GPIO, OUTPUT);
    pinMode(YLED_GPIO, OUTPUT);

    pinMode(RBUTTON_GPIO, INPUT);
    pinMode(GBUTTON_GPIO, INPUT);
    pinMode(YBUTTON_GPIO, INPUT);

    digitalWrite(RLED_GPIO, LOW);
    digitalWrite(GLED_GPIO, LOW);
    digitalWrite(YLED_GPIO, LOW);

    wiringPiISR(RBUTTON_GPIO, INT_EDGE_FALLING, &toggleLEDRed);
    wiringPiISR(GBUTTON_GPIO, INT_EDGE_FALLING, &toggleLEDGreen);
    wiringPiISR(YBUTTON_GPIO, INT_EDGE_FALLING, &toggleLEDYellow);

    while (1) {
        delay(1000);
    }
    return 0;
}

