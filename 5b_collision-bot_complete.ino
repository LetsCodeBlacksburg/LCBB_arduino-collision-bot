// 5b_collision-bot_complete
// This letscodeblacksburg.org project is for building a collision bot (from scratch) using 
// an Arduino Uno/R3 (Atmel based), US-100 ultrasonic "ping" sensor (not the Parallax version),
// two continuous rotation servos, a battery, approx 4"x6" piece of foam board, some milk jug
// caps (for wheels and drag-point), and some hot glue.  Implimenting this code from scratch 
// would take the better part of a weekend. But implimenting it in pieces (servo code, ping
// sensor code, movement code, collision avoidance) using this as a starting place to copy from,
// it is of course much faster.  Feel free to use/reuse that matieral. I publish it copy-left/
// creative commons, with credits listed.
// Thomas "Tweeks" Weeks, tweeks-homework(at)theweeks.org

#include <Servo.h>
Servo servoL;  // this creates the servo object to control the bot's LEFT servo
Servo servoR;  // this creates the servo object to control the bot's RIGHT servo

// This ping-sensor code is set up for using a four pin ping sensor such as
// the US-100 module:
// https://www.bananarobotics.com/shop/US-100-Ultrasonic-Distance-Sensor-Module
// http://www.iseerobot.com/produk-1255-us100-ultrasonic-sensor-for-arduino.html
// NOTE: For this code, + the US-100 module, be sure to remove the serial-data jumper on the
// back so that you get back the raw pulse from the echo pin (and not serial distance data).
//
// CAUTION: Have your code checked, and have the TA RUN IT BEFORE hooking up the US-100 ping
//          sensor! Not doing so could damage the Arduino!
// This is set up to direct connect power and ground for the US-100 ping sensor to be
// on pins 10(5v) 11(ping) 12(echo) 13(low/gnd) 14(hard ground)

const int powerPin = 10;    // providing power to ping sensor from pin 10
const int pingPin = 11;     // pin we're sending the trigger/ping on
const int echoPin = 12;     // pin we're reading back the echo on
const int gnd1Pin = 13;     // simulated ground so we can safely plug the module into our arduinos
//last GND pin goes to "pin 14" on the arduino or sensor shield

long dist = 0;

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
const int angleMult = 6;     // Tile/Carpet multiplier to aplify/dampen turn angle (for tile=6, carpet=7)
const int backDelay = 200;  // Delay for slight back up before turning out of an obstacle


int paused = true;        // Program starts off in paused mode
int waspaused = true;     // Tracks state if we were previously paused (or not)

int accel = 45;              // acceleration figure for turns (if needed)
const int conaccel = accel;  // constant (if needed)

int slowed = false;

int obstacleL = false;
int obstacleR = false;
int obstacleC = false;
  
// ***********************************************************
// ******* SETUP BLOCK ***************************************
// ***********************************************************
// only runs once at program startup
void setup() {
  // US-100 PING SENSOR POWER/GND SETUP
  // set up inline, direct connect power and ground for the US-100 ping sensor to be
  // on pins:                       
  // US-100  \--5v-trg-echo-GND-GND--/
  //             |   |   |   |   |
  // Arduino     10  11  12  13  14(hard ground)
  //
  pinMode(gnd1Pin, OUTPUT);      // sets up ping module's inner GND pin on a low output, and
  digitalWrite(gnd1Pin, LOW);     // the outter GND pin to hard GND (on most arduinos)
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);  // try to power the module from pin
  // ** US-100 PING SENSOR I/O PINS
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, OUTPUT);    // just to make sure
  digitalWrite(echoPin, LOW);  // we clear any previous settings
  pinMode(echoPin, INPUT);     // and then use it as INPUT
  delay(500);
  // Servo setup
  servoR.attach(5);  // attaches the left servo on pin 5
  servoL.attach(6);  // attaches the right servo on pin 6
  // little initialization dance
  turnL(20);
  turnR(20);
  // initialize serial communication:
  Serial.begin(9600);
}


// ***********************************************************
// ******* MAIN LOOP *****************************************
// ***********************************************************
// Runs forever...
void loop() {

  pauseNgo();                    // This uses the sensor as a "pause/start" toggle switch
                                 // Wave your hand (less than two inches) in front of ping to go (unpause)

  dist = getdist();              // looks with ping sensor to measure distance to any objects in front of bot


  //****** If object detected between 2-7 inches away (and the system is not paused), then run the slowDown() function.
  if ( (dist > 1 && dist < 8) && (paused == false) ) {
    slowed = false;
    slowDown();    //quickly slows down and sets state to "slowed = true"
  }


  //****** If Slowed (due to obstacle) in slowDown(), next scan L&R for obstacle position (L || R)
  if (slowed == true && paused == false) {
    Serial.println("Entered if-slowed test.. about to scan R & L");
    scanLR();     // scans for obstacle and records
    slowed = 0;
    Serial.print("obstacleR="); Serial.println(obstacleR);
    Serial.print("obstacleC="); Serial.println(obstacleC);
    Serial.print("obstacleL="); Serial.println(obstacleL);
  }

  //******  If obstacle is on the left, center or right...
  while ( (obstacleR == true || obstacleC == true || obstacleL == true ) && (paused == false) ){
      Serial.println("While (obstacle L||R)...");   

    //*** If obstacle in center (front), but none on the Right OR Left, then turn left and continue
    if (obstacleR == false && obstacleL == false && obstacleC == true && paused == false) {
      Serial.println("obstacleC only action");   
      slowed = 0;
      backward();         // back up a little
      delay(backDelay);   //
      turnL(120);            // if only something in front of us, just default turn left
      obstacleC = false;  // reset
      obstacleR = false;  // reset
      obstacleL = false;  // reset
      forward();          // go forward
      break;              // breaks out of while loop (skipping other checks)
    }

    //*** If obstacle is on the Right only (and system is not paused), turn left and continue
    if (obstacleR == true && paused == false) {
      Serial.println("obstacleR action");   
      slowed = 0;
      backward();         // back up a little
      delay(backDelay);   //
      turnL(120);            // turn left
      obstacleC = false;  // reset
      obstacleR = false;  // reset
      obstacleL = false;  // reset
      forward();          // go forward
      break;              // breaks out of while loop (skipping other checks)
    }
  
    //*** If obstacle is on the Left only (and system is not paused), turn right and continue
    if (obstacleL == true && paused == false) {
      Serial.println("obstacleL action");   
      slowed = 0;
      backward();         // back up a little
      delay(backDelay);   //
      turnR(120);            // turn right
      obstacleC = false;  // reset
      obstacleR = false;  // reset
      obstacleL = false;  // reset
      forward();          // go forward
      break;              // breaks out of while loop (skipping other checks)
    }    
  }

  delay(100);
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

// ***********************************************************
// ***** scanLR() *******************************************
// ***********************************************************
void scanLR() {
  Serial.println("Entered scanLR() ");
  int obstacleThold = 10;
  obstacleC = false;
  obstacleR = false;
  obstacleL = false;
  const int scandelay = 850;

  // Scan forward
  Serial.println("scan center");
  dist = getdist();
  if (dist <= obstacleThold) {
    obstacleC = true;
    Serial.print(dist);
    Serial.println("in.   obstacleC = true");
  }
  Serial.println("--");

  // Scan Right
  Serial.println("scan right");
  servoR.write(reverseR);           // rotate R servo reverse
  delay(scandelay-100);             // wait for turn
  dist = getdist();
  if (dist <= obstacleThold) {
    obstacleR = true;
    Serial.print(dist);
    Serial.println("in.   obstacleR = true");
  }
  servoR.write(forwardR);           // return center
  delay(scandelay-100);             // 
  Serial.println("--");
  stopAll();
  delay(250);


   // Scan Left
  Serial.println("scan left");
  servoL.write(reverseL);           // rotate L servo reverse
  delay(scandelay+100);             // turns further left (gets out of perfect perpendicular objects, getting out to the left)
  dist = getdist();
  if (dist <= obstacleThold) {
    obstacleL = true;
    Serial.print(dist);
    Serial.println("in.   obstacleL = true");
  }
  servoL.write(forwardL);           // return center
  delay(scandelay+100);             // turns further left (gets out of perfect perpendicular objects, getting out to the left)
  Serial.println("--");
  stopAll();
  delay(250);
}

// ***********************************************************
// ***** getdist() *******************************************
// ***********************************************************
long getdist()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingPin, HIGH);      // start the outgoing ping
  delayMicroseconds(10);            // do the ping for 10uS
  digitalWrite(pingPin, LOW);       // stop doing the ping
  duration = pulseIn(echoPin, HIGH);  // grab the delay of return echo
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  //cm = microsecondsToCentimeters(duration);
  //Serial.print(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();

  return (inches);
}


// ***********************************************************
// ***** pauseNgo() ******************************************
// ***********************************************************
void pauseNgo() {

  // If unpaused, but object less than two inches, go into paused mode
  dist = getdist();
  if (paused == false && dist < 2){
        Serial.println("UNPAUSED - I GO UNTIL I SEE SOMETHING CLOSE...");
  }
  while (paused == false && dist < 2 ) {
    dist = getdist();
    if (dist < 2 ) {
      paused = 1;
      Serial.println("ALL STOP");
      // Stop
      stopAll();
      paused = 1;
      waspaused = 0;
      delay(250);
    }
  }
  

  // Paused Loop & Unpausing Detection  
  dist = getdist();
  if (paused == true){
    Serial.println("PAUSED - UNTIL I SEE SOMETHING CLOSE...");
  }
  while (paused == true) {
    dist = getdist();
    Serial.print(dist);
    Serial.print(" ");
    if (dist < 2 ) {
      Serial.println("");
      Serial.println("ALL AHEAD");
      // Start moving forward, full speed
      servoL.write(forwardL);                  // forward L servo
      servoR.write(forwardR);                  // forward R servo
      paused = 0;
      waspaused = 1;
    }
  }
  
  
}

// ***********************************************************
// ***** slowDown() ******************************************
// ***********************************************************
void slowDown() {
  Serial.println("ENTERED slowDown()");
  accel = 0;
  for ( int x = 0 ; x < 8 ; x++ ) {
    accel =  accel + 5;
    servoL.write(forwardL - accel);                // slow L servo
    servoR.write(forwardR + accel);                // slow R servo
    delay(50);
  }
  stopAll();
  accel = conaccel;
  slowed = 1;
  waspaused = 0;
}

// Original code from the ping sensor library
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
