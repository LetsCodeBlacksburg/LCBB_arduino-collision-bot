// 5c_laser-bot_mission_to_mars
// This letscodeblacksburg.org project is for using the existing LCBB collision bot build, adding 
// a laser to it, and making an easy, "macro mission" for kids to program and fire a laser at aliens.
// Example code and documentation at https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot
// Thomas "Tweeks" Weeks, tweeks-homework(at)theweeks.org

#include <Servo.h>

// This ping-sensor code is set up for using a four pin ping sensor such as
// the US-100 module:
// https://www.bananarobotics.com/shop/US-100-Ultrasonic-Distance-Sensor-Module
// http://www.iseerobot.com/produk-1255-us100-ultrasonic-sensor-for-arduino.html
// NOTE: If using the US-100 module, be sure to remove the serial-data jumper on the
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
//last GND pin goes to "pin 14" on the arduino or sensor shield (not all ping sensors have this pin)

// Here is where we hook up the 5mW laser diode. We provide power and ground from the digital output pins 2 and 4.
const int laserPin = 3;      // Pin the laser power is on
const int laserGnd = 2;      // Pin the laser ground in on

long dist = 0;

Servo servoL;  // create servo object to control a servo
Servo servoR;  // create servo object to control a servo

// Servo Tunung
// These values are just starting points. Every servo is a little different and so you may need to fine tune each.
// Don't forget that depending n how you have your servos mounted, a value can go "forward" on one servo but "backward" on the other.
// You may need to tune the forward rev values to go in a straight line or turn.
// You will probably need to tune the stopL and stopR values to get to a dead stop on each servo
const int forwardL = 135;   // 135 is Clockwise, full speed (around 90 is stopped)
const int forwardR = 45;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int reverseL = 45;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int reverseR = 135;   // 135 is Clockwise, full speed (around 90 is stopped)

const int stopL = 93;  // 90 is usually "stopped" (you may need to fine tune up/down for dead stop)
const int stopR = 88;    // 90 is usually "stopped" (you may need to fine tune up/down it for dead stop)

// These distance and angle multipliers must be scaled along with servo supply voltage (e.g. 5v, 6v 9v, etc)
const int inchesMult = 125;  // Multiplier to convert inches into miliseconds of wheel movement
const int angleMult = 6;     // Multiplier to convert turn angle into miliseconds of wheel movement (6 for tile, 7 for carpet)
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

  // Servo Setup
  servoR.attach(5);            // attaches the left servo on pin 5
  servoL.attach(6);            // attaches the right servo on pin 6

  // Laser Setup
  pinMode(laserGnd, OUTPUT);    // Laser GND pin
  digitalWrite(laserGnd, LOW);
  pinMode(laserPin, OUTPUT);    // Laser Power (Vcc) Pin 
  digitalWrite(laserPin, HIGH);  // Test pulse laser
  delay(250);                   // for 1/4 second
  digitalWrite(laserPin, LOW);  // Start off with laser off
  
  ////  Servo reset
  turnL(45);
  turnR(45);
  ////  initialize serial communication:
  Serial.begin(9600);
}

  
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
    delay( (inches * inchesMult));           // roughly convert inches to miliseconds of wheel rotations
    stopAll();
}


// ***********************************************************
// ***** stopAll() *********************************************
// ***********************************************************
void stopAll(){
    Serial.println("stopAll()");
    servoR.write(stopR);              // stop
    servoL.write(stopL);              // stop
}

// ***********************************************************
// ***** pause() *********************************************
// ***********************************************************
void pause(){
  paused = true;        // Puts bot back in pause-mode (awaiting pauseNgo() hand sweep)
}


// ***********************************************************
// ***** fireLaser() *********************************************
// ***********************************************************
void fireLaser(int count){
    int x=0;
    for (x=1;x<(count+1);x++){
    Serial.println("fire()");
    digitalWrite(laserPin, HIGH); // Pulse laser
    delay(250);                   // for 1/4 second
    digitalWrite(laserPin, LOW);  // Start off with laser off 
    delay(250);                   // for 1/4 second    
    }

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
  servoR.write(stopR);              // stop
  servoL.write(stopL);              // stop
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
  servoR.write(stopR);              // stop
  servoL.write(stopL);              // stop
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
      servoL.write(stopL);                  // stop L servo
      servoR.write(stopR);                  // stop R servo
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
    delay(150);
  }
  servoL.write(stopL);                  // stop L servo
  servoR.write(stopR);                  // stop R servo
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



////////////// Everything above this is program functoions called from the main loop


// ***********************************************************
// ******* MAIN LOOP *****************************************
// ***********************************************************
// Runs forever...
void loop() {      // anything starting with "//" is just a comment :)
  pauseNgo();       // This uses the ping-eyes sensor as a "start/pause" toggle switch


  ////// Insert and fill in your code here

  forward(10);      // This tells the bot how many inches forward to go.  
  fireLaser(3);
  
   ////// end of your code

  pause();          // Sets bot to pause mode
  // loops back to top of main loop()
}
////// HELP WITH COMMANDS:
////// The commands available to you are below. Just copy/paste them to your own code and uncommend them:
//forward(x);  // goes forward x inches
//backward(x);  // goes backwards x inches         
//turnL(y); // turns left around y degrees    
//turnR(y); // turns right around y degrees           
//slowDown(); // slows to a dramatic stop   
//stopAll();  // Stops both L & R wheels    
//fireLaser(z); // fire the impressive 5,000 microWatt 650nM laser cannon z times

// Some of the more advanced commands:
//pauseNgo();     // uses the ping sensor as a "start/pause" switch
//pause();    //  sets the bot to pause (and wait) mode
//dist=getdist(); // looks with ping sensor to get distance to objects
//if ( dist < 4) { //do stuff }  // if allows you to compare things and then do stuff if true.
//while ( condition ) { //do stuff }  // while will do things forever (or until condition fails)
