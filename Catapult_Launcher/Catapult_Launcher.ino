/******************************************
  Title: Catapult Launcher
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/04/23
*******************************************/
/* Input */
const int reload = 2;
const int chargeUp = 3;
const int chargeDown = 4;
const int rune1 = 5;
const int rune2 = 6;
const int rune3 = 7;
/* Output */
const int emLockStone = 13;
/* Variable */
int valueReload = 0;
int valueChargeUp = 0;
int valueChargeDown = 0;
int valueRuneA = 0;
int valueRuneB = 0;
int valueRuneC = 0;
boolean unlocked = true;
char unlock;
void setup() 
{
  Serial.begin(9600);
  Serial.println("Catapult Launcher 2016/04/23 iLYuSha Wakaka KocmocA");
  pinMode(reload,INPUT_PULLUP);
  pinMode(chargeUp,INPUT_PULLUP);
  pinMode(chargeDown,INPUT_PULLUP);
  pinMode(rune1,INPUT_PULLUP);
  pinMode(rune2,INPUT_PULLUP);
  pinMode(rune3,INPUT_PULLUP);
  pinMode(emLockStone,OUTPUT);
  digitalWrite(emLockStone,HIGH);
}

void loop() 
{
  unlock = Serial.read();
  valueReload = digitalRead(reload);
  valueChargeUp = digitalRead(chargeUp);
  valueChargeDown = digitalRead(chargeDown);
  valueRuneA = digitalRead(rune1);
  valueRuneB = digitalRead(rune2);
  valueRuneC = digitalRead(rune3);

  if(unlock == '1')
  {
    digitalWrite(emLockStone,LOW);
    delay (1000);
    digitalWrite(emLockStone,HIGH);
  }

  if(valueReload == 0)
  {
    Serial.println("Reload");
  }

  if(valueChargeUp == 0)
    Serial.println("Charge Up");
  if(valueChargeDown == 0)
    Serial.println("Charge Down");

  if (valueRuneA == 0)
  {
    if (valueRuneB == 0 && valueRuneC == 0)
      Serial.println("7");
    else if (valueRuneB == 0)
      Serial.println("4");
    else if (valueRuneC == 0)
      Serial.println("6");
    else
      Serial.println("1");
  }
  else if (valueRuneB == 0)
  {
    if (valueRuneC == 0)
      Serial.println("5");
    else
      Serial.println("2");
  }
  else if (valueRuneC == 0)
    Serial.println("3");
}
