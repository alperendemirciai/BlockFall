#include "Leaderboard.h"

vector<string> Leaderboard::parseString(string line) {
    right_strip_string(line);
    vector<string> parsedLine;
    string temp="";
    for(int i = 0; i < line.length(); i++){
        if(line[i] == ' '){
            parsedLine.push_back(temp);
            temp = "";
        }
        else{
            temp += line[i];
        }
    }
    parsedLine.push_back(temp);
    return parsedLine;
}

void Leaderboard::deleteTail(){
    LeaderboardEntry* tempHead = head_leaderboard_entry;
    while(tempHead->next_leaderboard_entry->next_leaderboard_entry!= nullptr){
        tempHead = tempHead->next_leaderboard_entry;
    }
    tempHead->next_leaderboard_entry = nullptr;
}

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    // TODO: Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
    //       is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
    //       top 10 all-time high-scores should be kept in descending order by the score).
    if(length<MAX_LEADERBOARD_SIZE){
        LeaderboardEntry* tempHead = head_leaderboard_entry;
        if(tempHead== nullptr){
            head_leaderboard_entry = new_entry;
            length++;
        }
        else{
            if (tempHead->score < new_entry->score) {
                new_entry->next_leaderboard_entry = tempHead;
                head_leaderboard_entry = new_entry;
                return;
            } 
            else{
                while(tempHead->next_leaderboard_entry!= nullptr){
                    if(tempHead->next_leaderboard_entry->score < new_entry->score){
                        new_entry->next_leaderboard_entry = tempHead->next_leaderboard_entry;
                        tempHead->next_leaderboard_entry = new_entry;
                        length++;
                        return;
                    }
                    else{
                        tempHead = tempHead->next_leaderboard_entry;
                    }
                }
                tempHead->next_leaderboard_entry = new_entry;
                length++;
            }
        }
    }
    else if (length == MAX_LEADERBOARD_SIZE) {
        LeaderboardEntry* tempHead = head_leaderboard_entry;
        if (tempHead->score < new_entry->score) {
            new_entry->next_leaderboard_entry = tempHead;
            head_leaderboard_entry = new_entry;
            deleteTail();
            return;
        } else {
            while (tempHead->next_leaderboard_entry != nullptr) {
                if (tempHead->next_leaderboard_entry->score < new_entry->score) {
                    new_entry->next_leaderboard_entry = tempHead->next_leaderboard_entry;
                    tempHead->next_leaderboard_entry = new_entry;
                    deleteTail();
                    return;
                } else {
                    tempHead = tempHead->next_leaderboard_entry;
                }
            }
            tempHead->next_leaderboard_entry = new_entry;
            deleteTail();
            return;
        }
    }
}

void Leaderboard::write_to_file(const string& filename) {
    // TODO: Write the latest leaderboard status to the given file in the format specified in the PA instructions
    leaderboardFile.open(filename,ios::out);
    if(leaderboardFile.is_open()){
        LeaderboardEntry* tempHead = head_leaderboard_entry;
        while(tempHead!= nullptr){
            leaderboardFile<<tempHead->score<<" "<<tempHead->last_played<<" "<<tempHead->player_name<<endl;
            tempHead = tempHead->next_leaderboard_entry;
        }
    }
    leaderboardFile.close();

}

void Leaderboard::read_from_file(const string& filename) {
    // TODO: Read the stored leaderboard status from the given file such that the "head_leaderboard_entry" member
    //       variable will point to the highest all-times score, and all other scores will be reachable from it
    //       via the "next_leaderboard_entry" member variable pointer.
    int cnt=0;
    leaderboardFile.open(filename,ios::in);
    if(leaderboardFile.is_open()){
        string line="";
        while(getline(leaderboardFile,line)){ //Test this with a file with 0 entry.
            if(cnt<MAX_LEADERBOARD_SIZE){
                vector<string> parsedLine = parseString(line);
                insert_new_entry(new LeaderboardEntry(stoi(parsedLine[0]),stoi(parsedLine[1]),parsedLine[2]));
                cnt++;
            }
        }
    }
    else{
        //cout<<"File not found"<<endl; // comment this!!!
    }
    leaderboardFile.close();
}


void Leaderboard::print_leaderboard() {
    // TODO: Print the current leaderboard status to the standard output in the format specified in the PA instructions
    LeaderboardEntry* tempHead = head_leaderboard_entry;
    char timeFormatted[100];
    std::cout<<"Leaderboard"<<std::endl;
    std::cout<<"-----------"<<std::endl;
    int order=1;
    while(tempHead!= nullptr){
        strftime(timeFormatted, 100, "%H:%M:%S/%d.%m.%Y", localtime(&tempHead->last_played));
        std::cout<<order++<<". "<<tempHead->player_name<<" "<<tempHead->score<<" "<<timeFormatted<<std::endl;
        tempHead = tempHead->next_leaderboard_entry;
    }
}

Leaderboard::~Leaderboard() {
    // TODO: Free dynamically allocated memory used for storing leaderboard entries
}
