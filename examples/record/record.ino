/*!
 * @file record.ino
 * @brief Recording
 * @n Experiment Phenomenon:Power on the module then it enters the recording mode. 
 * @n                       Start recording after 2 seconds and save the recorded voice file 5 seconds later. 
 * @n                       Print the file name repeatedly at the serial port.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-07-16
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_AS7341
 */
#include <DFRobot_DF1101S.h>
#include <SoftwareSerial.h>

SoftwareSerial df1101sSerial(2, 3);  //RX  TX

DFRobot_DF1101S df1101s;

String RECFileName;  //Recording file name 

void setup(void){
  Serial.begin(115200);
  df1101sSerial.begin(115200);
  while(!df1101s.begin(df1101sSerial)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  /*Set baud rate, power-down data save，need to power down and restart*/
  //df1101s.setBaudRate(115200);
  /*Open LED prompt, power-down save*/
  //df1101s.setLED(true);
  /*Open voice prompt, power-down save*/
  //df1101s.setPrompt(true);
  
  /*Enter Recording mode */
  df1101s.switchFunction(df1101s.RECORD);
  /*Wait for the end of prompt tone/
  delay(2000);
  /*Start recording*/
  df1101s.start();
  /*Pause*/
  //df1101s.pause();
  delay(5000);
  /*Save*/
  RECFileName = df1101s.saveRec();
}

void loop(){
  Serial.println(RECFileName);
  delay(1000);
}
