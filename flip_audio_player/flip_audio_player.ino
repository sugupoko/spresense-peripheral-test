/*
 *  player.ino - Simple sound player example application
 *  Copyright 2018 Sony Semiconductor Solutions Corporation
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <SDHCI.h>
#include <Audio.h>
#include <Wire.h>
#include "KX122.h"

#define AUDIO_PLAY              0
#define AUDIO_STOP              1
#define PIN_BTN                 15
#define FLIP_THRETHOLD_STOP     -0.7
#define FLIP_THRETHOLD_PLAY     0.7

SDClass theSD;
AudioClass *theAudio;
KX122 kx122(KX122_DEVICE_ADDRESS_1F);
File myFile;

bool ErrEnd = false;

volatile int g_Audio_conndition = AUDIO_STOP;


/**
 * @brief Audio attention callback
 *
 * When audio internal error occurc, this function will be called back.
 */

static void audio_attention_cb(const ErrorAttentionParam *atprm)
{
  puts("Attention!");
  
  if (atprm->error_code >= AS_ATTENTION_CODE_WARNING)
    {
      g_Audio_conndition = AUDIO_STOP;
   }

}

/**
 * @brief Setup audio player to play mp3 file
 *
 * Set clock mode to normal <br>
 * Set output device to speaker <br>
 * Set main player to decode stereo mp3. Stream sample rate is set to "auto detect" <br>
 * System directory "/mnt/sd0/BIN" will be searched for MP3 decoder (MP3DEC file)
 * Open "Sound.mp3" file <br>
 * Set master volume to -16.0 dB
 */
void setup()
{
  audio_init();
  Acceleration_init();
}

/**
 * @brief Play stream
 *
 * Send new frames to decode in a loop until file ends
 */
void loop()
{

  check_flip();

  switch (g_Audio_conndition)
    {
      case AUDIO_PLAY:
        audio_play();
        break;

      case AUDIO_STOP:
        audio_stop();
        break;

      default:
        break;
    }  


  /* This sleep is adjusted by the time to read the audio stream file.
      Please adjust in according with the processing contents
      being processed at the same time by Application.
  */
 usleep(40000);
}

/**
 * @brief Play stream
 *
 * Send new frames to decode in a loop until file ends
 */

void audio_play(void)
{

  if (!myFile)
  {
    audio_fileopen();
  }
  /* Send new frames to decode in a loop until file ends */
  int err = theAudio->writeFrames(AudioClass::Player0, myFile);

  /*  Tell when player file ends */
  if (err == AUDIOLIB_ECODE_FILEEND)
    {
      printf("Main player File End!\n");
      audio_fileopen();
    }

  /* Show error code from player and stop */
  if (err)
    {
      printf("Main player error code: %d\n", err);
      g_Audio_conndition = AUDIO_STOP;
    }

}

/**
 * @brief Stop stream
 *
 * Send new frames to decode in a loop until file ends
 */

void audio_stop(void)
{
  printf("Audio STOP\n");
 
  if (myFile)
  {
    delay(1);
    theAudio->stopPlayer(AudioClass::Player0, AS_STOPPLAYER_NORMAL);
    myFile.close();
  }
}

/**
 * @brief init
 *
 * Send new frames to decode in a loop until file ends
 */

void audio_init(void)
{
  puts("initialization Audio Library");

  // start audio system
  theAudio = AudioClass::getInstance();
  theAudio->begin(audio_attention_cb);
  theAudio->setRenderingClockMode(AS_CLKMODE_NORMAL);
  theAudio->setPlayerMode(AS_SETPLAYER_OUTPUTDEVICE_SPHP, AS_SP_DRV_MODE_LINEOUT);
  err_t err = theAudio->initPlayer(AudioClass::Player0, AS_CODECTYPE_MP3, "/mnt/sd0/BIN", AS_SAMPLINGRATE_AUTO, AS_CHANNEL_STEREO);

  /* Verify player initialize */
  if (err != AUDIOLIB_ECODE_OK)
    {
      printf("Player0 initialize error\n");
      exit(1);
    }

}

void Acceleration_init(void)
{
  byte rc;
  Wire.begin();
  rc = kx122.init();
  if (rc != 0) {
    printf("KX122 initialization failed");
  }

}

void check_flip(void)
{
  byte rc;
  float acc[3];

  rc = kx122.get_val(acc);

  if (rc == 0) 
   {
     int out = acc[2] *100;
     printf("z:%d [g]\n", out);

    if(acc[2] < FLIP_THRETHOLD_STOP)
      {
        g_Audio_conndition = AUDIO_STOP;
        printf("FLIP!!!\n");  
      }
    else if (acc[2] > FLIP_THRETHOLD_PLAY)
      {
        g_Audio_conndition = AUDIO_PLAY;
        printf("Audio play!!!\n");  
      }
   }
}

void audio_fileopen()
{
  myFile.close();
  myFile = theSD.open("moon.mp3");
  theAudio->writeFrames(AudioClass::Player0, myFile);
  theAudio->startPlayer(AudioClass::Player0);
  theAudio->setVolume(-200);
}

