/******************************************
  Title: Dragonlord
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2015/11/20
*******************************************/
/* Input */
const int blade2 = 2;
const int blade3 = 3;
const int blade4 = 4;
const int blade5 = 5;
const int blade6 = 6;
const int blade7 = 7;
const int blade8 = 8;
const int blade9 = 9;
const int blade10 = 10;
const int blade11 = 11;
int valueBlade2;
int valueBlade3;
int valueBlade4;
int valueBlade5;
int valueBlade6;
int valueBlade7;
int valueBlade8;
int valueBlade9;
int valueBlade10;
int valueBlade11;
/* Output */
const int punishmentTrigger = 12;
const int passTrigger = 13;
/* Variable */
int lastValueBlade2 = 1;
int lastValueBlade3 = 1;
int lastValueBlade4 = 1;
int lastValueBlade5 = 1;
int lastValueBlade6 = 1;
int lastValueBlade7 = 1;
int lastValueBlade8 = 1;
int lastValueBlade9 = 1;
int lastValueBlade10 = 1;
int lastValueBlade11 = 1;
int numHit = 0;
int numLastHit = 0;
boolean determination = false;
boolean firstblood = false;
boolean hitDragonwing = false;
boolean pass = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(blade2,INPUT_PULLUP);
  pinMode(blade3,INPUT_PULLUP);
  pinMode(blade4,INPUT_PULLUP);
  pinMode(blade5,INPUT_PULLUP);
  pinMode(blade6,INPUT_PULLUP);
  pinMode(blade7,INPUT_PULLUP);
  pinMode(blade8,INPUT_PULLUP);
  pinMode(blade9,INPUT_PULLUP);
  pinMode(blade10,INPUT_PULLUP);
  pinMode(blade11,INPUT_PULLUP);
  pinMode(punishmentTrigger,OUTPUT);
  pinMode(passTrigger,OUTPUT);
  digitalWrite(punishmentTrigger, LOW);
  digitalWrite(passTrigger, LOW);
     
  Serial.println("Dragonlord 2015/11/26 iLYuSha 1649");
}

void loop() 
{
  valueBlade2 = digitalRead(blade2);
  valueBlade3 = digitalRead(blade3);
  valueBlade4 = digitalRead(blade4);
  valueBlade5 = digitalRead(blade5);
  valueBlade6 = digitalRead(blade6);
  valueBlade7 = digitalRead(blade7);
  valueBlade8 = digitalRead(blade8);
  valueBlade9 = digitalRead(blade9);
  valueBlade10 = digitalRead(blade10);
  valueBlade11 = digitalRead(blade11);
  
  if (valueBlade2 != lastValueBlade2)
  {
    if (valueBlade2 == 0)
      numHit++;
    else if (valueBlade2 == 1)
      numHit--;
  }
  if (valueBlade3 != lastValueBlade3)
  {
    if (valueBlade3 == 0)
      numHit++;
    else if (valueBlade3 == 1)
      numHit--;
  }
  if (valueBlade4 != lastValueBlade4)
  {
    if (valueBlade4 == 0)
      numHit++;
    else if (valueBlade4 == 1)
      numHit--;
  }
  if (valueBlade5 != lastValueBlade5)
  {
    if (valueBlade5 == 0)
      numHit++;
    else if (valueBlade5 == 1)
      numHit--;
  }
  if (valueBlade6 != lastValueBlade6)
  {
    if (valueBlade6 == 0)
      numHit++;
    else if (valueBlade6 == 1)
      numHit--;
  }
  if (valueBlade7 != lastValueBlade7)
  {
    if (valueBlade7 == 0)
      numHit++;
    else if (valueBlade7 == 1)
      numHit--;
  }
  if (valueBlade8 != lastValueBlade8)
  {
    if (valueBlade8 == 0)
      numHit++;
    else if (valueBlade8 == 1)
      numHit--;
  }
  if (valueBlade9 != lastValueBlade9)
  {
    if (valueBlade9 == 0)
      numHit++;
    else if (valueBlade9 == 1)
      numHit--;
  }
  if (valueBlade10 != lastValueBlade10)
  {
    if (valueBlade10 == 0)
      numHit++;
    else if (valueBlade10 == 1)
      numHit--;
  }
  if (valueBlade11 != lastValueBlade11)
  {
    if (valueBlade11 == 0)
      numHit++;
    else if (valueBlade11 == 1)
      numHit--;
  }
  if (numHit != numLastHit)
  {
    if(numHit > numLastHit)
      determination = true;
    else if(numHit < numLastHit)
    {
      determination = false;
      digitalWrite(punishmentTrigger, LOW);
    }
  }
  Serial.print("numHit:   ");
  Serial.println(numHit);
    Serial.print("determination:   ");
  Serial.println(determination);
  if(determination)
  {
    if (!pass && valueBlade4 == 0 && valueBlade5 == 0 && valueBlade8 == 0 && valueBlade10 == 0)
    {
      pass = true;
      digitalWrite(passTrigger, HIGH);
    }
    else if (!firstblood && numHit == 1)
    {
      determination = false;
      firstblood = true;
      if (valueBlade8 != 0)
        digitalWrite(punishmentTrigger, HIGH);
    }
    else if (!hitDragonwing && valueBlade2 == 0 && firstblood)
    {
      determination = false;
      hitDragonwing = true;
      digitalWrite(punishmentTrigger, HIGH);
    }
    else if (numHit == 4 && !pass)
    {
      determination = false;
      digitalWrite(punishmentTrigger, HIGH);
    }
  }

  lastValueBlade2 = valueBlade2;
  lastValueBlade3 = valueBlade3;
  lastValueBlade4 = valueBlade4;
  lastValueBlade5 = valueBlade5;
  lastValueBlade6 = valueBlade6;
  lastValueBlade7 = valueBlade7;
  lastValueBlade8 = valueBlade8;
  lastValueBlade9 = valueBlade9;
  lastValueBlade10 = valueBlade10;
  lastValueBlade11 = valueBlade11;
  numLastHit = numHit;
}
