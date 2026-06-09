#include "GameOverState.h"
#include "Game.h"
#include "PlayingState.h"
#include <memory>

void GameOverState::handleInput(Game& game)
{
    if(!game.getInput().hasInput()) return;

    char key{ game.getInput().readChar() };

    if(key == 'r' || key == 'R')
        game.setState(std::make_unique<PlayingState>(game));
    else if (key == 'q' || key == 'Q')
        game.stop();
}

void GameOverState::update(Game& game, double deltaTime)
{/* В состоянии Game Over логика игры не обновляется*/ }

void GameOverState::render(const Game& game) const {
    game.getRenderer().clearScreen();
   
     int highScore = HighScoreManager::load();
    
    std::cout << "\n\n";
    std::cout << "   \033[0;101m==================================\033[0m\n";
    std::cout << "   \033[0;101m=           GAME OVER            =\033[0m\n";
    std::cout << "   \033[0;101m==================================\033[0m\n\n";
    std::cout << "      YOUR FINAL SCORE: " << finalScore << "\n";
    std::cout << "      YOUR BEST SCORE: " << highScore << "\n\n";
    std::cout << "   \033[41mPress [R] to Restart              \033[0m\n";
    std::cout << "   \033[41mPress [Q] to Quit                 \033[0m\n";
    std::cout << "   \033[0;101m==================================\033[0m\n";
}