#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {

private:

    vector<vector<bool>> mirrorVectorHorizontal(vector<vector<bool>> org_vector){
        vector<vector<bool>> mirroredVector;
        vector<bool> tempRow;

        for(int i=0;i<org_vector.size();i++){
            for(int j=0;j<org_vector[i].size();j++){
                tempRow.push_back(org_vector[i][org_vector[i].size()-1-j]);
            }
            mirroredVector.push_back(tempRow);
            tempRow.clear();
        }

        return mirroredVector;
    }

    vector<vector<bool>> transposeVector(vector<vector<bool>> org_vector){
        vector<vector<bool>> transposed;
        //(org_vector[0].size(),vector<bool>(org_vector.size(),0));
        for(int i=0;i<org_vector.at(0).size();i++){
            vector<bool> tempRow;
            for(int j=0;j<org_vector.size();j++){
                tempRow.push_back(0);
            }
            transposed.push_back(tempRow);
            tempRow.clear();
        }

        for(int i=0;i<org_vector.size();i++){
            for(int j=0;j<org_vector[i].size();j++){
                transposed[j][i] = org_vector[i][j];
            }
        }
        return transposed;
    }

public:

    vector<vector<bool>> shape; // Two-dimensional vector corresponding to the block's shape
    Block * right_rotation = this; // Pointer to the block's clockwise neighbor block (its right rotation) // I CHANGD THIS FROM NULLPOINTER
    Block * left_rotation = this; // Pointer to the block's counter-clockwise neighbor block (its left rotation) // I CHANGD THIS FROM NULLPOINTER
    Block * next_block = nullptr; // Pointer to the next block to appear in the game

    int x=0;
    int y=0;
    
    bool operator==(const Block& other) const {
        // TODO: Overload the == operator to compare two blocks based on their shapes

        //first check the dimension of two shapes
        if((this->shape.size()!=other.shape.size()) && (this->shape[0].size()!= other.shape[0].size())){
            //their sizes are same , let's check their shapes
            for(int i=0;i<other.shape.size();i++){
                for(int j=0;j<other.shape[i].size();j++){
                    if(this->shape[i][j] != other.shape[i][j]){
                        return false;
                    }
                }
            }
            return true;
        }   

        return false;
    }

    bool operator!=(const Block& other) const {
        // TODO: Overload the != operator to compare two blocks based on their shapes
        return !(*(this) == other);
    }

    Block(){
        return ;
    }

    Block(vector<vector<bool>> genShape){
        this->shape=genShape;
    }

    /*
    vector<vector<bool>> rotateShape(Block*& org_block){
        vector<vector<bool>> rotatedShape;
        rotatedShape = transposeVector(org_block->shape);
        rotatedShape = mirrorVectorHorizontal(rotatedShape);
        return rotatedShape;
    }
    */

   vector<vector<bool>> rotateShape(Block*& org_block){
        vector<vector<bool>> rotatedShape;
        rotatedShape = transposeVector(org_block->shape);
        rotatedShape = mirrorVectorHorizontal(rotatedShape);
        return rotatedShape;
    }

    Block rotateBlock(){
        Block rotatedBlock;
        rotatedBlock.shape = transposeVector(shape);
        rotatedBlock.shape = mirrorVectorHorizontal(rotatedBlock.shape);
        return rotatedBlock;
    }

    int countFilled(){
        int cnt=0;
        for(int i=0;i<shape.size();i++){
            for(int j=0;j<shape[0].size();j++){
                if(shape[i][j]==1){
                    cnt++;
                }
            }
        }
        return cnt;
    }


    
};


#endif //PA2_BLOCK_H
