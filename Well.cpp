#include "Well.h"
#include "UserInterface.h"
#include <string>
using namespace std;
Well::Well(int width, int height) : m_width(width+2) , m_height(height+1)
{
    m_wellArray = new char*[m_height]; //dynamically allocates a 2D array
    for(int i = 0; i < m_height; i++)
    {
        m_wellArray[i] = new char[m_width];
    }
    for(int i = 0; i < m_height; i++)  //sets the well's values with @s and blanks
    {
        for(int j = 0; j < m_width; j++) //initializes the foam bomb array to blanks
        {
            if(j == 0 || j == m_width-1 || i == m_height-1)
            {
                m_wellArray[i][j] = '@';
            }
            else
                m_wellArray[i][j] = ' ';
        }
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            foamArray[i][j] = ' ';
        }
    }
}
Well::~Well() //destroys well after use
{
    for(int i = 0; i < m_height; i++)
    {
        delete [] m_wellArray[i];
    }
    delete [] m_wellArray;
}

void Well::display(Screen& screen, int x, int y)  //prints out well array values
{
    for(y = 0; y < m_height; y++)
    {
        for(x = 0; x < m_width; x++)
        {
            screen.gotoXY(x,y);
            screen.printChar(m_wellArray[y][x]);
        }
    }
}
char Well::getValue(int i, int j) const
{
    return m_wellArray[i][j];
}

void Well::setValue(int i, int j, char c)
{
    m_wellArray[i][j] = c;
}

void Well::placePiece(std::vector<std::vector<char>> m_piece, int x, int y, PieceType type)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_piece[i][j] == '#' && type == PIECE_VAPOR) //if piece is vapor, hardcode blanks above and below to simulate vaporization
            {
                setValue(i+y, j+x, ' ');
                if(i+y+1 < m_height - 1 && i+y+1 >= 0) //check for out-of-bounds
                setValue(i+y+1, j+x, ' ');
                if(i+y-1 < m_height-1 && i+y-1 >= 0)
                setValue(i+y-1, j+x, ' ');
                if(i+y+2 < m_height-1 && i+y+2 >= 0)
                setValue(i+y+2, j+x, ' ');
                if(i+y-2 < m_height-1 && i+y-2 >= 0)
                setValue(i+y-2, j+x, ' ');
            }
            if(m_piece[i][j] == '#' && type == PIECE_FOAM) //if foam, copy the contents of the well that are in bounds on to a 5x5 grid
            {
                for(int k = 0; k < 5; k++)
                {
                    for(int m = 0; m < 5; m++)
                    {
                        if(y-1+k < m_height-1 && y-1+k >= 0 && x-1+m < m_width-1 && x-1+m >= 1) //check for boundaries
                            foamArray[k][m] = getValue(y-1+k, x-1+m); //set foam array
                    }
                }
                placeFoam(2, 2); //foam bomb is at center of 5x5, aka 2,2
                for(int k = 0; k < 5; k++)
                {
                    for(int m = 0; m < 5; m++)
                    {
                        if(y-1+k < m_height-1 && y-1+k >= 0 && x-1+m < m_width-1 && x-1+m >= 1) //checks for bounds
                            setValue(y-1+k, x-1+m, foamArray[k][m]); //copies the values of the foam array back onto the well with foam added
                    }
                }
                
            }
            if(m_piece[i][j] == '#' && type != PIECE_FOAM && type != PIECE_VAPOR )
                setValue(i+y, j+x, '$'); //a regular piece simply turns into dollar signs
        }
    }
}

int Well::getHeight() const
{
    return m_height;
}
int Well::getWidth() const
{
    return m_width;
}

void Well::placeFoam(int foamx, int foamy) //foam bomb recursion utilizing the map solver algorithm
{
    if(foamx >= 5 || foamy >= 5 || foamx < 0 || foamy < 0) //checks for out of bounds
                return;
    foamArray[foamx][foamy] = '*';
            if(foamx-1 >= 0 && foamArray[foamx-1][foamy] == ' ') //checks for out of bounds and clear paths
                placeFoam(foamx-1, foamy);
            if(foamx+1 < 5 && foamArray[foamx+1][foamy] == ' ')
                placeFoam(foamx+1, foamy);
            if(foamy-1 >= 0 && foamArray[foamx][foamy-1] == ' ')
                placeFoam(foamx, foamy-1);
            if(foamy+1 < 5 && foamArray[foamx][foamy+1] == ' ')
                placeFoam(foamx, foamy+1);
}

void Well::blankWell() //clears the well at the start of a new level
{
    for(int row = 0; row <= m_height-2; row++)
    {
        for(int column = 1; column <= m_width-2; column++)
        {
            m_wellArray[row][column] = ' ';
        }
    }
}





