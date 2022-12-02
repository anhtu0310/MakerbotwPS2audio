#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PWM channels of pca9685 0-16
#define PWM_CHANNEL2 8
#define PWM_CHANNEL1 9
#define PWM_CHANNEL4 10
#define PWM_CHANNEL3 11

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWMMotors(int c1, int c2, int c3, int c4)
{
  #ifdef BEBUG_CTRL
  char dbg_str[30];
  sprintf(dbg_str,"C1: %d\tC2: %d\tC3: %d\tC4: %d",c1,c2,c3,c4);
  Serial.println(dbg_str);
  #endif
  pwm.setPWM(PWM_CHANNEL1, 0, c1);
  pwm.setPWM(PWM_CHANNEL2, 0, c2);
  pwm.setPWM(PWM_CHANNEL3, 0, c3);
  pwm.setPWM(PWM_CHANNEL4, 0, c4);
}

void setPWMMotors2(int c1, int c2, int c3, int c4)
{
  // setPWM(channel, on_duty_cycle, off_duty_cycle)
  // Serial.print(c1);
  // Serial.print("\t");
  // Serial.print(c2);
  // Serial.print("\t");
  // Serial.print(c3);
  // Serial.print("\t");
  // Serial.print(c4);
  // Serial.println();
  char PS2_text[100];
  sprintf(PS2_text,"pwm_left: %d, dir_left: %d  pwm_right: %d, dir_right: %d \n",c1,c2,c3,c4);
  Serial.println(PS2_text);

  pwm.setPWM(12, 0, c1);
  pwm.setPWM(13, 0, c2);
  pwm.setPWM(14, 0, c3);
  pwm.setPWM(15, 0, c4);
}

void initMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);
  Wire.setClock(400000);

  setPWMMotors(0, 0, 0, 0);
}
