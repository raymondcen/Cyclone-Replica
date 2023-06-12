#include <Adafruit_CircuitPlayground.h>

int j;
volatile int k;

int A_four = 440;
float midi[127];

bool switchBut;
bool butR;

//flags to stop loops
volatile int gameFlag = 0;
volatile int lvlFlag = 0;
volatile int begFlag = 0;
volatile int failFlag = 0;
volatile int endFlag = 0;
volatile int butRFlag = 0;

//level
volatile int lvl = 1;
//speed
volatile int rotSpd = 300;

void setup() {

  Serial.begin(9600);
  CircuitPlayground.begin();
  randomSeed(analogRead(0));

  generateMIDI();

  pinMode(7, INPUT_PULLUP);

  attachInterrupt(7, switchState, CHANGE);
  attachInterrupt(5, lState, FALLING);
  attachInterrupt(4, lState, FALLING);
}

void loop() {

  //start gameplay
  if(switchBut == 1 && gameFlag == 1){
    gameStart();
  }
  //turn off game
  if(switchBut==0){
    CircuitPlayground.clearPixels();
    gameFlag = 0;
    lvlFlag = 0;
    failFlag = 0;
    endFlag = 0;
    butR = 0;
    lvl = 1;
    rotSpd = 300;
    }
    
  //next level pattern
  if(lvlFlag == 1){
    for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,255,0,255);
      CircuitPlayground.setPixelColor(i+5,255,0,255);
      CircuitPlayground.setPixelColor(i-5,255,0,255);
      delay(30);
      CircuitPlayground.clearPixels();
    }
  }
//go to next level
  if(butR == 1 && lvlFlag ==1){
    lvlFlag = 0;
    begFlag = 1;
    butR = 0;
  }

//beginning sequence of game
  if (begFlag == 1 && switchBut){
    for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,255,0,0);
      delay(110);
    }
//insert
    for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,255,50,0);
      delay(110);
    }

    for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,255,255,0);
       delay(110);
    }

    for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,0,255,0);
       delay(110);
    }  
      for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,0,255,0);
    }  
    delay(110);
    CircuitPlayground.clearPixels();
    delay(50);
    gameFlag = 1;
    butRFlag = 1;
    begFlag = 0;
    butR = 0;
  }

//fail level
  if (failFlag == 1 && switchBut){
    for(int i = 0; i<10; i++){
      CircuitPlayground.setPixelColor(i,255,0,0);
      CircuitPlayground.setPixelColor(i+5,255,0,0);
      CircuitPlayground.setPixelColor(i-5,255,0,0);
      delay(30);
      CircuitPlayground.clearPixels();
      }
  }

  if(butR == 1 && failFlag ==1){
    randoSelect();
    failFlag = 0;
    begFlag = 1;
    butR = 0;
  }

//endgame
  if(endFlag == 1 && switchBut){
    for (int i=0; i<2; i++){
     int LED_Num = random(10);
     int red  = random(255);
     int blue  = random(255);
     int green  = random(255);
     CircuitPlayground.setPixelColor(0,red,blue,green);
     CircuitPlayground.setPixelColor(1,red,blue*2,green);
     CircuitPlayground.setPixelColor(2,red,blue,green*2);
     CircuitPlayground.setPixelColor(3,red*3,blue,green);
     CircuitPlayground.setPixelColor(4,red,blue*3,green);
     CircuitPlayground.setPixelColor(5,red,blue,green*3);
     CircuitPlayground.setPixelColor(6,red*4,blue,green);
     CircuitPlayground.setPixelColor(7,red,blue*4,green);
     CircuitPlayground.setPixelColor(8,red,blue,green*4);
     CircuitPlayground.setPixelColor(9,red*5,blue,green);
     delay(100);
     CircuitPlayground.clearPixels();
   }
  }
  if(butR == 1 && endFlag ==1){
    endFlag = 0;
    begFlag = 1;
    butR = 0;
  }

}

//GAME
void gameStart(){

//main section of game
  for(k = 0; k < 10; k++){
      CircuitPlayground.setPixelColor(j,0,255,0);
      CircuitPlayground.setPixelColor(k,0,0,255);
      delay(rotSpd);
      CircuitPlayground.setPixelColor(k,0,0,0);


    if(butR == 1){
      if(j==k){
        CircuitPlayground.playTone(midi[71], 200);
        nextLvl();
        butR = 0;
        break;
      } else {
        butR = 0;
        CircuitPlayground.playTone(midi[30], 200);
        failGame();
        
        break;
      }
    }
  //turn off during game
    if(switchBut == 0){
      break;
    }
  }
}

//functions
void nextLvl(){
  gameFlag = 0;
  lvlFlag = 1;
  CircuitPlayground.clearPixels();
  lvl++;
  rotSpd = rotSpd - 60;
  if(lvl > 5){
   endGame();
   lvl = 1;
   rotSpd = 300;
  }
 randoSelect();
}

void endGame(){
CircuitPlayground.clearPixels();
gameFlag = 0;
lvlFlag = 0;
begFlag = 0;
failFlag = 0;
butR = 0;
endFlag = 1;
lvl = 1;
}

void failGame(){
lvl = 1;
rotSpd = 300;
CircuitPlayground.clearPixels();
gameFlag = 0;
failFlag = 1; 
butR = 0;
}

void randoSelect(){
  j = random(1,9);
}

void switchState(){
  begFlag = 1;
  delay(5);
  switchBut = CircuitPlayground.slideSwitch();
  digitalRead(7);
  randoSelect();
}

void lState(){
  butR = 1;
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

