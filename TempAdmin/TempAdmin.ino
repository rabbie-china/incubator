//#include <SHT1x.h>
#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>
#include "U8glib.h"
#include "TempAdmin.h"
#include "DFRobot_SHT20.h"

//SHT1x sht1x(dataPin, clockPin);
DFRobot_SHT20    sht20;

void inQueue(QUEUE * pQueue,int value)
{
  pQueue->pBase[pQueue->point]=value;
  pQueue->point=++pQueue->point%6;
  //Serial.println(pQueue->point);
}

int traverseQueue(QUEUE * pQueue)
{
  int n=pQueue->point;
  int a=0,b=0,nCount=0;
  do{
    if(nCount<3){
      a+=pQueue->pBase[n];
    }
    else{
      b+=pQueue->pBase[n];
    }
    n=++n%6;
    nCount++;
  }while(n!=pQueue->point);
  return (b-a);
}

void TrunEggs(void)
{
  int nAngle=myservo1.read();
  //Serial.println(nAngle);
  //Serial.println(nDestAngle);
  if(abs(nAngle-nDestAngle)<6){
    nAngle=nDestAngle;
    myservo1.write(nAngle);
    return;
  }
  if(nDestAngle>nAngle){
    nAngle+=6;
    myservo1.write(nAngle);
    return;
  }
  else if(nDestAngle<nAngle){
    nAngle-=6;
    myservo1.write(nAngle);
    return;
  }
}

void drawSetting(void) {
  char chShowStr[100],chTemp[100];
  float fPre;
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setColorIndex(1);         // pixel on
  u8g.setFont(u8g_font_unifont);
  
  dtostrf(fSetTemp,4,2,chTemp);
  sprintf(chShowStr,"TEMP: %s C",chTemp);
  u8g.drawStr( 0, 12, chShowStr);

  u8g.drawBox( 0, 15, 128,16);
  u8g.setColorIndex(0);         // pixel on
  dtostrf(fSetTempOff,4,2,chTemp);
  sprintf(chShowStr,"TEMP OFF: %s C",chTemp);
  u8g.drawStr( 0, 28, chShowStr);

  u8g.setColorIndex(1);         // pixel on
  dtostrf(fSetHumi,4,2,chTemp);
  sprintf(chShowStr,"HUMI: %s %%",chTemp);
  u8g.drawStr( 0, 44, chShowStr);

  dtostrf(fSetHumiOff,4,2,chTemp);
  sprintf(chShowStr,"HUMI OFF: %s C",chTemp);
  u8g.drawStr( 0, 60, chShowStr);
  /*if(n_Status){
    dtostrf(fSetTemp,4,2,chTemp);
    sprintf(chShowStr,"TEMP: %s C",chTemp);
    u8g.drawStr( 0, 12, chShowStr);

    dtostrf(fSetTempOff,4,2,chTemp);
    sprintf(chShowStr,"TEMP OFF: %s C",chTemp);
    u8g.drawStr( 0, 28, chShowStr);

    dtostrf(fSetHumi,4,2,chTemp);
    sprintf(chShowStr,"HUMI: %s %%",chTemp);
    u8g.drawStr( 0, 44, chShowStr);

    dtostrf(fSetHumiOff,4,2,chTemp);
    sprintf(chShowStr,"HUMI OFF: %s C",chTemp);
    u8g.drawStr( 0, 60, chShowStr);
  }
  else{
    switch(n_SettingItem)
    {
      case 0:
        u8g.drawStr( 0, 12, "TEMP:");
        break;
      case 1:
        u8g.drawStr( 0, 28, "TEMP OFF:");
        break;
      case 2:
        u8g.drawStr( 0, 44, "HUMI:");
        break;
      case 3:
        u8g.drawStr( 0, 60, "HUMI OFF:");
        break;
    }
    dtostrf(fSetTempOff,4,2,chTemp);
    sprintf(chShowStr,"TEMP OFF: %s C",chTemp);
    u8g.drawStr( 0, 28, chShowStr);

    dtostrf(fSetHumi,4,2,chTemp);
    sprintf(chShowStr,"HUMI: %s %%",chTemp);
    u8g.drawStr( 0, 44, chShowStr);

    dtostrf(fSetHumiOff,4,2,chTemp);
    sprintf(chShowStr,"HUMI OFF: %s C",chTemp);
    u8g.drawStr( 0, 60, chShowStr);
  }*/
  //Serial.println(n_Status);
}

void draw(void) 
{
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);

  char chShowStr[100],chTemp[100];
  float fPre;
  dtostrf(fTemp_c,4,2,chTemp);
  sprintf(chShowStr,"TEMP: %s C",chTemp);
  u8g.drawStr( 0, 12, chShowStr);

  dtostrf(fHumidity,4,2,chTemp);
  sprintf(chShowStr,"HUMI: %s %%",chTemp);
  u8g.drawStr( 0, 28, chShowStr);

  u8g.drawLine(0,32, 108,32);
  if(digitalRead(nLineHeat)==HIGH)
    u8g.drawStr( 0, 48, "HEATING");
   else
    u8g.drawStr( 0, 48, " ");
  sprintf(chShowStr,"%ldDAY %02ld:%02ld:%02ld",nowtime/86400,(nowtime/3600)%24,(nowtime/60)%60,nowtime%60);
  //sprintf(chShowStr,"%02ld %02ld",nowtime,nowtime%60);
  u8g.drawStr( 0, 64, chShowStr);
}

void Process_Temp_Humi(void)
{
  inQueue(&queueTemp,fTemp_c*100);
  value=traverseQueue(&queueTemp);
  if(abs(value)<3){
    //温度没有变化
    if((fSetTemp-fTemp_c)>0.3){
      digitalWrite(nLineHeat,HIGH);
    }
    else{
      digitalWrite(nLineHeat,LOW);
    }
  }
  else if(value>0){
    //升温过程
    if(fTemp_c<fSetTemp-fSetTempOff){
      digitalWrite(nLineHeat,HIGH);
    }
    else{
      digitalWrite(nLineHeat,LOW);
    }
  }
  else{
    //降温过程
    if(fTemp_c<fSetTemp+fSetTempOff){
      digitalWrite(nLineHeat,HIGH);
    }
    else{
      digitalWrite(nLineHeat,LOW);
    }
  }
  
  inQueue(&queueHumi,fHumidity*100);
  value=traverseQueue(&queueHumi);
  
  if(g_un_count%20==0){
    if(abs(value)<15){
      //湿度没有变化
      if((fSetHumi-fHumidity)>5){
        digitalWrite(nLineHumid,HIGH);
        //Serial.println("code run here!");
        delaytime=currentMillis+20000;
        //digitalWrite(nLineHumid,LOW);
      }
    }
    else if(value>0){
      //加湿过程
      if(fHumidity<fSetHumi-fSetHumiOff){
        digitalWrite(nLineHumid,HIGH);
        delaytime=currentMillis+20000;
      }
    }
    else{
      //干燥过程
      if(fHumidity<fSetHumi+fSetHumiOff){
        digitalWrite(nLineHumid,HIGH);
        delaytime=currentMillis+20000;
      }
    }
  }
  g_un_count++;
}

void setup (void)
{
  Serial.begin(9600);  

  pinMode(nLineHeat, OUTPUT);
  pinMode(nLineHumid, OUTPUT);
  pinMode(nTurnEgg, OUTPUT);
  pinMode(nLineCO2, OUTPUT);
  pinMode(nSwitch1, INPUT);
  pinMode(nSwitch2, INPUT);
  pinMode(nSwitch3, INPUT);
  
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  queueTemp.point=0;
  queueHumi.point=0;
  previousMillis=0;
  previousMillis2=0;
  delay2hours=0;
  nowtime=0;
  
  fSetTemp=37.5;
  fSetHumi=60;
  fSetTempOff=0.3;
  fSetHumiOff=6;
  n_IsSetting=0;
  myservo1.attach(nTurnEgg);
  nAngleDirect=0;
  nDestAngle=20;
  sht20.initSHT20();                                 
  delay(100);
  sht20.checkSHT20();                                 
}

void loop (void) {
  //read temp and himidity loop
  currentMillis=millis(); //获取当前的系统运行时间长度
  
  if(currentMillis>=previousMillis+DELAY500){
    previousMillis=currentMillis;
    //fTemp_c = sht1x.readTemperatureC();    //读取当前温度
    //fHumidity = sht1x.readHumidity();      //读取湿度
    fTemp_c = sht20.readTemperature();    //读取当前温度
    fHumidity = sht20.readHumidity();      //读取当前湿度
    Serial.println(fTemp_c);
    Serial.println(fHumidity);
    if(fTemp_c>0&&fTemp_c<40){
      //TrunEggs();
      Process_Temp_Humi();
    }
    else{
      digitalWrite(nLineHeat,LOW);
      digitalWrite(nLineHumid,HIGH);
    }
  
    // picture loop
    u8g.firstPage();  
    do {
      if(n_IsSetting)
        drawSetting();
      else
        draw();
    } while( u8g.nextPage() );
  }
  if(currentMillis-previousMillis2>=ONE_SECOND){
    previousMillis2=currentMillis;
    nowtime++;
    if(nowtime-delay1day>=259200){
      delay1day=nowtime;
      fSetTemp-=0.5;
    }
    if(nowtime-delay20second>=120){
      if(digitalRead(nLineCO2)==HIGH){
        digitalWrite(nLineCO2,LOW);
      }
    }
    if(nowtime-delay2hours>=3600){
      delay2hours=nowtime;
      delay20second=nowtime;
      digitalWrite(nLineCO2,HIGH);
      if(nAngleDirect){
        nDestAngle+=35;
        if(nDestAngle>=160){
          nDestAngle=160;
          nAngleDirect=!nAngleDirect;
        }
      }
      else{
        nDestAngle-=35;
        if(nDestAngle<=20){
          nDestAngle=20;
          nAngleDirect=!nAngleDirect;
        }
      }
    }
  }
  //delay fuction
    //Serial.println(delaytime-currentMillis);
  if(delaytime<=currentMillis){
    if(digitalRead(nLineHumid)==HIGH){
      digitalWrite(nLineHumid,LOW);
    }
  }
  n_IsSetting=0;
  n_SettingItem=1;
      //digitalWrite(nLineHumid,HIGH);
  /*if(digitalRead(nSwitch1)==HIGH){
    n_IsSetting=1;
    settingdelay=currentMillis+10000;
    n_SettingItem=++n_SettingItem&4;
  }
  if(settingdelay-currentMillis<=0){
    n_IsSetting=0;
  }*/
}
