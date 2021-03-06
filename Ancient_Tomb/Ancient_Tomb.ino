/******************************************
  Title: Ancient Tomb
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/10
*******************************************/
#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information

#define SHOW_TAG_ID
/* Constant for Redemption Slate Tag ID */
const int tagRedemption[4] = {81,136,167,213}; // 5188A7D5
const int tagTombGate[4] = {117,28,160,9}; // 751CA09
/* Input */
const int sensorIR = 2;
const int reedSwitchTombGate = 3;
/* Input Variable */
int digitalIR = 0;
int digitalTombGate = 0;
/* Retained Variable */
int valueIR = 0;
int valueTombGate = 0;
/* Output */
const int emLockDestruction = 5;
const int emLockRedemption = 6;
const int emLockTombGate = 7;
/* Variable */
int escape = 0;

void setup() 
{
    Serial.begin(9600);        // Initialize serial communications with the PC
    SPI.begin();               // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
    //Serial.println("Scan a MIFARE Classic card");
    for (byte i = 0; i < 6; i++) 
    {
      key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
    }

  pinMode(sensorIR,INPUT); // IR will feedback 3.7 Volts
  pinMode(reedSwitchTombGate,INPUT_PULLUP);
  pinMode(emLockDestruction,OUTPUT);
  pinMode(emLockRedemption,OUTPUT);
  pinMode(emLockTombGate,OUTPUT);
  digitalWrite(emLockDestruction, HIGH);
  digitalWrite(emLockRedemption, HIGH);
  digitalWrite(emLockTombGate, LOW);
  Serial.println("Ancient Tomb 2016/09/10 iLYuSha Wakaka KocmocA");
}

int block=2;//this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.

byte blockcontent[16] = {"makecourse_____"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

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
void loop()
{
  digitalIR = digitalRead(sensorIR);
  digitalTombGate = digitalRead(reedSwitchTombGate);
  digitalIR == 1 ? valueIR++ : valueIR=0;
  digitalTombGate == 1 ? valueTombGate++ : valueTombGate=0;

  /* Traitor Mission */
  if(valueTombGate > 30)
  {
      digitalWrite(emLockTombGate, HIGH);
      if(valueIR > 30)
        digitalWrite(emLockDestruction, LOW);
  }
  else
      digitalWrite(emLockTombGate, LOW);

  if(escape == -1)
  {
    ShowTagID();
    /* Redeemer Mission*/
    if(mfrc522.uid.uidByte[0] == tagRedemption[0] && mfrc522.uid.uidByte[1] == tagRedemption[1] && mfrc522.uid.uidByte[2] == tagRedemption[2] && mfrc522.uid.uidByte[3] == tagRedemption[3])
    {
      digitalWrite(emLockRedemption, LOW);
      Serial.print("Redeemer Bingo ");
      ShowTagID();
      Serial.println("");
    }
    else if(mfrc522.uid.uidByte[0] == tagTombGate[0] && mfrc522.uid.uidByte[1] == tagTombGate[1] && mfrc522.uid.uidByte[2] == tagTombGate[2] && mfrc522.uid.uidByte[3] == tagTombGate[3])
    {
      digitalWrite(emLockTombGate, LOW);
      Serial.print("TombGate Bingo ");
      ShowTagID();
      Serial.println("");
    }
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
         /*****************************************writing and reading a block on the card**********************************************************************/

  Serial.print("uid:");
  for(int i=0;i<mfrc522.uid.size;i++)
  {
    Serial.print(mfrc522.uid.uidByte[i],HEX);
  }
  Serial.println("");
}
