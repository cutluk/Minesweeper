//
//  Tile.cpp
//  MineSweeper
//
//  Created by Luke Cutting on 4/4/22.
//  Copyright © 2022 Luke Cutting. All rights reserved.
//

#include "Tile.h"
#include "Board.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

Tile::Tile(){
    is_hidden=true;
    is_mine=false;
    is_flag=false;
    is_empty=false;
    end_game=false;
    debugMine=false;
};

Board board;

bool Tile::checkMine(vector<vector<Tile> >& tilesVect,int i, int j){

//Checks top Neighbors

    if(tilesVect[i-1][j-1].is_mine){
        return true;
    }
    if(tilesVect[i][j-1].is_mine){
        return true;
    }
    if(tilesVect[i+1][j-1].is_mine){
        return true;
    }
    //Checks middle neighbors
    if(tilesVect[i-1][j].is_mine){
        return true;
    }
    if(tilesVect[i+1][j].is_mine){
        return true;
    }
    //Check bottom neighbors
    if(tilesVect[i-1][j+1].is_mine||tilesVect[i][j+1].is_mine||tilesVect[i+1][j+1].is_mine){
        return true;
    }
return false;
}

int Tile::numberOfMines(vector<vector<Tile> >& tilesVect,int i, int j){
    int count=0;
        if(tilesVect[i-1][j-1].is_mine){
            count++;
        }
        if(tilesVect[i][j-1].is_mine){
            count++;
        }
        if(tilesVect[i+1][j-1].is_mine){
            count++;
        }
        if(tilesVect[i-1][j].is_mine){
            count++;
        }
        if(tilesVect[i+1][j].is_mine){
            count++;
        }
        if(tilesVect[i-1][j+1].is_mine){
            count++;
        }
        if(tilesVect[i][j+1].is_mine){
            count++;
        }
        if(tilesVect[i+1][j+1].is_mine){
            count++;
        }
    return count;
}
