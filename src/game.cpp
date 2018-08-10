#include "game.hpp"
#include <iostream>

Game::Game()
: gameWindow(sf::VideoMode(500, 600), "2048 - Por Satore")
, score_text()
, arial()
, background_t()
, background_s()
, running(true)
, score(0) 
, board()
{
    //Set the position of the board
    board.setPosition(50,150);

    //Load background texture, sprite and setting its position
    background_t.loadFromFile("res/background.png");
    background_s.setTexture(background_t);
    background_s.setPosition(0, 0);
    
    //Loading font from file
    arial.loadFromFile("res/arial.ttf");
    
    //Setting up text
    score_text.setFont(arial);
    score_text.setCharacterSize(20);

    //Se1tting the position of the score text
    score_text.setPosition(375,90);
}

//Game loop
int Game::run()
{
    sf::Event event;
    while(running)
    {
        show();
        manageEvents(event);
    }
    gameWindow.close();
    return 0;
}

void Game::manageEvents(sf::Event event)
{
    while(gameWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                running = false;
                return;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    score += board.move(LEFT);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    score += board.move(UP);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    score += board.move(RIGHT);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    score += board.move(DOWN);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                    reset();
                break;
            default:
                    break;
        }
        if(!running) return;
    }
}

void Game::reset()
{
    score = 0;
    board.reset();
}

void Game::show()
{
    //Updating text position and origin so it's centered
    score_text.setString(std::to_string(score));
    sf::FloatRect bounds = score_text.getLocalBounds();
    score_text.setOrigin( bounds.left + bounds.width/2 , 
                            bounds.top + bounds.height/2 );
    //Clearing window and drawing all objects
    gameWindow.clear();
    gameWindow.draw(background_s);
    gameWindow.draw(board);
    gameWindow.draw(score_text);
    //Display the drawed window
    gameWindow.display();
}