# Ghostbusters - Assignment 2 OOP Fall 2022
This contains our second homework in which we had to design a game

To run the game, go on ghostbusters.cpp and press f5 (how to compile is also given - you can run the command in the terminal), or you can just simply run the a.exe file.
Make sure to read the rules of the game.

//**Ghostbusters**

The Ghost Busters is a tiny simple game to find position of a ghost, hidden
somewhere in the grid. Initially all the blocks in grid are locked, and then
the player clicks any of the block to get some information about the ghost
location. Here are the rules of various objects being displayed upon click:
- A snake is drawn if the clicked block is 0-1 blocks away from the ghost
- A turtle is drawn if the clicked block is 2-3 blocks away from the ghost
- A bunny is drawn if the clicked block is 4 blocks away from the ghost
- If the clicked block is more than 4 blocks away, a snake, turtle or a
bunny is drawn randomly.
After exploring certain blocks of the game, the player finally busts the
ghost with a right-click. If the ghost location was correct, then a ghost is
drawn on that block else the game is failed.

The Code provides the implementation of the game logic, the backend handling etc abt various stuff was given already.
