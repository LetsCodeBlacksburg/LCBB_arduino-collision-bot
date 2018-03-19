// 3_ping_US-100_and_laser
// for Let's Code Blacksburg! www.letscodeblacksburg.org 2018-03-19
// By Thomas "Tweeks" Tweeks, tweeks-homework(at)theweeks.org
//
// This ping-sensor & laser code is set up for using a four pin ping sensor such as
// the US-100 or HC-SR04 ultrasonic distance sensor module:
// https://www.bananarobotics.com/shop/US-100-Ultrasonic-Distance-Sensor-Module
// http://www.iseerobot.com/produk-1255-us100-ultrasonic-sensor-for-arduino.html
// NOTE: For this code, + the US-100 module, be sure to remove the serial-data jumper on the
// back so that you get back the raw pulse from the echo pin (and not serial distance data).
//
// CAUTION: Have your code checked, and have the TA RUN IT BEFORE connecting the US-100 ping
//          sensor! Not doing so could damage the Arduino and/or sensor!
// This is set up to direct connect power and ground for the US-100 ping sensor to be
// on pins 10(5v) 11(ping) 12(echo) 13(low/gnd) 14(hard ground)

const int powerPin = 10;    // providing power to ping sensor from pin 10
const int pingPin = 11;     // pin we're sending the trigger/ping on
const int echoPin = 12;     // pin we're reading back the echo on
const int gnd1Pin = 13;     // simulated ground so we can safely plug the module into our arduinos
//last GND pin goes to "pin 14" on the arduino or sensor shield

// Here is where we hook up the 5mW laser diode. We provide power and ground from the digital output pins.
const int laserPin = 4;      // the pin the laser's power pin goes to
const int laserGnd = 2;      // the pin the laser's ground pin goes to


long dist = 0;
  
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
  // Arduino     10  11  12  13  14(hard ground, if present)
  //    (looking from the outter edge of arduino pin header)
  pinMode(gnd1Pin, OUTPUT);      // sets up ping module's inner GND pin on a low output, and
  digitalWrite(gnd1Pin, LOW);     // the outter GND pin to hard GND (on most arduinos)
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);  // try to power the module from pin
  // ** US-100 ping sensor I/O pin setup
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, OUTPUT);    // just to make sure
  digitalWrite(echoPin, LOW);  // we clear any previous settings
  pinMode(echoPin, INPUT);     // and then use it as INPUT
  delay(500);
  // Laser Setup
  pinMode(laserGnd, OUTPUT);    // Laser GND pin
  digitalWrite(laserGnd, LOW);
  pinMode(laserPin, OUTPUT);    // Laser Power (Vcc) Pin 
  digitalWrite(laserPin, HIGH);  // Test pulse laser
  delay(250);                   // for 1/4 second
  digitalWrite(laserPin, LOW);  // Start off with laser off
  // Set up serial port (for communcating back to the PC)
  Serial.begin(9600);
}




// ***********************************************************
// ***** fireLaser() *****************************************
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
// ******* MAIN LOOP *****************************************
// ***********************************************************
// Runs forever...
void loop() {

  dist = getdist();              // looks with ping sensor to measure distance to any objects
  Serial.print("Distance = ");
  Serial.println(dist);
  delay(100);

  fireLaser(1);	// fire the impressive 5,000 microWatt 650nM laser cannon z times
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
