#include <Adafruit_NeoPixel.h>
#define PIN 1
#define TRIG 3
#define ECHO 2
#define NUMPIXELS 2
#define MILLISBEFORESLEEP 10000

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t sensorState = 0;  //0=Sleep, No object, 1= Object in sensing range, 2= Object at desired distance, 3=Sleep, object at desired range
uint32_t timeToSleep = 0;
void setup()
{
	//Set Pins 0 and 1 as outputs.
	//Some Digisparks have a built-in LED on pin 0, while some have it on
	//pin 1. This way, we can all Digisparks.
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pixels.begin();
  

}
void loop()
{
  float duration, distance;
  static int cycle=0;
  int ii=0;
  uint32_t cycleMillis = millis();
  uint8_t colorToShow[3] = {0,0,0};
  cycle=!cycle;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = (duration*.0343)/2;
	//Set the LED pins to HIGH. This gives power to the LED and turns it on
  for(int i=0;i<NUMPIXELS;i++){
    if(distance>100){
      colorToShow[0] = 0;
      colorToShow[1] = 0;
      colorToShow[2] = 0;
    }
    else if(distance>80){
      timeToSleep = cycleMillis + MILLISBEFORESLEEP;
      colorToShow[0] = 0;
      colorToShow[1] = 0xFF;
      colorToShow[2] = 0;
    }
    else if(distance>65){
      timeToSleep = cycleMillis + MILLISBEFORESLEEP;
      colorToShow[0] = 0xFF;
      colorToShow[1] = 0xFF;
      colorToShow[2] = 0;
    }else{
      colorToShow[0] = 0xFF;
      colorToShow[1] = 0;
      colorToShow[2] = 0;
    }
  }
  if(cycleMillis>timeToSleep){
      colorToShow[0] = 0;
      colorToShow[1] = 0;
      colorToShow[2] = 0;
  }
  
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,colorToShow[0],colorToShow[1],colorToShow[2]);
  }
  //DigiKeyboard.println(distance);
	//Wait for a second
  pixels.show();
	delay(500);
}