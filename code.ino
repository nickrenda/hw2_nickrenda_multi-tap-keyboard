/*
10-switch single/double/triple tap keyboard
 by Nick Renda 
 last modififed 9/11/2016

 Adapted from the Arduino OneButton Library at https://github.com/mathertel/OneButton
 The circuit:
 * pushbuttons connected to D0-D9 and 3V3 on a Redbear duo
 
 */

// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

// No. of buttons on the keyboard
const int numButtons = 10;

// Pin Assignments
const int buttonPin[numButtons] = {D8, D9, D0, D1, D2, D3, D4, D5, D6, D7};

// Initializing State and Time arrays
int buttonState[numButtons] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int lastButtonState[numButtons] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int clickState[numButtons] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
long clickTime[numButtons] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Delay, Hold, and Timeout values
int debounceTime = 20; // time in ms to delay between loops to account for debounce
int clickTimeout = 400; // time in ms to wait between successive clicks of same button before timing out
int holdTime = 1000; // time in ms for before a held key is logged
int bkspHold = 200; // time between successive backspaces when button is held 

// Keyboard Output Assignments
char keyPress1[10] = "ASDFGHJKL"; // single tap keys
char keyPress2[10] = "QWERTYUIO"; // double tap keys
char keyPress3[10] = "ZXCVBNM P"; // triple tap keys
                                                              
void setup() {

  // Set Pin Modes
  for (int i=0; i<numButtons; i++)
  {
     pinMode(buttonPin[i], INPUT_PULLDOWN);
  }
  
  Serial.begin(9600);  
}

void loop() {

  for (int i=0; i<(numButtons-1); i++) { // Implement finite state machine for key clicks
    
  buttonState[i] = digitalRead(buttonPin[i]); // Read value of each switch and store

    
    if (clickState[i] == 0) { // State 0: Waiting for first button click
      
      if (buttonState[i] == HIGH) {
        clickState[i] = 1; // button was clicked, move to State 1
        clickTime[i] = millis(); // start timer
      }
      
    } else if (clickState[i] == 1) { // State 1: Button clicked for FIRST time, waiting for release or timeout
      
      if (buttonState[i] == LOW) {
        clickState[i] = 2; // button was released , move to State 2
        
      } else if ( (buttonState[i] == HIGH) && (millis() - clickTime[i] > holdTime)) {
        clickState[i] = 7; // button has been held for more than holdTime. move to State 7
      }
      
    } else if (clickState[i] == 2) { // State 2: Button released from first click, wait for second click or timeout

      if (millis() - clickTime[i] > clickTimeout) {
        Serial.print(keyPress1[i]); // First click timeout, print single click character
        clickState[i] = 0; // restart to State 0
        
      } else if (buttonState[i] == HIGH) {
        clickState[i] = 3; // button has been clicked for second time, move to State 3
        clickTime[i] = millis(); // start timer
      }

    } else if (clickState[i] == 3) { // State 3: Button clicked for SECOND time, waiting for release or timeout
      
      if (buttonState[i] == LOW) {
        clickState[i] = 4; // button was released, move to State 4
        
      } else if ( (buttonState[i] == HIGH) && (millis() - clickTime[i] > holdTime)) {
        clickState[i] = 8; // button has been held for more than holdTime, move to State 8
      }


    } else if (clickState[i] == 4) { // State 4: Button released from second click, wait for third click or timeout

      if (millis() - clickTime[i] > clickTimeout) {
        Serial.print(keyPress2[i]); // Second click timeout, print double click character
        clickState[i] = 0; // restart to State 0
        
      } else if (buttonState[i] == HIGH) {
        clickState[i] = 5; // button has been clicked for third time, move to State 5
        clickTime[i] = millis(); // start timer
      }

   } else if (clickState[i] == 5) { // State 5: Button clicked for THIRD time, waiting for release or timeout
      
      if (buttonState[i] == LOW) {
        clickState[i] = 6; // button was released, move to State 6
        
      } else if ( (buttonState[i] == HIGH) && (millis() - clickTime[i] > holdTime)) {
        clickState[i] = 9; // button has been held for more than holdTime, move to State 9
      }
      
   } else if (clickState[i] == 6) { // State 6: Button released from THIRD click, print character

        Serial.print(keyPress3[i]); // 3rd click timeout, print triple click character
        clickState[i] = 0; // restart to State 0
        
    } else if (clickState[i] == 7) { // State 7: Button has been held for more than holdTime
      
        Serial.print(keyPress1[i]); // 1st click timeout, print single click character
        clickState[i] = 0; // restart to State 0

    } else if (clickState[i] == 8) { // State 8: Button has been held for more than holdTime
      
        Serial.print(keyPress2[i]); // 1st click timeout, print double click character
        clickState[i] = 0; // restart to State 0

 } else if (clickState[i] == 9) { // State 9: Button has been held for more than holdTime
  
        Serial.print(keyPress3[i]); // 1st click timeout, print triple click character
        clickState[i] = 0; // restart to State 0
    }

  }


  // Separate code for backspace, which only needs to look for single clicks.
  
buttonState[9] = digitalRead(buttonPin[9]); // read value of backspace key

  if (buttonState[9] == HIGH && (millis()-clickTime[9] > bkspHold)) { // Check button is pressed and enough time has passed
    clickTime[9] = millis(); // start timer
    Serial.write(8); // print a backspace character (only in serial monitors that support this character) 
  }

delay(debounceTime); // delay loop to avoid debounce 
}
