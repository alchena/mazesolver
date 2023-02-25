#ifndef DEPTHGEN_HPP
#define DEPTHGEN_HPP
#include "MazeGenerator.hpp"
#include "Direction.hpp"

#include <vector>
#include <random>
class DepthGen : public MazeGenerator
{
public:
    void generateMaze(Maze& maze) override;
    
private:
    void tunneling(std::vector<std::vector<bool>>& mazeArray, 
    Maze& maze, std::default_random_engine& engine, int row, int col);

    bool visited(const std::vector<std::vector<bool>>& mazeArray, int row, 
    int col);
};

#endif