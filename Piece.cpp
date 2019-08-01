#include "Piece.h"
#include <vector>

std::vector<std::vector<char>> piece(PieceType type, int orientation) //vector-valued function that returns a vector to Game.cpp of the correct piece based on type and orientation
{
switch(type)
{
    case PIECE_I:   //Piece I and its four positions
        switch(orientation)
        {
            case 0:
            case 2:
                return
            {
                {' ', ' ', ' ', ' '},
                {'#', '#', '#', '#'},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '}
            };
                
            case 1:
            case 3:
                return
            {
                {' ', '#', ' ', ' '},
                {' ', '#', ' ', ' '},
                {' ', '#', ' ', ' '},
                {' ', '#', ' ', ' '}
            };
            
        }
    case PIECE_L:  //piece L and its four positions
        switch(orientation)
    {
        case 0:
            return
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', ' '},
            {'#', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
            
        case 1:
            return
        {
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        };
        case 2:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', ' ', '#', ' '},
            {'#', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        };
        case 3:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '}
        };
    }
    case PIECE_J:  //piece j and its four positions
        switch(orientation)
    {
        case 0:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', '#'},
            {' ', ' ', ' ', '#'},
            {' ', ' ', ' ', ' '}
        };
            
        case 1:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '}
        };
        case 2:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', '#', '#'},
            {' ', ' ', ' ', ' '}
        };
        case 3:
            return
        {
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_T:  //piece t and its four positions
        switch(orientation)
    {
        case 0:
            return
        {
            {' ', '#', ' ', ' '},
            {'#', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
            
        case 1:
            return
        {
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        case 2:
            return
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        case 3:
            return
        {
            {' ', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_O:  //piece o and its four positions
        switch(orientation)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return
        {
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_S:  //piece s and its four positions
        switch(orientation)
    {
        case 0:
        case 2:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
            
        case 1:
        case 3:
            return
        {
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_Z: //piece z and its four positions
        switch(orientation)
    {
        case 0:
        case 2:
            return
        {
            {' ', ' ', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        };
            
        case 1:
        case 3:
            return
        {
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_VAPOR:  //piece vapor and its four positions
        switch(orientation)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return
        {
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_FOAM: //piece foam and its four positions
        switch(orientation)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
    }
    case PIECE_CRAZY:  //piece crazy and its four positions
        switch(orientation)
    {
        case 0:
            return
        {
            {'#', ' ', ' ', '#'},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
            
        case 1:
            return
        {
            {' ', ' ', ' ', '#'},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', '#'}
        };
        case 2:
            return
        {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', ' ', ' ', '#'}
        };
        case 3:
            return
        {
            {'#', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {'#', ' ', ' ', ' '}
        };
            
    }

}
    return   //this should never run
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    };
}
