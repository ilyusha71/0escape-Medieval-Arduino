/******************************************
  Title: Caliburn
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/08
*******************************************/
/* Output */
const int eA = 4;
const int eB = 5;
const int eC = 6;
const int eD = 7;

int AA;
int BB;
int CC;
int DD;

char kk;

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  pinMode(eA, OUTPUT);
  pinMode(eB, OUTPUT);
  pinMode(eC, OUTPUT);
  pinMode(eD, OUTPUT);
  digitalWrite(eA, HIGH);
  digitalWrite(eB, HIGH);
  digitalWrite(eC, HIGH);
  digitalWrite(eD, HIGH);
  Serial.println("EEE 2016/09/08 iLYuSha Wakaka KocmocA");
}

void loop() 
{
 kk = Serial.read();
 if(kk == 'a')
   digitalWrite(eA, HIGH);
 else  if(kk == 'b')
   digitalWrite(eB, HIGH);
 else  if(kk == 'c')
   digitalWrite(eC, HIGH);
 else  if(kk == 'd')
   digitalWrite(eD, HIGH);
 else  if(kk == 'e')
   digitalWrite(eA, LOW);
 else  if(kk == 'f')
   digitalWrite(eB, LOW);
 else  if(kk == 'g')
   digitalWrite(eC, LOW);
 else  if(kk == 'h')
   digitalWrite(eD, LOW);

   AA = digitalRead(eA);
BB = digitalRead(eB);
CC = digitalRead(eC);
DD = digitalRead(eD);
   Serial.print("A: ");
   Serial.print(AA);
   Serial.print("  B: ");
   Serial.print(BB);
   Serial.print("  C: ");
   Serial.print(CC);
   Serial.print("  D: ");
    Serial.println(DD);
}
