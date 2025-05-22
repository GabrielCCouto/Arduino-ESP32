/****************************************************
FILE:  AMS_5600_example

Author: Tom Denton
www.ams.com
Date: 15 Dec 2014
Version 1.00

Description:  AS5600 "Potuino" demonstration application

AMS5600 Programming Sketch
***************************************************/

#include <Wire.h>
#include <Arduino.h>
#include "AS5600.h"

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SYS_VOL   3.3
#else
  #define SYS_VOL   5
#endif

String lastResponse;
String noMagnetStr = "Error: magnet not detected";

#define SDA_PIN 14
#define SCL_PIN 15

TwoWire myWire(SDA_PIN, SCL_PIN);
AMS_5600 ams5600(myWire);

/*******************************************************
* function: printMenu
* In: none
* Out: none
* Description: prints menu options and result of last
* command
*******************************************************/
void printMenu()
{
  Serial.println("AS5600 Serial Interface Program");
  Serial.println("");
  if(lastResponse.length()>0)
  {
    Serial.println(lastResponse);
    Serial.println("");
  }
  Serial.print("1 - Set start position\t|  "); Serial.println(" 7 - get raw angle");
  Serial.print("2 - Set end position\t|  ");   Serial.println(" 8 - get scaled angle");
  Serial.print("3 - Set max angle range\t|  ");  Serial.println(" 9 - detect magnet");
  Serial.print("4 - Get max angle range\t|  ");  Serial.println("10 - get magnet strength");
  Serial.print("5 - Get start position \t|  ");     Serial.println("11 - get automatic gain conrol");
  Serial.println("6 - get end position \t|  ");
  Serial.println();
  // Serial.print("Number of burns remaining: "); Serial.println(String(3 - ams5600.getBurnCount()));
  Serial.println("96 - Burn Angle");
  Serial.println("98 - Burn Settings (one time)");
}

/*******************************************************
* Function: convertRawAngleToDegrees
* In: angle data from AMS_5600::getRawAngle
* Out: human readable degrees as float
* Description: takes the raw angle and calculates
* float value in degrees.
*******************************************************/
float convertRawAngleToDegrees(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = newAngle * 0.087890625;
  return retVal;
}

/*******************************************************
* Function: convertScaledAngleToDegrees
* In: angle data from AMS_5600::getScaledAngle
* Out: human readable degrees as float
* Description: takes the scaled angle and calculates
* float value in degrees.
*******************************************************/
float convertScaledAngleToDegrees(word newAngle)
{
  word startPos = ams5600.getStartPosition();
  word endPos = ams5600.getEndPosition();
  word maxAngle = ams5600.getMaxAngle();

  float multipler = 0;

  /* max angle and end position are mutually exclusive*/
  if(maxAngle >0)
  {
    if(startPos == 0)
      multipler = (maxAngle*0.087890625)/4096;
    else  /*startPos is set to something*/
      multipler = ((maxAngle*0.087890625)-(startPos * 0.087890625))/4096;
  }
  else
  {
    if((startPos == 0) && (endPos == 0))
      multipler = 0.087890625;
    else if ((startPos > 0 ) && (endPos == 0))
      multipler = ((360 * 0.087890625) - (startPos * 0.087890625)) / 4096;
    else if ((startPos == 0 ) && (endPos > 0))
      multipler = (endPos*0.087890625) / 4096;
    else if ((startPos > 0 ) && (endPos > 0))
      multipler = ((endPos*0.087890625)-(startPos * 0.087890625))/ 4096;
  }
  return (newAngle * multipler);
}

/*******************************************************
* Function: burnAngle
* In: none
* Out: human readable string of success or failure
* Description: attempts to burn angle data to AMS5600
*******************************************************/
String burnAngle()
{
  int burnResult = ams5600.burnAngle();
  String returnStr = "Burn angle error: ";

  switch (burnResult)
  {
    case 1:
      returnStr = "Burn angle success";
      break;
    case -1:
      returnStr += "no magnet detected";
      break;
    case -2:
      returnStr += "no more burns left";
      break;
    case -3:
      returnStr += "no positions set";
      break;
    default:
      returnStr += "unknown";
      break;
  }
  return returnStr;
}

/*******************************************************
* Function: burnMaxAngleAndConfig
* In: none
* Out: human readable string of sucess or failure
* Description: attempts to burn max angle and config data
* to AMS5600
*******************************************************/
String burnMaxAngleAndConfig()
{
  int burnResult = ams5600.burnMaxAngleAndConfig();
  String retStr = "Burn max angle and config error: ";

  switch(burnResult)
  {
    case 1:
      retStr = "Burn max angle and config success";
      break;
    case -1:
      retStr += "chip has been burned once already";
      break;
    case -2:
      retStr += "max angle less than 18 degrees";
      break;
    default:
      retStr += "unknown";
      break;
  }
  return retStr;
}

/*******************************************************
* function: setup
* In: none
* Out: none
* Description: called by system at startup
*******************************************************/
void setup(){
  Serial.begin(115200);
  while (!Serial);  // Importante para placas USB
  myWire.begin();

  delay(1000);
  myWire.beginTransmission(0x36); // Endereço do AMS5600
  if (myWire.endTransmission() == 0) {
    Serial.println("AMS5600 detectado!");
  } else {
    Serial.println("AMS5600 NÃO detectado!");
  }
  delay(1000);
  printMenu();
}


 /*******************************************************
  * Function: loop
  * In: none
  * Out: none
  * Description: main program loop
  *******************************************************/
void loop()
{
  if (Serial.available() > 0)
  {
    char incomingByteBuffer[2] = {0};
    int incomingByte = 0;

    // Lê dois bytes da serial
    Serial.readBytes(incomingByteBuffer, 2);

    Serial.print("Recebido: ");
    Serial.print(incomingByteBuffer[0]);
    Serial.print(" ");
    Serial.println(incomingByteBuffer[1]);

    // Converte ASCII ('0'-'9') para número decimal
    if (incomingByteBuffer[0] >= '0' && incomingByteBuffer[0] <= '9')
    {
      incomingByte = (incomingByteBuffer[0] - '0') * 10;
    }

    if (incomingByteBuffer[1] >= '0' && incomingByteBuffer[1] <= '9')
    {
      incomingByte += (incomingByteBuffer[1] - '0');
    }

    Serial.print("Comando interpretado: ");
    Serial.println(incomingByte);

    // Executa a ação correspondente
    switch (incomingByte)
    {
      case 1:
        Serial.println("Ação: Set Start Angle");
        lastResponse = ams5600.detectMagnet() ?
          "Start angle set to = " + String(convertRawAngleToDegrees(ams5600.setStartPosition()), DEC) :
          noMagnetStr;
        break;

      case 2:
        Serial.println("Ação: Set End Angle");
        lastResponse = ams5600.detectMagnet() ?
          "End angle set to = " + String(convertRawAngleToDegrees(ams5600.setEndPosition()), DEC) :
          noMagnetStr;
        break;

      case 3:
        Serial.println("Ação: Set Max Angle");
        lastResponse = ams5600.detectMagnet() ?
          "Max angle range set to = " + String(convertRawAngleToDegrees(ams5600.setMaxAngle()), DEC) :
          noMagnetStr;
        break;

      case 4:
        Serial.println("Ação: Get Max Angle");
        lastResponse = "Max angle range = " + String(convertRawAngleToDegrees(ams5600.getMaxAngle()), DEC);
        break;

      case 5:
        Serial.println("Ação: Get Start Angle");
        lastResponse = "Start angle = " + String(convertRawAngleToDegrees(ams5600.getStartPosition()), DEC);
        break;

      case 6:
        Serial.println("Ação: Get End Angle");
        lastResponse = "End angle = " + String(convertRawAngleToDegrees(ams5600.getEndPosition()), DEC);
        break;

      case 7:
        Serial.println("Ação: Get Raw Angle");
        lastResponse = "Raw angle = " + String(convertRawAngleToDegrees(ams5600.getRawAngle()), DEC);
        break;

      case 8:
        Serial.println("Ação: Get Scaled Angle");
        lastResponse = "Scaled angle = " + String(convertScaledAngleToDegrees(ams5600.getScaledAngle()), DEC);
        break;

      case 9:
        Serial.println("Ação: Detect Magnet");
        lastResponse = ams5600.detectMagnet() ? "Magnet detected" : noMagnetStr;
        break;

      case 10:
        Serial.println("Ação: Get Magnet Strength");
        if (ams5600.detectMagnet())
        {
          int magStrength = ams5600.getMagnetStrength();
          lastResponse = "Magnet strength ";
          if (magStrength == 1)
            lastResponse += "is weak";
          else if (magStrength == 2)
            lastResponse += "is acceptable. Current Magnitude: " + String(ams5600.getMagnitude());
          else if (magStrength == 3)
            lastResponse += "is too strong";
        }
        else
        {
          lastResponse = noMagnetStr;
        }
        break;

      case 11:
        Serial.println("Ação: Get AGC");
        lastResponse = "Automatic Gain Control = " + String(ams5600.getAgc(), DEC);
        break;

      case 96:
        Serial.println("Ação: Burn Angle");
        lastResponse = burnAngle();
        break;

      case 98:
        Serial.println("Ação: Burn Max Angle and Config");
        lastResponse = burnMaxAngleAndConfig();
        break;

      default:
        Serial.println("Ação: Comando inválido");
        lastResponse = "Invalid Entry";
        break;
    }

    // Mostra resposta e menu novamente
    Serial.println("Resposta: " + lastResponse);
    printMenu();
  }
}
