#include "AlaLedRgb.h"
#include "rgb_pins.h"
#include "Wire.h"

int currentNumber = 0;

AlaLedRgb alaLedWindow;
AlaLedRgb alaLedTV;
AlaLedRgb alaLedKitchen;


AlaColor color_[1] = { 0xFFFFFF };
AlaPalette color = { 1, color_ };

AlaColor color_10[1] = { 0xFF0000 };
AlaPalette color10 = { 1, color_10 };
AlaColor color_11[1] = { 0xEF016E };
AlaPalette color11 = { 1, color_11 };
AlaColor color_12[1] = { 0xEF0197 };
AlaPalette color12 = { 1, color_12 };
AlaColor color_13[1] = { 0xF100BA };
AlaPalette color13 = { 1, color_13 };
AlaColor color_14[1] = { 0xF100BA };
AlaPalette color14 = { 1, color_14 };

AlaColor color_20[1] = { 0x0000FF };
AlaPalette color20 = { 1, color_20 };
AlaColor color_21[1] = { 0x01B0F4 };
AlaPalette color21 = { 1, color_21 };
AlaColor color_22[1] = { 0x01B0F4 };
AlaPalette color22 = { 1, color_22 };
AlaColor color_23[1] = { 0x00E4E4 };
AlaPalette color23 = { 1, color_23 };
AlaColor color_24[1] = { 0x01F0CE };
AlaPalette color24 = { 1, color_24 };

AlaColor color_30[1] = { 0x00FF00 };
AlaPalette color30 = { 1, color_30 };
AlaColor color_31[1] = { 0x61F900 };
AlaPalette color31 = { 1, color_31 };
AlaColor color_32[1] = { 0x7CF000 };
AlaPalette color32 = { 1, color_32 };
AlaColor color_33[1] = { 0xA5F900 };
AlaPalette color33 = { 1, color_33 };
AlaColor color_34[1] = { 0xC2F201 };
AlaPalette color34 = { 1, color_34 };

AlaPalette colorTemp;

AlaColor brightness[11] = { 0xFFFFFF, 0xe5e5e5, 0xcccccc, 0xb2b2b2, 0x999999, 0x7f7f7f, 0x666666, 0x4c4c4c, 0x333333, 0x191919, 0x000000 };

int x = 0;

int currentPointer = 0;
int currentMode = 0;
int currentAction = 0;
int currentGroup = 6;
int currentBrightness = 0;
int currentBrightnessGroups[3] = {0,0,0};

void setup()
{
  Serial.begin(9600);
  
  alaLedWindow.initTLC5940(7, stripWindow);
  alaLedWindow.setAnimation(ALA_ON,  1000, color10);
  
  alaLedTV.initTLC5940(3, stripTV);
  alaLedTV.setAnimation(ALA_ON,  1000, color20);
  
  alaLedKitchen.initTLC5940(2, stripKitchen);
  alaLedKitchen.setAnimation(ALA_ON, 1000, color30);
  
  refreshBrightness( true );
  
  Wire.begin(9); 
  Wire.onReceive(receiveEvent);
}

int returnBrightness()
{
  if( currentGroup == 6 )
    return currentBrightness;
  else if( currentGroup == 7 )
    return currentBrightnessGroups[0];
  else if( currentGroup == 8 )
    return currentBrightnessGroups[1];
  else if( currentGroup == 9 )
    return currentBrightnessGroups[2];
}

void updateBrightness( int newValue )
{
  if( currentGroup == 6 )
  {
    currentBrightness = newValue;
    currentBrightnessGroups[0] = newValue;
    currentBrightnessGroups[1] = newValue;
    currentBrightnessGroups[2] = newValue;
  }
  else if( currentGroup == 7 )
    currentBrightnessGroups[0] = newValue;
  else if( currentGroup == 8 )
    currentBrightnessGroups[1] = newValue;
  else if( currentGroup == 9 )
    currentBrightnessGroups[2] = newValue;
}

void decreaseBrightness()
{ 
  int tempBrightness = returnBrightness();
  if( tempBrightness != 10 )
  {
    tempBrightness++;
    updateBrightness( tempBrightness );
    refreshBrightness( false );
  }  
}

void increaseBrightness()
{
  int tempBrightness = returnBrightness();
  if( tempBrightness != 0 )
  {
    tempBrightness--;
    updateBrightness( tempBrightness );
    refreshBrightness( false );
  } 
}

void refreshBrightness( int reset )
{
  Serial.println(currentBrightness);
  
  if( reset )
  {
    currentGroup = 6;
    currentBrightness = 0;
    currentBrightnessGroups[0] = 0;
    currentBrightnessGroups[1] = 0;
    currentBrightnessGroups[2] = 0;
  }
    
  if( currentGroup == 6 || currentGroup == 7)
    alaLedWindow.setBrightness(brightness[returnBrightness()]);
    
  if( currentGroup == 6 || currentGroup == 8)
    alaLedTV.setBrightness(brightness[returnBrightness()]);
  
  if( currentGroup == 6 || currentGroup == 9)
    alaLedKitchen.setBrightness(brightness[returnBrightness()]);
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
  //Serial.println(x);
  
  if( x == 0 )
   currentPointer = 0;
  
  if( currentPointer == 1 )
   currentMode = x;
  
  if( currentPointer == 2)
  {
   currentAction = x;
   handleChange( currentMode, currentAction );
  }
  
  currentPointer++;
}

void handleChange( int mode, int action )
{
  Serial.println( mode );
  Serial.println( action );
   
  if( mode == 1 )
    handlePower( action );
  
  if( mode == 2 )
    handleColor( action );
    
  if( mode == 4 )
    handleParty( action );
}

void handlePower( int action )
{
  if( action == 1 )
  {
    currentGroup = 6;
    alaLedWindow.setAnimation(ALA_OFF,  1000, color);
    alaLedTV.setAnimation(ALA_OFF,  1000, color);
    alaLedKitchen.setAnimation(ALA_OFF,  1000, color);
  }
  
  if( action == 2 )
  {
    currentGroup = 6;
    alaLedWindow.setAnimation(ALA_ON,  1000, color);
    alaLedTV.setAnimation(ALA_ON,  1000, color);
    alaLedKitchen.setAnimation(ALA_ON,  1000, color);
  }
}

void handleColor( int action )
{
  
  if( action == 2 )
  {
    increaseBrightness();
    return;
  }
  
  if( action == 3 )
  {
    decreaseBrightness();
    return;
  }
  
  if( action >= 6 && action <= 9 )
  {
    currentGroup = action;
    return;
  }
  
  if( action == 1 )
    colorTemp = color;
  else if( action == 10 )
    colorTemp = color10;
  else if( action == 11 )
    colorTemp = color11;
  else if( action == 12 )
    colorTemp = color12;
  else if( action == 13 )
    colorTemp = color13;
  else if( action == 14 )
    colorTemp = color14;
  else if( action == 20 )
    colorTemp = color20;
  else if( action == 21 )
    colorTemp = color21;
  else if( action == 22 )
    colorTemp = color22;
  else if( action == 23 )
    colorTemp = color23;
  else if( action == 24 )
    colorTemp = color24;
  else if( action == 30 )
    colorTemp = color30;
  else if( action == 31 )
    colorTemp = color31;
  else if( action == 32 )
    colorTemp = color32;
  else if( action == 33 )
    colorTemp = color33;
  else if( action == 34 )
    colorTemp = color34;
    
  if( currentGroup == 6 || currentGroup == 7)
    alaLedWindow.setAnimation(ALA_ON,  1000, colorTemp);
  if( currentGroup == 6 || currentGroup == 8)
    alaLedTV.setAnimation(ALA_ON,  1000, colorTemp);
  if( currentGroup == 6 || currentGroup == 9)
    alaLedKitchen.setAnimation(ALA_ON,  1000, colorTemp);
}

void handleParty( int action )
{
  refreshBrightness( true );
  
  alaLedWindow.setAnimation(animations[random(0,30)], 1000, alaPalRgb);
  alaLedTV.setAnimation(animations[random(0,30)],  1000, alaPalRgb);
  alaLedKitchen.setAnimation(animations[random(0,30)], 1000, alaPalRgb);
}

void loop()
{
  alaLedWindow.runAnimation();
  alaLedTV.runAnimation();
  alaLedKitchen.runAnimation();
}

