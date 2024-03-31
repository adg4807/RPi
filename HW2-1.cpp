#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

using namespace std;

#define LED_PIN_1 17
#define LED_PIN_2 18
#define LED_PIN_3 27
#define BUTTON_PIN_1 13
#define BUTTON_PIN_2 19
#define BUTTON_PIN_3 26
#define DEBOUNCE_TIME 300 // 디바운싱을 위한 대기 시간 (밀리초)

bool ledState_1 = false;
bool ledState_2 = false;
bool ledState_3 = false;

unsigned long lastButtonPressTime_1 = 0;
unsigned long lastButtonPressTime_2 = 0;
unsigned long lastButtonPressTime_3 = 0;

void toggleLED_1() {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPressTime_1 >= DEBOUNCE_TIME) {
        ledState_1 = !ledState_1;
        digitalWrite(LED_PIN_1, ledState_1 ? HIGH : LOW);
        cout << "Button 1 pressed! LED 1 toggled." << endl;
        lastButtonPressTime_1 = currentTime;
    }
}

void toggleLED_2() {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPressTime_2 >= DEBOUNCE_TIME) {
        ledState_2 = !ledState_2;
        digitalWrite(LED_PIN_2, ledState_2 ? HIGH : LOW);
        cout << "Button 2 pressed! LED 2 toggled." << endl;
        lastButtonPressTime_2 = currentTime;
    }
}

void toggleLED_3() {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPressTime_3 >= DEBOUNCE_TIME) {
        ledState_3 = !ledState_3;
        digitalWrite(LED_PIN_3, ledState_3 ? HIGH : LOW);
        cout << "Button 3 pressed! LED 3 toggled." << endl;
        lastButtonPressTime_3 = currentTime;
    }
}

int main() {
    wiringPiSetupGpio();

    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);
    pinMode(BUTTON_PIN_1, INPUT);
    pinMode(BUTTON_PIN_2, INPUT);
    pinMode(BUTTON_PIN_3, INPUT);

    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);

    cout << "Press buttons on GPIO " << BUTTON_PIN_1 << ", " << BUTTON_PIN_2 << ", " << BUTTON_PIN_3 << endl;

    // Attach interrupts to buttons
    wiringPiISR(BUTTON_PIN_1, INT_EDGE_FALLING, &toggleLED_1);
    wiringPiISR(BUTTON_PIN_2, INT_EDGE_FALLING, &toggleLED_2);
    wiringPiISR(BUTTON_PIN_3, INT_EDGE_FALLING, &toggleLED_3);

    // Main loop
    while (true) {
        // Your main code goes here
        // This loop will keep your program running
        delay(1000); // Delay for stability
    }

    return 0;
}
