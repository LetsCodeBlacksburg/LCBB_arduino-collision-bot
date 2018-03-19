// 4_two-servos-test.ino
// for Let's Code Blacksburg! www.letscodeblacksburg.org 2018-03-19
// By Thomas "Tweeks" Tweeks, tweeks-homework(at)theweeks.org
//
// This is the simple code for the continuous rotation servo wheels for our bot.By default, the 
// main loop moves the bot forward 12 inches, turns right (90 degrees), again goes forward 12
// inches, turns right, and then waits 5 seconds.. then loops over and over (moving in a square).
// If your bot does not move in a perfect square, or come to a complete stop, you may need to 
// tune your stopR(), stopL() or tune your other MOTOR DEFAULTS constants below.

// This include is what loads the code to talk to the servos using PWM based digital I/O pins
#include <Servo.h>
Servo servoL;  // this creates the servo object to control the bot's LEFT servo
Servo servoR;  // this creates the servo object to control the bot's RIGHT servo

// Servo Tuning
// These values are just starting points. Every servo is a little different and so you may need to fine tune each.
//     NOTE: Don't forget that depending on how you have your servos mounted, a value can go "forward" 
//           on one servo but "backward" on the other.
//
// MOTOR DEFAULTS: You will probably need to fine tune the stopL and stopR values to get to a dead stop on each servo
const int stopL = 89;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)
const int stopR = 89;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)
// You may need to tune the forward rev values to go in a straight line or turn reliably.
const int forwardL = 135;   // 135 is Clockwise, full speed (around 90 is stopped)
const int forwardR = 45;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int reverseL = 45;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int reverseR = 135;   // 135 is Clockwise, full speed (around 90 is stopped)
// These distance and angle multipliers must be scaled along with servo supply voltage (e.g. 5v, 6v 9v, etc)
const int inchesMult = 125;  // Multiplier to convert inches into miliseconds of wheel movement
const int angleMult = 7;     // Tile/Carpet multiplier to aplify/dampen turn angle (for tile=6, carpet=7)
const int backDelay = 200;  // Delay for slight back up before turning out of an obstacle

void setup() {
  servoR.attach(5);  // attaches the left servo on pin 5
  servoL.attach(6);  // attaches the right servo on pin 6
  turnL(20);
  turnR(20);
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

  forward(12);    // move forward
  turnR(90);      // turn right
  forward(12);    // move forward
  turnR(90);      // turn right
  delay(5000);    // wait 5 seconds
}

////////////// Everything below this is program functoions called from the main loop

// ***********************************************************
// ***** turnR() *********************************************
// ***********************************************************
void turnR(int angle){
    Serial.println("turnR()");
    servoL.write(forwardL);           // rotate L servo forward
    servoR.write(reverseR);           // rotate R servo reverse (which turns us right)
    delay(angle*angleMult);                  // delay this amount to acheive angle
    stopAll();
}

// ***********************************************************
// ***** turnL() *********************************************
// ***********************************************************
void turnL(int angle){
    Serial.println("turnL()");
    servoL.write(forwardR);           // rotate R servo forward
    servoR.write(reverseL);           // rotate L servo reverse (which turns us left)
    delay(angle*angleMult);                  // delay this amount to acheive angle
    stopAll();
}

// ***********************************************************
// ***** forward() *********************************************
// ***********************************************************
void forward(int inches){
    Serial.println("forward()");
    servoL.write(reverseR);           // rotate R servo forward (weird, I know)
    servoR.write(reverseL);           // rotate L servo forward
    delay( (inches * inchesMult));           // roughly convert inches to miliseconds of wheel rotations
    stopAll();
}

// ***********************************************************
// ***** backward() *********************************************
// ***********************************************************
void backward(int inches){
    Serial.println("backward()");
    servoL.write(forwardR);           // rotate R servo forward (weird, I know)
    servoR.write(forwardL);           // rotate L servo forward
    delay( (inches * inchesMult));    // roughly convert inches to miliseconds of wheel rotations
    stopAll();
}

// ***********************************************************
// ***** stopAll() *********************************************
// ***********************************************************
void stopAll(){
    // stops
    Serial.println("stopall()");
    servoR.write(stopR);              // stop
    servoL.write(stopL);              // stop
}
