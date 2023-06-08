#include <Adafruit_CircuitPlayground.h>
volatile int j = 0;
volatile int check;

bool switchBut;
volatile int switchFlag;

//speed
volatile int rotSpd;


void setup() {

  Serial.begin(9600);
  CircuitPlayground.begin();
  randomSeed(analogRead(0));

  pinMode(7, INPUT_PULLUP);

  attachInterrupt(7, switchState, CHANGE);
}

void loop() {


  //on off
  if(switchFlag){
    switchBut = CircuitPlayground.slideSwitch();
    switchFlag = 0;
  }

  if(switchBut){
    gameStart();
  }


  if(switchBut==0){
    j=0;
  }


}


void gameStart(){
//rotation speed
rotSpd = 400;


for(int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,0,0,255);
    delay(rotSpd);
    CircuitPlayground.clearPixels();

//check if button off
    if(switchBut==0){
     return;
    }

//matching
    j++;
    if(j>9){
      j = 0;
    }
  }
}


void switchState(){
  switchFlag = 1;
}
