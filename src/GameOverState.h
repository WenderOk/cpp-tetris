#pragma once

#include "GameState.h"

class GameOverState: public GameState
{
    int finalScore;
public:
    GameOverState(int score): finalScore(score)
    {}

    void handleInput(Game& game) override;
    void update(Game& game, double deltaTime) override;
    void render(const Game& game) const override;
};