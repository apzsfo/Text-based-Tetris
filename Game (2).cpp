#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <cmath>
using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;



Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width, height) //well accepts arguments
{
    m_score = 0; //score starts off at zero
    m_rowsLeft = 5; //first level requires one vaporizes 5 rows
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
    
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    m_screen.gotoXY(16,3);
    m_screen.printString("Next Piece:"); //prints "next piece" at 16, 3
    m_screen.gotoXY(16,8); //prints "score" at 16, 8
    m_screen.printString("Score:     "+RightJustify(m_score)); //right justify function
    m_screen.gotoXY(16,9); //prints "rows left" at 16, 9
    m_screen.printString("Rows Left: "+RightJustify(m_rowsLeft));
    m_screen.gotoXY(16,10); //prints "level" at 16, 10
    m_screen.printString("Level:     "+RightJustify(m_level));
}

bool Game::playOneLevel()
{
    m_piece_type = chooseRandomPieceType(); //sets first piece to random type
    m_next_piece_type = chooseRandomPieceType(); //sets next piece to random type
    m_well.blankWell(); //clears well at start of new level
    m_rowsLeft = 5 * m_level; //resets rowsLeft to appropriate value
    displayStatus(); //reflects changes of the display
    m_screen.refresh();

    while(m_rowsLeft > 0) //continue level as long as all rows have not been vaporized
    {
        int orientation = 0; //starting out orientation for a piece
        m_next_piece = piece(m_next_piece_type, 0); //m_next_piece gets the value of the corresponding piece vector
        m_piece = piece(m_piece_type, orientation); //current piece gets value of corresponding piece vector
        m_y = 0; //starting out position as specified
        m_x = 4;
        m_well.display(m_screen, 0, 0); //redisplay screen
        printPiece(); //print piece in well
        removeOldPiece(); //removes the next piece from status
        printNextPiece(); //prints new next piece in status
        m_screen.refresh(); //reflects changes
        if(conflict()) //when piece is placed down, if there's an immediate conflict, end game
            return false;
        bool landed = false; //piece is still moving downward
        while (!landed)
        {
            Timer a;
            while(a.elapsed() < std::max(1000-(100*(m_level-1)), 100)) //duration of block position before moving
            {
                char ch; //keystrokes
                if (getCharIfAny(ch))
                {
                    switch(ch)
                    {
                        case 'q':
                        case 'Q':
                            return false; //end game
                        case ARROW_LEFT: //move left
                            if(m_piece_type == PIECE_CRAZY)
                            {
                                m_x++; //increment
                                if(conflict()) //if conflict, decrement
                                    m_x--;
                            }
                            if(m_piece_type != PIECE_CRAZY) //crazy piece operates differently
                            {
                                m_x--;
                                if(conflict())
                                    m_x++;
                            }
                            break;
                        case ARROW_RIGHT: //right
                            if(m_piece_type != PIECE_CRAZY)
                            {
                                m_x++;
                                if(conflict())
                                    m_x--;
                            }
                            if(m_piece_type == PIECE_CRAZY)
                            {
                                m_x--;
                                if(conflict())
                                    m_x++;
                            }
                            break;
                        case ARROW_UP: //rotate
                            orientation++; //change orientation of piece
                            if(orientation == 4) //can't go to orientation 4
                                orientation = 0;
                            m_piece = piece(m_piece_type, orientation); //piece gets assigned a new vector
                            if(conflict()) //if there's a conflict, undo the rotation
                            {
                                orientation--;
                                if(orientation < 0)
                                    orientation = 3;
                                m_piece  = piece(m_piece_type, orientation);
                            }
                            break;
                        case ARROW_DOWN: //down
                            m_y++;
                            if(conflict()){ //if there's a conflict, undo
                                landed=true;
                                m_y--;
                            }
                            a.start(); //reset timer
                            break;
                        case ' ': //fall immediately
                            while(!conflict())
                            {
                                m_y++; //stop incrementing when there's contact
                            }
                            landed=true; //landed at final position
                            m_y--; //decrement 1
                            break;
                    }
                    
                    if(landed)
                    { m_well.placePiece(m_piece, m_x, m_y, m_piece_type); //if landed, put the piece down
                    }
                    m_well.display(m_screen, 0, 0); //redisplay contents
                    printPiece();
                    m_screen.refresh();
                    if(landed) //go on to next piece
                        break;
                }
            }
            m_y++;
            if(conflict()) //if hits block, landed, don't let it collide
            {
                m_y--;
                landed = true;
                m_well.placePiece(m_piece, m_x, m_y, m_piece_type);
                rows_score_setter(); //sets rows left and score
                if(m_rowsLeft > 0) //only vaporize rows if these aren't the final rows of the level
                fullRows();
                displayStatus(); //display updated score and rows left
            }
            m_well.display(m_screen, 0, 0); //redisplay contents
            printPiece();
            m_screen.refresh();
        }
        m_well.display(m_screen, 0, 0);
        m_piece_type = m_next_piece_type; //assign the next piece type and piece
        m_next_piece_type = chooseRandomPieceType();
    }
    return true; //if there are no rows left and you didn't hit a false, you passed the level
}



void Game::printPiece()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m_screen.gotoXY(m_x+i,m_y+j);
            if(m_piece[j][i] == '#') //prints only the #s
            {
                m_screen.printChar(m_piece[j][i]);
            }
        }
    }
}
void Game:: printNextPiece()
{
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
        {
            m_screen.gotoXY(16+column,4+row);
            if(m_next_piece[row][column] == '#') //prints to the display
            {
                m_screen.printChar(m_next_piece[row][column]);
            }
        }
    }
}

void Game::removeOldPiece()
{
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
        {
            m_screen.gotoXY(16+column,4+row);
            m_screen.printChar(' '); //removes old next piece in display to avoid overlap
        }
    }
}

bool Game::conflict() const
{
    bool conflict = false;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_piece[i][j] == '#' && (m_well.getValue(i+m_y, j+m_x) == '@' || m_well.getValue(i+m_y, j+m_x) == '$'|| m_well.getValue(i+m_y, j+m_x) == '*')){ //if a piece collides with an @, $, *, true, else false
                conflict = true;}
        }
    }
    return conflict;
}



string Game::RightJustify(int m)
{
    string s = "       ";
    string amt = to_string(m);
    for(int i = s.length()-amt.length(), j = 0; i < s.length(); i++, j++)
    {
        s[i] = amt[j]; //a function to right justify score, rows left, level
    }
    return s;
}

void Game::rows_score_setter()
{
    int counter = 0;
    for(int row = m_well.getHeight()-2; row >= 0; row--)
    {
        int complete = 0;
        for(int column = m_well.getWidth()-2; column >= 1; column--)
        {
            if(m_well.getValue(row, column) != '$' && m_well.getValue(row, column) != '*')
            {
                break;
            }
            complete++; //uses a counter to determine if the whole row is filled
        }
        if(complete == m_well.getWidth()-2)
        {
            counter++; //counts up number of completed rows
        }
    }
    if(counter > 0) //if the counter is greater than zero, update score and rows left
    {
        m_rowsLeft = m_rowsLeft - counter;
        m_score = m_score + 100*pow(2, counter-1);
    }
    if(m_rowsLeft < 0) //the amount of rows left can never be negative
        m_rowsLeft = 0;
}

void Game::fullRows()
{
    for(int row = m_well.getHeight()-2; row >= 0; row--)
    {
        int complete = 0;
        for(int column = m_well.getWidth()-2; column >= 1; column--)
        {
            if(m_well.getValue(row, column) != '$' && m_well.getValue(row, column) != '*')
            {
                break;
            }
            complete++;
        }
        if(complete == m_well.getWidth()-2) //if row "row" is a vaporized row, proceed to shift all rows down
        {
            for(int r = row-1; r >= 0; r--) //start at the bottom and move upward so you don't lose the values of higher rows
            {
                for(int c = m_well.getWidth()-2; c >= 1; c--)
                {
                    m_well.setValue(r+1, c, m_well.getValue(r, c)); //cycle through each of column of a particular row above the vaporized row
                }
            }
            for(int c = 1; c <= m_well.getWidth()-2; c++)
            {
                m_well.setValue(0, c, ' '); //set the top row to blanks
            }
            row++;
        }
    }
}



