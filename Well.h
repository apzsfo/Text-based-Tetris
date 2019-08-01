#ifndef WELL_INCLUDED
#define WELL_INCLUDED
#include "Piece.h"
#include <string>
using namespace std;

class Screen;

class Well
{
public:
    Well(int width, int height);
    ~Well();
    void display(Screen& screen, int x, int y);
    void setValue(int i, int j, char c); //sets the value of the well to a particular value
    char getValue(int i, int j) const; //gets a particular value
    void placePiece(std::vector<std::vector<char>> m_piece, int x, int y, PieceType type);//sets piece based on type
    int getHeight() const;  //returns height of well
    int getWidth() const; //returns width of well
    void placeFoam(int foamx, int foamy); //foam bomb recursion
    void blankWell(); //clears well
    
private:
    char **m_wellArray; //2D dynamic well
    char foamArray[5][5]; //5x5 foam bomb array
    int m_width;
    int m_height;
};

#endif // WELL_INCLUDED

