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

### 4. Make a variable for determining the previous mode so we can know if we just transitioned
- New code lines: (this goes at the top of the program)
  - `bool prevSetTimerMode = true;`
- New code lines: (these go right after the line buttonStateMachine(); in loop)
  - `prevSetTimerMode = setTimerMode;`
  - `Serial.print("1.) prevSetTimerMode: ");`
  - `Serial.println(prevSetTimerMode);`
  - `Serial.print("2.) setTimerMode: ");`
  - `Serial.println(setTimerMode);`
- Comment out this line:
  - `Serial.println(timerCountDown);`
- (Upload, watch serial monitor, click button, stop autoscroll and look back at the clicks)
- Notice how the prevSetTimerMode is always the same as setTimerMode
- This is not the behavior we want, we want it so that prevSetTimerMode is different to setTimerMode when transitioning from one mode to another
- We just need to change when prevSetTimerMode gets updated
### 5. Debug prevSetTimerMode
- Move
  - `prevSetTimerMode = setTimerMode;`
- To the part to before the line 
  - `buttonStateMachine();`
- (Upload, watch serial monitor, click button, stop autoscroll and look back at the clicks)
- It works the way we want, now we can use this to time exactly when we transition between modes
### 6. Make the built-in LED always start the same after transitioning between modes
- Edit this line to make the LED blink slower so we can see the effect better
  - `long blinkDelay = 250;`
- To
  - `long blinkDelay = 1000;`
- New code lines:
- `if(prevSetTimerMode == 1 && setTimerMode == 0)`
- `{Serial.println("Was in 'set timer mode' now in 'count down mode'");`
- `blinkSwitchState=1;}`
- Comment out these lines:
  - `Serial.print("1.) prevSetTimerMode: ");`
  - `Serial.println(prevSetTimerMode);`
  - `Serial.print("2.) setTimerMode: ");`
  - `Serial.println(setTimerMode);`
- (Upload, watch serial monitor, click button, watch 3 LEDs, built-in LED)
- The built-in LED and the 3 counting LEDs line up fairly close now, and most importantly start blinking the same way every time
- There's still the issue that the LED will either be on or off depending on or off in "set timer mode" depending on when we stop it in "count down mode"
### 7. Make the built-in LED in "set timer mode" always the same
- New code lines:
digitalWrite(13, LOW);

### 8. Not working, try syncing timercountdown with LED state machine
long countDownDelay = 5000;

 



