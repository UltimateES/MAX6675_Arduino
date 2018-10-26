#include <max6675.h>
#include <LiquidCrystal.h>
#include <Wire.h>

int thermoDO = 13;
int thermoCS = 12;
int thermoCLK = 11;

int relay1 = 6;
int relay2 = 6;

int switchg = A2;
int switchr = 9;

int led1 = 7;
int led2 = 8;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal lcd(19,0,1,2,3,4);

int x = 0;
int y = 0 ;
int z = 0 ;

double thermocouplee=0;
double thermocoupl=0;
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup() {
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(switchg,INPUT_PULLUP);
  pinMode(switchr,INPUT_PULLUP);
  lcd.begin(20, 4);
  lcd.createChar(0, degree);
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      WEL-COME      ");
  lcd.setCursor(0, 1);
  lcd.print("         TO         ");
  lcd.setCursor(0, 2);
  lcd.print("   SANDI MICRO 05   ");
  lcd.setCursor(0, 3);
  lcd.print("   ELEMANTRA ENT.     ");
  delay(2000);
}

int s = 59;
int m = 9;

void loop() {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   SANDI MICRO 05   ");
    lcd.setCursor(0, 2);
    lcd.print("    Drop Pads &   ");
    lcd.setCursor(0, 3);
    lcd.print("Press Green Button ");
    while(digitalRead(switchg) == HIGH);
    s = 60;
    m = 14;
    while((digitalRead(switchr) != LOW) && ((s>=0) && (m >=0))){
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(relay2,HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   SANDI MICRO 05   ");
    lcd.setCursor(0, 1);
    lcd.print(" RED BUTTON FOR STOP ");
    lcd.setCursor(0, 2);
    lcd.print("Time Left : ");
    s=s-1; 
    if(s==-1){ 
     s=59; 
     m=m-1; 
    } 
    lcd.print(m); 
    lcd.print(":"); 
    lcd.print(s);
    lcd.setCursor(0, 3);
    lcd.print("Heater Tmp:");
    thermocouplee = thermocouple.readCelsius();
    if(thermocouplee < 100.00){
      thermocoupl=thermocouplee;
    }else if(thermocouplee >= 100.00){
      thermocoupl=(thermocouplee-100)*4.6;
      thermocoupl=thermocoupl+100;
    }
    if(thermocoupl > 915){
      thermocoupl = 915;
    }
    lcd.print(thermocoupl);
    #if ARDUINO >= 100
      lcd.write((byte)0);
    #else
      lcd.print(0, BYTE);
    #endif
    lcd.print("C");
    delay(999);
    }
    digitalWrite(relay2,LOW);
}













  

 

