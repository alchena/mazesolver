#ifndef DEPTHSOLVE_HPP
#define DEPTHSOLVE_HPP

#include "MazeSolver.hpp"
#include <vector>
class DepthSolve : public MazeSolver
{
public:
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
private:
    void recursion(std::vector<std::vector<bool>> pathArray, 
    const Maze& maze, MazeSolution& mazeSolution, int row, int col);
    bool visited(const std::vector<std::vector<bool>>& mazeArray, int row, int col);
};

#endif