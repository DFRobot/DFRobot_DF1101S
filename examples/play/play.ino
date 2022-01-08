/*!
 * @file play.ino
 * @brief Playing
 * @n details Phenomenon:Power on the module then it enters the music mode. 
 * @n                       Start playing the previously-recorded file, pause 3s later, 
 * @n                       play the next song 3s later, play the last song 3s later, 
   @n                       and play the file of specific number(FILE0000) once 3s later.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-07-16
 * @url https://github.com/DFRobot/DFRobot_DF1101S
 */
#include <DFRobot_DF1101S.h>
#include <SoftwareSerial.h>

SoftwareSerial df1101sSerial(2, 3);  //RX  TX

DFRobot_DF1101S df1101s;
void setup(void){
  Serial.begin(115200);
  df1101sSerial.begin(115200);
  while(!df1101s.begin(df1101sSerial)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  /*Set volume to 20*/
  df1101s.setVol(20);
  Serial.print("VOL:");
  /*Get volume*/
  Serial.println(df1101s.getVol());
  /*Enter music mode*/
  df1101s.switchFunction(df1101s.MUSIC);
  /*Wait for the end of prompt tone*/
  delay(2000);
  /*Set playback mode to "repeat all"*/
  df1101s.setPlayMode(df1101s.ALLCYCLE);
  Serial.print("PlayMode:");
  /*Get playback mode*/
  Serial.println(df1101s.getPlayMode());
}

void loop(){
  /*Start*/
  df1101s.start();
  delay(3000);
  /*Pause*/
  df1101s.pause();
  delay(3000);
  /*Next*/
  df1101s.next();
  delay(3000);
  /*Last*/
  df1101s.last();
  delay(3000);
  /*Play the specific file(FILE0000) in recording files once*/
  df1101s.playSpecFile(0);
  while(1);
  /*Delete the currently-playing file*/
  //df1101s.delCurFile();
}
