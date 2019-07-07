## Class 8: Adding more functionality to our kitchen timer
### 1. Import Class 7 (file 9)

### 2. Copy parts from Class 5 (file 4) relating to the blinking LED state machine
- Copy these lines to the top of the program
  - `int blinkSwitchState = 0;`
  - `long blinkStartTime = 0;`
  - `long blinkDelay = 250;`
- Copy this line to the setup funciton
  - `pinMode(13, OUTPUT);`
- Copy the blink state machine function to the end of the program
  - `void blinkStateMachine(){`
  - `switch(blinkSwitchState){`
  - `case 0:`
  - `if((millis()-blinkStartTime)>blinkDelay){blinkSwitchState=1;}`
  - `break;`
  - `case 1:`
  - `blinkStartTime = millis();`
  - `digitalWrite(13, HIGH);`
  - `blinkSwitchState = 2;`
  - `break;`
  - `case 2:`
  - `if((millis()-blinkStartTime)>blinkDelay){blinkSwitchState=3;}`
  - `break;`
  - `case 3:`
  - `blinkStartTime = millis();`
  - `digitalWrite(13, LOW);`
  - `blinkSwitchState = 0;`
  - `break;}}`

### 3. 













 



