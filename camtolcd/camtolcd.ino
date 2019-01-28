/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <stdio.h>  /* for sprintf */
#include <Camera.h>


// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired

void CamCB(CamImage img);

/**
 * Callback from Camera library when video frame is captured.
 */

void CamCB(CamImage img)
{
  /* Check the img instance is available or not. */

  if (img.isAvailable())
    {

      /* If you want RGB565 data, convert image data format to RGB565 */

      img.convertPixFormat(CAM_IMAGE_PIX_FMT_RGB565);

      /* You can use image data directly by using getImgSize() and getImgBuff().
       * for displaying image to a display, etc. */

      Serial.print("Image data size = ");
      Serial.print(img.getImgSize(), DEC);
      Serial.print(" , ");

      Serial.print("buff addr = ");
      Serial.print((unsigned long)img.getImgBuff(), HEX);
      Serial.println("");

      Serial.print("getWidth = ");
      Serial.print((unsigned long)img.getWidth(), DEC);
      Serial.print(" , ");

      Serial.print("getHeight = ");
      Serial.print((unsigned long)img.getHeight(), DEC);
      Serial.println("");
      drawimage(img);
    }
  else
    {
      Serial.print("Failed to get video stream image\n");
    }
}

void drawimage(CamImage img)
{
  int x,y,bx,by,i;
  uint16_t *pImg;
  y = img.getHeight();
  x = img.getWidth();
  pImg = (uint16_t *)img.getImgBuff();

   for(by = 0; by < y; by++)
   {
     for(bx = 0; bx < x; bx++)
     {
       i = bx + by * x;
       tft.drawPixel(bx,by,pImg[i]); 
     }
   }

}

void setup() {
  Serial.begin(9600);
 
  Serial.println("Prepare tft");
  tft.begin();
  tft.setRotation(3);

  Serial.println("Prepare camera");
  theCamera.begin();

  Serial.println("Start streaming");
  theCamera.startStreaming(true, CamCB);

  Serial.println("Set Auto white balance parameter");
  theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_DAYLIGHT);
 
  Serial.println("Start streaming");
  theCamera.setStillPictureImageFormat(
     CAM_IMGSIZE_QUADVGA_H,
     CAM_IMGSIZE_QUADVGA_V,
     CAM_IMAGE_PIX_FMT_JPG);

}


void loop(void) {

}
