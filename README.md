## Class 8: Adding more functionality to our kitchen timer
### 1. Import Class 7 (file 9)

### 2. Copy parts from Class 5 (file 4) relating to the blinking LED state machine
- Copy these lines to the top of the program
  - `int blinkSwitchState = 0;`
  - `long blinkStartTime = 0;`
  - `long blinkDelay = 250;`
- Copy this line to the setup funciton
  - `pinMode(13, OUTPUT);`
- Copy this line into the loop function
  - `blinkStateMachine();`
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
- (Upload, push button, slide potentiometer, watch built-in LED)
- Notice how the built-in LED acts as a second hand for our clock
- But also it never stops blinking. Let's make it so it only blinks in "count down mode"

### 3. Only flash the built-in LED in "count down mode"
- Move this line to inside the 'else' statement related to "count down mode" or "not set timer mode"
  - `blinkStateMachine();`
- (Upload, push button, move slider, watch LED)
- Notice how the LED stops blinking in "set timer mode", this is what we want
- However it will either be off or on to start with depending on when we press it
- We want it to consistently start the same way each time

### 4.











 



