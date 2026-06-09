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
    std::cout << "   \e[0;101m==================================\e[0m\n";
    std::cout << "   \e[0;101m=           GAME OVER            =\e[0m\n";
    std::cout << "   \e[0;101m==================================\e[0m\n\n";
    std::cout << "      YOUR FINAL SCORE: " << finalScore << "\n\n";
    std::cout << "   \e[41mPress [R] to Restart              \e[0m\n";
    std::cout << "   \e[41mPress [Q] to Quit                 \e[0m\n";
    std::cout << "   \e[0;101m==================================\e[0m\n";
}