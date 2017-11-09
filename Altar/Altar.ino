/**************************************************************************************** 
 * Wakaka Studio 2017
 * Author: iLYuSha Dawa-mumu Wakaka Kocmocovich Kocmocki KocmocA
 * Project: 0escape Medieval - Altar
 * Tools: Unity 5.6 + Arduino Mega2560
 * Last Updated: 2017/11/05
 ****************************************************************************************/
#define ALTAR_HOLY_GRAIL 0
#define ALTAR_ROUND_TABLE 1
#define ALTAR_DRAGON_FANG 2
#define ALTAR_CROWN 3
#define ALTAR_HEART_DESTRUCTION 4
#define ALTAR_HEART_REDEMPTION 5
#define PROPHET_HOLY_GRAIL 6
#define PROPHET_ROUND_TABLE 7
#define PROPHET_DRAGON_FANG 8
#define PROPHET_CROWN 9
#define NUMBER_CONTROL 10
/* Input */
const int control[NUMBER_CONTROL] = {23,25,27,29,31,33,35,36,39,41};
int msgUnity;
/* Output */
const int signalMagicAltar = 47;
const int signalDestruction = 49;
const int signalRedemption = 51;
const int signalProphet = 53;
String commandUnity;
/* Retained Variable */
int valueControl[NUMBER_CONTROL];
int durationMax = 1000;
int durationLimit = 10;
/* Flag */
boolean enableMagicAltar = false;
boolean enableProphetMission = false;

void setup() 
{
    Serial.begin(9600);
    for (int i = 0;i<NUMBER_CONTROL;i++)
    {
      pinMode(control[i],INPUT_PULLUP);
    }
    pinMode(48,INPUT_PULLUP);
    pinMode(signalMagicAltar,OUTPUT);
    pinMode(signalDestruction,OUTPUT);
    pinMode(signalRedemption,OUTPUT);
    pinMode(signalProphet,OUTPUT);
    digitalWrite(signalMagicAltar, HIGH);
    digitalWrite(signalDestruction, HIGH);
    digitalWrite(signalRedemption, HIGH);
    digitalWrite(signalProphet, HIGH);
    Serial.println("Altar 2017/11/05 iLYuSha Wakaka KocmocA");
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
    if(msgUnity == '5')
        enableMagicAltar = true;
    if(msgUnity == '9')
      enableProphetMission = true;

    if(!enableMagicAltar)
    {
        if(valueControl[ALTAR_HOLY_GRAIL] > durationLimit)
            commandUnity+="HolyGrail.";
        if(valueControl[ALTAR_ROUND_TABLE] > durationLimit)
            commandUnity+="RoundTable.";
        if(valueControl[ALTAR_DRAGON_FANG] > durationLimit)
            commandUnity+="DragonFang.";
        if(valueControl[ALTAR_CROWN] > durationLimit)
            commandUnity+="Crown.";
        if(valueControl[ALTAR_HOLY_GRAIL] > durationLimit &&
           valueControl[ALTAR_ROUND_TABLE] > durationLimit && 
           valueControl[ALTAR_DRAGON_FANG] > durationLimit && 
           valueControl[ALTAR_CROWN] > durationLimit)
        {
            commandUnity+="Altar.";
            digitalWrite(signalMagicAltar, LOW);
        }
    }
    if(digitalRead(48)==0)
      commandUnity+="This is test pin";
    if(!enableProphetMission)
    {
        if(valueControl[ALTAR_HOLY_GRAIL] > durationLimit &&
           valueControl[ALTAR_ROUND_TABLE] > durationLimit && 
           valueControl[ALTAR_DRAGON_FANG] > durationLimit && 
           valueControl[ALTAR_CROWN] > durationLimit)
        {
            if(valueControl[ALTAR_HEART_DESTRUCTION] > durationLimit)
            {
                commandUnity+="Destruction";
                digitalWrite(signalDestruction, LOW);
            }
            else if(valueControl[ALTAR_HEART_REDEMPTION] > durationLimit)
            {
                commandUnity+="Redemption";
                digitalWrite(signalRedemption, LOW);
            }
        }
    }
    else
    {
        if(valueControl[ALTAR_HEART_REDEMPTION] > durationLimit)
            commandUnity+="P5.";
        if(valueControl[PROPHET_HOLY_GRAIL] > durationLimit)
            commandUnity+="P1.";
        if(valueControl[PROPHET_ROUND_TABLE] > durationLimit)
            commandUnity+="P2.";
        if(valueControl[PROPHET_DRAGON_FANG] > durationLimit)
            commandUnity+="P3.";
        if(valueControl[PROPHET_CROWN] > durationLimit)
            commandUnity+="P4.";
        if(valueControl[ALTAR_HEART_REDEMPTION] > durationLimit &&
           valueControl[PROPHET_HOLY_GRAIL] > durationLimit &&
           valueControl[PROPHET_ROUND_TABLE] > durationLimit &&
           valueControl[PROPHET_DRAGON_FANG] > durationLimit &&
           valueControl[PROPHET_CROWN] > durationLimit)
        {
            commandUnity+="Prophet.";
            digitalWrite(signalProphet, LOW);
        }
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
    enableMagicAltar = false;
    enableProphetMission = false;
    digitalWrite(signalMagicAltar, HIGH);
    digitalWrite(signalDestruction, HIGH);
    digitalWrite(signalRedemption, HIGH);
    digitalWrite(signalProphet, HIGH);
}
