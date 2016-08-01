// Start of Code 
#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
// 30 seconds
#define WATER_TIME 30*1000L
// every 5 hours
#define WAIT_TIME 5*60*60*1000L
//#define WAIT_TIME 10*1000L

RBD::Timer timerWater(WATER_TIME);   
RBD::Timer timerWait(WAIT_TIME);  

#define LEDPIN 11
#define FLOATSW 0
#define MOTOR 2

#define WAITBLINKINTERVAL 1000L
#define PUMPBLINKINTERVAL 100

unsigned long blinkInterval = WAITBLINKINTERVAL;
int floatSwitchState = 0;
int pumpWater = 0;
unsigned long previousTime = 0;
unsigned long currentTime = 0;
int ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(FLOATSW, INPUT);
  pinMode(MOTOR, OUTPUT);

  timerWait.restart();
}

void loop() {
  
  floatSwitchState = digitalRead(FLOATSW);
  currentTime = millis();

  // if the wait timer expires
  if(timerWait.onExpired()) {
    timerWater.restart();
    blinkInterval = PUMPBLINKINTERVAL;
    pumpWater = 1;
  }

  // if the water timer expires
  if(timerWater.onExpired()) {
    timerWait.restart();
    pumpWater = 0;
    blinkInterval = WAITBLINKINTERVAL;
  }

  if (currentTime - previousTime >= blinkInterval) {
    previousTime = currentTime;
    ledState = !ledState;
    digitalWrite(LEDPIN, ledState);   // turn the LED on (HIGH is the voltage level)
  }

  if (floatSwitchState == 1 && pumpWater == 1) {
    digitalWrite(MOTOR, LOW);   
  } else {
    // Turn the pump off
    digitalWrite(MOTOR, HIGH);  
  }
}

// End of Code 
