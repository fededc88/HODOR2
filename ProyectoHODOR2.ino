
/*
  || Proyecto HODOR.
  || Author: Federico David Ceccarelli
  || fceccarelli@santafe.gov.ar

*/

//return true when a 3 digits code is entered. Numbers should be pressed in less than 1 second.
bool ArmarCodigo(char*, int, char);
void PrintMenu(void);
bool agregarPin(void);
void borrarPin(void);
bool Validacion(void);
bool Aceptar(void);
void cerradura(void);
void parpadeoRojo(void);
void parpadeoVerde(void);




#include <Keypad.h>
#include <EEPROM.h>


#define Ndigitos 3 //numero de digitos del codigo de acceso.
#define adrPass 1020 //direccion de la Contraseña Maestra en EEPROM
#define ledPinV 12
#define ledPinR 11


/*--------------------Inicialización de variables-----------------------*/
char customKey;
unsigned long timer;
bool CodeFlag, AbrirPuerta = false;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the kpd

unsigned long loopCount;
unsigned long startTime;
String msg;
char code[Ndigitos], codeV[Ndigitos], tecla;
int pos = 0, Ncod = 50; //Ncod es el numero de codigos que se pueden agregar
static char pass[Ndigitos];

/*--------------------Inicialización de KeyPad-----------------------*/

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {


  Serial.begin(9600);
  loopCount = 0;
  startTime = millis();
  msg = "";

  // Serial.println(EEPROM.length());

  //carga Pass de administrador guardado en la EEPROM en una variable global
  for (int i = 0; i < Ndigitos; i++) {
    EEPROM.get(adrPass + i, pass[i]);
  }
  
    pinMode(ledPinV, OUTPUT);
    pinMode(ledPinR, OUTPUT);
    pinMode(13, OUTPUT);

  //calculo numero de codigos en memoria.

  digitalWrite(ledPinV,HIGH);
  digitalWrite(ledPinR,LOW);
  


}

void loop() {

  digitalWrite(ledPinR,LOW);
  tecla = kpd.getKey();

  if (tecla) {
    if (ArmarCodigo(code, Ndigitos, kpd.key[0].kchar)) {

      //   CodeFlag = false;

      for (int i = 0; i <= (Ncod * Ndigitos); i = i + Ndigitos) {
        for (int a = 0; a < Ndigitos; a++) {
          EEPROM.get(i + a, codeV[a]);
          // Serial.print(codeV[a]);
        }
        if (code[0] == codeV[0] && code[1] == codeV[1] && code[2] == codeV[2]) {
          cerradura();
          break;
        }
        else if(i== (Ncod * Ndigitos)) parpadeoRojo();
      }

      //Me permite conocer la contraseña ingresada!
      //      Serial.print("contraseña: ");
      //      for (int a = 0; a < Ndigitos; a++) {
      //        Serial.print(code[a]);
      //      }
      //      Serial.println();
    }
  }
 

  if ((kpd.key[0].kstate == HOLD) && kpd.key[0].kchar == 'C' && Validacion()) {
   
   digitalWrite(ledPinR,HIGH);
   PrintMenu();
   
    while (kpd.key[0].kchar != 'D') {
      if ( kpd.getKeys()) {
        if ( kpd.key[0].stateChanged && kpd.key[0].kstate == PRESSED) {
          switch (kpd.key[0].kchar) {

            case 'A':
              agregarPin();
              PrintMenu();
              break;

            case 'B':
              borrarPin();
              PrintMenu();
              break;

            case 'D':
              break;

            default:
              Serial.println("\nSaca la mano de ahi antonio!!\n\r");
              parpadeoRojo();
              digitalWrite(ledPinR, HIGH);              
              PrintMenu();
              break;
          }
        }
      }
    }
  }



}  // End loop

void borrarPin(void) {

  int EEaddress = 0;

  EEaddress = Posicion() * 3;

  if (EEaddress >= 0 && EEaddress < (Ncod*3)) {
    for (int a = 0; a < Ndigitos; a++) {
      EEPROM.update(EEaddress + a, 'n');
    }
    parpadeoVerde();
  }
  else{
    Serial.println("\n\rLa posición es erronea...");
    parpadeoRojo();
    digitalWrite(ledPinR, HIGH);
  }
}
bool agregarPin(void) {


  bool HayPos = false, HayCodigo = false;
  char pos[2];
  int EEaddress = 0;
  int codei = 0;
  char codec[Ndigitos];
  char prueba[Ndigitos];


  //           kpd.getKeys();

  EEaddress = Posicion() * 3;


  Serial.println("Ingrese clave de 3 dígitos:");

  while (!HayCodigo) {
    tecla = kpd.getKey();
    if (tecla) {
      if (ArmarCodigo(codec, Ndigitos, tecla)) {
        Serial.print("Usted ingreso: ");
        for (int i = 0; i < Ndigitos; i++) {
          Serial.print(codec[i]);
        }
        Serial.println();
        HayCodigo = true;
      }
    }
  }

  if (EEaddress >= 0 && EEaddress < (Ncod*3)) {

    for (int a = 0; a < Ndigitos; a++) {
      EEPROM.update(EEaddress + a, codec[a]);
    }
    parpadeoVerde();
    
    Serial.print("El numero Guardado es: ");
    for (int a = 0; a < Ndigitos; a++) {
      EEPROM.get(EEaddress + a, prueba[a]);
      Serial.print(prueba[a]);
    }
    Serial.print("\nEn Address: ");
    Serial.print(EEaddress);
  }
  else{
    parpadeoRojo();
    digitalWrite(ledPinR, HIGH);
    
  }





  return true;
}

void cerradura(void) {
  AbrirPuerta = false;
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

void parpadeoRojo(void){

 //     Serial.print("Wrong pass");

  for(int i=0;i<3;i++){


      digitalWrite(ledPinR, HIGH);
      delay(200);
      digitalWrite(ledPinR, LOW);
      delay(200);
}
 
}

void parpadeoVerde(void){

 //     Serial.print("Wrong pass");

  for(int i=0;i<3;i++){


      digitalWrite(ledPinV, LOW);
      delay(200);
      digitalWrite(ledPinV, HIGH);
      delay(200);
}
 
}

int Posicion(void) {


  bool HayPos = false;
  char pos[2];
  int posi = 0;



  Serial.println("Ingrese posición:");

  while (!HayPos) {
    tecla = kpd.getKey();
    if (tecla) {
      if (ArmarCodigo(pos, Ndigitos - 1, kpd.key[0].kchar)) {
        posi = atoi(pos);

        Serial.print("\n\rUsted ingreso la posicion: ");
        Serial.println(posi);
        if (Aceptar()) {
          HayPos = true;
          return posi;
        }
        else  Serial.println("Ingrese posición:");
      }
    }
  }
}

bool Validacion(void) {

  char code[3];
  bool salir = false;
  char tecla;

  Serial.print("\nIngrese Pass...\n\r");

  while (!salir) {
    tecla = kpd.getKey();
    if ( ArmarCodigo(code, Ndigitos, tecla)) {
      if (code[0] == pass[0] && code[1] == pass[1] && code[2] == pass[2]) {
        salir = true;
        return true;
      }
      else {
        Serial.print("\nCodigo Incorrecto\n\rIngrese Pass...\n\r");
        parpadeoRojo();    
      }
    }
  }

  return false;
}

bool Aceptar(void) {

  bool salir = false;
  Serial.println();
  Serial.println("Es correcto?");
  Serial.println("(A) aceptar - (B) volver a elegir");
  Serial.println();

  while (!salir) {

    if ( kpd.getKeys()) {
      if ( kpd.key[0].stateChanged && kpd.key[0].kstate == PRESSED) {
        switch (kpd.key[0].kchar) {

          case 'A':
            salir = true;
            return true;
            break;

          case 'B':
            salir = true;
            return false;
            break;

          default:
            Serial.println("\nSaca la mano de ahi antonio!!\n\r");
            parpadeoRojo();
            digitalWrite(ledPinR, HIGH);
            Serial.println("Es correcto?");
            Serial.println("(A) aceptar - (B) volver a elegir");
            break;
        }
      }
    }
  }
}

bool ArmarCodigo(char * codep, int Nnumeros, char tecla) {


  if (millis() - timer > 3000) pos = 0;

  //Serial.println(timer);

  if (tecla) {
    Serial.print('*');

    if (pos < Nnumeros - 1) {
      timer = millis();
      codep[pos] = tecla;
      //               Serial.print(codep[pos]);
      pos++;

    }
    else {
      //               Serial.print(pos);
      codep[pos] = tecla;
      //               Serial.print(codep[pos]);
      pos = 0;
      //              Serial.print(pos);
      return true;
      //  CodeFlag = true;
    }

  }
  return false;
}

void PrintMenu(void) {

  String menu = "\n\r-----------------------MENU - CONFIGURACION ---------------------------\n\n\r(A)gregar nuevo Acceso\n\r(B)orrar nuevo acceso\n\r(D) SALIR\n\n\r------------------------------------------------------------------\n\r";
  Serial.print(menu);
}

