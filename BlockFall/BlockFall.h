#ifndef BLOCKFALL_H
#define BLOCKFALL_H

#define occupiedCellChar "██" // ██ 178u
#define unoccupiedCellChar "▒▒" // ▒▒ 176u

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Block.h"
#include "LeaderboardEntry.h" //CHANGE HERE !
#include "Leaderboard.h"  //CHANGE HERE !

using namespace std;

class BlockFall {

private:
    fstream blockFile;
    fstream gridFile;
    int gameStatus=0;
    vector<vector<bool>> convertShape(string blockStr){
        vector<vector<bool>> newShape ;
        vector<bool> newRow;
        if(blockStr.empty()==false){
            for(int i=0;i<blockStr.length();i++){
                if(blockStr[i]=='1'){
                    newRow.push_back(1);
                }
                else if(blockStr[i]=='0'){
                    newRow.push_back(0);
                }
                else if(blockStr[i]==','){
                    if(newRow.size()>0){
                        newShape.push_back(newRow);
                    }
                    newRow.clear();
                    newRow.shrink_to_fit();
                }
            }
        }

        return newShape;
    }

public:

    BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name,
              const string &player_name);
    virtual ~BlockFall();

    int rows;  // Number of rows in the grid
    int cols;  // Number of columns in the grid
    int score=0;
    int highscore=0;
    vector<vector<int> > grid;  // 2D game grid
    vector<vector<bool>> power_up; // 2D matrix of the power-up shape
    Block * initial_block = nullptr; // Head of the list of game blocks. Must be filled up and initialized after a call to read_blocks()
    Block * active_rotation = nullptr; // Currently active rotation of the active block. Must start with the initial_block
    bool gravity_mode_on = false; // Gravity mode of the game
    unsigned long current_score = 0; // Current score of the game
    string leaderboard_file_name; // Leaderboard file name, taken from the command-line argument 5 in main
    string player_name; // Player name, taken from the command-line argument 6 in main
    Leaderboard leaderboard; 

    void right_strip_string(string& raw){
        string escapeChars=" \t\f\v\n\r";
        if(raw.empty()) return; 
        size_t lns = raw.find_last_not_of(escapeChars);
        if (lns != std::string::npos) {
            raw.erase(lns + 1);
        }
    }

    
    void create_rotations(Block*& head,Block* next_block);
    void initialize_grid(const string & input_file); // Initializes the grid using the command-line argument 1 in main
    void read_blocks(const string & input_file); // Reads the input file and calls the read_block() function for each block;
    void print_grid(bool printScore); // Prints the grid
    void rotate_right();
    void rotate_left();
    void move_right();
    void move_left();

    int drop();

    void gravity_switch();

    bool check_collapses(Block* block,vector<vector<int>> lay);
    void write_grid(Block*& block);
    bool recognize_powerup(vector<vector<bool>> pattern, vector<vector<int>> lay);
    bool is_powerup(vector<vector<bool>> pattern,vector<vector<int>> lay,int si,int sj);
    void clear_grid(vector<vector<int>>& lay);

    int clear_rows(vector<vector<int>>& lay);
    bool check_row(vector<int> row);

    int countFilled(vector<vector<int>> matrix);

    int find_new_drop_pos(int i,int j,vector<vector<int>> lay);

    bool check_finished(vector<vector<int>> lay);

    void print_grid_lose();
};



#endif // BLOCKFALL_H
