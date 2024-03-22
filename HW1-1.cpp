/*
Code source and modifications
● https://github.com/derekmolloy/exploringrpi.git
*/
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>         
using namespace std;
#define GPIO         "/sys/class/gpio/"
#define FLASH_DELAY  1000000

class LED {
private:               
    string gpioPath;     
    int    gpioNumber;
    void writeSysfs(string path, string filename, string value);
public:                 
    LED(int gpioNumber); 
    virtual void turnOn();
    virtual void turnOff();
    virtual void displayState();
    virtual ~LED();     
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
    cout << "Starting the makeLEDs program" << endl;
    LED led1(4), led2(17) ,led3(27);          
    cout << "Flashing the LEDs for 5 seconds" << endl;
    for ( ; ; ) {        
        led1.turnOn();               
        led2.turnOff();              
        led3.turnOff();
        usleep(FLASH_DELAY);        
        led1.turnOff();              
        led2.turnOn();               
        led3.turnOff();
        usleep(FLASH_DELAY);
        led1.turnOff();              
        led2.turnOff();               
        led3.turnOn();
        usleep(FLASH_DELAY);
    }
    led1.displayState();            
    led2.displayState();            
    led3.displayState();
    cout << "Finished the makeLEDs program" << endl;
    return 0;
}
