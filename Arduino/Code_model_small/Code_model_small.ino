//LED Green 48 46 44 42 40 38 36 34 32
//LED Red 49 47 45 43 41 39 37 35 33
//{49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32};
//{32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49};

// p4 49 48, p3 47 46

#include <ArduinoJson.h>

String txt = "{\"green\":511,\"red\":511}";
int pinLEDg[9] = {32,34,36,40,38,42,44,46,48};
int pinLEDr[9] = {33,35,37,41,39,43,45,47,49};
int pinSW[4] = {3,4,5,6};
int showGreen[9] = {0,0,0,0,0,0,0,0,0};
int showRed[9] = {0,0,0,0,0,0,0,0,0};
unsigned long currenT = 0;

void setup() {
  Serial.begin(115200);

  for(int i=0;i<sizeof(pinLEDg)/sizeof(int);i++){
    pinMode(pinLEDg[i],OUTPUT);
  }
  for(int i=0;i<sizeof(pinLEDr)/sizeof(int);i++){
    pinMode(pinLEDr[i],OUTPUT);
  }
  for(int i=0;i<sizeof(pinSW)/sizeof(int);i++){
    pinMode(pinSW[i],INPUT);
  }
}

void loop() {
  StaticJsonDocument<256> doc;
  deserializeJson(doc, txt);
  int green = doc["g"];
  int red = doc["r"];
  if(Serial.available()){
    txt = Serial.readString();

    /*int b1 = digitalRead(pinSW[0]);
    int b2 = digitalRead(pinSW[1]);
    int b3 = digitalRead(pinSW[2]);
    int b4 = digitalRead(pinSW[3]);

    Serial.println("{\"b1\":"+String(b1)+",\"b2\":"+String(b2)+",\"b3\":"+String(b3)+",\"b4\":"+String(b4)+"}");
    //Serial.print(txt);
    */
  }

  po(green,1),po(red,0);
  int r = 0, g = 0;
  for(int i=0;i<sizeof(pinLEDg)/sizeof(int);i++){
      digitalWrite(pinLEDg[i],showGreen[i]);
      digitalWrite(pinLEDr[i],showRed[i]);
      //Serial.print(String(showGreen[i])+",");
  }
  //Serial.println();
  if(millis()-currenT > 1000){
    currenT = millis();
    int b1 = digitalRead(pinSW[0]);
    int b2 = digitalRead(pinSW[1]);
    int b3 = digitalRead(pinSW[2]);
    int b4 = digitalRead(pinSW[3]);

   // Serial.println("{\"b1\":"+String(b1)+",\"b2\":"+String(b2)+",\"b3\":"+String(b3)+",\"b4\":"+String(b4)+",\"g\":"+String(green)+",\"r\":"+String(red)+"}");
    Serial.println("{\"b1\":"+String(b1)+",\"b2\":"+String(b2)+",\"b3\":"+String(b3)+",\"b4\":"+String(b4)+"}");
    //Serial.print(txt);
  }

  delay(10);
}

void po(int co,bool c){
  int bit_[9] = {256,128,64,32,16,8,4,2,1};
  for(int i=0;i<sizeof(bit_)/sizeof(int);i++){
    if(c){ // green
      if(co>=bit_[i]){
        showGreen[sizeof(showGreen)/sizeof(int)-(i+1)] = 1;
        co = co - bit_[i];
      }else{
        showGreen[sizeof(showGreen)/sizeof(int)-(i+1)] = 0;
      }
    }else{ // red
      if(co>=bit_[i]){
        showRed[sizeof(showRed)/sizeof(int)-(i+1)] = 1;
        co = co - bit_[i];
      }else{
        showRed[sizeof(showRed)/sizeof(int)-(i+1)] = 0;
      }
    }
  }
}
