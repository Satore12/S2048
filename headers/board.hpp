#ifndef __BOARD_HPP_
#define __BOARD_HPP_

#include <SFML/Graphics.hpp>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Board : public sf::Drawable, public sf::Transformable
{
    public:
        const static int    BOARD_MAX_ROWS = 4;
        const static int    BOARD_MAX_COLUMNS = 4;
        const static int    BOARD_WIDTH = 400;
        const static int    BOARD_HEIGHT = 400;
        const static int    TILE_SIZE = BOARD_WIDTH / BOARD_MAX_COLUMNS;
        
    public:        
        Board();
        int                 move(Direction);
        void                draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void                reset();
        
    private:    
        int                 board_matrix[BOARD_MAX_COLUMNS][BOARD_MAX_ROWS];
    
        sf::Texture         tilesTexture;
        sf::Sprite          tilesSprite[12];
        
    private:
        bool                isFull();
        void                generateRandom();
        
};

#endif /* end of include guard _BOARD_HPP_ */


