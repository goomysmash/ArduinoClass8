int mapPotentiometer = 0; //integer to make it so we don't have to write out map(0,1,2,3,4) every time
int potInput = 0; //variable for holding the value of analogRead(A5)

bool setTimerMode = true; //boolean for setting whether we're in "set timer mode" or "countdown mode"
int timerCountDown = 0; //variable for counting down during the "countdown mode"
long countDownTimerStart = 0; //variable for the timer for "countdown mode"

bool prevSetTimerMode = true; //boolean for determine the previous mode we were in so we can tell if we've switched

//copied from Class 4
int buttonSwitchState = 0; //Declare a variable for switching the state for the state machine
long timerStart = 0; //variable for the start of the timer
bool buttonState = true; //declaring the boolean variable buttonState and setting it to true
bool prevButtonState = true; //declaring the boolean variable for the previous button state and setting it to true

//For the blink state machine (from Class 5)
int blinkSwitchState = 0; //for determining which case we are in for our state machine
long blinkStartTime = 0; //for holding the time when the timer starts for blinking the LED
long blinkDelay = 1000; //how long in milliseconds the delay will be between LED transitions

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); //set the Baud rate to 9600hz. You can change this in the bottom right corner of the serial monitor
  pinMode(A3, OUTPUT); //Set pin A3 as an output (this will be the 5V supply)
  pinMode(A4, OUTPUT); //Set pin A4 as the signal (otherwise known as the wiper of the potentiometer)
  pinMode(A5, INPUT); //Set pin A5 as the output (this will be the Ground)
  
  digitalWrite(A3, HIGH); //Set pin A3 to always be HIGH (act as a constant 5V supply essentially)
  digitalWrite(A4, LOW); //Set pin A4 to always be LOW (act as ground essentially)

  //Copied from class 4
  pinMode(5, OUTPUT); //LED 1
  pinMode(8, OUTPUT); //LED 2
  pinMode(11, OUTPUT); //LED 3
  pinMode(4, OUTPUT); //Ground for LED 1
  pinMode(7, OUTPUT); //Ground for LED 2
  pinMode(10, OUTPUT); //Ground for LED 3
  digitalWrite(4, LOW); //Ground for LED 1 gets set low
  digitalWrite(7, LOW); //Ground for LED 2 gets set low
  digitalWrite(10, LOW); //Ground for LED 3 gets set low

  pinMode(3, INPUT_PULLUP); //set pin D3 to be an input with a pullup resistor

  pinMode(13, OUTPUT); //set pin 13 (the built in LED) to be an output

}

void loop() 
{
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(A5)); //print the analogRead value of pin A5 to the serial monitor
  //analog value can go from 0 (0V) up to 1023 (5V)
  potInput = analogRead(A5); //storing the value of the analogRead in potInput
  potInput = constrain(potInput, 100, 800); //if potInput goes under 100, change to 100, if over 800, change to 800
  mapPotentiometer = map(potInput, 100, 800, 0, 7); // map(input, min observed, max observed, new min, new max)
  //Serial.println(mapPotentiometer); //print a value between 0 and 7 from the range 100-800
  
  //copied (with counter replaced with 'mapPotentiometer') from Class 4
  //Serial.print("mapPotentiometer: "); //so we know what we're seeing in the serial monitor
  //Serial.println(mapPotentiometer, BIN); //Binary representation of the number mapPotentiometer that ranges from 0-7
  
  if(setTimerMode == true) //if you're in set timer mode, allow the analog slider to determine the time with LEDs
  {
    if(bitRead(mapPotentiometer, 0) == 1){digitalWrite(5, HIGH);} //if bit 0 of mapPotentiometer is 1/HIGH, turn on LED 1
    else{digitalWrite(5, LOW);} //otherwise turn LED 1 off
    if(bitRead(mapPotentiometer, 1) == 1){digitalWrite(8, HIGH);} //if bit 1 of mapPotentiometer is 1/HIGH, turn on LED 2
    else{digitalWrite(8, LOW);} //otherwise turn LED 2 off
    if(bitRead(mapPotentiometer, 2) == 1){digitalWrite(11, HIGH);} //if bit 2 of mapPotentiometer is 1/HIGH, turn on LED 3
    else{digitalWrite(11, LOW);} //otherwise turn LED 3 off
  }
  
  else //if you're not in set timer mode
  {
    blinkStateMachine(); //Every time the loop runs this calls the blinkStateMachine() to decide what to do with the LED
    
    if(bitRead(timerCountDown, 0) == 1){digitalWrite(5, HIGH);} //if bit 0 of timerCountDown is 1/HIGH, turn on LED 1
    else{digitalWrite(5, LOW);} //otherwise turn LED 1 off
    if(bitRead(timerCountDown, 1) == 1){digitalWrite(8, HIGH);} //if bit 1 of timerCountDown is 1/HIGH, turn on LED 2
    else{digitalWrite(8, LOW);} //otherwise turn LED 2 off
    if(bitRead(timerCountDown, 2) == 1){digitalWrite(11, HIGH);} //if bit 2 of timerCountDown is 1/HIGH, turn on LED 3
    else{digitalWrite(11, LOW);} //otherwise turn LED 3 off
    
    if((millis()-countDownTimerStart)>5000) //if sufficient time has passed
    {
      //Serial.println(timerCountDown); //print the countdown number
      countDownTimerStart = millis(); //reset the timer
      timerCountDown = timerCountDown - 1; //decrement the countdown variable
      if (timerCountDown < 0){timerCountDown=0;} //round timerCountDown to 0 if it goes under 0 so it doesn't keep counting negatives
    }
  }
  prevSetTimerMode = setTimerMode; //update prevSetTimerMode so we know what mode we were in last time vs this time
  
  buttonStateMachine(); //Go to the buttonStateMachine() function

  if(prevSetTimerMode == 1 && setTimerMode == 0) //if the previous state was "set timer mode" and is currently in "count down mode"
  {
    Serial.println("Was in 'set timer mode' now in 'count down mode'");
    buttonSwitchState=0; //Reset the built-in LED blinking animation back to the beginning
    countDownTimerStart = millis(); //reset the timer for "count down mode"
  }
//  Serial.print("1.) prevSetTimerMode: "); //So in the serial monitor we know what we're looking at
//  Serial.println(prevSetTimerMode); //print a 1 if the previous mode was "set timer mode" and 0 if it was "count down mode"
//  Serial.print("2.) setTimerMode: "); //So in the serial monitor we know what we're looking at
//  Serial.println(setTimerMode); //print a 1 if the current mode is "set timer mode" and 0 if its "count down mode"
}

void buttonStateMachine() //Function that contains our state machine (can call this function whenever)
{
  switch(buttonSwitchState) //switch statement (how our state machine decides to go to different states)
  {
    //case 0: Wait for falling edge
    case 0: //if buttonSwitchState is 0, do this case
      //Serial.println("case 0: Wait for falling edge");
      prevButtonState = buttonState; //update the prevButtonState
      buttonState = digitalRead(3); //read pin 3 then store the value in buttonState
      
      if(prevButtonState == 1 && buttonState == 0){buttonSwitchState = 1;} //if a falling edge was detected, go to case 1
       
      break; //Exit from the buttonStateMachine() function
      
    //case 1: Falling edge detected
    case 1: //if buttonSwitchState is 1, do this case
      //Serial.println("case 1: Start the timer");
      timerStart = millis(); //store whatever time it is in this moment in the variable timerStart
  
      buttonSwitchState = 2; //go to case 2 (no if statement needed cause it always does this)
      
      break; //Exit from the buttonStateMachine() function
      
    //case 2: Not sure if debounced yet 
    case 2: //if buttonSwitchState is 2, do this case
      //Serial.println("case 2: Read the button state");
      prevButtonState = buttonState; //update the prevButtonState
      buttonState = digitalRead(3); //read pin 3 then store the value in buttonState
  
      if (prevButtonState==0 && buttonState==1){buttonSwitchState=0;} //if there was a rising edge, go to case 0
      if (millis() - timerStart > 5){buttonSwitchState = 3;} //if sufficient time (5ms) has passed, go to case 3
      
      break; //Exit from the buttonStateMachine() function
      
    //case 3: 5ms has passed, successfully debounced
    case 3: //if buttonSwitchState is 3, do this case
      //Serial.println("successful press"); //success message

      setTimerMode = !setTimerMode; //Switch the mode from what it was to the other mode
      //Serial.println(setTimerMode); //Print a 1 if you're in setTimerMode and 0 if not
      
      timerCountDown = mapPotentiometer; //if the button was pressed set whatever the current mapPotentiometer value to the timerCountDown
      
      buttonSwitchState = 0; //next time we enter the switch statement, go to case 0
      
      break; //Exit from the buttonStateMachine() function
  }
}

void blinkStateMachine() //Our state machine function
{
  switch(blinkSwitchState) //The part that does the work, the switch statement
  {
    case 0: //Off and waiting
      //Do nothing
      if((millis()-blinkStartTime)>blinkDelay){blinkSwitchState=1;}
      break;
    case 1: //Off and transitioning to On
      //Start timer
      //Turn LED on
      blinkStartTime = millis(); //Start the timer
      digitalWrite(13, HIGH); //Turn the built in LED on
      blinkSwitchState = 2; //go to case 2
      break;
    case 2: //On and waiting
      //Do nothing
      if((millis()-blinkStartTime)>blinkDelay){blinkSwitchState=3;}
      break;
    case 3: //On and transitioning to Off
      //Start timer
      //Turn LED off
      blinkStartTime = millis(); //Start the timer
      digitalWrite(13, LOW); //Turn the LED off
      blinkSwitchState = 0; //go to case 0
      break;
  }
}
