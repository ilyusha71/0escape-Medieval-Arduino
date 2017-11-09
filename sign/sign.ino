/******************************************
  Title: Star Timer
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2017/02/23
*******************************************/
/* 
 * game thoughout timer 
 *      in Middle Ages
 * 
 * feature
 * 1. counting whole game time
 *  Change sign every unit time  
 * 
 * 2. sent a signal when time out 
 *    -LOW active
 *    
 * 3. when device been placed, add time once.
 *  total 3 devices
 *  
 *Pin Configuration  
 *  pin 2  start counting down
 *  pin 3  output low while time up
 *  pin 4-7  control 15 LED (connect to a 4-to-16 decoder) ; LSB 4  MSB 7 
 *  pin 8-10 increase time active
 * 
 * Nov. 26 2015
 * by 31
 */
 
/*Variable*/
#define gameTime 60    // total game time (mins)  (remain 4 mins for demo that time increaseing device)
#define interval 1000  //1000ms = 1 sec
#define TimeAdding 4   // increase time (mins)

#define maxStar 15  // 15 LED
#define unitTime 4   //(mins)  change interval  (gameTime / maxStage)


/*pin configure*/
#define startPin   2
#define timeupPin  3
#define pinOffset  4 //4-7 is LED control pin
#define testPinA   8
#define testPinB   9
#define testPinC   10
#define addTimeA   11
#define addTimeB   12
#define addTimeC   13

// 七段顯示器腳位
#define PIN_f 23
#define PIN_a 25
#define PIN_3 27
#define PIN_e 29
#define PIN_d 31
#define PIN_h 33
#define PIN_c 35
#define PIN_g 37
#define PIN_0 39
#define PIN_b 41
#define PIN_1 43
#define PIN_2 45

// 共有4個七段顯示器，分別由針腳PIN_0、PIN_1、PIN_2、PIN_3控制
// 七段顯示器裡有8個LED（包含小數點）
#define POS_NUM 4
#define SEG_NUM 8
const byte pos_pins[POS_NUM] = {PIN_0, PIN_1, PIN_2, PIN_3};
const byte seg_pins[SEG_NUM] = {PIN_a, PIN_b, PIN_c, PIN_d, PIN_e, PIN_f, PIN_g, PIN_h};

// 底下定義由七段顯示器顯示數字時所需要的資料
#define t true
#define f false
const boolean data[10][SEG_NUM] = 
{
  {t, t, t, t, t, t, f, f}, // 0
  {f, t, t, f, f, f, f, f}, // 1
  {t, t, f, t, t, f, t, f}, // 2
  {t, t, t, t, f, f, t, f}, // 3
  {f, t, t, f, f, t, t, f}, // 4
  {t, f, t, t, f, t, t, f}, // 5
  {t, f, t, t, t, t, t, f}, // 6
  {t, t, t, f, f, f, f, f}, // 7
  {t, t, t, t, t, t, t, f}, // 8
  {t, t, t, t, f, t, t, f}, // 9
};

// 閃爍模式
enum ShiningMode
{
  Blink, // 自然閃爍
  Warning, // 隕落前提示
  Marquee, // 跑馬燈
} shiningMode;

// 遊戲階段
enum GameMode
{
  Ready, // 遊戲準備中
  Start, // 遊戲進行中
  Finish, // 遊戲結束
} gameMode = GameMode::Ready;

boolean start = 0;    //set 1 to start counting
boolean finish = 0;
boolean addTflag[3]={0}; // 加時判斷

unsigned long currentMillis; // Arduino計時器
unsigned long previousMillis = 0;
unsigned long starUpdate; // 星辰刷新時間
unsigned long displayUpdate; // 七段顯示器刷新時間
int blinkFrequency = 73; // 星辰閃爍頻率
const float displayFrequency = 3.971; // 七段顯示器刷新頻率

int numStar; // 當前星辰數
int mins; // 當前剩餘時間（分）
int secs; // 當前剩餘時間（秒）

long randNumber; // 當前閃爍星
int times = 0; // 七段顯示器位數刷新

void setup() 
{
    int i;
    Serial.begin(9600);

    pinMode(testPinA,INPUT_PULLUP);
    
    pinMode(addTimeA,INPUT_PULLUP);
    pinMode(addTimeB,INPUT_PULLUP);
    pinMode(addTimeC,INPUT_PULLUP);
    pinMode(startPin,INPUT_PULLUP);

    for(i=0;i<4;i++)
    {
        pinMode(i+pinOffset,OUTPUT);
        digitalWrite(i+pinOffset,HIGH);
    }
    
    pinMode(timeupPin,OUTPUT);
    digitalWrite(timeupPin,HIGH);

    for(i=0;i<3;i++)
    {
        addTflag[i]=0;
    }
    
    for(int i = 0; i < POS_NUM; i++)
    {
        pinMode(pos_pins[i], OUTPUT);
        digitalWrite(pos_pins[i], HIGH);
    }
    for(int i = 0; i < SEG_NUM; i++)
    {
        pinMode(seg_pins[i], OUTPUT);
        digitalWrite(seg_pins[i], LOW);
    }

    mins = gameTime;
    secs = 0;
}

//int r;
//int k;

void loop() 
{
//  r = Serial.read();
//  if(r==43)
//    mins++;
//  else if(r==45)
//    mins--;
//  else if(r==42)
//    secs-=10;
//      else if(r==47)
//    mins = 35;
//
//  if(r!=-1)
//    k = r-48;
  
  int i;



    /*waiting to start*/    
    if(!digitalRead(startPin) && gameMode == GameMode::Ready)
    {
        gameMode = GameMode::Start;
        Serial.println("timer start");
    }

if(!digitalRead(testPinA))
{
  mins = 0;
  secs = 25;
  }

  currentMillis = millis();
  
    if(gameMode == GameMode::Finish)
    {
        digitalWrite(timeupPin,LOW);
    }
    else
    {
        for(i=0;i<3;i++)
        {
            if(!digitalRead(addTimeA+i))
            {
                if(addTflag[i]==0)
                {
                    addTflag[i]=1;
                    mins=mins+TimeAdding;
                }
            }
            else
            {
                if(addTflag[i]==1)
                {
                    addTflag[i]=0;
                    mins=mins-TimeAdding;
                }  
            }
        }
    }
    
    if(gameMode == GameMode::Start)
    {        
        if(currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis; 
    
            if(secs <= 0)
            {
              secs = 60;
              mins--;        
            }
            secs--;
  
            /*sent time up signal*/
            if(mins<0)
            {
              gameMode = GameMode::Finish;
              mins = secs = 0;
            }
                
            Serial.print(numStar);
            Serial.print(":/");
            Serial.print(mins);
            
            Serial.print(":");
            Serial.println(secs);
            Serial.println(digitalRead(timeupPin));
        }
    }
    
    sign();   // change sign by scan
}

void sign(void)
{
    if(currentMillis > displayUpdate)
    {
        displayUpdate = currentMillis + displayFrequency;

        if(times%4==0)
            setDigit(0, secs%10);
        else if(times%4==1)
            setDigit(1, secs/10);
        else if(times%4==2)
            setDigit(2, mins%10);
        else if(times%4==3)
            setDigit(3, mins/10);
        
        times++;
        if(times == 1000)
            times = 0;    
    }

    if((mins+unitTime)%4 == 0 && secs >0 && secs <=15)
        shiningMode = ShiningMode::Warning;
    else if(numStar>3 && secs > 50)
        shiningMode = ShiningMode::Marquee;
    else
        shiningMode = ShiningMode::Blink;
        
    numStar = (mins+unitTime)/unitTime;
    if(mins == 0 && secs == 0)
        numStar = 0;
    if(numStar==0)
    {    
        //no star shining
        digitalWrite(pinOffset,HIGH);
        digitalWrite(pinOffset+1,HIGH);
        digitalWrite(pinOffset+2,HIGH);
        digitalWrite(pinOffset+3,HIGH);
    }
    else
    {
        if(currentMillis > starUpdate)
        {
            starUpdate = currentMillis + blinkFrequency;
            if(shiningMode == ShiningMode::Blink)
            {
                blinkFrequency = 97;
                randNumber = random(maxStar);
            }
            else if (shiningMode == ShiningMode::Marquee)
            {
              blinkFrequency = 197;
              randNumber++;
              if(randNumber >= numStar)
                randNumber = 1;
            }
            else if (shiningMode == ShiningMode::Warning)
            {
                if(secs < 5)
                  blinkFrequency = 137;
                else
                  blinkFrequency = 237;
                  
                if(randNumber != numStar-1)
                  randNumber = numStar-1;
                else if(randNumber == numStar-1)
                  randNumber = numStar;
            }
        }
        
//        if(r!=-1)
//            randNumber = k;

        if(numStar == 1)
        {
            digitalWrite(pinOffset,LOW);
            digitalWrite(pinOffset+1,LOW);
            digitalWrite(pinOffset+2,LOW);
            digitalWrite(pinOffset+3,LOW);
        }
        else
        {
            for(int i=0;i<numStar;i++)
            {
                if(randNumber == 0)
                  randNumber = maxStar;
                if(i != randNumber)
                {
                    digitalWrite(pinOffset,i&0x01);
                    digitalWrite(pinOffset+1,i&0x02);
                    digitalWrite(pinOffset+2,i&0x04);
                    digitalWrite(pinOffset+3,i&0x08);
                }
            }
        }
    }
}

void setDigit(int pos, int n){

  if(pos < 0 || 3 < pos){
    //pf("error pos=%d\n", pos);
    return;
  }

  // 控制想要更新哪一個七段顯示器，將其腳位設為LOW
  // 其他腳位則設為HIGH，代表不更新。 
  for(int p = 0; p < POS_NUM; p++){
    if(p == pos)
      digitalWrite(pos_pins[p], LOW);
    else
      digitalWrite(pos_pins[p], HIGH);
  }
  
  // 寫入數字 
  if(0 <= n && n <= 9){
    for(int i = 0; i < SEG_NUM; i++){
      digitalWrite(seg_pins[i], data[n][i] == t ? HIGH : LOW);
      if(pos == 2)
        digitalWrite(seg_pins[7],HIGH);
    }
  }
  else{
    for(int i = 0; i < SEG_NUM; i++){
      digitalWrite(seg_pins[i], LOW);
    }
    digitalWrite(PIN_h, HIGH);
    //pf("error pos=%d, n=%d\n", pos, n);
  }
}


