/******************************************
  Title: Caliburn
  Studio: iLYuSha Wakaka & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/08
*******************************************/
/* Output */
const int remote = 8;
const int caliburnLock = 9;

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  pinMode(remote, OUTPUT);
  pinMode(caliburnLock, OUTPUT);
  digitalWrite(remote, HIGH);
  digitalWrite(caliburnLock, HIGH);
  Serial.println("Caliburn 2016/09/08 iLYuSha Wakaka KocmocA");
  delay(3000);
  digitalWrite(remote, LOW);
  digitalWrite(caliburnLock, LOW);
}

void loop() 
{
  delay(60000);
  digitalWrite(caliburnLock, HIGH);
  delay(10000);
  digitalWrite(caliburnLock, LOW);
}
