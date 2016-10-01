/******************************************
  Title: Magic Altar & Prophet - Crown
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/10/01
*******************************************/
#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information

#define SHOW_TAG_ID
/* Constant for Tag ID */
const int tagCrown[4] = {90,241,0,185}; // 5AF10B9
/* Output */
const int passCrown = 8;
/* Variable */
int escape = 0;

void setup() 
{
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  
  for (byte i = 0; i < 6; i++) {
          key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }

  pinMode(passCrown,OUTPUT);
  digitalWrite(passCrown, LOW);
  Serial.println("Magic Altar & Prophet - Crown 2016/10/01 iLYuSha Wakaka KocmocA");
}

int block=2;//this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.
byte blockcontent[16] = {"makecourse_____"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

void loop()
{
  if(escape == -1)
  {
    ShowTagID();
    
    if(mfrc522.uid.uidByte[0] == tagCrown[0] && 
    mfrc522.uid.uidByte[1] == tagCrown[1] && 
    mfrc522.uid.uidByte[2] == tagCrown[2] && 
    mfrc522.uid.uidByte[3] == tagCrown[3])
    {
      digitalWrite(passCrown, HIGH);
      Serial.print(" Crown Bingo ");
      ShowTagID();
      Serial.println("");
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
    digitalWrite(passCrown, LOW);
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
    Serial.print(mfrc522.uid.uidByte[i],HEX);
  }
  Serial.println("");
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
