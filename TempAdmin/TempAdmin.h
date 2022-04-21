#ifndef _CPP_TEMPADMIN
#define _CPP_TEMPADMIN
typedef unsigned char      uChar8;      
typedef unsigned int       uInt16;
typedef unsigned long int  uInt32;

//3，5，6，9，10，11对应Pcduino V2单板的PWM引脚
//#define dataPin 10      //温度传感器data
//#define clockPin 11	//温度传感器clock
#define nLineHeat 9	//加热引脚
#define nLineHumid 6	//加湿引脚
#define nLineCO2 12	//换气引脚
#define nLineBeep 3	//报警接线
#define nTurnEgg 5      //翻蛋接口
#define nSwitch1 4	//switch1
#define nSwitch2 7	//switch2
#define nSwitch3 8	//switch3
#define nTempConst 300  //常量温度，计算问题的时候要加上这个常量除以10
#define DELAY500 500
#define ONE_SECOND 1000

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 
static float fTemp_c;
static float fHumidity;
int value;
uInt32 g_un_count=0;
static unsigned long currentMillis;
static unsigned long previousMillis;
static unsigned long nowtime;
static unsigned long previousMillis2;
static unsigned long delaytime;
static unsigned long settingdelay;
static unsigned long delay2hours;
static unsigned long delay20second;
static unsigned long delay1day=0;

static float fSetTemp;
static float fSetHumi;
static float fSetTempOff;
static float fSetHumiOff;
static int n_IsSetting;
static int n_SettingItem;
static int nAngleDirect;    //舵机旋转方向
static int nDestAngle;      //舵机目标角度

Servo myservo1;

/* 
 *循环队列，用数组实现 
 */  
//队列结构体定义  
typedef struct Queue  
{  
    int pBase[6];    //用于动态分配内存,pBase保存数组的首地址  
    int point;       //指向最后一个元素的下一结点  
} QUEUE;  
QUEUE queueTemp;
QUEUE queueHumi;

#endif
