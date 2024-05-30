#include <WiFi.h>
#include <TridentTD_LineNotify.h>

#define WIFI_SSID "Whaen_12" // Central-Engineering // WE_H12_AP // 13GOD FATHER's iPhone // waaan //WAEN_H12 //Backup_Alarm_WAEN //WAEN_H12
#define WIFI_PASSWORD "57225140" // #DeltaFarm11 // #DeltaFarm11 // tz-oishi // 57225140 //#DeltaFarm11 //#DeltaFarm11 // #DeltaFarm11
#define LINE_TOKEN "mGdUNjj4S98huhXEdALAzJgF8AXpvlER78XJGHsoZhp"

const int input_1 = 16;
const int input_2 = 5;
const int output_1 = 19;
const int output_2 = 21;

unsigned long currenTime = 0;
int sec_on = 0, sec_off = 0;
int sec_on_temp = 0, sec_off_temp = 0;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  LINE.setToken(LINE_TOKEN);
  pinMode(input_1, INPUT);
  pinMode(input_2, INPUT);
  pinMode(output_1, OUTPUT);
  pinMode(output_2, OUTPUT);

}

void loop() {
  int
  time_send_line = 30,  //ความถี่ในการส่งไลน์
  time_standby = 300;   //ระยะเวลาก่อนจะมีการส่งไลน์พัดลมตัวยืนหยุดทำงาน
  //time_standby_temp =     //ระบะเวลาก่อนจะมีการส่งไลน์อุณหภูมิสูง

  if (millis() - currenTime >= 1000) {  //ทำให้ระบบทำงานทุก ๆ 1 วินาที
    currenTime = millis();

    if (digitalRead(input_1) == 0) {
      sec_on++, sec_off = 0;                                             //เมื่อสถานเป็น 0 sec_on จะเริ่มนับเวลาแล้วรีเซ็ต sec_off
      Serial.println("time_sec_on : " + String(sec_on) + " s");          //ดีบัคดูเวลา
      if (sec_on == 300) digitalWrite(output_1, 0), Serial.println("On");  //ระยะเวลาที่ให้พัดลมทำงาน
      if (sec_on >= time_standby) {                                      //ระยะเวลาก่อนจะส่งไลน์
        if (sec_on % time_send_line == 0) {                              //ความถี่ในการส่งไลน์
          //Serial.println("Succ Line on.");
          Serial.println("พัดลมตัวยืนหยุดทำงาน !!");
          LINE.notify("Alarm !\n พัดลมตัวยืนหยุดทำงาน !!");
        }
      }
    } else {
      sec_on = 0;                                                          //รีเซ็ต sec_on
      if (sec_off < time_send_line + 1) sec_off++;                         //แก้บัคส่งไลน์หลายรอบ
      Serial.println("time_sec_off : " + String(sec_off) + " s");          //ดีบัคดูเวลา
      if (sec_off == 1) digitalWrite(output_1, 1), Serial.println("Off");  //ระยะเวลาที่เราต้องการจะดับพัดลม
      if (sec_off % time_send_line == 0) {                                                  //ตวามถี่ในการส่งไลน์ เมื่อสถานะกลับมาเป็น 1 จะส่งไลน์แจ้งเดือนเพียงครั้งเดียว แล้วรอเริ่มต้นใหม่
        //Serial.println("Succ Line off.");
        Serial.println("พัดลมตัวยืนทำงานปกติ");
        LINE.notify("\n พัดลมตัวยืนทำงานปกติ");  
      }
    }


    static int sec_on_temp = 0; // ตัวนับเวลา
    static int sec_off_temp = 0; // ตัวนับเวลา

    if (digitalRead(input_2) == 0) {
      sec_on_temp++, sec_off_temp = 0;                                             //เมื่อสถานเป็น 0 sec_on จะเริ่มนับเวลาแล้วรีเซ็ต sec_off
      Serial.println("time_sec_on2 : " + String(sec_on_temp) + " s");          //ดีบัคดูเวลา

      if (sec_on_temp == 300) digitalWrite(output_2, 0), Serial.println("On");  //ระยะเวลาที่ให้พัดลมทำงาน
      
      if (sec_on_temp >= time_standby) {                                      //ระยะเวลาก่อนจะส่งไลน์
        if (sec_on_temp % time_send_line == 0) {  
          //Serial.println("Succ Line on.");
          Serial.println("อุณหภูมิสูงเกิน 40 องศา !!");
          LINE.notify("Alarm !\n อุณหภูมิสูงเกิน 40 องศา !!");
        }
      }

    } else {
      sec_on_temp = 0;                                                          //รีเซ็ต sec_on
      if (sec_off_temp < time_send_line + 1) sec_off_temp++;                     //แก้บัคส่งไลน์หลายรอบ

      Serial.println("time_sec_off2 : " + String(sec_off_temp) + " s");         //ดีบัคดูเวลา

      if (sec_off_temp == 1) digitalWrite(output_2, 1), Serial.println("Off");  //ระยะเวลาที่เราต้องการจะดับพัดลม
      
      if (sec_off_temp % time_send_line == 0) {                                   //ตวามถี่ในการส่งไลน์ เมื่อสถานะกลับมาเป็น 1 จะส่งไลน์แจ้งเดือนเพียงครั้งเดียว แล้วรอเริ่มต้นใหม่
        //Serial.println("Succ Line off.");
        Serial.println("อุณหภูมิปกติ");
        LINE.notify("\n อุณหภูมิปกติ ");
      }
      
    }
  }
  delay(10);
}