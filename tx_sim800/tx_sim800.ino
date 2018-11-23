#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! bool error;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

Sim800l Sim800l;  //to declare the library
LiquidCrystal_I2C lcd(16, 2);
bool error;

const byte s_alarm1 = 12;
const byte s_alarm2 = 11;
const byte s_alarm3 = 13;

byte dt1, dt2, dt3;
bool hold1, hold2, hold3, hold4;
int data_sensor;
char* sms_people;
char* sms;
char* n_rx = "082165062273";
char* number1 = "082233008686";
char* number2 = "";
char* number3 = "";
char* number4 = "";
String line2;

void setup() {
  // put your setup code here, to run once:
  pinMode(s_alarm1, INPUT_PULLUP);
  pinMode(s_alarm2, INPUT_PULLUP);
  pinMode(s_alarm3, INPUT_PULLUP);
  lcd.autoAddress();
  lcd.begin();
  Sim800l.begin();
  lcd.setCursor(0,0);
  lcd.print("wait sms init");
  delay(2000);
  delay(2000);
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  control();
  delay(250);
}

void read_sensor(){
  dt1 = digitalRead(s_alarm1);
  dt2 = digitalRead(s_alarm2);
  dt3 = digitalRead(s_alarm3);
  data_sensor = dt1 + dt2 + dt3;
}

void control(){
  read_sensor();
  switch(data_sensor){
    case 0:
      if(hold1 == 0){
          sms = "alarm3";
          line2 = String(data_sensor) + (" /") + sms;          
          sms_people = "Kondisi Banjir level 3, SANGAT BERBAHAYA";
          lcd.setCursor(0,0);
          lcd.print(line2);
          lcd.setCursor(0,1);
          lcd.print("send sms...");
          Sim800l.sendSms(n_rx,sms);
          Sim800l.sendSms(number1,sms_people);
          //Sim800l.sendSms(number2,sms_people);
          //Sim800l.sendSms(number3,sms_people);
          //Sim800l.sendSms(number4,sms_people);
      hold1 = 1; hold2 = 0; hold3 = 0; hold4 = 0;
      }
      lcd.setCursor(0,1);
      lcd.print("sms sukses.");
    break;
    case 1:
      if (hold2 == 0){
        sms = "alarm2";
        sms_people = "Kondisi Banjir level 2, AWAS...";
        line2 = String(data_sensor) + (" /") + sms;
        lcd.setCursor(0,0);
        lcd.print(line2);
        lcd.setCursor(0,1);
        lcd.print("send sms...");
        Sim800l.sendSms(n_rx,sms);
        Sim800l.sendSms(number1,sms_people);
        //Sim800l.sendSms(number2,sms_people);
        //Sim800l.sendSms(number3,sms_people);
        //Sim800l.sendSms(number4,sms_people);
        hold1 = 0; hold2 = 1; hold3 = 0; hold4 = 0;
      }
      lcd.setCursor(0,1);
      lcd.print("sms sukses.");
    break;
    case 2:
    if(hold3 == 0){
      sms = "alarm1";
      sms_people = "Kondisi Banjir level 1, WASPADA";
      line2 = String(data_sensor) + (" /") + sms; 
      lcd.setCursor(0,0);
      lcd.print(line2);  
      lcd.setCursor(0,1);
      lcd.print("send sms...");
      Sim800l.sendSms(n_rx,sms);
      Sim800l.sendSms(number1,sms_people);
      //Sim800l.sendSms(number2,sms_people);
      //Sim800l.sendSms(number3,sms_people);
      //Sim800l.sendSms(number4,sms_people);
      hold1 = 0; hold2 = 0; hold3 = 1; hold4 = 0;
      }
      lcd.setCursor(0,1);
      lcd.print("sms sukses.");
    break;
    case 3:
      if(hold4 == 0){
      sms = "alarm0";
      sms_people = "Kondisi AIR aman...";
      line2 = String(data_sensor) + (" /") + sms; 
      lcd.setCursor(0,0);
      lcd.print(line2);  
      lcd.setCursor(0,1);
      lcd.print("send sms...");
      Sim800l.sendSms(n_rx,sms);
      Sim800l.sendSms(number1,sms_people);
      //Sim800l.sendSms(number2,sms_people);
      //Sim800l.sendSms(number3,sms_people);
      //Sim800l.sendSms(number4,sms_people);
      hold1 = 0; hold2 = 0; hold3 = 0; hold4 = 1;
      }
      lcd.setCursor(0,1);
      lcd.print("sms sukses.");
    break;
  }
}
