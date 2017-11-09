/**************************************************************************************** 
 * Wakaka Studio 2017
 * Author: iLYuSha Dawa-mumu Wakaka Kocmocovich Kocmocki KocmocA
 * Project:: 0escape Medieval - Round Table
 * Tools: Unity 5/C# + Arduino/C++
 * Last Updated: 2017/11/2
 ****************************************************************************************/
#define LASER 0
#define ARTHUR 1
#define LANCELOT 2
#define ECTOR 3
#define GALAHAD 4
#define TRISTAN 5
#define NUMBER_CONTROL 6
/* Input */
const int control[NUMBER_CONTROL] = {2,3,4,5,6,7};
/* Output */
const int outputLaser = 8;
const int emLockRoundTable = 9;
const int remote = 10;
/* Retained Variable */
int valueControl[NUMBER_CONTROL];
unsigned long lateTime;
boolean active = false;
boolean start = false;
char msgUnity;
void setup() 
{
    Serial.begin(9600);
    for (int i = 0;i<NUMBER_CONTROL;i++)
    {
      pinMode(control[i],INPUT_PULLUP);
    }
    pinMode(outputLaser,OUTPUT);
    pinMode(emLockRoundTable,OUTPUT);
    pinMode(remote,OUTPUT);
    digitalWrite(outputLaser,HIGH);
    digitalWrite(emLockRoundTable,HIGH);
    digitalWrite(remote,HIGH);
    Serial.println("Round Table 2017/10/25 iLYuSha Wakaka KocmocA");
}
void loop() 
{
    /* 溝通檢查 */
    if((millis()-lateTime)>100)
    {
        Serial.println("Wakaka");
        lateTime = millis();
    }
    /* Input訊號 */
    for(int k = 0 ; k < NUMBER_CONTROL ; k++)
    {
      valueControl[k] = Digital2Value(valueControl[k], digitalRead(control[k]));
    }
    /* Unity訊號 */
     msgUnity = Serial.read();
    if(msgUnity == 'R')
        Reset();
    if(msgUnity == 'A')
        Active();
    if(msgUnity == 'S')
        Start();
    if(msgUnity == 'E')
        End();

    if(!start)
    {
        if(!active)
        {
            if(valueControl[LASER] >= 100)
            {
                digitalWrite(outputLaser,HIGH);
                Serial.println("Active");
            }
            else
                digitalWrite(outputLaser,LOW);
        }
        else
            digitalWrite(outputLaser,HIGH);
    }
    else
    {
        digitalWrite(outputLaser,LOW);
        
        if(valueControl[ARTHUR] >= 1 && valueControl[LANCELOT] >= 1)
          Serial.println("1");
        else if(valueControl[LANCELOT] >= 1 && valueControl[ECTOR] >= 1)
          Serial.println("2");
        else if(valueControl[ECTOR] >= 1 && valueControl[GALAHAD] >= 1)
          Serial.println("3");
        else if(valueControl[GALAHAD] >= 1 && valueControl[TRISTAN] >= 1)
          Serial.println("4");
        else if(valueControl[TRISTAN] >= 1 && valueControl[ARTHUR] >= 1)
          Serial.println("5");
        else if(valueControl[ARTHUR] >= 1 && valueControl[ECTOR] >= 1)
          Serial.println("6");
        else if(valueControl[ECTOR] >= 1 && valueControl[TRISTAN] >= 1)
          Serial.println("7");
        else if(valueControl[TRISTAN] >= 1 && valueControl[LANCELOT] >= 1)
          Serial.println("8");
        else if(valueControl[LANCELOT] >= 1 && valueControl[GALAHAD] >= 1)
          Serial.println("9");
        else if(valueControl[GALAHAD] >= 1 && valueControl[ARTHUR] >= 1)
          Serial.println("10");

        if (valueControl[ARTHUR] >= 1)
            Serial.println("ARTHUR");
        if (valueControl[LANCELOT] >= 1)
            Serial.println("LANCELOT");
        if (valueControl[ECTOR] >= 1)
            Serial.println("ECTOR");
        if (valueControl[GALAHAD] >= 1)
            Serial.println("GALAHAD");
        if (valueControl[TRISTAN] >= 1)
            Serial.println("TRISTAN");
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
    return value;
}
void Reset()
{
    active = false;
    start = false;
    digitalWrite(outputLaser,HIGH);
    digitalWrite(emLockRoundTable,HIGH);
    digitalWrite(remote,HIGH);
    Serial.println("ResetFeedback");
}
void Active()
{
    active =true;
    Serial.println("ActiveFeedback");
    Darkness();
}
void Start()
{
    start = true;    
    Serial.println("StartFeedback");
    Brightness();
}
void End()
{
    digitalWrite(emLockRoundTable,LOW);
    Serial.println("EndFeedback");
}
void Darkness()
{
    digitalWrite(remote,LOW);
}
void Brightness()
{
    digitalWrite(remote,HIGH);
}
