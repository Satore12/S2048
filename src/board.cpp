#include "board.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

//Constructor for Board class
Board::Board()
{
    //Load the textures of the tiles from file
    tilesTexture.loadFromFile("res/tiles.png");
    
    //Create a sprite for each tile type and load its specific texture
    for(int i = 0; i < 12; i++)
    {
        tilesSprite[i].setTexture(tilesTexture);
        tilesSprite[i].setPosition(0, 0);
        tilesSprite[i].setTextureRect(sf::IntRect(i*100, 0, 100 ,100));
    }
    
    //Initialize the board grid with 0 in all its places
    for(int i = 0; i < BOARD_MAX_COLUMNS; i++)
    {
        for(int j = 0; j < BOARD_MAX_ROWS; j++)
        {
            board_matrix[i][j] = 0;
        }
    }
    
    //Set randon seed according to time
    srand(time(NULL));
    
    //Generating 2 new tiles with value 1 -> 2
    generateRandom();
    generateRandom();
}

//Draw the board
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Combine the transform of the board and the given transform
    states.transform *= getTransform();

    //Looping trough all tiles
    for(int i = 0; i < BOARD_MAX_COLUMNS; i++)
    {
        for(int j = 0; j < BOARD_MAX_ROWS; j++)
        {
            //Going to the specific point in the screen
            // in wich to draw the needed sprite
            states.transform.translate(i*TILE_SIZE, j*TILE_SIZE);
            target.draw(tilesSprite[board_matrix[i][j]], states);
            states.transform.translate(-i*TILE_SIZE, -j*TILE_SIZE);
        }
    }
}

//Generate a value 1(2) tile in a random place
void Board::generateRandom()
{
    //If board is full then exit the function
    if(isFull()) return;
    
    //looping trough do/while loop until it finds an empty space
    int x, y;
    do
    {
        x = rand()%4;
        y = rand()%4;
    }while(board_matrix[x][y] != 0);
    board_matrix[x][y] = 1;
}

//Move the board in the indicated direction and then if a tile has ben moved
// make it possible to have new tiles generated(1 or 2)
//Sum up the values of the combined tiles to get the newscore
int Board::move(Direction d)
{
    int score = 0;
    bool moved = false;
    switch(d)
    {
        case UP:
            for(int i = 0; i < BOARD_MAX_COLUMNS; i++)
            {
                for(int j = 1; j < BOARD_MAX_ROWS; j++)
                {
                    if(board_matrix[i][j] != 0)
                    {
                        int value = board_matrix[i][j];
                        
                        for(int y = j - 1; y >= 0; y--)
                        {
                            if(board_matrix[i][y] == 0)
                            {
                                board_matrix[i][y] = value;
                                board_matrix[i][y+1] = 0;
                                moved = true;
                            }else if(board_matrix[i][y] == value)
                            {
                                board_matrix[i][y] = value + 1;
                                score += pow(2, value + 1);
                                board_matrix[i][y+1] = 0;
                                moved = true;
                                break;
                            }else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        break;
        case DOWN:
            for(int i = 0; i < BOARD_MAX_COLUMNS; i++)
            {
                for(int j = BOARD_MAX_ROWS - 2; j >= 0; j--)
                {
                    if(board_matrix[i][j] != 0)
                    {
                        int value = board_matrix[i][j];
                        
                        for(int y = j + 1; y < BOARD_MAX_ROWS; y++)
                        {
                            if(board_matrix[i][y] == 0)
                            {
                                board_matrix[i][y] = value;
                                board_matrix[i][y - 1] = 0;
                                moved = true;
                            }else if(board_matrix[i][y] == value)
                            {
                                board_matrix[i][y] = value + 1;
                                score += pow(2, value + 1);
                                board_matrix[i][y - 1] = 0;
                                moved = true;
                                break;
                            }else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        break;
        case RIGHT:
            for(int j = 0; j < BOARD_MAX_ROWS ; j++)
            {
                for(int i = BOARD_MAX_COLUMNS - 2; i >= 0; i--)
                {
                    if(board_matrix[i][j] != 0)
                    {
                        int value = board_matrix[i][j];
                        for(int x = i + 1; x < BOARD_MAX_COLUMNS; x++)
                        {
                            if(board_matrix[x][j] == 0)
                            {
                                board_matrix[x][j] = value;
                                board_matrix[x - 1][j] = 0;
                                moved = true;
                            }else if(board_matrix[x][j] == value)
                            {
                                board_matrix[x][j] = value + 1;
                                score += pow(2, value + 1);
                                board_matrix[x - 1][j] = 0;
                                moved = true;
                                break;
                            }else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        break; 
        case LEFT:
            for(int j = 0; j < BOARD_MAX_ROWS; j++)
            {
                for(int i = 1; i < BOARD_MAX_COLUMNS; i++)
                {
                    if(board_matrix[i][j] != 0)
                    {
                        int value = board_matrix[i][j];
                        for(int x = i - 1; x >= 0; x--)
                        {
                            if(board_matrix[x][j] == 0)
                            {
                                board_matrix[x][j] = value;
                                board_matrix[x + 1][j] = 0;
                                moved = true;
                            }else if(board_matrix[x][j] == value) 
                            {
                                board_matrix[x][j] = value + 1;
                                score += pow(2, value + 1);
                                board_matrix[x + 1][j] = 0;
                                moved = true;
                                break;
                            }else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        break;
        default:
        ;
    }
    if(moved&&rand()<((RAND_MAX/4)*3))
    {   
        generateRandom();
        if(rand()<RAND_MAX/2)
            generateRandom();
    }
    return score;
}

//Check if board is full
bool Board::isFull()
{
    for(int i = 0; i < BOARD_MAX_COLUMNS; i++)
    {
        for(int j = 0; j < BOARD_MAX_ROWS; j++)
        {
            if(board_matrix[i][j] == 0)
                return false;
        }
    }
    return true;
}

void Board::reset()
{
    //Initialize the board grid with 0 in all its places
    for(int i = 0; i < BOARD_MAX_COLUMNS; i++)
    {
        for(int j = 0; j < BOARD_MAX_ROWS; j++)
        {
            board_matrix[i][j] = 0;
        }
    }
    generateRandom();
    generateRandom();
}