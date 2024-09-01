#include <LiquidCrystal_I2C.h>      //Library LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2);   //Alamat I2C

#include <DS3231.h>       //library DS3231
DS3231  rtc(SDA, SCL);    //inisialisasi penggunaan i2c
Time t;                   //Variabel t tampat menyimpan waktu
int set_jam = 15;         //Set alarm jam
int set_menit = 00;       //Set alarm menit

#include <Servo.h>  //Library servo
Servo myservo;      //Deklarasi nama servo

void setup(){
  lcd.init ();            //Mulai LCD
  lcd.setBacklight(HIGH);
  
  myservo.attach(9);      //Pin servo D9
  myservo.write(0);       //Posisi awal servo
  rtc.begin();            //Mulai RTC
  //setting pertama download program
  rtc.setDate(30, 9, 2020);     //mensetting tanggal 
  rtc.setTime(14, 59, 50);      //menset jam 
  rtc.setDOW(3);                //menset hari "Rabu"

  //setelah didownload awal selesai, download kedua dengan memberi tanda komen "//"
  
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print(rtc.getDateStr());  //prosedur pembacaan tanggal
  
  lcd.setCursor(0,1);
  lcd.print(rtc.getTimeStr());  //prosedur pembacaan waktu
  
  t = rtc.getTime();            //Baca waktu
  int jam = t.hour;
  int menit = t.min;
  int detik = t.sec;
  
  if(set_jam == jam){               //Jika jam sama dengan alarm, maka
    if(set_menit == menit){         //Jika menit sama dengan alarm, maka
      if(detik < 5){                //Jika detik < 5, maka
        myservo.write(90);          //Buka servo
      }
      else{
        myservo.write(0);
      }
    }
  }
  
  delay (1000); //waktu tunda 1 detik per cycle
}
