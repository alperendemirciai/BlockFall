#ifndef PA2_LEADERBOARD_H
#define PA2_LEADERBOARD_H
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "LeaderboardEntry.h"

#define MAX_LEADERBOARD_SIZE 10

using namespace std;

class Leaderboard {
public:
    LeaderboardEntry* head_leaderboard_entry = nullptr;
    fstream leaderboardFile;
    void read_from_file(const string &filename);
    void write_to_file(const string &filename);
    void print_leaderboard();
    void insert_new_entry(LeaderboardEntry *new_entry);

    vector<string> parseString(string line);

    void right_strip_string(string& raw){
        string escapeChars=" \t\f\v\n\r";
        if(raw.empty()){
            return;
        }
        size_t lns = raw.find_last_not_of(escapeChars);
        if (lns != std::string::npos) {
            raw.erase(lns + 1);
        }
    }

    void deleteTail();

    int getHighscore () {
        if(head_leaderboard_entry==nullptr){
            return 0;
        }
        else{
            return head_leaderboard_entry->score;
        }
    }   

    int length = 0;

    virtual ~Leaderboard();
};


#endif //PA2_LEADERBOARD_H
