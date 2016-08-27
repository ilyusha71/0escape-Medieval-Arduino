/******************************************
  Title: Catapult Controller
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/04/23
*******************************************/
/* Input */
const int leftLow = 4;
const int leftHigh = 5;
const int rightLow = 6;
const int rightHigh = 7;
const int node12 = 8;
const int node4 = 9;
const int node8 = 10;
/* Output */
const int emLockTunnelEntrance = 13;
/* Variable */
int valueLeftLow = 0;
int valueLeftHigh = 0;
int valueRightLow = 0;
int valueRightHigh = 0;
int valueNode12 = 0;
int valueNode4 = 0;
int valueNode8 = 0;
boolean unlocked = false;
char unlock;
void setup() 
{
  Serial.begin(9600);
  pinMode(leftLow,INPUT_PULLUP);
  pinMode(leftHigh,INPUT_PULLUP);
  pinMode(rightLow,INPUT_PULLUP);
  pinMode(rightHigh,INPUT_PULLUP);
  pinMode(node12,INPUT_PULLUP);
  pinMode(node4,INPUT_PULLUP);
  pinMode(node8,INPUT_PULLUP);
  pinMode(emLockTunnelEntrance,OUTPUT);
  digitalWrite(emLockTunnelEntrance,HIGH);
  Serial.println("Catapult Controller 2016/04/23 iLYuSha Wakaka KocmocA");
}

void loop() 
{
  unlock = Serial.read();
  valueLeftLow = digitalRead(leftLow);
  valueLeftHigh = digitalRead(leftHigh);
  valueRightLow = digitalRead(rightLow);
  valueRightHigh = digitalRead(rightHigh);
  valueNode12 = digitalRead(node12);
  valueNode4 = digitalRead(node4);
  valueNode8 = digitalRead(node8);

  if(!unlocked)
  {
    if(unlock == '1')
    {
      digitalWrite(emLockTunnelEntrance,LOW);
      unlocked = true;
    }
  }

  if(valueLeftLow == 0)
    Serial.println("Turn Left Low");
  else if(valueLeftHigh == 0)
    Serial.println("Turn Left High");
  else if(valueRightLow == 0)
    Serial.println("Turn Right Low");
  else if(valueRightHigh == 0)
    Serial.println("Turn Right High");
    
  if(valueNode12 == 0)
    Serial.println("Reed Switch Node 12");
  else if(valueNode4 == 0)
    Serial.println("Reed Switch Node 4");
  else if(valueNode8 == 0)
    Serial.println("Reed Switch Node 8");
}
