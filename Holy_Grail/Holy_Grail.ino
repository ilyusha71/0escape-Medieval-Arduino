/******************************************
  Title: Holy Grail
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2017/07/11
*******************************************/
/******************************************
  PURPOSE:  Learn to use the MF522-AN RFID card reader 
  Created by      Rudy Schlaf for www.makecourse.com
  DATE:   2/2014
*******************************************/
#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information

#define SHOW_TAG_ID
/* RFID Variable */
int tag[4];
int escape = 0;
/* Constant for Tag ID */
int tagBadge[4] = {84,174,186,235}; // EC3EF87
/* Constant for Badge(Back up) Tag ID */
int tagBackup[4] = {64,188,28,51};
/* Output */
const int pass = 2;
const int LED = 3;
/* Input */
const int bridge = 4;
/* Variable */
int valueLock;
int valueBridge;
char unlock = 0; // Receive Unity Command
boolean checkRFID = false; // On Card Trigger Enter is true, imdepedent of bridge
boolean induction = false; // On Card Trigger Enter is true
boolean unlocked = false;
void setup() 
{
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  
  for (byte i = 0; i < 6; i++) {
          key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }

    pinMode(pass,OUTPUT);
    pinMode(LED,OUTPUT);
    pinMode(bridge,INPUT);
    digitalWrite(pass, LOW);
    digitalWrite(LED, LOW);
    Serial.println("Medieval - Holy Grail - 2016/08/13 iLYuSha Wakaka KocmocA");
}

int block=2;//this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.

byte blockcontent[16] = {"makecourse_____"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//all zeros. This can be used to delete a block.
byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

void loop()
{
  valueBridge = digitalRead(bridge);
  unlock = Serial.read();
  if(!unlocked)
  {
    if(unlock == '1')
    {
      unlocked = true;
      digitalWrite(pass, HIGH);
      digitalWrite(LED, HIGH);
      delay(10000);
      Serial.println("Locked");
      delay(300);
      digitalWrite(pass, LOW);
      digitalWrite(LED, LOW);
      unlocked = false;
      delay(1000);
      mfrc522.PCD_Init();      
    }
    
    if(valueBridge == 0)
    {
      Serial.println("Bridge");
      valueLock++;
    }
    else if(valueBridge == 1)
      valueLock = 0;      
  }      

  if(escape == -1)
  {
    Serial.println("RFID");
    if(valueLock > 10)
    {
        if(CheckTagID(tagBadge))
        {
          Serial.println("Release");
          //ShowTagID();
        }
        else if(CheckTagID(tagBackup))
        {
          Serial.println("Release");
          //ShowTagID();
        }
        else
        {
          Serial.println("Refuse");
          //ShowTagID();
        }
    }
  }
  /* 重啟機制 */
  /********************************************* 
   *  避免RFID當掉的自動重啟方法
  **********************************************/
  else if(escape > 300)
  {
    escape = 0;
    mfrc522.PCD_Init();
  }
  /* 復位機制 */
  /********************************************* 
   *  Important!!! escape每次迴圈都會+1
   *  Arduino RFID 第一次進入迴圈會確認Tag並讀取(escape = -1)
   *  Arduino RFID 第二次進入迴圈【一定】會return跳出(escape = 0)
   *  故判斷Tag離開會在第三次進入迴圈
   *  此時如果Tag仍留著，escape = -1
   *  反之，escape = 1
   *  所以第四次迴圈判斷條件如下
  **********************************************/
  else if(escape > 0)
  {
  }
  /*****************************************establishing contact with a tag/card**********************************************************************/
  // Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if ( ! mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    escape++;
    return;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }
  escape = -1;
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return;//if it returns a '0' something went wrong and we return to the start of the loop
  }
 
  Serial.print("uid:");
  for(int i=0;i<mfrc522.uid.size;i++)
  {
    tag[i] = mfrc522.uid.uidByte[i];
    Serial.print(mfrc522.uid.uidByte[i],HEX);
  }
  Serial.print(" ");
  ShowTagID();
}

void ShowTagID()
{
  #ifdef SHOW_TAG_ID
  Serial.print("Tag ID: ");
  Serial.print(mfrc522.uid.uidByte[0]);
  Serial.print(" , ");
  Serial.print(mfrc522.uid.uidByte[1]);
  Serial.print(" , ");
  Serial.print(mfrc522.uid.uidByte[2]);
  Serial.print(" , ");
  Serial.println(mfrc522.uid.uidByte[3]);
  #endif
}

boolean CheckTagID(int tagWakaka [])
{
  for(int i = 0; i < 4 ; i++ )
  {
    if(tag[i] != tagWakaka[i])
      return false;
  }
  return true;
}
