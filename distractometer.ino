 // Looking at the display like this: 8.8.8.8. pin 1 is on the lower row, starting from the left.
 // Pin 12 is the top row, upper left pin.

 // Pinout:
 // 1: Segment E
 // 2: Segment D
 // 3: Segment DP
 // 4: Segment C
 // 5: Segment G
 // 6: Digit 4
 // 7: Segment B
 // 8: Digit 3
 // 9: Digit 2
 // 10: Segment F
 // 11: Segment A
 // 12: Digit 1

#include "SevSeg.h"

//Create an instance of the object.
SevSeg myDisplay;

//Create global variables
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 13;          // connect Red LED to pin 11 (PWM pin)
bool last_state;
bool is_on = false;
int distractions = 0;
char tempString[10]; //Used for sprintf

void setup()
{
  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode

  //Declare what pins are connected to the digits
  int digit1 = 2; //Pin 12 on my 4 digit display
  int digit2 = 3; //Pin 9 on my 4 digit display
  int digit3 = 4; //Pin 8 on my 4 digit display
  int digit4 = 5; //Pin 6 on my 4 digit display

  //Declare what pins are connected to the segments
  int segA = 6; //Pin 11 on my 4 digit display
  int segB = 7; //Pin 7 on my 4 digit display
  int segC = 8; //Pin 4 on my 4 digit display
  int segD = 9; //Pin 2 on my 4 digit display
  int segE = 10; //Pin 1 on my 4 digit display
  int segF = 11; //Pin 10 on my 4 digit display
  int segG = 12; //Pin 5 on my 4 digit display
  int segDP= 13; //Pin 3 on my 4 digit display

  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);

  myDisplay.SetBrightness(100); //Set the display to 100% brightness level

  Serial.begin(9600);

}

void loop()
{
  // distractions = 1234;
  sprintf(tempString, "%4d", distractions); //Convert distractions into a string that is right adjusted
  myDisplay.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)

  photocellReading = analogRead(photocellPin);

  last_state = is_on;
  if (photocellReading > 200){
    is_on = true;
  }
  else if(photocellReading > 100){
    is_on = false;
  }

  if (last_state && !is_on){
    distractions++;
    Serial.print("Distractions = ");
    Serial.println(distractions);     // the raw analog reading
  }

  // delay(100);

}
