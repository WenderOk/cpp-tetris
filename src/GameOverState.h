#pragma once

#include "GameState.h"
#include "Game.h"
#include "HighScoreManager.h"
#include "HighScoreManager.h"

class GameOverState: public GameState
{
    int finalScore;
public:
    GameOverState(int score): finalScore(score)
    {
        HighScoreManager::saveIfHigher(finalScore);
    }

    void handleInput(Game& game) override;
    void update(Game& game, double deltaTime) override;
    void render(const Game& game) const override;
};