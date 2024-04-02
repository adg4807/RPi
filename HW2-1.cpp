#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;

#define RLED_GPIO      17
#define RBUTTON_GPIO   13
#define GLED_GPIO      27
#define GBUTTON_GPIO   19 
#define YLED_GPIO      18
#define YBUTTON_GPIO   26 

#define DEBOUNCE_TIME 300
bool stateRLED =false;
bool stateGLED =false;
bool stateYLED =false;


void lightRLED(void){
  static unsigned long lastISRTime = 0,  num = 1;
  unsigned long currentISRTime = millis();
  if(currentISRTime - lastISRTime > DEBOUNCE_TIME){
    digitalWrite(RLED_GPIO, !stateRLED);     
    stateRLED = !stateRLED;
    if(stateRLED)
      cout << "Red Button pressed " << num++ << " times! RedLED on" << endl;
    else
      cout << "Red Button pressed " << num++ << " times! RedLED off" << endl;
  }
  lastISRTime = currentISRTime;
}

void lightGLED(void){
  static unsigned long lastISRTime = 0,  num = 1;
  unsigned long currentISRTime = millis();
  if(currentISRTime - lastISRTime > DEBOUNCE_TIME){
    digitalWrite(GLED_GPIO, !stateGLED);     
    stateGLED = !stateGLED;
    if(stateGLED)
      cout << "Green Button pressed " << num++ << " times! GreenLED on" << endl;
    else
      cout << "Green Button pressed " << num++ << " times! GreenLED off" << endl;
  }
  lastISRTime = currentISRTime;
}

void lightYLED(void){
  static unsigned long lastISRTime = 0,  num = 1;
  unsigned long currentISRTime = millis();
  if(currentISRTime - lastISRTime > DEBOUNCE_TIME){
    digitalWrite(YLED_GPIO, !stateYLED);     
    stateYLED = !stateYLED;
    if(stateYLED)
      cout << "Yellow Button pressed " << num++ << " times! YellowLED on" << endl;
    else
      cout << "Yellow Button pressed " << num++ << " times! YellowLED off" << endl;
  }
  lastISRTime = currentISRTime;
}

int main() {                             
  wiringPiSetupGpio();                  
  pinMode(RLED_GPIO, OUTPUT);  
  pinMode(GLED_GPIO, OUTPUT);
  pinMode(YLED_GPIO, OUTPUT);
  pinMode(RBUTTON_GPIO, INPUT);
  pinMode(GBUTTON_GPIO, INPUT);
  pinMode(YBUTTON_GPIO, INPUT);
  digitalWrite (RLED_GPIO, LOW);
  digitalWrite (GLED_GPIO, LOW);
  digitalWrite (YLED_GPIO, LOW);
  
  wiringPiISR(RBUTTON_GPIO, INT_EDGE_RISING, &lightRLED);
  wiringPiISR(GBUTTON_GPIO, INT_EDGE_RISING, &lightGLED);
  wiringPiISR(YBUTTON_GPIO, INT_EDGE_RISING, &lightYLED);
  for(; ; ){ 
    int i=0;
    cout << "You have " << i << " seconds remaining..." << endl;
    sleep(1);                         
  }
  return 0;                             
}
