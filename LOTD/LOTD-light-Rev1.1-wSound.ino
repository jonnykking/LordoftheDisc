#include <Adafruit_NeoPixel.h>

#define PIN 0
#define BUTTON 2
#define PIN 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(100, PIN);

int play=4; //play duration

uint8_t  mode   = 0,   // Current animation effect
         offset = 0;   // Position of spinny eyes
uint32_t color  = 0x00ff96;    //Start red
uint32_t prevTime;
uint32_t randomColor;
long RanColor = 0;
uint32_t ColorOff;

void setup() {
  
  pinMode(play,OUTPUT); // sound output
  digitalWrite(play,LOW);
  
  randomSeed(analogRead(7));
  pixels.begin();

  mode = 1;
  pixels.setBrightness(90);   // 1/3 brightness
  prevTime = millis();
  pinMode(2, INPUT_PULLUP);   // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE);   // pressed
}

void changeEffect() {
  if (digitalRead (BUTTON) == LOW) {
    mode = 0;
    gobblegobble();
  }
}


void gobblegobble() {
  digitalWrite(play,HIGH); //soundtest
delay(50);
  digitalWrite(play,LOW);  //soundtest
  break;
  }



void loop() {
  uint8_t  i;
  uint32_t t;

  switch (mode) {

    case 0:   // Random sparks - just one LED on at a time!
      RanColor = random(48);   // # of cases +1
      randomColor = RanColor;   // Set color from random number

/// why this not work??
       ColorOff = pixels.Color(0, 0, 0);
        pixels.setPixelColor(   i, ColorOff);   // First eye
        pixels.setPixelColor(70 - i, ColorOff);
              pixels.show();
/// bah!
              
      switch (RanColor) {
        case 0 : randomColor = pixels.Color(0, 255, 0); break; //Lime
        case 1 : randomColor = pixels.Color(0, 0, 255); break; //Blue
        case 2 : randomColor = pixels.Color(255, 255, 0); break; //Yellow
        case 3 : randomColor = pixels.Color(0, 255, 255); break; //Cyan / Aqua
        case 4 : randomColor = pixels.Color(255, 0, 255); break; //Magenta / Fuchsia
        case 5 : randomColor = pixels.Color(128, 128, 128); break; //Gray
        case 6 : randomColor = pixels.Color(128, 0, 0); break; //Maroon
        case 7 : randomColor = pixels.Color(128, 128, 0); break; //Olive
        case 8 : randomColor = pixels.Color(0, 128, 0); break; //Green
        case 9 : randomColor = pixels.Color(128, 0, 128); break; //Purple
        case 10 : randomColor = pixels.Color(0, 128, 128); break; //Teal
        case 11 : randomColor = pixels.Color(0, 0, 128); break; //Navy
        case 12 : randomColor = pixels.Color(128, 0, 0); break; //maroon
        case 13 : randomColor = pixels.Color(139, 0, 0); break; //dark red
        case 14 : randomColor = pixels.Color(165, 42, 42); break; //brown
        case 15 : randomColor = pixels.Color(178, 34, 34); break; //firebrick
        case 16 : randomColor = pixels.Color(220, 20, 60); break; //crimson
        case 17 : randomColor = pixels.Color(255, 0, 0); break; //red
        case 18 : randomColor = pixels.Color(255, 140, 0); break; //dark orange
        case 19 : randomColor = pixels.Color(255, 165, 0); break; //orange
        case 20 : randomColor = pixels.Color(255, 215, 0); break; //gold
        case 21 : randomColor = pixels.Color(154, 205, 50); break; //yellow green
        case 22 : randomColor = pixels.Color(85, 107, 47); break; //dark olive green
        case 23 : randomColor = pixels.Color(107, 142, 35); break; //olive drab
        case 24 : randomColor = pixels.Color(124, 252, 0); break; //lawn green
        case 25 : randomColor = pixels.Color(0, 100, 0); break; //dark green
        case 26 : randomColor = pixels.Color(0, 128, 0); break; //green
        case 27 : randomColor = pixels.Color(34, 139, 34); break; //forest green
        case 28 : randomColor = pixels.Color(0, 255, 0); break; //lime
        case 29 : randomColor = pixels.Color(50, 205, 50); break; //lime green
        case 30 : randomColor = pixels.Color(46, 139, 87); break; //sea green
        case 31 : randomColor = pixels.Color(102, 205, 170); break; //medium aqua marine
        case 32 : randomColor = pixels.Color(60, 179, 113); break; //medium sea green
        case 33 : randomColor = pixels.Color(32, 178, 170); break; //light sea green
        case 34 : randomColor = pixels.Color(47, 79, 79); break; //dark slate gray
        case 35 : randomColor = pixels.Color(0, 128, 128); break; //teal
        case 36 : randomColor = pixels.Color(0, 139, 139); break; //dark cyan
        case 37 : randomColor = pixels.Color(95, 158, 160); break; //cadet blue
        case 38 : randomColor = pixels.Color(70, 130, 180); break; //steel blue
        case 39 : randomColor = pixels.Color(100, 149, 237); break; //corn flower blue
        case 40 : randomColor = pixels.Color(30, 144, 255); break; //dodger blue
        case 41 : randomColor = pixels.Color(25, 25, 112); break; //midnight blue
        case 42 : randomColor = pixels.Color(0, 0, 128); break; //navy
        case 43 : randomColor = pixels.Color(0, 0, 205); break; //medium blue
        case 44 : randomColor = pixels.Color(0, 0, 255); break; //blue
        case 45 : randomColor = pixels.Color(138, 43, 226); break; //blue violet
        case 46 : randomColor = pixels.Color(75, 0, 130); break; //indigo
        case 47 : randomColor = pixels.Color(72, 61, 139); break; //dark slate blue
      }

      i = random(100);
      
      pixels.setPixelColor(i, randomColor);
      pixels.show();
      delay(5);
      pixels.setPixelColor(i, 0);
      break;

    case 1:   // Spinny wheels
      for (i = 0; i < 100; i++) {
        uint32_t c = 0;
        if (((offset + i) & 7) < 2) c = randomColor;  // 2 pixels on...   // was color now randomColor
        pixels.setPixelColor(   i, c);   // First eye
        pixels.setPixelColor(70 - i, c); // Second eye (flipped)
      }
      pixels.show();
      offset++;
      delay(90);
      break;
  }

  t = millis();
  if ((t - prevTime) > 8000) {       // Every 8 seconds...
    mode++;                          // Next mode
    if (mode > 1) {                  // End of modes?
      mode = 1;                      // Start modes over
    }
    prevTime = t;
  }
}
