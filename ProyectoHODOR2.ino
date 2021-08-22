
/* 
|| Proyecto HODOR.
|| Author: Federico David Ceccarelli
|| fceccarelli@santafe.gov.ar
 
*/

//return true when a 3 digits code is entered. Numbers should be pressed in less than 1 second. 
bool HayCodigo(char*, int);


#include <Keypad.h>

#define Ndigitos 3

    char customKey;
    unsigned long timer;
    bool CodeFlag;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;
char code[Ndigitos];
int pos=0;

void setup() {


    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {

  if (HayCodigo(code,Ndigitos)){
     //   CodeFlag = false;
    
         Serial.print("contraseña: ");
         for(int a=0;a<Ndigitos;a++){
            Serial.print(code[a]);
        }
        Serial.println();
  }
  /*
    if (millis()-timer > 5000) pos=0;
    //Serial.println(timer);
    
      
    if (customKey = kpd.getKey()){
            
            Serial.print("customKey: ");                   
            Serial.println(customKey);
            
            if(pos<2){
              timer=millis();
              code[pos]=customKey;
              pos++;
            }
            else{
              code[pos]=customKey;
              Serial.print("contraseña: ");
              for(pos=0;pos<3;pos++){
              Serial.print(code[pos]);
            }
              pos=0;
              Serial.println();
            }          
     }              

    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

     // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                    if(pos<3){
                        code[pos]=kpd.key[i].kchar;
                        pos++;
                    }
                    else{
                        pos=0;
                        Serial.print("contraseña: ");
                        for(pos=0;pos<3;pos++){
                        Serial.print(code[pos]);
                        }
                      }

                    
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
            }
        }
    }*/
    
}  // End loop

bool HayCodigo(char * codep, int Nnumeros){

      if (millis()-timer > 1000) pos=0;
      
    //Serial.println(timer);
 
     if (customKey = kpd.getKey()){
            
            Serial.print("customKey:");                   
            Serial.println(customKey);
            
            if(pos<Nnumeros-1){
                timer=millis();
                codep[pos]=customKey;
                pos++;
            }
            else{
//                Serial.print(pos);
                codep[pos]=customKey;
                pos=0;
//              Serial.print(pos);
                return true;
            //  CodeFlag = true;
            }
                 
     } 
  return false;
}

