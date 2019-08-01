#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include "Piece.h"
using namespace std;
class Game
{
public:
    Game(int width, int height); //done
    void play();  //done
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    void printPiece(); //prints piece in well
    void printNextPiece(); //prints new next piece on display status
    void removeOldPiece(); //when displaying next piece, removes old next piece
    void fullRows(); //vaporizes rows and shifts down
    void rows_score_setter(); //sets m_rows and m_score accordingly
    bool conflict() const;//returns true if there's a conflict btwn two pieces, otherwise false
    
    // [Add other members as necessary.]
    
private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    int     m_score; //current score
    int     m_rowsLeft; //amount of rows left
    int m_x; //top left x-coord of bounding box
    int m_y; // top left y-coord of bounding box
    PieceType m_piece_type; //piece type for current piece
    PieceType m_next_piece_type; //piece type for next piece
    string RightJustify(int m); //right justifies the display status text
    std::vector<std::vector<char>> m_piece; //vector accepting current piece
    std::vector<std::vector<char>> m_next_piece; //vector accepting next piece
    
    
    
    
    
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED

