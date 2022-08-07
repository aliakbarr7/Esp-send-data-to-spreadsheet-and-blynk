// Monitoring Data Logger


// Menambahkan Library
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "TRIGGER_WIFI.h"
#include "TRIGGER_GOOGLESHEETS.h"


/**********Google Sheets Definations***********/
char column_name_in_sheets[ ][20] = {"value1","value2","value3"};                        /*1. The Total no of column depends on how many value you have created in Script of Sheets;2. It has to be in order as per the rows decided in google sheets*/
String Sheets_GAS_ID = "AKfycbxC_mISLKz62_QR8fw53RdAUvSjOMpuao_dRKZHp1NEO95HN1fD";                                         /*This is the Sheets GAS ID, you need to look for your sheets id*/
int No_of_Parameters = 3;                                                                /*Here No_of_Parameters decides how many parameters you want to send it to Google Sheets at once, change it according to your needs*/
/*********************************************/


// Masukan Token Yang di Kirim dari Blynk Melalui Email
char auth[] = "FmtHFGO58_YC_vSzT6AJIqplhMpd5LOH";

//Masukkan Nama dan Kata Sandi Wifi
char ssid[] = "Teras Karya";
char pass[] = "1122334455";

// Menginisialisasikan BlynkTimer. Timer ini digunakan sebagai interval waktu untuk pengiriman data ke server Blynk
BlynkTimer timer; 

int v;
int a;
int arahAngin;

WidgetLCD lcd(V2);
WidgetLED PLTB(V3);
WidgetLED PLN(V4);

void setup(){
  Serial.begin(9600);
  while (!Serial);
  Blynk.begin(auth, ssid, pass, "axial-labs.tech", 8081);
  WIFI_Connect(ssid, pass);
  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );
  lcd.clear();
}

void loop (){
  Blynk.run();

  float v,a,arahAngin;
  
  v = random(0,50);
  a = random(0,50);
  arahAngin = random(0,360);

  int v1,a1,arahAngin1;

  v1=v;
  a1=a;
  arahAngin1=arahAngin;
 
  Blynk.virtualWrite(V0, v1);
  Blynk.virtualWrite(V1, a1);
  Blynk.virtualWrite(V2, arahAngin1);
  lcd.print(0,0, "Arah Angin :");
  lcd.print(12,0,arahAngin1);
  lcd.print(15,0, "°");


  if (arahAngin1 >= 0 && arahAngin1 <= 21){
    lcd.print(0,1, "Utara");
  }

  else if (arahAngin1 >= 22 && arahAngin1 <= 30){
    lcd.print(0,1, "Utara Timur Laut");
  }

  else if (arahAngin1 >= 31 && arahAngin1 <= 45){
    lcd.print(0,1, "Timur Laut");
  }

   else if (arahAngin1 >= 46 && arahAngin1 <= 80){
    lcd.print(0,1, "Timur Timur Laut");
  }

  else if (arahAngin1 == 90){
    lcd.print(0,1, "Timur");
  }

   else if (arahAngin1 >= 122 && arahAngin1 <= 130){
    lcd.print(0,1, "Timur Tenggara");
  }

  else if (arahAngin1 == 135){
    lcd.print(0,1, "Tenggara");
  }

  else if (arahAngin1 >= 157 && arahAngin1 <= 179){
    lcd.print(0,1, "Selatan Tenggara");
  }

  else if (arahAngin1 == 180){
    lcd.print(0,1, "Selatan");
  }

   

  if (v1 > 24){
    PLTB.on();
    PLN.off();
  }
  else if (v1 < 24){
    PLTB.off();
    PLN.on();
  }

  

  Data_to_Sheets(No_of_Parameters,  v,  a, arahAngin);

  Serial.println();
  delay(1000);
  
}
