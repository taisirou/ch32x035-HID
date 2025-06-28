//====================================================================
//　参考・引用
//  電車でGO!コントローラでTSマスコンをエミュレートしてBVEで遊ぶ。
//  7M4MON
//  https://github.com/KeKe115/Densya_de_go
//  
// TSマスコンのコマンドとBVEの内部処理の解説
// https://scrapbox.io/p4ken/%E5%85%A5%E5%8A%9B%E3%83%87%E3%83%90%E3%82%A4%E3%82%B9%E3%83%97%E3%83%A9%E3%82%B0%E3%82%A4%E3%83%B3%E5%88%B6%E4%BD%9C%E8%AC%9B%E5%BA%A7
//====================================================================
/*
ブレーキ9  TSB20
 ブレーキ8  TSB30
 ブレーキ7  TSB40
 ブレーキ6  TSB99
 ブレーキ5  TSA05
 ブレーキ4  TSA15
 ブレーキ3  TSA25
 ブレーキ2  TSA35
 ブレーキ1  TSA45
 ノッチ切 TSA50
 ノッチ1 TSA55
 ノッチ2 TSA65
 ノッチ3 TSA75
 ノッチ4 TSA85
 ノッチ5 TSA95
 ノッチ6 TSB60
 ノッチ7 TSB70
 ノッチ8 TSB80
 レバーサ前  TSG99
 レバーサ切  TSG50
 レバーサ後  TSG00
 ボタンS押し TSK99
 ボタンS離し TSK00
 ボタンA押し TSX99
 ボタンA離し TSX00
 ボタンB押し TSY99
 ボタンB離し TSY00
 ボタンC押し TSZ99
 ボタンC離し TSZ00
*/
#include "src\\userUsbKB\\usbdKBMS.h"
uint8_t  Buffer[ 8 ];
bool buttonPB0PressPrev = false;
bool buttonPB3PressPrev = false;
bool buttonPB4PressPrev = 0;

//ブレーキ
const int BR0 = PA3;  //151
int BR0sw = 0;
const int BR1 = PA4;  //155
int BR1sw = 0;
const int BR2 = PA5;  //156
int BR2sw = 0;
const int BR3 = PA6;  //157
int BR3sw = 0;
//マスコン
const int MC0 = PC0;  //20_1
int MC0sw = 0;
const int MC1 = PC3;  //2
int MC1sw = 0;
const int MC2 = PA0;  //3
int MC2sw = 0;
const int MC3 = PA1;  //7
int MC3sw = 0;

const int REBF = PA2;
int REBFsw = 0; //5
const int REBR = PA7;
int REBRsw = 0; //4

int NOWREB = 0;
int BEFORREB = 0;

int ON = LOW;
int OFF = HIGH;

void setup() {
  Serial.begin(19200);
  delay(500);
  /* Usb Init */
  USBFS_RCC_Init();
  USBFS_Device_Init( ENABLE , PWR_VDD_SupplyVoltage( ));
  USB_Sleep_Wakeup_CFG( );

  pinMode(PC0, INPUT_PULLUP);
  pinMode(PC3, INPUT_PULLUP);
  pinMode(PA0, INPUT_PULLUP);
  pinMode(PA1, INPUT_PULLUP);
  pinMode(PA2, INPUT_PULLUP);
  pinMode(PA3, INPUT_PULLUP);
  pinMode(PA4, INPUT_PULLUP);
  pinMode(PA5, INPUT_PULLUP);
  pinMode(PA6, INPUT_PULLUP);
  pinMode(PA7, INPUT_PULLUP);
  pinMode(PB0, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB8, INPUT_PULLUP);
  pinMode(PB9, INPUT_PULLUP);
  pinMode(PB12, INPUT_PULLUP);
  // pinMode(PB10, INPUT_PULLUP);
  // pinMode(PB11, INPUT_PULLUP);
  // pinMode(PC14, INPUT_PULLUP);
  // pinMode(PC15, INPUT_PULLUP);
  pinMode(PC18, INPUT_PULLUP);
  pinMode(PC19, INPUT_PULLUP);
}

void loop() {
  BR0sw = digitalRead(BR0);
  BR1sw = digitalRead(BR1);
  BR2sw = digitalRead(BR2);
  BR3sw = digitalRead(BR3);
  MC0sw = digitalRead(MC0);
  MC1sw = digitalRead(MC1);
  MC2sw = digitalRead(MC2);
  MC3sw = digitalRead(MC3);

  REBFsw = digitalRead(REBF);
  REBRsw = digitalRead(REBR);

  //レバーサ
  if (REBFsw == OFF && REBRsw == ON) {
    NOWREB = 1;
  }
  if (REBFsw == OFF && REBRsw == OFF) {
    NOWREB = 0;
  }
  if (REBFsw == ON && REBRsw == OFF) {
    NOWREB = 2;
  }
  if (NOWREB != BEFORREB) {
    if (NOWREB == 0) {
      Serial.print("TSG50\r");
    }
    if (NOWREB == 1) {
      Serial.print("TSG99\r");
    }
    if (NOWREB == 2) {
      Serial.print("TSG00\r");
    }
  }
  BEFORREB = NOWREB;

  if (MC0sw == OFF  &&  BR0sw == OFF && BR1sw == ON && BR2sw == ON  && BR3sw == ON) {
    Serial.print("TSA45\r");
  }
  if (MC0sw == OFF  &&  BR0sw == OFF && BR1sw == ON && BR2sw == ON && BR3sw == OFF) {
    Serial.print("TSA35\r");
  }
  if (MC0sw == OFF  &&  BR0sw == OFF && BR1sw == ON && BR2sw == OFF && BR3sw == OFF) {
    Serial.print("TSA25\r");
  }
  if (MC0sw == OFF  &&  BR0sw == OFF && BR1sw == OFF && BR2sw == OFF && BR3sw == ON ) {
    Serial.print("TSA15\r");
  }
  if (MC0sw == OFF  &&  BR0sw == OFF && BR1sw == OFF && BR2sw == ON && BR3sw == OFF ) {
    Serial.print("TSA05\r");
  }
  if (MC0sw == OFF  &&  BR0sw == ON && BR1sw == ON && BR2sw == OFF && BR3sw == ON ) {
    Serial.print("TSB20\r");
  }
  if (MC0sw == OFF  &&  BR0sw == OFF && BR1sw == ON && BR2sw == OFF && BR3sw == ON) {
    Serial.print("TSA50\r");
  }
  if (BR3sw == ON &&  MC0sw == ON && MC1sw == ON && MC2sw == ON && MC3sw == ON) {
    Serial.print("TSB80\r");
  }
  if (BR3sw == ON &&  MC0sw == ON && MC1sw == ON && MC2sw == ON && MC3sw == OFF) {
    Serial.print("TSA75\r");
  }
  if (BR3sw == ON &&  MC0sw == ON && MC1sw == OFF && MC2sw == OFF && MC3sw == OFF) {
    Serial.print("TSA55\r");
  }
  if (BR3sw == ON &&  MC0sw == ON && MC1sw == ON && MC2sw == OFF && MC3sw == OFF) {
    Serial.print("TSA65\r");
  }
  bool buttonPB0Press = !digitalRead(PB0);
  if (buttonPB0PressPrev != buttonPB0Press) {
    buttonPB0PressPrev = buttonPB0Press;
    if (buttonPB0Press ) {
      Buffer[2] = 0x08; //"e"
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      delay(20);
      memset(Buffer, 0, sizeof(Buffer));
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      Serial.println("Send e");
      delay(20);
    }
  }
  bool buttonPB3Press = !digitalRead(PB3);
  if (buttonPB3PressPrev != buttonPB3Press) {
    buttonPB3PressPrev = buttonPB3Press;
    if (buttonPB3Press == LOW ) {
      Buffer[2] = 0x15; //"R"
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      memset(Buffer, 0, sizeof(Buffer));
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      Serial.println("Send r");
      delay(20);
      Buffer[2] = 0x0c; //"I"
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      memset(Buffer, 0, sizeof(Buffer));
      delay(50);
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      Serial.println("Send i");
    }
  }
  bool buttonPB4Press = !digitalRead(PB4);
  if (buttonPB4PressPrev != buttonPB4Press) {
    buttonPB4PressPrev = buttonPB4Press;
    if (buttonPB4Press ) {
      Buffer[2] = 0x04; //"a"
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      delay(20);
      memset(Buffer, 0, sizeof(Buffer));
      USBFS_Endp_DataUp( DEF_UEP1, Buffer, sizeof( Buffer ), DEF_UEP_CPY_LOAD );
      Serial.println("Send a");
      delay(20);
    }
  }
}
