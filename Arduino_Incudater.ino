#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 26 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 25 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

const int OxyMachine = 18;
int btnOxy1 = 19;
int btnOxy2 = 20;
int btnOxyVal1 = 0;
int btnOxyVal2 = 0;

int btnP1 = 31;
int btnP2 = 33;

int debounceDelay = 300;
int btnValP1 = 0;
int btnValP2 = 0;

String love, happy, sad, disappoint, anger;
String loveAvg, happyAvg, sadAvg, disappointAvg, angerAvg;
String loveHappy, negEmotions, oxyVal;
int missingPosVal = 0;

int P1_Love = 0;
int P1_Happy = 0;
int P1_Sad = 0;
int P1_Disappoint = 0;
int P1_Anger = 0;

int P2_Love = 0;
int P2_Happy = 0;
int P2_Sad = 0;
int P2_Disappoint = 0;
int P2_Anger = 0;

int P1_Love_outVal = 0;
int P1_Happy_outVal = 0;
int P1_Sad_outVal = 0;
int P1_Disappoint_outVal = 0;
int P1_Anger_outVal = 0;

int P2_Love_outVal = 0;
int P2_Happy_outVal = 0;
int P2_Sad_outVal = 0;
int P2_Disappoint_outVal = 0;
int P2_Anger_outVal = 0;

void setup() {

  Serial.begin(9600);

  // P1 potentiometers
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  // P2 potentiometers
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);

  // P1 lights
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  // P2 lights
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(btnP1, INPUT);
  pinMode(btnP2, INPUT);

  mySerial.begin(19200);
  printer.begin();

  loveAvg = ((P1_Love/10.23) + (P2_Love/10.23))/2;
  happyAvg = ((P1_Happy/10.23) + (P2_Happy/10.23))/2;
  sadAvg = ((P1_Sad/10.23) + (P2_Sad/10.23))/2;
  disappointAvg = ((P1_Disappoint/10.23) + (P2_Disappoint/10.23))/2;
  angerAvg = ((P1_Anger/10.23) + (P2_Anger/10.23))/2;

  loveHappy = loveAvg + happyAvg;
  missingPosVal = 200 - loveHappy;
  negEmotions = sadAvg + disappointAvg + angerAvg;

}


void loop() {

  P1_Love = analogRead(A0);
  P1_Happy = analogRead(A1);
  P1_Sad = analogRead(A2);
  P1_Disappoint = analogRead(A3);
  P1_Anger = analogRead(A4);

  P2_Love = analogRead(A5);
  P2_Happy = analogRead(A6);
  P2_Sad = analogRead(A7);
  P2_Disappoint = analogRead(A8);
  P2_Anger = analogRead(A9);

  love = loveAvg + "%";
  happy = happyAvg + "%";
  sad = sadAvg + "%";
  disappoint = disappointAvg + "%";
  anger = angerAvg + "%";
  oxyVal = missingPosVal + negEmotions + "mg";

   // map it to the range of the analog out:
  P1_Love_outVal = map(P1_Love, 0, 1023, 0, 255);
  P1_Happy_outVal = map(P1_Happy, 0, 1023, 0, 255);
  P1_Sad_outVal = map(P1_Sad, 0, 1023, 0, 255);
  P1_Disappoint_outVal = map(P1_Disappoint, 0, 1023, 0, 255);
  P1_Anger_outVal = map(P1_Anger, 0, 1023, 0, 255);

  P2_Love_outVal = map(P2_Love, 0, 1023, 0, 255);
  P2_Happy_outVal = map(P2_Happy, 0, 1023, 0, 255);
  P2_Sad_outVal = map(P2_Sad, 0, 1023, 0, 255);
  P2_Disappoint_outVal = map(P2_Disappoint, 0, 1023, 0, 255);
  P2_Anger_outVal = map(P2_Anger, 0, 1023, 0, 255);
  
  
  // change the analog out value:
  analogWrite(12, P1_Love_outVal);
  analogWrite(11, P1_Happy_outVal);
  analogWrite(10, P1_Sad_outVal);
  analogWrite(9, P1_Disappoint_outVal);
  analogWrite(8, P1_Anger_outVal);
  
  analogWrite(7, P2_Love_outVal);
  analogWrite(6, P2_Happy_outVal);
  analogWrite(5, P2_Sad_outVal);
  analogWrite(4, P2_Disappoint_outVal);
  analogWrite(3, P2_Anger_outVal);

  btnValP1 = digitalRead(btnP1);
  btnValP2 = digitalRead(btnP2);

  if (btnValP1 == HIGH && btnValP2 == HIGH) {
    Serial.write("Button Pressed");
    printer.justify('L');
    printer.setSize('L');
    printer.println(F(" "));
    printer.println(F("Dating\nIncubator"));
    printer.setSize('S');
    printer.println(F("Lab Results"));
    printer.println(F(" "));
    printer.println(F("LAB# 008961           02/05/2021"));
    printer.println(F("Participants: 02         09:19PM"));
    
    printer.println(F(" "));
    printer.println(F(" "));
    
    printer.boldOn();
    printer.underlineOn();
    printer.setSize('M');
    printer.println(F("EMOTIONAL DATA\n---------------------------"));
    printer.underlineOff();
    printer.boldOff();
    
    printer.justify('L');
    printer.setSize('S');
    printer.print("Love             ");
    printer.justify('R');
    printer.print(love); // love value
    printer.print("\n");

    printer.print("Happiness        ");
    printer.justify('R');
    printer.print(happy); // happy value
    printer.print("\n");

    printer.print("Sadness          ");
    printer.justify('R');
    printer.print(sad); // sad value
    printer.print("\n");

    printer.print("Disappointment    ");
    printer.justify('R');
    printer.print(disappoint); // disappoint value
    printer.print("\n");

    printer.print("Anger             ");
    printer.justify('R');
    printer.print(anger); // anger value
    printer.print("\n");

    printer.println(F(" "));
    printer.println(F(" "));
    
    printer.justify('L');
    printer.setSize('S');
    printer.boldOn();
    printer.underlineOn();
    printer.println(F("PRESCRIPTION"));
    printer.underlineOff();
    printer.boldOff();
    printer.print("\n");
    printer.print("Oxytocin                     ");
    printer.justify('R');
    printer.print(oxyVal);
    printer.println(F(" "));
    
    printer.boldOn();
    printer.underlineOn();
    printer.justify('L');
    printer.setSize('S');
    printer.println(F("REASON FOR PRESCRIPTION\n"));
    printer.underlineOff();
    printer.boldOff();
    printer.setSize('L');
    printer.println(F("Falling in\nlove..."));
    
    printer.println(F(" "));
    printer.printBarcode("DATA ROMANTICS", CODE39);
    printer.setBarcodeHeight(100);
    
    printer.println(F(" "));
    printer.println(F(" "));
    printer.println(F(" "));
    delay(1000);
    printer.sleep();
    printer.wake();
    printer.setDefault();
  }

  btnOxyVal1 = digitalRead(btnOxy1);
  btnOxyVal2 = digitalRead(btnOxy2);

  if (btnOxy1 == HIGH && btnOxy2 == HIGH) {
    digitalWrite(OxyMachine, HIGH);
  } else {
    digitalWrite(OxyMachine, LOW);
  }
}
