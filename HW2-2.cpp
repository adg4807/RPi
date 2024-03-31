 #include <iostream>
 2 #include <wiringPi.h>
 3 #include <unistd.h>
 4 using namespace std;
 5
 6 #define RED_LED       18 // 빨간색 LED
 7 #define GREEN_LED     13 // 녹색 LED
 8
 9 void fadeLED(int ledPin) {
10     for (int i = 0; i <= 1000; ++i) {
11         pwmWrite(ledPin, i);
12         usleep(4080); // 페이드 속도 조절
13     }
14     for (int i = 1000; i >= 0; --i) {
15         pwmWrite(ledPin, i);
16         usleep(4080); // 페이드 속도 조절
17     }
18 }
19
20 int main() {
21     wiringPiSetupGpio();
22     pinMode(RED_LED, PWM_OUTPUT);
23     pinMode(GREEN_LED, PWM_OUTPUT);
24     pwmSetRange(1000);
25
26     cout << "Fading LEDs R, G with a period of 4080 ms" << endl;
27
28     while (true) {
29         fadeLED(RED_LED);
30         fadeLED(GREEN_LED);
31     }
32
33     return 0;
34 }
35
