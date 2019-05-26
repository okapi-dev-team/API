#include <Arduino.h>

const char user[4];

void userAnlegen(char nameChar, char rechteChar, char codeChar, char rfidChar)
{
  const char user[4]={nameChar,rechteChar,codeChar,rfidChar};
}

void setup()
{
  userAnlegen('Nutzer 1','master','1234','xxxx xxxx xxxx');
  Serial.begin(9600);
  for(int i=0;i<4;i++)
  {
    Serial.print(user[i]);
  }
}

void loop()
{
}