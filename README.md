# xp-gifs - display animated gifs on my 16x25 LED matrix
Made for:
* Teensy (https://www.pjrc.com/teensy/ v3)
* OctoWS2811 (https://www.pjrc.com/store/octo28_adaptor.html)

General approach is to rip code from other places and swap out the display calls for ones that use my 16x25-specific functions

## Code:
* xp-gifs.ino - main program
* xp16x25.h - functions and variables to control 16x25 matrix
  - wrapper around Teensy OctoWS2811 library (https://www.pjrc.com/teensy/td_libs_OctoWS2811.html)

- GifDecoder components from: https://github.com/pixelmatix/AnimatedGIFs/tree/51b7dac8bf487f021ecd0755f69c93b57dd9a1eb
  - (library since removed LzwDecoder_Impl and incorporated a different sub-library)
  - GifDecoder_Impl.has a "#ifndef min" section that is added in the next commit, but i don't have the format changes that are in the next commit. <shrug>
  - files:
    - GifDecoder.h - copied
    - GifDecoder_Impl.h - copied
    - LzwDecoder_Impl.h -copied
    - FilenameFunctions.h - modified:
      - see comments for what is modified vs copied




