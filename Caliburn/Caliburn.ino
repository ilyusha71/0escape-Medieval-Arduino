/******************************************
  Title: Caliburn
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/08
*******************************************/
/* Output */
const int caliburnLock = 8;
const int remote = 9;

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  pinMode(caliburnLock, OUTPUT);
  pinMode(remote, OUTPUT);
  digitalWrite(caliburnLock, HIGH);
  digitalWrite(remote, HIGH);
  Serial.println("Caliburn 2016/09/08 iLYuSha Wakaka KocmocA");
  delay(3000);
  digitalWrite(remote, LOW);
}

void loop() 
{
  delay(200000);
  digitalWrite(caliburnLock, LOW);
  delay(10000);
  digitalWrite(caliburnLock, HIGH);
}
