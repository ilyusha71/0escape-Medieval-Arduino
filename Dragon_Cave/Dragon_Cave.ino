/******************************************
  Title: Dragon Cave
  Studio: iLYuSha Wakaka & 0escape
  Author: iLYuSha Wakaka KocmocA
  Date: 2017/10/31
*******************************************/
#define NUMBER_DRACO 10
#define NUMBER_PUNISH 3
unsigned long timer;
/* Input */
const int draco[NUMBER_DRACO] = {23,25,27,29,31,33,35,37,39,41};
const int dracoEgg = 43;
/* Output */
const int soundPass = 5;
const int soundEgg = 6;
const int soundStone[NUMBER_PUNISH] = {2,3,4};
const int emLockPunishment[NUMBER_PUNISH] = {45,47,49};
const int emLockPass = 51;
const int emLockLight = 53;
/* Retained Variable */
int durationMax = 1000;
int durationLimit = 10;
int valueDraco[3][NUMBER_DRACO] = {{},{},{0,0,1,1,0,0,1,0,1,0}};
int valueDracoEgg;
/* Variable */
boolean determination = false;
boolean firstblood = false;
boolean hitDragonwing = false;
boolean pass = false;
int dracoHP = 100;
int numHit = 0;
int numLastHit = 0;
int lastHit = -1;

void setup() 
{
    Serial.begin(9600);
    for (int i = 0;i<NUMBER_DRACO;i++)
    {
      pinMode(draco[i],INPUT_PULLUP);
    }
    pinMode(dracoEgg,INPUT_PULLUP);    
    for (int j = 0;j<NUMBER_PUNISH;j++)
    {
      pinMode(soundStone[j],OUTPUT);
      pinMode(emLockPunishment[j],OUTPUT);
      digitalWrite(soundStone[j], HIGH);
      digitalWrite(emLockPunishment[j], HIGH);
    }
    pinMode(soundPass,OUTPUT);
    pinMode(soundEgg,OUTPUT);
    pinMode(emLockPass,OUTPUT);
    pinMode(emLockLight,OUTPUT);
    digitalWrite(soundPass, HIGH);
    digitalWrite(soundEgg, HIGH);
    digitalWrite(emLockPass, HIGH);
    digitalWrite(emLockLight, LOW);
    Serial.println("Dragon Cave 2017/10/31");
    Serial.println("by iLYuSha Wakaka KocmocA");
}

void loop() 
{
    /* 破關 */
    if(dracoHP <= 0)
    {
        pass = true;
        digitalWrite(soundPass, LOW);      
        digitalWrite(emLockPass, LOW);
        digitalWrite(emLockLight, HIGH);
        return;
    }
    else
    {
        // 龍蛋觸發
        valueDracoEgg = Digital2Value(valueDracoEgg, digitalRead(dracoEgg));
        if(valueDracoEgg > 0)
        {
            digitalWrite(soundEgg, LOW);
            digitalWrite(emLockLight, HIGH);
            determination = true;
        }
        else
            digitalWrite(emLockLight, LOW);
        if(!determination)
            return;
            
        // 遊戲開始
        numHit = 0;
        for(int k = 0 ; k < NUMBER_DRACO ; k++)
        {
          valueDraco[1][k] = Attack(k, valueDraco[0][k], valueDraco[1][k] ,valueDraco[2][k]);
          valueDraco[0][k] = Digital2Value(valueDraco[0][k],digitalRead(draco[k]));
        }    
        if(numHit > numLastHit)
            Check();
        numLastHit = numHit;
    }
}

/*********************** 觸發機制判斷經驗規則 ************************
 *  1. 僅觸發一次使用 value > 0 判斷
 *  2. 單次觸發使用 value == durationLimit 判斷 (durationLimit > 1)
 *  3. 連續觸發使用 value >= durationLimit 判斷 (durationLimit > 1)
 *  4. 多組Arduino輸入(durationLimit > 30)
**********************************************************************/
int Digital2Value(int value, int digital)
{
    digital == 0 ? value++ : value = 0;
    if(value > durationMax)
        value = durationLimit; 
    return value;
}

int Attack(int numberDraco, int valueDraco, int lastDraco, int fatal)
{
    if(valueDraco > 0)
    {
//        Serial.print(numberDraco);
//        Serial.print(" is HIT, value is ");
//        Serial.println(valueDraco);
        if(valueDraco >= durationLimit)
            numHit++;
        if(valueDraco == durationLimit && lastDraco == durationLimit-1)
        {
            if(lastHit != numberDraco)
            {
                  if(fatal)
                  {
                      Serial.print("Fatal HIT ");
                      Serial.println(numberDraco);
                      dracoHP = DracoHP(dracoHP,2);
                  }
                  else
                  {
                      Serial.print("HIT ");
                      Serial.println(numberDraco);
                      dracoHP = DracoHP(dracoHP,1);
                  }
            }
            lastHit = numberDraco;
        }
    }
    return valueDraco;
}

void Check()
{ 
    if(numHit == 4 && 
      valueDraco[0][2] >= durationLimit && 
      valueDraco[0][3] >= durationLimit && 
      valueDraco[0][6] >= durationLimit && 
      valueDraco[0][8] >= durationLimit)
        dracoHP = DracoHP(dracoHP,1000);
    else if(!pass)
    {
        // 首次插劍沒刺在龍腹8時觸發
        if (!firstblood && numHit == 1)
        {
            firstblood = true;
            if (valueDraco[0][6] >= durationLimit)
            {
                Serial.println("Hit Death Point");
                dracoHP = DracoHP(dracoHP,50);
            }
            else
            {
                Serial.println("Hit Fail");
                digitalWrite(soundStone[0], LOW);
                digitalWrite(emLockPunishment[0], LOW);
            }
        }
        // 刺中龍翼觸發
        else if (!hitDragonwing && valueDraco[0][0] > durationLimit)
        {
            Serial.println("Attack Wing");
            hitDragonwing = true;
            digitalWrite(soundStone[1], LOW);
            digitalWrite(emLockPunishment[1], LOW);
        }
        // 屠龍劍皆插上沒有破關時觸發
        else if (numHit == 4 && !pass)
        {
            digitalWrite(soundStone[2], LOW);
            digitalWrite(emLockPunishment[2], LOW);
        }
    }
}

int DracoHP(int hp, int dmg)
{
      hp -= dmg;
      if(hp < 0)
          hp = 0;
      Serial.print("Dragon HP: ");
      Serial.println(hp);
      return hp;
}
