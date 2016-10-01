/******************************************
  Title: Magic Altar
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/10/01
*******************************************/
/* Input */
const int holyGrail = 2;
const int roundTable = 3;
const int dragonFang = 4;
const int crown = 5;
const int heartDestruction = 6;
const int heartRedemption = 7;
/* Input Variable */
int digitalHolyGrail = 0;
int digitalRoundTable = 0;
int digitalDragonFang = 0;
int digitalCrown = 0;
int digitalDestruction = 0;
int digitalRedemption = 0;
/* Retained Variable */
int valueHolyGrail = 0;
int valueRoundTable = 0;
int valueDragonFang = 0;
int valueCrown = 0;
int valueDestruction = 0;
int valueRedemption = 0;
/* Output */
const int activeTomb = 8; // Ancient Tomb Active
const int activeAltar = 9; //uvLight, Caliburn
const int emLockMagic = 10; // Magician Room
const int animMagic = 11; // Animation 1st
const int animDestruction = 12; // Animation 2nd
const int animRedemption = 13; // Animation 3rd
/* Function */
boolean enableMagicAltar = false;
/* Variable */
int passLoop = 1000;

void setup() 
{
  Serial.begin(9600);        // Initialize serial communications with the PC
  pinMode(holyGrail,INPUT);
  pinMode(dragonFang,INPUT);
  pinMode(roundTable,INPUT);
  pinMode(crown,INPUT);
  pinMode(heartDestruction,INPUT);
  pinMode(heartRedemption,INPUT);  
  pinMode(activeTomb,OUTPUT);
  pinMode(activeAltar,OUTPUT);
  pinMode(emLockMagic,OUTPUT);
  pinMode(animMagic,OUTPUT);
  pinMode(animDestruction,OUTPUT);
  pinMode(animRedemption,OUTPUT);
  digitalWrite(activeTomb, LOW); // NO
  digitalWrite(activeAltar, LOW); // NO
  digitalWrite(emLockMagic, LOW); // NC
  digitalWrite(animMagic, HIGH);
  digitalWrite(animDestruction, HIGH);
  digitalWrite(animRedemption, HIGH);
  Serial.println("Magic Altar 2016/10/01 iLYuSha Wakaka KocmocA");
}

int Digital2Value(int value, int digital)
{
  digital == 1 ? value++ : value = 0;
  return value;
}

void loop() 
{
  valueHolyGrail = Digital2Value(valueHolyGrail, digitalRead(holyGrail));
  valueRoundTable = Digital2Value(valueRoundTable, digitalRead(roundTable));
  valueDragonFang = Digital2Value(valueDragonFang, digitalRead(dragonFang));
  valueCrown = Digital2Value(valueCrown, digitalRead(crown));
  valueDestruction = Digital2Value(valueDestruction, digitalRead(heartDestruction));
  valueRedemption = Digital2Value(valueRedemption, digitalRead(heartRedemption));
  
  if(valueHolyGrail > passLoop && valueRoundTable > passLoop && valueDragonFang > passLoop && valueCrown > passLoop)
  {
    if(!enableMagicAltar)
    {
      digitalWrite(activeTomb, HIGH);
      digitalWrite(activeAltar, HIGH);
      digitalWrite(animMagic, LOW);
      enableMagicAltar = true;
    }
    else
    {
      if(valueDestruction > passLoop)
        digitalWrite(animDestruction, LOW);
        
      if(valueRedemption > passLoop)
      {
        digitalWrite(emLockMagic, HIGH);
        digitalWrite(animRedemption, LOW);
      }
    }
  }
}
