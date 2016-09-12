/******************************************
  Title: Magic Altar
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/08/28
*******************************************/
/* Input */
const int holyGrail = 2;
const int dragonFang = 3;
const int roundTable = 4;
const int crown = 5;
const int heartDestruction = 6;
const int heartRedemption = 7;
/* Output */
const int activeTomb = 8; // Ancient Tomb Active
const int activeAltar = 9; //uvLight,caliburn
const int emLockMagic = 10; // Magician Room
const int magic = 11; // Animation 1st
const int destruction = 12; // Animation 2nd
const int redemption = 13; // Animation 3rd
/* Function */
int holyGrailValue = 0;
int dragonFangValue = 0;
int roundTableValue = 0;
int crownValue = 0;
int heartDestructionValue = 0;
int heartRedemptionValue = 0;
boolean enableMagicAltar = false;

void setup() {
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
  pinMode(magic,OUTPUT);
  pinMode(destruction,OUTPUT);
  pinMode(redemption,OUTPUT);
  digitalWrite(activeTomb, LOW);
  digitalWrite(activeAltar, LOW);
  digitalWrite(emLockMagic, LOW);
  digitalWrite(magic, LOW);
  digitalWrite(destruction, LOW);
  digitalWrite(redemption, LOW);
  Serial.println("Magic Altar 2016/08/28 iLYuSha Wakaka KocmocA");
  delay(3000);
}

void loop() {
  holyGrailValue = digitalRead(holyGrail);
  dragonFangValue = digitalRead(dragonFang);
  roundTableValue = digitalRead(roundTable);
  crownValue = digitalRead(crown);
  heartDestructionValue = digitalRead(heartDestruction);
  heartRedemptionValue = digitalRead(heartRedemption);
  
  if(holyGrailValue == 1 && dragonFangValue == 1 && roundTableValue == 1 && crownValue == 1)
  {
    if(!enableMagicAltar)
    {
      digitalWrite(activeTomb, HIGH);
      digitalWrite(activeAltar, HIGH);
      digitalWrite(magic, HIGH);
      enableMagicAltar = true;
    }
    else
    {
      if(heartDestructionValue == 1)
        digitalWrite(destruction, HIGH);
        
      if(heartRedemptionValue == 1)
      {
        digitalWrite(emLockMagic, HIGH);
        digitalWrite(redemption, HIGH);
      }
    }
  }
}
