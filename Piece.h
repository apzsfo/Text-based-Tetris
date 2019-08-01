#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include <vector>
#include "UserInterface.h"

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

std::vector<std::vector<char>> piece(PieceType type, int orientation);  //declaring a vector function that returns a piece

#endif // PIECE_INCLUDED


