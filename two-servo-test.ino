// two-servo-test.ino
// for Let's Code Blacksburg! www.letscodeblacksburg.org 2015-04-28
// By Thomas "Tweeks" Tweeks, tweeks-homework(at)theweeks.org
//
// This is the simple code for the continuous rotation servo wheels for our bot

// this include is what loads the code to talk to the servos on PWN based digital I/O pins
#include <Servo.h>
Servo servoL;  // creates servo object to control a servo
Servo servoR;  // creates servo object to control a servo

// Servo Tuning
// These values are just starting points. Every servo is a little different and so you may need to fine tune each.
// Don't forget that depending n how you have your servos mounted, a value can go "forward" on one servo but 
// "backward" on the other.
// You may need to tune the forward rev values to go in a straight line or turn.
// You will probably need to tune the stopL and stopR values to get to a dead stop on each servo
const int forwardL = 135;   // 135 is Clockwise, full speed (around 90 is stopped)
const int forwardR = 45;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int reverseL = 45;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int reverseR = 135;   // 135 is Clockwise, full speed (around 90 is stopped)

const int stopL = 85;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)
const int stopR = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)

const int turnDelay = 500;  // Delay for turnL() turnR() to achive close to 90 degrees (at full throttle)



void setup() {
  servoR.attach(5);  // attaches the left servo on pin 5
  servoL.attach(6);  // attaches the right servo on pin 6
  turnL();
  turnR();
  delay(2000);       // 2 second delay
  
  // ** initialize serial communication:
  Serial.begin(9600);

}


// ***********************************************************
// ******* MAIN LOOP *****************************************
// ***********************************************************
// Runs forever...
void loop() {
  // put your main code here, to run repeatedly:

  forward();    // move forward
  delay(500);   // got for 500ms (1/2 second)
  turnR();      // turn right
  forward();    //move forward
  delay(1000);  // go for 1,000 ms (1 second)
  stopall();    // stops
}


////////////// Everything below this is program functoions called from the main loop

// ***********************************************************
// ***** turnR() *********************************************
// ***********************************************************
void turnR(){
    // turns right approx 90 degrees (may need to be tuned)
    Serial.println("turnR()");
    servoL.write(forwardL);           // rotate L servo forward
    servoR.write(reverseR);           // rotate R servo reverse (which turns us right)
    delay(turnDelay);                 // wait for full turn
    servoR.write(stopR);              // stop
    servoL.write(stopL);              // stop 
}


// ***********************************************************
// ***** turnL() *********************************************
// ***********************************************************
void turnL(){
    // turns left approx 90 degrees (may need to be tuned)
  Serial.println("turnL()");
    servoL.write(forwardR);           // rotate R servo forward
    servoR.write(reverseL);           // rotate L servo reverse (which turns us left)
    delay(turnDelay);                       // wait for full turn
    servoR.write(stopR);              // stop
    servoL.write(stopL);              // stop
}


// ***********************************************************
// ***** forward() *********************************************
// ***********************************************************
void forward(){
    // goes forward, forever
    Serial.println("forward()");
    servoL.write(reverseR);           // rotate R servo forward
    servoR.write(reverseL);           // rotate L servo forward
}

// ***********************************************************
// ***** backward() *********************************************
// ***********************************************************
void backward(){
    // goes backwards, forever
    Serial.println("backward()");
    servoL.write(forwardR);           // rotate R servo forward
    servoR.write(forwardL);           // rotate L servo forward
}

// ***********************************************************
// ***** stopall() *********************************************
// ***********************************************************
void stopall(){
    // stops
    Serial.println("stopall()");
    servoR.write(stopR);              // stop
    servoL.write(stopL);              // stop
}
