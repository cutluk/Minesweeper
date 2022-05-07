//
//  Board.h
//  MineSweeper
//
//  Created by Luke Cutting on 4/4/22.
//  Copyright © 2022 Luke Cutting. All rights reserved.
//

#ifndef Board_h
#define Board_h
#include "Tile.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Board{
    vector<vector<Tile> > tilesVect;
    
public:
    Texture tileHidden,tileRevealed,tileMine,tile1T,tile2T,tile3T,tile4T,tile5T,tile6T,tile7T,tile8T,happyFace,debugT,test1T,test2T,test3T,flagT,d0,d1,d2,d3,d4,d5,d6,d7,d8,d9,dNeg,wonFaceT,loseFaceT;
    Sprite tileR,tileH,mine,tile1,tile2,tile3,tile4,tile5,tile6,tile7,tile8,faceHappy,debug,test1,test2,test3,flag,digit0,digit1,digit2,digit3,digit4,digit5,digit6,digit7,digit8,digit9,digitNeg,wonFace,lostFace;
    
    
    int windowHeight;
    int windowWidth;
    int Height;
    int Width;
    int mineCount;
    int tileCount;
    int middle;
    
    bool debugButton;
    bool won=false;
    
    
    
    Board();
    
    void PrintBoard(sf::RenderWindow& window,Vector2i& mousePosition);
    
    void RevealTile(RenderWindow& window, Vector2i& mousePosition);
    
    void IntializeBoard();
    
    void IntializeTestBoard(string board);
    
    void loadImages();
    
    void setBottom(RenderWindow& window);
    
    void setFlag(Vector2i& mousePosition);
    
    void EmptyTile(int a,int b);
    
    void Digits(RenderWindow& window);
    
    void getConfig(string fileName);
    
    bool checkWin();
    
    void displayWin(Vector2i& mousePosition);
    
    void displayLost(Vector2i& mousePosition);
    
    void checkDebug(int x, int y);
    
    void checkTest1(int x, int y);
    
    void checkTest2(int x, int y);
    
    void checkTest3(int x, int y);
    
    void readTestBoard(string fileName);
};


#endif /* Board_h */
