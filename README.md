PopDrop
=======

A simple balloon-popping arcade game made with SDL2.

Description
-----------

PopDrop is a fast-paced, arcade-style balloon popping game built 
entirely from scratch using C/C++ and the SDL2 framework. Test your 
reflexes and see how many balloons you can pop before the time runs out! 
It features addictive arcade gameplay, lightweight native performance, 
and classic retro casual mechanics.


How to Run (Linux x86_64)
-------------------------

1. Extract the downloaded zip file:
   unzip PopDrop-Linux-x86_64.zip

2. Open a terminal inside the extracted 'PopDrop-itch' folder.

3. Make the launcher script executable (only needed once):
   chmod +x run.sh

4. Run the game:
   ./run.sh


Controls
--------

Mouse:
- Left Click = Pop balloons

Keyboard:
- ESC = Quit game


How it Works (No Dependencies Needed)
--------------------------------------

This package includes all necessary SDL2 runtime libraries pre-compiled 
inside the 'lib/' directory. 

The 'run.sh' script automatically configures the game's library path 
(LD_LIBRARY_PATH) before launching, so you do not need to install SDL2, 
SDL2_mixer, or SDL2_image system-wide.


Troubleshooting
---------------

If the game fails to start, run the script from your terminal to view 
any console output errors:

   ./run.sh


Credits
-------

Engine/Framework: SDL2 (and SDL2_image, SDL2_mixer)

Enjoy the game!