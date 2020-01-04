=========================================
la            _ _            _   _       
  /\/\   __ _| (_)_ __   ___| |_| |_ ___ 
 /    \ / _` | | | '_ \ / _ \ __| __/ _ \
/ /\/\ \ (_| | | | | | |  __/ |_| ||  __/
\/    \/\__,_|_|_|_| |_|\___|\__|\__\___|
 
/////////////////////////////////////////

      Version: 0.89
      Language: English, French
      Date: 06/11/2014
      Contact: contact_at_reso-nance.org
      Website:        Licence: GNU/GPL v3

Special thanks for all Pure Data developers, we've taken some good ideas from few projects (pdmtl abstractions, DIY2, ...)

Description
=======================================
Malinette is an all-in-one solution, a rapid prototyping tool to show and make simple interaction and multimedia projects. It is a software and a hardware set. The software is based on Pure Data extended. It will be (one day) also a very convenient suitcase with a computer, speakers, arduino and electronic circuits to test ideas and projects very quickly.

Requirements
=======================================
- Computer : a decent computer (>2005 is adviced)
- Operating system : tested on GNU/Linux/Xubuntu.12.4. But the main other platforms sould work (Mac Os X, MS Windows XP, Vista, 7 and main distributions GNU/Linux)
- Install Pure Data extended 0.43.4 : http://puredata.info/community/projects/software/pd-extended
- Optional, if you want to use an Arduino, download the Arduino software : http://www.arduino.cc/en/Main/Software. Plug the USB board, install drivers if required, and upload the "StandardFirmata" sketch from the Arduino software : Menu File > Examples > Firmata > StandardFirmata

Installation and startup
=======================================
1. Download the software: http://reso-nance.org/malinette/download
2. Extract anywhere
3. Open the "MALINETTE-en.pd" patch for English people and "Malinette-fr" for French People.
4. Clic on "? Help" or "? Aides" button if needed
5. Open examples to see how it works

User instructions
=======================================
You have two windows : the menu on the left, and the project on the right (a "patch" in Pure Data).
Basically, you can open examples or create your project.
When you open an example it close the last one.
When you want to start a project, the better way is to open the "00-new" project and fill it with some objects ("abstractions" is the right term in Pure Data).
You have helps in the main patch, see the "?" button and you can find some documentations in the "./docs" folder.
Have fun and report feedbacks and bugs at info_at_reso-nance.org

Contents
=======================================
./abstractions	: all abstractions (in, out, filters, fx-audio, fx-video, tools and master)
./data		: media files (images, videos, sounds, etc.)
./docs		: some documentations (licence, todo, changes) and helps
./examples	: examples patchs to show and edit projects about interaction
./lib 		: externals objects or abstractions
./other		: tclplugins, scripts, processing code, ...
./projects	: your projects
MALINETTE.pd	: open this patch to start the program 
license.txt
readme.txt

Abstractions
=======================================
./abstractions/fx-audio : audio effects abstractions
./abstractions/fx-data 	: data effects abstractions
./abstractions/fx-video	: video effects abstractions
./abstractions/in 	: input abstractions (arduino, audio, video, mouse, key, kinect, ...)
./abstractions/master 	: abstractions to manage the main patch (audio, gem, arduino, buttons)
./abstractions/out 	: output abstractions (arduino, audio, video, ...)
./abstractions/tools 	: tools abstractions

Coding rules
=======================================
- file names with dash
- file names in lowercase
- default values
- test arguments
- a yellow toggle to switch on/off the abstraction
- when an extra object is used from pd-extended, put the library as a prefix. Ex: [tof/menubutton] (to discuss)
- if they are more than 2 or 3 inlets, a good practice would be to use the cold inlet (on the right) to pass messages throught it and route them with a [route] object.

Files formats (video, audio, 3d etc..)
=======================================
Video : best format for video files (better performance in pd) is MJPEG, this compression is better packed in .avi for windows // .mov for mac.
Audio : Pure Data audio object use .aiff or .wav, except some librairies which use mp3 (malinette do not have mp3 player yet.).
3d: .obj is the right 3d-model-file you can import in Pure Data , you can create .obj from most of 3D software (like blender for instance).

Some documentations (in french)
=======================================
Linux : http://doc.ubuntu-fr.org/
Logiciels libres : http://www.framasoft.net/ 
Pure Data : http://fr.flossmanuals.net/Puredata/
Arduino : http://www.arduino.cc/fr/
Arduino : http://fr.flossmanuals.net/arduino/
Informatique : http://www.siteduzero.com/
Forum de bidouilleurs : http://codelab.fr/
