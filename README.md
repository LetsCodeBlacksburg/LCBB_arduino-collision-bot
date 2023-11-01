## Overview <IMG SRC=http://www.theweeks.org/tmp/PICS/LCBB/laser-bot2_800.png align=right width=400>

This is the code and courseware code for the hands on [Lets Code Blacksburg Collision Bot arduino Robotics Workshop](https://www.eventbrite.com/e/18949799360). It consist of a three hour, hands-on build & code worksop ([build-doc](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/Arduino-robotics-collision-bot_build-doc.pdf)), or, after building the bot, a shorter more intro level [Martian Laser-Bot navigation activity](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/Mission-to-mars_robotics-laser-bot-lab.pdf).

First, the collision-bot (aka "Laser Bot") [workshop build document](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/Arduino-robotics-collision-bot_build-doc.pdf) steps you through the building of a a foam board, arduino based collision-avoidance, autonomous rover. See PDF instructions and code below.  The collision-bot workshop build and coding takes around three hours and you can buy all the parts from Amazon or AliExpress.com for around $40. This is straigh up C++ programming best for high school age kids, and so some level of basic C++ or Java coding is recommended before attemptig this lab.

After you've built the laser-bot or have a few bots on hand, there is this more basic, shorter-duration (20min), simple hands on ["Martian Laser-Bot Mission" activity](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/Mission-to-mars_robotics-laser-bot-lab.pdf) that is both a lot of fun, as well as geared much more to the beginner coder (e.g. forward(10), turnR(90), fireLaser(3)). Good for younger kids grades 5-8.

> TEACHERS: If you build 3-4 collision-bots (with lasers) ahead of time, you can use them along 
> with the Martian laser-bot activity to introduce kids to very simple, intro level robotics programming 
> (via arduino IDE in C++).  Then after their hooked, move them on to the full 3 hour, hands on 
> Collision-Bot workshop (below) where they can build and take home their own laser-bot.


## Collision-Bot Workshop: (advanced level)
To get started on the hands on, three hour workshop to build and code your collision-bots from scratch..

1.  Download the [collision bot workshop build doc PDF](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/Arduino-robotics-collision-bot_build-doc.pdf) to build and code the bot. Required parts are a 5"x6" foam board, 2 milk jug caps, 1 soda cap, arduino, two continuous servos and a US-100 ping sensor, optional 5mW laser and hot glue.)

2. Download and run the 2_blink test code and verify your arduino hardware and software are working

3. Next, download 3_ping_US-100_and_laser.ino.. build/upload and THEN hook up the US-100 ping sensor (do not connect ping sensor until you have uploaded/run the code!)

4. Download the 4_two-servos-test.ino code, tune the stopL, stopR values solid stopAll() functionality (and optionally forwardL, forwardR values to ensure your bot goes in a straight line).

5. Completing the bot's code:
* 5a For experienced coders, combine ping and sevo code to make autonomous bot
* 5b For inexperienced coders, download the 5b_collision-bot_complete.ino code and tune your stopL and stopR values
* 5c For doing the ["Mission to Mars" mission PDF](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/Mission-to-mars_robotics-laser-bot-lab.pdf), and download [5c_Laser_Bot_Mission_to_Mars.ino code](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) to begin programming your bot movements on Mars! (but you'll have to find, fix and upload the laser cannon first!)

For a stretch goal, have your more advanced students employ the getDist() function in [5c_Laser_Bot_Mission_to_Mars.ino code](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) to detect objects in the bot's path to make your very own autonomous collision-avoiding robot, or even shoot things with the laser that get in the path of your robot!

## Here's the parts list: (updated 2023-02-14)
* Arduino (brain, 1x) - https://www.amazon.com/dp/B085RHTBJT/ ($15)
* Ultrasonic US-100 (eyes, 1x) - https://www.amazon.com/dp/B098R34Y12 ($8)
* KY-008 Laser - https://www.amazon.com/dp/B07R45F1KY  ($5)
* Servos (x2) - https://www.robotshop.com/en/9g-continuous-rotation-micro-servo.html ($10)
* optional Servos (x2) w/Big Wheels - https://www.amazon.com/dp/B086ZGTLZB/ ($15 optional)
* 9V Battery Case - https://amazon.com/dp/B07T83B4SW/ ($3)
* 9V Battery (~$2)


## Additional Martian Laser-Bot Mission: (intro level)
The Laser-Bot Mission to Mars coding activity uses the previously built collision-bot (w/5000 µWatt laser cannon). The Martian Laser-Bot mission is a much less intensive, more intro level coding activity.  In this shorter (20 minute) intro  level hands on coding activity, each student is tasked with programming their already built, [code-complete](https://github.com/LetsCodeBlacksburg/LCBB_arduino-collision-bot/blob/master/5c_Laser_Bot_Mission_to_Mars.ino) laser-bot rover to navigate the mountainous Martian terrain, find the alien armada, and take them out with their laser cannon before they launch their attack on Earth!  [See activity photos and video here](https://photos.app.goo.gl/Kyo2fSg3D5SCUErP8)
:
All LCBB code and related materials are copy left (open sourced) under the Creative Commons (CC)(BY)(SA)[1] License.

[1] - https://en.wikipedia.org/wiki/Creative_Commons_license#Types_of_licenses
