#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#define NUM_LEDS 60
#define DATA_PIN 6

//Using bytes to reduce storage used. Especially for global variables.
const byte standardPin = 2;
const byte blueWhitePin = 3;
const byte purpleSwirlsPin = 4;
const byte redBurstPin = 5;

//6 groups
int colorState[6];
bool upDownState[6] = {true, false, true, true, false, false};

//Parameter for end of patterns
const byte delayVal = 5;
int state = 1;

bool doStandard, doBlueWhite, doPurple, doRedBurst;

CRGB leds[NUM_LEDS];

void setup() {
  //Declare the LED strip, and specifically the data pin.
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.show();
  delay(delayVal);
  pinMode(standardPin, INPUT);
  pinMode(blueWhitePin, INPUT);
  pinMode(purpleSwirlsPin, INPUT);
  pinMode(redBurstPin, INPUT);

  //Initialize to randomize the starting conditions.
  initialize();
  
}

 void loop() {
  
//  doStandard = digitalRead(standardPin);
//  if(doStandard){ state = 1; } IMPLIED
  doBlueWhite = digitalRead(blueWhitePin);
  if(doBlueWhite){ state = 2; }
  doPurple = digitalRead(purpleSwirlsPin);
  if(doPurple){ state = 3; }
  doRedBurst = digitalRead(redBurstPin);
  if(doRedBurst){ state = 4; }
  switch(state){
    case 2:
      blueSpike();
      initialize();
      break;
    case 3:
      purpleSwirls();
      initialize();
      break;
    case 4:
      redBurst(300);
      initialize();
      break;
    default:
      standardLoop();
      delay(100); //This line determines how fast the system cycles through the standardLoop(). 100 makes a nice twinkling.
      break;
  }

  state = 1; //Reset to default value.
}

//This initialize method resets the system. It sets half the lights to be 
//increasing in brightness and half of them to be decreasing and randomizes the colors of each group.
void initialize(){ 
  for(int i = 0; i<6; ++i){ //For each group
    //Set the red to be somewhere between 25 and 200. 
    //This is done to just avoid the corner cases where it starts at the max or min value. 
    leds[i].r = (int)random(25, 200); //I still use the value of red as the determiner of brightness.
    colorState[i] = (int)random(1, 4);
  }
  upDownState[0], upDownState[2], upDownState[3] = true; //Half to true
  upDownState[1], upDownState[4], upDownState[5] = false; //Half to false
} 

//A wrapper method for the one line in the method. Makes the syntax in other methods easier to read. 
void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].setRGB(red, green, blue);
} 

//A wrapper method for setting all LEDs to be the same color. Usually used to blank the lights. 
void setAll(byte red, byte green, byte blue){
  for(int j = 0; j<NUM_LEDS; j++){
    leds[j].setRGB(red, green, blue);
  }
  FastLED.show();
}

void standardLoop(){

    //Attempt 4 Appoach:
    //Update the first 6 lights with the values from the arrays
    //with the changeBrightness(int group), then iterate through
    //all the lights, starting at 6. 
    for(int j = 0;j<6;++j){ //j = {0, 1, 2, 3, 4, 5}
      changeBrightness(j);
    }
    for(int add = 6; add<60; ++add){
      leds[add] = leds[add-6];
    }
    FastLED.show();
}

void changeBrightness(int group)
    int cS = colorState[group];
    if(upDownState[group]){//true means go up, false is go down. 
      switch(cS){
        case 1: //If it's RED
            leds[group].r = leds[group].r + 5;
          break;
        case 2: //If it's ORANGE
            leds[group].r = leds[group].r + 5;
            leds[group].g =( (leds[group].r) / 4);
          break;
        case 3: //If it's YELLOW
            leds[group].r = leds[group].r + 5;
            leds[group].g =(leds[group].r / 2);
          break;
        }
    } else { //If it is in the dimming phase. The only difference is that the "+"s above are turned into "-"
      switch(cS){
        case 1: //If it's RED
            leds[group].r = leds[group].r - 5;
          break;
        case 2: //If it's ORANGE
            leds[group].r = leds[group].r - 5;
            leds[group].g =( (leds[group].r) / 4 );
          break;
        case 3: //If it's YELLOW
            leds[group].r = leds[group].r - 5;
            leds[group].g = ((leds[group].r) / 2);
          break;
      }
    }

    if(leds[group].r >250){ upDownState[group] = false;} //If the brightness of any group is above 250, then its time to switch to the decreasing mode
    else if(leds[group].r < 6){ upDownState[group] = true; colorState[group] = (int)random(1, 4); } //If the brightness is below 6, its time to switch into decreasing mode and select a new random color. 
}

void blueSpike(){
  //Version 1, Half Blue, Half White
  for(int k = 1; k < 150; k++){
    for(int j = 0; j<59; j= j+2){
      setPixel(j, k, k, k); //White (R=G=B)
      setPixel(j+1, 0, 0, k); //All Blue
    }
    FastLED.show();
    delay(delayVal + 5);
  }
  for(int k = 0; k < 15; k++){ //This loop is supposed to be a twinkling routine, but it doesnt really do anything, but I dont wanna take it out.
    int i = random(0, 60);
    setPixel(i, 255, 255, 255);
    delay(200);
    setPixel(i, leds[i+2].r, leds[i+2].g, leds[i+2].b); 
  }
  //delay(2500); //Delay at the end to let the colors be seen.
  allOff();
}

void redBurst(int count){
  for(int k = 0; k< count; ++k){
    standardLoop(); //No delay here, unlike in the loop() method. Pretty fast.
  }
  int longDelay = 2000;
  for(int j = 0; j<count; j++){
    standardLoop();
  }
  for(int k = 0; k<256; k++){
    setAll(k, 0, 0);
    delay(5); //Quickly ramp up to RED
  }
  delay(longDelay); //Stay at RED for longDelay milliseconds
  for(int k = 256; k>0; k--){
    setAll(k, 0, 0);
    delay(5);
  }
  allOff();
}

void purpleSwirls(){
  //Code from 
  // https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/ "Running Lights"
  byte red = 150; //These values seem to be a good mix for a nice bright purple. 
  byte green = 0;
  byte blue = 200;

  int Position=0;
  int waveDelay = 25;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        //sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      FastLED.show();
      delay(waveDelay);
  }
  allOff();
}

void allOff(){
  //Cut all the lights off. Rarely used?
  for(int j = 0; j<NUM_LEDS; j++){
    setPixel(j, 0, 0, 0);
  }
  FastLED.show();
}



