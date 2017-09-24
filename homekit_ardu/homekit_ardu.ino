/*
 Sample sketch to demonstrate Multi Level JSON parsing in Arduino
 
 This sketch parses the complexly nested JSON
 
 Libraries needed:
 - aJson library for JSON parsing - https://github.com/interactive-matter/aJson
 
 Circuit:
    You don't need any circuit, but need the Arduino board
 Author: 
    Sudar - <http://sudarmuthu.com> <http://hardwarefun.com>
    Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 License:a
    BeerWare ;)
 
 */
#include "aJSON.h"
String Data="" ;
boolean stringComplete=false;
// function definitions
char* parseJson(char *jsonString) ;
// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 4;    // the number of the pushbutton pin
const int relayPin = 31;      // the number of the relay pin

const int LED_HB = 13;

// Variables will change:
int relayState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Json string to parse
//char jsonString[] = "{\"Accessory\":{\"Name\":\"Light\",\"Status\":{\"Color\":[100,100,100],\"Brightness\":100,\"State\":true}}}";

void setup() {
   Serial1.begin(57600);
   Serial.begin(57600);
    pinMode(LED_HB,OUTPUT);
    pinMode(buttonPin,INPUT);
    pinMode(relayPin,OUTPUT);
    pinMode(30,OUTPUT);
    pinMode(1,OUTPUT);
    pinMode(2,OUTPUT);
    digitalWrite(30,LOW);
    //char* value= parseJson(jsonString);
    Data.reserve(300);
    Serial1.println("Starting...");
    Serial1.setTimeout(5000);
}
   

/**
 * Parse the JSON String. Uses aJson library
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 */
struct Accessories {
     int Switches =4;
     int MultiOut=2;
     int Alarm=3;
     int Lights=1;
     
};
char* parseJson(char *jsonString) 
{
    char* value;
    char* AccName ;
    int NumValue;
    bool BoolValue;
   // char *selectedprogram;
//   // bool activate;
//    bool pause;
//    bool state;
//    bool remotetrigger;
//    int brightness;
    
    int SwitchValue=0;
    
    aJsonObject* root = aJson.parse(jsonString);

    if (root != NULL) {
        //Serial.println("Parsed successfully 1 " );
        aJsonObject* Accessory = aJson.getObjectItem(root, "Accessory"); 

       Serial.print(aJson.print(Accessory));
                        if(Accessory != NULL) //parsarw accessory
                        {
                          ////////diko mou
                          aJsonObject* name = aJson.getObjectItem(Accessory, "Name");
                          aJsonObject* status = aJson.getObjectItem(Accessory, "Status");
                          if(name != NULL) // parsarw name
                          {
                             //pianw to paidi name
                            AccName = name->valuestring; //pairnw thn timh tou name..gia na kserw me poio accessory exw na kanw
                            //do something
                            if(strcmp(AccName,"Light")==0)
                            {
                              SwitchValue=1;
                              Serial.print(SwitchValue);
                            }
                             if(strcmp(AccName,"Alarm")==0)
                            {
                              SwitchValue=3;
                            }
                             if(strcmp(AccName,"Mul")==0)
                            {
                              SwitchValue=2;
                            }
                             if(strcmp(AccName,"Switch")==0)
                            {
                              SwitchValue=4;
                            }
                            
                            switch(SwitchValue) //case gia na praksw analogws to Accessory pou irthe
                           {
                             case 1:
                             
                             
                             if(status != NULL) //parsarw status 
                             {
                               
                               
                                aJsonObject* brightness = aJson.getObjectItem(status, "Brightness");
                               if(brightness != NULL) //parsarw brightness
                               {
                                
                                 NumValue = brightness->valueint; // pairnw thn timh tou brightness
                                 //do something
                                 
                               }
                               aJsonObject* state = aJson.getObjectItem(status, "State");

                               if(state != NULL) // parsarw state
                               {
                                 Serial.println("mphkw sto state");
                                 
                                 BoolValue = state->valuebool;
                                 if(BoolValue==1)
                                 {
                                   
                                  digitalWrite(relayPin,HIGH); 
                                 Serial.println("ena");
                                 }
                                 else
                                 {
                                   digitalWrite(relayPin,LOW); 
                                   Serial.println("0");
                                   
                                 }
                                 //do something
                                 aJson.deleteItem(root);
                                 return "ok";
                                 
                               }
                             }
                             
                             break;
                             case 2: // parsarw to switch
                             if(status != NULL) //parsarw to status
                             {
                              
                               
                               aJsonObject* state = aJson.getObjectItem(status, "one");
                               if(state != NULL) //parsarw to state
                               {
                                 
                                 BoolValue = state->valuebool;
                                 if(BoolValue == true) //anavw diakopth
                                    digitalWrite(1,HIGH);
                                else
                                    digitalWrite(1,LOW);
                                 //do something
                               }
                               state = aJson.getObjectItem(status, "two");
                               if(state != NULL) //parsarw to state
                               {
                                 
                                 BoolValue = state->valuebool;
                                 if(BoolValue == true) //anavw diakopth
                                    digitalWrite(2,HIGH);
                                else
                                    digitalWrite(2,LOW);
                                 //do something
                               }
                               aJson.deleteItem(root);
                               return "ok";
                             }
                        
                             //do something
                             break;
                             case 3: //parsarw to alarm
                             if(status != NULL) //parsarw status
                             {
                               aJsonObject* remotetrigger = aJson.getObjectItem(status, "RemoteTrigger");
                              if(remotetrigger != NULL) //parsarw remote
                              {
                               
                                BoolValue = remotetrigger->valuebool;
                                
                               
                                //do something
                                return "ok";
                              }
                             aJsonObject* state = aJson.getObjectItem(status, "State");
                             if(state != NULL) //parsarw state
                             {
                               
                               BoolValue = state->valuebool;

                               digitalWrite(2,BoolValue==true ? HIGH : LOW);
                               
                               
                             }
                             aJson.deleteItem(root);
                              return "ok";
                             }
                             
                             
                             break;
                             
                             case 4:
                             if(status != NULL)
                             {
                               
                                aJsonObject* state = aJson.getObjectItem(status, "State");
                               if(state != NULL)
                               {
                                
                                 BoolValue = state->valuebool;
                                 digitalWrite(relayPin,BoolValue==true?HIGH:LOW);
                                 //do something                              
                               }
                               
                               aJson.deleteItem(root);
                               return "ok";
                             }
                             
                             break;
                             default:
                             //ti na valw ?????
                             break;
                             
                           }
                            
                          }
                           
                           
                           
                        }
                   
                    }
                    aJson.deleteItem(root);
                    return "fail";
}

uint8_t hbval = 245;
int8_t hbdelta = 8;
void heartbeat() {
  static unsigned long last_time = 0;
  unsigned long now = millis();
  if ((now - last_time) < 40)
    return;
  last_time = now;
  if (hbval > 192) hbdelta = -hbdelta;
  if (hbval < 32) hbdelta = -hbdelta;
  hbval += hbdelta;
  digitalWrite(LED_HB, !digitalRead(LED_HB));
}

void loop() {
  heartbeat();
  int reading = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
        buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        relayState = !relayState;
        if(relayState == HIGH)
        Serial1.print("{\"Accessory\":{\"Name\":\"Switch\",\"Status\":{\"State\":true}}}!"); // enhmerwnw thn efarmogh dinontas to state tou button
      else
        Serial1.print("{\"Accessory\":{\"Name\":\"Switch\",\"Status\":{\"State\":false}}}!");
      }
    }
  }

  // set the LED:
  //digitalWrite(relayPin, relayState);
  //int statusRelayState=digitalRead(0);
  //digitalWrite(0,!statusRelayState);
  delay(5000);
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;

  
    if (Serial1.available()) {
      Data=Serial1.readStringUntil('\n');
      //stringComplete=false;
    char buf[300];
    Data.toCharArray(buf,300);
    Serial1.println(buf);
    Data="";
    char* value = parseJson(buf);
      if (strcmp(value,"ok")==0) {
                    Serial.print(F("Successfully Parsed: "));
                    Serial1.println("ok!");
          } else {
                    Serial.print(F("There was some problem in parsing the JSON"));
                    Serial1.print("fail!");
         }

  }

}

