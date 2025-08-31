// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

#define PIN            1
#define NUMPIXELS      4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t LightArray[30][4]=
{
  {50,0,0,0},
  {20,50,0,0},
  {5,20,50,0},
  {1,5,20,50},
  {0,1,5,20},
  {0,0,1,50},
  {0,0,50,20},
  {0,50,20,5},
  {50,20,5,1},
  {20,5,1,0},
  {5,1,0,0},
  {1,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0}
};
int delayval = 100; // delay for half a second
uint8_t j=0;
void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  float r,g,b;
  for(int f=0;f<7;f++){
    switch(f){
      case 0:
        r=1;
        g=0;
        b=0;
        break;
      case 1:
        r=0.5;
        g=0.5;
        b=0;
        break;
      case 2:
        r=0;
        g=1;
        b=0;
        break;
      case 3:
        r=0;
        g=0.5;
        b=0.5;
        break;
      case 4:
        r=0;
        g=0;
        b=1;
        break;
      case 5:
        r=0.5;
        g=0;
        b=0.5;
        break;
      default:
        r=0.5;
        g=0.5;
        b=0.5;
        break;
    }
    for(int h=0;h<21;h++){
      // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
      for(int i=0;i<NUMPIXELS;i++){
        j=LightArray[h][i];
        pixels.setPixelColor(i,(uint8_t)((float)j*r),(uint8_t)((float)j*g),(uint8_t)((float)j*b)); // Moderately bright green color.        
      }
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).      
    }
  }
}
