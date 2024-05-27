//Transmitter
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A5 // Arduino pin connected to VRX pin


#define BTN_BTM_LEFT  0

RF24 radio(7, 8); // CE, CSN
const byte address[10] = "FATHOMADD";

int rawXValue = 0; // To store value of the X axis
int rawYValue = 0; // To store value of the Y axis
const char txtLeft[] = "LEFT";
const char txtRight[] = "RIGHT";
const char txtBack[] = "BWD";
const char txtFront[] = "FWD";
const char ytxtCenter[] = "CTNY";
const char xtxtCenter[] = "CTNX";
const char txtKill[] = "KILL";

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  pinMode(BTN_BTM_LEFT, INPUT_PULLUP);
}

void loop()
{
  rawXValue = analogRead(VRY_PIN);
  rawYValue = analogRead(VRX_PIN);
  
  int xValue = map(rawXValue, 0, 1023, -100, 100); // Maps the raw analog input value to a range of -100 to 100
  int yValue = map(rawYValue, 0, 1023, -100, 100); // Maps the raw analog input value to a range of -100 to 100


  byte Status_BTN_BTM_LEFT = digitalRead(BTN_BTM_LEFT);
  if(xValue >= 10){
    radio.write(&txtLeft, sizeof(txtLeft));
  }
  if(xValue <= -10){
    radio.write(&txtRight, sizeof(txtRight));
  }
  if(yValue >= 10){
    radio.write(&txtBack, sizeof(txtBack));
  }
  if(yValue <= -10 ){
    radio.write(&txtFront, sizeof(txtFront));
  } 
  if(yValue >= -10 && yValue <= 10){
    radio.write(&ytxtCenter, sizeof(ytxtCenter));
  }
  if(xValue >= -10 && xValue <= 10){
    radio.write(&xtxtCenter, sizeof(xtxtCenter));
  }
  if (Status_BTN_BTM_LEFT == LOW) {
    radio.write(&txtKill, sizeof(txtKill));
  }
  
}
