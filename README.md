## Overview
This is the code for the Let's Code Blacksburg Arduino, Sensors, Robotics Workshop
https://www.eventbrite.com/e/18949799360

The collision-bot workshop build document steps you through building a foam board, arduino based collision-avoidance bot. See PDF instruction and code.  You can buy all the parts off Amazon or AliExpress.com for around $30. 

## Collision-Bot Workshop:
To get started..

1.  Download the [collision bot workshop build doc PDF](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/PDF_arduino-robotics-collision-bot.pdf) and build the bot (requires 5"x6" foam board, 2 milk jug caps, 1 soda cap, arduino, two continuous servos and a US-100 ping sensor, optional 5mW laser and hot glue.)

2. Download and run the 2_blink test code and verify your arduino hardware and software are working

3. Next, download 3_ping_US-100_and_laser.ino.. build/upload and THEN hook up the US-100 ping sensor (do not connect ping sensor until you have uploaded/run the code!)

4. Download the 4_two-servos-test.ino code, tune the stopL, stopR values solid stopAll() functionality (and optionally forwardL, forwardR values to ensure your bot goes in a straight line).

5. Completing the bot's code:
* 5a For experienced coders, combine ping and sevo code to make autonomous bot
* 5b For inexperienced coders, download the 5b_collision-bot_complete.ino code and tune your stopL and stopR values
* 5c For doing the ["Mission to Mars" mission PDF](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/2016-03-19_arduino-robotics-laser-bot-lab.pdf), and download [5c_Laser_Bot_Mission_to_Mars.ino code](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) and program bot movements on another planet! (can you find and fix the laser cannon bug?)

Taking this workshop to the next level, using getDist() to detect objects in the bot's path, you should be able to code your very own autonomous collision-avoiding robot, or shoot things with the laser that get in the path of your robot!

## Here's the parts list:
* Arduino (brain, 1x) - https://www.amazon.com/dp/B01E8LKITO/ ($10)
* Ultrasonic US-100 (eyes, 1x) - https://www.amazon.com/dp/B009URKD2E ($4)
* KY-008 Laser - https://www.amazon.com/dp/B07216CZTV/  (<$5)
* Servos (x2) - https://www.robotshop.com/en/9g-continuous-rotation-micro-servo.html ($10)
* 9V Battery Case - https://www.amazon.com/dp/B06WGQKJ5P ($5)
* 9V Battery (~$2)

The Laser-Bot Mission to Mars uses the collision-bot chassis, adds a laser diode to make a mission to Mars lab where the student has to program the laser-bot rover to it's target and blast the alien ship. See photos here:
https://www.flickr.com/photos/cultureinstigator/albums/72157670487243765

All LCBB code and related materials are copy left (open sourced) under the Creative Commons (CC)(BY)(SA)[1] License.

[1] - https://en.wikipedia.org/wiki/Creative_Commons_license#Types_of_licenses
