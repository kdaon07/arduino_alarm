#include <core_build_options.h>
#include <swRTC.h>
#include <LiquidCrystal_I2C.h>     //LiquidCrystal 
LiquidCrystal_I2C lcd(0x27, 16, 2);

swRTC rtc;  //클래스 개체 선언
int sh=0, sm=0, ss=0;
int set1=0, set2=0,set3=0, set4=0, set5=0;
int buzzerPin = 10;
int h, m, s;

void setup() {
  lcd.begin();
  lcd.backlight();
  rtc.stopRTC();            //정지
  rtc.setTime(0, 0, 0);  //시, 분, 초
  rtc.startRTC();           //시작
  Serial.begin(9600);
  pinMode(4,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  
  h = rtc.getHours(), DEC;
  m = rtc.getMinutes(), DEC;
  s = rtc.getSeconds(), DEC;
  if(set1==1) {
    if(set2==0) {
      if(digitalRead(4) == 1) {
        sh=sh+1;
      }
      if(digitalRead(2) == 1) {
        sm=sm+5;
      }
      if(digitalRead(7) == 1) {
        ss=ss+5;
      }
      if(digitalRead(8) == 1) {
        set2 = 1; 
      }
      if(sh == 24)sh = 0;
      if(sm == 60)sm = 0;
      if(ss == 60)ss = 0;
    }
    if(set2==1)
    {
      if(h==sh && m==sm && s==ss)
      {
        set5=1;
      }
    }
    if(set5==1)
    {
      set4=1;
        tone(buzzerPin, 262);
        digitalWrite(13, HIGH);
        delay(500);
        noTone(buzzerPin);
        digitalWrite(13, LOW);
        if(digitalRead(8) == 1) {
          set3 = 0;
          set2 = 0;
          set4 = 0;
          set5 = 0;
          noTone(buzzerPin);
        }
    }
    if(set4==0) delay(500);
    Serial.println(set4);

    lcd.setCursor(0, 0);      
    lcd.print("Time:");
    if(rtc.getHours()<10)lcd.print("0");
    lcd.print(rtc.getHours(), DEC);
    lcd.print(":");
    if(rtc.getMinutes()<10)lcd.print("0");
    lcd.print(rtc.getMinutes(), DEC);
    lcd.print(":");
    if(rtc.getSeconds()<10)lcd.print("0");
    lcd.print(rtc.getSeconds(), DEC);
    lcd.setCursor(0, 1); //set시작
    if(set2==0) lcd.print("*");
    else lcd.print(" ");
    lcd.print("Set:");
    if(sh<10)lcd.print("0");
    lcd.print(sh);
    lcd.print(":");
    if(sm<10)lcd.print("0");
    lcd.print(sm);
    lcd.print(":");
    if(ss<10)lcd.print("0");
    lcd.print(ss);
    delay(500);
  }
  else {
    if(digitalRead(4) == 1) {
      sh=sh+1;
    }
    if(digitalRead(2) == 1) {
      sm=sm+5;
    }
    if(digitalRead(7) == 1) {
      ss=ss+5;
    }
    rtc.setTime(sh, sm, ss);
    if(digitalRead(8) == 1) {
      set1 = 1;
      sh = 0; 
      sm = 0;
      ss = 0;
    }
    if(sh == 24)sh = 0;
    if(sm == 60)sm = 0;
    if(ss == 60)ss = 0;
    Serial.println(sh);
    lcd.setCursor(0, 0);      
    lcd.print("Time:");
    if(rtc.getHours()<10)lcd.print("0");
    lcd.print(rtc.getHours(), DEC);
    lcd.print(":");
    if(rtc.getMinutes()<10)lcd.print("0");
    lcd.print(rtc.getMinutes(), DEC);
    lcd.print(":");
    if(rtc.getSeconds()<10)lcd.print("0");
    lcd.print(rtc.getSeconds(), DEC);
    delay(1000);
    lcd.clear();
  }
} 
