#include "GameOverState.h"
#include "Game.h"
#include "PlayingState.h"
#include <memory>
#include "Colors.h"

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

void GameOverState::render(const Game& game) const 
{
    game.getRenderer().clearScreen();
   
    int highScore = HighScoreManager::load();
    
    const int width{36};

    std::cout << "\n\n";
    std::cout << "   " << BG_BRED << FG_WHITE << "╔" << std::setfill('=') << std::setw(width - 2) << "" << "╗" << RESET << "\n";
    std::cout << "   " << BG_BRED << FG_WHITE << "║" 
              << std::setfill(' ') << std::setw(12) << "" 
              << BOLD << "GAME OVER" << RESET << BG_BRED << FG_WHITE
              << std::setw(13) << "" << "║" << RESET << "\n";
    std::cout << "   " << BG_BRED << FG_WHITE << "╠" << std::setfill('=') << std::setw(width - 2) << "" << "╣" << RESET << "\n";

    std::string scoreStr = "  YOUR FINAL SCORE: " + std::to_string(finalScore);
    std::string bestStr  = "  YOUR BEST SCORE:  " + std::to_string(highScore) ;

    std::cout << "   " << BG_BRED << FG_WHITE << "║" << std::left << std::setfill(' ') << std::setw(width - 2) << scoreStr << "║" << RESET << "\n";
    std::cout << "   " << BG_BRED << FG_WHITE << "║" << std::left << std::setfill(' ') << std::setw(width - 2) << bestStr << "║" << RESET << "\n";
    
    std::cout << "   " << BG_BRED << FG_WHITE << "╠" << std::setfill('=') << std::setw(width - 2) << "" << "╣" << RESET << "\n";

    std::string restartStr = "  Press [R] to Restart";
    std::string quitStr    = "  Press [Q] to Quit";

    std::cout << "   " << BG_BRED << FG_WHITE << "║" << std::left << std::setfill(' ') << std::setw(width - 2) << restartStr << "║" << RESET << "\n";
    std::cout << "   " << BG_BRED << FG_WHITE << "║" << std::left << std::setfill(' ') << std::setw(width - 2) << quitStr << "║" << RESET << "\n";

    std::cout << "   " << BG_BRED << FG_WHITE << "╚" << std::setfill('=') << std::setw(width - 2) << "" << "╝" << RESET << "\n\n";
}