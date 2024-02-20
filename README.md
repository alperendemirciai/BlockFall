## Directory for Compilation ##
The code should be compiled inside the BlockFall folder.
Location for compilation : ...\BlockFall\


## How to Compile ##
This code compiles all the .cpp and .h files and creates an executable named as blockfall.
```
$ g++ -std=c++11 main.cpp Block.h BlockFall.h BlockFall.cpp GameController.h
GameController.cpp LeaderboardEntry.h LeaderboardEntry.cpp Leaderboard.h Leaderboard.cpp -o blockfall
```

## How to Run ##
After the compilation, you can run the game with necessary inputs by typing this following command:
```
$ ./blockfall grid.dat blocks.dat commands.dat GRAVITY_ON leaderboard.txt BlockBuster
```

Remember that this version of the game is not written for active gameplay, it's just an assignment for Data Structures class.
Please check the PA2.pdf for detailed explanation.
