
// INCLUSÃO DE BIBLIOTECAS

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DEFINIÇÕES

#define endereco 0x27 // Endereço comuns 0x27, 0x3F
#define colunas 16
#define linhas 2

// INSTANCIANDO OBJETOS
LiquidCrystal_I2C lcd(endereco, colunas, linhas);



   //INNOVATION
  // PINOS USADOS QTA  
  int ING = 13; // OUT CINZA
  int CHOKE = 12; // OUT BRANCO
  int START = 11; //OUT  ROXO
  int CONTACRD = A2; //OUT LARANGA
  int CONTACGE = A3; //OUT 
  int REDE = 2; //IN   VERDE  
  int GERADOR = 3; //IN AZUL
  int led_carga=4;
  int led_rede = 5; // OUT 
  int led_gerador = 6; // OUT
  const int pino_buzzer = 1;
  // int botao;

  int STREDE;
  int STGER;
  int PARTGER;


   


void setup(){
   
   //LCD
   
  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY  
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY 
  lcd.clear(); // LIMPA O DISPLAY

  lcd.setCursor(0,0);
 lcd.print("  INNOVATION  ");
 delay(5000); //DELAY DE 5 SEGUNDOS
 lcd.setCursor(0,1); // POSICIONA O CURSOR NA PRIMEIRA COLUNA DA LINHA 2
 lcd.print(" QTA Versao 2.0 ");
 lcd.clear();
 
 lcd.setCursor(0,0);
 lcd.print("     Aguarde     ");  
 delay (2000);
 lcd.setCursor(0,1); 
 lcd.print("    Ligando     ");
 lcd.clear();
    

  // CONFIGURACAO PINOS IN OUT

  pinMode (ING, OUTPUT); //IGNICAO
  pinMode (CHOKE, OUTPUT); //AFOGADOR
  pinMode (START, OUTPUT); //PARTIDA
  pinMode (CONTACRD, OUTPUT); //CONTATORA REDE
  pinMode (CONTACGE, OUTPUT);// CONTATORA GERADOR
  pinMode (REDE, INPUT);// ENTRADA STATUS REDE
  digitalWrite(REDE, 1);
  pinMode (GERADOR, INPUT);
  digitalWrite(GERADOR, 1);// ENTRADA STATUS GERADOR
  pinMode(led_rede, OUTPUT);
  pinMode(led_gerador, OUTPUT);
  pinMode(pino_buzzer, OUTPUT);
  pinMode(led_carga, OUTPUT);


}  // FIM  VOID SETUP

   
   
void loop()  { //INICIO LOOP VOID
   
 
 
  STREDE = digitalRead (REDE); // LE STATUS DA REDE E COLOCA EM STREDE
  STGER =  digitalRead (GERADOR); // LE STATUS DO GERADOR E COLOCAR EM STGER
   
if ( STREDE == 0 ) {  // REDE LIGADA

 digitalWrite(led_rede, HIGH);
 digitalWrite(led_carga, HIGH);
  lcd.setCursor(0,0); 
  lcd.print("  REDE CPFL ");  
  lcd.setCursor(0,1);  
  lcd.print("   LIGADA  ");
  redegeroff();
  redeon();
  geradoroff();
 
}
 
  else if  ( STREDE == 1) { // FALHA REDE LIGANDO GERADOR
 digitalWrite(led_rede, LOW);
 
  lcd.setCursor(0,0);
  lcd.print("   FALHA REDE CPFL ");  
  lcd.setCursor(0,1);  
  lcd.print("   GERADOR LIGADO ");
  redeoff();
  delay(1000); // era 1000
  
if (STGER == 1){
  geradoron();

}
  redegeron();
  return;
   
}

}  // FIM LOOP VOID
   

void redeon() {     //  LIGA REDE
     
  lcd.setCursor(0,0);
  lcd.print("    REDE CPFL ");
  lcd.setCursor(0,1);  
  lcd.print("    LIGADA  ");
  digitalWrite (CONTACGE, 0);
  digitalWrite (CONTACRD, 1);
  delay (7000);
  
}  
   
 
void redeoff(){     //  DESLIGA REDE
     
  lcd.setCursor(0,0); 
  lcd.print("   REDE CPFL ");
  lcd.setCursor(0,1);  
  lcd.print("   DESLIGADA  ");  
  digitalWrite (CONTACRD, 0);
  delay(3000); // era 2000
 digitalWrite(led_carga, LOW);
  return;  
}
   

   
void redegeron(){     // LIGA REDE GERADOR

  lcd.setCursor(0,0);
  lcd.print("   GERADOR   ");
  lcd.setCursor(0,1);  
  lcd.print("      LIGADO     ");
  digitalWrite(led_gerador ,HIGH);
  digitalWrite(led_carga, HIGH);
  digitalWrite(pino_buzzer, LOW);
  digitalWrite (CONTACRD, 0);
  delay(500); // era 1000
  digitalWrite (CONTACGE, 1);
  delay(4000); // era 1000

}

   
void redegeroff(){     //  DESLIGA REDE GERADOR
     
  lcd.setCursor(0,0);
  lcd.print(" ");  
  lcd.setCursor(0,1);  
  lcd.print("  ");
  digitalWrite (CONTACGE, 0);
  return;
}

void geradoron(){     // PARTIDA DO GERADOR
  PARTGER = digitalRead (GERADOR);
  STREDE = digitalRead (REDE); // NOVO COMANDO CONTROLE
  delay(100); // era 2000
if (PARTGER == 1 && STREDE == 1){

do{    
  lcd.setCursor(0,0);
  lcd.print(" Inicializando ");  
  lcd.setCursor(0,1);  
  lcd.print(" PARTIDA GERADOR ");
  digitalWrite (CONTACRD, 0);
  digitalWrite (CONTACGE, 0);
  delay(400); // era 1000
  digitalWrite (ING, 1);
  delay(150);
  digitalWrite (CHOKE, 1);
  delay(300); // era 1000
    digitalWrite (START, 1);
  delay(3000);
  digitalWrite (START, 0);
  delay(2500);
  digitalWrite (CHOKE, 0);
  delay(1000); // era 3000
  
  PARTGER = digitalRead (GERADOR);
  STREDE = digitalRead (REDE);
  delay(2000);
} while ( PARTGER == 1 && STREDE == 1);
}
  return;
}

void geradoroff(){     // DESLIGA GERADOR
     
  lcd.setCursor(0,0);
  lcd.print("    GERADOR ");  
  lcd.setCursor(0,1);  
  lcd.print("   DESLIGADO   ");
  digitalWrite( led_gerador , LOW);
  digitalWrite (ING, 0);
  digitalWrite (CHOKE, 0);
  delay (3000);
  
  return;
  
 
}
