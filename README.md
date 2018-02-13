## Overview
This is the code for the Let's Code Blacksburg Arduino, Sensors, Robotics Workshop
https://www.eventbrite.com/e/18949799360

The collision-bot workshop build document steps you through building a foam board, arduino based collision-avoidance bot. See PDF instruction and code.  You can buy all the parts off Amazon or AliExpress.com for around $30. 

## Collision-Bot Workshop:
To get started..

1.  Download the workshop build doc PDF and build the bot (requires 5"x6" foam board, 2 milk jug caps, 1 soda cap, arduino, two continuous servos and a US-100 ping sensor, optional 5mW laser and hot glue.)

2. Download ping_US-100_sensor.ino fist.. build/upload and THEN hook up the US-100 ping sensor (do not connect ping sensor until you have uploaded/run the code!)

3. Download the two-servo-test.ino sevo motor test code and tune forwardL, forwardR, stopL and stopR values for straight movement and solid stopping

4. Combine ping and sevo code to make autonomous bot

You should be able to code your very own collision-avoidance bot.  
If you want to see a more complete version, check out the LCBB_collision-bot_complete.ino code.

## Here's the parts list:
* Arduino (brain, 1x) - https://www.amazon.com/dp/B01E8LKITO/ ($10)
* Ultrasonic US-100 (eyes, 1x) - https://www.amazon.com/dp/B009URKD2E ($4)
* KY-008 Laser - https://www.amazon.com/dp/B07216CZTV/  (<$5)
* Servos (x2) - https://www.robotshop.com/en/9g-continuous-rotation-micro-servo.html ($10)
* 9V Battery Case - https://www.amazon.com/dp/B06WGQKJ5P ($5)
* 9V Battery (~$2)

The Laser-Bot Mission to Mars uses the collision-bot chassis, add a laser diode to make a mission to marse lab where the student has to program the laser-bot rover to it's target and blast the alien ship.


All LCBB code and related materials are copy left (open sourced) under the Creative Commons (CC)(BY)(SA)[1] License.

[1] - https://en.wikipedia.org/wiki/Creative_Commons_license#Types_of_licenses
