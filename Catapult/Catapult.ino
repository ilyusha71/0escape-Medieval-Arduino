/**************************************************************************************** 
 * Wakaka Studio 2017
 * Author: iLYuSha Dawa-mumu Wakaka Kocmocovich Kocmocki KocmocA
 * Project: 0escape Medieval - Catapult
 * Tools: Unity 5.6 + Arduino Mega2560
 * Last Updated: 2017/11/07
 ****************************************************************************************/
#define LOADING 0
#define RUNE_ODAL 1
#define RUNE_JERAN 2
#define RUNE_EHWAZ 3
#define LEFT_LOW 4
#define LEFT_HIGH 5
#define RIGHT_LOW 6
#define RIGHT_HIGH 7
#define NODE_12 8
#define NODE_4 9
#define NODE_8 10
#define SCENE 11
#define NUMBER_CONTROL 12
/* Input */
const int control[NUMBER_CONTROL] = {27,29,31,33,35,37,39,41,43,45,47,52};
int msgUnity;
/* Output */
const int emLockScene = 53;
const int emLockTunnelEntrance = 51;
String commandUnity;
/* Retained Variable */
int valueControl[NUMBER_CONTROL];
int durationMax = 1000;
int durationLimit = 10;
/* Variable */
int lastNode;

void setup() 
{
    Serial.begin(9600);
    for (int i = 0;i<NUMBER_CONTROL;i++)
    {
      pinMode(control[i],INPUT_PULLUP);
    }
    pinMode(emLockScene,OUTPUT);
    pinMode(emLockTunnelEntrance,OUTPUT);
    Reset();
    Serial.println("Catapult 2017/11/07 iLYuSha Wakaka KocmocA");
}

void loop() 
{
    /* Input訊號 */
    for(int k = 0 ; k < NUMBER_CONTROL ; k++)
    {
      valueControl[k] = Digital2Value(valueControl[k], digitalRead(control[k]));
    }
    /* Unity Input訊號 */
    msgUnity = Serial.read();
    /* Unity Output訊號 */
    commandUnity = "";
    /* 溝通檢查 */
     commandUnity+="Wakaka/";

    if(msgUnity == 'R')
        Reset();
    if(msgUnity == 'T')
        digitalWrite(emLockTunnelEntrance,LOW);

    if(valueControl[LOADING] >= durationLimit)
    {
        if(valueControl[SCENE] == 0)
            digitalWrite(emLockScene,LOW); 
        else
            digitalWrite(emLockScene,HIGH); 
        commandUnity+="Loading";
    }
    
    commandUnity+="/";
    
    if (valueControl[RUNE_ODAL] > 0)
    {
        if (valueControl[RUNE_JERAN] >0 && valueControl[RUNE_EHWAZ] > 0)
            commandUnity+="Rune7";
        else if (valueControl[RUNE_JERAN] > 0)
            commandUnity+="Rune4";
        else if (valueControl[RUNE_EHWAZ] > 0)
            commandUnity+="Rune6";
        else
            commandUnity+="Rune1";
    }
    else if (valueControl[RUNE_JERAN] > 0)
    {
        if (valueControl[RUNE_EHWAZ] > 0)
            commandUnity+="Rune5";
        else
            commandUnity+="Rune2";
    }
    else if (valueControl[RUNE_EHWAZ] > 0)
        commandUnity+="Rune3";
    else
        commandUnity+="Rune0";
    
    commandUnity+="/";

    if(valueControl[LEFT_HIGH] > 0)
        commandUnity+="LeftHigh";
    else if(valueControl[LEFT_LOW] > 0)
        commandUnity+="LeftLow";
    else if(valueControl[RIGHT_HIGH] > 0)
        commandUnity+="RightHigh";
    else if(valueControl[RIGHT_LOW] > 0)
        commandUnity+="RightLow";
    
    commandUnity+="/";

    if(valueControl[NODE_12] > 0)
    {
        if(lastNode == 8)
            commandUnity+="Anticlockwise";
        else if(lastNode == 4)
            commandUnity+="Clockwise";
        lastNode = 12;
    }
    else if(valueControl[NODE_4] > 0)
    {
      //  commandUnity+="NODE4";
        if(lastNode >= 12)
            commandUnity+="Anticlockwise";
        else if(lastNode == 8)
            commandUnity+="Clockwise";
        lastNode = 4;
    }
    else if(valueControl[NODE_8] > 0)
    {
        if(lastNode == 4)
            commandUnity+="Anticlockwise";
        else if(lastNode == 12)
            commandUnity+="Clockwise";
        lastNode = 8;
    }
    
    Serial.println(commandUnity);
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
void Reset()
{
    digitalWrite(emLockTunnelEntrance,HIGH);
    digitalWrite(emLockScene,HIGH);
}
