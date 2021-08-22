
/* 
|| Proyecto HODOR.
|| Author: Federico David Ceccarelli
|| fceccarelli@santafe.gov.ar
 
*/

//return true when a 3 digits code is entered. Numbers should be pressed in less than 1 second. 
bool HayCodigo(char*, int,char);
void PrintMenu(void);


#include <Keypad.h>

#define Ndigitos 3 //numero de digitos del codigo de acceso. 

/*--------------------Inicialización de variables-----------------------*/
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

unsigned long loopCount;
unsigned long startTime;
String msg;
char code[Ndigitos], tecla;
int pos=0;

/*--------------------Inicialización de KeyPad-----------------------*/

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {


    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {

  
  tecla = kpd.getKey();
    

  if (tecla){

    if (HayCodigo(code,Ndigitos,kpd.key[0].kchar)){
      
     //   CodeFlag = false;
    
         Serial.print("contraseña: ");
         for(int a=0;a<Ndigitos;a++){
            Serial.print(code[a]);
        }
        Serial.println();
     }
    
     
        
     }

     if((kpd.key[0].kstate==HOLD) && kpd.key[0].kchar == 'C'){
      PrintMenu();
       while(kpd.key[0].kchar != 'D'){
              kpd.getKeys();

        
      }
  }
    

    
}  // End loop

bool HayCodigo(char * codep, int Nnumeros,char tecla){
  

      if (millis()-timer > 1000) pos=0;
      
    //Serial.println(timer);
 
     if (tecla){
                 
            if(pos<Nnumeros-1){
                timer=millis();
                codep[pos]=tecla;
                pos++;
            }
            else{
//               Serial.print(pos);
                codep[pos]=tecla;
                pos=0;
//              Serial.print(pos);
                return true;
            //  CodeFlag = true;
            }
                 
     } 
  return false;
}

void PrintMenu(void){
  Serial.println("-----------------------MENU - CONFIGURACION ---------------------------");
  Serial.println();
  Serial.println("(A)gregar nuevo Acceso");
  Serial.println("(B)orrar nuevo acceso");
  Serial.println("");
  Serial.println("(D) SALIR");
  Serial.println("");
  Serial.println("------------------------------------------------------------------");


   
}

