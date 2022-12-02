/*
 * A better version of MakerBotwPS2 example used with makerbot BANHMI hardware platform
 * This version simplify the joystick driving method, where the functionality stay the same.
 * Added new controling menthod, switch driving mode by pressing SELECT button
 * Added nitro like speed booster when holding L2
 *
 * Writen by Tu Dang - Makerviet
 */
#include "Arduino.h"
#include "motors.h"
#include "PS2_controller.h"
TaskHandle_t Task1;
// TaskHandle_t Task2;

#include <LittleFS.h>
#include "AudioTools.h"

File audioFile;
I2SStream out;
// AnalogAudioStream out;                  // output via the internal DAC of the ESP32
VolumeStream volume(out);     // the volume control
EncodedAudioStream decoder(&volume, new WAVDecoder());      //decoding wave files 16bit signed PCM
StreamCopy copier;                          // copies sound via i2s to the DAC




void Task1code(void *parameter)
{
for(;;)
  {

  
  // Serial.println("Done setting up!");
  ps2x.read_gamepad(0, 0);
  PS2control();
  delay(50);
  //   Serial.print("task running on core ");
  // Serial.println(xPortGetCoreID());
  // delay(500);
  }
}
void setup()
{
  Serial.begin(115200);

  initMotors();
  setupPS2controller();
  // xTaskCreatePinnedToCore(
  xTaskCreate(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      2000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      24,         /* priority of the task */
      &Task1);//,    /* Task handle to keep track of created task */
      //1);        /* pin task to core 0 */
  delay(500);
  // xTaskCreatePinnedToCore(
  //                   Task2code,   /* Task function. */
  //                   "Task2",     /* name of task. */
  //                   10000,       /* Stack size of task */
  //                   NULL,        /* parameter of the task */
  //                   1,           /* priority of the task */
  //                   &Task2,      /* Task handle to keep track of created task */
  //                   1);          /* pin task to core 1 */
  //   delay(500);

 AudioLogger::instance().begin(Serial, AudioLogger::Info);

  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  auto config = out.defaultConfig(TX_MODE);   

  config.sample_rate = 44100;   //44.1kHz  --- always make sure, that the same config is loaded for decoder and out ---
  config.channels = 1;      // mono sound only here
  config.bits_per_sample = 16;   //16 bit signed PCM
  //  config.sample_rate = sample_rate;
    // config.channels = channels;
    // config.bits_per_sample = 16;
    config.pin_bck=26;
    config.pin_data = 33;
    config.pin_ws = 27;
    out.begin(config);

  // out.begin(config);
  
  audioFile = LittleFS.open("/tom.wav");  // load ready wave file from SPIFFS
  decoder.setNotifyAudioChange(out);
  decoder.begin(config);
  volume.setVolume(1);    
      copier.begin(decoder, audioFile);  
  pinMode(0,INPUT);
  pinMode(2,INPUT);
}

void loop()
{
  if(!digitalRead(0)){
    audioFile.seek(0);
    while(copier.copy()); 
  }
  delay(100);
  }
