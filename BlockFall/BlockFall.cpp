#include "BlockFall.h"
#include "Block.h"

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

void BlockFall::create_rotations(Block*& head_block,Block* next_block){

    Block* newRotation = new Block(); // Rotated new block

    Block* last_block = head_block->left_rotation;

    //newRotation->shape = newRotation->rotateShape(last_block);

    //cout<<"ERROR 1"<<endl;
    //cout<<"newRotation : "<<newRotation<<endl;
    //cout<<"newRotation->shape.size() : "<<newRotation->shape.size()<<endl;
    //cout<<"newRotation->shape[0].size() : "<<newRotation->shape[0].size()<<endl;
    //cout<<"ERROR 2"<<endl;

    vector<vector<bool>> tempShape = newRotation->rotateShape(last_block); //ERROR HERE !!!!!
    vector<bool> tempRow;
    
    for(int i=0;i<tempShape.size();i++){
        for(int j=0;j<tempShape[0].size();j++){
            tempRow.push_back(tempShape[i][j]);
        }
        newRotation->shape.push_back(tempRow);
        tempRow.clear();
    }

    last_block->right_rotation = newRotation;
    newRotation->left_rotation = last_block;
    head_block->left_rotation = newRotation;
    newRotation->right_rotation = head_block;

    newRotation->next_block = head_block->next_block;
    head_block->next_block = head_block->next_block;
}

void BlockFall::read_blocks(const string &input_file) {
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    // TODO: For every block, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.
    // TODO: Initialize the "power_up" member variable as the last block from the input file (do not add it to the linked list!)
    int cnt=0;
    blockFile.open(input_file,ios::in);
    if(blockFile.is_open()){
        string tempLine="";
        string blockLine="";
        while (getline(blockFile,tempLine))
        {
            right_strip_string(tempLine);
            if(tempLine!=""){
                if(tempLine[tempLine.length()-1]==']'){
                    blockLine=blockLine+tempLine+",";
                    Block* newBlock = new Block(); 
                    newBlock->shape = convertShape(blockLine);
                    if(initial_block==nullptr){
                        initial_block = newBlock;
                        for(int i=0;i<3;i++){
                            create_rotations(initial_block,nullptr);
                        }
                    }
                    else{
                        
                        Block* tempHead=initial_block;
                        while(tempHead->next_block!=nullptr){
                            tempHead=tempHead->next_block;
                        }
                        tempHead->next_block=newBlock;
                        active_rotation = tempHead;

                        for(int r=0;r<4;r++){
                            active_rotation->next_block = newBlock;
                            active_rotation=active_rotation->right_rotation;
                        }
                        //cout<<"BLOCKFALL READ_BLOCKS : SINGLE LINKAGE HAS EXECUTED!"<<endl;

                        for(int i=0;i<3;i++){
                            create_rotations(newBlock,nullptr);
                        }
                        //cout<<"BLOCKFALL READ_BLOCKS : ROTATIONAL LINKAGE HAS EXECUTED!"<<endl;
                    }

                    active_rotation=initial_block;

                    blockLine="";
                    //cout<<"BLOCKFALL READ_BLOCKS : BLOCK HAS BEEN CREATED!"<<endl;
                }
                else{
                    blockLine=blockLine+tempLine+",";
                }
            }
        }
        Block* tempHead = initial_block;
        while(tempHead->next_block->next_block!=nullptr){
            tempHead=tempHead->next_block;
        }

        power_up = tempHead->next_block->shape;
        delete tempHead->next_block;
        tempHead->next_block = nullptr;

        blockFile.close();       
    }
}

void BlockFall::initialize_grid(const string &input_file) {
    // TODO: Initialize "rows" and "cols" member variables
    // TODO: Initialize "grid" member variable using the command-line argument 1 in main
    
    gridFile.open(input_file,ios::in);
    string tempLine="";
    vector<int> tempRow;
    if(gridFile.is_open()){
        while(getline(gridFile,tempLine)){
            for(int i=0;i<tempLine.size();i++){
                if(tempLine[i]=='1'){
                    tempRow.push_back(1);
                }
                else if(tempLine[i]=='0'){
                    tempRow.push_back(0);
                }
            }
            grid.push_back(tempRow);
            tempRow.clear();
        }
        rows=grid.size();
        cols=grid[0].size();
    }
    gridFile.close(); 

}

void BlockFall::print_grid(bool printScore){
    
    if(printScore){
        std::cout<<"Score: "<<current_score<<std::endl;
        std::cout<<"High Score: "<<leaderboard.getHighscore()<<std::endl;
    }
    else{
        std::cout<<"Before clearing:"<<endl;
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(active_rotation!=nullptr){
                if(active_rotation->x<=j && j<active_rotation->x + active_rotation->shape[0].size()){
                    if(active_rotation->y<=i && i<active_rotation->y + active_rotation->shape.size()){
                        if(active_rotation->shape[i-active_rotation->y][j-active_rotation->x]==0){
                            //std::cout<<grid[i][j]; // Change this to occupied cells!!!!!
                            if(grid[i][j]==1){
                                std::cout<< (occupiedCellChar);
                            }
                            else if(grid[i][j]==0){
                                std::cout<< (unoccupiedCellChar);
                            }
                        }
                        else{
                            //std::cout<<active_rotation->shape[i-active_rotation->y][j-active_rotation->x];
                            if(active_rotation->shape[i-active_rotation->y][j-active_rotation->x]==1){
                                std::cout<< (occupiedCellChar);
                            }
                            else if(active_rotation->shape[i-active_rotation->y][j-active_rotation->x]==0){
                                std::cout<< (unoccupiedCellChar);
                            }
                        }
                        
                    }
                    else{
                        //std::cout<<grid[i][j];
                        
                        if(grid[i][j]==1){
                            std::cout<< (occupiedCellChar);
                        }
                        else if(grid[i][j]==0){
                            std::cout<< (unoccupiedCellChar);
                        }
                        
                    }
                }
                else{
                    //std::cout<<grid[i][j];
                    
                    if(grid[i][j]==1){
                        std::cout<<occupiedCellChar;
                    }
                    else if(grid[i][j]==0){
                        std::cout<<unoccupiedCellChar;
                    }
                    
                }
            }
            else{
                //std::cout<<grid[i][j];

                if(grid[i][j]==1){
                    std::cout<<occupiedCellChar;
                }
                else if(grid[i][j]==0){
                    std::cout<<unoccupiedCellChar;
                }
            }
        }
        std::cout<<"\n";
    }
    std::cout<<"\n"<<std::endl;
}

void BlockFall::rotate_right(){
    Block* rotatedBlock = active_rotation->right_rotation;
    if(rotatedBlock->x <= grid.size() - rotatedBlock->shape[0].size()){
        int temp_x = active_rotation->x;
        int temp_y = active_rotation->y;
        active_rotation=active_rotation->right_rotation;
        active_rotation->x = temp_x;
        active_rotation->y = temp_y;
    }
}

void BlockFall::rotate_left(){   
        int temp_x = active_rotation->x;
        int temp_y = active_rotation->y;
        active_rotation=active_rotation->left_rotation;
        active_rotation->x = temp_x;
        active_rotation->y = temp_y;
}

void BlockFall::move_right(){
    if(active_rotation->x < grid[0].size() - active_rotation->shape[0].size()){ // check if the initial block is in the right as it can goes.
       
        active_rotation->x += 1;
        if(!(check_collapses(active_rotation,grid))){
            active_rotation->x -= 1;
        }
    }
}

void BlockFall::move_left(){
    if(active_rotation->x>0){ // check if the initial block is in the left most corner
        active_rotation->x -= 1;
        if(!(check_collapses(active_rotation,grid))){
            active_rotation->x += 1;
        }
    }
}

bool BlockFall::check_collapses(Block* block,vector<vector<int>> lay){
    for(int i=0;i<block->shape.size();i++){
        for(int j=0;j<block->shape[0].size();j++){
            if(block->shape[i][j]==1){
                if(lay[i+ block->y][j+ block->x]==1){
                    return false;
                }
            }
        }
    }
    return true;
}

void BlockFall::write_grid(Block*& block){

    for(int i=0;i<block->shape.size();i++){
        for(int j=0;j<block->shape[0].size();j++){
            if(block->shape[i][j]==1){
                if(grid[i + block->y][j + block->x]==0){
                    grid[i + block->y][j + block->x] = 1;
                }
                else{
                    cout<<"ERROR IN WRITE_GRID "<<i + block->y<<"-"<<+ j + block->x <<" BLOCKFALL.CPP   BLOCK : "<<grid[i + block->y][j + block->x]<<endl;
                }
            }
        }
    }
}

bool BlockFall::is_powerup(vector<vector<bool>> pattern,vector<vector<int>> lay,int si,int sj){
    for(int i=0; i<pattern.size();i++){
        for(int j=0; j<pattern[0].size();j++){
            if(pattern[i][j]!=lay[si+i][sj+j]){
                return false;
            }
        }
    }
    return true;
}

bool BlockFall::recognize_powerup(vector<vector<bool>> pattern, vector<vector<int>> lay){

    for(int si=0; si <= lay.size()-pattern.size();si++){
        for(int sj=0; sj <= lay[0].size()-pattern[0].size();sj++){
            if(is_powerup(pattern,lay,si,sj)){
                return true;
            }
        }
    }
    return false;

}

void BlockFall::clear_grid(vector<vector<int>>& lay){
    for(int i=0; i<lay.size();i++){
        for(int j=0; j<lay[0].size();j++){
            lay[i][j]=0;
        }
    }
}

int BlockFall::countFilled(vector<vector<int>> matrix){
    int cnt=0;
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            if(matrix[i][j]==1){
                cnt++;
            }
        }
    }
    return cnt;
}

bool BlockFall::check_row(vector<int> row){
    for(int i=0;i<row.size();i++){
        if(row[i]==0){
            return false;
        }
    }
    return true;
}

int BlockFall::clear_rows(vector<vector<int>>& lay){

    vector<int> drop_rows;

    for(int i=0;i<lay.size();i++){
        if(check_row(lay[i])){
            drop_rows.push_back(i);
        }
    }

    for(int j=0;j<drop_rows.size();j++){
        lay.erase(lay.begin()+drop_rows[j]);
        lay.insert(lay.begin(),vector<int>(lay[0].size(),0));
    }

    return drop_rows.size();

}

bool BlockFall::check_finished(vector<vector<int>> lay){
    for(int i=0;i<grid[0].size();i++){
        if(grid[0][i]==1){
            return true;
        }
    }
    return false;
}

void BlockFall::print_grid_lose(){
    std::cout<<"GAME OVER!"<<std::endl;
    cout<<"Next block that couldn't fit:"<<endl;
    active_rotation=active_rotation->next_block;
    for(int i=0;i<active_rotation->shape.size();i++){
        for(int j=0;j<active_rotation->shape[0].size();j++){
            if(active_rotation->shape[i][j]==1){
                cout<<occupiedCellChar;
                //change this to occupied cells !!!!!!!
            }
            else{
                cout<<unoccupiedCellChar; // change this to occupied cells !!!!!!!
            }
        }
        cout<<endl;
    }
    cout<<endl;

    std::cout<<"Score: "<<current_score<<std::endl;
    std::cout<<"High Score: "<<leaderboard.getHighscore()<<std::endl;

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            //std::cout<<grid[i][j]; // Change this to occupied cells!!!!!
            if(grid[i][j]==1){
                std::cout<<occupiedCellChar;
            }
            else{
                std::cout<<unoccupiedCellChar;
            }
        }
        std::cout<<"\n";
    }
}

int BlockFall::drop(){

    for(int i=0;i< grid.size()-active_rotation->shape.size();i++){
        active_rotation->y += 1;
        if(check_collapses(active_rotation,grid)){
            //active_rotation->y += 1;
        }
        else{
            //cout<<"COLLAPSED!!!!!"<<endl;
            active_rotation->y -= 1;
            break;
        }
    }

    current_score += (active_rotation->countFilled())*(active_rotation->y);
    write_grid(active_rotation);

    //Gravity function
    if(gravity_mode_on){
        for(int i=grid.size()-1;i>=0;i--){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    grid[i][j]=0;
                    grid[find_new_drop_pos(i,j,grid)][j]=1;
                }
            }
        }
    }
    
    //Recogniziton part 
    if(recognize_powerup(power_up,grid)){
        current_score+=1000;
        current_score += (countFilled(grid));
        print_grid(false);
        clear_grid(grid);
    }
    else{
        int cleared_rows = clear_rows(grid);
        if(cleared_rows!=0){
            print_grid(true);
            current_score += cleared_rows*(grid[0].size());
        }
        
        
    }

    if(check_finished(grid)){
        //cout<<"YOU HAVE LOST THE GAME. THE GRID IS FULL."<<endl;
        print_grid_lose();
        leaderboard.insert_new_entry(new LeaderboardEntry(current_score,time(nullptr),player_name));
        leaderboard.write_to_file(leaderboard_file_name);
        return -1;
    }
    //initial_block=initial_block->next_block;
    active_rotation=active_rotation->next_block;

    if(active_rotation==nullptr){ // Finished all the blocks.
        //cout<<"YOU HAVE WON THE GAME !!! ALL BLOCKS ARE FINISHED !!!"<<endl;
        leaderboard.insert_new_entry(new LeaderboardEntry(current_score,time(nullptr),player_name));
        leaderboard.write_to_file(leaderboard_file_name);
        return 1;
    }
    /*
    else{
        //cout<<"GAME CONTINUES..."<<endl;
        return 0;
    }
    */
    return 0;
    
}

int BlockFall::find_new_drop_pos(int i ,int j ,vector<vector<int>> lay){
    int new_pos=i;
    
    for(int new_i=i+1;new_i<lay.size();new_i++){
        if(lay[new_i][j]==1){
            break;
        }
        else{
            new_pos=new_i;
        }
    }
    return new_pos;

}

void BlockFall::gravity_switch(){
    gravity_mode_on = !(gravity_mode_on);
    if(gravity_mode_on){
        for(int i=grid.size()-1;i>=0;i--){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    grid[i][j]=0;
                    grid[find_new_drop_pos(i,j,grid)][j]=1;
                }
            }
        }
    }

    if(recognize_powerup(power_up,grid)){
        current_score+=1000;
        current_score += (countFilled(grid));
        print_grid(false);
        clear_grid(grid);
    }
    else{
        print_grid(false);
        current_score += clear_rows(grid)*(grid[0].size());
    }

}

BlockFall::~BlockFall() {
    // TODO: Free dynamically allocated memory used for storing game blocks

    Block* currBlock = initial_block;
    while(currBlock!=nullptr){
        Block* tempHead = currBlock;
        do {
            Block* tlr = tempHead->left_rotation;
            tempHead->left_rotation = tlr->left_rotation;
            if (currBlock == tlr) {
                currBlock = tempHead->left_rotation;
            }
            if (tlr->right_rotation != nullptr) {
                tlr->right_rotation->left_rotation = tlr->left_rotation;
            }

            delete tlr;
        } while (tempHead->left_rotation != tempHead);

        currBlock=currBlock->next_block;
        delete tempHead;
    }
}
