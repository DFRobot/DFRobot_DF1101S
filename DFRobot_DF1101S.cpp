/*!
 *@file DFRobot_DF1101S.cpp
 *@brief Define the basic structure of class DFRobot_DF1101S, the implementation of the basic methods
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2021-10-15
 *@url https://github.com/DFRobot/DFRobot_DF1101S
*/
#include <DFRobot_DF1101S.h>
DFRobot_DF1101S::DFRobot_DF1101S(){

}

bool DFRobot_DF1101S::begin(Stream &s){
   sPacket_t cmd;
   _s = &s;
   cmd = pack();
   
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

uint8_t DFRobot_DF1101S::getVol(){
   String vol = "";
   sPacket_t cmd;
   cmd = pack("VOL","?");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(12);
   vol += str[7];
   if(str[8] != 0X5D)
         vol += str[8];
   return (uint8_t)atoi(vol.c_str());
}

bool DFRobot_DF1101S::setVol(uint8_t vol){
   sPacket_t cmd;
   cmd = pack("VOL",String(vol));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

DFRobot_DF1101S::ePlayMode_t DFRobot_DF1101S::getPlayMode(){

   String playMode = "";
   sPacket_t cmd;
   cmd = pack("PLAYMODE","?");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(13);
   playMode = str[10];
   //Serial.println(str);
   if(str[11] == '\r'  && str[12] == '\n')
     return (ePlayMode_t)atoi(playMode.c_str());
   else 
     return ERROR;

}
bool DFRobot_DF1101S::setBaudRate(uint32_t baud){
   sPacket_t cmd;
   cmd = pack("BAUDRATE",String(baud));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_DF1101S::switchFunction(eFunction_t function){
   sPacket_t cmd;
   cmd = pack("FUNCTION",String(function));
   curFunction = function;
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 0;
   if(readAck() == "OK\r\n"){
    delay(1300);
    return true;
   } else{
    return false;
   }
}
bool DFRobot_DF1101S::setPlayMode(ePlayMode_t mode){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAYMODE",String(mode));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_DF1101S::setLED(bool on){

   sPacket_t cmd;
   String mode;
   if(on == true )
     mode = "ON";
   else 
     mode = "OFF";
   cmd = pack("LED",mode);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }

}
bool DFRobot_DF1101S::setPrompt(bool on){
   sPacket_t cmd;
   String mode;
   if(on == true )
     mode = "ON";
   else 
     mode = "OFF";
   cmd = pack("PROMPT",mode);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

bool DFRobot_DF1101S::next(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAY","NEXT");
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 1;
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}


bool DFRobot_DF1101S::last(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAY","LAST");
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 1;
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_DF1101S::start(){
   sPacket_t cmd;
   if(curFunction == MUSIC){
     cmd = pack("PLAY","PP");
   }else if(curFunction == RECORD){
     cmd = pack("REC","RP");
   }else{
      return false;
   }

   if(pauseFlag == 1) return false;
   pauseFlag = 1;
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

bool DFRobot_DF1101S::pause(){
   sPacket_t cmd;
   if(curFunction == MUSIC){
     cmd = pack("PLAY","PP");
   }else if(curFunction == RECORD){
     cmd = pack("REC","PP");
   }else{
      return false;
   }
   if(pauseFlag == 0) return false;
   pauseFlag = 0;
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

String DFRobot_DF1101S::saveRec(){
   if(curFunction != RECORD) return "error";
   sPacket_t cmd;
   cmd = pack("REC","SAVE");
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 0;
   String str = readAck(22);
   if(str != "error"){
    return str;
   } else{
    return "error";
   }
}

bool DFRobot_DF1101S::delCurFile(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   
   cmd = pack("DEL");
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }

}
bool DFRobot_DF1101S::playSpecFile(String str){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAYFILE",str);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_DF1101S::playSpecFile(int16_t num){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAYFILE",String(num));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }


}
DFRobot_DF1101S::sPacket_t DFRobot_DF1101S::pack(String cmd ,String para){
  sPacket_t pack;
  atCmd = "";
  atCmd += "AT";
  if(cmd != " "){
   atCmd += "+";
   atCmd += cmd;
  }
 
  if(para != " "){
   atCmd += "=";
   atCmd += para;
  }
  atCmd += "\r\n";
  pack.str = atCmd;
  pack.length = atCmd.length();
  return pack;
}
void DFRobot_DF1101S::writeATCommand(String command,uint8_t length){
   uint8_t data[40];
   //Serial.print(command);
    while(_s->available()) {
         _s->read();
    }
   for(uint8_t i=0;i<length;i++)
      data[i] = command[i];
   _s->write(data,length);
}



String DFRobot_DF1101S::readAck(uint8_t len){

  String str="                           ";
  size_t offset = 0,left = len;
  long long curr = millis();
  while(left) {
    if(_s->available()) {
       str[offset]= _s->read();
      left--;
      offset++;
    }
    if(millis() - curr > 1000) {
      return "error";
      break;
    }
  }
  str[len]=0;
  return str;
}




