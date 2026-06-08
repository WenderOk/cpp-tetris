#pragma once

#include "Block.h"
#include "GameState.h"
#include <chrono>

class PlayingState: public GameState
{
    Block currentBlock;
    std::chrono::steady_clock::time_point lastFallTime;

    int fallInterval;
    int score;
    int linesCleared;
    int level;
    
    void spawnNewBlock(Game& game);
public:
    PlayingState() 
        : currentBlock{Block::createRandom(10)}, 
          lastFallTime{std::chrono::steady_clock::now()}, 
          fallInterval{500},
          score{},
          linesCleared{0},
          level{1}
    {}
    void handleInput(Game& game) override;
    void update(Game& game, double deltaTime) override;
    void render(const Game& game) const override;

    int getScore() const { return score; }
    int getLevel() const { return level; }
};