Winmine-Trainer
===============

Project 2 of Rensselaer Polytechnic Institute's Malware Analysis Course
(CSCI 4976). Runs a trainer that allows you to talk to a winmine.exe instance
and allows you to automatically win, show layout of tiles, etc.

### How to Use
Running trainer.exe opens up a console window and a winmine.exe instance.
Running the commands should work as expected. Closing the console window will
also kill the winmine.exe. The following operations are supported:

1. Extract layout of the tiles
2. Make the mines visible in game
3. Freeze the timer
4. Render mines inert
5. Auto win!

Note: pausing the timer only works after the first bomb has been pressed

### How to Build
Notice! Only works on MSVC (for now)!

Everything compiles fine on MinGW but for some reason the dll's won't inject...

```
mkdir build
cd build
cmake ..
msbuild ALL_BUILD.vxcproj
# NOTE: it might be necessary to copy winmine.exe into the current directory
# of the binary (probably in the Debug folder). CMake currently fails at moving
# winmine.exe to the current binary dir...
```
