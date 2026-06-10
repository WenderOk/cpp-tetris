#include "PlayingState.h"
#include "GameOverState.h"
#include "Block.h"
#include "InputHandler.h"
#include "Game.h"
#include "Colors.h"

void PlayingState::spawnNewBlock(Game& game)
{

    currentBlock = Block::createRandom(game.getField().getWidth());

    if(game.getField().hasCollision(currentBlock, 0, 0))
    {
        game.setState(std::make_unique<GameOverState>(score));
        return;
    }    

    lastFallTime = std::chrono::steady_clock::now();
}

void PlayingState::handleInput(Game& game)
{
    if(!game.getInput().hasInput()) return;

    char key = game.getInput().readChar();
    int x{currentBlock.getX()};
    int y{currentBlock.getY()};

    
    if (key == 'f' || key == 'F') 
    {
        isPaused = !isPaused;
        #ifdef _WIN32
          system("cls");
        #endif
        return;
    }
    
    if (key == 'q' || key == 'Q') 
    {
        game.stop();
        return;
    }

    if (isPaused) return;

    if (key == 'a' || key == 'A')
    {
        if (!game.getField().hasCollision(currentBlock, -1, 0))
            currentBlock.move(-1, 0);
    }
    else if (key == 'd' || key == 'D')
    {
        if (!game.getField().hasCollision(currentBlock, 1, 0))
            currentBlock.move(1, 0);
    }
    else if (key == 'w' || key == 'W')
    {
        Block rotated{ currentBlock.getRotated() };
        
        if (!game.getField().hasCollision(rotated, 0, 0))
            currentBlock = rotated;
    }
    else if (key == 's' || key == 'S')
    {
        // Мгновенное падение (drop)
        while (!game.getField().hasCollision(currentBlock, 0, 1))
            currentBlock.move(0, 1);
        game.getField().lockBlock(currentBlock);
        int cleared{ game.getField().clearLines() };
        if(cleared > 0)
        {
            linesCleared+=cleared;
            int points[]{0, 100, 300, 500, 800};
            score += points[cleared] * level;
            level = (linesCleared / 10) + 1;
            fallInterval = std::max(100, 500 - (level - 1) * 50);
        }
        spawnNewBlock(game);
        
        lastFallTime = std::chrono::steady_clock::now(); // сброс таймера
    }
}

void PlayingState::update(Game& game, double deltaTime)
{       
    if(isPaused) return;

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFallTime).count();

    if (elapsed >= fallInterval)
    {
        if (!game.getField().hasCollision(currentBlock, 0, 1))
            currentBlock.move(0, 1);
        else
        {
            game.getField().lockBlock(currentBlock);
            int cleared{ game.getField().clearLines() };
            if(cleared > 0)
            {
                linesCleared+=cleared;
                int points[]{0, 100, 300, 500, 800};
                score += points[cleared] * level;
                level = (linesCleared / 10) + 1;
                fallInterval = std::max(100, 500 - (level - 1) * 50);
            }
            
            spawnNewBlock(game);
        }
        lastFallTime = std::chrono::steady_clock::now();
    }
}

void PlayingState::render(const Game& game) const
{
    if (isPaused) 
    {
        game.getRenderer().clearScreen();
        const int width{30};

        std::cout << "\n\n";
        std::cout << "   " << BG_BGREEN << FG_WHITE << "╔" << std::setfill('-') << std::setw(width - 2) << "" << "╗" << RESET << "\n";
        
        std::cout << "   " << BG_BGREEN << FG_WHITE << "║" 
                << std::setfill(' ') << std::setw(11) << "" 
                << BOLD << "PAUSED" << RESET << BG_BGREEN << FG_WHITE
                << std::setw(11) << "" << "║" << RESET << "\n";
                
        std::cout << "   " << BG_BGREEN << FG_WHITE << "╚" << std::setfill('-') << std::setw(width - 2) << "" << "╝" << RESET << "\n";

        std::cout << "\n" << std::setfill(' ');
        std::cout << std::setw(8) << "" << "Press [" << BOLD << "F" << RESET << "] to Resume\n";
        std::cout << std::setw(8) << "" << "Press [" << BOLD << "Q" << RESET << "] to Quit\n\n";
        return;
    }

    game.getRenderer().draw(game.getField(), currentBlock, score, level, linesCleared);
}
