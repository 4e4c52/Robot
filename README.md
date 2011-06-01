## Robot project

### Config
You can set some configuration directives in the file _headers/constants.h_ like:
* Map blocks number
  * Width
  * Height
* Enable SDL
* Size of the window
  * Width
  * Height
* Size of the right sidebar
  * Width
  * Padding
  
### Moves
The robot knows its position and the exit position.
It doesn't know where the walls are located until it's in front of.
The robot has a memory and knows where it has already walked.

The robot **is not** allowed to return on its steps except if it is stuck.

The robot is always trying to move first horizontally to the exit then vertically to the exit.

If the bot is stuck, it will switch in *random mod*.
Once it has a direction, it will follow this one until the number of random moves has reached
the maximum of random move allowed in the same direction. Then, it gets a new direction randomly.

When in *random mod*, if the robot is able to perform a non-blocking move to reach the exit, it will do. 
