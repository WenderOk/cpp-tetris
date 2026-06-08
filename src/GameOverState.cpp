#include "GameOverState.h"
#include "Game.h"
#include "PlayingState.h"
#include <memory>

void GameOverState::handleInput(Game& game)
{
    if(!game.getInput().kbhit()) return;

    char key{ game.getInput().getch() };

    if(key == 'r' || key == 'R')
        game.setState(std::make_unique<PlayingState>(game));
    else if (key == 'q' || key == 'Q')
        game.stop();
}

void GameOverState::update(Game& game, double deltaTime)
{/* В состоянии Game Over логика игры не обновляется*/ }

void GameOverState::render(const Game& game) const {
    game.getRenderer().clearScreen();
    
    std::cout << "\n\n";
    std::cout << "   ==================================\n";
    std::cout << "   =           GAME OVER            =\n";
    std::cout << "   ==================================\n";
    std::cout << "\n";
    std::cout << "      YOUR FINAL SCORE: " << finalScore << "\n\n";
    std::cout << "   Press [R] to Restart\n";
    std::cout << "   Press [Q] to Quit\n";
    std::cout << "   ==================================\n";
}