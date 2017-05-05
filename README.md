# BabyRoomWatcher
## Project Description

The purpose of the project is to monitor what happening in the baby room when we are not present there. To capture the event in the baby room we will use the Cypress CY8CKIT-048 PSoC Analog Coprocessor Pioneer Kit. The kit has a sensor interface composed of a PIR Motion sensor, Humidity sensor, proximity sensor, ambient light sensor and a thermistor. Theses sensors will allow to detect:

* the presence of someone in the room
* the temperature of the room
* the ambient light in the room
* the humidity of the room

Once the data collected by the kit, it will be sent to the Raspberry Pi. To notify the parents we will use:

* OpenHab: which is an open source automation software, will be used as a web server to see the video streaming of what is happening in the baby room.
* GSM module which will allow to send SMS directly to the parents.

Finally, to have a good idea of what happening in the baby room, a Raspberry pi camera will be used to start recording when the sensors will detect the presence of someone in the room.

![ScreenShot](https://raw.github.com/raygi/BabyRoomWatcher/tree/master/Pictures/BabyRoomWatcherComplete.JPG)
