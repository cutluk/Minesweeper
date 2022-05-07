#include <iostream>
#include "Board.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <vector>


using namespace std;
using namespace sf;

int main(){
    
    Board board;
    Tile tile;
    
        
    board.IntializeBoard();
   
    RenderWindow window(VideoMode(board.windowWidth,board.windowHeight), "Minesweeper");
    window.setFramerateLimit(120);
    
   
    
    while(window.isOpen()){
        Event event;
        
        Vector2i mousePosition = Mouse::getPosition(window);
        
        while (window.pollEvent(event)) {
            if(event.type==Event::Closed){
                window.close();
                }
            if (event.type == sf::Event::MouseButtonPressed){
                if (Mouse::isButtonPressed(Mouse::Left)){
                    board.RevealTile(window, mousePosition);
                    }
                if(Mouse::isButtonPressed(Mouse::Right)){
                    Vector2i mousePositionright = Mouse::getPosition(window);
                    board.setFlag(mousePositionright);
                }
                
            }
        }
        window.clear();
        
        board.PrintBoard(window,mousePosition);
        
        window.display();
    
    }
    return EXIT_SUCCESS;
    }
