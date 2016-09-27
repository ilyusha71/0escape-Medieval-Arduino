/******************************************
  Title: Help Bell
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/18
*******************************************/
/* Input */
const int triggerBell = 2;
const int reset = 3;
/* Output */
const int soundBell = 8;
/* Function */
int digitalBell = 0;
int digitalReset = 0;
int valueBell = 0;
int valueReset = 0;

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  pinMode(triggerBell,INPUT_PULLUP);
  pinMode(reset,INPUT_PULLUP);
  pinMode(soundBell,OUTPUT);
  digitalWrite(soundBell, LOW);
  Serial.println("Help Bell 2016/09/18 iLYuSha Wakaka KocmocA");
}

void loop() {
  digitalBell = digitalRead(triggerBell);
  digitalReset = digitalRead(reset);
  
  digitalBell == 1 ? valueBell++ : valueBell=0;
  digitalReset == 0 ? valueReset++ : valueReset=0;

  if(valueBell > 30)
    digitalWrite(soundBell, HIGH);
  if(valueReset > 30)
    digitalWrite(soundBell, LOW);
}
