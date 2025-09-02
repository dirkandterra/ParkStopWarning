// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

#define PIN            1
#define NUMPIXELS      2
#define SENSOR         2

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t alarmOutputMask;
void setup() {
  pinMode(SENSOR,INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  static int cycle = 0, oldSensor=0;;
  uint32_t scanMillis = millis();
  int sensorValue=0;
  cycle=!cycle;
  sensorValue=digitalRead(SENSOR);
  if(!oldSensor && sensorValue){
    alarmOutputMask = scanMillis + 10000;
  }else if(!sensorValue){
    alarmOutputMask = 0;
  }
  oldSensor = sensorValue;
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    for(int i=0;i<NUMPIXELS;i++){
      if(cycle && (alarmOutputMask > scanMillis)){
        pixels.setPixelColor(i,0xFF,0x00,0x00); // Moderately bright green color.  
      } else{
        pixels.setPixelColor(i,0x00,0x00,0x00);
      }     
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(250); // Delay for a period of time (in milliseconds).      
}
