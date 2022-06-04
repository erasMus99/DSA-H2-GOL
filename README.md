# DSA-H2-GOL

Repo for the second homework of DSA at Algebra University - Game Of Life

---

For this homework, we needed to do [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++.
We we're allowed to use any methods we wanted but it was better if SFML was used.

Unfortunatly i wasn't able to create the game with SFML but used [SDL](https://www.libsdl.org/) as I'm more familiar
with it due to EPITA's project.

I also tried to do some cross compilation so that you could have an executable but failed.

---

In order to show that my code and game is working I did a screen record so that you can see the execution.

First we do ```g++ Source.cpp Cell.cpp -w -lSDL2 -g -o gol```
Then ```./gol```
And TADA !

![](./Images/execution.gif)
