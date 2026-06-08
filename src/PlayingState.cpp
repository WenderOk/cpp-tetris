#include "PlayingState.h"
#include "Block.h"
#include "InputHandler.h"
#include "Game.h"
#include <cstdlib>

void PlayingState::spawnNewBlock(Game& game)
{

    currentBlock = Block::createRandom(game.getField().getWidth());

    if(game.getField().hasCollision(currentBlock, 0, 0))
    {
        // TODO: В будущем здесь будет game.setState(std::make_unique<GameOverState>());
        // Пока для простоты можно просто очистить поле и начать заново
        exit(0);
        game.getField().clearLines(); // Очистит всё, если поле забито
        currentBlock = Block::createRandom(game.getField().getWidth());
    }

    lastFallTime = std::chrono::steady_clock::now();
}

void PlayingState::handleInput(Game& game)
{
    if(!game.getInput().kbhit()) return;

    char key = game.getInput().getch();
    int x{currentBlock.getX()};
    int y{currentBlock.getY()};

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
        game.getField().clearLines();
        spawnNewBlock(game);
        
        lastFallTime = std::chrono::steady_clock::now(); // сброс таймера
    }
}

void PlayingState::update(Game& game, double deltaTime)
{       
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFallTime).count();

    if (elapsed >= fallInterval)
    {
        if (!game.getField().hasCollision(currentBlock, 0, 1))
            currentBlock.move(0, 1);
        else
        {
            game.getField().lockBlock(currentBlock);
            game.getField().clearLines();
            spawnNewBlock(game);
        }
        lastFallTime = std::chrono::steady_clock::now();
    }
}

void PlayingState::render(const Game& game) const
{
    game.getRenderer().draw(game.getField(), currentBlock);
}
