#include "GifDecoder.h"
#include "SdFileFunctions.h"
#include "xp16x25.h"

// loopLED should be lit while executing the loop() code, by default it's the
// onboard LED on pin 13.
const int loopLed = 13;

// SD chipSelect
// for Teensy 3.5/3.6 builtin use BUILTIN_SDCARD constant
const int sdChipSelect = BUILTIN_SDCARD;

//template parameters are maxGifWidth, maxGifHeight, lzwMaxBits
//(see GifDecoder.h)
GifDecoder<16,25,12> decoder;

//callback functions connecting GifDecoder to xp16x25
void screenClearCallback(void) {
  fillScreen(0);
}
void updateScreenCallback(void) {
  updateScreen();
}
void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  drawPixel(x, y, red, green, blue);
}

// Global setup/loop variables
File root;

void setup() {
  pinMode(loopLed, OUTPUT);
  // ledPowerPin is output, of course, and it starts out LOW = off
  pinMode(ledPowerPin, OUTPUT);

  xp16x25Setup();
  Serial.begin(115200);

  decoder.setScreenClearCallback(screenClearCallback);
  decoder.setUpdateScreenCallback(updateScreenCallback);
  decoder.setDrawPixelCallback(drawPixelCallback);
  // These are in SdFileFunctions.h
  decoder.setFileSeekCallback(fileSeekCallback);
  decoder.setFilePositionCallback(filePositionCallback);
  decoder.setFileReadCallback(fileReadCallback);
  decoder.setFileReadBlockCallback(fileReadBlockCallback);

  initSdCard(sdChipSelect);

  root = SD.open("/");
  
}

// Global loop variables
File file;
String fileName;
boolean fileOpen = false;

void loop() {
  digitalWrite(loopLed, LOW);
  //Serial.println("loop");
  if (! fileOpen) {
    file = root.openNextFile();
    if (! file) {
      root.rewindDirectory();
      Serial.println("rewind");
      file = root.openNextFile();
      delay(100);
    }
    fileName = String(file.name());
    if (fileName.endsWith(".GIF") || fileName.endsWith(".gif")) { 
      Serial.println(fileName);
      //file.close();
      openSdFile(file.name());
      decoder.startDecoding();
      fileOpen = true;
    }
    else {
      Serial.println("nope: " + fileName);
    }
  } else {
    if (decoder.decodeFrame() == ERROR_DONE_PARSING) {
      //file.close();
      fileOpen = false;
    }
  }
}
