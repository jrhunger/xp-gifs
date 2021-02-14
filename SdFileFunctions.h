/* 
 *  This incorporates only the required functionality from FilenameFunctions at 
 *  https://github.com/pixelmatix/AnimatedGIFs as needed for callbacks from GifDecoder.
 */

#include <SD.h>

/** Added/modified stuff */
File sdFile;

int openSdFile(char *fileName) {
  if (sdFile) {
    Serial.println("open, closing..");
    sdFile.close();
  }
  sdFile = SD.open(fileName);
  Serial.println("opened");
  if (! sdFile) {
    Serial.printf("Error opening GIF file: %s", fileName);
    return -1;
  }
  Serial.println("returning");
  return 0;
}

void setSdFile(File sdFileIn) {
  sdFile = sdFileIn;
}

/** This part copied unmodified (except variable names) from source **/
bool fileSeekCallback(unsigned long position) {
    return sdFile.seek(position);
}

unsigned long filePositionCallback(void) {
    return sdFile.position();
}

int fileReadCallback(void) {
    return sdFile.read();
}

int fileReadBlockCallback(void * buffer, int numberOfBytes) {
    return sdFile.read(buffer, numberOfBytes);
}

int initSdCard(int chipSelectPin) {
    // initialize the SD card at full speed
    pinMode(chipSelectPin, OUTPUT);
    if (!SD.begin(chipSelectPin))
        return -1;
    return 0;
}
