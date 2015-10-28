Writeup
=======

## Main C2 Program
The main program creates a process into winmine.exe and records a handle to
it. On command we inject one of 5 dll's, each of them containing the code
relevant to the task within their DllMain functions. In order to be able to
hit each option more than once we also clean up by freeing the library we
created in the remote thread as well.

## Dll's
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
