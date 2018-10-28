## Overview
<IMG SRC=http://theweeks.org/tmp/PICS/LCBB/laser-bot.png align=right width=400>
This is the code for the three hour, hands on [Let's Code Blacksburg Arduino, Sensors, Robotics Workshop](https://www.eventbrite.com/e/18949799360) as well as the shorter, more intro level intro to robotics [LCBB Martian Laser Bot coding activity]().

The collision-bot (aka "Laser Bot") workshop build document steps you through building a foam board, arduino based collision-avoidance bot. See PDF instruction and code below.  The collision-bot workshop takes around 3 hours and you can buy all the parts off Amazon or AliExpress.com for around $30.

As an additional hands on activity (after you've built a few laser-bots), you can run a shorter (20min), much more simple hands on ["Martian Laser-Bot Mission" activity](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/arduino-robotics-laser-bot-lab.pdf) that is both a lot of fun, as well as geared much more to the beginner coder.

> TEACHERS: If you build 3-4 collision-bots (with lasers) ahead of time, you can use them along 
> with the Martian laser-bot mission to introduce kids to very simple, intro level robotics programming 
> (via arduino IDE in C++).  Then after their hooked, move them on to the full 3 hour, hands on 
> Collision-Bot workshop (below) where they can build and take home their own laser-bot.


## Collision-Bot Workshop: (advanced level)
To get started on the hands on, three hour workshop to build and code your collision-bots from scratch..

1.  Download the [collision bot workshop build doc PDF](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/PDF_arduino-robotics-collision-bot.pdf) and build the bot (requires 5"x6" foam board, 2 milk jug caps, 1 soda cap, arduino, two continuous servos and a US-100 ping sensor, optional 5mW laser and hot glue.)

2. Download and run the 2_blink test code and verify your arduino hardware and software are working

3. Next, download 3_ping_US-100_and_laser.ino.. build/upload and THEN hook up the US-100 ping sensor (do not connect ping sensor until you have uploaded/run the code!)

4. Download the 4_two-servos-test.ino code, tune the stopL, stopR values solid stopAll() functionality (and optionally forwardL, forwardR values to ensure your bot goes in a straight line).

5. Completing the bot's code:
* 5a For experienced coders, combine ping and sevo code to make autonomous bot
* 5b For inexperienced coders, download the 5b_collision-bot_complete.ino code and tune your stopL and stopR values
* 5c For doing the ["Mission to Mars" mission PDF](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/arduino-robotics-laser-bot-lab.pdf), and download [5c_Laser_Bot_Mission_to_Mars.ino code](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) and program bot movements on another planet! (can you find and fix the laser cannon bug?)

For a stretch goal, have your more advanced students employ the getDist() function in [5c_Laser_Bot_Mission_to_Mars.ino code](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) to detect objects in the bot's path to make your very own autonomous collision-avoiding robot, or even shoot things with the laser that get in the path of your robot!

## Here's the parts list:
* Arduino (brain, 1x) - https://www.amazon.com/dp/B01E8LKITO/ ($10)
* Ultrasonic US-100 (eyes, 1x) - https://www.amazon.com/dp/B009URKD2E ($4)
* KY-008 Laser - https://www.amazon.com/dp/B07216CZTV/  (<$5)
* Servos (x2) - https://www.robotshop.com/en/9g-continuous-rotation-micro-servo.html ($10)
* 9V Battery Case - https://www.amazon.com/dp/B06WGQKJ5P ($5)
* 9V Battery (~$2)


## Additional Martian Laser-Bot Mission: (intro level)
The Laser-Bot Mission to Mars coding activity uses the previously built collision-bot (w/5000 µWatt laser cannon). The Martian Laser-Bot mission is a much less intensive, more intro level coding activity.  In this shorter (20 minute) intro  level hands on coding activity, each student is tasked with programming their already built, [code-complete](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) laser-bot rover to navigate the mountainous Martian terrain, find the alien armada, and take them out with their laser cannon before they launch their attack on Earth!  See photos and video here:
https://photos.app.goo.gl/Kyo2fSg3D5SCUErP8

All LCBB code and related materials are copy left (open sourced) under the Creative Commons (CC)(BY)(SA)[1] License.

[1] - https://en.wikipedia.org/wiki/Creative_Commons_license#Types_of_licenses
