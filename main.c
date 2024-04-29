// Lab 7
// Part 3
int buttonState = 0;
const int buttonPin = 4;  // the number of the pushbutton pin

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <SoftwareSerial.h>
SoftwareSerial BTserial(3, 2);  // RX on Arduino | TX on Arduino
// Connect the HC-06 TXD to the Arduino RX on pin 2.
// Connect the HC-06 RXD to the Arduino TX on pin 3 through a voltage divider as shown in the cct diagram.

unsigned long lastMessageTime = 0;
const unsigned long messageInterval = 500;  // .5 seconds interval

void setup() {
  // setup button
  pinMode(buttonPin, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // setup serial
  Serial.begin(9600);

  // HC-06 default serial speed is 9600
  BTserial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();  // current time

  // Check if it's been enough time since the last message was sent
  if (currentTime - lastMessageTime >= messageInterval) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      BTserial.write("Message Triggered By Button\n");
      lastMessageTime = currentTime;  // Update the last message time
    }
  }

  // Keep reading from HC-06 and send to Arduino Serial Monitor and LCD
  if (BTserial.available()) {
    int incomingByte = BTserial.read();
    if (isAscii(incomingByte) && incomingByte != '\n' && incomingByte != '\0' && incomingByte != '\r' && incomingByte != '\t') {  // make sure that it's a valid character
      Serial.write(incomingByte);
      lcd.print((char)incomingByte);
    }
  }
}
