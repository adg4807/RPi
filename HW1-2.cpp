/*
Code source and modifications
¡Ü https://github.com/derekmolloy/exploringrpi.git
*/
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>         

using namespace std;

#define GPIO         "/sys/class/gpio/"
#define FLASH_DELAY  1000000 // 1초

class LED {
private:
    string gpioPath;
    int    gpioNumber;
    void writeSysfs(string path, string filename, string value);

public:
    LED(int gpioNumber);
    void turnOn();
    void turnOff();
    void displayState();
    ~LED();
};

LED::LED(int gpioNumber) {
    this->gpioNumber = gpioNumber;
    gpioPath = string(GPIO "gpio") + to_string(gpioNumber) + string("/");
    writeSysfs(string(GPIO), "export", to_string(gpioNumber));
    usleep(100000);
    writeSysfs(gpioPath, "direction", "out");
}

void LED::writeSysfs(string path, string filename, string value) {
    ofstream fs;
    fs.open((path + filename).c_str());
    fs << value;
    fs.close();
}

void LED::turnOn() {
    writeSysfs(gpioPath, "value", "1");
}

void LED::turnOff() {
    writeSysfs(gpioPath, "value", "0");
}

void LED::displayState() {
    ifstream fs;
    fs.open((gpioPath + "value").c_str());
    string line;
    cout << "The current LED state is ";
    while (getline(fs, line)) cout << line << endl;
    fs.close();
}

LED::~LED() {
    cout << "Destroying the LED with GPIO number " << gpioNumber << endl;
    writeSysfs(string(GPIO), "unexport", to_string(gpioNumber));
}

int main(int argc, char* argv[]) {
    cout << "Starting the LED blinking program" << endl;
    LED leds[] = {LED(4), LED(17), LED(27)};
    int num_leds = sizeof(leds) / sizeof(leds[0]);
    cout << "Blinking the LEDs" << endl;
    
    bool forward = true; // 순방향으로 시작
    int currentLED = 0; // 현재 켜진 LED의 위치

    while(true) {
        // 현재 LED를 켜고 다음 LED로 이동
        leds[currentLED].turnOn();
        usleep(FLASH_DELAY);
        leds[currentLED].turnOff();

        // 순방향일 때
        if (forward) {
            currentLED++; // 다음 LED로 이동
            // 마지막 LED일 경우
            if (currentLED == num_leds) {
                forward = false; // 방향을 반대로 변경
                currentLED = num_leds - 2; // 다음에 켜질 LED는 뒤에서 두 번째
            }
        }
        // 역방향일 때
        else {
            currentLED--; // 이전 LED로 이동
            // 첫 번째 LED일 경우
            if (currentLED < 0) {
                forward = true; // 방향을 순방향으로 변경
                currentLED = 1; // 다음에 켜질 LED는 두 번째
            }
        }
    }

    cout << "Finished the LED blinking program" << endl;
    return 0;
}
