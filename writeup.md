Writeup
=======

## Main C2 Program
The main program creates a process into winmine.exe and records a handle to
it. On command we inject one of 5 dll's, each of them containing the code
relevant to the task within their DllMain functions. In order to be able to
hit each option more than once we also clean up by freeing the library we
created in the remote thread as well.

## Analysis and Report
As soon as we open up IDA, we clearly see some nice functions, namely ShowBombs
and PauseTimer. These do as expected, either showing the locations of the bombs
or pausing the timer if it is currently running. We also see a GameOver function
which takes a boolean as an argument, however using this is cheating, even by
our standards :)

![important functions in IDA](https://raw.githubusercontent.com/toshipiazza/winmine-trainer/master/img/ida_important_functions.png?token=AF9vVr0SWZHxDOwo5dWcabNinPBbQ1hqks5WQSK-wA%3D%3D)

Although the previous two functions take care of mines_visible and free_timer,
we still know nothing about get_layout, auto_win, etc. However, we see in the
ShowBombs function, and many others that there exists a common memory address
0x01005360 which stores information on the board. Dumping its values at various
points in the program shows us that it takes on a few common traits:

![nothing much to see here...](https://raw.githubusercontent.com/toshipiazza/winmine-trainer/master/img/visible_board_XREF.png?token=AF9vVmXAnhBlp9w7Hj0pgzf9MxI8jUGhks5WQSM1wA%3D%3D)

* The board is a fixed size. Variables are used at runtime to keep track of what
  memory is being used or not. We can thus get the value of tile (i,j) with
  ```*(0x01005360 + j + 0x20 * i)```.
* We can get the dimensions of the board from some variables in memory, and get
  the bomb count at each tile from the function CountBombs.
* We see that all bombs, visible or invisible or flagged or whatever all have
  0x80 set, in other words it is a flag for a tile being a bomb tile.
* Also, all numbers that have been revealed are flagged with 0x40
* Less important, flags have bitmask 0xFE and question marks have bitmask 0xFD
* Tiles are all masked with 0x1F, so that these bits are not shown... as a
  result the values taken up by the tiles can be between 0 and 16, after being
  anded with 0x1F. (see below)

![playing with the debugger](https://raw.githubusercontent.com/toshipiazza/winmine-trainer/master/img/malware-print.png?token=AF9vVkaIUToqmXAeVNXGGIuIGVPAChqvks5WQSNQwA%3D%3D)

Finally, we later see the function StepSquare which allows us to complete both
GetLayout and AutoWin - we can simply iterate over the board and perform operations
based on the bits that are set on each tile.

We handle disable_mines specially because there is no simple function that gives
us this functionality (why would there be?). We instead patch some bytes at runtime.

## Writing the Trainer
The trainer was written using CMake, which automates builds for visual c++/msbuild,
as well as MinGW (which currently is not supported). The unimportant driver is trainer.cpp
which heavily uses inject.cpp. trainer.cpp opens up a console and winmine.exe and asks
the user for a command, and will inject the correct dll depending on the command.

![pretty output! - Cmake](https://raw.githubusercontent.com/toshipiazza/winmine-trainer/master/img/cmake.png?token=AF9vVpnWtbHzQNWyHVahvBAH0wQt6K6fks5WQSS-wA%3D%3D)

Each dll is written in the same format with a DllMain. These are all compiled in 32bit
because it must match the bitwidth of the target process, winmine. Although intensive
work should not be done in DllMain, for example calling MessageBox, since all the other
modules have been loaded already we don't really need to worry about doing annoying stuff
while holding the global loader lock.

Each dll essentially works the same. They all take some hardcoded values as pointers
to variables or functions in the program and take advantage of them in some way.

## Features
### get_layout
  * We iterate over the board (located at address 0x01005360) and call
    winmine.exe's custom CountBombs function which gets all adjacent bombs.
  * Because winmine.exe determines all of its important tiles based on flags,
    while also not determining any numbers until the user has clicked on a
    good tile, we need to mask the return value with 0x80, the indicator for
    the existence of a bomb.

### mines_visible
  * We make use of the build in ShowBombs function, which takes 0xa in as an
    argument (is it the bitmap?). This displays all of the bombs.
  * Funny enough, if you click on a bomb after ShowBombs gets called, we see
    that we do not lose the game. This is because MineSweeper is not able to
    penalize someone on the very first click, so it moves the bomb elsewhere.

### freeze_timer
  * We again call a built-in function to PauseGame(), though this only works
    after the timer has started initially, i.e. the game was started.

### disable_mines
  * This was the most involved system. We VirtualProtect all memory relevant
    to us with very XRW permissions temporarily, and dump some
    code in, completely overwriting what was there. This allows us to skip
    the call to GameOver(0), which inevitably exits the game.

### auto_win
  * We use a scheme similar to get_layout except if we are not on a bomb tile
    we step on it with StepSquare.
