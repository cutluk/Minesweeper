//
//  Tile.h
//  MineSweeper
//
//  Created by Luke Cutting on 4/4/22.
//  Copyright © 2022 Luke Cutting. All rights reserved.
//

#ifndef Tile_h
#define Tile_h
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Tile{
  
public:
    Tile();
    bool is_hidden;
    bool is_mine;
    bool is_flag;
    bool is_empty;
    bool end_game;
    bool debugMine;
   

    
    bool checkMine(vector<vector<Tile> >& tilesVect, int i, int j);
    int numberOfMines(vector<vector<Tile> >& tilesVect, int i, int j);
 
};

#endif /* Tile_h */
