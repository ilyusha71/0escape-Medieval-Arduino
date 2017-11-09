/******************************************
  Title: Holy Grail
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/10/01
*******************************************/
/******************************************
  PURPOSE:  Learn to use the MF522-AN RFID card reader 
  Created by      Rudy Schlaf for www.makecourse.com
  DATE:   2/2014
*******************************************/

/*
 * This sketch uses the MFRC522 Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * 
 * This library has been released into the public domain.
*/

#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information
/* Constant for Badge Tag ID */
const int tag[4] = {84,174,186,235};
/* Constant for Badge(Back up) Tag ID */
const int tagBackup[4] = {64,188,28,51};
/* Output */
const int pass = 2;
const int LED = 3;
/* Input */
const int bridge = 4;
/* Variable */
int valueLock;
int valueBridge;
int escape = 0; // On Card Trigger Exit, this variable will > 1 (3rd frame)
char unlock = 0; // Receive Unity Command
boolean checkRFID = false; // On Card Trigger Enter is true, imdepedent of bridge
boolean induction = false; // On Card Trigger Enter is true
boolean unlocked = false;
void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
        Serial.println("Scan a MIFARE Classic card");
        
        // Prepare the security key for the read and write functions - all six key bytes are set to 0xFF at chip delivery from the factory.
        // Since the cards in the kit are new and the keys were never defined, they are 0xFF
        // if we had a card that was programmed by someone else, we would need to know the key to be able to access it. This key would then need to be stored in 'key' instead.
 
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

    // 人體電橋訊號不穩定
    if(valueBridge == 0)
      valueLock++;
    else if(valueBridge == 1)
      valueLock = 0;

    if(valueLock > 23)
      Serial.println("Bridge");

    // Give a initail number, avoid repeat "Reduse" Comman
    if(mfrc522.uid.uidByte[0] != 254 && mfrc522.uid.uidByte[1] != 254 && 
    mfrc522.uid.uidByte[2] != 254 && mfrc522.uid.uidByte[3] != 254)
    {  
      if(checkRFID)
      {
        Serial.println("RFID");
        checkRFID = false;
      }
      if(valueLock > 23)
      {
        if(mfrc522.uid.uidByte[0] == tag[0] && mfrc522.uid.uidByte[1] == tag[1] && 
        mfrc522.uid.uidByte[2] == tag[2] && mfrc522.uid.uidByte[3] == tag[3])
        {
          Serial.println("Release");
        }
        else if(mfrc522.uid.uidByte[0] == tagBackup[0] && mfrc522.uid.uidByte[1] == tagBackup[1] && 
        mfrc522.uid.uidByte[2] == tagBackup[2] && mfrc522.uid.uidByte[3] == tagBackup[3])
        {
          Serial.println("Release");
        }
        else
        {
          if(induction)
          {
            Serial.println("Refuse");
          }
        }
        induction = false;
      }
    }
  }       
    
  mfrc522.uid.uidByte[0] = -2;
  mfrc522.uid.uidByte[1] = -2;
  mfrc522.uid.uidByte[2] = -2;
  mfrc522.uid.uidByte[3] = -2;

        /*****************************************establishing contact with a tag/card**********************************************************************/
        
    // Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if ( ! mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    escape++;
    return;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }
  escape = 0;
  induction = true;
  checkRFID = true;
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return;//if it returns a '0' something went wrong and we return to the start of the loop
  }

        // Among other things, the PICC_ReadCardSerial() method reads the UID and the SAK (Select acknowledge) into the mfrc522.uid struct, which is also instantiated
        // during this process.
        // The UID is needed during the authentication process
          //The Uid struct:
          //typedef struct {
    //byte    size;     // Number of bytes in the UID. 4, 7 or 10.
    //byte    uidByte[10];            //the user ID in 10 bytes.
    //byte    sak;      // The SAK (Select acknowledge) byte returned from the PICC after successful selection.
          //} Uid;
         
         //Serial.println("card selected");
         
         /*****************************************writing and reading a block on the card**********************************************************************/
         
         //writeBlock(block, blockcontent);//the blockcontent array is written into the card block
         //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
         
         //The 'PICC_DumpToSerial' method 'dumps' the entire MIFARE data block into the serial monitor. Very useful while programming a sketch with the RFID reader...
         //Notes:
         //(1) MIFARE cards conceal key A in all trailer blocks, and shows 0x00 instead of 0xFF. This is a secutiry feature. Key B appears to be public by default.
         //(2) The card needs to be on the reader for the entire duration of the dump. If it is removed prematurely, the dump interrupts and an error message will appear.
         //(3) The dump takes longer than the time alloted for interaction per pairing between reader and card, i.e. the readBlock function below will produce a timeout if
         //    the dump is used.
         
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));//uncomment this if you want to see the entire 1k memory with the block written into it.
         /*
         readBlock(block, readbackblock);//read the block back
         Serial.print("read block: ");
         for (int j=0 ; j<16 ; j++)//print the block contents
         {
           Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
         }
         Serial.println("");
         */
       
  int i;
  //Serial.print("uid:");
  for(i=0;i<mfrc522.uid.size;i++)
  {
    //Serial.print(mfrc522.uid.uidByte[i],HEX);
  }
  //Serial.println();
}
