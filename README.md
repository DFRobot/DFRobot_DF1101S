# DFRobot_DF1101S

Wanna buy a simple & practical voice recorder? This one is right for you! The voice recorder module supports 4 controlling modes Arduino, AT command, on-board buttons and ADKEY, and multi-segment voice recording. You can directly press the on-board buttons to record or play voice without using a controller. Moreover, the 16MB storage on the module can store up to 40 minutes recording voice and the recorded files can be copied to your computer via the type-C interface.  
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
1. Audio Recording <br>
2. Audio Playback


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods
```C++
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
   * @brief Set indicator LED(Power-down save) 
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
   * @brief Play(in music mode) or Record (in recording mode)
   * @return true or false
   */
  bool start();
  
  /**
   * @brief Playing Pause(in music mode) or recording pause(in recording mode)
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
  void playSpecFile(String str);
  
  /**
   * @brief Play the file of specific number(only valide for the default file name),
   * @  play the first one if there is no file designated.  
   * @param File name number: 0-999
   */
  void playSpecFile(int16_t num);

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
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
ESP8266        |      √       |              |             | 
M0        |      √       |              |             | 


## History

- Date 2020-11-26
- Version V1.0


## Credits

Written by fengli(li.feng@dfrobot.com), 2020.11.26 (Welcome to our [website](https://www.dfrobot.com/))





