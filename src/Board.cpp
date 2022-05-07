//
//  Board.cpp
//  MineSweeper
//
//  Created by Luke Cutting on 4/4/22.
//  Copyright © 2022 Luke Cutting. All rights reserved.
//

#include "Board.h"
#include "Tile.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>


using namespace std;
using namespace sf;

Board::Board(){};

Tile tile;

void Board::IntializeBoard(){
    
    getConfig("boards/config.cfg");
    
    int mines = mineCount;

    debugButton=false;
    
    tileCount = windowHeight*windowWidth;
    Height=windowHeight;
    Width=windowWidth;

    windowWidth*=32;
    windowHeight=(32*windowHeight)+100;
    
    middle=(Width/2)-1;
    Tile tile;
    
    for(int i=0; i<=Width+1; i++){
        vector<Tile> column;
        for(int j=0; j<=Height+1; j++){
                column.push_back(tile);
                }
            tilesVect.push_back(column);
            }

    while(mines>0){
        for(int i=1;i<=Width;i++){
            for(int j=1;j<=Height;j++){
                if(mines>0 && tilesVect[i][j].is_mine==false){
                    int val=rand()%100;
                    if(val==7){
                        tilesVect[i][j].is_mine=true;
                        mines--;
                    }
                }
            }
        }
    }
    won=false;
}

void Board::IntializeTestBoard(string board){
    
    getConfig("boards/config.cfg");
    mineCount=0;
    debugButton=false;
    tileCount = windowHeight*windowWidth;
    Height=windowHeight;
    Width=windowWidth;
    windowWidth*=32;
    windowHeight=(32*windowHeight)+100;
    middle=(Width/2)-1;
    Tile tile;
    
    for(int i=0; i<=Width+1; i++){
        vector<Tile> column;
        for(int j=0; j<=Height+1; j++){
                column.push_back(tile);
                }
            tilesVect.push_back(column);
            }
    
    readTestBoard(board);
}

void Board::PrintBoard(RenderWindow& window,Vector2i& mousePosition){
bool reveal=true;
loadImages();

for(int i=1,a=0; i<=Width; i++,a++){
    for(int j=1,b=0; j<=Height; j++,b++){
        
        if(won){
            displayWin(mousePosition);
        }
        if(tile.end_game){
            displayLost(mousePosition);
        }
        
        if(tilesVect[i][j].is_empty){
            EmptyTile(i,j);
        }
        if(tilesVect[i][j].is_flag){
            tileH.setPosition(a*32,b*32);
            window.draw(tileH);
            flag.setPosition(a*32,b*32);
            window.draw(flag);
            if(tilesVect[i][j].debugMine){
                mine.setPosition(a*32,b*32);
                window.draw(mine);
            }
            continue;
        }
        if(tilesVect[i][j].debugMine){
            tileH.setPosition(a*32,b*32);
            window.draw(tileH);
            mine.setPosition(a*32,b*32);
            window.draw(mine);
        }
        else if(tilesVect[i][j].is_hidden){
            tileH.setPosition(a*32,b*32);
            window.draw(tileH);
        }
            
        else{
            if(tilesVect[i][j].is_mine){
                tileR.setPosition(a*32,b*32);
                window.draw(tileR);
                mine.setPosition(a*32,b*32);
                window.draw(mine);
                tile.end_game=true;
            }
            else if(tile.checkMine(tilesVect,i,j)){
                tileR.setPosition(a*32,b*32);
                window.draw(tileR);
                
                int numOfMines = tile.numberOfMines(tilesVect,i,j);
                switch(numOfMines){
                    case 1:
                        tile1.setPosition(a*32,b*32);
                        window.draw(tile1);
                        break;
                    case 2:
                        tile2.setPosition(a*32,b*32);
                        window.draw(tile2);
                        break;
                    case 3:
                        tile3.setPosition(a*32,b*32);
                        window.draw(tile3);
                        break;
                    case 4:
                        tile4.setPosition(a*32,b*32);
                        window.draw(tile4);
                        break;
                    case 5:
                        tile5.setPosition(a*32,b*32);
                        window.draw(tile5);
                        break;
                    case 6:
                        tile6.setPosition(a*32,b*32);
                        window.draw(tile6);
                        break;
                    case 7:
                        tile7.setPosition(a*32,b*32);
                        window.draw(tile7);
                        break;
                    case 8:
                        tile8.setPosition(a*32,b*32);
                        window.draw(tile8);
                        break;
                    }
            }else{
                tileR.setPosition(a*32,b*32);
                window.draw(tileR);
                tilesVect[i][j].is_empty=true;
                }
            }
        }
    }
    setBottom(window);
    
    if(checkWin()){
        won=true;
    }
}

void Board::RevealTile(RenderWindow& window, Vector2i& mousePos){
    
    int x = mousePos.x;
    int y = mousePos.y;
    x/=32;
    y/=32;
    
    if(won==false && tile.end_game==false){
        checkDebug(x,y);
        
        tilesVect[x+1][y+1].is_hidden = false;
    }
    
    checkTest1(x,y);
    checkTest2(x,y);
    checkTest3(x,y);
    
}

void Board::loadImages(){
    tileRevealed.loadFromFile("images/tile_revealed.png");
    tileHidden.loadFromFile("images/tile_hidden.png");
    tileMine.loadFromFile("images/mine.png");
    tile1T.loadFromFile("images/number_1.png");
    tile2T.loadFromFile("images/number_2.png");
    tile3T.loadFromFile("images/number_3.png");
    tile4T.loadFromFile("images/number_4.png");
    tile5T.loadFromFile("images/number_5.png");
    tile6T.loadFromFile("images/number_6.png");
    tile7T.loadFromFile("images/number_7.png");
    tile8T.loadFromFile("images/number_8.png");
    happyFace.loadFromFile("images/face_happy.png");
    wonFaceT.loadFromFile("images/face_win.png");
    loseFaceT.loadFromFile("images/face_lose.png");
    debugT.loadFromFile("images/debug.png");
    test1T.loadFromFile("images/test_1.png");
    test2T.loadFromFile("images/test_2.png");
    test3T.loadFromFile("images/test_3.png");
    flagT.loadFromFile("images/flag.png");
    d0.loadFromFile("images/digits.png",IntRect(0,0,21,32));
    d1.loadFromFile("images/digits.png",IntRect(21,0,21,32));
    d2.loadFromFile("images/digits.png",IntRect(42,0,21,32));
    d3.loadFromFile("images/digits.png",IntRect(63,0,21,32));
    d4.loadFromFile("images/digits.png",IntRect(84,0,21,32));
    d5.loadFromFile("images/digits.png",IntRect(105,0,21,32));
    d6.loadFromFile("images/digits.png",IntRect(126,0,21,32));
    d7.loadFromFile("images/digits.png",IntRect(147,0,21,32));
    d8.loadFromFile("images/digits.png",IntRect(168,0,21,32));
    d9.loadFromFile("images/digits.png",IntRect(189,0,21,32));
    dNeg.loadFromFile("images/digits.png",IntRect(210,0,21,32));
    
    
    tileH.setTexture(tileHidden);
    tileR.setTexture(tileRevealed);
    mine.setTexture(tileMine);
    tile1.setTexture(tile1T);
    tile2.setTexture(tile2T);
    tile3.setTexture(tile3T);
    tile4.setTexture(tile4T);
    tile5.setTexture(tile5T);
    tile6.setTexture(tile6T);
    tile7.setTexture(tile7T);
    tile8.setTexture(tile8T);
    faceHappy.setTexture(happyFace);
    debug.setTexture(debugT);
    test1.setTexture(test1T);
    test2.setTexture(test2T);
    test3.setTexture(test3T);
    flag.setTexture(flagT);
    digit0.setTexture(d0);
    digit1.setTexture(d1);
    digit2.setTexture(d2);
    digit3.setTexture(d3);
    digit4.setTexture(d4);
    digit5.setTexture(d5);
    digit6.setTexture(d6);
    digit7.setTexture(d7);
    digit8.setTexture(d8);
    digit9.setTexture(d9);
    digitNeg.setTexture(dNeg);
    wonFace.setTexture(wonFaceT);
    lostFace.setTexture(loseFaceT);
}

void Board::setBottom(RenderWindow& window){

    Digits(window);
    
    if(won){
        wonFace.setPosition(middle*32,Height*32);
        window.draw(wonFace);
    }else if(tile.end_game){
        lostFace.setPosition(middle*32,Height*32);
        window.draw(lostFace);
    }else{
        faceHappy.setPosition(middle*32,Height*32);
        window.draw(faceHappy);
    }
    
    debug.setPosition((middle*32)+128,Height*32);
    window.draw(debug);
    
    test1.setPosition((middle*32)+192,Height*32);
    window.draw(test1);
    
    test2.setPosition((middle*32)+256,Height*32);
    window.draw(test2);
    
    test3.setPosition((middle*32)+318,Height*32);
    window.draw(test3);
    
}

void Board::setFlag(Vector2i& mousePosition){
    if(won==false && tile.end_game==false){
        loadImages();
        
        int x = mousePosition.x;
        int y = mousePosition.y;
        x/=32;
        y/=32;
        x++;
        y++;
        
        if(tilesVect[x][y].is_hidden||tilesVect[x][y].is_flag){
            if(tilesVect[x][y].is_flag){
                tilesVect[x][y].is_flag = false;
                mineCount++;
            }else{
                tilesVect[x][y].is_flag = true;
                mineCount--;
            }
        }
    }
}

void Board::EmptyTile(int a, int b){
    
    if(tilesVect[a-1][b-1].is_mine==false){
        tilesVect[a-1][b-1].is_hidden = false;
    }
    if(tilesVect[a-1][b].is_mine==false){
        tilesVect[a-1][b].is_hidden = false;
    }
    if(tilesVect[a-1][b+1].is_mine==false){
        tilesVect[a-1][b+1].is_hidden = false;
    }
    
    if(tilesVect[a][b-1].is_mine==false){
        tilesVect[a][b-1].is_hidden = false;
    }
    if(tilesVect[a][b+1].is_mine==false){
        tilesVect[a][b+1].is_hidden = false;
    }
   
    if(tilesVect[a+1][b-1].is_mine==false){
        tilesVect[a+1][b-1].is_hidden = false;
    }
    if(tilesVect[a+1][b].is_mine==false){
        tilesVect[a+1][b].is_hidden = false;
    }
    if(tilesVect[a+1][b+1].is_mine==false){
        tilesVect[a+1][b+1].is_hidden = false;
    }
}

void Board::Digits(RenderWindow& window){
    
    int digitDisplay = mineCount;
    
    if(mineCount<0){
        digitNeg.setPosition(0,Height*32);
        window.draw(digitNeg);
        digitDisplay=-digitDisplay;
    }
    int a = digitDisplay%10;
    digitDisplay/=10;
    int b = digitDisplay%10;
    digitDisplay/=10;
    int c = digitDisplay%10;
    
    switch(c){
    case 0:
        digit0.setPosition(16,Height*32);
        window.draw(digit0);
        break;
    case 1:
        digit1.setPosition(16,Height*32);
        window.draw(digit1);
        break;
    case 2:
        digit2.setPosition(16,Height*32);
        window.draw(digit2);
        break;
    case 3:
        digit3.setPosition(16,Height*32);
        window.draw(digit3);
        break;
    case 4:
        digit4.setPosition(16,Height*32);
        window.draw(digit4);
        break;
    case 5:
        digit5.setPosition(16,Height*32);
        window.draw(digit5);
        break;
    case 6:
        digit6.setPosition(16,Height*32);
        window.draw(digit6);
        break;
    case 7:
        digit7.setPosition(16,Height*32);
        window.draw(digit7);
        break;
    case 8:
        digit8.setPosition(16,Height*32);
        window.draw(digit8);
        break;
    case 9:
        digit9.setPosition(16,Height*32);
        window.draw(digit9);
        break;
}
    switch(b){
    case 0:
        digit0.setPosition(37,Height*32);
        window.draw(digit0);
        break;
    case 1:
        digit1.setPosition(37,Height*32);
        window.draw(digit1);
        break;
    case 2:
        digit2.setPosition(37,Height*32);
        window.draw(digit2);
        break;
    case 3:
        digit3.setPosition(37,Height*32);
        window.draw(digit3);
        break;
    case 4:
        digit4.setPosition(37,Height*32);
        window.draw(digit4);
        break;
    case 5:
        digit5.setPosition(37,Height*32);
        window.draw(digit5);
        break;
    case 6:
        digit6.setPosition(37,Height*32);
        window.draw(digit6);
        break;
    case 7:
        digit7.setPosition(37,Height*32);
        window.draw(digit7);
        break;
    case 8:
        digit8.setPosition(37,Height*32);
        window.draw(digit8);
        break;
    case 9:
        digit9.setPosition(37,Height*32);
        window.draw(digit9);
        break;
}
    switch(a){
        case 0:
            digit0.setPosition(58,Height*32);
            window.draw(digit0);
            break;
        case 1:
            digit1.setPosition(58,Height*32);
            window.draw(digit1);
            break;
        case 2:
            digit2.setPosition(58,Height*32);
            window.draw(digit2);
            break;
        case 3:
            digit3.setPosition(58,Height*32);
            window.draw(digit3);
            break;
        case 4:
            digit4.setPosition(58,Height*32);
            window.draw(digit4);
            break;
        case 5:
            digit5.setPosition(58,Height*32);
            window.draw(digit5);
            break;
        case 6:
            digit6.setPosition(58,Height*32);
            window.draw(digit6);
            break;
        case 7:
            digit7.setPosition(58,Height*32);
            window.draw(digit7);
            break;
        case 8:
            digit8.setPosition(58,Height*32);
            window.draw(digit8);
            break;
        case 9:
            digit9.setPosition(58,Height*32);
            window.draw(digit9);
            break;
}
}

void Board::getConfig(string filePath){
    ifstream inFile(filePath);
    if (inFile.is_open()){
    string val1,val2,val3;
        getline(inFile, val1);
        getline(inFile, val2);
        getline(inFile, val3);
    
        windowWidth = stoi(val1);
        windowHeight = stoi(val2);
        mineCount = stoi(val3);
    }
    
}

bool Board::checkWin(){
    if(debugButton){
        return false;
    }
    for(int i=1; i<=Width; i++){
        for (int j=1; j<=Height; j++){
            if(tilesVect[i][j].is_hidden==false || tilesVect[i][j].is_mine){
                continue;
            }else{
                return false;
            }
        }
    }return true;
}

void Board::displayWin(Vector2i& mousePosition){
    for(int i=1; i<=Width; i++){
        for (int j=1; j<=Height; j++){
            tilesVect[i][j].is_hidden=false;
            if(tilesVect[i][j].is_mine){
                tilesVect[i][j].is_flag=true;
                mineCount=0;
            }
        }
    }
    int x = mousePosition.x;
    int y = mousePosition.y;
    x/=32;
    y/=32;
    x++;
    y++;
    
    if(Mouse::isButtonPressed(Mouse::Left)){
        if((x==middle+1 && y == Height+1)||(x==middle+2 && y==Height+1)||(x==middle+1&&y==Height+2)||(x==middle+2&&y==Height+2)){
            
            tilesVect.clear();
            IntializeBoard();
            tilesVect.clear();
            IntializeBoard();
            won=false;
    }
        
      
    }
}

void Board::displayLost(Vector2i& mousePosition){
    
    for(int i=1; i<=Width; i++){
        for (int j=1; j<=Height; j++){
            if(tilesVect[i][j].is_mine){
                tilesVect[i][j].is_hidden=false;
            }
        }
    }
    int x = mousePosition.x;
    int y = mousePosition.y;
    x/=32;
    y/=32;
    x++;
    y++;
    
    if(Mouse::isButtonPressed(Mouse::Left)){
        if((x==middle+1 && y == Height+1)||(x==middle+2 && y==Height+1)||(x==middle+1&&y==Height+2)||(x==middle+2&&y==Height+2)){
            
            tilesVect.clear();
            IntializeBoard();
            tilesVect.clear();
            IntializeBoard();
            tile.end_game=false;
    }
      
    }
}

void Board::checkDebug(int x, int y){
    if((x==middle+4 && y==Height)||(x==middle+5 && y==Height)||(x==middle+4 && y==Height+1)||(x==middle+5 && y==Height+1)){
        if(debugButton==false){
            for(int i=0;i<=Width+1;i++){
                for(int j=0;j<=Height+1;j++){
                    if(tilesVect[i][j].is_mine){
                        tilesVect[i][j].debugMine=true;
                    }
                }
            }
            debugButton=true;
        }else{
            for(int i=0;i<=Width+1;i++){
                for(int j=0;j<=Height+1;j++){
                    tilesVect[i][j].debugMine=false;
                }
            }
            debugButton=false;
        }
    }
}

void Board::checkTest1(int x, int y){
    if((x==middle+6 && y==Height)||(x==middle+7 && y==Height)||(x==middle+6 && y==Height+1)||(x==middle+7 && y==Height+1)){
        tilesVect.clear();
        IntializeTestBoard("boards/testboard1.brd");
        tile.end_game=false;
        won=false;
        }
}

void Board::checkTest2(int x, int y){
    if((x==middle+8 && y==Height)||(x==middle+9 && y==Height)||(x==middle+8 && y==Height+1)||(x==middle+9 && y==Height+1)){
        tilesVect.clear();
        IntializeTestBoard("boards/testboard2.brd");
        tile.end_game=false;
        won=false;
        }
}

void Board::checkTest3(int x, int y){
    if((x==middle+10 && y==Height)||(x==middle+11 && y==Height)||(x==middle+10 && y==Height+1)||(x==middle+11 && y==Height+1)){
        tilesVect.clear();
        IntializeTestBoard("boards/testboard3.brd");
        tile.end_game=false;
        won=false;
        }
}

void Board::readTestBoard(string filePath){
    ifstream inFile(filePath);
    if (inFile.is_open()){
        string line;
        char c;
        
        for(int j=0;j<Height;j++){
            getline(inFile, line);
            for(int i=0;i<line.size(); i++){
                c = line[i];
                if(c=='1'){
                    tilesVect[i+1][j+1].is_mine=true;
                    mineCount++;
                }
            }
        }
    }
}
