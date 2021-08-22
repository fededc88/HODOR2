
/* 
|| Proyecto HODOR.
|| Author: Federico David Ceccarelli
|| fceccarelli@santafe.gov.ar
 
*/

//return true when a 3 digits code is entered. Numbers should be pressed in less than 1 second. 
bool HayCodigo(char*, int,char);
void PrintMenu(void);
bool agregarPin(void);



#include <Keypad.h>
#include <EEPROM.h>


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
          if( kpd.getKeys()){
            if ( kpd.key[0].stateChanged && kpd.key[0].kstate == PRESSED){
                  switch (kpd.key[0].kchar){

                    case 'A':
                      agregarPin();
                      PrintMenu();
                      Serial.println(kpd.key[0].kchar);
                      Serial.println(kpd.key[0].stateChanged);
                      break;

                    case 'B':
                     Serial.println("CASE B");
                     break;

                    default:
                      break;
                  }
              
            }
            
          }
                    
      }
  }
    

    
}  // End loop
bool agregarPin(void){
  

  bool HayPos=false;
  char pos[2];
  int posi=0; 
  int codei=0;
  char codec[Ndigitos-1];
  

//           kpd.getKeys();            
           Serial.println("Ingrese posición:");                                          
           
           while(!HayPos){ 
                   tecla = kpd.getKey();   
                    if (tecla){
                          if (HayCodigo(pos,Ndigitos-1,kpd.key[0].kchar)){
                             posi = atoi(pos);                      

                        Serial.print("Usted ingreso la posicion: ");  
                        Serial.println(posi);
                        HayPos=true;                     
                     }
                    }
           }
                     
           Serial.println("Ingrese clave de 3 dígitos:"); 

            while(kpd.key[0].kchar != 'D'){ 
                   tecla = kpd.getKey();   
                    if (tecla){
                          if (HayCodigo(codec,Ndigitos,kpd.key[0].kchar)){
                                                   
                        codei=atoi(codec);
                        Serial.print("Code: ");  
                        Serial.println(codei);
                     }
                    }
            }
            
                        
                    
                        
                        
                      
       
  kpd.getKeys();
  return true;
}
 
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

  String menu = "-----------------------MENU - CONFIGURACION ---------------------------\n\n\r(A)gregar nuevo Acceso\n\r(B)orrar nuevo acceso\n\r(D) SALIR\n\n\r------------------------------------------------------------------\n\r";
  //String RC = "   /s:`        `-/+-                                             \n\r                                    -y+`-o+.  `:oo+omo`                                             \n\r                                  `os` ./ .oyoo-`.sy.                                               \n\r                                 -y: -/+/.`o+/``+h:                                                 \n\r                                +y.-`o`o `+:+./hoso`   `..``````````                                \n\r                              `ys` +/s://s:::h+`.o/doo+//:::////:-:/oo+.                            \n\r                              `+ys. `:-oo-.+h.  `y:m`                 .s+                           \n\r                                `ho /so::`.N/////:+h`-:///:`            s/                          \n\r                                `m+++++-  +m-      +y/-```:h:           +s                          \n\r                                :m/::-   ++`     `+d`      `/`        `/y.`:o/  .:+.                \n\r                                h/ -:./hy    `/oy+/N-   `-:///+o+///:/dhooo/-moo+-.h`               \n\r                               sh`:sdNNd.  -so//://hmhoo++m:..``    `.N/    .m/-/o++`               \n\r                              -Nhdo+MNo` `sy:h+:No+/--+o:-m.      ```-N- `:.o/s.-m-                 \n\r                             .hNo` :Ns` -h/+h- +h  :dso-:ys`      ```+m`  -//:dh//y/                \n\r                           .oNN+ ./+:  :h-yNho+d.  y/ .my+y.      ```do      `hys+ooy`              \n\r                        `-yNNNd`/my`  :y.dNNNNNNo-/s  `m```      `.:ho`       `.Ns+/s.              \n\r                       :hNNNNNy  `   -y.dNNNNNNNNNhy/.s/       `+yo+..:  `:+++//-`                  \n\r                     :hNNNNNNNN:    `h.yNNNNNNNNm:/d/+:   `:/o+:` /o+ym++/-`                        \n\r                   -hNNNNdNNNNNNs.  o:/NNNNNNNNN/+y`   .//ssymo` -+++:`                             \n\r                 `sNNNhhmNNNNNNNN- .s`dNNNNNNNd-os``/+osyhdhdhdh:-`                                 \n\r                :mNh+omNNNNNNNNNm` o`:NNNNNNNm-od+oosyddhhhddyom`                                   \n\r               :Nh- hNNNNNNNNNNNy `o /:.oNNNN-/m+oydhhhhddh+:/+s.                                   \n\r               +:   .sNNNNNNNNNM/ .+    -+`.o.dmddhdhddyo:+o+-`                                     \n\r                      `+MNNNNNNM. -/`o.    .-sdhhddmh+:/oo:`                                        \n\r                        ydNNNNNM` :/`mm- -y//dhdmds:/os/`                                           \n\r                          :dNNNM. :/ hNosNs:ddds//oo:`                                              \n\r                          -sysmN+ .o oNNNs/mds/oo/`                                                 \n\r                       `+hy/:/dNd` s``oo:+h:/so.                                                    \n\r                     `/dy::odmddNs:oh//ohdmd+`                                                      \n\r                    :hs::/ddhhhmh+++hdhdmm/`                                                        \n\r                  `omo+osmdhddmh+//oysss+`                                                          \n\r                   ..`````   `                            \n\r";
  Serial.print(menu);
//  Serial.print(RC);
  
}

