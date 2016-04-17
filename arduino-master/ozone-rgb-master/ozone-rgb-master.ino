#include "Wire.h"
#include "SPI.h"
#include "Ethernet2.h"
#include "utility/w5500.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 1, 69);
EthernetServer server(80);
String HTTPget = "";

boolean reading = false;
boolean active = false;
boolean interrupt = false;


int t = 0;

void setup() {
  Wire.begin(); 
  Ethernet.begin(mac, ip);
  server.begin();
  //Serial.begin(9600);
  w5500.setRetransmissionTime(0x07D0);
  w5500.setRetransmissionCount(2);
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
    // send http reponse header
    
    //Serial.println(t);
    interrupt = false;
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    // process request.
    processClient(client);
  }
}

void processClient(EthernetClient client)
{
  // http request will end with a blank line
  boolean lineIsBlank = true;
  while (client.connected())
  {
    
    if (client.available())
    {
      char c = client.read();
      if(reading && c == ' ') reading = false;
      if(c == '?') reading = true; // ? in GET request was found, start reading the info
 
      //check that we are reading, and ignore the '?' in the URL, then append the get parameter into a single string
      if(reading && c != '?') HTTPget += c;
 
      if (c == '\n' && lineIsBlank)  break;
      
      if (c == '\n')
      {
        lineIsBlank = true;
      }
      else if (c != '\r')
      {
        lineIsBlank = false;
      }
 
    }
  }

  client.print(HTTPget);
  processData(HTTPget);
  delay(1); // give the web browser a moment to recieve
  client.stop(); // close connection
  active = false;
  HTTPget = ""; // clear out the get param we saved
}

void processData( String data )
{
  data.replace("mode=", "");
  data.replace("&action=", "|");
  
  char * usedData = new char[data.length() + 1];
  strcpy(usedData, data.c_str());
  
  char * mode;
  mode = strtok(usedData, "|");
  
  String originalData;
  originalData = data;
  
  data.replace( mode, "" );
  data.replace( "|", "" );
  
  String actionString = data;
  
  originalData.replace( actionString, "" );
  originalData.replace( "|", "" );
  
  String modeString = originalData;
  
  //Serial.println(modeString);
  //Serial.println(actionString);
  
  if( modeString == "power" )
    handlePower( actionString );
  
  if( modeString == "color" )
    handleColor( actionString );
    
  if( modeString == "party" )
    handleParty( actionString );
}

void handlePower( String action )
{
  int actionInt; 
  
  if( action == "off")
    actionInt = 1;
    
  if( action == "on" )
    actionInt = 2;
    
  //Power  is defined by Mode(1)
  sendWire( 1, actionInt );
} 


void handleColor( String action )
{
  int actionInt; 
  
  actionInt = action.toInt();
  
  //Color is defined by Mode(2)
  sendWire( 2, actionInt );
} 

void handleParty( String action )
{
  int actionInt;
  
  if( action == "beat" )
    actionInt = 1;
    
  //Color is defined by Mode(4)
  sendWire( 4, actionInt );
}

void sendWire( int mode, int action )
{
  Wire.beginTransmission(9);
  Wire.write(0);
  Wire.endTransmission();
  
  Wire.beginTransmission(9);
  Wire.write(mode);
  Wire.endTransmission();
  
  Wire.beginTransmission(9);
  Wire.write(action);
  Wire.endTransmission();
  
  //Serial.println("sendWire");
  //Serial.print("0 - ");
  //Serial.print(mode);
  //Serial.print(" - ");
  //Serial.print(action);
  //Serial.println();
}
