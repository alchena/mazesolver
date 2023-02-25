#include "DepthSolve.hpp"
#include "Direction.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "MazeSolutionException.hpp"
#include <algorithm>
#include <vector>
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, DepthSolve, "DepthSolve (Required)");

void DepthSolve::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
    std::vector<bool> cols(maze.getWidth(), false);
    std::vector<std::vector<bool>> pathArray(maze.getHeight(), cols);
    recursion(pathArray, maze, mazeSolution, 0, 0);
}

//recursion for mazeSolution similar to DepthGen
void DepthSolve::recursion(std::vector<std::vector<bool>> pathArray, 
const Maze& maze, MazeSolution& mazeSolution, int row, int col){    
    pathArray[row][col] = true;

    //before recursion begins check to see if maze is complete;
    if(mazeSolution.isComplete()){
        return;
    }

    //get the available directions, directions are available if
    // 1. theres no wall between this one and the cell in that direction
    // 2. row and col are within bounds
    // 3. the next cell has not been visited yet

    std::vector<Direction> directions;
    if(row+1 < maze.getHeight() && !maze.wallExists(col, row, Direction::down)
        && !visited(pathArray, row+1, col)){
        directions.push_back(Direction::down);
    }
    if(row-1 >= 0 && !maze.wallExists(col, row, Direction::up)
       && !visited(pathArray, row-1, col)){
        directions.push_back(Direction::up);
    }
    if(col+1 < maze.getWidth() && !maze.wallExists(col, row, Direction::right)
        && !visited(pathArray, row, col+1)){
        directions.push_back(Direction::right);
    }
    if(col-1 >= 0 && !maze.wallExists(col, row, Direction::left)
        && !visited(pathArray, row, col-1)){
        directions.push_back(Direction::left);
    }

    if(directions.size() == 0){
        mazeSolution.backUp();
        return;
    }

    int newRow;
    int newCol;
    while(directions.size() > 0){

        //introduce bottom right bias
        Direction nextDir;
        if (std::find(directions.begin(), directions.end(), Direction::down) != directions.end()){
            nextDir = Direction::down;
        }
        else if(std::find(directions.begin(), directions.end(), Direction::right) != directions.end()){
            nextDir = Direction::right;
        } else {
            nextDir = directions[0];
        }
    
    //check which direction was chosen to find next newRow
        if(nextDir == Direction::down){
            newRow = row+1;
            newCol = col;
            mazeSolution.extend(Direction::down);
        }
        if(nextDir == Direction::up){
            newRow = row-1;
            newCol = col;
            mazeSolution.extend(Direction::up);
        }
        if(nextDir == Direction::right){
            newRow = row;
            newCol = col+1;
            mazeSolution.extend(Direction::right);
        }
        if(nextDir == Direction::left){
            newRow = row;
            newCol = col-1;
            mazeSolution.extend(Direction::left);
        }
        //after direction has been done, erase and resize vector
        directions.erase(std::remove(directions.begin(), directions.end(), nextDir), directions.end());
        //recursively call this function with the next cell
        recursion(pathArray, maze, mazeSolution, newRow, newCol);
        
        //if the maze is complete after the recursion is finished return
        if(mazeSolution.isComplete()){
            return;
        }

        //if not then check to see if direction vector is empty
        //if it is empty this means this path is back at the beginning
        if(directions.size() == 0){
            try{
                mazeSolution.backUp();
                return;
            } catch(MazeSolutionException){
                return;
            }
        }
    }
}

bool DepthSolve::visited(const std::vector<std::vector<bool>>& pathArray, int row, int col){
    return pathArray[row][col];
}