#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Graphics.hpp>
#include "board.hpp"


class Game
{
    public:
                                Game();
        int                 run();
     
    private:
        
        sf::RenderWindow    gameWindow;
        sf::Text            score_text;
        sf::Font            arial;
        sf::Texture         background_t;
        sf::Sprite          background_s;
        
        bool                running;
        int                 score;
    
        Board               board;
    
    private:
        void                manageEvents(sf::Event);
        void                show();
        void                reset();
};


#endif /* end of include guard: _GAME_HPP_ */
