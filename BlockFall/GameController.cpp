#include "GameController.h"
#include <fstream>
#include <string>
#include <iostream>

bool GameController::play(BlockFall& game, const string& commands_file){

    // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
    //       argument. The return value represents if the gameplay was successful or not: false if game over,
    //       true otherwise.
    int gameStatus=0;
    fstream cmd_file;
    cmd_file.open(commands_file,ios::in);
    string currCommand="";

    if(cmd_file.is_open()){
        while(getline(cmd_file,currCommand))
        {
            //Trimming the string from escape characters.
            string escapeChars=" \t\f\v\n\r";
            size_t lns = currCommand.find_last_not_of(escapeChars);
            if (lns != std::string::npos) {
                currCommand.erase(lns + 1);
            }

            if(currCommand=="PRINT_GRID"){
                game.print_grid(true);
            }
            else if(currCommand=="ROTATE_RIGHT"){
                game.rotate_right();
            }
            else if(currCommand=="ROTATE_LEFT"){
                game.rotate_left();
            }
            else if(currCommand=="MOVE_RIGHT"){
                game.move_right();
            }
            else if(currCommand=="MOVE_LEFT"){
                game.move_left();
            }
            else if(currCommand=="DROP"){
                gameStatus=game.drop();
                if(gameStatus==0){
                    // Game has ended successfully
                    //std::cout<<"GAME IS STILL TERMINATING "<<std::endl;
                }
                else if(gameStatus==-1){
                    // Losing the game
                    game.leaderboard.print_leaderboard();
                    std::cout<<"\n\n\n";

                    cmd_file.close();
                    return false;
                }
                else if(gameStatus==1){
                    // Finished all the blocks
                    std::cout<<"YOU WIN!"<<std::endl;
                    std::cout<<"No more blocks."<<std::endl;
                    std::cout<<"Final grid and score:"<<std::endl;
                    std::cout<<"\n";
                    game.print_grid(true);
                    game.leaderboard.print_leaderboard();
                    std::cout<<"\n\n\n";   

                    cmd_file.close();                 
                    return true;
                }

            }
            else if(currCommand=="GRAVITY_SWITCH"){
                game.gravity_switch();
            }
            else{
                std::cout<<"ERROR!!! YOU HAVE GIVEN A WRONG INPUT."<<std::endl;
                std::cout<<currCommand;
            }

        }
        
        std::cout<<"GAME FINISHED!"<<std::endl;
        std::cout<<"No more commands."<<std::endl;
        std::cout<<"Final grid and score:"<<std::endl;
        std::cout<<"\n";
        game.print_grid(true);
        game.leaderboard.print_leaderboard();
        game.leaderboard.insert_new_entry(new LeaderboardEntry(game.current_score,time(nullptr),game.player_name));
        game.leaderboard.write_to_file(game.leaderboard_file_name);
        std::cout<<"\n\n\n";
        cmd_file.close();
        return true;


    }

    cmd_file.close();
    return false;
}



