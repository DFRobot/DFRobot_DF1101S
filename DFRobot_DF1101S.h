#ifndef DFROBOT_DF1101S_H
#define DFROBOT_DF1101S_H

#include <Arduino.h>
#include <string.h>

//extern Stream *dbg;
class DFRobot_DF1101S
{
public:

  typedef enum{
    MUSIC = 1,  //Music Mode 
    RECORD,     //Recording Mode
    UFDISK,     //Slave Mode
  }eFunction_t;
  
  typedef struct{
   String str;
   uint8_t length;
  }sPacket_t;
  
  typedef enum{
    SINGLECYCLE = 1,  //Repeat one song
    ALLCYCLE,         //Repeat all
    SINGLE,           //Play one song once
    ERROR,
  }ePlayMode_t;



  DFRobot_DF1101S();
  //~DFRobot_DF1101S();
  bool begin(Stream &s);
  
  /**
   * @brief Set baud rate(Need to power off and restart, power-down save)  
   * @param 9600,19200,38400,57600,115200
   * @return true or false
   */
  bool setBaudRate(uint32_t baud);

  /**
   * @brief Set playback mode
   * @param ePlayMode_t:SINGLECYCLE,ALLCYCLE,SINGLE
   * @return true or false
   */
  bool setPlayMode(ePlayMode_t mode);

  /**
   * @brief Set indicator(Power-down save) 
   * @param true or false
   * @return true or false
   */
  bool setLED(bool on);
  
  /**
   * @brief Set prompt tone(power-down save)
   * @param true or false
   * @return true or false
   */
  bool setPrompt(bool on);
  
  /**
   * @brief Set volume 
   * @param vol:0-30
   * @return true or false
  */
  bool setVol(uint8_t vol);
  
  /**
   * @brief Set working mode 
   * @param eFunction_t:MUSIC,RECORD,UFDISK
   * @return true or false
   */
  bool switchFunction(eFunction_t function);
  
  //bool operation( );
  /**
   * @brief Next 
   * @return true or false
   */
  bool next();
  
  /**
   * @brief Last 
   * @return true or false
   */
  bool last();
  
  /**
   * @brief Play(music mode) or record(recording mode) 
   * @return true or false
   */
  bool start();
  
  /**
   * @brief Playing pause(in music mode) or recording pause(in recording mode)
   * @return true or false
   */
  bool pause();
  
  /**
   * @brief Save the recorded voice 
   * @return true or false
   */
  String saveRec();

  /**
   * @brief Delete the currently-playing file  
   * @return true or false
   */
  bool delCurFile();
  
  /**
   * @brief Play the file of specific path 
   * @param The designated path 
   */
  bool playSpecFile(String str);
  
  /**
   * @brief Play the file of specific number(only valid for the default file name),
   * @ play the first one if there is no file designated. 
   * @param File number: 0-999
   */
  bool playSpecFile(int16_t num);

  /**
   * @brief Get volume 
   * @return vol
   */
  uint8_t getVol();

  /**
   * @brief Get playback mode 
   * @return ePlayMode_t
   */
  ePlayMode_t getPlayMode();
private:
  sPacket_t pack(String cmd = " ",String para = " " );
  Stream *_s = NULL;
  void writeATCommand(String command,uint8_t length);
  String readAck(uint8_t len = 4);
  eFunction_t curFunction;
  String atCmd;
  
  uint8_t pauseFlag;
  
};

#endif
