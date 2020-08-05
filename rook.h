#pragma once
#include "common.h"
#include "cmath"
#include "string"
// #include "piece.h"

class rook : public piece{
    public:
        rook(int x, int y, int color, int gridSize, SDL_Renderer *renderer);
        bool Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece);
        bool Checking(int ignore, vector<piece*> &pieces, int draggedPiece);
        bool Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece);
    private:
        
};

rook :: rook(int ix, int iy, int pcolor, int gridSize, SDL_Renderer *renderer) : piece(ix, iy, pcolor, (pcolor == 0) ? "../Chess/wrook.png" : "../Chess/brook.png", gridSize, renderer){
    
}

bool rook :: Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece){
    if(indexx == x && indexy == y)
        return false;
    else if(indexx != x && indexy != y)
        return false;
    int amount;
    if(x != indexx){
        if(indexx > x)
            amount = -1*gridSize;
        else
            amount = 1*gridSize;
        for(int i = indexx+amount; i != x; i+=amount){
            for(int j = 0; j < pieces.size(); j++){
                if(pieces[j]->x == i && pieces[j]->y == indexy)
                    return false;
            }
        }
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->x == indexx && pieces[i]->y == indexy){
                if(pieces[i]->color == color)
                    return false;
                else{
                    if(capture){
                        if(i < draggedPiece)
                            draggedPiece--;
                        delete pieces[i];
                        pieces[i] = nullptr;
                        pieces.erase(pieces.begin()+i);
                    }
                    return true;
                }
            }
        }
        return true;
    }
    else{
        if(indexy > y)
            amount = -1*gridSize;
        else
            amount = 1*gridSize;
        for(int i = indexy+amount; i != y; i+=amount){
            for(int j = 0; j < pieces.size(); j++){
                if(pieces[j]->x == indexx && pieces[j]->y == i)
                    return false;
            }
        }
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->x == indexx && pieces[i]->y == indexy){
                if(pieces[i]->color == color)
                    return false;
                else{
                    if(capture){
                        if(i < draggedPiece)
                            draggedPiece--;
                        delete pieces[i];
                        pieces[i] = nullptr;
                        pieces.erase(pieces.begin()+i);
                    }
                    return true;
                }
            }
        }
        return true;
    }
    
    return true;
}

bool rook :: Checking(int ignore, vector<piece*> &pieces, int draggedPiece){
    for(int xoff = -1; xoff <= 1; xoff+=2){
        int ix = x/gridSize+xoff;
        bool term = false;
        while(ix >= 0 && ix < 8){
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x/gridSize == ix && pieces[i]->y/gridSize == y/gridSize && i != ignore){
                    if(pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
                        return true;
                    }
                    term = true;
                    i = pieces.size();
                }
            }
            if(term)
                break;
            ix += xoff;
        }
    }
    for(int yoff = -1; yoff <= 1; yoff+=2){
        int iy = y/gridSize+yoff;
        bool term = false;
        while(iy >= 0 && iy < 8){
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->y/gridSize == iy && pieces[i]->x/gridSize == x/gridSize && i != ignore){
                    if(pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
                        return true;
                    }
                    term = true;
                    i = pieces.size();
                }
            }
            if(term)
                break;
            iy += yoff;
        }
    }
    return false;
}

bool rook :: Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece){
    if(iy/gridSize == y/gridSize){
        for(int xoff = -1; xoff <= 1; xoff+=2){
            int ax = x/gridSize+xoff;
            bool term = false;
            while(ax >= 0 && ax < 8){
                if(ax == ix/gridSize){
                    return true;
                }
                else{
                    for(int i = 0; i < pieces.size(); i++){
                        if(pieces[i]->x/gridSize == ax && pieces[i]->y/gridSize == y/gridSize){
                            i = pieces.size();
                            term = true;
                        }
                    }
                }
                
                if(term)
                    break;
                ax += xoff;
            }
        }
    }
    else{
        for(int yoff = -1; yoff <= 1; yoff+=2){
            int ay = y/gridSize+yoff;
            bool term = false;
            while(ay >= 0 && ay < 8){
                if(ay == iy/gridSize){
                    return true;
                }
                else{
                    for(int i = 0; i < pieces.size(); i++){
                        if(pieces[i]->y/gridSize == ay && pieces[i]->x/gridSize == x/gridSize){
                            term = true;
                            i = pieces.size();
                        }
                    }
                }
                if(term)
                    break;
                ay += yoff;
            }
        }
    }
    return false;
}