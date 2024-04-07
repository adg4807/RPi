#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <iomanip>

using namespace std;

#define RED_LED_PIN 16
#define GREEN_LED_PIN 20
#define DHT_GPIO 22
#define LH_THRESHOLD 26
#define TARGET_TEMPERATURE 30.0

int main() {
    cout << "DHT11 sensor program started" << endl;
    wiringPiSetupGpio();
    piHiPri(99);

    while (true) {
        int humid = 0, temp = 0;

    TRYAGAIN:
        unsigned char data[5] = {0, 0, 0, 0, 0};
        pinMode(DHT_GPIO, OUTPUT);
        digitalWrite(DHT_GPIO, LOW);
        usleep(18000);
        digitalWrite(DHT_GPIO, HIGH);
        pinMode(DHT_GPIO, INPUT);

        do { delayMicroseconds(1); } while (digitalRead(DHT_GPIO) == HIGH);
        do { delayMicroseconds(1); } while (digitalRead(DHT_GPIO) == LOW);
        do { delayMicroseconds(1); } while (digitalRead(DHT_GPIO) == HIGH);

        for (int d = 0; d < 5; d++) {
            for (int i = 0; i < 8; i++) {
                do { delayMicroseconds(1); } while (digitalRead(DHT_GPIO) == LOW);
                int width = 0;
                do {
                    width++;
                    delayMicroseconds(1);
                    if (width > 1000) break;
                } while (digitalRead(DHT_GPIO) == HIGH);
                data[d] = data[d] | ((width > LH_THRESHOLD) << (7 - i));
            }
        }

        humid = data[0] * 10;
        temp = data[2] * 10;

        unsigned char chk = 0;
        for (int i = 0; i < 4; i++) { chk += data[i]; }
        if (chk == data[4]) {
            cout << "Checksum is good" << endl;
            cout << "Temperature: " << (float)temp / 10 << "°C" << endl;
            cout << "Humidity: " << (float)humid / 10 << "%" << endl;

            // LED 제어
            if ((float)temp / 10 > TARGET_TEMPERATURE) {
                digitalWrite(RED_LED_PIN, HIGH);
                digitalWrite(GREEN_LED_PIN, LOW);
            } else {
                digitalWrite(GREEN_LED_PIN, HIGH);
                digitalWrite(RED_LED_PIN, LOW);
            }
        } else {
            cout << "Checksum bad - data error - trying again!" << endl;
            usleep(2000000);
            goto TRYAGAIN;
        }

        // 2초 대기 후 다음 반복
        delay(2000);
    }

    return 0;
}
