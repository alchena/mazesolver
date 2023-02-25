#include "DepthGen.hpp"
#include "Maze.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, DepthGen, "DepthGen (Required)");

void DepthGen::generateMaze(Maze& maze){
    maze.addAllWalls();
    std::vector<bool> cols(maze.getWidth(), false);
    std::vector<std::vector<bool>> mazeArray(maze.getHeight(), cols);

    //create a random engine
    std::random_device device;
    std::default_random_engine engine{device()};

    tunneling(mazeArray,maze,engine,0,0);
}

void DepthGen::tunneling(std::vector<std::vector<bool>>& mazeArray, 
Maze& maze, std::default_random_engine& engine, int row, int col){

    //mark cell
    mazeArray[row][col] = true;

    int newCol;
    int newRow;
    
    //get possible directions
    std::vector<Direction> directions;
    if(row+1 < maze.getHeight()){
        if(!visited(mazeArray, row+1, col)){
            directions.push_back(Direction::down);
        }
    }
    if(row-1 >= 0) {
        if(!visited(mazeArray, row-1, col)){
            directions.push_back(Direction::up);
        }
    }
    if(col+1 < maze.getWidth()){
        if(!visited(mazeArray, row, col+1)){
            directions.push_back(Direction::right);
        }
    }
    if(col-1 >= 0) {
        if(!visited(mazeArray, row, col-1)){
            directions.push_back(Direction::left);
        }
    }
    
    //while there are directions
    while(directions.size() > 0){
        
        //random distribution
        std::uniform_int_distribution<int> distribution{0,(int)directions.size()-1};
        int nextElem = distribution(engine);
    
        //choose random direction from the directions vector
        Direction nextDir = directions[nextElem];
        
        //check which direction was chosen to find next newRow
        if(nextDir == Direction::down){
            newRow = row+1;
            newCol = col;
        }
        if(nextDir == Direction::up){
            newRow = row-1;
            newCol = col;
        }
        if(nextDir == Direction::right){
            newRow = row;
            newCol = col+1;
        }
        if(nextDir == Direction::left){
            newRow = row;
            newCol = col-1;
        }

        //remove wall  
        if (!visited(mazeArray, newRow, newCol)){
            maze.removeWall(col, row, nextDir);
        }
        
        //remove executed direction and resize the array
        directions.erase(std::remove(directions.begin(), directions.end(), nextDir), directions.end());

        //recursive call
        tunneling(mazeArray, maze, engine, newRow, newCol);
    }
}

//check if the given cell has been visisted
bool DepthGen::visited(const std::vector<std::vector<bool>>& mazeArray, int row, int col){
    return mazeArray[row][col];
}

