#include <LiquidCrystal.h> 

// github.com/forgeworksdev

//         :XXXXo;'                .;lXXXXl         
//         cNX....                  ....KNo         
//         ,do                          ld;         
//         ...    .cccccc:  ;cccccc.    ...         
//                ,NNxx0N0  kNKxxNN:                
//                'KK. cKk  xKo  KK;                
//                .::  .:;  ,:'  ::.                
//              ,::::  .::::::'  ::::;              
//                                                  
//              cxc  ',. .xx. .,,  :xo              
//         .'.  ,:,  ...  ::.  ..  ':;  .'.         
//         ,xd                          lx;         
//         cNX''..                  ..''KNo         
//         :KKKKl;'                .;cKKKKc         
                                                  
// ForgeWorks

// In engineering I trust.

//licensed under the GNU AFFERO GENERAL PUBLIC LICENSE

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Isso é um(a).....

//Relógio ajustável (Não RTC)

int hours = 12;
int minutes = 0;
int seconds = 0;

bool ispmflag = false;

const char message[] = "In engineering I trust.  ";
int textposition = 0;

// Podem ser qualquer pino digital com um resistor de pullup interno
#define hoursetpin 8 
#define minutesetpin 9

// Pinos do display. Para uso sem chip ADC. Altere conforme o necessário
const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

void setup() {
  // INPUT_PULLUP remove a necessidade de resistores para os botões
  pinMode(hoursetpin, INPUT_PULLUP);
  pinMode(minutesetpin, INPUT_PULLUP);

 Serial.begin(9600);

 lcd.begin(16,2); //Inicia o display, specificando que ele possui 16 colunas e 2 lihas
}


void debugPrint() {
    // Prints time to Serial Monitor for debugging. 
  Serial.print("DEBUGTIME: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  Serial.print("Valor da flag (bool): ");
  Serial.println(ispmflag ? "PM" : "AM");

}

void printTimeToScreen() {
  lcd.print("HORAS:"); 
  if (hours < 10) lcd.print("0");  
  lcd.print(hours); 
  lcd.print(":"); 
  if (minutes < 10) lcd.print("0");  
  lcd.print(minutes); 
  lcd.print(":"); 
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print(ispmflag ? "PM" : "AM");
}

// Switches between AM and PM
void manageFlag() {
  if (hours == 12) {  
    ispmflag = !ispmflag;
  }
}

void limitTime() {
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
  }
  if (minutes >= 60) {
    minutes = 0;
    hours++;
  }
  if (hours > 12) {
    hours = 1;
  }
  manageFlag();
}


void checkButtonPress() {
  if (digitalRead(hoursetpin) == LOW) {
    hours++;  // Only increase hours, don't reset them here
  }
  if (digitalRead(minutesetpin) == LOW) {
    minutes++; 
  }
  limitTime();
}

void printMessageToDisplay() {
  	lcd.setCursor(0,1); 
    for (int i = 0; i < 16; i++) {
        int index = (textposition + i) % strlen(message);
        lcd.print(message[index]);
    }
    textposition = (textposition + 1) % strlen(message);
}
void loop() {
  printMessageToDisplay();
  lcd.setCursor(0,0);
  seconds++;
  printTimeToScreen();
  //debugPrint();
  delay(1000);
  lcd.clear();
  limitTime();
  checkButtonPress();
}

