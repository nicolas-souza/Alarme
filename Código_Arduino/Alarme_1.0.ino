#include <Keypad.h>

#define LEDL 12
#define LEDA 13

#define LIVRE 1  // Define que o estados seriam representados por numeros, 1-LIVRE e 2-ARMADO
#define ARMADO 2 // O controle será pela variável ESTADO

#define BUZZER 10 

#define SP 11 //SENSOR DE PRESENÇA

/*CONTROLE PARA PISCAR SEM DELAY*/
long previousMillisVERDE = 0; 
long LedIntervalVERDE = 500;
int statusLedVERDE = LOW;

/*BUZZER*/
long previousMillisBUZZER = 0; 
long IntervalBUZZER = 5000; //20 SEGUNDOS

char* password = "123"; //SENHA

/*DECLARAÇÃO DO TECLADO*/

int position = 0; 
const byte LINHA = 4; 
const byte COLUNA = 4; 
char BUTTON[LINHA][COLUNA] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte linhaPins[LINHA] = { 8, 7, 6, 9 }; 
byte colunasPins[COLUNA] = { 5, 4, 3, 2 }; 
Keypad keypad = Keypad( makeKeymap(BUTTON), linhaPins, colunasPins, LINHA, COLUNA );

/*VARIÁVEIS DE APOIO*/

int ESTADO = LIVRE;
int PISCA;
int SENSOR=0;
int FLAG=0;
int FLAG1=0;

void setup(){
 
 pinMode (LEDL, OUTPUT);
 digitalWrite(LEDL, HIGH);
 
 pinMode (LEDA, OUTPUT);
 digitalWrite(LEDA, LOW);
 
 pinMode (BUZZER, OUTPUT);
 digitalWrite(BUZZER, LOW);

 pinMode (SP, INPUT_PULLUP);
 
 PISCA =0;
 ESTADO = LIVRE;

}

void loop(){
  unsigned long currentMillisLIVRE = millis(); 
  unsigned long currentMillisARMADO = millis(); 
  
 char senha = keypad.getKey();

/*       LIVRE       */
      
  if (ESTADO==LIVRE){
  

    if (senha != NO_KEY){
   
      FLAG++;
    
      if (senha == '*' || senha == '#') { 
        position = 0; 
      
      }
      if (senha == password[position]){ 
        position ++;
      }
      if (position == 3){
        ESTADO = ARMADO;
        FLAG = 0;
      
        digitalWrite (LEDL, LOW);
        digitalWrite (LEDA, HIGH);
    
        senha = NO_KEY;
    
      }
    }
    if (FLAG>3){
        if (currentMillisLIVRE - previousMillisVERDE > LedIntervalVERDE) { 
          previousMillisVERDE = currentMillisLIVRE; 
 
          if (statusLedVERDE == LOW) { 
            statusLedVERDE = HIGH; 
          } else { 
            statusLedVERDE = LOW; 
          }
        }
     digitalWrite(LEDL, statusLedVERDE);
    }
  }
  
 /*    ARMADO     */
  

  if(ESTADO==ARMADO){
    if(FLAG1==0){ 
      if (digitalRead(SP)==LOW){
        SENSOR = 1;
        previousMillisBUZZER = currentMillisARMADO; 
        FLAG1=1;
      }
    }
    if (SENSOR==1){
        if (currentMillisARMADO - previousMillisBUZZER > IntervalBUZZER) { 
        previousMillisBUZZER = currentMillisARMADO; 
        digitalWrite(BUZZER, HIGH);

      }
    }
    
    if (senha != NO_KEY){
    
  
      if (senha == '*' || senha == '#') {
        position = 0; 
      
      }
      if (senha == password[position]){ 
      position ++;
      }
      if (position == 3){ 
        ESTADO = LIVRE;
        SENSOR = 0;
        FLAG1=0;
        digitalWrite(BUZZER, HIGH);
        delay(3000);
        digitalWrite(BUZZER, LOW);
        digitalWrite (LEDL, HIGH);
        digitalWrite (LEDA, LOW);
      }
    


    }
  
  }
}
