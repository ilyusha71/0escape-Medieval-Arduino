/******************************************
  Title: Dragon Cave
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2015/11/26
*******************************************/

/* Input */
const int active = 13;
const int punishmentTrigger = 8;
const int passTrigger = 9;
int valueActive;
int valuePunishment;
int valuePass;

/* Output */
const int punishmentA = 2;
const int punishmentB = 3;
const int punishmentC = 4;
const int pass = 5;

/* Variable */
int numPunishment = 1;
boolean start = false;
boolean trigger = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(active,INPUT);
  pinMode(punishmentTrigger,INPUT);
  pinMode(passTrigger,INPUT);
  pinMode(punishmentA,OUTPUT);
  pinMode(punishmentB,OUTPUT);
  pinMode(punishmentC,OUTPUT);
  pinMode(pass,OUTPUT);
  
  digitalWrite(punishmentA,HIGH);
  digitalWrite(punishmentB,HIGH);
  digitalWrite(punishmentC,HIGH);
  digitalWrite(pass, HIGH);

  Serial.println("Dragon Cave 2015/11/26 iLYuSha 2016");
}

void loop() 
{
  valueActive = digitalRead(active);
  valuePunishment = digitalRead(punishmentTrigger);
  valuePass = digitalRead(passTrigger);

  if (valueActive == 1)
    start = true;

  if(start)
  {
    if (valuePunishment == 1 && !trigger)
    {
      trigger = true;
      if (numPunishment == 1)
        digitalWrite(punishmentA, LOW);
      if (numPunishment == 2)
        digitalWrite(punishmentB, LOW);
      if (numPunishment == 3)
        digitalWrite(punishmentC, LOW);
      numPunishment++;
    }
    else if (valuePunishment == 0 && trigger)
    {
      trigger = false;
    }
    if (valuePass == 1)
    {
      digitalWrite(pass, LOW);
    }
  }
}
