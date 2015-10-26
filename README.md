Winmine-Trainer
===============

Project 2 of Rensselaer Polytechnic Institute's Malware Analysis Course
(CSCI 4976). Runs a trainer that allows you to talk to a winmine.exe instance
and allows you to automatically win, show layout of tiles, etc.

### How to Use
Running trainer.exe opens up a console window and a winmine.exe instance.
Running the commands should work as expected. Closing the console window will
also kill the winmine.exe.

### How to Build
Notice! Only works on MSVC for now!

```
mkdir build
cd build
cmake ..
msbuild ALL_BUILD.vxcproj
```
